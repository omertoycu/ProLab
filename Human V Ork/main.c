#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "raylib.h"
#include "include/curl/curl.h"

#undef DrawText
#define GRID_SIZE 20
#define MAX_UNITS_PER_CELL 100
#define CELL_SIZE 45

const char* url_list[] =
{
    "https://yapbenzet.org.tr/1.json",
    "https://yapbenzet.org.tr/2.json",
    "https://yapbenzet.org.tr/3.json",
    "https://yapbenzet.org.tr/4.json",
    "https://yapbenzet.org.tr/5.json",
    "https://yapbenzet.org.tr/6.json",
    "https://yapbenzet.org.tr/7.json",
    "https://yapbenzet.org.tr/8.json",
    "https://yapbenzet.org.tr/9.json",
    "https://yapbenzet.org.tr/10.json"
};

size_t ft_write(void *ptr, size_t size, size_t nmemb, FILE *stream)
{
    return fwrite(ptr, size, nmemb, stream);
}

void dosya_indir(int num)
{
    CURL *curl;
    FILE *file;
    CURLcode res;

    if (num < 1 || num > 10)
	{
        printf("Gecersiz Numara! 1-10 Arasinda Bir Numara Giriniz.\n");
        return;
    }
    const char *url = url_list[num - 1];
    printf("Secilen Senaryoya Ait URL: %s\n", url);

    curl = curl_easy_init();
    if (curl)
	{
        file = fopen("senaryo.json", "wb");
        if (!file)
		{
            perror("Dosya Acilamadi!");
            return;
        }

        curl_easy_setopt(curl, CURLOPT_URL, url);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, ft_write);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, file);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);  // SSL sertifikasını doğrulamayı kapat
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);

        res = curl_easy_perform(curl);

        if (res != CURLE_OK)
		{
            fprintf(stderr, "Dosya Indirilemedi: %s\n", curl_easy_strerror(res));
        }

        fclose(file);
        curl_easy_cleanup(curl);

    }
}

typedef struct {
    int saldiri;
    int savunma;
    int saglik;
    int kritik_sans;
    int sayi;
} Unit;

typedef struct {
    Unit piyadeler;
    Unit okcular;
    Unit suvariler;
    Unit kusatma_makineleri;
} Human_Unit;

typedef struct {
    Unit ork_dovusculeri;
    Unit mizrakcilar;
    Unit varg_binicileri;
    Unit troller;
} Ork_Unit;

typedef struct {
    char bonus_turu[50];
    char aciklama[256];
    int bonus_degeri;
    int sayi;
} Hero;

typedef struct {
    Hero alparslan;
    Hero fsm;
    Hero metehan;
    Hero yss;
    Hero tugrul_bey;
} Human_Hero;

typedef struct {
    Hero goruk;
    Hero thruk;
    Hero vrog;
    Hero ugar;
} Ork_Hero;

typedef struct {
    int etki_degeri;
    char etki_turu[50];
    char aciklama[256];
    int sayi;
} Creature;

typedef struct {
    Creature ejderha;
    Creature agri_dagi;
    Creature tepegoz;
    Creature karakurt;
    Creature samur;
} Human_Creature;

typedef struct {
    Creature troll;
    Creature golge;
    Creature camur;
    Creature ates_iblisi;
    Creature makrog;
    Creature buz_devi;
} Ork_Creature;

typedef struct {
    int deger;
    char aciklama[100];
    int sayi;
} Seviye;

typedef struct {
    Seviye seviye_1;
    Seviye seviye_2;
    Seviye seviye_3;
} Research_Type;

typedef struct {
    Research_Type savunma_ustaligi;
    Research_Type saldiri_gelistirmesi;
    Research_Type elit_egitim;
    Research_Type kusatma_ustaligi;
} Research;

Human_Unit HU;
Ork_Unit OU;
Human_Hero HH;
Ork_Hero OH;
Human_Creature HC;
Ork_Creature OC;
Research_Type RT;
Research HR;
Research OR;


void parse_creature_json(const char *filename, Human_Creature *HC, Ork_Creature *OC)
{
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        printf("Dosya Acilamadi: %s\n", filename);
        return;
    }

    char line[256];
    char etki_str[10];
    while (fgets(line, sizeof(line), file))
    {
        if (strstr(line, "\"Ejderha\"") != NULL)
        {
            fgets(line, sizeof(line), file);
            sscanf(line, " \"etki_degeri\" : \"%[^\"]\",", etki_str);
            HC->ejderha.etki_degeri = atoi(etki_str);
            fgets(line, sizeof(line), file);
            sscanf(line, " \"etki_turu\" : \"%[^\"]\",", &HC->ejderha.etki_turu);
            fgets(line, sizeof(line), file);
            sscanf(line, " \"aciklama\" : \"%[^\"]\",", &HC->ejderha.aciklama);

        }
        if (strstr(line, "\"Agri_Dagi_Devleri\"") != NULL)
        {
            fgets(line, sizeof(line), file);
            sscanf(line, " \"etki_degeri\" : \"%[^\"]\",", etki_str);
            HC->agri_dagi.etki_degeri = atoi(etki_str);
            fgets(line, sizeof(line), file);
            sscanf(line, " \"etki_turu\" : \"%[^\"]\",", &HC->agri_dagi.etki_turu);
            fgets(line, sizeof(line), file);
            sscanf(line, " \"aciklama\" : \"%[^\"]\",", &HC->agri_dagi.aciklama);

        }
        if (strstr(line, "\"Tepegoz\"") != NULL)
        {
            fgets(line, sizeof(line), file);
            sscanf(line, " \"etki_degeri\" : \"%[^\"]\",", etki_str);
            HC->tepegoz.etki_degeri = atoi(etki_str);
            fgets(line, sizeof(line), file);
            sscanf(line, " \"etki_turu\" : \"%[^\"]\",", &HC->tepegoz.etki_turu);
            fgets(line, sizeof(line), file);
            sscanf(line, " \"aciklama\" : \"%[^\"]\",", &HC->tepegoz.aciklama);
            ;
        }
        if (strstr(line, "\"Karakurt\"") != NULL)
        {
            fgets(line, sizeof(line), file);
            sscanf(line, " \"etki_degeri\" : \"%[^\"]\",", etki_str);
            HC->karakurt.etki_degeri = atoi(etki_str);
            fgets(line, sizeof(line), file);
            sscanf(line, " \"etki_turu\" : \"%[^\"]\",", &HC->karakurt.etki_turu);
            fgets(line, sizeof(line), file);
            sscanf(line, " \"aciklama\" : \"%[^\"]\",", &HC->karakurt.aciklama);

        }
        if (strstr(line, "\"Samur\"") != NULL)
        {
            fgets(line, sizeof(line), file);
            sscanf(line, " \"etki_degeri\" : \"%[^\"]\",", etki_str);
            HC->samur.etki_degeri = atoi(etki_str);
            fgets(line, sizeof(line), file);
            sscanf(line, " \"etki_turu\" : \"%[^\"]\",", &HC->samur.etki_turu);
            fgets(line, sizeof(line), file);
            sscanf(line, " \"aciklama\" : \"%[^\"]\",", &HC->samur.aciklama);

        }
        if (strstr(line, "\"Kara_Troll\"") != NULL)
        {
            fgets(line, sizeof(line), file);
            sscanf(line, " \"etki_degeri\" : \"%[^\"]\",", etki_str);
            OC->troll.etki_degeri = atoi(etki_str);
            fgets(line, sizeof(line), file);
            sscanf(line, " \"etki_turu\" : \"%[^\"]\",", &OC->troll.etki_turu);
            fgets(line, sizeof(line), file);
            sscanf(line, " \"aciklama\" : \"%[^\"]\",", &OC->troll.aciklama);

        }
        if (strstr(line, "\"Golge_Kurtlari\"") != NULL)
        {
            fgets(line, sizeof(line), file);
            sscanf(line, " \"etki_degeri\" : \"%[^\"]\",", etki_str);
            OC->golge.etki_degeri = atoi(etki_str);
            fgets(line, sizeof(line), file);
            sscanf(line, " \"etki_turu\" : \"%[^\"]\",", &OC->golge.etki_turu);
            fgets(line, sizeof(line), file);
            sscanf(line, " \"aciklama\" : \"%[^\"]\",", &OC->golge.aciklama);

        }
        if (strstr(line, "\"Camur_Devleri\"") != NULL)
        {
            fgets(line, sizeof(line), file);
            sscanf(line, " \"etki_degeri\" : \"%[^\"]\",", etki_str);
            OC->camur.etki_degeri = atoi(etki_str);
            fgets(line, sizeof(line), file);
            sscanf(line, " \"etki_turu\" : \"%[^\"]\",", &OC->camur.etki_turu);
            fgets(line, sizeof(line), file);
            sscanf(line, " \"aciklama\" : \"%[^\"]\",", &OC->camur.aciklama);

        }
        if (strstr(line, "\"Ates_Iblisi\"") != NULL)
        {
            fgets(line, sizeof(line), file);
            sscanf(line, " \"etki_degeri\" : \"%[^\"]\",", etki_str);
            OC->ates_iblisi.etki_degeri = atoi(etki_str);
            fgets(line, sizeof(line), file);
            sscanf(line, " \"etki_turu\" : \"%[^\"]\",", &OC->ates_iblisi.etki_turu);
            fgets(line, sizeof(line), file);
            sscanf(line, " \"aciklama\" : \"%[^\"]\",", &OC->ates_iblisi.aciklama);

        }
        if (strstr(line, "\"Makrog_Savas_Beyi\"") != NULL)
        {
            fgets(line, sizeof(line), file);
            sscanf(line, " \"etki_degeri\" : \"%[^\"]\",", etki_str);
            OC->makrog.etki_degeri = atoi(etki_str);
            fgets(line, sizeof(line), file);
            sscanf(line, " \"etki_turu\" : \"%[^\"]\",", &OC->makrog.etki_turu);
            fgets(line, sizeof(line), file);
            sscanf(line, " \"aciklama\" : \"%[^\"]\",", &OC->makrog.etki_turu);

        }
        if (strstr(line, "\"Buz_Devleri\"") != NULL)
        {
            fgets(line, sizeof(line), file);
            sscanf(line, " \"etki_degeri\" : \"%[^\"]\",", etki_str);
            OC->buz_devi.etki_degeri = atoi(etki_str);
            fgets(line, sizeof(line), file);
            sscanf(line, " \"etki_turu\" : \"%[^\"]\",", &OC->buz_devi.etki_turu);
            fgets(line, sizeof(line), file);
            sscanf(line, " \"aciklama\" : \"%[^\"]\",", &OC->buz_devi.aciklama);

        }
    }
    fclose(file);
}

