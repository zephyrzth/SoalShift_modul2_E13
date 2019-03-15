#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <error.h>
#include <signal.h>
#include <unistd.h>
#include <syslog.h>

int main()
{
    FILE *getPIDS;
    char data[100];
    pid_t killpid;
    // pid dan ppid dari file ini
    /*pid_t mypid   = getpid();
    printf("Current PID: %d\n", mypid);
    pid_t myppid  = getppid();
    printf("Current PPID: %d\n", myppid);*/

    getPIDS = popen("pidof -x /home/anargya/Sistem_Operasi/Modul_2/Soal_Shift/hasil-soal5","r");

    fgets(data, sizeof(data), getPIDS);

    pid_t pid = atoi(data);
    kill(pid, SIGKILL);
    printf("PID: %s killed\n",data);
}
