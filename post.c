#include "post.h"

void dodajElementListy(struct Post **head, int id, char *autor, char *tresc, char *kat, int zgloszenia, char *status) {
    struct Post *nowy = (struct Post*)malloc(sizeof(struct Post));
    if (nowy == NULL) return;
    nowy->id = id;
    strcpy(nowy->autor, autor);
    strcpy(nowy->tresc, tresc);
    strcpy(nowy->kategoria, kat);
    nowy->liczbaZgloszen = zgloszenia;
    strcpy(nowy->status, status);
    nowy->next = NULL;

    if (*head == NULL) {
        *head = nowy;
    } else {
        struct Post *temp = *head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = nowy;
    }
}

void zwolnijPamiec(struct Post **head) {
    struct Post *current = *head;
    struct Post *next;
    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }
    *head = NULL;
}

void wczytajzPliku(struct Post **head, char *nazwaPliku) {
    FILE *plik = fopen(nazwaPliku, "r");
    if (!plik) {
        printf("Nie mozna otworzyc pliku lub plik nie istnieje.\n");
        return;
    }

    int id, zgloszenia;
    char autor[101], tresc[281], kat[101], status[101];
    int licznik = 0;

    while (fscanf(plik, "%d;%[^;];%[^;];%[^;];%d;%[^\n]\n", &id, autor, tresc, kat, &zgloszenia, status) != EOF) {
        dodajElementListy(head, id, autor, tresc, kat, zgloszenia, status);
        licznik++;
    }
    fclose(plik);
    printf("Wczytano %d postow do listy dynamicznej.\n", licznik);
}

void wyswietlBaze(struct Post *head) {
    if (head == NULL) {
        printf("\nBaza jest pusta\n");
        return;
    }
    printf("\n%-4s | %-15s | %-30s | %-15s | %-3s | %-15s\n", "ID", "AUTOR", "TRESC", "KATEGORIA", "LICZBAZGLOSZEN", "STATUS");
    printf("--------------------------------------------------------------------------------------------------\n");

    struct Post *current = head;
    while (current != NULL) {
        printf("%-4d | %-15s | %-30.30s | %-15s | %-3d | %-15s\n", current->id, current->autor, current->tresc, current->kategoria, current->liczbaZgloszen, current->status); current = current->next;
    }
}

void moderacja(struct Post *head) {
    int znalezionyPost = 0;
    struct Post *current = head;

    while (current != NULL) {
        if (strcmp(current->status, "do weryfikacji") == 0) {
            znalezionyPost = 1;
            printf("\nid: %d, autor: %s\n", current->id, current->autor);
            printf("tresc: %s\n", current->tresc);
            printf("powod zgloszenia: `%s`, ilosc zgloszen %d\n", current->kategoria, current->liczbaZgloszen);
            printf("1 - zostaw post, 2 - usun post\n");
            
            int potwierdzenie;
            scanf("%d", &potwierdzenie);
            if (potwierdzenie == 1) {
                strcpy(current->status, "zatwierdzony");
                printf("post zatwierdzony\n");
            } else if (potwierdzenie == 2) {
                strcpy(current->status, "usuniety");
                printf("post oznaczony jako usuniety\n");
            }
        }
        current = current->next;
    }

    if (!znalezionyPost) {
        printf("brak postow do weryfikacji\n");
    }
}

