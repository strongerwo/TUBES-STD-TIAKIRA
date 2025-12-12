#include "tubes.h"

void createListKursus(listKursus &L) {
    /* I.S. sembarang
       F.S. terbentuk list kosong dengan first dan last = NULL */
    L.first = NULL;
    L.last = NULL;
}

adrKursus alokasiKursus(kursus x) {
    /* Mengembalikan address hasil alokasi elemen kursus
       Jika alokasi berhasil, maka address != NULL */
    adrKursus P = new elemenKursus;
    P->info = x;
    P->next = NULL;
    P->prev = NULL;
    P->firstModul = NULL;
    return P;
}

void dealokasiKursus(adrKursus &P) {
    /* I.S. P terdefinisi
       F.S. memori yang digunakan P dikembalikan ke sistem */
    delete P;
    P = NULL;
}

void insertFirstKursus(listKursus &L, adrKursus P) {
    /* I.S. L mungkin kosong, P sudah dialokasi
       F.S. P menjadi elemen pertama list */
    if (L.first == NULL) {
        L.first = P;
        L.last = P;
    } else {
        P->next = L.first;
        L.first->prev = P;
        L.first = P;
    }
}

void insertLastKursus(listKursus &L, adrKursus P) {
    /* I.S. L mungkin kosong, P sudah dialokasi
       F.S. P menjadi elemen terakhir list */
    if (L.first == NULL) {
        L.first = P;
        L.last = P;
    } else {
        P->prev = L.last;
        L.last->next = P;
        L.last = P;
    }
}

void insertAfterKursus(listKursus &L, adrKursus Prec, adrKursus P) {
    /* I.S. Prec dan P sudah dialokasi, Prec adalah elemen list
       F.S. P menjadi elemen setelah Prec */
    if (Prec != NULL && P != NULL) {
        P->next = Prec->next;
        P->prev = Prec;
        if (Prec->next != NULL) {
            Prec->next->prev = P;
        } else {
            L.last = P;
        }
        Prec->next = P;
    }
}

void deleteFirstKursus(listKursus &L, adrKursus &P) {
    /* I.S. L tidak kosong
       F.S. elemen pertama list dihapus dan disimpan di P */
    if (L.first != NULL) {
        P = L.first;
        if (L.first == L.last) {
            L.first = NULL;
            L.last = NULL;
        } else {
            L.first = P->next;
            L.first->prev = NULL;
            P->next = NULL;
        }
    }
}

void deleteLastKursus(listKursus &L, adrKursus &P) {
    /* I.S. L tidak kosong
       F.S. elemen terakhir list dihapus dan disimpan di P */
    if (L.first != NULL) {
        P = L.last;
        if (L.first == L.last) {
            L.first = NULL;
            L.last = NULL;
        } else {
            L.last = P->prev;
            L.last->next = NULL;
            P->prev = NULL;
        }
    }
}

void deleteAfterKursus(listKursus &L, adrKursus Prec, adrKursus &P) {
    /* I.S. Prec adalah elemen list dan bukan elemen terakhir
       F.S. elemen setelah Prec dihapus dan disimpan di P */
    if (Prec != NULL && Prec->next != NULL) {
        P = Prec->next;
        Prec->next = P->next;
        if (P->next != NULL) {
            P->next->prev = Prec;
        } else {
            L.last = Prec;
        }
        P->next = NULL;
        P->prev = NULL;
    }
}

adrKursus findKursus(listKursus L, string kode) {
    /* Mengembalikan address kursus dengan kode tertentu
       Mengembalikan NULL jika tidak ditemukan */
    adrKursus P = L.first;
    while (P != NULL) {
        if (P->info.kode == kode) {
            return P;
        }
        P = P->next;
    }
    return NULL;
}

