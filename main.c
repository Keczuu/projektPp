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

int main() {
    struct Post baza[100];
    int liczbaPostow = 0;
    return 0;
}