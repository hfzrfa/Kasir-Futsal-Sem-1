#include <iostream> // digunakan untuk input output ke layar dari pengguna
#include <string> // untuk mengnangani teks, seperti nama lapangan dan transaksi
#include <vector> // struktur data yang digunakan untuk menyimpan daftar transaksi
#include <iomanip> // digunakan untuk mengatur presisi angka desimal (misalnya harga)
#include <fstream>  // Untuk membaca dan menuis file, digunakan dalam pencacatan transaksi ke dalam file log
#include <windows.h> // Untuk mengatur warna teks dan latar belakang
#include <ctime> // Untuk mendapatkan waktu sekarang
using namespace std;

struct Transaksi {
    int idTransaksi;
    string jenisLapangan;
    int hargaPerJam;
    int durasiSewa;  // dalam jam
    int totalHarga;
    string waktuSelesai; // waktu selesai booking
};

vector<Transaksi> daftarTransaksi;  // digunakan sebagai kontainer dinamis untuk menyimpan daftar transaksi

// Fungsi untuk mengatur warna teks
void setColor(int textColor, int bgColor) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    int colorAttribute = textColor + (bgColor * 16);
    SetConsoleTextAttribute(hConsole, colorAttribute);
}

// Pilihan warna
enum Colors {
    BLACK = 0,
    BLUE = 1,
    GREEN = 2,
    CYAN = 3,
    RED = 4,
    MAGENTA = 5,
    BROWN = 6,
    LIGHTGRAY = 7,
    DARKGRAY = 8,
    LIGHTBLUE = 9,
    LIGHTGREEN = 10,
    LIGHTCYAN = 11,
    LIGHTRED = 12,
    LIGHTMAGENTA = 13,
    YELLOW = 14,
    WHITE = 15
};

// Fungsi untuk mendapatkan waktu sekarang dan menghitung waktu selesai
string hitungWaktuSelesai(int durasiSewa) {
    time_t now = time(0);
    tm *ltm = localtime(&now);

    ltm->tm_hour += durasiSewa; // Tambahkan durasi sewa ke jam sekarang
    mktime(ltm); // Perbarui waktu jika terjadi overflow (misalnya lebih dari 24 jam)

    char buffer[80];
    strftime(buffer, 80, "%H:%M", ltm); // Format waktu menjadi HH:MM
    return string(buffer);
}

// Berikut adalah fungsi untuk mengakses login admin
bool loginAdmin() {
    string username, password;
    const string adminUsername = "byte";  // Username admin
    const string adminPassword = "mantap";  // Password admin

    setColor(YELLOW, BLACK);
    cout << "Masukkan username admin: ";
    cin >> username;
    cout << "Masukkan password admin: ";
    cin >> password;

    setColor(WHITE, BLACK);
    return (username == adminUsername && password == adminPassword); // Mengembalikan true jika username dan password benar
}

// Berikut adalah fungsi untuk menulis log ke file
void writeLog(const string &message) {
    ofstream logFile;
    logFile.open("log futsal.txt", ios::app);  // Membuka file log untuk menambah (append)
    if (logFile.is_open()) {
        logFile << fixed << setprecision(2) << message << endl;  // Format log dengan 2 angka desimal
        logFile.close();
    } else {
        setColor(RED, BLACK);
        cout << "Error: Tidak bisa membuka file log.\n";
        setColor(WHITE, BLACK);
    }
}

// Berikut adalah fungsi untuk menambah transaksi
void addTransaksi(Transaksi &transaksi, int id) {
    transaksi.idTransaksi = id;

    int pilihanLapangan;
    setColor(CYAN, BLACK);
    cout << "Pilih Jenis Lapangan:\n";
    cout << "1. Lapangan Standar (Rp 100.000/jam)\n";
    cout << "2. Lapangan VIP (Rp 150.000/jam)\n";
    cout << "Pilih (1/2): ";
    cin >> pilihanLapangan;

    // memvalidasi pilihan lapangan dan menghitung total harga menggunakan switch case
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
            setColor(RED, BLACK);
            cout << "Pilihan tidak valid.\n";
            setColor(WHITE, BLACK);
            return;
    }

    // setelah itu, user diminta untuk memasukkan durasi sewa 
    cout << "Masukkan durasi sewa (dalam jam): ";
    cin >> transaksi.durasiSewa;
    if (transaksi.durasiSewa <= 0) { // durasi sewa harus lebih dari 1 jam
        setColor(RED, BLACK);
        cout << "Durasi sewa tidak valid.\n";
        setColor(WHITE, BLACK);
        return;
    }

    // setelah itu, total harga dihitung berdasarkan harga per jam dan durasi sewa
    transaksi.totalHarga = transaksi.hargaPerJam * transaksi.durasiSewa;
    transaksi.waktuSelesai = hitungWaktuSelesai(transaksi.durasiSewa); // Hitung waktu selesai
    daftarTransaksi.push_back(transaksi);  // menambahkan transaksi ke daftar transaksi yang ada

    // menuliskan log transaksi baru ke log file
    string logMessage = "Transaksi Baru: ID " 
                        + to_string(transaksi.idTransaksi) 
                        + ", Lapangan: " + transaksi.jenisLapangan 
                        + ", Durasi: " + to_string(transaksi.durasiSewa) 
                        + " jam, Total: Rp " + to_string(transaksi.totalHarga)
                        + ", Waktu Selesai: " + transaksi.waktuSelesai;
    writeLog(logMessage);

    setColor(GREEN, BLACK);
    cout << "Transaksi berhasil ditambahkan!\n";
    setColor(WHITE, BLACK);
}

