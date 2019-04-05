#include <stdlib.h>
#include <stdio.h>
#include <string.h>   //funcoes de strings
#include <time.h>     //usada para se poder calcular o tempo
#include <ctype.h>    //toupper and tolower functions
#include <unistd.h>   //permite usar a funcao sleep
#include <stdio.h>    //funçoes de ficheiros
#include <dirent.h>
#include <limits.h>

void SeparaInput(char str[200], char instruction_line[10][200]){
  /*apaga o \n do final*/
  char *newline = strchr( str, '\n' );
  if ( newline ) *newline = 0;

  /*reset aos valores guardados na string de comado*/
  for(int a=0;a<10;a++){
    strcpy(instruction_line[a],"\0");
  }

  /*separa a string de comando*/
  int i=0;
  char *token;
  token = strtok(str, " ");
  while( token != NULL ) {
    strcpy(instruction_line[i],token);
    token = strtok(NULL, " ");
    i++;
  }

  return;
}

int main()
{

  char cwd[PATH_MAX]="\0";
  char str[200]="\0";
  char instruction_line[10][200]={"\0"};
  struct dirent *de;
  DIR *dr;

    while(1){
      if (getcwd(cwd, sizeof(cwd)) != NULL) {
        printf("%s\n", cwd);
        printf("$ ");
        fgets(str, 100, stdin);
        SeparaInput(str, instruction_line);
        printf("%s\n",instruction_line[0]);
        printf("%s\n",instruction_line[1]);
        if(strcmp(instruction_line[0],"ls")==0){

          if(strcmp(instruction_line[1],"-a")==0){

            if(strcmp(instruction_line[2],"")!=0){
              strcat(cwd, "\\");
              strcat(cwd, instruction_line[2]);
            }
            dr = opendir(cwd);
            if (dr == NULL)  // opendir returns NULL if couldn't open directory
            {
                printf("Could not find directory\n");
            }
            while ((de = readdir(dr)) != NULL){
              printf("%s\n", de->d_name);
            }
            closedir(dr);

          }

          else{
            if(strcmp(instruction_line[1],"")!=0){
              strcat(cwd, "\\");
              strcat(cwd, instruction_line[1]);
            }
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
        }

        else if(strcmp(instruction_line[0],"back")==0){
          char * ptr = strrchr(cwd,'\\');
          *ptr='\0';
          chdir(cwd);
        }

        else if(strcmp(instruction_line[0],"goto")==0){

          if(strcmp(instruction_line[1],"-n")==0){

            if(strcmp(instruction_line[2],".")==0||strcmp(instruction_line[2],"..")==0){
              printf("Could not find directory\n");
            }

            else{
              int flag=0;
              dr = opendir(cwd);
              if (dr == NULL)  // opendir returns NULL if couldn't open directory
              {
                  printf("Could not find directory\n");
              }
              while ((de = readdir(dr)) != NULL){
                if(strcmp(instruction_line[2],de->d_name)==0){
                  strcat(cwd,"\\");
                  strcat(cwd,instruction_line[2]);
                  chdir(cwd);
                  flag=1;
                }
              }
              if(flag==0) printf("Could not find directory\n");
            }

          }
          else if(strcmp(instruction_line[1],"-d")==0){

          }
          else{
            printf("Command not available\n");
          }
        }

        else{
          printf("Command not available1\n");
        }


      }

      printf("\n");
    }

    return 0;
}
