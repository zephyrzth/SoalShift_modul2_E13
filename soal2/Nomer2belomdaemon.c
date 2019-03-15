#include <stdio.h>
#include <grp.h>
#include <pwd.h>
#include <sys/stat.h>
#include <string.h>
#include <unistd.h>

int main(){
    struct stat sb;
    char outstr[200], x[100];

    stat("elen.ku", &sb);

    struct passwd *pw = getpwuid(sb.st_uid);
    struct group  *gr = getgrgid(sb.st_gid);
    strcpy(x,pw->pw_name);
    //strcat(x,"");
    if(x[strlen(x)-1]=='a' && x[strlen(x)-2]=='t' && x[strlen(x)-3]=='a' && x[strlen(x)-4]=='d' && x[strlen(x)-5]=='-' && x[strlen(x)-6]=='w' && x[strlen(x)-7]=='w' && x[strlen(x)-8]=='w'){
        //printf("hai");
        chmod("elen.ku",777);
        char *argv[3] = {"rm", "elen.ku", NULL};
        execv("/bin/rm", argv);
        }
    //printf("%s %s\n", pw->pw_name, gr->gr_name);
}

