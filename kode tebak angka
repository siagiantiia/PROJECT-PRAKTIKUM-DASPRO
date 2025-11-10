#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    int angkaRahasia, tebakan, jumlahTebakan = 0;
    char mainLagi;

    // Inisialisasi generator angka acak
    srand(time(NULL));

    do {
        // Pilih angka acak antara 1 dan 100
        angkaRahasia = rand() % 100 + 1;
        jumlahTebakan = 0;

        printf("=== GAME TEBAK ANGKA ===\n");
        printf("Saya telah memilih angka antara 1 dan 100.\n");
        printf("Coba tebak angka tersebut!\n\n");

        do {
            printf("Masukkan tebakan Anda: ");
            scanf("%d", &tebakan);
            jumlahTebakan++;

            if (tebakan < angkaRahasia) {
                printf("Terlalu kecil! Coba lagi.\n");
            } else if (tebakan > angkaRahasia) {
                printf("Terlalu besar! Coba lagi.\n");
            } else {
                printf("Selamat! Anda menebak dengan benar.\n");
                printf("Jumlah tebakan: %d\n", jumlahTebakan);
            }
        } while (tebakan != angkaRahasia);

        printf("\nApakah Anda ingin bermain lagi? (y/n): ");
        scanf(" %c", &mainLagi); // Spasi sebelum %c untuk mengabaikan newline

    } while (mainLagi == 'y' || mainLagi == 'Y');

    printf("Terima kasih telah bermain!\n");
    return 0;
}

