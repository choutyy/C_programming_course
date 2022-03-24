#include<stdio.h>
#define size 20
void str_read(char [], int);

int main(){
    char str[size];
    int max_length = size-1;
    str_read(str, max_length);
    printf("%s", str);
    return 0;
}

void str_read(char str[], int n){
    int i;
    for(i = 0; i<n; i++){
       scanf("%c", &str[i]);
       if (str[i] == '\n') break;
   }
   str[i] = '\0';
}

//    int i = 0;
//    while(1){
//        scanf("%c", &str[i]);
//        if (str[i] == '\n') break;
//        i++;
//    }
//    str[i] = '\0';