void sortujPostyZgloszenia(struct Post *head) {
    if (head == NULL) return;

    int zamiana;
    struct Post *ptr1;
    struct Post *lptr = NULL;

    int tempId, tempZgl;
    char tempAutor[101], tempTresc[281], tempKat[101], tempStatus[101];

    do {
        zamiana = 0;
        ptr1 = head;

        while (ptr1->next != lptr) {
            if (ptr1->liczbaZgloszen < ptr1->next->liczbaZgloszen) { 
                tempId = ptr1->id;
                ptr1->id = ptr1->next->id;
                ptr1->next->id = tempId;
                tempZgl = ptr1->liczbaZgloszen;
                ptr1->liczbaZgloszen = ptr1->next->liczbaZgloszen;
                ptr1->next->liczbaZgloszen = tempZgl;

                strcpy(tempAutor, ptr1->autor);
                strcpy(ptr1->autor, ptr1->next->autor);
                strcpy(ptr1->next->autor, tempAutor);
                strcpy(tempTresc, ptr1->tresc);
                strcpy(ptr1->tresc, ptr1->next->tresc);
                strcpy(ptr1->next->tresc, tempTresc);
                strcpy(tempKat, ptr1->kategoria);
                strcpy(ptr1->kategoria, ptr1->next->kategoria);
                strcpy(ptr1->next->kategoria, tempKat);
                strcpy(tempStatus, ptr1->status);
                strcpy(ptr1->status, ptr1->next->status);
                strcpy(ptr1->next->status, tempStatus);

                zamiana = 1;
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1;
    } while (zamiana);
    
    printf("\nPosortowano baze wg liczby zgloszen.\n");
}

void zapiszDoPliku(struct Post *head, char *nazwaPliku) {
    FILE *plik = fopen(nazwaPliku, "w");
    if (!plik) {
        printf("Blad zapisu do pliku!\n");
        return;
    }

    struct Post *current = head;
    while (current != NULL) {
        fprintf(plik, "%d;%s;%s;%s;%d;%s\n", current->id, current->autor, current->tresc, current->kategoria, current->liczbaZgloszen, current->status); current = current->next;
    }
    fclose(plik);
    printf("\nZapisano dane do pliku %s\n", nazwaPliku);
}

void usunPost(struct Post **head) {
    int id;
    printf("\nID postu do usuniecia: ");
    scanf("%d", &id);

    struct Post *temp = *head;
    struct Post *prev = NULL;

    if (temp != NULL && temp->id == id) {
        if (strcmp(temp->status, "do weryfikacji") == 0) {
            printf("Nie mozna usunac postu do weryfikacji!\n");
            return;
        }
        *head = temp->next;
        free(temp);
        printf("Post ID %d usuniety.\n", id);
        return;
    }

    while (temp != NULL && temp->id != id) {
        prev = temp;
        temp = temp->next;
    }

    if (temp == NULL) {
        printf("Nie znaleziono postu o ID %d.\n", id);
        return;
    }

    if (strcmp(temp->status, "do weryfikacji") == 0) {
        printf("Nie mozna usunac postu do weryfikacji!\n");
        return;
    }

    prev->next = temp->next;
    free(temp);
    printf("Post ID %d usuniety.\n", id);
}

void szukajPostAutor(struct Post *head) {
    char autor[101];
    printf("\nAutor do wyszukania (poczatek nazwy): ");
    scanf("%100s", autor);

    int znaleziony = 0;
    struct Post *current = head;

    while (current != NULL) {
        if (strstr(current->autor, autor) != NULL) {
            printf("ID: %d,  autor: %s,  tresc: %.50s...,  status: %s\n", 
                   current->id, current->autor, current->tresc, current->status);
            znaleziony = 1;
        }
        current = current->next;
    }
    if (!znaleziony) printf("Brak postow spelniajacych kryteria.\n");
}

void edytujPost(struct Post *head) {
    int id;
    printf("Podaj ID postu do edycji: ");
    if (scanf("%d", &id) != 1) {
        while(getchar() != '\n');
        return;
    }

    struct Post *current = head;
    int znaleziono = 0;
    while (current != NULL) {
        if (current->id == id) {
            znaleziono = 1;
            if (strcmp(current->status, "usuniety") == 0) {
                printf("Post z danym ID jest usuniety. Nie mozna go zedytowac.");
                return;
            }

            printf("\nEdycja postu ID: %d\n", current->id);
            printf("Obecna tresc: %s\n", current->tresc);
            printf("Obecna kategoria: %s\n", current->kategoria);
            printf("Wpisz nowa tresc: ");
            char tresc1[281];
            while(getchar() != '\n');
            scanf("%[^\n]", tresc1);
            if(strlen(tresc1) > 0) {
                strcpy(current->tresc, tresc1);
            }
            printf("Wpisz nowa kategorie: ");
            while(getchar() != '\n');
            tresc1[0] = '\0';
            scanf("%[^\n]", tresc1);
            if (strlen(tresc1) > 0) {
                strcpy(current->kategoria, tresc1);
            }
            strcpy(current->status, "do weryfikacji");
            printf("Post zaktualizowany i przeslany do weryfikacji.\n");
            break;
        }
        current = current->next;
    }
    if (!znaleziono) {
        printf("Nie znaleziono postu o ID %d\n", id);
    }
}