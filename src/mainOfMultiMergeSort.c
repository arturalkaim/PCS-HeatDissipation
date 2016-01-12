/*
 * main.c
 *
 *  Created on: Nov 7, 2014
 *      Author: rafael
 */
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>


#include "MultiMergeSort.c"


int main(int argc, char *argv[]){
	srand(atoi(argv[1]));
	int r = rand();
	int n,i,j,k;

	if(argc<=2) {
	        printf("Args: randSeed Array_Size");
	        exit(1);
	     }  //otherwise continue on our merry way....
	n = atoi(argv[2]);
	n = 1500000;
	printf("RAND_MAX %d\n", RAND_MAX);
	int const numbArrays = 1;
	int* arrays[numbArrays];
	int* copies[numbArrays];
	int sizes[numbArrays];
	for(i=0; i < numbArrays; i++){
		//n=Cenas
		//n = 100000;//TODO
		sizes[i]=n=rand()%2==0?rand()%n:rand()%5000;
		arrays[i]=(int*) malloc(n*sizeof(int));
		copies[i]=(int*) malloc(n*sizeof(int));


		printf("%d\n", sizes[i]);
		for(j=0,k=n-1; j<n;j++,k--){

			arrays[i][j]=j;//rand();
		}
	}

	//FILE * inputFile;
	int teste;
	//inputFile = fopen(argv[1], "r");
	//inputFile = fopen("", "r");
	//teste = fscanf(inputFile, "%d", &n);
	/*if(teste != 1){
		printf("Input error!\n");
		exit(-1);
	}*/

/*	for(i=0; i<n; i++){
		aUp[i] = i;
	}
	for(j=0,i=n; i>0; j++, i--){
		aDown[j]=i;
	}
	for(i=0; i<n; i++){
		aRand[i]=rand();
	}
*/	struct timeval before, after;
	gettimeofday(&before, NULL);
	
	SortSeveral(arrays,copies,sizes,numbArrays);
    
    gettimeofday(&after, NULL);
    double time = (double)(after.tv_sec - before.tv_sec) + 
        (double)(after.tv_usec - before.tv_usec) / 1e6;
    //printf("TIME %f\n ", time );
	/*for (i = 0; i < 10; ++i) {
		printf("%d ", a3[i] );
	}*/
	return 0;
}


/*
 *  rm arrayrm array.txt; for ((i=999;i>=0;i--)) do printf "$i , "; done > array.txt
 * gcc -fopenmp main.c
 *
 *
 */

