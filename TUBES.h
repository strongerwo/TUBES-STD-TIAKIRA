#ifndef TUBES_H_INCLUDED
#define TUBES_H_INCLUDED
#include <iostream>

using namespace std;

typedef struct elemenKursus *adrKursus;
typedef struct elemenModul *adrModul;

struct kursus{
    string kode;
    string judul;
    string level;
    int durasi;
};

struct modul{
    string nama;
};

struct elemenKursus{
    kursus info;
    adrKursus next;
    adrKursus prev;
    adrModul firstModul;
};

struct elemenModul{
    modul info;
    adrModul next;
    adrModul prev;
};

struct listKursus{
    adrKursus first;
    adrKursus last;
};

void createList(listKursus &L);
adrKursus createElemenKursus(kursus k);
adrModul createElemenModul(modul m);
void insertLastKursus(listKursus &L, adrKursus P);
void insertLastModul(adrKursus K, adrModul M);
adrKursus findKursus(listKursus L, string kode);
void deleteKursus(listKursus &L, string kode);
void tampilModul(adrKursus K);
void tampilKursus(listKursus L);
void cariBerdasarkanLevel(listKursus L, string level);
void cariBerdasarkanJudul(listKursus L, string judul);
void cariDurasiKurang(listKursus L, int maxDurasi);
int hitungPerLevel(listKursus L, string level);
adrKursus kursusModulTerbanyak(listKursus L);




#endif // TUBES_H_INCLUDED
