#include "the2.h"
#include <cmath>
// You may write your own helper functions here
void counting_sort(int* arr, int arr_size, int max_number, long& no_of_iterations, int exp, int groupsize){
    int count_arrsize = (int) (pow(10,groupsize)+0.5);
    int* count_arr = new int[count_arrsize];
    int* result_arr = new int[arr_size];

    for(int i=0; i<count_arrsize; i++){
        count_arr[i] = 0;
    }

    for(int j=0; j<arr_size; j++){
        count_arr[(arr[j] / exp) % ((int) (pow(10,groupsize)+0.5))]++;
        no_of_iterations++;
    }

    for(int i=1; i<count_arrsize; i++){
        count_arr[i] = count_arr[i] + count_arr[i-1];
        no_of_iterations++;
    }

    for(int j=arr_size-1; j>=0; j--){
        result_arr[count_arr[(arr[j] / exp) % ((int) (pow(10,groupsize)+0.5))]-1] = arr[j];
        count_arr[(arr[j] / exp) % ((int) (pow(10,groupsize)+0.5))]--;
        no_of_iterations++;
    }

    for(int j=0; j<arr_size; j++){
        arr[j] = result_arr[j];
        no_of_iterations++;
    }
    
    delete []result_arr;
    delete []count_arr;
}


long multiDigitRadixSort(int* arr, bool ascending, int arraySize, int groupSize, int maxDigitLength){
    long numberOfIterations = 0;
    int max_number = (int) (pow(10,maxDigitLength)+0.5);

    if(maxDigitLength % groupSize == 0){
        for (int exp = 1; (max_number-1) / exp > 0; exp *= (int) (pow(10,groupSize)+0.5)){
            counting_sort(arr, arraySize, max_number, numberOfIterations, exp, groupSize);
        }
    }

    else if(maxDigitLength % groupSize != 0){
        int digit = (int) (pow(10,groupSize)+0.5);
        for (int exp = 1; (max_number-1) / exp > 0; exp *= digit){
            if(!((max_number-1) / (exp*digit) > 0)){
                digit = (int) (pow(10,(maxDigitLength % groupSize))+0.5);
                groupSize = (maxDigitLength % groupSize);
            }
            counting_sort(arr, arraySize, max_number, numberOfIterations, exp, groupSize);
        }
    }

    if(ascending == false){
        int last = arraySize-1;
        for(int i=0; i<arraySize/2; i++){
            int temp = arr[i];
            arr[i] = arr[last];
            arr[last] = temp;
            last--;
        }
    }
    
    return numberOfIterations;
}