# SoalShift_modul2_E13
Soal Shift Modul 2 Praktikum Sistem Operasi

1. Elen mempunyai pekerjaan pada studio sebagai fotografer. Suatu hari ada seorang klien yang bernama Kusuma yang meminta untuk mengubah nama file yang memiliki ekstensi .png menjadi “[namafile]_grey.png”. Karena jumlah file yang diberikan Kusuma tidak manusiawi, maka Elen meminta bantuan kalian untuk membuat suatu program C yang dapat mengubah nama secara otomatis dan diletakkan pada direktori /home/[user]/modul2/gambar.
   
   Catatan : Tidak boleh menggunakan crontab.
   
   Jawab:
   ```
   #include <sys/types.h>
   #include <sys/stat.h>
   #include <stdio.h>
   #include <stdlib.h>
   #include <fcntl.h>
   #include <errno.h>
   #include <unistd.h>
   #include <syslog.h>
   #include <string.h>
   #include <dirent.h>

   int main() {
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

     if ((chdir("/home/trasv/Timo/Sisop/2")) < 0) {
       exit(EXIT_FAILURE);
     }

     close(STDIN_FILENO);
     close(STDOUT_FILENO);
     close(STDERR_FILENO);

     while(1) {
       DIR *d;
       struct dirent *dir;
       d = opendir(".");
       if (d){
         while ((dir = readdir(d)) != NULL){
           char x[100], y[100];
           strcpy(x,dir->d_name);
           strcat(x,"");
           if(x[strlen(x)-1] == 'g' && x[strlen(x)-2] == 'n' && x[strlen(x)-3] == 'p' && x[strlen(x)-4] == '.'){
             strcpy(y,dir->d_name);
             y[strlen(y)-4]='\0';
             strcat(y,"_grey.png");
             char direktori[100]="/home/trasv/Timo/modul2/gambar/";
             printf("%s\n", direktori);
             strcat(direktori,y);
             rename(x,direktori);
           }
         }
       closedir(d);
       }

     sleep(1);
     }

     exit(EXIT_SUCCESS);
   }
   ```
   Pertama kita harus me-list isi dari folder dengan variabel bertipe `DIR*` dan `struct dirent*`. Dan dilakukan fungsi `opendir()` yang hasilnya dimasukkan ke variabel bertipe DIR* tadi. Hal ini dilakukan untuk mengecek apakah isi folder ada.
   
   Jika ada file, maka akan masuk ke `if()`, dalam `while()` kita akan meloop untuk setiap file, untuk setiap file namanya dimasukkan ke string `x[]`, lalu dicek apakah file tersebut berakhiran `.png`.
   
   Jika iya maka akan masuk ke `if()`, lalu memasukkan nama file tersebut ke dalam string `y`, lalu akan dihapus 4 karakter terakhir, lalu ditambahkan `_grey.png` dibelakangnya, lalu menambahkan direktori ke depan nama file png tersebut agar muncul di direktori yang sudah ditentukan dengan menggunakan fungsi rename. Saat file didalam folder tersebut sudah habis, maka akan menutup dengan `closedir`.
   
   Dalam soal perintahnya adalah untuk secara otomatis, maka menggunakan daemon di setiap detik `sleep(1)`.

