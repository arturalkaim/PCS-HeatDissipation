//
//  main.c
//  Test1
//
//  Created by Artur Alkaim on 30/10/14.
//  Copyright (c) 2014 Artur Alkaim. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>
#include "run.h"
#include "input.h"

#define DIRECT_N_CONST(condutivity) (sqrt(2)/(sqrt(2)+1))*(1-condutivity)
#define DIAGONAL_N_CONST(condutivity) (1/(sqrt(2)+1))*(1-condutivity)


#define U(i, j) mat[i==0?(N-1)*M+j:(i-1)*M+j] //up i*M+j


#define D(i, j) mat[((i+1)%N)*M+j] //down


#define L(i, j) mat[i*M + (j==0?M-1:(j-1))] //left


#define R(i, j) mat[i*M+((j+1)%M)] //right

#define RU(i, j) mat[i==0?(N-1)*M + ((j+1)%M):(i-1)*M + ((j+1)%M)] //right up - diagonal

#define RD(i, j) mat[((i+1)%N)*M + ((j+1)%M)] //right down - diagonal

#define LU(i, j) mat[i==0?(N-1)*M + (j==0?M-1:(j-1)) : (i-1)*M + (j==0?M-1:(j-1)) ] //left up - diagonal

#define LD(i, j) mat[((i+1)%N)*M + (j==0?M-1:(j-1))] //left down - diagonal


//1.567000e+00
/*
 calc the next value for the cell mat[i][j] depends on the surroundings
 now is just the average of the 4 direct cells, ignoring diagonals
 */
double nextValue(int i, int j){
    double condty=conductivity[i*M+j];    
    return ((R(i,j) + L(i,j) + U(i,j) + D(i,j))/4)*DIRECT_N_CONST(condty)+((RU(i,j) + LU(i,j) + RD(i,j) + LD(i,j))/4)*DIAGONAL_N_CONST(condty)+mat[i*M+j]*(condty);
    
    
}

double* processCells(double* in){

    int i, j;
    for (j = 0; j< M; j++) {
        for (i = 0; i< N; i++) {
            matAux[i*M+j] = nextValue(i,j);
        }
    }
    mat=matAux;
    matAux=pointerAux;
    pointerAux=mat;
    return mat;
}


/*
 print the matrix to std output
 */
void print(int iter){
    int i, j;
    printf("\n\n%d \n",iter);
    for (i = 0; i< N; i++) {
        for (j = 0; j< M; j++) {
            printf("%5.3f ", mat[i*M+j]);
        }
        printf("\n");
    }
    
}


void calcResoult(struct results*  r){
	//Compare with mat
    double min = tKmax, max=tKmin, average=0, aux2, aux, abs = 0, absAux;
    int i,j;
    for (i = 0; i< N; i++) {
        for (j = 0; j< M; j++) {
        	aux2 = matKth[i*M+j];
            aux = mat[i*M+j];
            absAux = fabs(aux2-aux);
            if(absAux > abs){
            	abs = absAux;
            }
            if (aux<min)
             {
               min = aux;
             } 
             if (aux>max)
             {
               max = aux;
             }
             average += aux; 
        }
    }
    average = average/(N*M);
    r->tmin = min;
    r->tmax = max;
    r->maxdiff = abs;
    r->tavg = average;
    r->time = average*-1;
    tKmin = min;
    tKmax = max;

    //keep the matrix to keep the values.
    memcpy(matKth, mat, N*M*sizeof(double));

}


void run(size_t iter,double thsl, struct results*  r, int k){
    //print(0);
    int i;
    for (i = 0; i< iter; i++) {
        mat = processCells(mat);
        //print(i);
        if(i%k == 0){
        	calcResoult(r);
        	if( r->maxdiff < thsl)
        		break;
        }
    }

    calcResoult(r);

    
    r->niter = i;
    
}


void initiation(const struct parameters* p){
    N = p->N;
    M = p->M;
    tmin = p->io_tmin;
    tmax = p->io_tmax;
    tKmin = tmin;
    tKmax = tmax;
    int range = abs(p->io_tmin) + abs(p->io_tmax);

    printf("%d  %d\n", N, M);

    mat = (double*) calloc(N*M, sizeof(double));
    matAux = (double*) calloc(N*M, sizeof(double));
    matKth = (double*) calloc(N*M, sizeof(double));
    conductivity = (double*) calloc(N*M, sizeof(double));
    pointerAux = mat;
    int i, j,k=0;
    for (i = 0; i< N; i++) {
        for (j = 0; j< M; j++) {
            mat[i*M+j] = p->tinit[k++]*(255/range);
        }
    }
    memcpy(matKth, mat, N*M*sizeof(double));

    for (i = 0; i< N; i++) {
        for (j = 0; j< M; j++) {
            conductivity[i*M+j] = p->conductivity[k++]*(255/range);
        }
    }

}

