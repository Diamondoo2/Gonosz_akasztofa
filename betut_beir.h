#ifndef BETUT_BEIR_H
#define BETUT_BEIR_H

#include "fuggvenyek.h"

void nincs_benne(adat_elem **szotar, long *megfelelo_szavak_szama, char *nem_talalt_tippek, int *nem_talalt_tippek_szama, char betu, int legkevesebb_betut_tartalmazo_szavak_szama, int legkevesebb_betu, int kitalalando_szo_hossza, char *kitalalando_szo);
void egyszer_fordul_elo(adat_elem **szotar, long *megfelelo_szavak_szama, char *nem_talalt_tippek, int *nem_talalt_tippek_szama, char betu, int legkevesebb_betu, char *kitalalando_szo,
                            char *talalt_tippek, int *kitalalt_betuk_szama, int kitalalando_szo_hossza);
void tobbszor_fordul_elo(adat_elem **szotar, long *megfelelo_szavak_szama, char *nem_talalt_tippek, int *nem_talalt_tippek_szama, char betu, char *kitalalando_szo,
                            char *talalt_tippek, int *kitalalt_betuk_szama, int kitalalando_szo_hossza, int legkevesebb_betu);
void betuket_beir(adat_elem **szotar, long *megfelelo_szavak_szama, char betu, char *nem_talalt_tippek, int kitalalando_szo_hossza, int *kitalalt_betuk_szama, char *kitalalando_szo,
                            int *tippek_szama, char *talalt_tippek, int *nem_talalt_tippek_szama);

#endif