2. Pada suatu hari Kusuma dicampakkan oleh Elen karena Elen dimenangkan oleh orang lain. Semua kenangan tentang Elen berada pada file bernama “elen.ku” pada direktori “hatiku”. Karena sedih berkepanjangan, tugas kalian sebagai teman Kusuma adalah membantunya untuk menghapus semua kenangan tentang Elen dengan membuat program C yang bisa mendeteksi owner dan group dan menghapus file “elen.ku” setiap 3 detik dengan syarat ketika owner dan grupnya menjadi “www-data”. Ternyata kamu memiliki kendala karena permission pada file “elen.ku”. Jadi, ubahlah permissionnya menjadi 777. Setelah kenangan tentang Elen terhapus, maka Kusuma bisa move on.

   Catatan: Tidak boleh menggunakan crontab
   
   Jawab:
   ```
   #include <sys/types.h>
   #include <sys/stat.h>
   #include <stdio.h>
   #include <stdlib.h>
   #include <fcntl.h>
   #include <errno.h>
   #include <unistd.h>
   #include <syslog.h>
   #include <string.h>
   #include <grp.h>
   #include <pwd.h>


   int main() {
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

     if ((chdir("/home/trasv/Timo/Sisop/2/hatiku")) < 0) {
       exit(EXIT_FAILURE);
     }

     close(STDIN_FILENO);
     close(STDOUT_FILENO);
     close(STDERR_FILENO);

     while(1) {
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
       sleep(3);
     }

     exit(EXIT_SUCCESS);
   }
   ```
   Pertama dibutuhkan header `sys/stat.h` untuk melakukan fungsi `stat`untuk menjalankan fungsi `stat` seperti di linux bash, dan disimpan dalam `struct stat`.
   
   Lalu kita mengambil `user` dan `group`  menggunakan `getpwuid` dan `getgrgid` lalu mencocokkan apakah itu `www-data` atau tidak, kalau iya maka masuk if.
   
   Dalam if kita menghapus file `elen.ku`, tapi sebelum itu harus mengubah permission menjadi `777` dengan `chmod([file], 777)` artinya rwx untuk semua, maka bisa kita hapus menggunakan `execv()` untuk fungsi `rm`.
   
   Dalam soal ini diperintahkan untuk menjalankan setiap 3 detik, maka akan dimasukkan ke dalam daemon tiap 3 detik `sleep(3)`. 

3. Diberikan file campur2.zip. Di dalam file tersebut terdapat folder “campur2”. 
Buatlah program C yang dapat :
i)  mengekstrak file zip tersebut.
ii) menyimpan daftar file dari folder “campur2” yang memiliki ekstensi .txt ke dalam file daftar.txt. 

   Catatan:  
   ○	Gunakan fork dan exec.
   ○	Gunakan minimal 3 proses yang diakhiri dengan exec.
   ○	Gunakan pipe
   ○	Pastikan file daftar.txt dapat diakses dari text editor
   
   Jawab:
   ```
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
       char *argv[3] = {"unzip", "campur2.zip", NULL};
       execv("/usr/bin/unzip", argv);
       close(p[0]);
     }
     else{
       while ((wait(&status2)) > 0);
       pid2 = fork();
       if(pid2 == 0){
         dup2(p[1], 1);
         close(p[0]);
         char *argv[3] = {"ls", "campur2", NULL};
         execv("/bin/ls", argv);
       }
       else{
         pid3 = fork();
         if(pid3 == 0){
           char *argv[3] = {"touch", "daftar.txt", NULL};
           execv("/usr/bin/touch", argv);
         }
         else{
           while ((wait(&status)) > 0);
           file = open("daftar.txt",O_WRONLY); 
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
   ```
   Kita menggunakan 4 proses yaitu masing masing untuk unzip campur2, untuk membuat txt, untuk me-list isi folder campur2, dan untuk mengambil yang hanya berakhiran .txt dan dimasukkan ke dalam daftar.txt
   
   Untuk membuat pipe, menggunakan fungsi `pipe()` dengan parameter `int[2]` yaitu indeks 0 digunakan sebagai input, dan indeks 1 digunakan untuk output.
   
   Untuk unzip digunakan `execv` untuk fungsi `unzip`.
   
   Untuk membuat txt juga dengan `touch` dengan `execv`.
   
   Untuk me-list isi folder campur2 digunakan fungsi `ls campur2` yang dimasukkan dalam fungsi `execv`.
   
   Untuk mengambil yang berakhiran .txt juga menggunakan `grep .txt$` di dalam `execv`, bedanya di sini digunakan redirection dalam C dengan mengubah STDOUT dari proses untuk grep ini dengan file yang sudah dibuka dengan `open()`.
   
   Dalam kasus ini, pipe digunakan saat melakukan fungsi `ls` dan `grep`. Jadi pertama dalam proses untuk menjalankan `ls`, `STDOUT` diganti dengan `p[1]` dengan `dup2(p[1], 1)` sehingga output dari proses ini akan masuk ke `p[1]` yang berperan sebagai pipe. Sedangkan di proses `grep`, `STDIN` dan `STDOUT`nya diganti karena kita akan merubah input dan output untuk proses ini, dimana input bersumber dari pipe `p[0]` untuk input yang dilakukan dengan `dup2(p[0], 0)` dan `dup2(file, 1)`.
   
   Dalam program ini juga harus ada urutan penjalanan proses, yang diatur dengan fungsi `wait()`. proses `grep` harus menunggu proses `touch` jadi, dan proses `ls` harus menunggu `campur2.zip` selesai diextract.

