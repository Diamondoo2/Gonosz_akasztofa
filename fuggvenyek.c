#include "fuggvenyek.h"
#include "betut_beir.h"
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "debugmalloc.h"

/*A beolvasást segíti elo, kap paraméterként egy dinamikus tömböt és egy méretet, majd a tömb hosszát megnöveli egy egységgel. Visszatér az új tömbre mutató pointerrel.*/

char *dintomb_atmeretez(char *tomb, int ujmeret)
{
    char *ujtomb = (char*) malloc((ujmeret) * sizeof(char));
    if (ujtomb == NULL)
    {
        printf("Nem sikerult memoriat foglalni.\n");
        return false;
    }
    for (int i = 0; i < ujmeret - 1; i++)
    {
        ujtomb[i] = tomb[i];
    }
    ujtomb[ujmeret - 1] = '\0';
    free(tomb);
    return ujtomb;
}

/*A bekérésnél van erre a függvényre szükség. Beolvassa azokat a karaktereket, amelyek a bemenetrol érkeznek.*/

char *hosszu_sort_olvas(void)
{
    char *tomb = (char*) malloc((1) * sizeof(char));
    int meret = 1;
    char bekert_karakter;
    scanf("%c", &bekert_karakter);
    while (bekert_karakter != '\n')
    {
        tomb[meret - 1] = bekert_karakter;
        meret++;
        tomb = dintomb_atmeretez(tomb, meret);
        scanf("%c", &bekert_karakter);
    }
    return tomb;
}

/*Nehézség választásnál eldönti, hogy érvényes-e a bemeneten adott érték. */

int beker(void)
{
    int szam;
    bool kilepes = false;
    do
    {
        char *bemenet = hosszu_sort_olvas();
        szam = atoi(bemenet);
        if(szam < 1)
        {
            printf("Ervenytelen bemenet.\nKerem adja meg ujra: ");
            free(bemenet);
        }
        else if(szam >= 1 && szam <= 20)
        {
            kilepes = true;
            free(bemenet);
        }
        else
        {
            free(bemenet);
            printf("Igy mar tul konnyu lenne.\nKerem adja meg ujra: ");
        }
    }
    while (kilepes != true);
    return szam;
}

/*A játék végén el lehet dönteni, hogy újra akarunk-e játszani. Ekkor a függvény vizsgálja a bemenetre adott értéket.*/

int beker_vege()
{
    int szam;
    bool kilepes = false;
    do
    {
        char *bemenet = hosszu_sort_olvas();
        szam = atoi(bemenet);
        if (szam < 1 || szam > 2)
        {
            printf("Ervenytelen bemenet.\nKerem adja meg ujra: ");
            free(bemenet);
        }
        else
        {
            kilepes = true;
            free(bemenet);
        }
    }
    while (kilepes != true);
    return szam;
}

/*A függvény paraméterként var egy adat_elem típusú dinamikus tömböt, a tömb eleminek a számát, egy változót, amelybe majd a kiválogatással maradt szavak számát írja és a kitalálandó szó hosszát.
A kiválogat függvény a randomgenerátor által meghatározott betűszámnak megfelelő szavakat válogatja ki, majd azokat dinamikusan egy új memóriaterületen tárolja el.*/

void kivalogat(adat_elem **szotar, unsigned long szavak_szama, long *megfelelo_szavak_szama, int kitalalando_szo_hossza)
{
    long j = 0;
    for (long i = 0; i < szavak_szama; i++)
    {
        if ((*szotar)[i].hossza == kitalalando_szo_hossza)
        {
            j++;
            (*szotar)[i].szoban_elofordulo_betu_szama = 0;
        }
    }
    adat_elem *megfelelo_szavak = (adat_elem*) malloc(j * sizeof(adat_elem));
    if (megfelelo_szavak == NULL)
    {
        printf("Nem sikerult memoriat foglalni.");
        exit(-1);
    }
    long k = 0;
    for (long i = 0; i < szavak_szama; i++)
    {
        if ((*szotar)[i].hossza == kitalalando_szo_hossza)
        {
            memcpy(megfelelo_szavak + k, (*szotar) + i, sizeof(adat_elem));
            k++;
        }
        else
        {
            free((*szotar)[i].szo);
        }
    }
    free(*szotar);
    *szotar = megfelelo_szavak;
    *megfelelo_szavak_szama = j;
}

/*A függvény paraméterként egy számot vár, amelybe a felhasznaló döntését írja. Az uj_jatek függvény a kilép változó erteke alapján dönt arról, hogy újrakezdődjön-e a játék vagy sem.*/

void uj_jatek(int *kilep)
{
    printf("\nSzeretne ujra jatszani? (nem: 1-es szam / igen: 2-es szam)  ");
    getchar(); //egy K betut beolvas es azt el kell dobni
    *kilep = beker_vege();
    if (*kilep == 2)
    {
        printf("\n\n");
    }
}

/*A függvény paraméterként kapja a játékos által választott tippek számát. A felhasználó tud a játék elején nehézségi szintet választani annak megfeleloen, hogy maximum hányat tudjon tippelni. A függvény a beker függvény segítségével bekéri a tippek számát.*/

