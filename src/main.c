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
#include "main.h"

#define DIRECT_N_CONST(condutivity) (sqrt(2)/(sqrt(2)+1))*(1-condutivity)
#define DIAGONAL_N_CONST(condutivity) (1/(sqrt(2)+1))*(1-condutivity)


double U(int i, int j){
    return mat[i==0?N-1:(i-1)][j]; //up
}

double D(int i, int j){
    return mat[(i+1)%N][j]; //down
}

double L(int i, int j){
    return mat[i][j==0?M-1:(j-1)]; //left
}

double R(int i, int j){
    return mat[i][(j+1)%M]; //right
}

double RU(int i, int j){
    return mat[i==0?N-1:(i-1)][(j+1)%M]; //right up - diagonal
}
double RD(int i, int j){
    return mat[(i+1)%N][(j+1)%M]; //right down - diagonal
}

double LU(int i, int j){
    return mat[i==0?N-1:(i-1)][j==0?M-1:(j-1)]; //left up - diagonal
}

double LD(int i, int j){
    return mat[(i+1)%N][j==0?M-1:(j-1)]; //left down - diagonal
}


/*
 calc the next value for the cell mat[i][j] depends on the surroundings
 now is just the average of the 4 direct cells, ignoring diagonals
 */
double nextValue(int i, int j){
    double condutivity=0.2;
    
    //printf("COND = %f\n", condutivity+DIRECT_N_CONST(condutivity)+DIAGONAL_N_CONST(condutivity));
    
    return ((R(i,j) + L(i,j) + U(i,j) + D(i,j))/4)*DIRECT_N_CONST(condutivity)+((RU(i,j) + LU(i,j) + RD(i,j) + LD(i,j))/4)*DIAGONAL_N_CONST(condutivity)+mat[i][j]*(condutivity);
    
    
}

double** processCells(double** in){
    double ** Amat = (double**) calloc(N, sizeof(double*));
    int i, j;
    for (i = 0; i< N; i++) {
        Amat[i] = (double*) calloc(M, sizeof(double));
    }
    
    for (j = 0; j< M; j++) {
        for (i = 0; i< N; i++) {
            Amat[i][j] = nextValue(i,j);
        }
    }
    
    return Amat;
}




/*
 print the matrix to std output
 */
void print(int iter){
    int i, j;
    printf("\n\n%d \n",iter);
    for (i = 0; i< N; i++) {
        for (j = 0; j< M; j++) {
            printf("%5.3f ", mat[i][j]);
        }
        printf("\n");
    }
    
}

void run(int iter){
    print(0);
    int i;
    for (i = 0; i< iter; i++) {
        mat = processCells(mat);
        print(i);
    }
}

void init(){
    mat = (double**) calloc(N, sizeof(double*));
    int i, j;
    for (i = 0; i< N; i++) {
        mat[i] = (double*) calloc(M, sizeof(double));
    }
    for (i = 0; i< N; i++) {
        for (j = 0; j< M; j++) {
            mat[i][j] = i*M+j;
        }
    }
}

int main(int argc, const char * argv[]) {
    init();
    
    run(91);

    printf("Hello, World!\n");
    return 0;
}