4. Dalam direktori /home/[user]/Documents/makanan terdapat file makan_enak.txt yang berisikan daftar makanan terkenal di Surabaya. Elen sedang melakukan diet dan seringkali tergiur untuk membaca isi makan_enak.txt karena ngidam makanan enak. Sebagai teman yang baik, Anda membantu Elen dengan membuat program C yang berjalan setiap 5 detik untuk memeriksa apakah file makan_enak.txt pernah dibuka setidaknya 30 detik yang lalu (rentang 0 - 30 detik).
Jika file itu pernah dibuka, program Anda akan membuat 1 file makan_sehat#.txt di direktori /home/[user]/Documents/makanan dengan '#' berisi bilangan bulat dari 1 sampai tak hingga untuk mengingatkan Elen agar berdiet.

   Contoh:
   File makan_enak.txt terakhir dibuka pada detik ke-1
   Pada detik ke-10 terdapat file makan_sehat1.txt dan makan_sehat2.txt

   Catatan: 
   • dilarang menggunakan crontab
   • Contoh nama file : makan_sehat1.txt, makan_sehat2.txt, dst
    
   Jawab:

   Metode yang kami gunakan adalah mencari access time dari file makan_enak.txt, mencari waktu local sekarang, dan membandingkan kedua waktu dengan operasi matematika untuk mengetahui selisih waktu akses file dan waktu sekarang apakah dalam rentang 30 detik. Jika dalam rentang 30 detik, maka akan membuat file kosong bernama makan_sehat#.txt
   ```
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
   ```
   Pertama dibuat folder makanan di `/home/anargya/Documents/` dan file makan_enak.txt dipindah ke sana. Lalu, dibuat variabel counter untuk memberi nama file nanti. Dan langsung dibuat judul file makan_sehat dalam array judul[].
   ```
   char judul[100], counter2[2];
   strcpy(judul, "/home/anargya/Documents/makanan/makan_sehat");
   snprintf(counter2, 10, "%d", counter);
   strcat(judul, counter2);
   strcat(judul, ".txt");
   ```
   Lalu untuk menjalankan fungsi `stat` di C, menggunakan header `sys/stat.h` dan membuat variabel bertipe `struct stat*`. Berikutnya digunakan `lstat` untuk menjalankan fungsi stat di C dari judul file tadi (parameter 2) dan hasilnya dimasukkan ke parameter 1 yaitu variabel struct stat* yang telah dibuat, seperti berikut.
   ```
   int errno;
   const char* filename;
   filename = "/home/anargya/Documents/makanan/makan_enak.txt";
   errno = 0;
   struct stat *file_info = malloc(sizeof(struct stat));
   if (lstat(filename, file_info) != 0) {
     perror("Error");
     exit(1);
   }
   ```
   Selanjutnya, masing-masing data seperti waktu akses, modify, change bisa didapatkan. Karena akan ada banyak data (bahkan untuk satu atribut access time sekalipun), digunakan fungsi strftime untuk membuat data `st_atime` dari struct tersebut (data access time) dibuat ke dalam format `jam:menit:detik` agar mudah digunakan nantinya, seperti ini.
   ```
   char timeakses[36];
   strftime(timeakses, 36, "%H:%M:%S", localtime(&file_info->st_atime));
   ```
   Setelah itu kita ingin membagi data akses time ke masing-masing jam, menit, detik, dengan fungsi `strncpy` dan mengubahnya menjadi int untuk dapat dilakukan perhitungan, dengan menggunakan fungsi `atoi()`.
   ```
   char jamakses[2];
   strncpy(jamakses, timeakses, 2);
   jamakses[2] = '\0';
   int jamakses2 = atoi(jamakses);

   char menitakses[2];
   strncpy(menitakses, timeakses+3, 2);
   menitakses[2] = '\0';
   int menitakses2 = atoi(menitakses);

   char detikakses[2];
   strncpy(detikakses, timeakses+6, 2);
   detikakses[2] = '\0';
   int detikakses2 = atoi(detikakses);
   ```
   Di sini kita sudah selesai mendapatkan access time yang siap dilakukan perhitungan. Untuk mendapatkan waktu saat ini, diperlukan header `time.h` dan dibuat variabel bertipe `struct tm*`. Untuk mendapatkan waktu sekarang dilakukan fungsi `time()` dan waktu sekarang akan disimpan dalam format detik sejak 1 January 1970 ke dalam parameter fungsi time() yaitu variabel bertipe time_t. Untuk menyimpan data tersebut ke dalam struct tm* yang sudah terdapat atribut seperti tm_hour, tm_min, dan tm_sec (untuk membagi data detik tersebut ke dalam berbagai format), digunakan fungsi `localtime()` yang parameternya diisi variabel bertipe `time_t*` atau alamat dari variabel bertipe `time_t` yaitu `&time_t`. Fungsi tersebut akan mereturn data bertipe `struct tm*` yang bisa kita masukkan ke dalam `struct tm* timeinfo` yang sudah kita buat. Berikutnya dibuat tiga variabel untuk menyimpan tm_hour, tm_min, tm_sec dari timeinfo (data langsung dalam format int sehingga tidak perlu diconvert). Seperti pada kode berikut.
   ```
   time_t rawtime;
   struct tm * timeinfo;
   time ( &rawtime );
   timeinfo = localtime ( &rawtime );
   int jam = timeinfo->tm_hour;
   int menit = timeinfo->tm_min;
   int detik = timeinfo->tm_sec;
   ```
   Lalu kita bisa menggunakan `free(fileinfo)` untuk membersihkan fileinfo dari memory karena sudah tidak diperlukan. Dan dilakukan perbandingan waktu akses dan waktu sekarang, diawali dari detik. Terdiri dari banyak syarat karena ada banyak kasus, ketika detik sekarang - detikakses < 0, harus meminjam waktu dari menit, ketika menit - 1 < 0 harus meminjam tambahan menit dari jam dan jam ditambah 23 (berlaku jika pada jam 00:00), dan syarat-syarat lainnya. Seperti di bawah ini.
   ```
   if (detik - detikakses2 >= 0) {
     if (jam == jamakses2 && menit == menitakses2 && detik - detikakses2 <= 30) {
       // Memenuhi syarat
     }
   } else if (detik - detikakses2 < 0) {
     if (detik+60 - detikakses2 <= 30) {
       if (menit-1 < 0) {
         if (menit+59 == menitakses2) {
           if (jam-1 < 0 && jam+23 == jamakses2) {
             // Memenuhi syarat
           } else if (jam-1 >= 0 && jam-1 == jamakses2) {
             // Memenuhi syarat
           }
        }
       } else if (menit-1 == menitakses2) {
         if (jam == jamakses2) {
           // Memenuhi syarat
         }
       }
     }
   }
   ```
   Jika syarat memenuhi, maka siap dibuat file baru, dengan menggunakan `fork()`, tapi kita hanya memanfaatkan child saja, karena kita tidak ingin program ini berhenti ketika kita menggunakan exec di proses tanpa fork(). Dan dilakukan `execv` dari perintah touch dan nama file yang sudah dibuat di awal. Seperti berikut.
   ```
   pid_t child;
   child = fork();
   if (child == 0){
     char *arr[3] = {"touch", judul, NULL};
     execv("/usr/bin/touch", arr);
   } else {
     // Kosong
   }
   ```
   Setelah program siap, tinggal dimasukkan ke dalam daemon dan dilakukan sleep setiap 5 detik dengan `sleep(5)`.

