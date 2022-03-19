#include "accesstime.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

// Author: Caden Corontzos
// CSCI 389 - Spring 2022

// Handles nanosec overflow
struct timespec diff(struct timespec start, struct timespec end)
{
    struct timespec temp;

    if ((end.tv_nsec-start.tv_nsec)<0)
    {
            temp.tv_sec = end.tv_sec-start.tv_sec-1;
            temp.tv_nsec = 1000000000+end.tv_nsec-start.tv_nsec;
    }
    else 
    {
            temp.tv_sec = end.tv_sec-start.tv_sec;
            temp.tv_nsec = end.tv_nsec-start.tv_nsec;
    }
    return temp;
}

// returns a pointer to an array of size size with values in [bound, -bound]
int8_t* generate_random_list( int size, int bound){
    int8_t* ptr = calloc (size, sizeof(int8_t));
    for(int i = 0 ; i< size; i++){
        ptr[i] = (int8_t) ((rand()%(2*bound)) - bound);
    }
    return ptr;
}

// generates a list of random indicies to query
int* generate_random_index_list( int size, int bound){
    int* ptr = calloc (size, sizeof(int));
    for(int i = 0 ; i< size; i++){
        ptr[i] = (int) ((rand()%(bound)));
    }
    return ptr;
}




int main(){

    // go through buffer sizes by powers of 2
    for(int buffsize=1024; buffsize < 4194305; buffsize*=2 ){

        int numChecks = buffsize*50;
        
        // we have an array to read from, the random indicies that we plan to read, and an array in which to store that data
        int8_t* arrToRead = generate_random_list(buffsize, 127);
        int* indexesToRead = generate_random_index_list(numChecks, buffsize);
        
        double time= 0;
        

        for(int i = 0 ; i< numChecks; i=i+50){


            struct timespec start, end;

            int x = 0 ;
            clock_gettime(CLOCK_MONOTONIC, &start);

            // time 50 accesses to the array
            // There are technically 2 accesses here, since we are accesssing the idexes to read too, but those should be getting prefetched since they are sequential 
            for( int j = 0; j < 50; j++){
                x+= arrToRead[indexesToRead[i+j]];
            }
            clock_gettime(CLOCK_MONOTONIC, &end);
            // write x to a file so that the complier doesn't get smart.
            // to watch this work open out.txt while the program is running
            FILE* fptr = fopen("./out.txt","w");
            fprintf(fptr, "   %i", x);
            fclose(fptr);
            struct timespec dif = diff(start, end);
            time += (dif.tv_nsec/50.0);
     
        }


        // print output and free arrays
        printf("%f", (double) buffsize/1000);
        printf("    %f\n",time/buffsize);
        free(arrToRead);
        free(indexesToRead);
    }
    return 0;
}

