#include <stdio.h> 
#include <time.h> 
#include <stdlib.h> 
#include <assert.h> 
void array_generator(int array[], int ndim);
void selection_sort(int array[], int ndim);
void array_print(int array[], int ndim);

int main(void) {   
    int n;
    printf("Enter the order of the Matrix :"); 
    scanf("%d", &n); 
    assert(n >=3 && n <=10); 

    int b[n*n];
    //original
    array_generator(b,n);
    array_print(b,n);
    printf("\n");
    //sorted
    selection_sort(b,n);
    array_print(b,n);
    printf("\n");
    
    return 0;
}

void array_generator(int array[], int ndim){
    srand(time(NULL)); 
    
    for (int i = 0;  i<ndim*ndim; i++) 
    {         
        int k = 10 + rand() %90; 
        array[i] = k;         
    } 
    return;
}

void selection_sort(int array[], int ndim){

     for(int i=0; i<ndim*ndim; i++){ 
         for(int j=i+1; j<ndim*ndim; j++) {     
           if(array[i]<array[j])
           {
               int temp = array[i];
               array[i] = array[j];
               array[j]= temp;               
           }
         }
        }
   return;
}

void array_print(int array[], int ndim){
    for(int i=0; i<ndim*ndim; i++){ 
        if(i%ndim == (ndim-1)){
            printf("%5d\n", array[i]); 
        }
        else
            printf("%5d", array[i]);
    }
    return;
}