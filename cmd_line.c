#include <stdlib.h>
#include <stdio.h>
#include <string.h>   //funcoes de strings
#include <time.h>     //usada para se poder calcular o tempo
#include <ctype.h>    //toupper and tolower functions
#include <unistd.h>   //permite usar a funcao sleep
#include <stdio.h>    //funçoes de ficheiros
#include <dirent.h>
#include <limits.h>

int main()
{

  char cwd[PATH_MAX];
  char dir[]="\0";
  struct dirent *de;  // Pointer for directory entry
  // opendir() returns a pointer of DIR type.
  DIR *dr;

    while(1){
      if (getcwd(cwd, sizeof(cwd)) != NULL) {
        printf("%s\n", cwd);
        printf("$ ");
        gets(dir);
        dr = opendir(dir);

        if (dr == NULL)  // opendir returns NULL if couldn't open directory
        {
            printf("Could not find directory\n");
        }

        while ((de = readdir(dr)) != NULL)
                printf("%s\n", de->d_name);

        closedir(dr);
      }
    }

    return 0;
}
