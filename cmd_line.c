#include <stdlib.h>
#include <stdio.h>
#include <string.h>   //funcoes de strings
#include <time.h>     //usada para se poder calcular o tempo
#include <ctype.h>    //toupper and tolower functions
#include <unistd.h>   //permite usar a funcao sleep
#include <stdio.h>    //funçoes de ficheiros
#include <dirent.h>
#include <limits.h>
#include <windows.h>

void SeparaInput(char str[400], char instruction_line[100][400]){
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
    char str[400]="\0";
    char instruction_line[100][400]={"\0"};
    char directory[200]="\0";
    char program[200]="\0";
    struct dirent *de;
    DIR *dr;

    while(1){

      char color[9]="COLOR ";
      FILE *defs;
      defs = fopen("settings.txt", "r");
      if(defs!=NULL){
        char c;
        while((c=getc(defs))!=EOF){
          if(c=='C'){
            if((c=getc(defs))=='O'){
              if((c=getc(defs))=='L'){
                if((c=getc(defs))=='O'){
                  if((c=getc(defs))=='R'){
                    if((c=getc(defs))==' '){
                      c=getc(defs);
                      color[6]=c;
                      c=getc(defs);
                      color[7]=c;
                      system(color);
                    }
                  }
                }
              }
            }
          }
        }
      }
      /* Some list of combinations

      0 = Black
      1 = Blue
      2 = Green
      3 = Aqua
      4 = Red
      5 = Purple
      6 = Yellow
      7 = White
      8 = Gray
      9 = Light Blue

      A = Light Green
      B = Light Aqua
      C = Light Red
      D = Light Purple
      E = Light Yellow
      F = Bright White
      */
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

          if(instruction_line[1][0]!='-'){
            if(strcmp(instruction_line[1],".")==0||strcmp(instruction_line[1],"..")==0){
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
              for(int a=1;a<100;a++){
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
          char file[100];
          strcpy(file,"\0");
          for(int i=1;i<100;i++){
            strcat(file,instruction_line[i]);
            strcat(file," ");
          }
          fptr = fopen(file, "r");
          if(fptr!=NULL){
            printf("\n");
            while ((c = getc(fptr)) != EOF) printf("%c", c);
            printf("\n");
          }
          else{
            perror("Error");
          }
          fclose(fptr);
        }

        else if(strcmp(instruction_line[0],"remove")==0){
          char file[100];
          strcpy(file,"\0");
          for(int i=1;i<100;i++){
            strcat(file,instruction_line[i]);
            strcat(file," ");
          }
          if(remove(file)==0){
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

        else if(strcmp(instruction_line[0],"run")==0){
          if(strcmp(instruction_line[1],"notepad")==0){
            system("notepad.exe");
          }
          else if(strcmp(instruction_line[1],"-c")==0){
            if(strcmp(instruction_line[2],"")!=0){
              strcpy(program,"\0");
              strcpy(program,"\"");
              strcat(program,cwd);
              strcat(program,"\\");
              strcat(program,instruction_line[2]);
              strcat(program,"\"");
              printf("Running: %s\n\n",instruction_line[2]);
              system(program);
              system("cls");
              printf("Back to the command line!\n");
            }
            else{printf("No executable file defined\n");}
          }
          else{
            printf("Command not available\n");
          }
        }

        else if(strcmp(instruction_line[0],"settings")==0){
          FILE *fptr;
          if(strcmp(instruction_line[1],"-r")==0){
            char c;
            fptr = fopen("settings.txt", "r");
            if(fptr!=NULL){
              printf("\n");
              while ((c = getc(fptr)) != EOF) printf("%c", c);
            }
            else{
              perror("Error");
            }
            fclose(fptr);
          }

          else if(strcmp(instruction_line[1],"-w")==0){
             char text[101]="\0";
             fptr = fopen("settings.txt","a");

             if(fptr != NULL){
               do{
                 strcpy(text,"\0");
                 fgets(text,100,stdin);
                 if(strcmp(text,"done\n")!=0){
                   fprintf(fptr,"%*s",strlen(text)-1,text);
                 }
               }while(strcmp(text,"done\n")!=0);
             }
             else{
               perror("Error");
             }
             fclose(fptr);
          }

          else if(strcmp(instruction_line[1],"-d")==0){
            fptr = fopen("settings.txt","w");
            fclose(fptr);
            system("COLOR 07");
            printf("All definitions set as default\n" );
          }

          else{printf("Command not available\n");}
        }

        else if(strcmp(instruction_line[0],"help")==0){
          printf("Lista de operacoes disponiveis na linha de comandos:\n\n");
          printf("  ls: lista todos os ficheiros e sub-diretorios do diretorio atual;\n");
          printf("    [-a] mostra os ficheiros e diretorios escondidios;\n\n");
          printf("  back: recua no diretorio;\n\n");
          printf("  goto: muda o diretorio de trabalho;\n");
          printf("    [] avanca para um diretorio que esta dentro do atual;\n");
          printf("    [-d] avanca para o diretorio especifica de forma total;\n\n");
          printf("  print: imprime o conteudo do ficheiro para a consola;\n\n");
          printf("  remove: apaga o ficheiro especificado;\n\n");
          printf("  new: cria um novo ficheiro ou diretorio;\n");
          printf("    [-f] cria ficheiro;\n\n");
          printf("  run: corre um executavel;\n");
          printf("    [notepad] executa o notepad;\n");
          printf("    [-c] corre o executavel indicado;\n\n");
          printf("  settings: ;\n");
          printf("    [-r] mostra as definicoes atuais;\n");
          printf("    [-w] alterar as definicoes;\n");
          printf("    [-d] apagar todas as definicoes\n\n");
          printf("  clear: limpa o ecra;\n\n");
          printf("  exit: termina a execucao da linha de comandos;\n\n");

        }

        else if(strcmp(instruction_line[0],"clear")==0){
          system("cls");
        }

        else if(strcmp(instruction_line[0],"exit")==0){
          exit(0);
        }

        else{
          printf("Command not available\n");
        }

      }

      printf("\n");
    }

    return 0;
}
