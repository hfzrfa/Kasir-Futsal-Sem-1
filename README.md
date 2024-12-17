Berikut adalah penjelasan dari kode yang saya buat:

### **1. Struktur Data Transaksi**

```cpp
struct Transaksi {
    int idTransaksi;
    string jenisLapangan;
    double hargaPerJam;
    int durasiSewa;  // dalam jam
    double totalHarga;
};
```
- **Struct** `Transaksi` digunakan untuk menyimpan detail transaksi penyewaan.
- Anggota struct:
  - `idTransaksi`: ID unik untuk transaksi.
  - `jenisLapangan`: Jenis lapangan yang disewa (Standar atau VIP).
  - `hargaPerJam`: Harga sewa per jam sesuai jenis lapangan.
  - `durasiSewa`: Durasi sewa lapangan dalam jam.
  - `totalHarga`: Total biaya sewa.

---

### **2. Vektor Penyimpanan Transaksi**

```cpp
vector<Transaksi> daftarTransaksi;
```
- **`vector<Transaksi>`** digunakan sebagai kontainer dinamis untuk menyimpan daftar transaksi yang terjadi selama program berjalan.

---

### **3. Login Admin**

```cpp
bool loginAdmin() {
    string username, password;
    const string adminUsername = "admin";
    const string adminPassword = "admin123";

    cout << "Masukkan username admin: ";
    cin >> username;
    cout << "Masukkan password admin: ";
    cin >> password;

    return (username == adminUsername && password == adminPassword);
}
```
- Fungsi **`loginAdmin`** digunakan untuk membatasi akses program hanya untuk admin.
- Menggunakan **username** dan **password** statis.
- Jika input cocok, fungsi mengembalikan **true**, sebaliknya **false**.

---

### **4. Menulis Log ke File**

```cpp
void writeLog(const string &message) {
    ofstream logFile;
    logFile.open("log_transaksi.txt", ios::app);
    if (logFile.is_open()) {
        logFile << message << endl;
        logFile.close();
    } else {
        cout << "Error: Tidak bisa membuka file log.\n";
    }
}
```
- Fungsi **`writeLog`** mencatat aktivitas program ke file `log_transaksi.txt` (append mode).
- Contoh log: "Transaksi Baru: ID 1, Lapangan: VIP, Durasi: 3 jam, Total: Rp 450000".

---

### **5. Menambah Transaksi**

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

    cout << "Masukkan durasi sewa (dalam jam): ";
    cin >> transaksi.durasiSewa;

    if (transaksi.durasiSewa <= 0) {
        cout << "Durasi sewa tidak valid.\n";
        return;
    }

    transaksi.totalHarga = transaksi.hargaPerJam * transaksi.durasiSewa;
    daftarTransaksi.push_back(transaksi);

    string logMessage = "Transaksi Baru: ID " + to_string(transaksi.idTransaksi) + 
                        ", Lapangan: " + transaksi.jenisLapangan +
                        ", Durasi: " + to_string(transaksi.durasiSewa) + 
                        " jam, Total: Rp " + to_string(transaksi.totalHarga);
    writeLog(logMessage);
}
```
- Mengambil input jenis lapangan dan durasi sewa dari user.
- Menghitung **totalHarga**: `hargaPerJam * durasiSewa`.
- Menambahkan transaksi ke **vector `daftarTransaksi`**.
- Menulis log transaksi baru ke file.

---

### **6. Mencetak Struk Transaksi**

```cpp
void printStruk(const Transaksi &transaksi) {
    cout << "\n\n======== Struk Pembayaran Futsal MarBit ========\n";
    cout << "ID Transaksi: " << transaksi.idTransaksi << endl;
    cout << "Jenis Lapangan: " << transaksi.jenisLapangan << endl;
    cout << "Durasi Sewa: " << transaksi.durasiSewa << " jam\n";
    cout << "Harga Per Jam: Rp " << fixed << setprecision(2) << transaksi.hargaPerJam << endl;
    cout << "Total Harga: Rp " << fixed << setprecision(2) << transaksi.totalHarga << endl;
    cout << "==============================================\n";
}
```
- Mencetak detail transaksi dengan format struk yang rapi.

---

### **7. Menampilkan Daftar Transaksi**

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
- Menampilkan semua transaksi yang disimpan di **vector `daftarTransaksi`**.

---

### **8. Menghapus Transaksi**

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
- Menghapus transaksi berdasarkan ID yang dimasukkan oleh user.
- Jika ID tidak ditemukan, menampilkan pesan kesalahan.

---

### **9. Menu Utama**

```cpp
int main() {
    int idTransaksi = 1;
    Transaksi transaksi;
    int choice;

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
            case 1: tampilkanDaftarTransaksi(); break;
            case 2: {
                int idHapus;
                cout << "Masukkan ID transaksi yang ingin dihapus: ";
                cin >> idHapus;
                hapusTransaksi(idHapus);
                break;
            }
            case 3: 
                addTransaksi(transaksi, idTransaksi);
                printStruk(transaksi);
                idTransaksi++;
                break;
            case 4: cout << "Terima kasih telah menggunakan layanan kami!\n"; break;
            default: cout << "Pilihan tidak valid.\n";
        }
    } while (choice != 4);

    return 0;
}
```
- Menu utama untuk admin dengan **4 pilihan**:
  1. Lihat daftar transaksi.
  2. Hapus transaksi.
  3. Tambah transaksi.
  4. Keluar dari program.

---

### **Kesimpulan**:
- Program ini sederhana tetapi mencakup berbagai fitur penting untuk aplikasi kasir.
- Menggunakan **vector** untuk penyimpanan sementara dan **file handling** untuk mencatat log transaksi.
- Fitur login memastikan akses dibatasi hanya untuk admin.
