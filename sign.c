// Joseph Gildner
// CSCI 461: Assignment 3

#include<stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

void createkey();
void encryptkey(const char* id);

void main(int argc, char const *argv[]) {
	createkey();
	encryptkey(argv[1]);
}

void createkey(){
	const pid_t cpid = fork();
	switch(cpid) {
		case -1: {
			perror("fork");
			break;
		}

		case 0: {
			int randkey = open("key.bin", O_WRONLY | O_CREAT, 0660);
			dup2(randkey,1);
			execlp("openssl", "openssl", "rand", "-base64", "32", (char *) NULL);
			exit(EXIT_FAILURE);
			break;
		}

		default: {
			int   status;
			const pid_t pid = wait(&status);
			break;
		}
	}
}

void encryptkey(const char* id){
	const pid_t cpid = fork();
	switch(cpid) {
		case -1: {
			perror("fork");
			break;
		}

		case 0: {
			char inputkey[64];
			for(int i=0; i<64; i++){
				inputkey[i] = '\0';
			}
			strcat(inputkey,"./pubkeys/");
			strcat(inputkey,id);
			strcat(inputkey,"_rsa.pub.pem");
			execlp("openssl", "openssl", "rsautl", "-encrypt", "-inkey", inputkey, "-pubin", "-in", "key.bin", "-out", "key.bin.enc", (char *) NULL);
			exit(EXIT_FAILURE);
			break;
		}

		default: {
			int   status;
			const pid_t pid = wait(&status);
			break;
		}
	}
}