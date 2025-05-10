/* SUBMIT ONLY THIS FILE */
/* NAME: Eric Huang */ /* UCI ID: 59504944 */
/* NAME: Midhuna Mohanraj */ /* UCI ID: 39922268 */
/* NAME: Destin Wong */ /* UCI ID: 64848542 */
 /* Use only standard libraries.
 ** See description in header file.
 **/

#include "util_common.h"
#include "transpose.h" //implementing
#include <pthread.h> // needed for threads

typedef struct {
    Mat *a;
    int grain;
    int thread_index;
    int number_threads;
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
        // int overflow = 0;
        // current i and j for the thread to start swapping at
        current_i = i;
        current_j = j;

                // incrementng rowwise
        // while remaining jump is more than the avalable spots left of the diagonal
        int remaining_jump = args->grain; //some amount
        while (remaining_jump > n - j - 1){
            // first subtract remaining dist from j to end of row
            int dist_from_j_to_n = n - j - 1;
            remaining_jump -= dist_from_j_to_n;

            // then jump to next i
            i += 1;
            if (i > n - 1){
                // pthread_mutex_unlock(&lock);
                break;
            }
            j = i;
        }
        j += remaining_jump;
        // printf("i is %d, j is %d\n", i, j);
        
       
        if (current_i > n - 2 ){ // if on last row, done transposing
            // printf("i is %d, n is %d\n", i, n);
            pthread_mutex_unlock(&lock);
            break;
        }
        pthread_mutex_unlock(&lock);
        // incremental solution for finding next index for next thread to work on
        // int remaining_increments = args->grain;
        // while(remaining_increments > 0){
        //     j += 1;
        //     remaining_increments -= 1;
        //     if (j > n- 1){
        //         i += 1;
        //         j= i + 1;
        //     }
        //     // printf("j: %d\n", j);
        // }
        // // printf("i: %d, j: %d\n", i, j);
        // // printf("after i: %d, after j: %d\n", i, j);

        // pthread_mutex_unlock(&lock);
        // for(int current_j=0; j<args->grain; j++){ // 
        //     // use row major 
            
        // }
    
        int remaining_work = args->grain;
        // use current i j
        // swap grain # of elements
        while (remaining_work > 0 && current_i != n - 1){
            int temp = args->a->ptr[current_i*n + current_j];
            // printf("swapping %d and %d\n", current_i, current_j);
            args->a->ptr[current_i*n + current_j] = args->a->ptr[current_j*n + current_i];
            args->a->ptr[current_j*n + current_i] = temp;
            current_j += 1;
            remaining_work -= 1;
            if (current_j > n - 1){
                current_i += 1;
                current_j= current_i + 1;
            }
        }
        // i and j should now be updated for the next thread
        // swap grain # of elements
        // for(int g = 0; g< args->grain; g++){
            // swap i and j
            // for(int x = current_i;x<n; x++){
            //     for (int y = current_j; y < n; y++){
            //         //swap mat [x][y] and mat[y][x]
            //         int temp = args->a->ptr[x*n + y];
            //         printf("temp is %d\n", temp);
            //         args->a->ptr[x*n + y] = args->a->ptr[y*n + x];
            //         args->a->ptr[y*n + x] = temp;
            //     }
            // }
        // }
        
    




        // PSEUDOCODE FOR NO MUTEX

        // get grain size, number of threads, and starting index
        // set current starting index to starting index
        // while i is less than n-1:
            // do a grain amount of work while i is less than n-1
            // jump to the next starting index by adding grain * number threads to the current starting index
    }
    return NULL;
}

void mat_squaretransp_parallel(Mat *mat, unsigned int grain, unsigned int thr){
    
    // YOUR CODE GOES HERE
    int numThreads = (int)thr;
    pthread_mutex_init(&lock, NULL);
    pthread_t thread[numThreads];
    ThreadArgs args[numThreads];
    for (int i=0; i < numThreads; i++){ // creates thr # of threads
        // args to pass into thread function: struct of: grain, matrix,
        args[i].a=mat;
        args[i].grain=grain;
        args[i].thread_index=i;
        //create threads
        // printf("Creating thread %d\n", i);
        pthread_create(&thread[i], NULL, ith_thread, &args[i]);
    }
    for (int i=0; i < numThreads; i++){
        pthread_join(thread[i], NULL); //join each thread we created
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

    
    return;
}