void showAllKursus(listKursus L) {
    /* I.S. L mungkin kosong
       F.S. menampilkan semua data kursus dalam list */
    if (L.first == NULL) {
        cout << "List kursus kosong" << endl;
    } else {
        adrKursus P = L.first;
        int no = 1;
        cout << "\n========== DAFTAR KURSUS ==========" << endl;
        while (P != NULL) {
            cout << no << ". " << P->info.judul << endl;
            cout << "   Kode   : " << P->info.kode << endl;
            cout << "   Level  : " << P->info.level << endl;
            cout << "   Durasi : " << P->info.durasi << " jam" << endl;
            cout << "   Modul  : " << countModul(P) << " modul" << endl;
            cout << "-----------------------------------" << endl;
            P = P->next;
            no++;
        }
    }
}

int countKursus(listKursus L) {
    /* Mengembalikan jumlah elemen dalam list kursus */
    int count = 0;
    adrKursus P = L.first;
    while (P != NULL) {
        count++;
        P = P->next;
    }
    return count;
}

adrModul alokasiModul(modul x) {
    /* Mengembalikan address hasil alokasi elemen modul
       Jika alokasi berhasil, maka address != NULL */
    adrModul M = new elemenModul;
    M->info = x;
    M->next = NULL;
    M->prev = NULL;
    return M;
}

void dealokasiModul(adrModul &M) {
    /* I.S. M terdefinisi
       F.S. memori yang digunakan M dikembalikan ke sistem */
    delete M;
    M = NULL;
}

void insertFirstModul(adrKursus P, adrModul M) {
    /* I.S. P terdefinisi, M sudah dialokasi
       F.S. M menjadi modul pertama pada kursus P */
    if (P != NULL && M != NULL) {
        if (P->firstModul == NULL) {
            P->firstModul = M;
        } else {
            M->next = P->firstModul;
            P->firstModul->prev = M;
            P->firstModul = M;
        }
    }
}

void insertLastModul(adrKursus P, adrModul M) {
    /* I.S. P terdefinisi, M sudah dialokasi
       F.S. M menjadi modul terakhir pada kursus P */
    if (P != NULL && M != NULL) {
        if (P->firstModul == NULL) {
            P->firstModul = M;
        } else {
            adrModul temp = P->firstModul;
            while (temp->next != NULL) {
                temp = temp->next;
            }
            temp->next = M;
            M->prev = temp;
        }
    }
}

void insertAfterModul(adrKursus P, adrModul Prec, adrModul M) {
    /* I.S. P, Prec, dan M terdefinisi
       F.S. M menjadi modul setelah Prec pada kursus P */
    if (P != NULL && Prec != NULL && M != NULL) {
        M->next = Prec->next;
        M->prev = Prec;
        if (Prec->next != NULL) {
            Prec->next->prev = M;
        }
        Prec->next = M;
    }
}

void deleteFirstModul(adrKursus P, adrModul &M) {
    /* I.S. P terdefinisi dan memiliki minimal 1 modul
       F.S. modul pertama pada kursus P dihapus dan disimpan di M */
    if (P != NULL && P->firstModul != NULL) {
        M = P->firstModul;
        if (M->next == NULL) {
            P->firstModul = NULL;
        } else {
            P->firstModul = M->next;
            P->firstModul->prev = NULL;
            M->next = NULL;
        }
    }
}

void deleteLastModul(adrKursus P, adrModul &M) {
    /* I.S. P terdefinisi dan memiliki minimal 1 modul
       F.S. modul terakhir pada kursus P dihapus dan disimpan di M */
    if (P != NULL && P->firstModul != NULL) {
        if (P->firstModul->next == NULL) {
            M = P->firstModul;
            P->firstModul = NULL;
        } else {
            adrModul temp = P->firstModul;
            while (temp->next != NULL) {
                temp = temp->next;
            }
            M = temp;
            temp->prev->next = NULL;
            M->prev = NULL;
        }
    }
}

