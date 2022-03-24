#include<stdio.h>
void print_str(char[], int n);

int main(){
    char str[] = {'T','h','i','s',' ','i','s',' ','d','o','g','\0'};
    print_str(str, 11);
return 0;
}

void print_str(char str[], int n){
    for(int i = 0; str[i]!='\0'; i++){
    printf("%c",str[i]);
    }
}


// final version 
/*
#include<stdio.h>
void print_str(char[]);

int main(){
    char str[] = {"This is dog"};
    printf("%s",str);
return 0;
}

*/