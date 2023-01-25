#include "the4.h"
#include <iostream>

int dp_sln(char**& arr1, char**& arr2, int nrow, int ncol1, int ncol2, int**& mem){ //dynamic programming
    mem[0][0]=0;
    char** copy_arr2 = new char*[nrow];

    for(int i=0; i<nrow; i++){
        copy_arr2[i] = new char[ncol2];
    }

    for(int i=0; i<nrow; i++){
        for(int j=0; j<ncol2; j++){
            copy_arr2[i][j] = arr2[i][j]; 
        }
    }

    // First row of mem array
    for(int i=0;i<ncol2;i++){
        int count =0;
        for(int j=0;j<nrow;j++){
            if(arr2[j][i]!='-'){
                count++;
            }
        }
        mem[0][i+1]=mem[0][i] + count;
    }

    // First column of mem array
    for(int i=0;i<ncol1;i++){
        int count2 = 0;
        for(int j=0;j<nrow;j++){
            if(arr1[j][i] != '-'){
                count2++;
            }
        }
        mem[i+1][0]=mem[i][0] + count2;
    }
    
    for(int i=1; i<=ncol1; i++){ // box1
        for(int j=1; j<=ncol2; j++){ // box2
            // sol ve üste bak reordera replacementa bak hallet
            int insertion_cost = 0;
            int deletion_cost = 0;
            int reordering_cost = 0;
            int replacement_cost = 0;

            for(int k=0; k<nrow; k++){
                if(arr2[k][j-1] != '-'){
                    insertion_cost++;
                }
            }

            for(int l=0; l<nrow; l++){
                if(arr1[l][i-1] != '-'){
                    deletion_cost++;
                }
            }

            bool is_columns_same = true;
            
            // reordering case
            int last = nrow-1;
            for(int x=0; x<nrow; x++){
                for(int y=0; y<nrow; y++){
                    if((arr1[x][i-1] == arr2[y][j-1]) && (copy_arr2[y][j-1] != '*')){
                        copy_arr2[y][j-1] = '*';
                        break;
                    }
                    else if(y == last){
                        is_columns_same = false;
                    }
                }
                if(is_columns_same == false){
                    break;
                }
            }

            if(is_columns_same == true){
                for(int t=0; t<nrow; t++){
                    if(arr1[t][i-1] != arr2[t][j-1]){
                        reordering_cost++;
                    }
                }
            }

            // replacement case
            for(int m = 0; m < nrow; m++){
                if(arr1[m][i-1] != arr2[m][j-1]){
                    if(arr1[m][i-1] == '-' || arr2[m][j-1] == '-'){
                        replacement_cost += 2;
                    }
                    else{
                        replacement_cost ++;
                    }
                }
            }

            int total_cost = 0;
            if(reordering_cost != 0){
                if(replacement_cost > reordering_cost){
                    total_cost = reordering_cost;
                }
                else if(replacement_cost < reordering_cost){
                    total_cost = replacement_cost;
                }
            }
            else{
                total_cost = replacement_cost;
            }
            
            int temp_cost = fmin(mem[i-1][j]+deletion_cost, mem[i][j-1]+insertion_cost);
            if(temp_cost <= mem[i-1][j-1]+total_cost){
                mem[i][j] = temp_cost;
            }
            else if(temp_cost > mem[i-1][j-1]+total_cost){
                mem[i][j] = mem[i-1][j-1]+total_cost;
            }

        }
    }
    for(int i=0; i<nrow; i++){
        delete[]copy_arr2[i];
    }
    delete copy_arr2;   
    return mem[ncol1][ncol2];
}



