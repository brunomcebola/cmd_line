#include <stdlib.h>
#include <stdio.h>
#include <string.h>   //funcoes de strings
#include <time.h>     //usada para se poder calcular o tempo
#include <ctype.h>    //toupper and tolower functions
#include <unistd.h>   //permite usar a funcao sleep
#include <termios.h>  //permite usar a funcao tcflush
#include <stdio.h>    //funçoes de ficheiros

int main() {
  FILE *fptr;
  
  fptr = fopen("myfile.txt", "w");
  if (fptr == NULL) {
    printf("Error opening file.");
    return -1;
  }
  fclose(fptr);
  return 0;
}