void yazdir_human_unit(const char filename, Human_Unit *hu, Human_Creature *HC, Human_Hero *HH, Research *HR) {
    FILE *file = fopen(filename, "a");
    if (file == NULL)
    {
        printf("Dosya Acilamadi: %s\n", filename);
        return;
    }
    fprintf(file, "Insan_Imparatorlugu: \n");
    
    fprintf(file, "Piyadeler - Saldiri: %d, Savunma: %d, Saglik: %d, Kritik Sans: %d, Sayi: %d\n",
            hu->piyadeler.saldiri, hu->piyadeler.savunma, hu->piyadeler.saglik, hu->piyadeler.kritik_sans, hu->piyadeler.sayi);
    fprintf(file, "Okcular - Saldiri: %d, Savunma: %d, Saglik: %d, Kritik Sans: %d, Sayi: %d\n",
            hu->okcular.saldiri, hu->okcular.savunma, hu->okcular.saglik, hu->okcular.kritik_sans, hu->okcular.sayi);
    fprintf(file, "Suvariler - Saldiri: %d, Savunma: %d, Saglik: %d, Kritik Sans: %d, Sayi: %d\n",
            hu->suvariler.saldiri, hu->suvariler.savunma, hu->suvariler.saglik, hu->suvariler.kritik_sans, hu->suvariler.sayi);
    fprintf(file, "Kusatma Makineleri - Saldiri: %d, Savunma: %d, Saglik: %d, Kritik Sans: %d, Sayi: %d\n",
            hu->kusatma_makineleri.saldiri, hu->kusatma_makineleri.savunma, hu->kusatma_makineleri.saglik, hu->kusatma_makineleri.kritik_sans, hu->kusatma_makineleri.sayi);
    
    fprintf(file, "Kahramanlar: \n");
    
    if (HH->alparslan.sayi == 1)
    {
        fprintf(file, "Alparslan\n");
    }

    if (HH->fsm.sayi == 1)
    {
        fprintf(file, "Fatih_Sultan_Mehmet\n");
    }

    if (HH->metehan.sayi == 1)
    {
        fprintf(file, "Mete_Han\n");
    }

    if(HH->yss.sayi == 1)
    {
        fprintf(file, "Yavuz_Sultan_Selim\n");
    }

    if(HH->tugrul_bey.sayi == 1)
    {
        fprintf(file, "Tugrul_Bey\n");
    }
    
    fprintf(file, "Canavarlar: \n");
    
    if(HC->ejderha.sayi == 1)
    {
        fprintf(file, "Ejderha\n");
    }

    if(HC->agri_dagi.sayi == 1)
    {
        fprintf(file, "Agri_Dagi_Devleri\n");
    }

    if(HC->tepegoz.sayi == 1)
    {
        fprintf(file, "Tepegoz\n");

    }

    if(HC->karakurt.sayi == 1)
    {
        fprintf(file, "Karakurt\n");
    }

    if(HC->samur.sayi == 1)
    {
        fprintf(file, "Samur\n");
    }
    
    fprintf(file, "Arastirmalar: \n");
    
    if (HR->savunma_ustaligi.seviye_1.sayi == 1)
    {
        fprintf(file, "Savunma_Ustaligi Seviye_1\n");
    }
    if (HR->savunma_ustaligi.seviye_2.sayi == 1)
    {
        fprintf(file, "Savunma_Ustaligi Seviye_2\n");
    }
    if (HR->savunma_ustaligi.seviye_3.sayi == 1)
    {
        fprintf(file, "Savunma_Ustaligi Seviye_3\n");
    }

    if(HR->saldiri_gelistirmesi.seviye_1.sayi == 1)
    {
        fprintf(file, "Saldiri_Gelistirmesi Seviye_1\n");
    }

    if(HR->saldiri_gelistirmesi.seviye_2.sayi == 1)
    {
        fprintf(file, "Saldiri_Gelistirmesi Seviye_2\n");
    }

    if(HR->saldiri_gelistirmesi.seviye_3.sayi == 1)
    {
        fprintf(file, "Saldiri_Gelistirmesi Seviye_3\n");
    }

    if(HR->elit_egitim.seviye_1.sayi == 1)
    {
        fprintf(file, "Elit_Egitim Seviye_1\n");
    }

    if(HR->elit_egitim.seviye_2.sayi == 1)
    {
        fprintf(file, "Elit_Egitim Seviye_2\n");
    }

    if(HR->elit_egitim.seviye_3.sayi == 1)
    {
        fprintf(file, "Elit_Egitim Seviye_3\n");
    }

    if(HR->kusatma_ustaligi.seviye_1.sayi == 1)
    {
       fprintf(file, "Kusatma_Ustaligi Seviye_1\n");
    }

    if(HR->kusatma_ustaligi.seviye_2.sayi == 1)
    {
       fprintf(file, "Kusatma_Ustaligi Seviye_2\n");
    }

    if(HR->kusatma_ustaligi.seviye_3.sayi == 1)
    {
       fprintf(file, "Kusatma_Ustaligi Seviye_3\n");
    }
    fclose(file);
}

void yazdir_ork_unit(const char filename, Ork_Unit *ou, Ork_Creature *OC, Ork_Hero *OH, Research *OR) {
    FILE *file = fopen(filename, "a");
    if (file == NULL)
    {
        printf("Dosya Acilamadi: %s\n", filename);
        return;
    }
    
    fprintf(file, "Ork_Legi: \n");
    
    fprintf(file, "Ork Dovusculeri - Saldiri: %d, Savunma: %d, Saglik: %d, Kritik Sans: %d, Sayi: %d\n",
            ou->ork_dovusculeri.saldiri, ou->ork_dovusculeri.savunma, ou->ork_dovusculeri.saglik, ou->ork_dovusculeri.kritik_sans, ou->ork_dovusculeri.sayi);
    fprintf(file, "Mizrakcilar - Saldiri: %d, Savunma: %d, Saglik: %d, Kritik Sans: %d, Sayi: %d\n",
            ou->mizrakcilar.saldiri, ou->mizrakcilar.savunma, ou->mizrakcilar.saglik, ou->mizrakcilar.kritik_sans, ou->mizrakcilar.sayi);
    fprintf(file, "Varg Binicileri - Saldiri: %d, Savunma: %d, Saglik: %d, Kritik Sans: %d, Sayi: %d\n",
            ou->varg_binicileri.saldiri, ou->varg_binicileri.savunma, ou->varg_binicileri.saglik, ou->varg_binicileri.kritik_sans, ou->varg_binicileri.sayi);
    fprintf(file, "Troller - Saldiri: %d, Savunma: %d, Saglik: %d, Kritik Sans: %d, Sayi: %d\n",
            ou->troller.saldiri, ou->troller.savunma, ou->troller.saglik, ou->troller.kritik_sans, ou->troller.sayi);
    
    fprintf(file, "Kahramanlar: \n");
    
    if(OH->goruk.sayi == 1)
    {
        fprintf(file, "Goruk_Vahsi\n");
    }

    if(OH->thruk.sayi == 1)
    {
        fprintf(file, "Thruk_Kemikkiran\n");
    }

    if(OH->vrog.sayi == 1)
    {
        fprintf(file, "Vrog_Kafakiran\n");
    }

    if (OH->ugar.sayi == 1)
    {
        fprintf(file, "Ugar_Zalim\n");
    }
    
    fprintf(file, "Canavarlar: \n");
    
    if(OC->troll.sayi == 1)
    {
        fprintf(file, "Kara_Troll\n");
    }

    if(OC->golge.sayi == 1)
    {
        fprintf(file, "Golge_Kurtlari\n");
    }

    if(OC->camur.sayi == 1)
    {
        fprintf(file, "Camur_Devleri\n");
    }

    if(OC->ates_iblisi.sayi == 1)
    {
        fprintf(file, "Ates_Iblisi\n");
    }

    if(OC->makrog.sayi == 1)
    {
        fprintf(file, "Makrog_Savas_Beyi\n");
    }

    if(OC->buz_devi.sayi == 1)
    {
        fprintf(file, "Buz_Devleri\n");
    }
    
    fprintf(file, "Arastirmalar: \n");
    
    if (OR->savunma_ustaligi.seviye_1.sayi == 1)
    {
        fprintf(file, "Savunma_Ustaligi Seviye_1\n");
    }
    if (OR->savunma_ustaligi.seviye_2.sayi == 1)
    {
        fprintf(file, "Savunma_Ustaligi Seviye_2\n");
    }
    if (OR->savunma_ustaligi.seviye_3.sayi == 1)
    {
        fprintf(file, "Savunma_Ustaligi Seviye_3\n");
    }

    if(OR->saldiri_gelistirmesi.seviye_1.sayi == 1)
    {
        fprintf(file, "Saldiri_Gelistirmesi Seviye_1\n");
    }

    if(OR->saldiri_gelistirmesi.seviye_2.sayi == 1)
    {
        fprintf(file, "Saldiri_Gelistirmesi Seviye_2\n");
    }

    if(OR->saldiri_gelistirmesi.seviye_3.sayi == 1)
    {
        fprintf(file, "Saldiri_Gelistirmesi Seviye_3\n");
    }

    if(OR->elit_egitim.seviye_1.sayi == 1)
    {
        fprintf(file, "Elit_Egitim Seviye_1\n");
    }

    if(OR->elit_egitim.seviye_2.sayi == 1)
    {
        fprintf(file, "Elit_Egitim Seviye_2\n");
    }

    if(OR->elit_egitim.seviye_3.sayi == 1)
    {
        fprintf(file, "Elit_Egitim Seviye_3\n");
    }
    fclose(file);
}

