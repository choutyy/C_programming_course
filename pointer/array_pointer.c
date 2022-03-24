int main(){
    int v[5] = {1,2,3,4,5};
    print(&v);
    return 0;
}

void print(int *(*vptr)){
    for(int i=0; i<sizeof(*vptr)/sizeof((*vptr[0])); i++)
    printf("%d", (*vptr)[i]);
}

// int main(){
//     int v[3] = {1,2,3};
//     print(v);
//     return 0;
// }

// void print(int *vptr){
//     for(int i=0; i<sizeof(vptr)/sizeof(vptr[0]); i++)
//     printf("%d", vptr[i]);
// }


// int main(){
//     int v[3] = {1,2,3};
//     int num = 3;
//     print(v,num);
//     return 0;
// }
// void print(int *vptr, int n){
//     for(int i=0; i<n; i++)
//     printf("%d", vptr[i]);
// }