#include<stdio.h>
typedef struct complex{
    int real;
    int imag;
} complex;

void addComplex(const complex *a, const complex *b, complex *c){
    c->real = a->real + b->real;
    c->imag = a->imag + b->imag;
    return;
}

void printComplex(const complex *c){
    printf("%d+i%d", c->real, c->imag);
    return;
}

int main(void)
{
    complex a,b,c;
    scanf("%d", &(a.real));
    scanf("%d", &(a.imag));
    scanf("%d", &(b.real));
    scanf("%d", &(b.imag));

    addComplex(&a,&b,&c);
    printComplex(&c);

    return 0;
}



/*void addComplex(const complex *, const complex *, complex *);
void mulComplex(struct complex *, struct complex *, struct complex *);
void printComplex(const struct complex *);*/

