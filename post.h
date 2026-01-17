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
    struct Post *next;
};

void wczytajzPliku(struct Post **head, char *nazwaPliku);
void zapiszDoPliku(struct Post *head, char *nazwaPliku);
void zwolnijPamiec(struct Post **head);
void dodajElementListy(struct Post **head, int id, char *autor, char *tresc, char *kat, int zgloszenia, char *status);
void wyswietlBaze(struct Post *head);
void dodajNowyPost(struct Post **head);
void usunPost(struct Post **head);
void edytujPost(struct Post *head);
void moderacja(struct Post *head);
void szukajPostAutor(struct Post *head);
void szukajPostZgloszenia(struct Post *head);
void sortujPostyAutor(struct Post *head);
void sortujPostyZgloszenia(struct Post *head);

#endif