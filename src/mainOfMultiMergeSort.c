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

	int r = rand();
	int n,i,j;

	if(argc<=1) {
	        printf("Arg1 Max Array Size");
	        exit(1);
	     }  //otherwise continue on our merry way....
	n = atoi(argv[1]);

	int const numbArrays = 10;
	int* arrays[numbArrays];
	int* copies[numbArrays];
	int sizes[numbArrays];
	for(i=0; i < numbArrays; i++){
		//n=Cenas
		//n = 100000;
		arrays[i]=(int*) malloc(n*sizeof(int));
		copies[i]=(int*) malloc(n*sizeof(int));
		sizes[i]=n;
		for(j=0; j<n;j++){

			arrays[i][j]=rand();
		}
	}
	#include "multiMergeSortSeq.c"
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
*/

	SortSeveral(arrays,copies,sizes,numbArrays);
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

