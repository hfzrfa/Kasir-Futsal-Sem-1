Berikut adalah penjelasan yang lebih rinci mengenai kode **Aplikasi Kasir Futsal** yang dapat Anda presentasikan kepada dosen Anda. Saya akan membahas bagian per bagian, menjelaskan alur program, dan cara kerjanya.

### 1. **Library dan Struct**

```cpp
#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <fstream>  // Untuk file handling
using namespace std;
```

- **iostream**: Digunakan untuk input/output data ke layar dan dari pengguna.
- **string**: Untuk menangani teks, seperti nama lapangan dan transaksi.
- **vector**: Struktur data dinamis yang digunakan untuk menyimpan objek transaksi.
- **iomanip**: Digunakan untuk mengatur format output, seperti presisi angka (misalnya untuk harga).
- **fstream**: Untuk membaca dan menulis ke file, digunakan dalam pencatatan transaksi ke dalam file log.

**Struct `Transaksi`**:
```cpp
struct Transaksi {
    int idTransaksi;
    string jenisLapangan;
    double hargaPerJam;
    int durasiSewa;  // dalam jam
    double totalHarga;
};
```

- **idTransaksi**: Menyimpan ID unik untuk setiap transaksi.
- **jenisLapangan**: Menyimpan jenis lapangan yang disewa (Standar atau VIP).
- **hargaPerJam**: Menyimpan harga sewa per jam untuk lapangan yang dipilih.
- **durasiSewa**: Durasi sewa dalam jam.
- **totalHarga**: Total biaya yang harus dibayar berdasarkan harga per jam dan durasi sewa.

### 2. **Fungsi Login Admin**

```cpp
bool loginAdmin() {
    string username, password;
    const string adminUsername = "admin";  // Username admin
    const string adminPassword = "admin123";  // Password admin

    cout << "Masukkan username admin: ";
    cin >> username;
    cout << "Masukkan password admin: ";
    cin >> password;

    return (username == adminUsername && password == adminPassword); // Mengembalikan true jika username dan password benar
}
```

- **loginAdmin()**: Fungsi ini meminta input username dan password dari pengguna dan memeriksa apakah keduanya cocok dengan username dan password admin yang telah ditentukan (`admin` dan `admin123`).
- Jika username dan password cocok, fungsi mengembalikan nilai `true` (login berhasil), jika tidak, maka akan gagal login.

### 3. **Fungsi Menulis Log**

```cpp
void writeLog(const string &message) {
    ofstream logFile;
    logFile.open("log_transaksi.txt", ios::app);  // Membuka file log untuk menambah (append)
    if (logFile.is_open()) {
        logFile << message << endl;
        logFile.close();
    } else {
        cout << "Error: Tidak bisa membuka file log.\n";
    }
}
```

- **writeLog()**: Fungsi ini digunakan untuk menulis pesan log ke dalam file `log_transaksi.txt`. File ini dibuka dengan mode `ios::app` (append), yang artinya setiap pesan baru akan ditambahkan di akhir file.
- Jika file log berhasil dibuka, pesan log akan ditulis dan file ditutup setelah selesai. Jika file tidak bisa dibuka, program menampilkan pesan kesalahan.

### 4. **Fungsi Menambah Transaksi**

```cpp
void addTransaksi(Transaksi &transaksi, int id) {
    transaksi.idTransaksi = id;

    int pilihanLapangan;
    cout << "Pilih Jenis Lapangan:\n";
    cout << "1. Lapangan Standar (Rp 100.000/jam)\n";
    cout << "2. Lapangan VIP (Rp 150.000/jam)\n";
    cout << "Pilih (1/2): ";
    cin >> pilihanLapangan;

    switch (pilihanLapangan) {
        case 1:
            transaksi.jenisLapangan = "Lapangan Standar";
            transaksi.hargaPerJam = 100000;
            break;
        case 2:
            transaksi.jenisLapangan = "Lapangan VIP";
            transaksi.hargaPerJam = 150000;
            break;
        default:
            cout << "Pilihan tidak valid.\n";
            return;
    }

    cout << "Masukkan durasi sewa (dalam jam): ";
    cin >> transaksi.durasiSewa;
    if (transaksi.durasiSewa <= 0) {
        cout << "Durasi sewa tidak valid.\n";
        return;
    }

    transaksi.totalHarga = transaksi.hargaPerJam * transaksi.durasiSewa;
    daftarTransaksi.push_back(transaksi);  // menambahkan transaksi ke daftar transaksi yang ada

    string logMessage = "Transaksi Baru: ID " + to_string(transaksi.idTransaksi) + ", Lapangan: " + transaksi.jenisLapangan +
                        ", Durasi: " + to_string(transaksi.durasiSewa) + " jam, Total: Rp " + to_string(transaksi.totalHarga);
    writeLog(logMessage);
}
```

- **addTransaksi()**: Fungsi ini menangani penambahan transaksi baru. Prosesnya adalah:
  1. Meminta admin untuk memilih jenis lapangan (Standar atau VIP).
  2. Meminta durasi sewa (dalam jam).
  3. Menghitung total harga berdasarkan harga per jam dan durasi sewa.
  4. Menambahkan transaksi ke dalam **`daftarTransaksi`**, yang merupakan kontainer vector untuk menyimpan transaksi-transaksi yang sudah dilakukan.
  5. Menulis pesan log tentang transaksi baru yang telah dilakukan.

### 5. **Fungsi Menampilkan Struk Pembayaran**

