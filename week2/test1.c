#include <stdio.h>  
#include <stdlib.h> 
 
int y = 3;  
 
int main(int argc, char *argv[]) { 
  printf("location of code : %p\n", main); 
  printf("location of heap : %p\n", malloc(10)); 
  printf("location of data : %p\n", &y); 
  int x = 3; 
  printf("location of stack: %p\n", &x); 
  return x; 
} 