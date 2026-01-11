#ifndef POST_H
#define POST_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Post {
    int id;
    char autor[101];
    char tresc[281];
    char kategoria[101];
    int liczbaZgloszen;
    char status[101];
};

void wczytajzPliku(struct Post t1[], int *licznik, char *nazwaPliku);
void wyswietlBaze(struct Post t1[], int licznik);
void moderacja(struct Post t1[], int licznik);
void sortowanie(struct Post t1[], int licznik);
void zapiszPlik(struct Post t1[], int licznik);
void usunPost(struct Post t1[], int *licznik);
void szukajPost(struct Post t1[], int *licznik);

#endif