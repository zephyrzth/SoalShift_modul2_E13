#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <fcntl.h>


int main(){
    int p[2];
    pid_t pid1, pid2, pid3;
    int status, status2, status3;
    int file;
    pipe(p);
    pid1 = fork();
    if(pid1 == 0){
	//printf("1\n");
	char *argv[3] = {"unzip", "campur2.zip", NULL};
    	execv("/usr/bin/unzip", argv);
	close(p[0]);
    }
    else{
	    while ((wait(&status2)) > 0);
	    //printf("2\n");
	    pid2 = fork();
	    //printf("hai");
	    if(pid2 == 0){
		dup2(p[1], 1);
                close(p[0]);
		char *argv[3] = {"ls", "campur2", NULL};
	        execv("/bin/ls", argv);
	     }
	     else{
		//while ((wait(&status2)) > 0);
		//printf("3\n");
	        pid3 = fork();
		if(pid3 == 0){
		   char *argv[3] = {"touch", "daftar.txt", NULL};
                   execv("/usr/bin/touch", argv);
		}
		else{
		     while ((wait(&status)) > 0);
		     //printf("4\n");
		     //printf("hai");
		     file = open("daftar.txt",O_WRONLY); 
                     //printf("hai");
                     dup2(p[0], 0);
                     close(p[1]);
		     dup2(file, 1);
		     char *argv[3] = {"grep", "[.]txt$", NULL};
                     execv("/bin/grep", argv);
                     close(p[0]);
		}
	     }
    }
}
