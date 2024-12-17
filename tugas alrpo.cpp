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
    // string emailPelanggan;
};

vector<Transaksi> daftarTransaksi;  // Menyimpan semua transaksi

// Fungsi untuk login admin
bool loginAdmin() {
    string username, password;
    const string adminUsername = "admin";  // Username admin
    const string adminPassword = "admin123";  // Password admin

    cout << "Masukkan username admin: ";
    cin >> username;
    cout << "Masukkan password admi     n: ";
    cin >> password;

    return (username == adminUsername && password == adminPassword);
}

// Fungsi untuk menulis log ke file
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

// Fungsi untuk menambah transaksi
void addTransaksi(Transaksi &transaksi, int id) {
    transaksi.idTransaksi = id;

    int pilihanLapangan;
    cout << "Pilih Jenis Lapangan:\n";
    cout << "1. Lapangan Standar (Rp 100.000/jam)\n";
    cout << "2. Lapangan VIP (Rp 150.000/jam)\n";
    cout << "Pilih (1/2): ";
    cin >> pilihanLapangan;

    // Validasi pilihan lapangan
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

    // Validasi durasi sewa
    cout << "Masukkan durasi sewa (dalam jam): ";
    cin >> transaksi.durasiSewa;
    if (transaksi.durasiSewa <= 0) {
        cout << "Durasi sewa tidak valid.\n";
        return;
    }

    // cout << "Masukkan alamat email pelanggan: ";
    // cin >> transaksi.emailPelanggan;

    transaksi.totalHarga = transaksi.hargaPerJam * transaksi.durasiSewa;
    daftarTransaksi.push_back(transaksi);  // Menambahkan transaksi ke daftar

    // Menulis log transaksi baru
    string logMessage = "Transaksi Baru: ID " + to_string(transaksi.idTransaksi) + ", Lapangan: " + transaksi.jenisLapangan +
                        ", Durasi: " + to_string(transaksi.durasiSewa) + " jam, Total: Rp " + to_string(transaksi.totalHarga);
    writeLog(logMessage);
}

// Fungsi untuk mencetak struk transaksi
void printStruk(const Transaksi &transaksi) {
    cout << "\n\n======== Struk Pembayaran Futsal MarBit ========\n";
    cout << "ID Transaksi: " << transaksi.idTransaksi << endl;
    cout << "Jenis Lapangan: " << transaksi.jenisLapangan << endl;
    cout << "Durasi Sewa: " << transaksi.durasiSewa << " jam\n";
    cout << "Harga Per Jam: Rp " << fixed << setprecision(2) << transaksi.hargaPerJam << endl;
    cout << "Total Harga: Rp " << fixed << setprecision(2) << transaksi.totalHarga << endl;
    cout << "==============================================\n";
}

// Fungsi untuk menampilkan semua transaksi
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

// Fungsi untuk menghapus transaksi berdasarkan ID
void hapusTransaksi(int id) {
    bool ditemukan = false;
    for (auto it = daftarTransaksi.begin(); it != daftarTransaksi.end(); ++it) {
        if (it->idTransaksi == id) {
            daftarTransaksi.erase(it);
            cout << "Transaksi dengan ID " << id << " telah dihapus.\n";

            // Menulis log penghapusan transaksi
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

int main() {
    int idTransaksi = 1;  // ID transaksi pertama
    Transaksi transaksi;
    int choice;

    // Menu untuk admin
    cout << "=== Kasir Futsal MarBit ===\n";
    if (!loginAdmin()) {
        cout << "Login gagal. Akses dibatasi.\n";
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
                idTransaksi++;  // Increment ID transaksi untuk transaksi berikutnya
                break;
            case 4:
                cout << "Terima kasih telah menggunakan layanan kami!" << endl;
                break;
            default:
                cout << "Pilihan tidak valid. Coba lagi.\n";
        }
    } while (choice != 4);

    return 0;
}