void parse_hero_json(const char *filename, Human_Hero *HH, Ork_Hero *OH)
{
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        printf("Dosya Acilamadi: %s\n", filename);
        return;
    }

    char line[256];
    char bonus_str[10];
    while (fgets(line, sizeof(line), file))
    {
        if (strstr(line, "\"Alparslan\"") != NULL)
        {
            fgets(line, sizeof(line), file);
            sscanf(line, " \"bonus_turu\" : \"%[^\"]\",", &HH->alparslan.bonus_turu);
            fgets(line, sizeof(line), file);
            sscanf(line, " \"bonus_degeri\" : \"%[^\"]\",", bonus_str);
            HH->alparslan.bonus_degeri = atoi(bonus_str);
            fgets(line, sizeof(line), file);
            sscanf(line, " \"aciklama\" : \"%[^\"]\",", &HH->alparslan.aciklama);

        }
        if (strstr(line, "\"Fatih_Sultan_Mehmet\"") != NULL)
        {
            fgets(line, sizeof(line), file);
            sscanf(line, " \"bonus_turu\" : \"%[^\"]\",", &HH->fsm.bonus_turu);
            fgets(line, sizeof(line), file);
            sscanf(line, " \"bonus_degeri\" : \"%[^\"]\",", bonus_str);
            HH->fsm.bonus_degeri = atoi(bonus_str);
            fgets(line, sizeof(line), file);
            sscanf(line, " \"aciklama\" : \"%[^\"]\",", &HH->fsm.aciklama);

        }
        if (strstr(line, "\"Mete_Han\"") != NULL)
        {
            fgets(line, sizeof(line), file);
            sscanf(line, " \"bonus_turu\" : \"%[^\"]\",", &HH->metehan.bonus_turu);
            fgets(line, sizeof(line), file);
            sscanf(line, " \"bonus_degeri\" : \"%[^\"]\",", bonus_str);
            HH->metehan.bonus_degeri = atoi(bonus_str);
            fgets(line, sizeof(line), file);
            sscanf(line, " \"aciklama\" : \"%[^\"]\",", &HH->metehan.aciklama);

        }
        if (strstr(line, "\"Yavuz_Sultan_Selim\"") != NULL)
        {
            fgets(line, sizeof(line), file);
            sscanf(line, " \"bonus_turu\" : \"%[^\"]\",", &HH->yss.bonus_turu);
            fgets(line, sizeof(line), file);
            sscanf(line, " \"bonus_degeri\" : \"%[^\"]\",", bonus_str);
            HH->yss.bonus_degeri = atoi(bonus_str);
            fgets(line, sizeof(line), file);
            sscanf(line, " \"aciklama\" : \"%[^\"]\",", &HH->yss.aciklama);
        }
        if (strstr(line, "\"Tugrul_Bey\"") != NULL)
        {
            fgets(line, sizeof(line), file);
            sscanf(line, " \"bonus_turu\" : \"%[^\"]\",", &HH->tugrul_bey.bonus_turu);
            fgets(line, sizeof(line), file);
            sscanf(line, " \"bonus_degeri\" : \"%[^\"]\",", bonus_str);
            HH->tugrul_bey.bonus_degeri = atoi(bonus_str);
            fgets(line, sizeof(line), file);
            sscanf(line, " \"aciklama\" : \"%[^\"]\",", &HH->tugrul_bey.aciklama);

        }
        if (strstr(line, "\"Goruk_Vahsi\"") != NULL)
        {
            fgets(line, sizeof(line), file);
            sscanf(line, " \"bonus_turu\" : \"%[^\"]\",", &OH->goruk.bonus_turu);
            fgets(line, sizeof(line), file);
            sscanf(line, " \"bonus_degeri\" : \"%[^\"]\",", bonus_str);
            OH->goruk.bonus_degeri = atoi(bonus_str);
            fgets(line, sizeof(line), file);
            sscanf(line, " \"aciklama\" : \"%[^\"]\",", &OH->goruk.aciklama);

        }
        if (strstr(line, "\"Thruk_Kemikkiran\"") != NULL)
        {
            fgets(line, sizeof(line), file);
            sscanf(line, " \"bonus_turu\" : \"%[^\"]\",", &OH->thruk.bonus_turu);
            fgets(line, sizeof(line), file);
            sscanf(line, " \"bonus_degeri\" : \"%[^\"]\",", bonus_str);
            OH->thruk.bonus_degeri = atoi(bonus_str);
            fgets(line, sizeof(line), file);
            sscanf(line, " \"aciklama\" : \"%[^\"]\",", &OH->thruk.aciklama);

        }
        if (strstr(line, "\"Vrog_Kafakiran\"") != NULL)
        {
            fgets(line, sizeof(line), file);
            sscanf(line, " \"bonus_turu\" : \"%[^\"]\",", &OH->vrog.bonus_turu);
            fgets(line, sizeof(line), file);
            sscanf(line, " \"bonus_degeri\" : \"%[^\"]\",", bonus_str);
            OH->vrog.bonus_degeri = atoi(bonus_str);
            fgets(line, sizeof(line), file);
            sscanf(line, " \"aciklama\" : \"%[^\"]\",", &OH->vrog.aciklama);

        }
        if (strstr(line, "\"Ugar_Zalim\"") != NULL)
        {
            fgets(line, sizeof(line), file);
            sscanf(line, " \"bonus_turu\" : \"%[^\"]\",", &OH->ugar.bonus_turu);
            fgets(line, sizeof(line), file);
            sscanf(line, " \"bonus_degeri\" : \"%[^\"]\",", bonus_str);
            OH->ugar.bonus_degeri = atoi(bonus_str);
            fgets(line, sizeof(line), file);
            sscanf(line, " \"aciklama\" : \"%[^\"]\",", &OH->ugar.aciklama);

        }
    }
    fclose(file);
}

void parse_research_json(const char *filename, Research *HR, Research *OR)
{
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        printf("Dosya Acilamadi: %s\n", filename);
        return;
    }

    char line[256];
    Research_Type *current_research_type = NULL;
    Seviye *current_level = NULL;

    while (fgets(line, sizeof(line), file))
    {
        if (strstr(line, "\"savunma_ustaligi\""))
        {
            current_research_type = &HR->savunma_ustaligi;
        }
        else if (strstr(line, "\"saldiri_gelistirmesi\""))
        {
            current_research_type = &HR->saldiri_gelistirmesi;
        }
        else if (strstr(line, "\"elit_egitim\""))
        {
            current_research_type = &HR->elit_egitim;
        }
        else if (strstr(line, "\"kusatma_ustaligi\""))
        {
            current_research_type = &HR->kusatma_ustaligi;
        }
        else if (strstr(line, "\"deger\""))
        {
            if (current_level)
            {
                sscanf(line, " \"deger\": \"%d\"", &current_level->deger);
            }
        }
        else if (strstr(line, "\"aciklama\""))
        {
            if (current_level)
            {
                char *start = strchr(line, ':') + 3;
                strncpy(current_level->aciklama, start, strlen(start) - 2);
                current_level->aciklama[strlen(start) - 2] = '\0';
            }
        }
        else if (strstr(line, "\"seviye_1\""))
        {
            current_level = &current_research_type->seviye_1;
        }
        else if (strstr(line, "\"seviye_2\""))
        {
            current_level = &current_research_type->seviye_2;
        }
        else if (strstr(line, "\"seviye_3\""))
        {
            current_level = &current_research_type->seviye_3;
        }
    }

    fclose(file);

    memcpy(&OR->savunma_ustaligi, &HR->savunma_ustaligi, sizeof(Research_Type));
    memcpy(&OR->saldiri_gelistirmesi, &HR->saldiri_gelistirmesi, sizeof(Research_Type));
    memcpy(&OR->elit_egitim, &HR->elit_egitim, sizeof(Research_Type));
    memcpy(&OR->kusatma_ustaligi, &HR->kusatma_ustaligi, sizeof(Research_Type));
}

