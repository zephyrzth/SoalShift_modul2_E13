#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <syslog.h>
#include <string.h>
#include <time.h>

int main() {
  int counter = 1;
  pid_t pid, sid;
  pid = fork();
  if (pid < 0) {
    exit(EXIT_FAILURE);
  }
  if (pid > 0) {
    exit(EXIT_SUCCESS);
  }
  umask(0);
  sid = setsid();
  if (sid < 0) {
    exit(EXIT_FAILURE);
  }
  if ((chdir("/home/anargya/Documents/makanan")) < 0) {
    exit(EXIT_FAILURE);
  }
  close(STDIN_FILENO);
  close(STDOUT_FILENO);
  close(STDERR_FILENO);
  while(1) {
    char judul[100], counter2[2];
    strcpy(judul, "/home/anargya/Documents/makanan/makan_sehat");
    snprintf(counter2, 10, "%d", counter);
    strcat(judul, counter2);
    strcat(judul, ".txt");
    //printf("%s\n", judul);

    int errno;
    const char* filename;
    filename = "/home/anargya/Documents/makanan/makan_enak.txt";

    errno = 0;
    struct stat *file_info = malloc(sizeof(struct stat));
    if (lstat(filename, file_info) != 0) {
      perror("Error");
      exit(1);
    }

    char timeakses[36];
    strftime(timeakses, 36, "%H:%M:%S", localtime(&file_info->st_atime));
    //printf("%s\n", timeakses);
    free(file_info);

    char jamakses[2];
    strncpy(jamakses, timeakses, 2);
    jamakses[2] = '\0';
    int jamakses2 = atoi(jamakses);
    //printf("%d\n", jamakses2);

    char menitakses[2];
    strncpy(menitakses, timeakses+3, 2);
    menitakses[2] = '\0';
    int menitakses2 = atoi(menitakses);
    //printf("%d\n", menitakses2);

    char detikakses[2];
    strncpy(detikakses, timeakses+6, 2);
    detikakses[2] = '\0';
    int detikakses2 = atoi(detikakses);
    //printf("%d\n", detikakses2);

    time_t rawtime;
    struct tm * timeinfo;
    time ( &rawtime );
    timeinfo = localtime ( &rawtime );

    int jam = timeinfo->tm_hour;
    int menit = timeinfo->tm_min;
    int detik = timeinfo->tm_sec;

    //printf("%d %d\n", jam, jamakses2);
    //printf("%d %d\n", menit, menitakses2);
    //printf("%d %d\n", detik, detikakses2);

    if (detik - detikakses2 >= 0) {
      if ((jam == jamakses2) && (menit == menitakses2) && ((detik - detikakses2) <= 30)) {
	//printf("1\n");
	counter++;
        pid_t child;
        child = fork();
        if (child == 0){
          char *arr[3] = {"touch", judul, NULL};
          execv("/usr/bin/touch", arr);
        } else {
          //printf("Parent\n");
        }
      }
    } else if (detik - detikakses2 < 0) {
      if (detik+60 - detikakses2 <= 30) {
        if (menit-1 < 0) {
	  if (menit+59 == menitakses2) {
	    if (jam-1 < 0 && jam+23 == jamakses2) {
	      //printf("2\n");
	      counter++;
	      pid_t child;
      	      child = fork();
       	      if (child == 0){
                char *arr[3] = {"touch", judul, NULL};
                execv("/usr/bin/touch", arr);
              } else {
                //printf("Parent\n");
      	      }
	    } else if (jam-1 >= 0 && jam-1 == jamakses2) {
	      //printf("3\n");
	      counter++;
	      pid_t child;
      	      child = fork();
      	      if (child == 0){
                char *arr[3] = {"touch", judul, NULL};
                execv("/usr/bin/touch", arr);
      	      } else {
                //printf("Parent\n");
      	      }
	    }
	  }
        } else if (menit-1 == menitakses2) {
	  if (jam == jamakses2) {
	    //printf("4\n");
	    counter++;
	    pid_t child;
            child = fork();
      	    if (child == 0){
              char *arr[3] = {"touch", judul, NULL};
              execv("/usr/bin/touch", arr);
      	    } else {
              //printf("Parent\n");
      	    }
	  }
        }
      }
    }
    
    sleep(5);
  }
  exit(EXIT_SUCCESS);
}
