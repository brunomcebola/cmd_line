#include <stdlib.h>
#include <stdio.h>
#include <string.h>   //funcoes de strings
#include <time.h>     //usada para se poder calcular o tempo
#include <ctype.h>    //toupper and tolower functions
#include <unistd.h>   //permite usar a funcao sleep
#include <stdio.h>    //funçoes de ficheiros
#include <dirent.h>
#include <limits.h>

void SeparaInput(char str[], char instruct[], char directory[]){
    char *token = strtok(str, " ");
    strcpy(instruct, token);
    token = strtok(NULL, " ");
    strcpy(directory,token);
    return;
}

int main()
{

  char cwd[PATH_MAX];
  char str[]="\0";
  char instruct[]="\0";
  char directory[]="\0";
  struct dirent *de;
  DIR *dr;

    while(1){
      if (getcwd(cwd, sizeof(cwd)) != NULL) {
        printf("%s\n", cwd);
        printf("$ ");
        fgets(str, 100, stdin);
        SeparaInput(str, instruct, directory);
          printf("%s", instruct);
            printf("%s\n", directory);
        if(strcmp(instruct,"ls")==0){
          dr = opendir(directory);

          if (dr == NULL)  // opendir returns NULL if couldn't open directory
          {
              printf("Could not find directory\n");
          }

          while ((de = readdir(dr)) != NULL){
            if(de->d_name[0]!='.'){printf("%s\n", de->d_name);}
          }


          closedir(dr);
        }
      }
      printf("\n");
    }

    return 0;
}
