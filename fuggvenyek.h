#ifndef FUGGVENYEK_H
#define FUGGVENYEK_H

typedef struct adat_elem
{
    char* szo;
    int hossza; //a szo hossza
    int szoban_elofordulo_betu_szama; //a tippelt betu hányszor szerepel a szoban
} adat_elem;

char *dintomb_atmeretez(char *tomb, int ujmeret);
char *hosszu_sort_olvas(void);
int beker(void);
int beker_vege(void);
void kivalogat(adat_elem **szotar, unsigned long szavak_szama, long *megfelelo_szavak_szama, int kitalalando_szo_hossza);
void uj_jatek(int *kilep);
void nehezseg(int *tippek_szama);
void felad(adat_elem *szotar, int megfelelo_szavak_szama, int *kilep, int jatek_vege);
void tippeles(adat_elem *szotar, long megfelelo_szavak_szama, int kitalalando_szo_hossza, int *tippek_szama, int *kilep, char *nem_talalt_tippek, char *kitalalando_szo, int *kitalalt_betuk_szama, int *jatek_vege, char *talalt_tippek, int *nem_talalt_tippek_szama);

#endif
