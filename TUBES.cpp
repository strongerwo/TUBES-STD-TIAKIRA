#include "TUBES.h"
#include <iostream>
#include <string>

using namespace std;

void createList(listKursus &L){
    // I.S. List kursus belum terinisialisasi atau berisi nilai acak.
    // F.S. List kursus menjadi kosong dengan first dan last bernilai nullptr.
    L.first = nullptr;
    L.last  = nullptr;
}

void clearList(listKursus &L){
    // I.S. List kursus L berisi data atau kosong.
    // F.S. Semua node kursus dan node modul dibebaskan, list menjadi kosong.
    adrKursus P = L.first;
    while(P != nullptr){
        adrKursus nextK = P->next;

        adrModul M = P->firstModul;
        while(M != nullptr){
            adrModul nextM = M->next;
            delete M;
            M = nextM;
        }

        delete P;
        P = nextK;
    }
    L.first = nullptr;
    L.last  = nullptr;
}

adrKursus createElemenKursus(kursus k){
    // I.S. Data kursus k tersedia.
    // F.S. Mengembalikan alamat node kursus baru dengan list modul kosong.
    adrKursus P = new elemenKursus;
    P->info = k;
    P->next = nullptr;
    P->prev = nullptr;
    P->firstModul = nullptr;
    return P;
}

adrModul createElemenModul(modul m){
    // I.S. Data modul m tersedia (nama, materi[], jumlahMateri).
    // F.S. Mengembalikan alamat node modul baru, jumlahMateri dipastikan 0..MAX_MATERI.
    if(m.jumlahMateri < 0) m.jumlahMateri = 0;
    if(m.jumlahMateri > MAX_MATERI) m.jumlahMateri = MAX_MATERI;

    adrModul P = new elemenModul;
    P->info = m;
    P->next = nullptr;
    P->prev = nullptr;
    return P;
}

void insertLastKursus(listKursus &L, adrKursus P){
    // I.S. List kursus L mungkin kosong/berisi, P adalah node kursus valid.
    // F.S. Node P ditambahkan sebagai elemen terakhir list kursus.
    if(L.first == nullptr){
        L.first = P;
        L.last  = P;
    } else {
        L.last->next = P;
        P->prev = L.last;
        L.last = P;
    }
}

void insertLastModul(adrKursus K, adrModul M){
    // I.S. K adalah kursus valid, list modul K bisa kosong/berisi, M node modul valid.
    // F.S. Node modul M ditambahkan sebagai modul terakhir pada kursus K.
    if(K->firstModul == nullptr){
        K->firstModul = M;
    } else {
        adrModul Q = K->firstModul;
        while(Q->next != nullptr){
            Q = Q->next;
        }
        Q->next = M;
        M->prev = Q;
    }
}

adrKursus findKursus(listKursus L, string kode){
    // I.S. List kursus L berisi data atau kosong, kode adalah kode kursus yang dicari.
    // F.S. Mengembalikan alamat kursus jika ditemukan, atau nullptr jika tidak ditemukan.
    adrKursus P = L.first;
    while(P != nullptr){
        if(P->info.kode == kode) return P;
        P = P->next;
    }
    return nullptr;
}

void updateKursus(listKursus &L, string kode, string judulBaru, string levelBaru, int durasiBaru){
    // I.S. List kursus L berisi data, kode adalah kode kursus yang akan diupdate.
    // F.S. Jika kursus ditemukan, judul/level/durasi berubah sesuai input baru.
    adrKursus P = findKursus(L, kode);
    if(P == nullptr) return;

    P->info.judul  = judulBaru;
    P->info.level  = levelBaru;
    P->info.durasi = durasiBaru;
}

void deleteKursus(listKursus &L, string kode){
    // I.S. List kursus L berisi data atau kosong, kode adalah kode kursus yang akan dihapus.
    // F.S. Jika ditemukan, kursus beserta seluruh modulnya terhapus dari list.
    adrKursus P = findKursus(L, kode);
    if(P == nullptr) return;

    adrModul M = P->firstModul;
    while(M != nullptr){
        adrModul del = M;
        M = M->next;
        delete del;
    }
    P->firstModul = nullptr;

    if(P == L.first && P == L.last){
        L.first = nullptr;
        L.last  = nullptr;
    } else if(P == L.first){
        L.first = P->next;
        if(L.first) L.first->prev = nullptr;
    } else if(P == L.last){
        L.last = P->prev;
        if(L.last) L.last->next = nullptr;
    } else {
        P->prev->next = P->next;
        P->next->prev = P->prev;
    }
    delete P;
}

void tampilModul(adrKursus K){
    // I.S. K adalah kursus valid, list modul bisa kosong/berisi.
    // F.S. Menampilkan semua modul beserta daftar materi ke layar.
    adrModul M = K->firstModul;
    while(M != nullptr){
        cout << "    - Modul: " << M->info.nama << endl;
        for(int i = 0; i < M->info.jumlahMateri; i++){
            cout << "        * " << M->info.materi[i] << endl;
        }
        M = M->next;
    }
}