5. Kerjakan poin a dan b di bawah:
   
   a. Buatlah program c untuk mencatat log setiap menit dari file log pada syslog ke /home/[user]/log/[dd:MM:yyyy-hh:mm]/log#.log
   
   Ket:
    • Per 30 menit membuat folder /[dd:MM:yyyy-hh:mm]
    • Per menit memasukkan log#.log ke dalam folder tersebut
    ‘#’ : increment per menit. Mulai dari 1
    
   b. Buatlah program c untuk menghentikan program di atas.
   NB: Dilarang menggunakan crontab dan tidak memakai argumen ketika menjalankan program.

   Jawab:
   
   a. Mencatat log setiap menit ke file
   ```
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
   ```
   Metode yang kami gunakan adalah menyiapkan judul dari folder dan file, menggunakan counter untuk menghitung menit ke berapa, menggunakan fungsi grep untuk mendapatkan data dari syslog khusus pada menit dan jam saat itu, dan melakukan redirection untuk membuat sekaligus menyimpan data dari grep ke dalam judul file yang sudah disiapkan.
   
   Pertama dibuat variabel counter untuk menghitung menit ke berapa dan pembuatan judul filelog, dan langsung dilakukan pengecekan di awal apakah counter == 30, jika ya maka counter direset ke 0 (karena akan dibuat folder baru, sehingga judul filelog akan dibuat dari 1 lagi). Seperti berikut.
   ```
   if (counter == 30) {
      counter = 0;
    }
    counter++;
   ```
   Lalu akan dicari waktu sekarang menggunakan `struct tm*` dan fungsi `time()` yang disimpan ke variabel bertipe `time_t` dan dilakukan fungsi `localtime()` dengan parameter alamat dari variabel time_t dan mereturn data yang dimasukkan ke variabel struct tm* (sama seperti no. 4). Seperti berikut.
   
   Berikutnya didapatkan waktu sekarang masing-masing sesuai atribut timeinfo, dan akan diubah formatnya ke string menggunakan `snprintf` karena kita akan memakai ini untuk judul file yang digabung dengan atribut waktu yang lain. Untuk hari, bulan, dan tahun hanya diambil dan dirubah formatnya pada saat counter == 1 (setelah counter direset) karena hanya dibutuhkan setiap 30 menit sekali untuk membuat judul folder.
   
   Untuk membuat folder, juga dicek apakah counter == 1 yang artinya sudah 30 menit. Jika iya, maka dibuat folder dengan fungsi `mkdir([judul_folder], 0777)` dengan parameter 0777 agar bisa dilakukan read, write, dsb. Seperti berikut.
   ```
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
   ```
   Berikutnya, kita membuat judul filelog dengan cara yang hampir sama, memanfaatkan header `string.h` untuk melakukan fungsi `strcpy` dan `strcat`, dan `jammenit` yang digunakan saat menjalankan fungsi `grep`. Seperti berikut.
   ```
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
   ```
   Setelah semuanya siap, dilakukan `fork()` dan di salah satu proses dilakukan `grep` dan `redirection`. Dalam C, redirection digunakan dengan merubah `STDOUT` dari proses agar output masuk ke file dengan fungsi `dup2([file], 1)`, 1 menandakan output atau STDOUT. Sebelum itu, file dalam parameter tersebut dibuka dengan fungsi `open()` dengan tambahan perintah tertentu di dalamnya dan disimpan di variabel int, dan file tadi bisa kita tutup dengan `close()`.
   ```
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
   ```
   Setelah siap, dijalankan fungsi `grep` dengan `execv`, dan dilakukan `sleep(60)` untuk menjalankan program setiap 1 menit.
   
   b. Menghentikan program
   ```
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

       getPIDS = popen("pidof -x /home/anargya/Sistem_Operasi/Modul_2/Soal_Shift/hasil-soal5a","r");

       fgets(data, sizeof(data), getPIDS);

       pid_t pid = atoi(data);
       kill(pid, SIGKILL);
       printf("PID: %s killed\n",data);
   }
   ```
   Untuk mendapatkan PID untuk menghentikan program, kita menggunakan `pidof -x [file hasil compile]`. Karena itu adalah sebuah file, maka digunakan fungsi `popen()` untuk membuka filenya dan memasukkan ke variabel bertipe `FILE*`. Dari variabel tersebut, data dipindah ke array, dan diconvert lagi ke int dengan `atoi` untuk dimasukkan ke fungsi `kill([pid], tipe kill)`.