void read_human_scenario(const char *filename, Human_Unit *HU, Human_Hero *HH, Human_Creature *HC, Research *HR)
{
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        printf("Dosya Acilamadi!\n");
        return;
    }
    char line[256];
    int value = 0;
    while (fgets(line, sizeof(line), file))
    {
        if (strstr(line, "\"insan_imparatorlugu\": {") != NULL)
        {
            while (fgets(line, sizeof(line), file) && !strstr(line, "ork_legi"))
            {
                if (strstr(line, "\"piyadeler\"") != NULL)
                {
                    sscanf(line, " \"piyadeler\": %d,", &HU->piyadeler.sayi);
                }
                if (strstr(line, "okcular") != NULL)
                {
                    sscanf(line, " \"okcular\": %d,", &HU->okcular.sayi);
                }
                if (strstr(line, "suvariler") != NULL)
                {
                    sscanf(line, " \"suvariler\": %d,", &HU->suvariler.sayi);
                }
                if (strstr(line, "kusatma_makineleri") != NULL)
                {
                    sscanf(line, " \"kusatma_makineleri\": %d,", &HU->kusatma_makineleri.sayi);
                }
                if (strstr(line, "\"Alparslan\"") != NULL)
                {
                    HH->alparslan.sayi = 1;
                }
                if (strstr(line, "\"Fatih_Sultan_Mehmet\"") != NULL)
                {
                    HH->fsm.sayi = 1;
                }
                if (strstr(line, "\"Yavuz_Sultan_Selim\"") != NULL)
                {
                    HH->yss.sayi = 1;
                }
                if (strstr(line, "\"Tugrul_Bey\"") != NULL)
                {
                    HH->tugrul_bey.sayi = 1;
                }
                if (strstr(line, "\"Ejderha\"") != NULL)
                {
                    HC->ejderha.sayi = 1;
                }
                if (strstr(line, "\"Agri_Dagi_Devleri\"") != NULL)
                {
                    HC->agri_dagi.sayi = 1;
                }
                if (strstr(line, "\"Tepegoz\"") != NULL)
                {
                    HC->tepegoz.sayi = 1;
                }
                if (strstr(line, "\"Karakurt\"") != NULL)
                {
                    HC->karakurt.sayi = 1;
                }
                if (strstr(line, "\"Samur\"") != NULL)
                {
                    HC->samur.sayi = 1;
                }
                if (strstr(line, "\"savunma_ustaligi\"") != NULL)
                {
                    sscanf(line, " \"%*[^\"]\": %d", &value);
                    if (value == 1)
                    {
                        HR->savunma_ustaligi.seviye_1.sayi = 1;
                    }
                    else if (value == 2)
                    {
                        HR->savunma_ustaligi.seviye_2.sayi = 1;
                    }
                    else if (value == 3)
                    {
                        HR->savunma_ustaligi.seviye_3.sayi = 1;
                    }
                }
                if (strstr(line, "\"saldiri_gelistirmesi\"") != NULL)
                {
                    sscanf(line, " \"%*[^\"]\": %d", &value);
                    if (value == 1)
                    {
                        HR->saldiri_gelistirmesi.seviye_1.sayi++;
                    }
                    else if (value == 2)
                    {
                        HR->saldiri_gelistirmesi.seviye_2.sayi++;
                    }
                    else if (value == 3)
                    {
                        HR->saldiri_gelistirmesi.seviye_3.sayi++;
                    }
                }
                if (strstr(line, "elit_egitim") != NULL)
                {
                    sscanf(line, " \"%*[^\"]\": %d", &value);
                    if (value == 1)
                    {
                        HR->elit_egitim.seviye_1.sayi++;
                    }
                    else if (value == 2)
                    {
                        HR->elit_egitim.seviye_2.sayi++;
                    }
                    else if (value == 3)
                    {
                        HR->elit_egitim.seviye_3.sayi++;
                    }
                }
                if (strstr(line, "kusatma_ustaligi") != NULL)
                {
                    sscanf(line, " \"%*[^\"]\": %d", &value);
                    if (value == 1)
                    {
                        HR->kusatma_ustaligi.seviye_1.sayi++;
                    }
                    else if (value == 2)
                    {
                        HR->kusatma_ustaligi.seviye_2.sayi++;
                    }
                    else if (value == 3)
                    {
                        HR->kusatma_ustaligi.seviye_3.sayi++;
                    }
                }
            }
        }
    }
    fclose(file);
}

void read_ork_scenario(const char *filename, Ork_Unit *OU, Ork_Hero *OH, Ork_Creature *OC, Research *OR)
{
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        printf("Dosya Acilamadi!\n");
        return;
    }
    char line[256];
    int value = 0;
    while (fgets(line, sizeof(line), file))
    {
        if (strstr(line, "\"ork_legi\": {") != NULL)
        {
            while (fgets(line, sizeof(line), file) && !strstr(line, "insan_imparatorlugu"))
            {
                if (strstr(line, "ork_dovusculeri") != NULL)
                {
                    sscanf(line, " \"ork_dovusculeri\": %d,", &OU->ork_dovusculeri.sayi);
                }
                if (strstr(line, "mizrakcilar") != NULL)
                {
                    sscanf(line, " \"mizrakcilar\": %d,", &OU->mizrakcilar.sayi);
                }
                if (strstr(line, "varg_binicileri") != NULL)
                {
                    sscanf(line, " \"varg_binicileri\": %d,", &OU->varg_binicileri.sayi);
                }
                if (strstr(line, "troller") != NULL)
                {
                    sscanf(line, " \"troller\": %d,", &OU->troller.sayi);
                }
                if (strstr(line, "\"Goruk_Vahsi\"") != NULL)
                {
                    OH->goruk.sayi++;
                }
                if (strstr(line, "\"Thruk_Kemikkiran\"") != NULL)
                {
                    OH->thruk.sayi++;
                }
                if (strstr(line, "\"Vrog_Kafakiran\"") != NULL)
                {
                    OH->vrog.sayi++;
                }
                if (strstr(line, "\"Ugar_Zalim\"") != NULL)
                {
                    OH->ugar.sayi++;
                }
                if (strstr(line, "\"Kara_Troll\"") != NULL)
                {
                    OC->troll.sayi++;
                }
                if (strstr(line, "\"Golge_Kurtlari\"") != NULL)
                {
                    OC->golge.sayi++;
                }
                if (strstr(line, "\"Camur_Devleri\"") != NULL)
                {
                    OC->camur.sayi++;
                }
                if (strstr(line, "\"Ates_Iblisi\"") != NULL)
                {
                    OC->ates_iblisi.sayi++;
                }
                if (strstr(line, "\"Makrog_Savas_Beyi\"") != NULL)
                {
                    OC->makrog.sayi++;
                }
                if (strstr(line, "\"Buz_Devleri\"") != NULL)
                {
                    OC->buz_devi.sayi++;
                }
                if (strstr(line, "savunma_ustaligi") != NULL)
                {
                    sscanf(line, " \"%*[^\"]\": %d", &value);
                    if (value == 1)
                    {
                        OR->savunma_ustaligi.seviye_1.sayi++;
                    }
                    else if (value == 2)
                    {
                        OR->savunma_ustaligi.seviye_2.sayi++;
                    }
                    else if (value == 3)
                    {
                        OR->savunma_ustaligi.seviye_3.sayi++;
                    }
                }
                if (strstr(line, "saldiri_gelistirmesi") != NULL)
                {
                    sscanf(line, " \"%*[^\"]\": %d", &value);
                    if (value == 1)
                    {
                        OR->saldiri_gelistirmesi.seviye_1.sayi++;
                    }
                    else if (value == 2)
                    {
                        OR->saldiri_gelistirmesi.seviye_2.sayi++;
                    }
                    else if (value == 3)
                    {
                        OR->saldiri_gelistirmesi.seviye_3.sayi++;
                    }
                }
                if (strstr(line, "elit_egitim") != NULL)
                {
                    sscanf(line, " \"%*[^\"]\": %d", &value);
                    if (value == 1)
                    {
                        OR->elit_egitim.seviye_1.sayi++;
                    }
                    else if (value == 2)
                    {
                        OR->elit_egitim.seviye_2.sayi++;
                    }
                    else if (value == 3)
                    {
                        OR->elit_egitim.seviye_3.sayi++;
                    }
                }
                if (strstr(line, "kusatma_ustaligi") != NULL)
                {
                    sscanf(line, " \"%*[^\"]\": %d", &value);
                    if (value == 1)
                    {
                        OR->kusatma_ustaligi.seviye_1.sayi++;
                    }
                    else if (value == 2)
                    {
                        OR->kusatma_ustaligi.seviye_2.sayi++;
                    }
                    else if (value == 3)
                    {
                        OR->kusatma_ustaligi.seviye_3.sayi++;
                    }
                }
            }
        }
    }
    fclose(file);
}

