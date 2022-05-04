#include <stdio.h>
#include <math.h>

float Length(int,int); //宣告Length函式

int main(){
 int x=3, y=4;
 printf("Before Normalize: (x,y)=(%d,%d)\n",x,y);
 printf("After Normalize: (x,y)=(%.1f,%.1f)\n",x/Length(x,y),y/Length(x,y));
 //呼叫函式length來標準化向量（x,y)
 return 0;
}

float Length (int x,int y){
 return sqrt(x*x+y*y); //回傳向量x,y的長度
}