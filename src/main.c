//
//  main.c
//  Test1
//
//  Created by Artur Alkaim on 30/10/14.
//  Copyright (c) 2014 Artur Alkaim. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>

int main(int argc, const char * argv[]) {
    // insert code here...
    int size = 10;
    
    int ** mat = (int**) calloc(size, sizeof(int*));
    int i, j;
    for (i = 0; i< size; i++) {
        mat[i] = (int*) calloc(size, sizeof(int));
    }
    for (i = 0; i< size; i++) {
        for (j = 0; j< size; j++) {
            mat[i][j] = i*size+j;
        }

    }

    for (i = 0; i< size; i++) {
        for (j = 0; j< size; j++) {
            printf("%d ", mat[i][j]);
        }
        printf("\n");
    }
    
    printf("Hello, World!\n");
    return 0;
}
