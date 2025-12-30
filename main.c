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

void wyswietlPosty(struct Post t1[], int rozmiar) {
    for (int i = 0; i < rozmiar; i++) {
        printf("id - %d\nautor - %s\n\n\n", t1[i].id, t1[i].autor);
    }
}

void wczytajzPliku(struct Post t1[], int *licznik) {
    FILE *plik = fopen("baza.txt", "r");
    *licznik = 0;
    while (fscanf(plik, "%d;%[^;];%[^;];%[^;];%d;%[^\n]\n", &t1[*licznik].id, t1[*licznik].autor, t1[*licznik].tresc, t1[*licznik].kategoria, &t1[*licznik].liczbaZgloszen, t1[*licznik].status) != EOF) {
        (*licznik)++;
        if (*licznik >= 100) break;
    }
    fclose(plik);
    printf("Wczytano %d postow", *licznik);
}

void wyswietlBaze(struct Post t1[], int licznik) {
    if (licznik == 0) {
        printf("\nBaza jest pusta\n");
        return;
    }
    printf("\n%-4s | %-15s | %-30s | %-15s | %-3s | %-15s\n", "ID", "AUTOR", "TRESC", "KATEGORIA", "LICZBAZGLOSZEN", "STATUS");
    
    for (int i = 0; i < licznik; i++) {
        printf("%-4d | %-15s | %-30.30s | %-15s | %-3d | %-15s\n", t1[i].id, t1[i].autor, t1[i].tresc, t1[i].kategoria, t1[i].liczbaZgloszen, t1[i].status);
    }
}

void moderacja(struct Post t1[], int licznik) {
    int znalezionyPost = 0;
    for (int i = 0; i < licznik; i++) {
        if (strcmp(t1[i].status, "do weryfikacji") == 0) {
            znalezionyPost = 1;
            printf("\nid: %d, autor: %s\n", t1[i].id, t1[i].autor);
            printf("tresc: %s\n", t1[i].tresc);
            printf("powod zgloszenia: `%s`, ilosc zgloszen %d\n", t1[i].kategoria, t1[i].liczbaZgloszen);
            printf("1 - zostaw post, 2 - usun post\n");
            int potwierdzenie;
            scanf("%d", &potwierdzenie);
            if (potwierdzenie == 1) {
                strcpy(t1[i].status, "zatwierdzony");
                printf("post zatwierdzony\n");
            } else if (potwierdzenie == 2) {
                strcpy(t1[i].status, "usuniety");
                printf("post usuniety\n");
            }
        }
    }
    if (!znalezionyPost) {
        printf("brak znalezionych postow\n");
    }
}

int main() {
    struct Post baza[100];
    int liczbaPostow = 0;
    wczytajzPliku(baza, &liczbaPostow);
    wyswietlBaze(baza, liczbaPostow);
    moderacja(baza, liczbaPostow);
    return 0;
}