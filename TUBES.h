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




#endif // TUBES_H_INCLUDED
