#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>  // Untuk toupper, tolower, isdigit

#define MAX_USERNAME 50
#define MAX_PASSWORD 50
#define MAX_NAMA 50
#define MAX_EMAIL 100
#define MAX_TRANSAKSI 100
#define MAX_KURSI 5  // 5x5 grid

// Struct untuk film
typedef struct {
    char judul[50];
    int harga;
    int rating;
} Film;

// Struct untuk transaksi
typedef struct {
    char nama[MAX_NAMA];
    char film[50];
    char kursi[3];  // e.g., "A1"
    int jumlah;
    int total;
    int diskon;
    int bayar;
} Transaksi;

// Variabel global
Film jadwal_film[5];  // Array untuk 4 film (index 1-4)
char kursi_terpesan[MAX_KURSI][MAX_KURSI];  // Array 2D untuk kursi (A-E, 1-5)
Transaksi riwayat_transaksi[MAX_TRANSAKSI];
int jumlah_transaksi = 0;

// Fungsi untuk inisialisasi data
void inisialisasi_data() {
    // Inisialisasi jadwal film
    strcpy(jadwal_film[1].judul, "Avengers: Endgame");
    jadwal_film[1].harga = 50000;
    jadwal_film[1].rating = 13;

    strcpy(jadwal_film[2].judul, "Frozen II");
    jadwal_film[2].harga = 40000;
    jadwal_film[2].rating = 7;

    strcpy(jadwal_film[3].judul, "Joker");
    jadwal_film[3].harga = 60000;
    jadwal_film[3].rating = 17;

    strcpy(jadwal_film[4].judul, "Detective Conan");
    jadwal_film[4].harga = 45000;
    jadwal_film[4].rating = 10;

    // Inisialisasi kursi terpesan (semua kosong)
    for (int i = 0; i < MAX_KURSI; i++) {
        for (int j = 0; j < MAX_KURSI; j++) {
            kursi_terpesan[i][j] = 0;  // 0 = kosong, 1 = terpesan
        }
    }
}

// Fungsi untuk login
int login() {
    char akun_user[] = "nadya";
    char akun_pass[] = "12345";
    char u[MAX_USERNAME], p[MAX_PASSWORD];

    while (1) {
        printf("\n=== LOGIN SISTEM ===\n");
        printf("Username: ");
        scanf("%49s", u);
        printf("Password: ");
        scanf("%49s", p);

        if (strcmp(u, akun_user) == 0 && strcmp(p, akun_pass) == 0) {
            printf("Login berhasil! Selamat datang, %s\n", u);
            return 1;
        } else {
            printf("Username/Password salah!\n");
        }
    }
}

// Fungsi untuk tampilkan jadwal
void tampilkan_jadwal() {
    printf("\n=== JADWAL FILM ===\n");
    for (int kode = 1; kode <= 4; kode++) {
        printf("%d. %s - Rp%d (Rating: %d+)\n", kode, jadwal_film[kode].judul, jadwal_film[kode].harga, jadwal_film[kode].rating);
    }
}

// Fungsi untuk tampilkan kursi
void tampilkan_kursi() {
    for (int i = 0; i < MAX_KURSI; i++) {
        for (int j = 0; j < MAX_KURSI; j++) {
            char kode[3];
            sprintf(kode, "%c%d", 'A' + i, j + 1);
            if (kursi_terpesan[i][j]) {
                printf("[ X ] ");
            } else {
                printf("[%s] ", kode);
            }
        }
        printf("\n");
    }
}

// Fungsi untuk cetak struk
void cetak_struk(Transaksi trx) {
    printf("\n==========================\n");
    printf("        STRUK XXI           \n");
    printf("===========================\n");
    printf("Nama   : %s\n", trx.nama);
    printf("Film   : %s\n", trx.film);
    printf("Kursi  : %s\n", trx.kursi);
    printf("Jumlah : %d tiket\n", trx.jumlah);
    printf("--------------------------\n");
    printf("Total  : Rp%d\n", trx.total);
    printf("Diskon : Rp%d\n", trx.diskon);
    printf("Bayar  : Rp%d\n", trx.bayar);
    printf("==========================\n");
    printf("Terima kasih! Selamat Menonton!\n\n");
}

// Fungsi untuk simpan struk
void simpan_struk(Transaksi trx) {
    char nama_file[100];
    sprintf(nama_file, "struk_%s_%s.txt", trx.nama, trx.film);
    // Ganti spasi dengan underscore
    for (int i = 0; nama_file[i]; i++) {
        if (nama_file[i] == ' ') nama_file[i] = '_';
    }

    FILE *f = fopen(nama_file, "w");
    if (f == NULL) {
        printf("Gagal simpan struk.\n");
        return;
    }
    fprintf(f, "=== STRUK PYTHON XXI ===\n");
    fprintf(f, "Nama   : %s\n", trx.nama);
    fprintf(f, "Film   : %s\n", trx.film);
    fprintf(f, "Kursi  : %s\n", trx.kursi);
    fprintf(f, "Jumlah : %d\n", trx.jumlah);
    fprintf(f, "Total  : %d\n", trx.total);
    fprintf(f, "Diskon : %d\n", trx.diskon);
    fprintf(f, "Bayar  : %d\n", trx.bayar);
    fclose(f);
    printf("Struk disimpan ke: %s\n", nama_file);
}

