#include<stdio.h>

int main(){

int array[6] = {1,2,3,4,5,6};
int *iptr;
iptr = array;

// array[0]
printf("%d\n",iptr[0]); // iptr[0] = *(0+iptr)
printf("%d\n",*iptr); // iptr[0] = *(0+iptr)
// array[1]
printf("%d\n",iptr[1]); 
printf("%d\n",*(iptr+1)); 

// array[0]
printf("%d\n",array[0]); // iptr[0] = *(0+iptr)
printf("%d\n",*array); // iptr[0] = *(0+iptr)
// array[1]
printf("%d\n",array[1]); 
printf("%d\n",*(array+1)); 

return 0;
}
