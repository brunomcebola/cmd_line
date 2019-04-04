#include <stdlib.h>
#include <stdio.h>
#include <string.h>   //funcoes de strings
#include <time.h>     //usada para se poder calcular o tempo
#include <ctype.h>    //toupper and tolower functions
#include <unistd.h>   //permite usar a funcao sleep
#include <stdio.h>    //funçoes de ficheiros
#include <dirent.h>
#include <limits.h>

void SeparaInput(char str[200], char instruction[20], char directory[180]){
    char *token = strtok(str, " ");
    if(token[strlen(token)-1]=='\n'){
      strncpy(instruction,token,strlen(token)-1);
    }
    else{
      strcpy(instruction,token);
    }

    token = strtok(NULL, " ");
    if(token != NULL){
      strncpy(directory,token,strlen(token)-1);
    }
    return;
}

int main()
{

  char cwd[PATH_MAX]="\0";
  char str[200]="\0";
  char instruction[20]="\0";
  char directory[180]="\0";
  struct dirent *de;
  DIR *dr;

    while(1){
      if (getcwd(cwd, sizeof(cwd)) != NULL) {
        printf("%s\n", cwd);
        printf("$ ");
        fgets(str, 100, stdin);
        SeparaInput(str, instruction, directory);

        if(strcmp(instruction,"ls")==0){
          strcat(cwd, "\\");
          strcat(cwd, directory);
          dr = opendir(cwd);
          if (dr == NULL)  // opendir returns NULL if couldn't open directory
          {
              printf("Could not find directory\n");
          }
          while ((de = readdir(dr)) != NULL){
            if(de->d_name[0]!='.'){printf("%s\n", de->d_name);}
          }
          closedir(dr);
        }
        else if(strcmp(instruction,"back")==0){
          char * ptr = strrchr(cwd,'\\');;
          *ptr='\0';
          chdir(cwd);
        }
        else{
          printf("Command not available\n");
        }


      }

      printf("\n");
    }

    return 0;
}