void deleteAfterModul(adrKursus P, adrModul Prec, adrModul &M) {
    /* I.S. P dan Prec terdefinisi, Prec bukan modul terakhir
       F.S. modul setelah Prec dihapus dan disimpan di M */
    if (P != NULL && Prec != NULL && Prec->next != NULL) {
        M = Prec->next;
        Prec->next = M->next;
        if (M->next != NULL) {
            M->next->prev = Prec;
        }
        M->next = NULL;
        M->prev = NULL;
    }
}

adrModul findModul(adrKursus P, string nama) {
    /* Mengembalikan address modul dengan nama tertentu pada kursus P
       Mengembalikan NULL jika tidak ditemukan */
    if (P == NULL) {
        return NULL;
    }
    adrModul M = P->firstModul;
    while (M != NULL) {
        if (M->info.nama == nama) {
            return M;
        }
        M = M->next;
    }
    return NULL;
}

void showAllModul(adrKursus P) {
    /* I.S. P terdefinisi
       F.S. menampilkan semua modul pada kursus P */
    if (P == NULL) {
        cout << "Kursus tidak ditemukan" << endl;
        return;
    }

    if (P->firstModul == NULL) {
        cout << "   Belum ada modul" << endl;
    } else {
        adrModul M = P->firstModul;
        int no = 1;
        while (M != NULL) {
            cout << "   " << no << ". " << M->info.nama << endl;
            M = M->next;
            no++;
        }
    }
}

int countModul(adrKursus P) {
    /* Mengembalikan jumlah modul pada kursus P */
    if (P == NULL) {
        return 0;
    }
    int count = 0;
    adrModul M = P->firstModul;
    while (M != NULL) {
        count++;
        M = M->next;
    }
    return count;
}

// ========== IMPLEMENTASI FUNGSI RELASI ==========

void connectModulToKursus(adrKursus K, modul dataModul) {
    /* I.S. K terdefinisi
       F.S. modul baru dengan data dataModul ditambahkan ke kursus K */
    if (K != NULL) {
        adrModul M = alokasiModul(dataModul);
        insertLastModul(K, M);
    }
}

void disconnectModulFromKursus(adrKursus K, string namaModul) {
    /* I.S. K terdefinisi
       F.S. modul dengan nama namaModul dihapus dari kursus K */
    if (K == NULL || K->firstModul == NULL) {
        return;
    }

    adrModul M = findModul(K, namaModul);
    if (M == NULL) {
        cout << "Modul tidak ditemukan" << endl;
        return;
    }

    if (M == K->firstModul) {
        deleteFirstModul(K, M);
    } else if (M->next == NULL) {
        deleteLastModul(K, M);
    } else {
        M->prev->next = M->next;
        M->next->prev = M->prev;
        M->next = NULL;
        M->prev = NULL;
    }
    dealokasiModul(M);
}

void showKursusWithModul(listKursus L) {
    /* I.S. L mungkin kosong
       F.S. menampilkan semua kursus beserta modulnya */
    if (L.first == NULL) {
        cout << "List kursus kosong" << endl;
    } else {
        adrKursus P = L.first;
        int no = 1;
        cout << "\n===== KURSUS DAN MODULNYA =====" << endl;
        while (P != NULL) {
            cout << no << ". " << P->info.judul;
            cout << " (" << P->info.kode << ")" << endl;
            cout << "   Level  : " << P->info.level << endl;
            cout << "   Durasi : " << P->info.durasi << " jam" << endl;
            cout << "   Modul  :" << endl;
            showAllModul(P);
            cout << "   Total  : " << countModul(P) << " modul" << endl;
            cout << "===============================" << endl;
            P = P->next;
            no++;
        }
    }
}

// ========== IMPLEMENTASI FUNGSI PENGOLAHAN DATA ==========

