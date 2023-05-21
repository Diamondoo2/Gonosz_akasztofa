#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <time.h>
#include "fuggvenyek.h"
#include "beolvas.h"
#include "betut_beir.h"
#include "econio.h"

#include "debugmalloc.h"

int main(void)
{
    srand(time(0));
    system("title Gonosz akasztofa"); // a megjeleno ablak elnevezese
    int kilep = 0;
    adat_elem *szotar = NULL;
    int leghosszabb_szo_karakter_szama = 0, tippek_szama;
    unsigned long szavak_szama = 0;
    while (kilep != 1)
    {
        econio_clrscr();
        beolvas(&szotar, &szavak_szama, &leghosszabb_szo_karakter_szama);
        int kitalalando_szo_hossza = rand() % leghosszabb_szo_karakter_szama + 1;
       //kitalalando_szo_hossza = 1; //teszteles celjabol
        long megfelelo_szavak_szama = 0;
        kivalogat(&szotar, szavak_szama, &megfelelo_szavak_szama, kitalalando_szo_hossza);
        nehezseg(&tippek_szama);
        char nem_talalt_tippek[26];
        int nem_talalt_tippek_szama = 0;
        char talalt_tippek[26];
        for (int i = 0; i < 26; i++)
        {
            talalt_tippek[i] = '_';
            nem_talalt_tippek[i] = '_';
        }
        char kitalalando_szo[61];
        int kitalalt_betuk_szama = 0;
        int jatek_vege = 0;
        tippeles(szotar, megfelelo_szavak_szama, kitalalando_szo_hossza, &tippek_szama, &kilep, nem_talalt_tippek, kitalalando_szo, &kitalalt_betuk_szama, &jatek_vege, talalt_tippek, &nem_talalt_tippek_szama);
    }
    return 0;
}
