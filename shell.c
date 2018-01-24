/*
 * By: Alex Duncanson and Lanndon Rose
 */
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/resource.h>
#include <time.h>

int main() {

  system("clear");
  printf("\n\nThis is a shell :)");

  while (1) {

    char* readin = (char*) malloc(sizeof(char)*50);
    char** args = (char**) malloc(sizeof(char)*50);
    char* token;
    int i = 0;
    struct rusage usage;
    pid_t process;

    printf("\n\n~: ");
    fgets(readin, 50, stdin);

    token = strtok(readin, " \n");

    while (token != NULL) {
      args[i] = token;
      token = strtok(NULL, " \n");
      i++;
    }

    if(strcmp(args[0], "quit") == 0) {
      printf("\nLeaving shell.\n\n");
      exit(0);
    }

    process = fork();
    if (process < 0) {
      perror("\nfork error, fork didn't happen.\n");
      free(readin);readin = NULL;
      free(args);args = NULL;
      exit(1);
    } else if (process){
      wait(0);
      getrusage(RUSAGE_CHILDREN,&usage);
      printf("\n\tChild CPU time used: %ld sec", usage.ru_utime.tv_usec);
      printf("\n\tInvoluntary context switches: %ld", usage.ru_nivcsw);
    } else {
      if(execvp(args[0], args) < 0) {
        perror("\n ");
        exit(1);
      }
    }
  }
}
