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
  if ((chdir("/home/anargya/log")) < 0) {
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

    char judul[100];

    time_t rawtime;
    struct tm * timeinfo;
    time ( &rawtime );
    timeinfo = localtime ( &rawtime );

    int jam = timeinfo->tm_hour;
    char jam2[5];
    snprintf(jam2, 10, "%d", jam);

    int menit = timeinfo->tm_min;
    char menit2[5];
    snprintf(menit2, 10, "%d", menit);

    if (counter == 1) {
      int hari = timeinfo->tm_mday;
      char hari2[5];
      snprintf(hari2, 10, "%d", hari);

      int bulan = timeinfo->tm_mon+1;
      char bulan2[5];
      snprintf(bulan2, 10, "%d", bulan);

      int tahun = timeinfo->tm_year+1900;
      char tahun2[5];
      snprintf(tahun2, 10, "%d", tahun);

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

      mkdir(judul, 0777);
    }

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

    //sleep(60);

    pid_t child;
    child = fork();
    if (child == 0){
      //printf("%d Success\n", counter);
      int out;
      out = open(filelog, O_WRONLY | O_TRUNC | O_CREAT, S_IRUSR | S_IRGRP | S_IWGRP | S_IWUSR);

      dup2(out, 1);
      close(out);

      char *arr[4] = {"grep", jammenit, "/var/log/syslog", NULL};
      execv("/bin/grep", arr);
    } else {
      //printf("Parent\n");
    }

    sleep(60);
  }
  exit(EXIT_SUCCESS);
}
