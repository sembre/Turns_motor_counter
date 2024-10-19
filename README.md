# Turns_motor_counter
Program ini mengontrol motor menggunakan input dari keypad, dengan tampilan jumlah putaran pada LCD 16x2. Pengguna dapat mengatur jumlah putaran motor yang diinginkan menggunakan keypad, dan motor akan beroperasi sampai jumlah putaran tercapai. Program juga menggunakan tombol # untuk mengunci input dari keypad setelah pengguna memasukkan jumlah putaran, serta tombol * untuk mereset nilai input dan membuka kembali kunci keypad.

# Fitur Utama:
Input Jumlah Putaran melalui Keypad:

Pengguna dapat memasukkan jumlah putaran motor yang diinginkan melalui keypad 4x4.
Nilai yang dimasukkan ditampilkan di LCD dan disimpan di variabel targetTurns.
Tombol Kunci (Tombol #):

Setelah pengguna memasukkan jumlah putaran, mereka harus menekan tombol # untuk mengunci input keypad.
Motor tidak akan bisa dinyalakan sebelum tombol # ditekan. Hal ini memastikan bahwa jumlah putaran sudah diatur dengan benar sebelum motor mulai beroperasi.
Tombol Reset (Tombol *):

Jika pengguna menekan tombol *, jumlah putaran akan direset ke nol, dan input keypad dibuka kembali (kunci dibatalkan). Ini memungkinkan pengguna untuk memasukkan jumlah putaran baru.
Tombol Start Motor:

Setelah input terkunci (dengan tombol #), pengguna dapat menekan tombol start (pada pin startButtonPin) untuk memulai motor.
Saat motor berjalan, program menghitung jumlah putaran berdasarkan pembacaan dari saklar penghitung putaran (switchPin).
Setiap kali jumlah putaran bertambah, nilai ini ditampilkan di layar LCD dan Serial Monitor.
Penghentian Otomatis:

Motor akan berhenti secara otomatis ketika jumlah putaran yang diinginkan tercapai (yaitu, jumlah putaran yang dimasukkan melalui keypad sama dengan hitungan dari sensor saklar).
Tampilan LCD:

LCD digunakan untuk menampilkan pesan dan status motor, seperti "Set Turns", jumlah putaran yang dimasukkan, serta status "Locked" ketika input keypad terkunci.
Saat motor berjalan, LCD menampilkan jumlah putaran yang telah tercapai.
Struktur Program:
Setup:

Menginisialisasi pin motor, tombol start, dan saklar penghitung putaran.
Menginisialisasi LCD dan keypad, serta menampilkan pesan awal untuk meminta input jumlah putaran.
Loop:

Program membaca input dari keypad untuk menentukan jumlah putaran.
Program memastikan bahwa motor hanya bisa dijalankan setelah input dari keypad dikunci dengan tombol #.
Selama motor berjalan, program menghitung jumlah putaran dan menghentikan motor secara otomatis setelah jumlah putaran yang diinginkan tercapai.
Kondisi Tambahan:
Jika pengguna mencoba menyalakan motor sebelum mengunci keypad (sebelum menekan tombol #), program akan menampilkan pesan kesalahan di LCD dan Serial Monitor, memberitahukan bahwa pengguna perlu mengunci input terlebih dahulu.
Program ini sangat bermanfaat untuk aplikasi yang memerlukan kontrol presisi pada motor berbasis jumlah putaran, seperti dalam sistem mekanik atau robotik.
