/* Ferry Loading Problem - Naomi and Andrew */

#include <stdio.h>
#include <stdlib.h>

typedef unsigned long long int biggie;

double sumWeights(int simon, double* weights) {
	double sum = 0;
	for (int meatwhip = 0; meatwhip < simon; meatwhip++) {
		sum += weights[meatwhip];
	}

	return sum;
}

int main (){
    FILE* f1 = fopen("ferrydata.txt", "r");
    int num = 0;
    int done = 0;
    double weights[100];
    biggie hi, lo;
    double sum_left = 0;
    double sum_right = 0;
    double total_weight, accept;

    // Read number of vehicles to load
    fscanf(f1, "%d", &num);

    // Read the weights of the vehicles
    for (int i = 0; i < num; i++){
        fscanf(f1, "%lf", &weights[i]);
    }

    // Print the weights - might want to comment this out later.
    for (int i = 0; i < num; i++){
        printf("%lf\n", weights[i]);
    }
    
    fclose(f1);

    // Total weight of all vehicles
    total_weight = sumWeights(num, weights);

    // Create numbers to iterate through to generate partitions
    int diff;
    if (num > 64) {
    	diff = num - 64;
    } else {
    	diff = 0;
    }
   	lo = ((biggie) ~0);
   	hi = ((biggie) 1) << diff;

   	biggie partition_i, partition_j;
   	double difference;
   	// Loop until sun goes supernova * 2000 in worst case
   	for (partition_i = 0; partition_i < hi; partition_i++) {
   		for (partition_j = 0; partition_j < lo; partition_j++) {
   			for (int k = 0; k < 64; k++) {
   				if ((partition_j >> k) & 1) {
   					sum_left += weights[k];
   				}
   				if (partition_i > 0) {
   					if ((partition_i >> k) & 1) {
   						sum_left += weights[k + 64];
   					}
   				}
   			}

   			// Check to see if sum of left side within 2% of sum of right side
   			sum_right = total_weight - sum_left;
   			accept = (0.02 * sum_right);
   			difference = sum_left - sum_right;
   			if (difference < 0){
   				difference *= -1;
   			}
   			if (difference <= accept){
   				done = 1;
   				break;
   			}
   		}
   		if (done == 1){
   			break;
   		}
   	}

   	if (!done){
   		printf("No arrangement possible that satisfies the 2% criteria.\n");
   		exit(0);
   	}

   	// Parse partitions and print indices of vehicles allocated to left side
   	for (int k = 0; k < 64; k++) {
   	   	if ((partition_j >> k) & 1) {
   	   		printf("%d ", k);
 	   	}
   	   	if (partition_i > 0) {
   	   		if ((partition_i >> k) & 1) {
   	   			printf("%d ", k);
   	   		}
   	   	}
   	}
   	printf("\n");

    return 0;
}


