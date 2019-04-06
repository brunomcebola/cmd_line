#include <stdlib.h>
#include <stdio.h>
#include <string.h>   //funcoes de strings
#include <time.h>     //usada para se poder calcular o tempo
#include <ctype.h>    //toupper and tolower functions
#include <unistd.h>   //permite usar a funcao sleep
#include <stdio.h>    //funçoes de ficheiros
#include <dirent.h>
#include <limits.h>

#define PATH_MAX 4096

void SeparaInput(char str[200], char instruction_line[100][200]){
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
  char instruction_line[100][200]={"\0"};
  char directory[100]="\0";
  struct dirent *de;
  DIR *dr;

    while(1){
      if (getcwd(cwd, sizeof(cwd)) != NULL) {

        printf("%s\n", cwd);
        printf("$ ");
        fgets(str, 100, stdin);
        SeparaInput(str, instruction_line);

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
              strcpy(directory,"\0");
              int flag=0;
              dr = opendir(cwd);
              if (dr == NULL)  // opendir returns NULL if couldn't open directory
              {
                  printf("Could not find directory\n");
              }

              /*Cria o caminho a seguir para o diretorio*/
              for(int a=2;a<100;a++){
                strcat(directory, instruction_line[a]);
                if(strcmp(instruction_line[a],"")!=0){
                  strcat(directory, " ");
                }
              }
              char * ptr = strrchr(directory,' ');
              *ptr='\0';

              /*verifica a existencia do diretorio dentro do diretorio atual*/
              while ((de = readdir(dr)) != NULL){
                if(strcmp(directory,de->d_name)==0){
                  strcat(cwd,"\\");
                  strcat(cwd,directory);
                  if(chdir(cwd)!=0) printf("Could not find directory\n");
                  flag=1;
                }
              }
              if(flag==0) printf("Could not find directory\n");
            }
          }

          else if(strcmp(instruction_line[1],"-d")==0){
            strcpy(cwd,"C:\\");
            for(int a=2;a<100;a++){
              strcat(cwd, instruction_line[a]);
              if(strcmp(instruction_line[a],"")!=0){
                strcat(cwd, " ");
              }
            }
            if(chdir(cwd)!=0) printf("Could not find directory\n");
          }

          else{
            printf("Command not available\n");
          }
        }

        else if(strcmp(instruction_line[0],"print")==0){
          FILE *fptr;
          int c;
          fptr = fopen(instruction_line[1], "r");
          if(fptr!=NULL){
            printf("\n");
            while ((c = getc(fptr)) != EOF) printf("%c", c);
          }
          else{
            perror("Error");
          }
          fclose(fptr);
        }

        else if(strcmp(instruction_line[0],"remove")==0){
          if(remove(instruction_line[1])==0){
            printf("File successfuly deleted\n");
          }
          else{
            perror("Error");
          }
        }

        else if(strcmp(instruction_line[0],"new")==0){

          if(strcmp(instruction_line[1],"-f")==0){
            FILE *fptr;
            fptr = fopen(instruction_line[2], "w");
            if (fptr == NULL) {
              perror("Error");
            }
            else{
              printf("File %s created successfuly\n", instruction_line[2]);
            }
            fclose(fptr);
          }

          else{
            printf("Command not available\n");
          }
        }

        else if(strcmp(instruction_line[0],"exit")==0){exit(0);}

        else{
          printf("Command not available\n");
        }

      }

      printf("\n");
    }

    return 0;
}