void parse_unit_json(const char *filename, Human_Unit *HU, Ork_Unit *OU)
{
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        printf("Dosya Acilamadi: %s\n", filename);
        return;
    }

    char line[256];
    while (fgets(line, sizeof(line), file))
    {
        if (strstr(line, "\"piyadeler\"") != NULL)
        {
            fgets(line, sizeof(line), file);
            sscanf(line, " \"saldiri\" : %d,", &HU->piyadeler.saldiri);
            fgets(line, sizeof(line), file);
            sscanf(line, " \"savunma\" : %d,", &HU->piyadeler.savunma);
            fgets(line, sizeof(line), file);
            sscanf(line, " \"saglik\" : %d,", &HU->piyadeler.saglik);
            fgets(line, sizeof(line), file);
            sscanf(line, " \"kritik_sans\" : %d", &HU->piyadeler.kritik_sans);
        }
        if (strstr(line, "\"okcular\"") != NULL)
        {
            fgets(line, sizeof(line), file);
            sscanf(line, " \"saldiri\" : %d,", &HU->okcular.saldiri);
            fgets(line, sizeof(line), file);
            sscanf(line, " \"savunma\" : %d,", &HU->okcular.savunma);
            fgets(line, sizeof(line), file);
            sscanf(line, " \"saglik\" : %d,", &HU->okcular.saglik);
            fgets(line, sizeof(line), file);
            sscanf(line, " \"kritik_sans\" : %d", &HU->okcular.kritik_sans);
        }
        if (strstr(line, "\"suvariler\"") != NULL)
        {
            fgets(line, sizeof(line), file);
            sscanf(line, " \"saldiri\" : %d,", &HU->suvariler.saldiri);
            fgets(line, sizeof(line), file);
            sscanf(line, " \"savunma\" : %d,", &HU->suvariler.savunma);
            fgets(line, sizeof(line), file);
            sscanf(line, " \"saglik\" : %d,", &HU->suvariler.saglik);
            fgets(line, sizeof(line), file);
            sscanf(line, " \"kritik_sans\" : %d", &HU->suvariler.kritik_sans);
        }
        if (strstr(line, "\"kusatma_makineleri\"") != NULL)
        {
            fgets(line, sizeof(line), file);
            sscanf(line, " \"saldiri\": %d,", &HU->kusatma_makineleri.saldiri);
            fgets(line, sizeof(line), file);
            sscanf(line, " \"savunma\": %d,", &HU->kusatma_makineleri.savunma);
            fgets(line, sizeof(line), file);
            sscanf(line, " \"saglik\": %d,", &HU->kusatma_makineleri.saglik);
            fgets(line, sizeof(line), file);
            sscanf(line, " \"kritik_sans\": %d", &HU->kusatma_makineleri.kritik_sans);
        }
        if (strstr(line, "\"ork_dovusculeri\"") != NULL)
        {
            fgets(line, sizeof(line), file);
            sscanf(line, " \"saldiri\": %d,", &OU->ork_dovusculeri.saldiri);
            fgets(line, sizeof(line), file);
            sscanf(line, " \"savunma\": %d,", &OU->ork_dovusculeri.savunma);
            fgets(line, sizeof(line), file);
            sscanf(line, " \"saglik\": %d,", &OU->ork_dovusculeri.saglik);
            fgets(line, sizeof(line), file);
            sscanf(line, " \"kritik_sans\": %d", &OU->ork_dovusculeri.kritik_sans);
        }
        if (strstr(line, "\"mizrakcilar\"") != NULL)
        {
            fgets(line, sizeof(line), file);
            sscanf(line, " \"saldiri\": %d,", &OU->mizrakcilar.saldiri);
            fgets(line, sizeof(line), file);
            sscanf(line, " \"savunma\": %d,", &OU->mizrakcilar.savunma);
            fgets(line, sizeof(line), file);
            sscanf(line, " \"saglik\": %d,", &OU->mizrakcilar.saglik);
            fgets(line, sizeof(line), file);
            sscanf(line, " \"kritik_sans\": %d", &OU->mizrakcilar.kritik_sans);
        }
        if (strstr(line, "\"varg_binicileri\"") != NULL)
        {
            fgets(line, sizeof(line), file);
            sscanf(line, " \"saldiri\": %d,", &OU->varg_binicileri.saldiri);
            fgets(line, sizeof(line), file);
            sscanf(line, " \"savunma\": %d,", &OU->varg_binicileri.savunma);
            fgets(line, sizeof(line), file);
            sscanf(line, " \"saglik\": %d,", &OU->varg_binicileri.saglik);
            fgets(line, sizeof(line), file);
            sscanf(line, " \"kritik_sans\": %d", &OU->varg_binicileri.kritik_sans);
        }
        if (strstr(line, "\"troller\"") != NULL)
        {
            fgets(line, sizeof(line), file);
            sscanf(line, " \"saldiri\": %d,", &OU->troller.saldiri);
            fgets(line, sizeof(line), file);
            sscanf(line, " \"savunma\": %d,", &OU->troller.savunma);
            fgets(line, sizeof(line), file);
            sscanf(line, " \"saglik\": %d,", &OU->troller.saglik);
            fgets(line, sizeof(line), file);
            sscanf(line, " \"kritik_sans\": %d", &OU->troller.kritik_sans);
        }
    }

    fclose(file);
}

int kritik_vurus_hesapla(Unit *unit, int adim)
{
    // Birimin kritik vuruş zamanını hesapla
    if(unit->kritik_sans == 0)
    {
        return unit->saldiri * unit->sayi;
    }

    if (adim % (100 / unit->kritik_sans) == 0)
    {
        return unit->saldiri * unit->sayi * 1.5; // Kritik vuruş varsa hasarı artır
    }

    return unit->saldiri * unit->sayi; // Kritik vuruş yoksa normal hasar
}

// İnsanların toplam saldırı gücünü hesaplayan fonksiyon
void saldiri_gucu_hesapla(Human_Unit *HU, Ork_Unit *OU , int adim , double *toplam_insan_saldiri , double *toplam_ork_saldiri)
{
    *toplam_insan_saldiri = kritik_vurus_hesapla(&HU->piyadeler , adim) +
                            kritik_vurus_hesapla(&HU->okcular , adim) +
                            kritik_vurus_hesapla(&HU->suvariler , adim) +
                            kritik_vurus_hesapla(&HU->kusatma_makineleri , adim) ;


    *toplam_ork_saldiri =   kritik_vurus_hesapla(&OU->ork_dovusculeri , adim) +
                            kritik_vurus_hesapla(&OU->mizrakcilar , adim) +
                            kritik_vurus_hesapla(&OU->varg_binicileri , adim) +
                            kritik_vurus_hesapla(&OU->troller , adim);

}

//Savunma gucu hesaplayan Fonksiyon
void savunma_gucu_hesapla(Human_Unit *HU , Ork_Unit *OU ,double *toplam_insan_savunma , double *toplam_ork_savunma) {

    *toplam_insan_savunma = (HU->piyadeler.savunma * HU->piyadeler.sayi) +
                            (HU->okcular.savunma * HU->okcular.sayi) +
                            (HU->suvariler.savunma * HU->suvariler.sayi) +
                            (HU->kusatma_makineleri.savunma * HU->kusatma_makineleri.sayi);

    *toplam_ork_savunma = (OU->ork_dovusculeri.savunma * OU->ork_dovusculeri.sayi) +
                          (OU->mizrakcilar.savunma * OU->mizrakcilar.sayi) +
                          (OU->varg_binicileri.savunma * OU->varg_binicileri.sayi) +
                          (OU->troller.savunma * OU->troller.sayi);

}

void ork_saglik_hesapla(Ork_Unit *OU, double net_hasar_insan, double *toplam_ork_savunma)
{
    // Oran Hesaplama(Ork)
    double oran_ork_dovusculeri = (double)(OU->ork_dovusculeri.savunma * OU->ork_dovusculeri.sayi) / *toplam_ork_savunma;
    double oran_mizrakcilar = (double)(OU->mizrakcilar.savunma * OU->mizrakcilar.sayi) / *toplam_ork_savunma;
    double oran_varg_binicileri = (double)(OU->varg_binicileri.savunma * OU->varg_binicileri.sayi) / *toplam_ork_savunma;
    double oran_troller = (double)(OU->troller.savunma * OU->troller.sayi) / *toplam_ork_savunma;


    // Hasar Dagilimi
    double hasar_ork_dovusculeri = net_hasar_insan * oran_ork_dovusculeri;
    double hasar_mizrakcilar = net_hasar_insan * oran_mizrakcilar;
    double hasar_varg_binicileri = net_hasar_insan * oran_varg_binicileri;
    double hasar_troller = net_hasar_insan * oran_troller;

    //
    OU->ork_dovusculeri.saglik -= (hasar_ork_dovusculeri / OU->ork_dovusculeri.sayi);
    OU->mizrakcilar.saglik -= (hasar_mizrakcilar / OU->mizrakcilar.sayi);
    OU->varg_binicileri.saglik -= (hasar_varg_binicileri / OU->varg_binicileri.sayi);
    OU->troller.saglik -= (hasar_troller / OU->troller.sayi);


    // Sağlık 0'ın altına düşerse, 0'da sabitle.

    if (OU->ork_dovusculeri.saglik <= 0) OU->ork_dovusculeri.saglik = 0;
    if (OU->mizrakcilar.saglik <= 0) OU->mizrakcilar.saglik = 0;
    if (OU->varg_binicileri.saglik <= 0) OU->varg_binicileri.saglik = 0;
    if (OU->troller.saglik <= 0) OU->troller.saglik = 0;

    if (OU->ork_dovusculeri.saglik <= 0) OU->ork_dovusculeri.sayi = 0;
    if (OU->mizrakcilar.saglik <= 0) OU->mizrakcilar.sayi = 0;
    if (OU->varg_binicileri.saglik <= 0) OU->varg_binicileri.sayi = 0;
    if (OU->troller.saglik <= 0) OU->troller.sayi = 0;
}

