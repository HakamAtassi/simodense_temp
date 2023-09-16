/* Copyright 2021 Philippos Papaphilippou

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
*/

#include <stdint.h>
#include <string.h>
#include <stdarg.h>
#include <stdio.h>
#include <limits.h>
#include <sys/signal.h>
#include <stdlib.h>
#include "syscalls.c"
#include <vector>
#include "time.h"





void get_random_B_tile(int **matrix){
    //std::srand(time()); // use current time as seed for random generator

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            matrix[i][j] = std::rand() % 100; // generate random number between 0 and 99
        }
    }
}



void print_tile(int **matrix, int N){
    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){
            printf("%0d ",matrix[i][j]);
        }
            printf("\n");
    }
}




int main() {


    int N = 8;
    int TILE_SIZE = 8;
    int TILED=false;

	// Add lists
    // Do stuff

    std::vector<std::vector<int>> A_tile(N, std::vector<int>(N));
    std::vector<std::vector<int>> B_tile(N, std::vector<int>(N));
    std::vector<std::vector<int>> C_tile(N, std::vector<int>(N, 0));

    for(int i=128;i<=512;i*=2){


        N=i;

        //// Allocate memory for the matrix
        A_tile=std::vector<std::vector<int>>(N, std::vector<int>(N));
        B_tile=std::vector<std::vector<int>>(N, std::vector<int>(N));
        C_tile=std::vector<std::vector<int>>(N, std::vector<int>(N,0));

        printf("Benchmarking for matrix size %0dx%0d size\n", N, N);
        //printf("Tile Size %0dx%0d\n", TILE_SIZE,TILE_SIZE);
        uint64_t time1=time();

        if(TILED==false){

            for(int i=0;i<N;i++){
                for(int j=0;j<N;j++){
                    for(int k=0;k<N;k++){
                        C_tile[i][j]+=A_tile[i][k]*B_tile[j][k];
                    }
                }
            }


        }else{

            for(int i=0;i<N;i+=TILE_SIZE){
                for(int j=0;j<N;j+=TILE_SIZE){
                    for(int k=0;k<N;k+=TILE_SIZE){
                        for(int ii=i;ii<i+TILE_SIZE;ii+=1){
                            for(int jj=j;jj<j+TILE_SIZE;jj+=1){
                                for(int kk=k;kk<k+TILE_SIZE;kk+=1){
                                    C_tile[ii][jj] += A_tile[ii][kk] * B_tile[jj][kk];
                                }
                            }
                        }
                    }
                }
            }

        }

        uint64_t time2=time();
        uint64_t elapsed=time2-time1;
        printf("%llu\n",elapsed);
    }





	// Read cycles and instruction count	


    return 0;
}
