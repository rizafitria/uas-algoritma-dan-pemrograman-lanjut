#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX 30

char nim[MAX][20];
float nilai[MAX][3];
int jumlah = 0;
char buffer[100];

/* ================= FUNGSI REKURSIF ================= */
int faktorial(int n) {
    if (n <= 1) return 1;
    return n * faktorial(n - 1);
}

/* ================= FIBONACCI ITERATIF ================= */
void fibonacciIteratif(int n) {
    int a = 0, b = 1, c;
    for (int i = 0; i < n; i++) {
        printf("%d ", a);
        c = a + b;
        a = b;
        b = c;
    }
}

/* ================= INPUT DATA OTOMATIS ================= */
void inputData() {
    char data_awal[22][20] = {
        "C2483207011", "C2483207028", "C2483207002", "C2483207016",
        "C2483207003", "C2483207006", "C2483207001", "C2483207009",
        "C2383207003", "C2483207014", "C2483207029", "C2383207017",
        "C2483207030", "C2483207004", "C2483207007", "C2483207005",
        "C2483207010", "C2483207031", "C2483207015", "C2383207016",
        "C2483207018", "C2483207012"
    };

    jumlah = 22;
    srand(time(NULL));

    printf("\n[!] Memproses 22 data mahasiswa...\n");
    for (int i = 0; i < jumlah; i++) {
        strcpy(nim[i], data_awal[i]);
        nilai[i][0] = (rand() % (85 - 70 + 1)) + 70;
        nilai[i][1] = (rand() % (85 - 70 + 1)) + 70;
        nilai[i][2] = (rand() % (85 - 70 + 1)) + 70;
    }
    printf("[OK] Data berhasil dimuat secara otomatis.\n");
}

/* ================= TAMPIL DATA (TABEL RAPI) ================= */
void tampilData() {
    if (jumlah == 0) {
        printf("\n[!] Data kosong! Silakan isi data terlebih dahulu.\n");
        return;
    }

    printf("\n+-----+--------------+-------+-------+-------+-----------+");
    printf("\n| No  |      NIM     | Tugas |  UTS  |  UAS  | Rata-rata |");
    printf("\n+-----+--------------+-------+-------+-------+-----------+");

    for (int i = 0; i < jumlah; i++) {
        float rata = (nilai[i][0] + nilai[i][1] + nilai[i][2]) / 3;
        printf("\n| %-3d | %-12s | %-5.1f | %-5.1f | %-5.1f | %-9.2f |",
               i + 1, nim[i], nilai[i][0], nilai[i][1], nilai[i][2], rata);
    }

    printf("\n+-----+--------------+-------+-------+-------+-----------+\n");
}

/* ================= TAMBAH DATA ================= */
void tambahData() {
    if (jumlah >= MAX) {
        printf("\n[!] Kapasitas penuh!\n");
        return;
    }
    printf("\n--- Tambah Mahasiswa Baru ---\n");
    printf("NIM          : ");
    fgets(nim[jumlah], sizeof(nim[jumlah]), stdin);
    nim[jumlah][strcspn(nim[jumlah], "\n")] = 0;

    printf("Nilai Tugas  : ");
    fgets(buffer, sizeof(buffer), stdin);
    sscanf(buffer, "%f", &nilai[jumlah][0]);

    printf("Nilai UTS    : ");
    fgets(buffer, sizeof(buffer), stdin);
    sscanf(buffer, "%f", &nilai[jumlah][1]);

    printf("Nilai UAS    : ");
    fgets(buffer, sizeof(buffer), stdin);
    sscanf(buffer, "%f", &nilai[jumlah][2]);

    jumlah++;
    printf("[OK] Data berhasil ditambahkan.\n");
}