void insan_saglik_hesapla(Human_Unit *HU, double net_hasar_ork, double *toplam_insan_savunma)
{
    //Oran hesaplama(insan)
    double oran_piyadeler = (double)(HU->piyadeler.savunma * HU->piyadeler.sayi) / *toplam_insan_savunma;
    double oran_okcular = (double)(HU->okcular.savunma * HU->okcular.sayi) / *toplam_insan_savunma;
    double oran_suvariler = (double)(HU->suvariler.savunma * HU->suvariler.sayi) / *toplam_insan_savunma;
    double oran_kusatma = (double)(HU->kusatma_makineleri.savunma * HU->kusatma_makineleri.sayi) / *toplam_insan_savunma;

    //Hasar Dagilimi(insan)
    double hasar_piyadeler = net_hasar_ork * oran_piyadeler;
    double hasar_okcular = net_hasar_ork * oran_okcular;
    double hasar_suvariler = net_hasar_ork * oran_suvariler;
    double hasar_kusatma = net_hasar_ork * oran_kusatma;

    // Sayi Guncelleme(insan)
    HU->piyadeler.saglik -= hasar_piyadeler / HU->piyadeler.sayi;
    HU->okcular.saglik -= hasar_okcular / HU->okcular.sayi;
    HU->suvariler.saglik -= hasar_suvariler / HU->suvariler.sayi;
    HU->kusatma_makineleri.saglik -= hasar_kusatma / HU->kusatma_makineleri.sayi;

    // sayi 0'in altina duserse, 0'da sabitle.(insan)
    if (HU->piyadeler.saglik <= 0) HU->piyadeler.saglik = 0;
    if (HU->okcular.saglik <= 0) HU->okcular.saglik = 0;
    if (HU->suvariler.saglik<= 0) HU->suvariler.saglik = 0;
    if (HU->kusatma_makineleri.saglik <= 0) HU->kusatma_makineleri.saglik = 0;

    if (HU->piyadeler.saglik <= 0) HU->piyadeler.sayi = 0;
    if (HU->okcular.saglik <= 0) HU->okcular.sayi = 0;
    if (HU->suvariler.saglik<= 0) HU->suvariler.sayi = 0;
    if (HU->kusatma_makineleri.saglik <= 0) HU->kusatma_makineleri.sayi = 0;

}

int insan_net_hasar_hesaplama(Human_Unit *HU, double *toplam_insan_saldiri, double *toplam_ork_savunma)
{
    int insan_net_hasar = *toplam_insan_saldiri * (1 - (*toplam_ork_savunma / *toplam_insan_saldiri));
    if (insan_net_hasar < 0)
        insan_net_hasar = 0;
    return (insan_net_hasar);
}

int ork_net_hasar_hesaplama(Ork_Unit *OU, double *toplam_ork_saldiri, double *toplam_insan_savunma)
{
    int ork_net_hasar = *toplam_ork_saldiri * (1 - (*toplam_insan_savunma / *toplam_ork_saldiri));
    if (ork_net_hasar < 0)
        ork_net_hasar = 0;
    return (ork_net_hasar);
}

void add_bonus_value(Human_Unit *HU, Ork_Unit *OU, Human_Hero *HH, Ork_Hero *OH, Human_Creature *HC, Ork_Creature *OC, Research *HR, Research *OR)
{
	if (HH->alparslan.sayi == 1)
    {
        HU->piyadeler.savunma *= 1.2;
    }

    if (HH->fsm.sayi == 1)
    {
        HU->kusatma_makineleri.saldiri *= 1.25;
    }

    if (HH->metehan.sayi == 1)
    {
        HU->okcular.savunma *= 1.2;
    }

    if(HH->yss.sayi == 1)
    {
        HU->suvariler.kritik_sans += 15;
    }

    if(HH->tugrul_bey.sayi == 1)
    {
        HU->okcular.saldiri *= 1.2;
    }

    if(OH->goruk.sayi == 1)
    {
        OU->ork_dovusculeri.saldiri *= 1.2;
    }

    if(OH->thruk.sayi == 1)
    {
        OU->troller.savunma *= 1.25;
    }

    if(OH->vrog.sayi == 1)
    {
        OU->varg_binicileri.kritik_sans += 15;
    }

    if (OH->ugar.sayi == 1)
    {
        OU->mizrakcilar.savunma *= 1.1;
        OU->ork_dovusculeri.savunma *= 1.1;
        OU->troller.savunma *= 1.1;
        OU->varg_binicileri.savunma *= 1.1;
    }

    if(HC->ejderha.sayi == 1)
    {
        HU->piyadeler.saldiri *= 1.15;
    }

    if(HC->agri_dagi.sayi == 1)
    {
        HU->suvariler.savunma *=1.2;
    }

    if(HC->tepegoz.sayi == 1)
    {
        HU->okcular.saldiri *= 1.25;

    }

    if(HC->karakurt.sayi == 1)
    {
        HU->okcular.kritik_sans += 10;
    }

    if(HC->samur.sayi == 1)
    {
        HU->piyadeler.savunma *= 1.1;
    }

    if(OC->troll.sayi == 1)
    {
        OU->troller.saldiri *= 1.2;
    }

    if(OC->golge.sayi == 1)
    {
        OU->varg_binicileri.savunma *= 1.15;
    }

    if(OC->camur.sayi == 1)
    {
        OU->ork_dovusculeri.savunma *= 1.25;
    }

    if(OC->ates_iblisi.sayi == 1)
    {
        OU->varg_binicileri.saldiri *= 1.3;
    }

    if(OC->makrog.sayi == 1)
    {
        OU->troller.savunma *= 1.25;
    }

    if(OC->buz_devi.sayi == 1)
    {
        OU->mizrakcilar.savunma *= 1.15;
    }

    if (HR->savunma_ustaligi.seviye_1.sayi == 1)
    {
        HU->piyadeler.savunma *= 1.1;
        HU->okcular.savunma *= 1.1;
        HU->suvariler.savunma *= 1.1;
        HU->kusatma_makineleri.savunma *= 1.1;
    }
    if (HR->savunma_ustaligi.seviye_2.sayi == 1)
    {
        HU->piyadeler.savunma *= 1.2;
        HU->okcular.savunma *= 1.2;
        HU->suvariler.savunma *= 1.2;
        HU->kusatma_makineleri.savunma *= 1.2;
    }
    if (HR->savunma_ustaligi.seviye_3.sayi == 1)
    {
        HU->piyadeler.savunma *= 1.3;
        HU->okcular.savunma *= 1.3;
        HU->suvariler.savunma *= 1.3;
        HU->kusatma_makineleri.savunma *= 1.3;
    }

    if(HR->saldiri_gelistirmesi.seviye_1.sayi == 1)
    {
        HU->piyadeler.saldiri *=1.1;
        HU->okcular.saldiri *=1.1;
        HU->suvariler.saldiri *=1.1;
        HU->kusatma_makineleri.saldiri *= 1.1;
    }

    if(HR->saldiri_gelistirmesi.seviye_2.sayi == 1)
    {
        HU->piyadeler.saldiri *=1.2;
        HU->okcular.saldiri *=1.2;
        HU->suvariler.saldiri *=1.2;
        HU->kusatma_makineleri.saldiri *= 1.1;
    }

    if(HR->saldiri_gelistirmesi.seviye_3.sayi == 1)
    {
        HU->piyadeler.saldiri *=1.3;
        HU->okcular.saldiri *=1.3;
        HU->suvariler.saldiri *=1.3;
        HU->kusatma_makineleri.saldiri *= 1.3;
    }

    if(HR->elit_egitim.seviye_1.sayi == 1)
    {
        HU->piyadeler.kritik_sans += 5;
        HU->okcular.kritik_sans += 5;
        HU->suvariler.kritik_sans += 5;
        HU->kusatma_makineleri.kritik_sans += 5;
    }

    if(HR->elit_egitim.seviye_2.sayi == 1)
    {
        HU->piyadeler.kritik_sans += 10;
        HU->okcular.kritik_sans += 10;
        HU->suvariler.kritik_sans += 10;
        HU->kusatma_makineleri.kritik_sans += 10;
    }

    if(HR->elit_egitim.seviye_3.sayi == 1)
    {
        HU->piyadeler.kritik_sans += 15;
        HU->okcular.kritik_sans += 15;
        HU->suvariler.kritik_sans += 15;
        HU->kusatma_makineleri.kritik_sans += 15;
    }

    if(HR->kusatma_ustaligi.seviye_1.sayi == 1)
    {
       HU->kusatma_makineleri.saldiri *= 1.1;
    }

    if(HR->kusatma_ustaligi.seviye_2.sayi == 1)
    {
       HU->kusatma_makineleri.saldiri *= 1.2;
    }

    if(HR->kusatma_ustaligi.seviye_3.sayi == 1)
    {
       HU->kusatma_makineleri.saldiri *= 1.3;
    }

    if (OR->savunma_ustaligi.seviye_1.sayi == 1)
    {
        OU->ork_dovusculeri.savunma *= 1.1;
        OU->mizrakcilar.savunma *= 1.1;
        OU->varg_binicileri.savunma *= 1.1;
        OU->troller.savunma *= 1.1;
    }
    if (OR->savunma_ustaligi.seviye_2.sayi == 1)
    {
        OU->ork_dovusculeri.savunma *= 1.2;
        OU->mizrakcilar.savunma *= 1.2;
        OU->varg_binicileri.savunma *= 1.2;
        OU->troller.savunma *= 1.2;
    }
    if (OR->savunma_ustaligi.seviye_3.sayi == 1)
    {
        OU->ork_dovusculeri.savunma *= 1.3;
        OU->mizrakcilar.savunma *= 1.3;
        OU->varg_binicileri.savunma *= 1.3;
        OU->troller.savunma *= 1.3;
    }

    if(OR->saldiri_gelistirmesi.seviye_1.sayi == 1)
    {
        OU->ork_dovusculeri.saldiri *=1.1;
        OU->mizrakcilar.saldiri *=1.1;
        OU->varg_binicileri.saldiri *=1.1;
        OU->troller.saldiri *= 1.1;
    }

    if(OR->saldiri_gelistirmesi.seviye_2.sayi == 1)
    {
        OU->ork_dovusculeri.saldiri *=1.2;
        OU->mizrakcilar.saldiri *=1.2;
        OU->varg_binicileri.saldiri *=1.2;
        OU->troller.saldiri *= 1.1;
    }

    if(OR->saldiri_gelistirmesi.seviye_3.sayi == 1)
    {
        OU->ork_dovusculeri.saldiri *=1.3;
        OU->mizrakcilar.saldiri *=1.3;
        OU->varg_binicileri.saldiri *=1.3;
        OU->troller.saldiri *= 1.3;
    }

    if(OR->elit_egitim.seviye_1.sayi == 1)
    {
        OU->ork_dovusculeri.kritik_sans += 5;
        OU->mizrakcilar.kritik_sans += 5;
        OU->varg_binicileri.kritik_sans += 5;
        OU->troller.kritik_sans += 5;
    }

    if(OR->elit_egitim.seviye_2.sayi == 1)
    {
        OU->ork_dovusculeri.kritik_sans += 10;
        OU->mizrakcilar.kritik_sans += 10;
        OU->varg_binicileri.kritik_sans += 10;
        OU->troller.kritik_sans += 10;
    }

    if(OR->elit_egitim.seviye_3.sayi == 1)
    {
        OU->ork_dovusculeri.kritik_sans += 15;
        OU->mizrakcilar.kritik_sans += 15;
        OU->varg_binicileri.kritik_sans += 15;
        OU->troller.kritik_sans += 15;
    }
}