```cpp
void printStruk(const Transaksi &transaksi) {
    cout << "\n\n======== STRUK PEMBAYARAN FUTSAL BYTE ========\n";
    cout << "ID Transaksi: " << transaksi.idTransaksi << endl;
    cout << "Jenis Lapangan: " << transaksi.jenisLapangan << endl;
    cout << "Durasi Sewa: " << transaksi.durasiSewa << " jam\n";
    cout << "Harga Per Jam: Rp " << fixed << setprecision(2) << transaksi.hargaPerJam << endl;
    cout << "Total Harga: Rp " << fixed << setprecision(2) << transaksi.totalHarga << endl;
    cout << "==============================================\n";
}
```

- **printStruk()**: Fungsi ini digunakan untuk menampilkan struk pembayaran berdasarkan transaksi yang baru saja dilakukan. Informasi yang ditampilkan meliputi:
  - ID transaksi
  - Jenis lapangan
  - Durasi sewa
  - Harga per jam
  - Total harga
- Fungsi ini menggunakan **`fixed`** dan **`setprecision(2)`** dari library `iomanip` untuk memastikan harga ditampilkan dengan dua angka desimal.

### 6. **Fungsi Menampilkan Daftar Transaksi**

```cpp
void tampilkanDaftarTransaksi() {
    if (daftarTransaksi.empty()) {
        cout << "Belum ada transaksi.\n";
        return;
    }

    cout << "\n===== Daftar Transaksi =====\n";
    for (const auto &transaksi : daftarTransaksi) {
        cout << "ID Transaksi: " << transaksi.idTransaksi << "\n";
        cout << "Lapangan: " << transaksi.jenisLapangan << ", Durasi: " 
             << transaksi.durasiSewa << " jam, Total Harga: Rp " 
             << fixed << setprecision(2) << transaksi.totalHarga << endl;
    }
    cout << "=============================\n";
}
```

- **tampilkanDaftarTransaksi()**: Fungsi ini digunakan untuk menampilkan daftar semua transaksi yang telah dilakukan. Jika belum ada transaksi, akan menampilkan pesan "Belum ada transaksi". Jika ada transaksi, maka akan menampilkan ID transaksi, jenis lapangan, durasi sewa, dan total harga.

### 7. **Fungsi Menghapus Transaksi**

```cpp
void hapusTransaksi(int id) {
    bool ditemukan = false;
    for (auto it = daftarTransaksi.begin(); it != daftarTransaksi.end(); ++it) {
        if (it->idTransaksi == id) {
            daftarTransaksi.erase(it);
            cout << "Transaksi dengan ID " << id << " telah dihapus.\n";

            string logMessage = "Transaksi Dihapus: ID " + to_string(id);
            writeLog(logMessage);

            ditemukan = true;
            break;
        }
    }
    
    if (!ditemukan) {
        cout << "Transaksi dengan ID " << id << " tidak ditemukan.\n";
    }
}
```

- **hapusTransaksi()**: Fungsi ini digunakan untuk menghapus transaksi berdasarkan ID. Fungsi ini mencari ID transaksi yang diberikan dalam daftar transaksi dan menghapusnya. Setelah transaksi dihapus, sebuah log akan dicatat bahwa transaksi telah dihapus.

### 8. **Main Program (Menu Utama)**

```cpp
int main() {
    int idTransaksi = 1;  // ID transaksi pertama
    Transaksi transaksi;
    int choice;

    cout << "APLIKASI KASIR FUTSAL BYTE\n\n";
    if (!loginAdmin()) {
        cout << "Login gagal. Keluar dari program.\n";
        return 0;
    }

    do {
        cout << "\n=== Menu Admin ===\n";
        cout << "1. Lihat Daftar

 Transaksi\n";
        cout << "2. Hapus Transaksi\n";
        cout << "3. Tambah Transaksi\n";
        cout << "4. Keluar\n";
        cout << "Pilih menu: ";
        cin >> choice;

        switch (choice) {
            case 1:
                tampilkanDaftarTransaksi();
                break;
            case 2:
                int idHapus;
                cout << "Masukkan ID transaksi yang ingin dihapus: ";
                cin >> idHapus;
                hapusTransaksi(idHapus);
                break;
            case 3:
                addTransaksi(transaksi, idTransaksi);
                printStruk(transaksi);
                idTransaksi++;  // ID transaksi selanjutnya
                break;
            case 4:
                cout << "Keluar dari program.\n";
                break;
        }

    } while (choice != 4);
    return 0;
}
```

- **Menu Admin**: Di dalam fungsi `main`, terdapat menu yang memungkinkan admin untuk:
  - Melihat daftar transaksi yang ada.
  - Menghapus transaksi berdasarkan ID.
  - Menambahkan transaksi baru.
  - Keluar dari aplikasi.

---

### Ringkasan Alur Program

1. **Login Admin**: Admin memasukkan username dan password untuk mengakses menu.
2. **Tambah Transaksi**: Admin dapat menambah transaksi baru (pilih jenis lapangan dan durasi sewa).
3. **Lihat Daftar Transaksi**: Admin dapat melihat semua transaksi yang telah dilakukan.
4. **Hapus Transaksi**: Admin dapat menghapus transaksi berdasarkan ID.
5. Semua perubahan transaksi dicatat dalam file log.

---

Penjelasan di atas memberikan gambaran yang cukup jelas tentang cara kerja aplikasi kasir futsal yang sederhana ini. Anda bisa menggunakan penjelasan tersebut untuk presentasi kepada dosen Anda, serta menjelaskan secara rinci bagaimana setiap bagian dari program berfungsi.
