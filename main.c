#include "post.h"

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Sposob uzycia: %s <plik_bazy_wejsciowy> [plik_do_zapisu]\n", argv[0]);
        return 1;
    }

    char *plikOdczytu = argv[1];
    char *plikZapisu = (argc >= 3) ? argv[2] : "raport.txt";
    struct Post *baza = NULL;
    wczytajzPliku(&baza, plikOdczytu);

    int wybor;
    do {
        printf("\n--- MENU GLOWNE ---\n");
        printf("1. Wyswietl baze\n");
        printf("2. Moderuj (weryfikacja postow)\n");
        printf("3. Sortuj (wg liczby zgloszen)\n");
        printf("4. Szukaj (wg autora - fragment)\n");
        printf("5. Usun post (wg ID)\n");
        printf("6. Zapisz do pliku\n");
        printf("0. Wyjdz\n");
        printf("Wybor: ");

        if (scanf("%d", &wybor) != 1) {
            while(getchar() != '\n');
            wybor = -1;
        }

        switch (wybor) {
            case 1: 
                wyswietlBaze(baza); 
                break;
            case 2: 
                moderacja(baza); 
                break;
            case 3: 
                sortujPostyZgloszenia(baza); 
                wyswietlBaze(baza);
                break;
            case 4: 
                szukajPostAutor(baza); 
                break;
            case 5: 
                usunPost(&baza); 
                break;
            case 6: 
                zapiszDoPliku(baza, plikZapisu); 
                break;
            case 0:
                printf("Konczenie programu...\n");
                break;
            default:
                printf("Niepoprawny wybor.\n");
        }
    } while (wybor != 0);

    zwolnijPamiec(&baza);
    return 0;
}