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


#define TILE_SIZE 4



void get_random_B_tile(int **matrix){
    std::srand(time()); // use current time as seed for random generator

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            matrix[i][j] = std::rand() % 100; // generate random number between 0 and 99
        }
    }
}



void print_tile(int matrix[TILE_SIZE][TILE_SIZE]){
    for(int i=0;i<TILE_SIZE;i++){
        for(int j=0;j<TILE_SIZE;j++){
            printf("%0d ",matrix[i][j]);
        }
            printf("\n");
    }
}





void main(int argc, char** argv) {


	#include "mats_c/GD99_c.c"

    int N=sizeof(row_ptr)-1;
    N=N/sizeof(row_ptr[0]);
    printf("MATRIX SIZE: %0d\n", N);


    // Allocate memory for the matrix
    std::vector<std::vector<int>> B(N, std::vector<int>(N));
    std::vector<std::vector<int>> C(N, std::vector<int>(N, 0));


    //get_random_B_tile(B);



	uint64_t time0=time(); 
	uint64_t icount0=insn();
	// Add lists
    // Do stuff


    





	// Read cycles and instruction count	
	uint64_t time1=time()-time1;
	uint64_t icount1=insn()-icount1;  


    return;
}
