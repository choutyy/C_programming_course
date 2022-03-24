#include<stdio.h>
#include<string.h>

// int main()
// {
//     char origin[5] = "This"; // 5 elements including '\0'
//     char *copy;

//     copy = origin; // copy is a string pointer

//     printf("%s", copy);
//     return 0;
// }

/* strcpy example */
#include <stdio.h>
#include <string.h>

int main ()
{
  char *str1 = "Sample string";
  char str2[50];
  char str3[50];
  strcpy (str2,str1);
  strcpy (str3,"copy successful");
  printf ("str1: %s\nstr2: %s\nstr3: %s\n",str1,str2,str3);
  return 0;
}