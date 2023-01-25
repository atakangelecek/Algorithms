#include "the3.h"

// recursive ve memoizationdaki i ==> arr(size)-1 


int recursive_sln(int i, char**& arr, int*& len, int &number_of_calls) { //direct recursive
    number_of_calls+=1;

    // i ===> arr(size)-1
    
    bool flag1=false;
    bool flag2=false;
    bool flag3=false;
    int k,m,max;
    int temp_max = 0;
    
    // Pseudocodeun ilk casei
    if(number_of_calls == 1){

        // i'nin olduğu index kullanılacak mı case'i
        for(k = i-1; k>=0; k--){
            if((arr[i][0] =='I' && arr[k][1] =='O') || (arr[i][0] =='O' && arr[k][1] =='I') || (arr[i][0] =='S' && arr[k][1] =='S')){
                flag1 = true;
                break;
            }
        }
        for(int y=i-1; y >= 0; y--){
            max = recursive_sln(y, arr, len, number_of_calls);
            if(max > temp_max){
                temp_max = max;
            }
        }
        if(flag1 == true){
            return fmax(temp_max, (len[i] + recursive_sln(k, arr, len, number_of_calls)));
        }
        else if(flag1 == false){
            return fmax(temp_max,len[i]);
        }
    }

    else if(i > 0){
        // i'nin olduğu index kullanılmayacak mı case'i
        for(m = i-1; m>=0; m--){
            if((arr[i][1] =='I' && arr[m][1] =='I') || (arr[i][1] =='O' && arr[m][1] =='O') || (arr[i][1] =='S' && arr[m][1] =='S')){
                flag2 = true;
                break;
            }
        }

        // i'nin olduğu index kullanılacak mı case'i
        for(k = i-1; k>=0; k--){
            if((arr[i][0] =='I' && arr[k][1] =='O') || (arr[i][0] =='O' && arr[k][1] =='I') || (arr[i][0] =='S' && arr[k][1] =='S')){
                flag3 = true;
                break;
            }
        }

        if(flag2 && flag3){
            return fmax(recursive_sln(m, arr, len, number_of_calls), (len[i] + recursive_sln(k, arr, len, number_of_calls))); 
        }
        else if(flag2 == true && flag3 == false){
            return fmax(recursive_sln(m, arr, len, number_of_calls), len[i]);
        }
        else if(flag2 == false && flag3 == true){
            return len[i] + recursive_sln(k, arr, len, number_of_calls);
        }
        else{
           return len[i];
        }
    }
    else if(i==0){
        return len[i];
    }
}



int memoization_sln(int i, char**& arr, int*& len, int**& mem) { //memoization
    if(i == 0){
        mem[0][0] = mem[0][1] = mem[0][2] = 0;
    
        if(arr[0][1] == 'I'){
            mem[0][0] = len[0];
        }
        else if(arr[0][1] == 'O'){
            mem[0][1] = len[0];
        }
        else if(arr[0][1] == 'S'){
            mem[0][2] = len[0];
        }
        return 0;
    }
    else{
        memoization_sln(i-1, arr, len, mem);
        for(int k=1; k <= i; k++){
            mem[k][0] = mem[k-1][0]; mem[k][1] = mem[k-1][1]; mem[k][2] = mem[k-1][2];
                
            // hangi columnu değiştirceğimizi bulma
            int column_index;
            if(arr[k][1] == 'I'){column_index=0;}
            else if(arr[k][1] == 'O'){column_index=1;}
            else if(arr[k][1] == 'S'){column_index=2;}
        
            bool is_found = false;
            int found_index;
            // match bulma 
            for(int j=k-1; j>=0; j--){
                if( (arr[k][0] =='I' && arr[j][1] =='O') || (arr[k][0] =='O' && arr[j][1] =='I') || (arr[k][0] =='S' && arr[j][1] =='S') ){
                    is_found = true;
                    found_index = j;
                    break;
                }
            }
            if(is_found){
                if(arr[found_index][1] == 'I'){
                    mem[k][column_index] = fmax(mem[k-1][column_index], (mem[found_index][0]+len[k]));
                }
                else if(arr[found_index][1] == 'O'){
                    mem[k][column_index] = fmax(mem[k-1][column_index], (mem[found_index][1]+len[k]));
                }
                else if(arr[found_index][1] == 'S'){
                    mem[k][column_index] = fmax(mem[k-1][column_index], (mem[found_index][2]+len[k]));
                }
            }
            else{
                mem[k][column_index] = fmax(mem[k-1][column_index],len[k]);
            }
        }
    }
    int max1 = fmax(mem[i][0], mem[i][1]);
    return fmax(max1,mem[i][2]);
}



int dp_sln(int size, char**& arr, int*& len, int**& mem) { //dynamic programming

    mem[0][0] = mem[0][1] = mem[0][2] = 0;
    
    if(arr[0][1] == 'I'){
        mem[0][0] = len[0];
    }
    else if(arr[0][1] == 'O'){
        mem[0][1] = len[0];
    }
    else if(arr[0][1] == 'S'){
        mem[0][2] = len[0];
    }
    
    for(int i=1; i<size; i++){
        mem[i][0] = mem[i-1][0]; mem[i][1] = mem[i-1][1]; mem[i][2] = mem[i-1][2];
        
        // hangi columnu değiştirceğimizi bulma
        int column_index;
        if(arr[i][1] == 'I'){column_index=0;}
        else if(arr[i][1] == 'O'){column_index=1;}
        else if(arr[i][1] == 'S'){column_index=2;}

        bool is_found = false;
        int found_index;
        // match bulma 
        for(int j=i-1; j>=0; j--){
            if( (arr[i][0] =='I' && arr[j][1] =='O') || (arr[i][0] =='O' && arr[j][1] =='I') || (arr[i][0] =='S' && arr[j][1] =='S') ){
                is_found = true;
                found_index = j;
                break;
            }
        }
        if(is_found){
            if(arr[found_index][1] == 'I'){
                mem[i][column_index] = fmax(mem[i-1][column_index], (mem[found_index][0]+len[i]));
            }
            else if(arr[found_index][1] == 'O'){
                mem[i][column_index] = fmax(mem[i-1][column_index], (mem[found_index][1]+len[i]));
            }
            else if(arr[found_index][1] == 'S'){
                mem[i][column_index] = fmax(mem[i-1][column_index], (mem[found_index][2]+len[i]));
            }
        }
        else{
            mem[i][column_index] = fmax(mem[i-1][column_index],len[i]);
        }
    }
    
    int max1 = fmax(mem[size-1][0], mem[size-1][1]);
    return fmax(max1,mem[size-1][2]);
}

