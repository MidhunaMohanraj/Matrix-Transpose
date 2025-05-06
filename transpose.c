/**
 ** SUBMIT ONLY THIS FILE
 ** NAME: .......
 ** UCI ID: .......
 **
 ** Use only standard libraries.
 ** See description in header file.
 **/

#include "util_common.h"
#include "transpose.h" //implementing
#include <pthread.h> // needed for threads

typedef struct {
    Mat *a;
    int grain;
} ThreadArgs;

pthread_mutex_t lock;
int i = 0;
int j = 1;

#ifdef DEBUG
#include <stdio.h> //remove if not using.
#endif

// mat->ptr[i*n + j] how to access the matrix
void mat_squaretransp_sequential(Mat *mat){
    
    // YOUR CODE GOES HERE
    int temp;
    int n = mat->n;
    for(int i = 0; i< n; i++){
        for (int j = i + 1; j <= n-1; j++){
            //swap mat [i][j] and mat[j][i]
            temp = mat->ptr[i*n + j];
            mat->ptr[i*n + j] = mat->ptr[j*n + i];
            mat->ptr[j*n + i] = temp;
        
        }
    }
    return;
}

// 
void* ith_thread(void* arg){ // thread function to perform certain number grains of work
    while(1){
        ThreadArgs *args = (ThreadArgs*) arg;
        // for loop using grain
            // transpose one element of matrix
        
        // get the current i and j and increment them
        int current_i;
        int current_j;
        int n = args->a->n;
        pthread_mutex_lock(&lock);
        int overflow = 0;
        current_i = i;
        current_j = j;
        j += args->grain;
        // if (j<=n-1){ // overflow
        //     i += j/n; // how many rows to 
        // }

        // while( j > n - 1){
        //     i += 1;
        //     j -= n;
        // }                   

        // if(j>n-1){ // check if moving to next row
        //     i+=j/n; // how many rows to move down
        //     int old_j = j;
        //     j=i; // set j = to diagonal
        //     j+=old_j%n; // add remainder to j to find out where to begin for next thread
        // }


        // incremental solution for finding next index for next thread to work on
        int remaining_increments = args->grain;
        if (i == n - 1){
            return;
        }
        while (remaining_increments > 0){
            j += 1;
            remaining_increments -= 1;
            if (j > n- 1){
                i += 1;
                j= i + 1;
            }
        }
        

        pthread_mutex_unlock(&lock);
        for(int current_j=0; j<args->grain; j++){ // 
            // use row major 
            
        }

        int remaining_work = args->grain;
        // use current i j
        while (remaining_work > 0){
            j += 1;
            remaining_work -= 1;
            if (j > n - 1){
                i += 1;
                j= i + 1;
            }
        }
    }
}

void mat_squaretransp_parallel(Mat *mat, unsigned int grain, unsigned int thr){
    
    // YOUR CODE GOES HERE
    pthread_mutex_init(&lock, NULL);
    pthread_t thread[thr];
    ThreadArgs args[thr];
    for (int i=0; i < thr; i++){ // creates thr # of threads
        // args to pass into thread function: struct of: grain, matrix,
        args[i].a=mat;
        args[i].grain=grain;

        //create
    
       
       
        pthread_create(&thread[i], NULL, ith_thread, NULL);
    }



    //>>>>>>>> DELETE THE CODE BELOW
    // this is a useless demo code. Delete it before
    // submittiong your solution.
// #ifdef DEBUG
//     printf("TO UNDEFINE THE MACRO 'DEBUG', COMMENT common/util_common.c:15\n");
//     printf("mat: {%p, %u, %u}\n", mat->ptr, mat->m, mat->n);
//     printf("grain: %u\n", grain);
//     printf("threads: %u\n", thr);
// #endif
    //<<<<<<<< DELETE UP TO THIS POINT

    
    return NULL;
}
