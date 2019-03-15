# SoalShift_modul2_E13
Soal Shift Modul 2 Praktikum Sistem Operasi
1.	Elen mempunyai pekerjaan pada studio sebagai fotografer. Suatu hari ada seorang klien yang bernama Kusuma yang meminta untuk mengubah nama file yang memiliki ekstensi .png menjadi “[namafile]_grey.png”. Karena jumlah file yang diberikan Kusuma tidak manusiawi, maka Elen meminta bantuan kalian untuk membuat suatu program C yang dapat mengubah nama secara otomatis dan diletakkan pada direktori /home/[user]/modul2/gambar.
Catatan : Tidak boleh menggunakan crontab.



Pertama kita harus me-list isi dari folder dengan fungsi dir diatas, jika ada file maka akan masuk ke if, dalam while kita akan meloop untuk setiap file, untuk setiap file namanya dimasukkan ke string x, lalu dicek apakah file tersebut berakhiran .png, jika iya maka akan masuk ke if, lalu memasukkan nama file tersebut ke dalam string y, lalu akan dihapus 4 karakter terakhir, lalu ditambahkan _grey.png dibelakangnya, lalu menambahkan direktori ke depan nama file png tersebut agar muncul di direktori yang sudah ditentukan dengan menggunakan fungsi rename. Saat file didalam folder tersebut sudah habis, maka akan menutup dengan closedir.
Dalam soal perintahnya adalah untuk secara otomatis, maka menggunakan daemon di setiap detik (sleep(1))
  
 

2.	Pada suatu hari Kusuma dicampakkan oleh Elen karena Elen dimenangkan oleh orang lain. Semua kenangan tentang Elen berada pada file bernama “elen.ku” pada direktori “hatiku”. Karena sedih berkepanjangan, tugas kalian sebagai teman Kusuma adalah membantunya untuk menghapus semua kenangan tentang Elen dengan membuat program C yang bisa mendeteksi owner dan group dan menghapus file “elen.ku” setiap 3 detik dengan syarat ketika owner dan grupnya menjadi “www-data”. Ternyata kamu memiliki kendala karena permission pada file “elen.ku”. Jadi, ubahlah permissionnya menjadi 777. Setelah kenangan tentang Elen terhapus, maka Kusuma bisa move on.
Catatan: Tidak boleh menggunakan crontab

 

Pertama kita mengambil user dan group  menggunakan getpwuid dan get grgid lalu mencocokan apakah itu www-data atau tidak, kalau iya maka masuk if. Dalam if kita menghapus file elen.ku, tapi sebelum itu harus mengubah permission menjadi 777 artinya rwx untuk semua, maka bisa kita hapus.
Dalam soal ini diperintahkan untuk menjalankan setiap 3 detik, maka akan dimasukkan ke dalam daemon tiap 3 detik (sleep(3))
  

3.	Diberikan file campur2.zip. Di dalam file tersebut terdapat folder “campur2”. 
Buatlah program C yang dapat :
i)  mengekstrak file zip tersebut.
ii) menyimpan daftar file dari folder “campur2” yang memiliki ekstensi .txt ke dalam file daftar.txt. 
Catatan:  
○	Gunakan fork dan exec.
○	Gunakan minimal 3 proses yang diakhiri dengan exec.
○	Gunakan pipe
○	Pastikan file daftar.txt dapat diakses dari text editor

  

Kita menggunakan 4 proses yaitu masing masing untuk unzip campur2, untuk membuat txt, untuk me list isi folder campur2, dan untuk mengambil yang hanya berakhiran .txt dan dimasukkan ke dalam daftar.txt
Untuk memasukkan isi dari ls dan digunakan di grep, kita menggunakan fungsi pipe untuk menyambungkan keduanya

4. Dalam direktori /home/[user]/Documents/makanan terdapat file makan_enak.txt yang berisikan daftar makanan terkenal di Surabaya. Elen sedang melakukan diet dan seringkali tergiur untuk membaca isi makan_enak.txt karena ngidam makanan enak. Sebagai teman yang baik, Anda membantu Elen dengan membuat program C yang berjalan setiap 5 detik untuk memeriksa apakah file makan_enak.txt pernah dibuka setidaknya 30 detik yang lalu (rentang 0 - 30 detik).
Jika file itu pernah dibuka, program Anda akan membuat 1 file makan_sehat#.txt di direktori /home/[user]/Documents/makanan dengan '#' berisi bilangan bulat dari 1 sampai tak hingga untuk mengingatkan Elen agar berdiet.

Contoh:
File makan_enak.txt terakhir dibuka pada detik ke-1
Pada detik ke-10 terdapat file makan_sehat1.txt dan makan_sehat2.txt

Catatan: 
    • dilarang menggunakan crontab
    • Contoh nama file : makan_sehat1.txt, makan_sehat2.txt, dst
    
Jawab:
Di sini digunakan daemon untuk mengerjakan hal tersebut di background. Setelah seting daemon awal untuk daemon selesai, pertama kita ingin tahu access time, yaitu menggunakan struct stat dalam header sys/stat.h. Dari situ bisa dilakukan lstat dalam bahasa C untuk menghubungkannua ke sebuah file, dan masing-masing data waktu akses, modify, change bisa didapatkan, dan dilakukan strftime untuk format tanggal. Setelah itu kita juga mencari tahu waktu sekarang untuk membandingkan dengan struct tm dari time.h yang diisi parameter time_t, dan bisa diambil komponen waktu seperti jam, menit, detik dari struct tersebut.

Berikutnya digunakan kondisional if untuk mengecek waktu rentang 30 detik dari access time terakhir. Dan jika memenuhi, dilakukan exec touch untuk membuat file makan_sehat#.txt

5. Kerjakan poin a dan b di bawah:
    a. Buatlah program c untuk mencatat log setiap menit dari file log pada syslog ke /home/[user]/log/[dd:MM:yyyy-hh:mm]/log#.log
Ket:
    • Per 30 menit membuat folder /[dd:MM:yyyy-hh:mm]
    • Per menit memasukkan log#.log ke dalam folder tersebut
‘#’ : increment per menit. Mulai dari 1
    b. Buatlah program c untuk menghentikan program di atas.
NB: Dilarang menggunakan crontab dan tidak memakai argumen ketika menjalankan program.

Jawab:
Pertama disiapkan aturan untuk pembuatan daemon. Jika sudah, dibuat struct tm untuk tahu waktu sekarang, dan dibuat kondisional terhadap counter untuk membuat folder di menit ke 30, selain menit ke 30, akan selalu dirancang untuk membuat file log#.log berisi syslog yang telah difilter berdasarkan menit sekarang dengan grep.
