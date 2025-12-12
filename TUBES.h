#ifndef TUBES_H_INCLUDED
#define TUBES_H_INCLUDED
#include <iostream>

using namespace std;

typedef struct elemenKursus *adrKursus;
typedef struct elemenModul *adrModul;

struct kursus {
    string kode;
    string judul;
    string level;
    int durasi;
};

struct modul {
    string nama;
};

struct elemenKursus {
    kursus info;
    adrKursus next;
    adrKursus prev;
    adrModul firstModul;
};

struct elemenModul {
    modul info;
    adrModul next;
    adrModul prev;
};

struct listKursus {
    adrKursus first;
    adrKursus last;
};


void createListKursus(listKursus &L);
adrKursus alokasiKursus(kursus x);
void dealokasiKursus(adrKursus &P);
void insertFirstKursus(listKursus &L, adrKursus P);
void insertLastKursus(listKursus &L, adrKursus P);
void insertAfterKursus(listKursus &L, adrKursus Prec, adrKursus P);
void deleteFirstKursus(listKursus &L, adrKursus &P);
void deleteLastKursus(listKursus &L, adrKursus &P);
void deleteAfterKursus(listKursus &L, adrKursus Prec, adrKursus &P);
adrKursus findKursus(listKursus L, string kode);
void showAllKursus(listKursus L);
int countKursus(listKursus L);
adrModul alokasiModul(modul x);
void dealokasiModul(adrModul &P);
void insertFirstModul(adrKursus P, adrModul M);
void insertLastModul(adrKursus P, adrModul M);
void insertAfterModul(adrKursus P, adrModul Prec, adrModul M);
void deleteFirstModul(adrKursus P, adrModul &M);
void deleteLastModul(adrKursus P, adrModul &M);
void deleteAfterModul(adrKursus P, adrModul Prec, adrModul &M);
adrModul findModul(adrKursus P, string nama);
void showAllModul(adrKursus P);
int countModul(adrKursus P);
void connectModulToKursus(adrKursus K, modul dataModul);
void disconnectModulFromKursus(adrKursus K, string namaModul);
void showKursusWithModul(listKursus L);
adrKursus findKursusMaxModul(listKursus L);
adrKursus findKursusMinModul(listKursus L);
int countKursusByLevel(listKursus L, string level);
int countKursusByDuration(listKursus L, int minDur, int maxDur);
void searchKursusByLevel(listKursus L, string level);
void deleteAllModulFromKursus(adrKursus K);
void deleteKursusWithModul(listKursus &L, string kode);
float averageDurasiKursus(listKursus L);

#endif // TUBES_H_INCLUDED