adrKursus findKursusMaxModul(listKursus L) {
    /* Mengembalikan address kursus dengan jumlah modul terbanyak */
    if (L.first == NULL) {
        return NULL;
    }

    adrKursus P = L.first;
    adrKursus maxP = P;
    int maxCount = countModul(P);

    while (P != NULL) {
        int count = countModul(P);
        if (count > maxCount) {
            maxCount = count;
            maxP = P;
        }
        P = P->next;
    }
    return maxP;
}

adrKursus findKursusMinModul(listKursus L) {
    /* Mengembalikan address kursus dengan jumlah modul paling sedikit */
    if (L.first == NULL) {
        return NULL;
    }

    adrKursus P = L.first;
    adrKursus minP = P;
    int minCount = countModul(P);

    while (P != NULL) {
        int count = countModul(P);
        if (count < minCount) {
            minCount = count;
            minP = P;
        }
        P = P->next;
    }
    return minP;
}

int countKursusByLevel(listKursus L, string level) {
    /* Mengembalikan jumlah kursus dengan level tertentu */
    int count = 0;
    adrKursus P = L.first;
    while (P != NULL) {
        if (P->info.level == level) {
            count++;
        }
        P = P->next;
    }
    return count;
}

int countKursusByDuration(listKursus L, int minDur, int maxDur) {
    /* Mengembalikan jumlah kursus dalam rentang durasi tertentu */
    int count = 0;
    adrKursus P = L.first;
    while (P != NULL) {
        if (P->info.durasi >= minDur && P->info.durasi <= maxDur) {
            count++;
        }
        P = P->next;
    }
    return count;
}

void searchKursusByLevel(listKursus L, string level) {
    /* I.S. L mungkin kosong
       F.S. menampilkan semua kursus dengan level tertentu */
    adrKursus P = L.first;
    bool found = false;
    int no = 1;

    cout << "\nKursus dengan level " << level << ":" << endl;
    cout << "====================================" << endl;

    while (P != NULL) {
        if (P->info.level == level) {
            cout << no << ". " << P->info.judul;
            cout << " (" << P->info.kode << ")";
            cout << " - " << P->info.durasi << " jam";
            cout << " - " << countModul(P) << " modul" << endl;
            found = true;
            no++;
        }
        P = P->next;
    }

    if (found == false) {
        cout << "Tidak ada kursus dengan level tersebut" << endl;
    }
}

void deleteAllModulFromKursus(adrKursus K) {
    /* I.S. K terdefinisi
       F.S. semua modul pada kursus K dihapus */
    if (K == NULL) {
        return;
    }

    adrModul M;
    while (K->firstModul != NULL) {
        deleteFirstModul(K, M);
        dealokasiModul(M);
    }
}

void deleteKursusWithModul(listKursus &L, string kode) {
    /* I.S. L mungkin kosong
       F.S. kursus dengan kode tertentu beserta semua modulnya dihapus */
    adrKursus P = findKursus(L, kode);

    if (P == NULL) {
        cout << "Kursus tidak ditemukan" << endl;
        return;
    }

    // Hapus semua modul dari kursus
    deleteAllModulFromKursus(P);

    // Hapus kursus dari list
    if (P == L.first && P == L.last) {
        L.first = NULL;
        L.last = NULL;
    } else if (P == L.first) {
        deleteFirstKursus(L, P);
    } else if (P == L.last) {
        deleteLastKursus(L, P);
    } else {
        P->prev->next = P->next;
        P->next->prev = P->prev;
        P->next = NULL;
        P->prev = NULL;
    }

    dealokasiKursus(P);
    cout << "Kursus dan semua modulnya berhasil dihapus" << endl;
}

float averageDurasiKursus(listKursus L) {
    /* Mengembalikan rata-rata durasi semua kursus */
    if (L.first == NULL) {
        return 0;
    }

    int totalDurasi = 0;
    int jumlahKursus = 0;
    adrKursus P = L.first;

    while (P != NULL) {
        totalDurasi = totalDurasi + P->info.durasi;
        jumlahKursus++;
        P = P->next;
    }

    return (float)totalDurasi / jumlahKursus;
}
