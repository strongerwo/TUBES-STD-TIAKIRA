#ifndef TUBES_H_INCLUDED
#define TUBES_H_INCLUDED

#include <iostream>
#include <string>
#include <fstream>

/*input
3 kursus
- kursus 1 = A1, c++, 1 jam, beginner,
            1 modul ,

    judul baru = c, 2 jam, intermediate
            2 materi = v, w
- kursus 2 = A2, phyton, 2 jam, intermediate,
            2 modul,
            3, 4 materi = v,w,x,y
- kursus 3 = A3, golang, 3 jam, hard,
            4 modul,
            2,4,6 materi =  u,v,w,x,y,z
*/

using namespace std;

const int MAX_MATERI = 10;

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
    string materi[MAX_MATERI];
    int jumlahMateri;
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
void clearList(listKursus &L);
adrKursus createElemenKursus(kursus k);
adrModul createElemenModul(modul m);
void insertLastKursus(listKursus &L, adrKursus P);
void insertLastModul(adrKursus K, adrModul M);
adrKursus findKursus(listKursus L, string kode);
void updateKursus(listKursus &L, string kode, string judulBaru, string levelBaru, int durasiBaru);
void deleteKursus(listKursus &L, string kode);
void tampilModul(adrKursus K);
void tampilKursus(listKursus L);
void cariBerdasarkanLevel(listKursus L, string level);
void cariBerdasarkanJudul(listKursus L, string judul);
void cariDurasiKurang(listKursus L, int maxDurasi);
int hitungPerLevel(listKursus L, string level);
adrKursus kursusModulTerbanyak(listKursus L);
adrKursus kursusModulTersedikit(listKursus L);
void sortKursusByJumlahModul(listKursus &L);

#endif // TUBES_H_INCLUDED
