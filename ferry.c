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


    fscanf(f1, "%d", &num);

    //weights = (double*)(malloc(sizeof(double) * num));
    
    for (int i = 0; i < num; i++){
        fscanf(f1, "%lf", &weights[i]);
    }

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

   	biggie i, j;
   	// Loop until sun goes supernova * 2000 in worst case
   	for (i = 0; i < hi; i++) {
   		for (j = 0; j < lo; j++) {
   			for (int k = 0; k < 64; k++) {
   				if ((j >> k) & 1) {
   					sum_left += weights[k];
   				}
   				if (i > 0) {
   					if ((i >> k) & 1) {
   						sum_left += weights[k + 64];
   					}
   				}
   			}

   			// Check to see if sum of left side within 2% of sum of right side
   			sum_right = total_weight - sum_left;
   			accept = (0.02 * sum_right);

   		}
   	}


    return 0;
}