void nehezseg(int *tippek_szama)
{
    printf("A mozaik szavak is kis betuvel vannak megadva.\nFeladas: 0 \nJatek vegen kilepes: 1\nJatek vegen uj jatek inditasa: 2\n\nKerem adja meg, hogy maximum hany tippelesi lehetoseggel szeretne jatszani(maximum: 20): ");
    *tippek_szama = beker();
}

/*Feladasnál a felad függvény a lehetséges szavakból kiír egy randomgenerátorral választott szót.*/

void felad(adat_elem *szotar, int megfelelo_szavak_szama, int *kilep, int jatek_vege)
{
    long random = rand() % megfelelo_szavak_szama;
    if (jatek_vege)
    {
        printf("Megoldas: %s\n", szotar[random].szo);
        uj_jatek(kilep);
    }
    else
    {
        printf("Feladta a jatekot.  Megoldas: %s\n", szotar[random].szo);
        uj_jatek(kilep);
    }
}

/*A függvény kezeli a felhasználó által adott tippeket, eldönti, hogy volt-e már, érvényes-e és a tippek száma alapján eldönti, hogy még folytatódhat a játék vagy nyert, esetleg veszített a felhasználó.*/

void tippeles(adat_elem *szotar, long megfelelo_szavak_szama, int kitalalando_szo_hossza, int *tippek_szama, int *kilep, char *nem_talalt_tippek, char *kitalalando_szo, int *kitalalt_betuk_szama, int *jatek_vege, char *talalt_tippek, int *nem_talalt_tippek_szama)
{
    for (int i = 0; i < kitalalando_szo_hossza; i++)
    {
        kitalalando_szo[i] = '_';
    }
    kitalalando_szo[kitalalando_szo_hossza] = '\0';
    /*for (int i = 0; i < 26; i++)
    {
        nem_talalt_tippek[i] = '0';
    }*/
    int tipp;
    printf("A szo: ");
    for (int i = 0; i < kitalalando_szo_hossza; i++)
    {
        printf("_ ");
    }
    printf("\nKerem adjon egy tippet: ");
    int kitalalta = 0;
    while (kitalalta != 1)
    {
        tipp = getchar();
        if(tipp != '\n' && tipp != '\r')
        {
            tipp = tolower(tipp);
            (*tippek_szama)--;
            if (tipp == '0')                        // feladas
            {
                *jatek_vege = 0;
                felad(szotar, megfelelo_szavak_szama, kilep, *jatek_vege);
                for (int i = 0; i <megfelelo_szavak_szama; i++)
                {
                    free(szotar[i].szo);
                }
                free(szotar);
                break;
            }
            else if (tipp < 'a' || tipp > 'z' || tipp == EOF)
            {
                printf("Ervenytelen karakter. Kerem probalja ujra: ");
                (*tippek_szama)++;
            }
            else
            {
                int mar_volt = 0;
                for (int i = 0; i < *nem_talalt_tippek_szama; i++)
                {
                    if (tipp == nem_talalt_tippek[i])
                    {
                        mar_volt = 1;
                    }
                }
                for (int i = 0; i <= *kitalalt_betuk_szama; i++)
                {
                    if (tipp == talalt_tippek[i])
                    {
                        mar_volt = 1;
                    }
                }
                if (mar_volt)
                {
                    printf("Ez a betu mar volt.\n\n");
                    (*tippek_szama)++;
                }
                else
                {
                    betuket_beir(&szotar, &megfelelo_szavak_szama, tipp, nem_talalt_tippek, kitalalando_szo_hossza, kitalalt_betuk_szama, kitalalando_szo, &*tippek_szama, talalt_tippek, nem_talalt_tippek_szama);
                }
                if (*tippek_szama >= 0)
                {
                    int l = 0;
                    for (int k = 0; k < kitalalando_szo_hossza; k++)
                    {
                        if (kitalalando_szo[k] != '_')
                        {
                            l++;
                        }
                    }
                    if (l == kitalalando_szo_hossza)
                    {
                        kitalalta = 1;
                    }
                    if (*tippek_szama > 0 && kitalalta == 0)
                    {
                        printf("Tippek szama: %d", *tippek_szama);
                        printf("\n\nKerem adjon egy tippet: ");
                    }
                }
            }
            if ((*tippek_szama) == 0 && kitalalta == 0)
            {
                printf("Vesztett. Elfogytak a tippelesi lehetosegek.\n");
                *jatek_vege = 1;
                felad(szotar, megfelelo_szavak_szama, kilep, *jatek_vege);
                for (int i = 0; i <megfelelo_szavak_szama; i++)
                {
                    free(szotar[i].szo);
                }
                free(szotar);
                break;
            }
        }
    }
    if (kitalalta)
    {
        printf("Gratulalok, On kitalalta a szot es nyert.\n\n");
        uj_jatek(kilep);
        for (int i = 0; i <megfelelo_szavak_szama; i++)
        {
            free(szotar[i].szo);
        }
        free(szotar);
    }
}