/* ================= UBAH NILAI ================= */
void ubahData() {
    char cari[20];
    printf("\nMasukkan NIM yang akan diubah: ");
    fgets(cari, sizeof(cari), stdin);
    cari[strcspn(cari, "\n")] = 0;

    for (int i = 0; i < jumlah; i++) {
        if (strcmp(nim[i], cari) == 0) {
            printf("[ Found ] Mengubah data NIM: %s\n", nim[i]);
            printf("Nilai Tugas Baru : "); fgets(buffer, sizeof(buffer), stdin); sscanf(buffer, "%f", &nilai[i][0]);
            printf("Nilai UTS Baru   : "); fgets(buffer, sizeof(buffer), stdin); sscanf(buffer, "%f", &nilai[i][1]);
            printf("Nilai UAS Baru   : "); fgets(buffer, sizeof(buffer), stdin); sscanf(buffer, "%f", &nilai[i][2]);
            printf("[OK] Data diperbarui.\n");
            return;
        }
    }
    printf("[!] NIM tidak ditemukan.\n");
}

/* ================= HAPUS DATA ================= */
void hapusData() {
    char cari[20];
    printf("\nMasukkan NIM yang ingin dihapus: ");
    fgets(cari, sizeof(cari), stdin);
    cari[strcspn(cari, "\n")] = 0;

    for (int i = 0; i < jumlah; i++) {
        if (strcmp(nim[i], cari) == 0) {
            for (int j = i; j < jumlah - 1; j++) {
                strcpy(nim[j], nim[j + 1]);
                nilai[j][0] = nilai[j + 1][0];
                nilai[j][1] = nilai[j + 1][1];
                nilai[j][2] = nilai[j + 1][2];
            }
            jumlah--;
            printf("[OK] Data %s telah dihapus.\n", cari);
            return;
        }
    }
    printf("[!] Data tidak ditemukan.\n");
}

/* ================= PENGOLAHAN (STATISTIK) ================= */
void pengolahanNilai() {
    if (jumlah == 0) return;
    float max = 0, min = 101, total_kelas = 0;
    for (int i = 0; i < jumlah; i++) {
        float rata = (nilai[i][0] + nilai[i][1] + nilai[i][2]) / 3;
        if (rata > max) max = rata;
        if (rata < min) min = rata;
        total_kelas += rata;
    }
    printf("\n======== STATISTIK NILAI ========\n");
    printf("Rata-rata tertinggi : %.2f\n", max);
    printf("Rata-rata terendah  : %.2f\n", min);
    printf("Rata-rata kelas     : %.2f\n", total_kelas / jumlah);
    printf("=================================\n");
}

/* ================= FITUR REKURSIF ================= */
void fiturRekursif() {
    printf("\n--- Fitur Matematika Rekursif ---\n");
    printf("Faktorial dari %d (jumlah mhs) : %d\n", jumlah, faktorial(jumlah));
    printf("Deret Fibonacci (%d angka)     : ", jumlah);
    fibonacciIteratif(jumlah);
    printf("\n---------------------------------\n");
}

/* ================= MAIN PROGRAM ================= */
int main() {
    int menu;
    do {
        printf("\n=======================================");
        printf("\n      SISTEM DATA MAHASISWA PTI       ");
        printf("\n=======================================");
        printf("\n1. Isi Data Otomatis (22 NIM)");
        printf("\n2. Lihat Tabel Nilai ");
        printf("\n3. Tambah Mahasiswa");
        printf("\n4. Ubah Nilai Mahasiswa");
        printf("\n5. Hapus Mahasiswa");
        printf("\n6. Statistik & Pengolahan");
        printf("\n7. Fitur Rekursif & Fibonacci");
        printf("\n8. Keluar");
        printf("\n=======================================");
        printf("\nPilih Menu [1-8]: ");

        if (fgets(buffer, sizeof(buffer), stdin) != NULL) {
            if (sscanf(buffer, "%d", &menu) != 1) menu = 0;
        }

        switch (menu) {
            case 1: inputData(); break;
            case 2: tampilData(); break;
            case 3: tambahData(); break;
            case 4: ubahData(); break;
            case 5: hapusData(); break;
            case 6: pengolahanNilai(); break;
            case 7: fiturRekursif(); break;
            case 8: printf("\nKeluar program. Sampai jumpa!\n"); break;
            default: printf("\n[!] Pilihan tidak valid.\n");
        }
    } while (menu != 8);

    return 0;
}
