#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <stdio.h>
#include <time.h>
#include <string.h>

int main() {
  int counter = 0;
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
  if ((chdir("/home/anargya/Sistem_Operasi/Modul_2/Soal_Shift")) < 0) {
    exit(EXIT_FAILURE);
  }
  close(STDIN_FILENO);
  close(STDOUT_FILENO);
  close(STDERR_FILENO);
  while(1) {
    if (counter == 30) {
      counter = 0;
    }
    counter++;
    int status;

    time_t rawtime;
    struct tm * timeinfo;
    time ( &rawtime );
    timeinfo = localtime ( &rawtime );

    //pid_t child_id;
    //child_id = fork();

    int jam = timeinfo->tm_hour;
    char jam2[5];
    snprintf(jam2, 10, "%d", jam);

    int menit = timeinfo->tm_min;
    char menit2[5];
    snprintf(menit2, 10, "%d", menit);

    int hari = timeinfo->tm_mday;
    char hari2[5];
    snprintf(hari2, 10, "%d", hari);

    int bulan = timeinfo->tm_mon+1;
    char bulan2[5];
    snprintf(bulan2, 10, "%d", bulan);

    int tahun = timeinfo->tm_year+1900;
    char tahun2[5];
    snprintf(tahun2, 10, "%d", tahun);

    char judul[100];
    strcpy(judul, "/home/anargya/log/");
    strcat(judul, hari2);
    strcat(judul, ":");
    strcat(judul, bulan2);
    strcat(judul, ":");
    strcat(judul, tahun2);
    strcat(judul, "-");
    strcat(judul, jam2);
    strcat(judul, ":");
    strcat(judul, menit2);

    char filelog[200];
    char counter2[2];
    snprintf(counter2, 10, "%d", counter);
    strcpy(filelog, judul);
    strcat(filelog, "/log");
    strcat(filelog, counter2);
    strcat(filelog, ".log");

    char jammenit[6];
    strcpy(jammenit, jam2);
    strcat(jammenit, ":");
    strcat(jammenit, menit2);

    pid_t child_id;
    child_id = fork();

    if (child_id != 0) {
      // parent of child
      while((wait(&status)) > 0);
      int status2;
      int pipefd[2];
      pid_t child2_id;

      pipe(pipefd);
      child2_id = fork();

      if (child2_id != 0) {
        // parent of child2 and handles cat syslog
        // replace standard output with output part of pipe
        dup2(pipefd[1], 1);

        //close unused input of pipe
        close(pipefd[0]);

        char *arr[3] = {"cat", "/var/log/syslog", NULL};
        execv("/bin/cat", arr);
      } else if (child2_id == 0) {
        while((wait(&status2)) > 0);
        // child of child2 and handles grep time
        // replace standard output with log#.log
        int out;
        out = open(filelog, O_WRONLY | O_TRUNC | O_CREAT, S_IRUSR | S_IRGRP | S_IWGRP | S_IWUSR);

        dup2(out, 1);
        close(out);
	dup2(pipefd[0], 0);
        close(pipefd[1]);

        char *arr[] = {"grep", jammenit, NULL};
        execv("/bin/grep", arr);
      }
    } else {
      if (counter == 1) {
	char *arr[3] = {"mkdir", judul, NULL};
        execv("/bin/mkdir", arr);
      }
    }

    sleep(60);
  }
  exit(EXIT_SUCCESS);
}