// Saglik bari cizdirme
void BarCizimi(int x, int y, int health) {
    int barKalinlik = 40;
    int barUzunluk = 5;
    Color barRengi = (health > 50) ? (Color){0, 255, 0, 180} :
                     (health > 20) ? (Color){255, 255, 0, 180} :
                     (Color){255, 0, 0, 180};

    DrawRectangle(x - barKalinlik / 2, y - 15, barKalinlik * health / 100, barUzunluk, barRengi);
    DrawText(TextFormat("%d", health), x + 5, y - 20, 10, BLACK); // Can degerini goster
}

const char* kazananMesaj = NULL; // Kazananı saklayacak global değişken

// Kazanan irki belirleme
const char* KazananTespit(Human_Unit *HU, Ork_Unit *OU) {

    //insan toplam saglik
    int insanSaglik = HU->piyadeler.saglik + HU->okcular.saglik + HU->suvariler.saglik + HU->kusatma_makineleri.saglik;

    // ork toplam saglik
    int orkSaglik = OU->ork_dovusculeri.saglik + OU->mizrakcilar.saglik + OU->varg_binicileri.saglik + OU->troller.saglik;

    // Kazananı belirleme
    if (insanSaglik <= 0 && orkSaglik > 0) {
        return "Orklar Kazandi!";
    } else if (orkSaglik <= 0 && insanSaglik > 0) {
        return "Insanlar Kazandi!";
    } else if (insanSaglik <= 0 && orkSaglik <= 0) {
        return "Berabere!";
    } else {
        return NULL; // Savaş hala devam ediyor
    }
}


void SavasGuncelle(Human_Unit *HU, Ork_Unit *OU) {

    if (IsKeyPressed(KEY_SPACE) && kazananMesaj == NULL) {
        kazananMesaj = KazananTespit(HU, OU);
    }
}
// Birim simgelerini çizme fonksiyonu
void BirimCizme(int x, int y, Unit unit, Color color, const char* unitName) {
    BarCizimi(x, y, unit.saglik);
    DrawCircle(x, y, 10, color);
    DrawText(unitName, x - 20, y + 15, 10, BLACK); // Birim ismini hafif aşağı kaydırdık
}

// Izgara üzerine birim yerleştirme fonksiyonu
void PlaceUnitsOnGrid(int startX, int startY, Unit unit, Color color, const char* unitName, int spacing) {
    int unitsRemaining = unit.sayi;
    int gridX = startX;
    int gridY = startY;

    for (int i = 0; i < GRID_SIZE && unitsRemaining > 0; i++) {
        int unitsInThisCell = (unitsRemaining > MAX_UNITS_PER_CELL) ? MAX_UNITS_PER_CELL : unitsRemaining;
        int cellX = (i % GRID_SIZE) * CELL_SIZE + gridX;
        int cellY = gridY + (i / GRID_SIZE) * spacing; // spacing ile satırlar arasında boşluk bırakıyoruz
        int centerX = cellX + CELL_SIZE / 2;
        int centerY = cellY + CELL_SIZE / 2;

        // Birimi ciz
        BirimCizme(centerX, centerY, unit, color, unitName);

        char countText[4];
        sprintf(countText, "%d", unitsInThisCell);
        DrawText(TextFormat("Sayi:%d", unitsInThisCell), centerX - 15, centerY + 30, 10, BLACK);

        unitsRemaining -= unitsInThisCell;
    }

}