// Berikut adalah fungsi untuk menampilkan semua transaksi
void printStruk(const Transaksi &transaksi) {
    setColor(LIGHTBLUE, BLACK);
    cout << "\n\n======== STRUK PEMBAYARAN FUTSAL BYTE ========\n";
    cout << "ID Transaksi: " << transaksi.idTransaksi << endl;
    cout << "Jenis Lapangan: " << transaksi.jenisLapangan << endl;
    cout << "Durasi Sewa: " << transaksi.durasiSewa << " jam\n";
    cout << "Harga Per Jam: Rp " << fixed << setprecision(3) << transaksi.hargaPerJam << endl;
    cout << "Total Harga: Rp " << fixed << setprecision(3) << transaksi.totalHarga << endl;
    cout << "Waktu Selesai: " << transaksi.waktuSelesai << endl;
    cout << "==============================================\n";
    setColor(WHITE, BLACK);
}

// Berikut adalah fungsi untuk menampilkan semua transaksi
void tampilkanDaftarTransaksi() {
    if (daftarTransaksi.empty()) {
        setColor(RED, BLACK);
        cout << "Belum ada transaksi.\n";
        setColor(WHITE, BLACK);
        return;
    }

    setColor(YELLOW, BLACK);
    cout << "\n===== Daftar Transaksi =====\n";
    for (const auto &transaksi : daftarTransaksi) {
        cout << "ID Transaksi: " << transaksi.idTransaksi << "\n";
        cout << "Lapangan: " << transaksi.jenisLapangan << ", Durasi: " 
             << transaksi.durasiSewa << " jam, Total Harga: Rp " 
             << fixed << setprecision(2) << transaksi.totalHarga << ", Waktu Selesai: " 
             << transaksi.waktuSelesai << endl;
    }
    cout << "=============================\n";
    setColor(WHITE, BLACK);
}

// berikut adalah fungsi untuk menghapus transaksi berdasarkan ID
void hapusTransaksi(int id) {
    bool ditemukan = false;
    for (auto it = daftarTransaksi.begin(); it != daftarTransaksi.end(); ++it) {
        if (it->idTransaksi == id) {
            daftarTransaksi.erase(it);
            setColor(GREEN, BLACK);
            cout << "Transaksi dengan ID " << id << " telah dihapus.\n";
            setColor(WHITE, BLACK);

            // menulis log penghapusan transaksi
            string logMessage = "Transaksi Dihapus: ID " + to_string(id);
            writeLog(logMessage);

            ditemukan = true;
            break;
        }
    }
    
    if (!ditemukan) {
        setColor(RED, BLACK);
        cout << "Transaksi dengan ID " << id << " tidak ditemukan.\n";
        setColor(WHITE, BLACK);
    }
}

int main(){
    int idTransaksi = 1;  // ID transaksi pertama
    Transaksi transaksi;
    int choice;

    // Menampilkan menu untuk admin
    setColor(WHITE, BLUE); // Teks putih, background biru
    cout << "=======================================\n";
    cout << "        APLIKASI KASIR FUTSAL BYTE     \n";
    cout << "=======================================\n\n";
    setColor(WHITE, BLACK);

    if (!loginAdmin()) {
        setColor(RED, BLACK);
        cout << "Login gagal. Keluar dari program.\n";
        return 0;
    }

    do {
        setColor(YELLOW, BLACK); // Teks kuning
        cout << "\n=== Menu Admin ===\n";
        setColor(WHITE, BLACK);
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
                setColor(LIGHTRED, BLACK);
                cout << "Keluar dari program.\n";
                setColor(WHITE, BLACK);
                break;
        }

    } while (choice != 4);
    return 0;
}
