#include "post.h"

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("sposob uzycia: %s baza.txt\n", argv[0]);
        return 1;
    }

    struct Post *baza = (struct Post*)malloc(100 * sizeof(struct Post));
    if (baza == NULL) return 1;

    int liczbaPostow = 0;
    int wybor;

    wczytajzPliku(baza, &liczbaPostow, argv[1]);


    do {
        printf("\n1. Wyswietl\n2. Moderuj\n3. Sortuj\n4. Szukaj\n5. Usun\n6. Raport\n0. Wyjdz\nWybor: ");
        scanf("%d", &wybor);

        switch (wybor) {
            case 1: wyswietlBaze(baza, liczbaPostow); break;
            case 2: moderacja(baza, liczbaPostow); break;
            case 3: sortowanie(baza, liczbaPostow); break;
            case 4: szukajPost(baza, &liczbaPostow); break;
            case 5: usunPost(baza, &liczbaPostow); break;
            case 6: zapiszPlik(baza, liczbaPostow); break;
        }
    } while (wybor != 0);

    free(baza);
    return 0;
}