// Fungsi untuk pesan tiket
void pesan_tiket() {
    char nama[MAX_NAMA], kursi[3];
    int umur, kode, jumlah, row, col;

    printf("\n=== PESAN TIKET ===\n");
    printf("Nama Pembeli: ");
    scanf(" %[^\n]%*c", nama);  // Baca string dengan spasi
    // Kapitalisasi nama (sederhana)
    for (int i = 0; nama[i]; i++) {
        if (i == 0 || nama[i-1] == ' ') nama[i] = toupper(nama[i]);
        else nama[i] = tolower(nama[i]);
    }

    printf("Umur: ");
    scanf("%d", &umur);

    tampilkan_jadwal();
    printf("Pilih kode film: ");
    scanf("%d", &kode);
    if (kode < 1 || kode > 4) {
        printf("Film tidak tersedia.\n");
        return;
    }

    Film film = jadwal_film[kode];
    if (umur < film.rating) {
        printf("Maaf, umur Anda belum cukup.\n");
        return;
    }

    printf("\n=== DENAH KURSI ===\n");
    tampilkan_kursi();
    printf("Pilih kursi (A1-E5): ");
    scanf("%2s", kursi);
    // Konversi kursi ke row/col
    row = toupper(kursi[0]) - 'A';
    col = kursi[1] - '1';
    if (row < 0 || row >= MAX_KURSI || col < 0 || col >= MAX_KURSI || kursi_terpesan[row][col]) {
        printf("Kursi tidak valid atau sudah dipesan.\n");
        return;
    }
    kursi_terpesan[row][col] = 1;

    printf("Jumlah tiket: ");
    scanf("%d", &jumlah);
    int total = film.harga * jumlah;
    int diskon = (jumlah > 5) ? 0.1 * total : 0;
    int bayar = total - diskon;

    Transaksi trx;
    strcpy(trx.nama, nama);
    strcpy(trx.film, film.judul);
    strcpy(trx.kursi, kursi);
    trx.jumlah = jumlah;
    trx.total = total;
    trx.diskon = diskon;
    trx.bayar = bayar;

    riwayat_transaksi[jumlah_transaksi++] = trx;
    cetak_struk(trx);
    simpan_struk(trx);
}

// Fungsi untuk lihat riwayat
void lihat_riwayat() {
    printf("\n=== RIWAYAT TRANSAKSI ===\n");
    if (jumlah_transaksi == 0) {
        printf("Belum ada transaksi.\n");
        return;
    }
    for (int i = 0; i < jumlah_transaksi; i++) {
        printf("%d. %s - %s - Kursi %s - Rp%d\n", i+1, riwayat_transaksi[i].nama, riwayat_transaksi[i].film, riwayat_transaksi[i].kursi, riwayat_transaksi[i].bayar);
    }
}

// Fungsi untuk cetak ulang struk
void cetak_ulang_struk() {
    lihat_riwayat();
    if (jumlah_transaksi == 0) return;
    int no;
    printf("Pilih nomor transaksi: ");
    if (scanf("%d", &no) != 1 || no < 1 || no > jumlah_transaksi) {
        printf("Nomor tidak valid.\n");
        return;
    }
    cetak_struk(riwayat_transaksi[no - 1]);
}

// Fungsi untuk cek email
void cek_email() {
    char email[MAX_EMAIL];
    printf("\n=== VALIDASI EMAIL ===\n");
    printf("Masukkan email: ");
    scanf("%99s", email);
    char *at = strchr(email, '@');
    if (at && strchr(at + 1, '.')) {
        printf("Email valid!\n");
    } else {
        printf("Email tidak valid!\n");
    }
}

int main() {
    inisialisasi_data();
    printf("=== SELAMAT DATANG DI SISTEM BIOSKOP PYTHON XXI ===");

    if (!login()) return 1;

    while (1) {
        printf("\n=== MENU UTAMA PYTHON XXI ===\n");
        printf("1. Pesan Tiket\n");
        printf("2. Lihat Jadwal Film\n");
        printf("3. Lihat Riwayat Transaksi\n");
        printf("4. Cetak Ulang Struk\n");
        printf("5. Validasi Email\n");
        printf("6. Keluar\n");
        printf("Pilih menu: ");

        int menu;
        if (scanf("%d", &menu) != 1) {
            printf("Input harus angka!\n");
            while (getchar() != '\n');  // Clear buffer
            continue;
        }

        if (menu == 1) pesan_tiket();
        else if (menu == 2) tampilkan_jadwal();
        else if (menu == 3) lihat_riwayat();
        else if (menu == 4) cetak_ulang_struk();
        else if (menu == 5) cek_email();
        else if (menu == 6) {
            printf("Terima kasih, sampai jumpa!\n");
            break;
        } else {
            printf("Menu tidak valid!\n");
        }
    }

    return 0;
}
