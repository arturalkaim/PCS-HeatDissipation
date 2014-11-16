/*
 * main.c
 *
 *  Created on: Nov 7, 2014
 *      Author: rafael
 */
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]){

	srand(time(NULL));
	int r = rand();
	int n,i,j;

	if(argc<=1) {
	        printf("You did not feed me arguments, I will die now :( ...");
	        exit(1);
	     }  //otherwise continue on our merry way....
	      n = atoi(argv[1]);

	int* aUp = (int*) malloc(n*sizeof(int));
	int* aDown = (int*) malloc(n*sizeof(int));
	int* aRand = (int*) malloc(n*sizeof(int));

	int* b = (int*) malloc(n*sizeof(int));
	#include "mergeSortSeq.c"

	//FILE * inputFile;
	int teste;
	//inputFile = fopen(argv[1], "r");
	//inputFile = fopen("", "r");
	//teste = fscanf(inputFile, "%d", &n);
	/*if(teste != 1){
		printf("Input error!\n");
		exit(-1);
	}*/

	for(i=0; i<n; i++){
		aUp[i] = i;
	}
	for(j=0,i=n; i>0; j++, i--){
		aDown[j]=i;
	}
	for(i=0; i<n; i++){
		aRand[i]=rand();
	}


	TopDownMergeSort(aUp, b, n);
	TopDownMergeSort(aDown, b, n);
	TopDownMergeSort(aRand, b, n);

	int i = 0;
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

