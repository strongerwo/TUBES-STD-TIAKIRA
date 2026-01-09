#include <iostream>
#include <string>
#include "TUBES.h"

using namespace std;

int main(){
    listKursus L;
    createList(L);

    while(true){
        int pilih;

        cout << "---------------------------------";
        cout << "\n========== MENU KURSUS==========\n";
        cout << "---------------------------------\n";
        cout << "1. Tambah Kursus\n";
        cout << "2. Tambah Modul ke Kursus\n";
        cout << "3. Update Kursus\n";
        cout << "4. Hapus Kursus\n";
        cout << "5. Tampilkan Semua Kursus\n";
        cout << "6. Cari Berdasarkan Level\n";
        cout << "7. Cari Berdasarkan Judul\n";
        cout << "8. Cari Durasi <= X Jam\n";
        cout << "9. Hitung Kursus per Level\n";
        cout << "10. Kursus dengan Modul Terbanyak\n";
        cout << "11. Kursus dengan Modul Tersedikit\n";
        cout << "12. Urutkan Kursus berdasarkan Jumlah Modul\n";
        cout << "0. Keluar\n";

        cout << "Pilih menu: ";
        cin >> pilih;

        if(pilih == 0){
            break; // KELUAR PROGRAM
        }

        if(pilih == 1){
            kursus k;

            cout << "Kode   : ";
            cin >> k.kode;

            cout << "Judul  : ";
            cin >> k.judul;

            int p;
            do{
                cout << "Pilih Level:\n";
                cout << "1. Beginner\n";
                cout << "2. Intermediate\n";
                cout << "3. Advanced\n";
                cout << "Pilih (1-3): ";
                cin >> p;
            } while(p < 1 || p > 3);

            if(p == 1) k.level = "Beginner";
            if(p == 2) k.level = "Intermediate";
            if(p == 3) k.level = "Advanced";

            cout << "Durasi (jam): ";
            cin >> k.durasi;

            if(findKursus(L, k.kode) != nullptr){
                cout << "Kode sudah ada!\n";
            } else {
                insertLastKursus(L, createElemenKursus(k));
                cout << "--Berhasil tambah kursus--\n";
            }
        }
        else if(pilih == 2){
            string kode;
            cout << "Kode kursus: ";
            cin >> kode;

            adrKursus K = findKursus(L, kode);
            if(K != nullptr){
                modul m;

                cout << "Nama modul: ";
                cin >> m.nama;

                cout << "Jumlah materi (max 10): ";
                cin >> m.jumlahMateri;

                if(m.jumlahMateri > MAX_MATERI) m.jumlahMateri = MAX_MATERI;
                if(m.jumlahMateri < 0) m.jumlahMateri = 0;

                for(int i = 0; i < m.jumlahMateri; i++){
                    cout << "Materi ke-" << i+1 << ": ";
                    cin >> m.materi[i];
                }

                insertLastModul(K, createElemenModul(m));
                cout << "--Berhasil tambah modul--\n";
            } else {
                cout << "--Kursus tidak ditemukan--\n";
            }
        }
        else if(pilih == 3){
            string kode;
            cout << "Kode kursus: ";
            cin >> kode;

            adrKursus K = findKursus(L, kode);
            if(K != nullptr){
                string judul;
                cout << "Judul baru: ";
                cin >> judul;

                int p;
                do{
                    cout << "Pilih Level:\n";
                    cout << "1. Beginner\n";
                    cout << "2. Intermediate\n";
                    cout << "3. Advanced\n";
                    cout << "Pilih (1-3): ";
                    cin >> p;
                } while(p < 1 || p > 3);

                string level;
                if(p == 1) level = "Beginner";
                if(p == 2) level = "Intermediate";
                if(p == 3) level = "Advanced";

                int durasi;
                cout << "Durasi baru: ";
                cin >> durasi;

                updateKursus(L, kode, judul, level, durasi);
                cout << "--Berhasil update--\n";
            } else {
                cout << "--Kursus tidak ditemukan--\n";
            }
        }
        else if(pilih == 4){
            string kode;
            cout << "Kode kursus: ";
            cin >> kode;
            deleteKursus(L, kode);
            cout << "--Kursus berhasil dihapus-- \n";
        }
        else if(pilih == 5){
            tampilKursus(L);
        }
        else if(pilih == 6){
            string level;
            cout << "Level: ";
            cin >> level;
            cariBerdasarkanLevel(L, level);
        }
        else if(pilih == 7){
            string j;
            cout << "Judul: ";
            cin >> j;
            cariBerdasarkanJudul(L, j);
        }
        else if(pilih == 8){
            int d;
            cout << "Durasi max: ";
            cin >> d;
            cariDurasiKurang(L, d);
        }
        else if(pilih == 9){
            string level;
            cout << "Level: ";
            cin >> level;
            cout << "Jumlah: " << hitungPerLevel(L, level) << endl;
        }
        else if(pilih == 10){
            adrKursus k = kursusModulTerbanyak(L);
            if(k != nullptr)
                cout << k->info.kode << " - " << k->info.judul << endl;
        }
        else if(pilih == 11){
            adrKursus k = kursusModulTersedikit(L);
            if(k != nullptr)
                cout << k->info.kode << " - " << k->info.judul << endl;
        }
        else if(pilih == 12){
            sortKursusByJumlahModul(L);
            tampilKursus(L);
        }
        else{
            cout << "--Menu tidak valid--\n";
        }
    }

    clearList(L);
    cout << "---Program selesai---\n";
    return 0;
}
