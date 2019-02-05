// Joseph Gildner
// CSCI 461: Assignment 3

#include<stdio.h>

FILE* createkey();

void main(int argc, char const *argv[]) {

}

void createkey(){
    const pid_t cpid = fork();
    switch(cpid) {
      case -1: {
        perror("fork");
        break;
      }

      case 0: {
        FILE* randkey = fopen("key.bin")
        execvp(commandArgs[0],commandArgs);
        perror("execvp");
        exit(EXIT_FAILURE);
        break;
      }

      default: {
        int   status;
        const pid_t pid = wait(&status);
        if(-1 == pid) {
          perror("wait");
        }
        else if (pid != cpid) {
          fprintf(stderr, "wait: expected process %d, but waited for process %d",
          cpid, pid);
        }
        break;
      }

}