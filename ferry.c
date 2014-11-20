/* Ferry Loading Problem - Naomi and Andrew */

#include <stdio.h>
#include <stdlib.h>


int main (){
    FILE* f1 = fopen("ferrydata.txt", "r");
    int num = 0;
    int done = 0;
    double weights[100];


    fscanf(f1, "%d", &num);

    //weights = (double*)(malloc(sizeof(double) * num));
    
    for (int i = 0; i < num; i++){
        fscanf(f1, "%lf", &weights[i]);
    }

    for (int i = 0; i < num; i++){
        printf("%lf\n", weights[i]);
    }
    

    fclose(f1);
    return 0;
}