// Izgara çizimi ve birimlerin yerleştirilmesi
void SavasAlaniCiz(Human_Unit *HU, Ork_Unit *OU) {
    int gridOffsetX = 50;
    int gridOffsetY = 50;


    // Izgara çizimi
    for (int i = 0; i <= GRID_SIZE; i++) {
        DrawLine(gridOffsetX, gridOffsetY + i * CELL_SIZE, gridOffsetX + GRID_SIZE * CELL_SIZE, gridOffsetY + i * CELL_SIZE, LIGHTGRAY);
        DrawLine(gridOffsetX + i * CELL_SIZE, gridOffsetY, gridOffsetX + i * CELL_SIZE, gridOffsetY + GRID_SIZE * CELL_SIZE, LIGHTGRAY);
    }

    int humanSpacing = CELL_SIZE * 2; // İnsan birimleri için aralık
    int orkSpacing = CELL_SIZE * 2;   // Ork birimleri için aralık

    // İnsan birimlerinin yerleştirilmesi - Üst satırlar
    PlaceUnitsOnGrid(gridOffsetX, gridOffsetY, HU->piyadeler, BLUE, "Piyade", humanSpacing);
    PlaceUnitsOnGrid(gridOffsetX, gridOffsetY + CELL_SIZE * 2, HU->okcular, GREEN, "Okcu", humanSpacing);
    PlaceUnitsOnGrid(gridOffsetX, gridOffsetY + CELL_SIZE * 4, HU->suvariler, YELLOW, "Suvari", humanSpacing);
    PlaceUnitsOnGrid(gridOffsetX, gridOffsetY + CELL_SIZE * 6, HU->kusatma_makineleri, GRAY , "Kusatma", humanSpacing);

    // Ork birimlerinin yerleştirilmesi - Alt satırlar
    int orkStartY = gridOffsetY + CELL_SIZE * 8; // Orklar için daha alt satırlardan başlatıyoruz
    PlaceUnitsOnGrid(gridOffsetX, orkStartY + CELL_SIZE * 5 , OU->ork_dovusculeri, BLACK, "OrkD", orkSpacing);
    PlaceUnitsOnGrid(gridOffsetX, orkStartY + CELL_SIZE * 7, OU->mizrakcilar, RED, "Mizrakci", orkSpacing);
    PlaceUnitsOnGrid(gridOffsetX, orkStartY + CELL_SIZE * 9, OU->varg_binicileri, BROWN, "Varg", orkSpacing);
    PlaceUnitsOnGrid(gridOffsetX, orkStartY + CELL_SIZE * 11, OU->troller, ORANGE, "Troll", orkSpacing);

    // Oyun durumu güncellenir
    SavasGuncelle(HU, OU);

    // Eğer kazanan belirlenmişse, sonucu ekrana sabit olarak yazdır
    if (kazananMesaj != NULL) {
        DrawText(kazananMesaj, 400, 400, 20, BLACK); // Kazananı ekrana sabit yazdır
    }
}
void savas_adim_adim(const char *filename, Human_Unit *HU, Ork_Unit *OU, int adim)
{
    FILE *file = fopen(filename, "a");
    if (file == NULL)
    {
        printf("Dosya Acilamadi: %s\n", filename);
        return;
    }

    double toplam_insan_saldiri = 0;
    double toplam_ork_saldiri = 0;
    double toplam_insan_savunma = 0;
    double toplam_ork_savunma = 0;
    int tur = 1;

    // Saldiri ve savunma guclerini hesapla
    saldiri_gucu_hesapla(HU, OU, tur, &toplam_insan_saldiri, &toplam_ork_saldiri);
    savunma_gucu_hesapla(HU, OU, &toplam_insan_savunma, &toplam_ork_savunma);

    // Insanlarin orklara verdigi net hasari hesapla


    // Orklarin insanlara verdigi net hasari hesapla


    if(adim % 2 == 0)
    {
        fprintf(file, "\nAdim %d: Ork_Legi'nin Saldirisi\n", adim);
        
        fprintf(file, "Saldiri Gucu Hesaplama (Bonuslar Dahil):\n");
        
        fprintf(file, "Ork Dovusculeri: %d Birim x %d Saldiri Gucu\nMizrakcilar: %d Birim x %d Saldiri Gucu\nVarg Binicileri: %d Birim x %d Saldiri Gucu\nTroller: %d Birim x %d Saldiri Gucu\n", 
                OU->ork_dovusculeri.sayi, OU->ork_dovusculeri.saldiri, OU->mizrakcilar.sayi, OU->mizrakcilar.saldiri, OU->varg_binicileri.sayi, OU->varg_binicileri.saldiri, OU->troller.sayi, OU->troller.saldiri);
        
        fprintf(file, "Toplam Saldiri Gucu: %d\n", toplam_ork_saldiri);
        
        fprintf(file, "Insan Imparatorlugu Toplam Savunma Gucu: %d\n", toplam_insan_savunma);
        
        double net_hasar_ork = ork_net_hasar_hesaplama(OU, &toplam_ork_saldiri, &toplam_insan_savunma);
        
        fprintf(file, "Ork irki insan birimlerine %.2f net hasar verdi.\n", net_hasar_ork);
        
        insan_saglik_hesapla(HU, net_hasar_ork, &toplam_insan_savunma);
        
        fprintf(file, "Saldırı Sonucunda:\n");
        fprintf(file, "Insan Piyadeleri: \n Sayi: %d\tSaglik: %d\n", HU->piyadeler.sayi, HU->piyadeler.saglik);
        fprintf(file, "Insan Okculari: \n Sayi: %d\tSaglik: %d\n", HU->okcular.sayi, HU->okcular.saglik);
        fprintf(file, "Insan Suvarileri: \n Sayi: %d\tSaglik: %d\n", HU->suvariler.sayi, HU->suvariler.saglik);
        fprintf(file, "Insan Kusatma Makineleri: \n Sayi: %d\tSaglik: %d\n", HU->kusatma_makineleri.sayi, HU->kusatma_makineleri.saglik);
        tur++;
    }

    if(adim % 2 == 1)
    {
        fprintf(file, "\nAdim %d: Insan_Imparatorlugu'nun Saldirisi\n", adim);
        
        fprintf(file, "Saldiri Gucu Hesaplama (Bonuslar Dahil):\n");
        
        fprintf(file, "Piyadeler: %d Birim x %d Saldiri Gucu\nOkcular: %d Birim x %d Saldiri Gucu\nSuvariler: %d Birim x %d Saldiri Gucu\nKusatma Makineleri: %d Birim x %d Saldiri Gucu\n", 
                HU->piyadeler.sayi, HU->piyadeler.saldiri, HU->okcular.sayi, HU->okcular.saldiri, HU->suvariler.sayi, HU->suvariler.saldiri, HU->kusatma_makineleri.sayi, HU->kusatma_makineleri.saldiri);
        fprintf(file, "Toplam Saldiri Gucu: %d\n", toplam_insan_saldiri);
        
        fprintf(file, "Ork Lejyonu Toplam Savunma Gucu: %d\n", toplam_ork_savunma);
        
        double net_hasar_insan = insan_net_hasar_hesaplama(HU, &toplam_insan_saldiri, &toplam_ork_savunma);
        
        fprintf(file, "Insan irki ork birimlerine %.2f net hasar verdi.\n", net_hasar_insan);
        
        ork_saglik_hesapla(OU, net_hasar_insan, &toplam_ork_savunma);
        
        fprintf(file, "Saldırı Sonucunda:\n");
        fprintf(file, "Ork Dovusculeri: \n Sayi: %d\tSaglik: %d\n", OU->ork_dovusculeri.sayi, OU->ork_dovusculeri.saglik);
        fprintf(file, "Ork Mizrakcilari: \n Sayi: %d\tSaglik: %d\n", OU->mizrakcilar.sayi, OU->mizrakcilar.saglik);
        fprintf(file, "Ork Varg Binicileri: \n Sayi: %d\tSaglik: %d\n", OU->varg_binicileri.sayi, OU->varg_binicileri.saglik);
        fprintf(file, "Ork Trolleri: \n Sayi: %d\tSaglik: %d\n\n", OU->troller.sayi, OU->troller.saglik);
    }

    if(tur % 5 == 0)
    {
        HU->piyadeler.saldiri *= 0.9;
        HU->piyadeler.savunma *= 0.9;
        
        HU->okcular.saldiri *= 0.9;
        HU->okcular.savunma *= 0.9;
        
        HU->suvariler.saldiri *= 0.9;
        HU->suvariler.savunma *= 0.9;
        
        HU->kusatma_makineleri.saldiri *= 0.9;
        HU->kusatma_makineleri.savunma *= 0.9;

        OU->ork_dovusculeri.saldiri *= 0.9;
        OU->ork_dovusculeri.savunma *= 0.9;
        
        OU->mizrakcilar.saldiri *= 0.9;
        OU->mizrakcilar.savunma *= 0.9;
        
        OU->varg_binicileri.saldiri *= 0.9;
        OU->varg_binicileri.savunma *= 0.9;
        
        OU->troller.saldiri *= 0.9;
        OU->troller.savunma *= 0.9;
    }

    // Eger insan birimlerinin sayilari 0'a ulastiysa savasi bitir
    if (HU->piyadeler.sayi <= 0 && HU->okcular.sayi <= 0 &&
            HU->suvariler.sayi <= 0 && HU->kusatma_makineleri.sayi <= 0)
    {
        fprintf(file, "Ork irki kazandi!\n");
        return;
    }

    // Eger ork birimlerinin sayilari 0'a ulastiysa savasi bitir
    if (OU->ork_dovusculeri.sayi <= 0 && OU->mizrakcilar.sayi <= 0 &&
            OU->varg_binicileri.sayi <= 0 && OU->troller.sayi <= 0)
    {
        fprintf(file, "Insan irki kazandi!\n\n");
        return;
    }

    fclose(file);
}

int main()
{

    int num;
    int adim = 1;
    printf("1-10 arasi sayi seciniz.\n");
    scanf("%d",&num);

    dosya_indir(num);

    parse_unit_json("unit_types.json", &HU, &OU);
    parse_hero_json("heroes.json", &HH, &OH);
    parse_creature_json("creatures.json", &HC, &OC);
    parse_research_json("research.json", &HR, &OR);

    read_ork_scenario("senaryo.json", &OU, &OH, &OC, &OR);
    read_human_scenario("senaryo.json", &HU, &HH, &HC, &HR);

    add_bonus_value(&HU, &OU, &HH, &OH, &HC, &OC, &HR, &OR);

	FILE *file = fopen("savas_sim.txt", "w");
	if (file == NULL)
    {
        printf("Dosya Acilamadi: %s\n", "savas_sim.txt");
        return 0;
    }
    fprintf(file, "Savas Oncesi Durum: \n");

	fclose(file);

	yazdir_human_unit("savas_sim.txt", &HU, &HC, &HH, &HR);
	yazdir_ork_unit("savas_sim.txt", &OU, &OC, &OH, &OR);

// Raylib başlat
    InitWindow(1000, 1000, "Savaş Simülasyonu");
    SetTargetFPS(60);

    // Başlangıç durumu
    SavasAlaniCiz(&HU, &OU);
    DrawText("Başlangıç Durumu", 50, 10, 20, BLACK);
    DrawText("Savaş başlatmak için bir tuşa basın...", 50, 30, 20, DARKGRAY);

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        // Başlangıç durumu
        SavasAlaniCiz(&HU, &OU);

        if (IsKeyPressed(KEY_SPACE)) { // Savaş için boşluk tuşuna bas

            while (!((HU.piyadeler.sayi == 0 && HU.okcular.sayi == 0 &&
           HU.suvariler.sayi == 0 && HU.kusatma_makineleri.sayi == 0) ||
          (OU.ork_dovusculeri.sayi == 0 && OU.mizrakcilar.sayi == 0 &&
           OU.varg_binicileri.sayi == 0 && OU.troller.sayi == 0))){

    		savas_adim_adim("savas_sim.txt", &HU, &OU, adim);
    		adim++;
           }
            ClearBackground(RAYWHITE);
            DrawText("Savaş Sonrası Durum", 50, 10, 20, BLACK);
            SavasAlaniCiz(&HU, &OU);
            DrawText("Son durumu görmek için herhangi bir tuşa basın...", 50, 30, 20, BLACK);
            while (!WindowShouldClose() && !IsKeyPressed(KEY_SPACE)) {
                // Son durumu bekler
                BeginDrawing();
                ClearBackground(RAYWHITE);
                DrawText("Savaş Sonrası Durum", 50, 10, 20, BLACK);
                SavasAlaniCiz(&HU, &OU);
                EndDrawing();
            }
            ClearBackground(RAYWHITE);
            DrawText("Son durum görüntülendi, çıkmak için bir tuşa basın...", 50, 30, 20, DARKGRAY);
        }

        EndDrawing();
    }

    CloseWindow(); // Pencereyi kapat

    return 0;
}
