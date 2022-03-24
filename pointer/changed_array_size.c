#include <stdio.h>
#include <stdlib.h>

int main(){
    int * store = 0; // 0 indicates Null ptr
    int store_length = 0;
    while(1){
        int input; 
        scanf("%d", &input);
        if(input == 0) break;
        int *store_larger = (int*) malloc(sizeof(int) * (store_length+1));
        for (int i = 0; i<store_length; i++) store_larger[i] = store[i]; 
        free(store);
        store = store_larger;
        store[store_length] = input; 
        store_length = store_length+1;
    }
    
    printf("Numbers: ");
    for (int i =0; i<store_length; i++){
        printf("%4d", store[i]);
    }
    printf("\n");
    return 0;
}

// int main(){
//     int *number;
//     int length = 0;

//     while(1){
//         int input;
//         scanf("%d", &input);
//         if (input == 0) break;
//         int larger[0]; // need to use malloc
//         for(int i =0; i<length; i++) larger[i] = number[i];
//         number = larger;
//         number[length] = input;
//         length++;
//     }
//     printf("Numbers: ");
//     for(int i =0; i<length; i++){
//         printf("%d", number[i]);
//     }
//     printf("\n");
//     return 0;
// }