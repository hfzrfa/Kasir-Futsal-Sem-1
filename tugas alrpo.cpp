// TUBES ALRPO SEMESTER 1
// APLIKASI KASIR FUTSAL


#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <fstream>  // Untuk file handling
using namespace std;

struct Transaksi {
    int idTransaksi;
    string jenisLapangan;
    double hargaPerJam;
    int durasiSewa;  // dalam jam
    double totalHarga;
};

vector<Transaksi> daftarTransaksi;  // digunakan sebagai kontainer dinamis untuk menyimpan daftar transaksi

// Berikut adalah fungsi untuk mengakses login admin
bool loginAdmin() {
    string username, password;
    const string adminUsername = "admin";  // Username admin
    const string adminPassword = "admin123";  // Password admin

    cout << "Masukkan username admin: ";
    cin >> username;
    cout << "Masukkan password admi     n: ";
    cin >> password;

    return (username == adminUsername && password == adminPassword); // Mengembalikan true jika username dan password benar
}

// Berikut adalah fungsi untuk menulis log ke file

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

// Berikut adalah fungsi untuk menambah transaksi

void addTransaksi(Transaksi &transaksi, int id) {
    transaksi.idTransaksi = id;

    int pilihanLapangan;
    cout << "Pilih Jenis Lapangan:\n";
    cout << "1. Lapangan Standar (Rp 100.000/jam)\n";
    cout << "2. Lapangan VIP (Rp 150.000/jam)\n";
    cout << "Pilih (1/2): ";
    cin >> pilihanLapangan;

// memvalidasi pilihan lapangan dan menghitung total harga menggunakan siwtch case

    switch (pilihanLapangan) {
        case 1:
            transaksi.jenisLapangan = "Lapangan Standar";
            transaksi.hargaPerJam = 100.000;
            break;
        case 2:
            transaksi.jenisLapangan = "Lapangan VIP";
            transaksi.hargaPerJam = 150.000;
            break;
        default:
            cout << "Pilihan tidak valid.\n";
            return;
    }

// setelah itu, user diminta untuk memasukkan durasi sewa 

    cout << "Masukkan durasi sewa (dalam jam): ";
    cin >> transaksi.durasiSewa;
    if (transaksi.durasiSewa <= 0) { // yang arti nya durasi sewa harus lebih dari 1 jam
        cout << "Durasi sewa tidak valid.\n"; // jika durasi sewa tidak valid maka akan muncul pesan ini
        return;
    }

    // setelah itu, total harga dihitung berdasarkan harga per jam dan durasi sewa

    transaksi.totalHarga = transaksi.hargaPerJam * transaksi.durasiSewa;
    daftarTransaksi.push_back(transaksi);  // menambahkan transaksi ke daftar transaksi yang ada

    
    // menuliskan log transaksi baru ke log file

    string logMessage = "Transaksi Baru: ID " + to_string(transaksi.idTransaksi) + ", Lapangan: " + transaksi.jenisLapangan +
                        ", Durasi: " + to_string(transaksi.durasiSewa) + " jam, Total: Rp " + to_string(transaksi.totalHarga);
    writeLog(logMessage);
}


    // Berikut adalah fungsi untuk menampilkan semua transaksi
void printStruk(const Transaksi &transaksi) {
    cout << "\n\n======== STRUK PEMBAYARAN FUTSAL BYTE ========\n";
    cout << "ID Transaksi: " << transaksi.idTransaksi << endl;  // memanggil id transkasi 
    cout << "Jenis Lapangan: " << transaksi.jenisLapangan << endl; // memanggil jenis lapangan
    cout << "Durasi Sewa: " << transaksi.durasiSewa << " jam\n"; // memanggil durasi sewa untuk di tampilkan
    cout << "Harga Per Jam: Rp " << fixed << setprecision(2) << transaksi.hargaPerJam << endl; // memanggil harga per jam
    cout << "Total Harga: Rp " << fixed << setprecision(2) << transaksi.totalHarga << endl;  // memanggil total harga
    
    cout << "==============================================\n";
}


// Berikut adalah fungsi untuk menampilkan semua transaksi


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

// berikut adalah funsi untuk menghapus transaksi berdasarkan ID

void hapusTransaksi(int id) {
    bool ditemukan = false;
    for (auto it = daftarTransaksi.begin(); it != daftarTransaksi.end(); ++it) {
        if (it->idTransaksi == id) {
            daftarTransaksi.erase(it);
            cout << "Transaksi dengan ID " << id << " telah dihapus.\n";

            // menulis log penghapusan transaksi

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

int main(){
    int idTransaksi = 1;  // ID transaksi pertama
    Transaksi transaksi;
    int choice;

    // Menampilkan menu untuk admin

    cout << "APLIKASI KASIR FUTSAL BYTE\n\n";
    if (!loginAdmin()) {
        cout << "Login gagal. Keluar dari program.\n";
        return 0;
    }

    do {
        cout << "\n=== Menu Admin ===\n";
        cout << "1. Lihat Daftar Transaksi\n";
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
