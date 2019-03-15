#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <unistd.h>

int main(){
        DIR *d;
        struct dirent *dir;
        d = opendir(".");
        //printf("hai");
        //printf("%s\n",direktori);
        if (d){
                while ((dir = readdir(d)) != NULL){
                        char x[100]="", y[100]="";
                        strcpy(x,dir->d_name);
                        //strcat(x,"");
                        if(x[strlen(x)-1] == 'g' && x[strlen(x)-2] == 'n' && x[strlen(x)-3] == 'p' && x[strlen(x)-4] == '.'){
                                strcpy(y,dir->d_name);
//                              printf("%s\n",y);
                                y[strlen(y)-4]='\0';
                                //printf("%s\n",y);
                                strcat(y,"_grey.png");
//                              printf("%s\n",y);
                                char direktori[100]="/home/trasv/Timo/modul2/gambar/";
                                //strcpy(direktori,"/Home/Timo/modul2/gambar/");
                                //strcat(direktori,"");
                                printf("%s\n", direktori);
                                //rename(x,y);
                                //printf("%s\n", x);
                                strcat(direktori,y);
                                //strcat(direktori,"");
                                //printf("%s\n",direktori);
//                              printf("%s\n", x);
                                rename(x,direktori);
                                //rename(y,direktori);
                                //printf("ini x %s\n",x);
//                              printf("ini hasil %s\n",direktori);
                                //printf("%s\n%s\n",x,y);
                                }

//                      printf("%c",x[strlen(x)-1]);
                        //printf("%s\n",x);
                        //printf("%s\n", dir->d_name);
                        }
                closedir(d);
        }
}
