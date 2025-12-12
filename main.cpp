#include "tubes.h"

void tampilkanMenu() {
    cout << "\n=== MENU MANAJEMEN KURSUS ===" << endl;
    cout << "1. Tambah Kursus" << endl;
    cout << "2. Tambah Modul ke Kursus" << endl;
    cout << "3. Hapus Kursus" << endl;
    cout << "4. Tampilkan Semua Kursus" << endl;
    cout << "5. Cari Berdasarkan Level" << endl;
    cout << "6. Cari Berdasarkan Judul" << endl;
    cout << "7. Cari Durasi <= X Jam" << endl;
    cout << "8. Hitung Kursus per Level" << endl;
    cout << "9. Kursus dengan Modul Terbanyak" << endl;
    cout << "0. Keluar" << endl;
    cout << "Pilih menu: ";
}

int main() {
    listKursus L;
    createListKursus(L);

    int pilihan;
    pilihan = -1;

    while (pilihan != 0) {
        tampilkanMenu();
        cin >> pilihan;

        if (pilihan == 1) {
            // ========== 1. TAMBAH KURSUS ==========
            kursus dataKursus;
            cout << "\n--- Tambah Kursus ---" << endl;
            cout << "Kode Kursus: ";
            cin >> dataKursus.kode;

            adrKursus cek = findKursus(L, dataKursus.kode);
            if (cek != NULL) {
                cout << "Kode sudah ada!" << endl;
            } else {
                cout << "Judul Kursus: ";
                cin >> dataKursus.judul;
                cout << "Level: ";
                cin >> dataKursus.level;
                cout << "Durasi (jam): ";
                cin >> dataKursus.durasi;

                adrKursus P = alokasiKursus(dataKursus);
                insertLastKursus(L, P);
                cout << "Kursus berhasil ditambahkan!" << endl;
            }

        } else if (pilihan == 2) {
            // ========== 2. TAMBAH MODUL KE KURSUS ==========
            string kodeKursus;
            modul dataModul;

            cout << "\n--- Tambah Modul ke Kursus ---" << endl;
            cout << "Kode Kursus: ";
            cin >> kodeKursus;

            adrKursus P = findKursus(L, kodeKursus);

            if (P == NULL) {
                cout << "Kursus tidak ditemukan!" << endl;
            } else {
                cout << "Nama Modul: ";
                cin >> dataModul.nama;

                adrModul cek = findModul(P, dataModul.nama);
                if (cek != NULL) {
                    cout << "Modul sudah ada!" << endl;
                } else {
                    connectModulToKursus(P, dataModul);
                    cout << "Modul berhasil ditambahkan!" << endl;
                }
            }

        } else if (pilihan == 3) {
            // ========== 3. HAPUS KURSUS ==========
            string kodeKursus;
            cout << "\n--- Hapus Kursus ---" << endl;
            cout << "Kode Kursus: ";
            cin >> kodeKursus;

            adrKursus P = findKursus(L, kodeKursus);

            if (P == NULL) {
                cout << "Kursus tidak ditemukan!" << endl;
            } else {
                deleteKursusWithModul(L, kodeKursus);
                cout << "Kursus berhasil dihapus!" << endl;
            }

        } else if (pilihan == 4) {
            // ========== 4. TAMPILKAN SEMUA KURSUS ==========
            showKursusWithModul(L);

        } else if (pilihan == 5) {
            // ========== 5. CARI BERDASARKAN LEVEL ==========
            string level;
            cout << "\n--- Cari Berdasarkan Level ---" << endl;
            cout << "Level: ";
            cin >> level;

            searchKursusByLevel(L, level);

        } else if (pilihan == 6) {
            // ========== 6. CARI BERDASARKAN JUDUL ==========
            string judul;
            cout << "\n--- Cari Berdasarkan Judul ---" << endl;
            cout << "Judul: ";
            cin >> judul;

            adrKursus P = L.first;
            bool found = false;

            cout << "\nHasil pencarian:" << endl;
            while (P != NULL) {
                if (P->info.judul == judul) {
                    cout << "Kode   : " << P->info.kode << endl;
                    cout << "Judul  : " << P->info.judul << endl;
                    cout << "Level  : " << P->info.level << endl;
                    cout << "Durasi : " << P->info.durasi << " jam" << endl;
                    cout << "Modul  : " << countModul(P) << " modul" << endl;
                    found = true;
                }
                P = P->next;
            }

            if (found == false) {
                cout << "Kursus tidak ditemukan!" << endl;
            }

        } else if (pilihan == 7) {
            // ========== 7. CARI DURASI <= X JAM ==========
            int maxDurasi;
            cout << "\n--- Cari Durasi <= X Jam ---" << endl;
            cout << "Maksimal durasi (jam): ";
            cin >> maxDurasi;

            adrKursus P = L.first;
            bool found = false;
            int no = 1;

            cout << "\nKursus dengan durasi <= " << maxDurasi << " jam:" << endl;
            while (P != NULL) {
                if (P->info.durasi <= maxDurasi) {
                    cout << no << ". " << P->info.judul;
                    cout << " (" << P->info.kode << ")";
                    cout << " - " << P->info.durasi << " jam" << endl;
                    found = true;
                    no++;
                }
                P = P->next;
            }

            if (found == false) {
                cout << "Tidak ada kursus!" << endl;
            }

        } else if (pilihan == 8) {
            // ========== 8. HITUNG KURSUS PER LEVEL ==========
            string level;
            cout << "\n--- Hitung Kursus per Level ---" << endl;
            cout << "Level: ";
            cin >> level;

            int jumlah = countKursusByLevel(L, level);
            cout << "Jumlah kursus level " << level << ": " << jumlah << endl;

        } else if (pilihan == 9) {
            // ========== 9. KURSUS DENGAN MODUL TERBANYAK ==========
            adrKursus P = findKursusMaxModul(L);

            if (P == NULL) {
                cout << "Tidak ada kursus!" << endl;
            } else {
                cout << "\n--- Kursus dengan Modul Terbanyak ---" << endl;
                cout << "Kursus : " << P->info.judul << endl;
                cout << "Kode   : " << P->info.kode << endl;
                cout << "Level  : " << P->info.level << endl;
                cout << "Jumlah : " << countModul(P) << " modul" << endl;
            }

        } else if (pilihan == 0) {
            cout << "\nTerima kasih!" << endl;

        } else {
            cout << "Pilihan tidak valid!" << endl;
        }
    }

    return 0;
}