void tampilKursus(listKursus L){
    // I.S. List kursus L berisi data atau kosong.
    // F.S. Menampilkan seluruh data kursus beserta modul dan materinya ke layar.
    adrKursus P = L.first;
    if(P == nullptr){
        cout << "(Belum ada kursus)\n";
        return;
    }

    while(P != nullptr){
        cout << "Kode   : " << P->info.kode << endl;
        cout << "Judul  : " << P->info.judul << endl;
        cout << "Level  : " << P->info.level << endl;
        cout << "Durasi : " << P->info.durasi << " jam" << endl;
        cout << "Modul  :\n";
        tampilModul(P);
        cout << "-------------------------\n";
        P = P->next;
    }
}

void cariBerdasarkanLevel(listKursus L, string level){
    // I.S. List kursus L berisi data atau kosong.
    // F.S. Menampilkan kursus sesuai level.
    adrKursus P = L.first;
    bool ada = false;
    while(P != nullptr){
        if(P->info.level == level){
            cout << P->info.kode << " - " << P->info.judul << endl;
            ada = true;
        }
        P = P->next;
    }
    if(!ada) cout << "(Tidak ada)\n";
}

void cariBerdasarkanJudul(listKursus L, string judul){
    // I.S. List kursus L berisi data atau kosong.
    // F.S. Menampilkan kursus sesuai judul.
    adrKursus P = L.first;
    bool ada = false;
    while(P != nullptr){
        if(P->info.judul == judul){
            cout << P->info.kode << " - " << P->info.level << endl;
            ada = true;
        }
        P = P->next;
    }
    if(!ada) cout << "(Tidak ada)\n";
}

void cariDurasiKurang(listKursus L, int maxDurasi){
    // I.S. List kursus L berisi data atau kosong.
    // F.S. Menampilkan kursus dengan durasi <= maxDurasi.
    adrKursus P = L.first;
    bool ada = false;
    while(P != nullptr){
        if(P->info.durasi <= maxDurasi){
            cout << P->info.kode << " - " << P->info.judul << endl;
            ada = true;
        }
        P = P->next;
    }
    if(!ada) cout << "(Tidak ada)\n";
}

int hitungPerLevel(listKursus L, string level){
    // I.S. List kursus L berisi data atau kosong.
    // F.S. Mengembalikan jumlah kursus per level.
    int count = 0;
    adrKursus P = L.first;
    while(P != nullptr){
        if(P->info.level == level) count++;
        P = P->next;
    }
    return count;
}

adrKursus kursusModulTerbanyak(listKursus L){
    // I.S. List kursus L berisi data atau kosong.
    // F.S. Mengembalikan kursus dengan modul terbanyak.
    adrKursus P = L.first;
    adrKursus maxK = nullptr;
    int maxCount = -1;

    while(P != nullptr){
        int count = 0;
        adrModul M = P->firstModul;
        while(M != nullptr){
            count++;
            M = M->next;
        }

        if(count > maxCount){
            maxCount = count;
            maxK = P;
        }
        P = P->next;
    }
    return maxK;
}

adrKursus kursusModulTersedikit(listKursus L){
    // I.S. List kursus L berisi data atau kosong.
    // F.S. Mengembalikan kursus dengan modul tersedikit.
   adrKursus P = L.first;
    if(P == nullptr) return nullptr;
    int minCount = 0;
    adrModul M = P->firstModul;
    while(M != nullptr){
        minCount++;
        M = M->next;
    }

    adrKursus minK = P;
    P = P->next;

    while(P != nullptr){
        int count = 0;
        M = P->firstModul;
        while(M != nullptr){
            count++;
            M = M->next;
        }

        if(count < minCount){
            minCount = count;
            minK = P;
        }
        P = P->next;
    }
    return minK;
}

void sortKursusByJumlahModul(listKursus &L){
    // I.S. List kursus L berisi data atau kosong
    // F.S. Kursus diurutkan DESC berdasarkan jumlah modul

    if(L.first == nullptr || L.first->next == nullptr){
        return;
    }

    bool swapped = true;

    while(swapped){
        swapped = false;
        adrKursus P = L.first;

        while(P->next != nullptr){
            adrKursus Q = P->next;

            // Hitung modul P
            int cP = 0;
            adrModul M = P->firstModul;
            while(M != nullptr){
                cP++;
                M = M->next;
            }

            // Hitung modul Q
            int cQ = 0;
            M = Q->firstModul;
            while(M != nullptr){
                cQ++;
                M = M->next;
            }

            // Swap jika perlu (DESC)
            if(cP < cQ){
                // swap info kursus
                kursus tempInfo = P->info;
                P->info = Q->info;
                Q->info = tempInfo;

                // swap modul
                adrModul tempModul = P->firstModul;
                P->firstModul = Q->firstModul;
                Q->firstModul = tempModul;

                swapped = true;
            }

            P = P->next;
        }
    }
}
