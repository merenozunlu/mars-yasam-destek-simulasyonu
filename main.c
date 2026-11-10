/*
 * ============================================================================
 * PROJE ADI    : KARAKTER TABANLI "MARS KOLONISI YASAM DESTEK SIMULATORU"
 * DOSYA ADI    : main.c
 * ACIKLAMA     : C dilinin temel yapilari (aritmetik ve mantiksal operatorler,
 *                IF-ELSE IF-ELSE zincirleri, fall-through ozellikli SWITCH-CASE,
 *                break/continue iceren FOR dongusu ve tek mantiksal kosullu
 *                DO-WHILE dongusu) kullanilarak gelistirilmis 15 gunluk
 *                Mars koloni hayatta kalma simulasyonu.
 * ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <locale.h>

int main(void) {
    /* Rastgele sayi ureteci baslatilir (Zorunlu: srand(time(NULL))) */
    srand((unsigned int)time(NULL));

    /* ========================================================================
     * 4. DURUM YONETIMI DEGISKENLERI
     * ======================================================================== */
    int saglik = 100;           /* Saglik (0-100) */
    int enerji = 100;           /* Enerji (0-100) */
    int oksijen = 100;          /* Oksijen (0-100) */
    int su = 10;                /* Su miktari (birim) */
    int yedekParca = 3;         /* Yedek parca sayisi */
    int modulHasari = 0;        /* Modul hasari (0-100) */
    int kilitMuhurlu = 0;       /* Hava kilidinin muhurlu olup olmadigi (0/1) */
    int gun = 1;                /* Gun sayisi (1'den baslar) */
    int tur = 0;                /* Gecerli komut (tur) sayaci */

    /* Zorluk seviyesine gore degisen parametreler */
    char zorlukSecimi = ' ';
    int zorlukGecerli = 0;
    int firtinaTuru = 5;        /* Kum firtinasi suresi (Kolay: 3, Normal: 5, Zor: 7) */
    int firtinaBazHasar = 8;    /* Zorluk seviyesine gore firtina siddeti */
    int kesifYuksekEsik = 75;   /* Enerji ve oksijen yuksekken kesif basari esigi */
    int kesifDusukEsik = 45;    /* Enerji veya oksijen dusukken kesif basari esigi */

    /* Komut ve oyun dongusu degiskenleri */
    char komut = ' ';
    int oyunDevam = 1;          /* 1: Oyun suruyor, 0: Oyun bitti */
    int turGecti = 0;           /* Gecerli komut girildiginde 1 olur (D ve gecersiz haric) */
    int zar = 0;                /* rand() % 100 ile uretilen rastgele sayi */
    int esik = 0;               /* Zar ile karsilastirilan esik deger */
    int puan = 0;               /* Oyun sonu puani */

    printf("====================================================================\n");
    printf("       MARS KOLONISI YASAM DESTEK SIMULATORUNE HOS GELDINIZ!        \n");
    printf("====================================================================\n");
    printf("Goreviniz: Mars'taki arastirma istasyonunda kurtarma ekibi gelene\n");
    printf("kadar 15 gun boyunca hayatta kalmak ve sistemleri calisir tutmak!\n\n");

    /* ========================================================================
     * ZORLUK SEVIYESI SECIMI (AyrI SWITCH-CASE ve Gecersiz Giris Kontrolu)
     * ======================================================================== */
    do {
        printf("Zorluk Seviyesi Seciniz:\n");
        printf("  [K] Kolay  (Bol kaynak, dusuk hasar, 3 turluk kum firtinasi)\n");
        printf("  [N] Normal (Dengeli kaynak, orta hasar, 5 turluk kum firtinasi)\n");
        printf("  [Z] Zor    (Az su ve parca, yuksek hasar, 7 turluk kum firtinasi)\n");
        printf("Seciminiz (K/N/Z): ");

        if (scanf(" %c", &zorlukSecimi) != 1) {
            break;
        }

        switch (zorlukSecimi) {
            case 'k':
            case 'K':
                saglik = 100;
                enerji = 100;
                oksijen = 100;
                su = 20;
                yedekParca = 5;
                modulHasari = 10;
                firtinaTuru = 3;
                firtinaBazHasar = 6;
                kesifYuksekEsik = 85;
                kesifDusukEsik = 60;
                zorlukGecerli = 1;
                printf("\n[BILGI] KOLAY zorluk seviyesi secildi. Baslangic suyu: %d, Firtina suresi: %d tur.\n", su, firtinaTuru);
                break;

            case 'n':
            case 'N':
                saglik = 100;
                enerji = 90;
                oksijen = 90;
                su = 14;
                yedekParca = 3;
                modulHasari = 20;
                firtinaTuru = 5;
                firtinaBazHasar = 8;
                kesifYuksekEsik = 75;
                kesifDusukEsik = 50;
                zorlukGecerli = 1;
                printf("\n[BILGI] NORMAL zorluk seviyesi secildi. Baslangic suyu: %d, Firtina suresi: %d tur.\n", su, firtinaTuru);
                break;

            case 'z':
            case 'Z':
                saglik = 90;
                enerji = 80;
                oksijen = 85;
                su = 8;
                yedekParca = 2;
                modulHasari = 35;
                firtinaTuru = 7;
                firtinaBazHasar = 10;
                kesifYuksekEsik = 65;
                kesifDusukEsik = 40;
                zorlukGecerli = 1;
                printf("\n[BILGI] ZOR zorluk seviyesi secildi. Baslangic suyu: %d, Firtina suresi: %d tur.\n", su, firtinaTuru);
                break;

            default:
                printf("\n[UYARI] Gecersiz zorluk seviyesi girdiniz! Lutfen K, N veya Z giriniz.\n\n");
                zorlukGecerli = 0;
                break;
        }
    } while (zorlukGecerli == 0);

    /* ========================================================================
     * ANA KOMUT DINLEME DONGUSU (DO-WHILE ZORUNLU)
     * ======================================================================== */
    do {
        turGecti = 0;

        printf("\n--------------------------------------------------------------------\n");
        printf("[GUN: %d/15 | TUR: %d] Saglik:%d | Enerji:%d | Oksijen:%d | Su:%d | Parca:%d | Hasar:%d | Kilit:%s\n",
               gun, tur, saglik, enerji, oksijen, su, yedekParca, modulHasari,
               (kilitMuhurlu == 1) ? "MUHURLU" : "ACIK");
        printf("--------------------------------------------------------------------\n");
        printf("Komutlar: [G] Kesif | [O] Oksijen Uret | [T] Tamir | [D] Durum Raporu\n");
        printf("          [U] Uyu   | [K] Kum Firtinasi| [H] Hava Kilidi | [Q] Cikis\n");
        printf("Komut giriniz: ");

        if (scanf(" %c", &komut) != 1) {
            break;
        }

        printf("\n");

        /* 1. KOMUT SISTEMI (SWITCH-CASE ve FALL-THROUGH ZORUNLU) */
        switch (komut) {

            /* ================================================================
             * [G] KESIF GOREVI
             * ================================================================ */
            case 'g':
            case 'G':
                /* Yetersiz kaynak kontrolu: Kesif icin en az 15 enerji gerekir */
                if (enerji < 15) {
                    printf("[IPTAL] Kesif gorevi icin yeterli enerjiniz yok! (Gereken: 15, Mevcut: %d)\n", enerji);
                    printf("        Lutfen once [U] komutu ile dinlenerek enerji toplayin.\n");
                } else {
                    printf(">>> [G] KESIF GOREVI BASLATILDI <<<\n");

                    /* Enerji ve oksijen durumuna gore basari esiginin belirlenmesi (Mantiksal && operatoru) */
                    if (enerji > 40 && oksijen > 30) {
                        esik = kesifYuksekEsik;
                        printf("Fiziksel kondisyonunuz iyi (Enerji > 40 && Oksijen > 30). Arama esigi yuksek: %d\n", esik);
                    } else {
                        esik = kesifDusukEsik;
                        printf("Yorgun veya oksijensizsiniz! Arama esigi dusuk: %d\n", esik);
                    }

                    /* Enerji 15, oksijen 10 azalir */
                    enerji = enerji - 15;
                    oksijen = oksijen - 10;
                    printf("Kesif eforu: Enerji -15, Oksijen -10 harcandi.\n");

                    /* Rastgele sayi uretimi ve esik karsilastirmasi */
                    zar = rand() % 100;
                    if (zar < esik) {
                        printf("Arama Sonucu -> Zar: %d / Esik: %d -> BASARILI\n", zar, esik);

                        /* En az 3 farkli sonuc icinden basarili olanlar: Su bulma veya Yedek parca bulma */
                        if (zar < (esik - 10)) {
                            int bulunanSu = 12 + (zar % 7); /* 12 ile 18 birim arasi su */
                            su = su + bulunanSu;
                            printf("[SONUC 1 - SU BULUNDU] Kesifte yeralti buz kutlesi buldunuz! +%d birim su eklendi. (Toplam Su: %d)\n", bulunanSu, su);
                        } else {
                            int bulunanParca = 1 + (zar % 2); /* 1 veya 2 adet yedek parca */
                            yedekParca = yedekParca + bulunanParca;
                            printf("[SONUC 2 - YEDEK PARCA BULUNDU] Eski kesif aracinin enkazindan +%d adet yedek parca topladiniz! (Toplam Parca: %d)\n", bulunanParca, yedekParca);
                        }
                    } else {
                        printf("Arama Sonucu -> Zar: %d / Esik: %d -> BASARISIZ\n", zar, esik);
                        printf("[SONUC 3 - ELI BOS DONME] Kayalik bolgede faydali hicbir kaynak bulamadiniz.\n");
                    }

                    /* Yaralanma kontrolu: (zar < 10 || modulHasari > 70) kosulu (Mantiksal || operatoru) */
                    if (zar < 10 || modulHasari > 70) {
                        printf("Tehlike Kontrolu -> Zar: %d / Esik: 10 (veya Modul Hasari: %d > 70) -> YARALANMA GERCEKLESTI!\n", zar, modulHasari);
                        saglik = saglik - 10;
                        printf("[HASAR] Kesif sirasinda kaza gecirdiniz ve yaralandiniz! Saglik -10 azaldi.\n");
                    } else {
                        printf("Tehlike Kontrolu -> Zar: %d / Esik: 10 -> GUVENLI (Yaralanma yok)\n", zar);
                    }

                    turGecti = 1;
                }
                break;

            /* ================================================================
             * [O] OKSIJEN URET
             * ================================================================ */
            case 'o':
            case 'O':
                /* Yetersiz kaynak kontrolu: Oksijen uretimi icin en az 10 enerji ve 2 birim su gerekir */
                if (enerji < 10) {
                    printf("[IPTAL] Elektroliz jenaratorunu calistirmak icin yeterli enerjiniz yok! (Gereken: 10, Mevcut: %d)\n", enerji);
                } else if (su < 2) {
                    printf("[IPTAL] Oksijen uretimi icin en az 2 birim suya ihtiyac var! (Mevcut Su: %d)\n", su);
                } else {
                    int girilenSu = 0;
                    printf(">>> [O] OKSIJEN URETIM SISTEMI <<<\n");
                    printf("Bilgi: Her 2 birim su, 3 birim oksijene donusur (Tek sayi girilirse 1 birimi depoda kalir).\n");
                    printf("Mevcut Su: %d | Mevcut Oksijen: %d/100\n", su, oksijen);
                    printf("Kullanilacak su miktarini giriniz: ");

                    if (scanf("%d", &girilenSu) != 1) {
                        girilenSu = 0;
                    }

                    if (girilenSu <= 0) {
                        printf("[IPTAL] Gecersiz su miktari girdiniz! Islem iptal edildi.\n");
                    } else if (girilenSu > su) {
                        printf("[IPTAL] Mevcut sudan fazla miktar girilemez! (Girilen: %d, Mevcut Su: %d)\n", girilenSu, su);
                    } else {
                        int kullanilanSu = 0;
                        int artikSu = 0;
                        int uretilenOksijen = 0;

                        /* Mod (%) operatoru ile cift/tek kontrolu (Zorunlu) */
                        if (girilenSu % 2 == 0) {
                            kullanilanSu = girilenSu;
                            artikSu = 0;
                            printf("Girilen su miktari (%d) CIFTTIR (%d %% 2 == 0). Tamami uretimde kullaniliyor.\n", girilenSu, girilenSu);
                        } else {
                            kullanilanSu = girilenSu - 1;
                            artikSu = 1;
                            printf("Girilen su miktari (%d) TEKTIR (%d %% 2 == 1). %d birimi kullanildi, %d birimi artik olarak depoda kaldi.\n",
                                   girilenSu, girilenSu, kullanilanSu, artikSu);
                        }

                        if (kullanilanSu == 0) {
                            printf("[IPTAL] 1 birim su tek basina oksijen uretimi icin yeterli degildir (En az 2 birim gerekir).\n");
                        } else {
                            /* Donusum aritmetik operatorlerle hesaplanir: Her 2 birim su -> 3 birim oksijen */
                            uretilenOksijen = (kullanilanSu / 2) * 3;
                            su = su - kullanilanSu;
                            enerji = enerji - 10;
                            oksijen = oksijen + uretilenOksijen;

                            /* Oksijen 100'u asmamalidir kontrolu */
                            if (oksijen > 100) {
                                oksijen = 100;
                            }

                            /* Her komut icin rastgele sayi ve esik gosterimi */
                            zar = rand() % 100;
                            esik = 20;
                            if (zar >= esik) {
                                printf("Verimlilik Kontrolu -> Zar: %d / Esik: %d -> BASARILI (Tam kapasite uretim)\n", zar, esik);
                            } else {
                                printf("Verimlilik Kontrolu -> Zar: %d / Esik: %d -> STANDART (Normal uretim)\n", zar, esik);
                            }

                            printf("[BASARILI] %d birim su harcandi -> +%d birim oksijen uretildi! (Enerji -10, Depoda Kalan Su: %d)\n",
                                   kullanilanSu, uretilenOksijen, su);
                            turGecti = 1;
                        }
                    }
                }
                break;

            /* ================================================================
             * [T] TAMIR
             * ================================================================ */
            case 't':
            case 'T':
                /* Yedek parca yoksa veya enerji yetersizse tamir yapilamaz */
                if (yedekParca <= 0) {
                    printf("[IPTAL] Yedek parcaniz yok! (Mevcut Parca: %d). Tamir yapilamaz.\n", yedekParca);
                } else if (enerji < 10) {
                    printf("[IPTAL] Tamir islemi icin yeterli enerjiniz yok! (Gereken: 10, Mevcut: %d)\n", enerji);
                } else if (modulHasari == 0) {
                    printf("[IPTAL] Istasyon modullerinde hicbir hasar yok (Hasar: 0). Tamire gerek duyulmadi.\n");
                } else {
                    printf(">>> [T] MODUL TAMIR ISLEMI <<<\n");

                    /* Hasar seviyesi IF-ELSE IF-ELSE zinciri ile en az uc kademeye ayrilir:
                     * 1-30 Hafif, 31-70 Orta, 71-100 Agir hasar */
                    if (modulHasari <= 30) {
                        /* Kademe 1: Hafif Hasar (0-30) -> 1 parca harcanir, 15 hasar onarilir */
                        int onarim = 15;
                        yedekParca = yedekParca - 1;
                        enerji = enerji - 10;
                        modulHasari = modulHasari - onarim;

                        zar = rand() % 100;
                        esik = 50;
                        if (zar < esik) {
                            printf("Kalibrasyon -> Zar: %d / Esik: %d -> BASARILI (+5 Bonus Onarim!)\n", zar, esik);
                            modulHasari = modulHasari - 5;
                            onarim = onarim + 5;
                        } else {
                            printf("Kalibrasyon -> Zar: %d / Esik: %d -> STANDART ONARIM\n", zar, esik);
                        }

                        printf("[HAFIF HASAR KADEMESI (0-30)] 1 yedek parca ve 10 enerji harcandi. Onarilan hasar: %d\n", onarim);
                        turGecti = 1;
                    } else if (modulHasari <= 70) {
                        /* Kademe 2: Orta Hasar (31-70) -> 2 parca varsa 2 parca ile 30 onarim, 1 parca varsa 1 parca ile 20 onarim */
                        int harcananParca = 1;
                        int onarim = 20;

                        if (yedekParca >= 2) {
                            harcananParca = 2;
                            onarim = 30;
                        }

                        yedekParca = yedekParca - harcananParca;
                        enerji = enerji - 10;
                        modulHasari = modulHasari - onarim;

                        zar = rand() % 100;
                        esik = 40;
                        if (zar < esik) {
                            printf("Kalibrasyon -> Zar: %d / Esik: %d -> BASARILI (+5 Bonus Onarim!)\n", zar, esik);
                            modulHasari = modulHasari - 5;
                            onarim = onarim + 5;
                        } else {
                            printf("Kalibrasyon -> Zar: %d / Esik: %d -> STANDART ONARIM\n", zar, esik);
                        }

                        printf("[ORTA HASAR KADEMESI (31-70)] %d yedek parca ve 10 enerji harcandi. Onarilan hasar: %d\n", harcananParca, onarim);
                        turGecti = 1;
                    } else {
                        /* Kademe 3: Agir Hasar (71-100) -> Mevcut parcalara gore kapsamli onarim */
                        int harcananParca = 1;
                        int onarim = 25;

                        if (yedekParca >= 3) {
                            harcananParca = 3;
                            onarim = 45;
                        } else if (yedekParca == 2) {
                            harcananParca = 2;
                            onarim = 35;
                        }

                        yedekParca = yedekParca - harcananParca;
                        enerji = enerji - 15;
                        modulHasari = modulHasari - onarim;

                        zar = rand() % 100;
                        esik = 30;
                        if (zar < esik) {
                            printf("Kalibrasyon -> Zar: %d / Esik: %d -> BASARILI (+5 Bonus Onarim!)\n", zar, esik);
                            modulHasari = modulHasari - 5;
                            onarim = onarim + 5;
                        } else {
                            printf("Kalibrasyon -> Zar: %d / Esik: %d -> STANDART ONARIM\n", zar, esik);
                        }

                        printf("[AGIR HASAR KADEMESI (71-100)] %d yedek parca ve 15 enerji harcandi. Onarilan hasar: %d\n", harcananParca, onarim);
                        turGecti = 1;
                    }
                }
                break;

            /* ================================================================
             * [D] DURUM RAPORU (Tur harcamaz!)
             * ================================================================ */
            case 'd':
            case 'D':
                printf("==================== ISTASYON DURUM RAPORU ====================\n");
                printf("  Gun Sayisi           : %d / 15\n", gun);
                printf("  Toplam Gecen Tur     : %d\n", tur);
                printf("  Saglik               : %d / 100\n", saglik);
                printf("  Enerji               : %d / 100\n", enerji);
                printf("  Oksijen              : %d / 100\n", oksijen);
                printf("  Su Miktari           : %d birim\n", su);
                printf("  Yedek Parca Sayisi   : %d adet\n", yedekParca);
                printf("  Modul Hasari         : %d / 100\n", modulHasari);
                printf("  Hava Kilidi Durumu   : %s (%d)\n", (kilitMuhurlu == 1) ? "MUHURLU" : "ACIK", kilitMuhurlu);
                printf("---------------------------------------------------------------\n");

                /* Sensor taramasi icin zar ve esik gosterimi */
                zar = rand() % 100;
                esik = 90;
                if (zar < esik) {
                    printf("Telemetri Taramasi -> Zar: %d / Esik: %d -> BASARILI\n", zar, esik);
                } else {
                    printf("Telemetri Taramasi -> Zar: %d / Esik: %d -> PARAZITLI SINYAL (Veriler dogrulandi)\n", zar, esik);
                }

                /* Kritik seviyedeki her deger icin ayri IF uyarilari */
                if (oksijen < 25) {
                    printf("  [KRITIK UYARI] Oksijen seviyesi kritik duzeyde (%d < 25)! Derhal [O] ile oksijen uretin!\n", oksijen);
                }
                if (saglik < 30) {
                    printf("  [KRITIK UYARI] Saglik durumu tehlikede (%d < 30)! Oksijen yeterli iken [U] ile dinlenin!\n", saglik);
                }
                if (modulHasari > 70) {
                    printf("  [KRITIK UYARI] Modul hasari cok yuksek (%d > 70)! [T] ile tamir yapmazsaniz saglik kaybedeceksiniz!\n", modulHasari);
                }
                if (enerji < 20) {
                    printf("  [KRITIK UYARI] Enerji seviyesi cok dusuk (%d < 20)! Komutlari calistirmak icin [U] ile uyuyun!\n", enerji);
                }
                if (su < 2) {
                    printf("  [KRITIK UYARI] Su rezervi tukenmek uzere (%d < 2)! [G] ile kesfe cikip su arayin!\n", su);
                }

                /* Tum degerler guvenli araliktaysa && ile birlestirilmis TEK BIR KOSULLA mesaj yazdirilir */
                if (oksijen >= 25 && saglik >= 30 && modulHasari <= 70 && enerji >= 20 && su >= 2) {
                    printf("  [SISTEM DURUMU] TUM SISTEMLER NORMAL\n");
                }
                printf("===============================================================\n");
                printf("(Bilgi: Durum raporu komutu tur/sure harcamamistir.)\n");
                turGecti = 0;
                break;

            /* ================================================================
             * [U] UYU / DINLEN
             * ================================================================ */
            case 'u':
            case 'U':
                printf(">>> [U] DINLENME VE UYKU MODU <<<\n");

                /* Rastgele sayi ve esik degerlendirmesi (Uyku kalitesi) */
                zar = rand() % 100;
                esik = 60;

                /* Ic ice IF (Nested IF) zorunlulugu:
                 * Enerji ve saglik artisi aritmetik islemlerle hesaplanir;
                 * ancak oksijen 20'nin altindaysa saglik artmaz, azalir! */
                if (enerji < 100 || saglik < 100) {
                    int enerjiArtisi = 25;
                    if (zar < esik) {
                        printf("Uyku Kalitesi -> Zar: %d / Esik: %d -> BASARILI (Derin Uyku: +30 Enerji)\n", zar, esik);
                        enerjiArtisi = 30;
                    } else {
                        printf("Uyku Kalitesi -> Zar: %d / Esik: %d -> NORMAL (Standart Uyku: +25 Enerji)\n", zar, esik);
                    }

                    enerji = enerji + enerjiArtisi;

                    /* Ic IF: Oksijen 20'nin altindaysa saglik artmaz, azalir */
                    if (oksijen < 20) {
                        saglik = saglik - 10;
                        printf("[TEHLIKE - IC ICE IF] Oksijen seviyesi 20'nin altinda (%d) oldugu icin uykuda hipoksi gecirdiniz!\n", oksijen);
                        printf("                      Saglik artmadi, aksine -10 AZALDI! Enerji +%d artti.\n", enerjiArtisi);
                    } else {
                        int saglikArtisi = 10 + (zar % 6);
                        saglik = saglik + saglikArtisi;
                        printf("[DINLENME] Yeterli oksijen altinda dinlendiniz. Enerji +%d, Saglik +%d artti.\n", enerjiArtisi, saglikArtisi);
                    }
                } else {
                    printf("Uyku Kalitesi -> Zar: %d / Esik: %d -> BASARILI\n", zar, esik);
                    if (oksijen < 20) {
                        saglik = saglik - 10;
                        printf("[TEHLIKE] Oksijen 20'nin altinda oldugu icin dinlenirken Saglik -10 azaldi!\n");
                    } else {
                        printf("[DINLENME] Enerji ve sagliginiz zaten tam kapasitede, dinlenerek vakit gecirdiniz.\n");
                    }
                }

                /* Uyurken oksijen tuketimi devam eder */
                oksijen = oksijen - 5;
                printf("Uyku suresince solunum nedeniyle Oksijen -5 tuketildi.\n");
                turGecti = 1;
                break;

            /* ================================================================
             * [K] KUM FIRTINASINI FOR DONGUSU ILE SIMULE ET
             * ================================================================ */
            case 'k':
            case 'K':
                if (enerji < 10) {
                    printf("[IPTAL] Kum firtinasi protokollerini yonetmek icin en az 10 enerji gerekir! (Mevcut: %d)\n", enerji);
                } else {
                    int i = 1;
                    int hasarAlinanTurSayisi = 0;
                    int toplamKaybedilenSaglik = 0;
                    int toplamKaybedilenOksijen = 0;

                    enerji = enerji - 10;
                    printf(">>> [K] KUM FIRTINASI SIMULASYONU BASLADI (%d Tur Surecek, Enerji -10) <<<\n", firtinaTuru);

                    /* FOR DONGUSU ZORUNLULUGU */
                    for (i = 1; i <= firtinaTuru; i++) {
                        int carpan = 1;
                        int anlikHasar = 0;

                        printf("\n  --- [Firtina Turu %d / %d] ---\n", i, firtinaTuru);

                        /* Cift numarali turlarda ruzgar siddetlenir ve hasar iki katina cikar (Mod % operatoru zorunlu) */
                        if (i % 2 == 0) {
                            carpan = 2;
                            printf("  [SIDDETLI RUZGAR] %d. tur cift numarali turdur (%d %% 2 == 0)! Ruzgar siddetlendi, hasar 2 katina cikti!\n", i, i);
                        }

                        /* Her turda rastgele sayi uretilir ve esik ile karsilastirilir */
                        zar = rand() % 100;
                        esik = 70;

                        if (zar < 25) {
                            /* Durum 1: Oksijen sizintisi olayi */
                            printf("  Firtina Olayi -> Zar: %d / Esik: 25 -> OKSIJEN SIZINTISI TEHLIKESI!\n", zar);

                            /* Hava kilidi daha once H komutuyla muhurlendiyse (kilitMuhurlu == 1) continue ile atlanir! */
                            if (kilitMuhurlu == 1) {
                                printf("  [KORUNMA - CONTINUE] Hava kilidi onceden muhurlendigi icin (kilitMuhurlu == 1) oksijen sizintisi bu tur ATLANDI!\n");
                                continue;
                            }

                            anlikHasar = firtinaBazHasar * carpan;
                            oksijen = oksijen - anlikHasar;
                            toplamKaybedilenOksijen = toplamKaybedilenOksijen + anlikHasar;
                            hasarAlinanTurSayisi = hasarAlinanTurSayisi + 1;
                            printf("  [SIZINTI] Hava kilidi acik! Istasyondan -%d birim oksijen sizdi!\n", anlikHasar);

                        } else if (zar < 50) {
                            /* Durum 2: Can kaybi (Saglik azalmasi) */
                            printf("  Firtina Olayi -> Zar: %d / Esik: 50 -> SAVRULAN ENKAZ CARPMASI!\n", zar);
                            anlikHasar = (firtinaBazHasar - 2) * carpan;
                            saglik = saglik - anlikHasar;
                            toplamKaybedilenSaglik = toplamKaybedilenSaglik + anlikHasar;
                            hasarAlinanTurSayisi = hasarAlinanTurSayisi + 1;
                            printf("  [YARALANMA] Basinc dalgasi nedeniyle yaralandiniz! Saglik -%d azaldi.\n", anlikHasar);

                        } else if (zar < esik) {
                            /* Durum 3: Modul hasari */
                            printf("  Firtina Olayi -> Zar: %d / Esik: %d -> DIS CEPHE HASARI!\n", zar, esik);
                            anlikHasar = firtinaBazHasar * carpan;
                            modulHasari = modulHasari + anlikHasar;
                            if (modulHasari > 100) {
                                modulHasari = 100;
                            }
                            hasarAlinanTurSayisi = hasarAlinanTurSayisi + 1;
                            printf("  [MODUL HASARI] Firtina gunes panellerini ve govdeyi vurdu! Modul Hasari +%d artti.\n", anlikHasar);

                        } else {
                            /* Durum 4: Firtinadan zararsiz korunma */
                            printf("  Firtina Olayi -> Zar: %d / Esik: %d -> BASARILI KORUNMA!\n", zar, esik);
                            printf("  [GUVENLI] Koruyucu kalkanlar bu turu hasarsiz atlatmanizi sagladi.\n");
                        }

                        /* Saglik veya oksijen 0'a duserse dongu BREAK ile derhal sonlandirilir (Zorunlu) */
                        if (saglik <= 0 || oksijen <= 0) {
                            if (saglik < 0) {
                                saglik = 0;
                            }
                            if (oksijen < 0) {
                                oksijen = 0;
                            }
                            printf("\n  [KRITIK DURUM - BREAK] Saglik (%d) veya Oksijen (%d) 0'a dustu! Firtina dongusu derhal sonlandiriliyor!\n",
                                   saglik, oksijen);
                            break;
                        }
                    }

                    /* Dongu sonunda firtina ozeti yazdirilir */
                    printf("\n  ================ KUM FIRTINASI OZETI ================\n");
                    printf("  Hasar Alinan Tur Sayisi   : %d tur\n", hasarAlinanTurSayisi);
                    printf("  Toplam Kaybedilen Saglik  : %d\n", toplamKaybedilenSaglik);
                    printf("  Toplam Kaybedilen Oksijen : %d\n", toplamKaybedilenOksijen);
                    printf("  Guncel Modul Hasari       : %d / 100\n", modulHasari);
                    printf("  =====================================================\n");

                    turGecti = 1;
                }
                break;

            /* ================================================================
             * [H] HAVA KILIDI SIFRESI (DO-WHILE DOGRULAMA DONGUSU ZORUNLU)
             * ================================================================ */
            case 'h':
            case 'H':
                if (kilitMuhurlu == 1) {
                    printf("[BILGI] Hava kilidi zaten muhurlu durumda (kilitMuhurlu == 1)!\n");
                } else if (enerji < 5) {
                    printf("[IPTAL] Hava kilidi terminalini calistirmak icin en az 5 enerji gerekir! (Mevcut: %d)\n", enerji);
                } else {
                    /* Sifre o anki gun sayisindan aritmetik olarak turetilir: sifre = 'A' + (gun % 26) */
                    char dogruSifre = (char)('A' + (gun % 26));
                    char girilenHarf = ' ';
                    char buyukGirilen = ' ';
                    int kalanHak = 3;

                    printf(">>> [H] HAVA KILIDI GUVENLIK TERMINALI <<<\n");

                    /* Rastgele sayi ve esik gosterimi */
                    zar = rand() % 100;
                    esik = 50;
                    if (zar < esik) {
                        printf("Terminal Baglantisi -> Zar: %d / Esik: %d -> BASARILI (Guvenli hat acildi)\n", zar, esik);
                    } else {
                        printf("Terminal Baglantisi -> Zar: %d / Esik: %d -> YEDEK HAT (Sifreleme aktif)\n", zar, esik);
                    }

                    printf("[IPUCU] Sifre, Ingiliz alfabesinde 'A' harfinden bugunun gun sayisi (%d) kadar ilerideki harftir.\n", gun % 26);
                    printf("        (Toplam 3 deneme hakkiniz vardir. Kucuk veya buyuk harf girebilirsiniz.)\n");

                    /* DO-WHILE DONGUSU ZORUNLULUGU:
                     * Dongu kosulu hem sifrenin yanlis olmasini hem de deneme hakkinin bitmemis olmasini
                     * TEK BIR MANTIKSAL IFADEDE (&&) kontrol etmelidir! */
                    do {
                        printf("\nHava kilidi sifresini giriniz (Kalan Hak: %d): ", kalanHak);
                        if (scanf(" %c", &girilenHarf) != 1) {
                            break;
                        }

                        /* Kucuk harf girisi de kabul edilmelidir (Aritmetik donusum) */
                        if (girilenHarf >= 'a' && girilenHarf <= 'z') {
                            buyukGirilen = (char)(girilenHarf - 'a' + 'A');
                        } else {
                            buyukGirilen = girilenHarf;
                        }

                        if (buyukGirilen == dogruSifre) {
                            kilitMuhurlu = 1;
                            printf("[BASARILI] Sifre dogru (%c)! Hava kilidi basariyla muhurlendi (kilitMuhurlu = 1).\n", dogruSifre);
                        } else {
                            kalanHak = kalanHak - 1;
                            enerji = enerji - 5;
                            if (enerji < 0) {
                                enerji = 0;
                            }

                            /* Girilen harf sifreden onceyse "ileri git", sonraysa "geri git" ipucu verilir */
                            if (buyukGirilen < dogruSifre) {
                                printf("[YANLIS] Enerji -5 azaldi. Ipucu: Alfabede ILERI GIT! (Girilen: %c)\n", buyukGirilen);
                            } else {
                                printf("[YANLIS] Enerji -5 azaldi. Ipucu: Alfabede GERI GIT! (Girilen: %c)\n", buyukGirilen);
                            }
                        }
                    } while (buyukGirilen != dogruSifre && kalanHak > 0);

                    /* 3 deneme de basarisiz olursa modul hasari 20 artar */
                    if (kilitMuhurlu == 0) {
                        modulHasari = modulHasari + 20;
                        printf("\n[BASARISIZ] 3 deneme hakkiniz da bitti! Dogru sifre '%c' idi.\n", dogruSifre);
                        printf("            Acil kilitlenme hatasi nedeniyle Modul Hasari +20 artti!\n");
                    }

                    turGecti = 1;
                }
                break;

            /* ================================================================
             * [Q] CIKIS
             * ================================================================ */
            case 'q':
            case 'Q':
                zar = rand() % 100;
                esik = 100;
                printf("Sistem Kapatma Onayi -> Zar: %d / Esik: %d -> BASARILI\n", zar, esik);
                printf("[CIKIS] Simulasyondan cikis komutu (Q) verildi. Sonuc raporu hazirlaniyor...\n");
                oyunDevam = 0;
                turGecti = 0;
                break;

            /* ================================================================
             * TANIMSIZ KOMUT (DEFAULT BLOGU - Tur harcamaz!)
             * ================================================================ */
            default:
                printf("[UYARI] Tanimsiz bir komut girdiniz ('%c')! Lutfen gecerli bir komut (G, O, T, D, U, K, H, Q) giriniz.\n", komut);
                printf("        (Gecersiz komutlar tur/sure harcamaz.)\n");
                turGecti = 0;
                break;
        }

        /* ====================================================================
         * SINIRLANDIRMA KONTROLLERI (0 - 100 Araligi, IF Yapilari ile Zorunlu)
         * ==================================================================== */
        if (saglik > 100) {
            saglik = 100;
        }
        if (saglik < 0) {
            saglik = 0;
        }

        if (enerji > 100) {
            enerji = 100;
        }
        if (enerji < 0) {
            enerji = 0;
        }

        if (oksijen > 100) {
            oksijen = 100;
        }
        if (oksijen < 0) {
            oksijen = 0;
        }

        if (modulHasari > 100) {
            modulHasari = 100;
        }
        if (modulHasari < 0) {
            modulHasari = 0;
        }

        /* ====================================================================
         * ZAMAN AKISI VE OYUN SONU KOSULLARI (Her turun sonunda kontrol edilir)
         * ==================================================================== */
        if (oyunDevam == 1) {
            /* Komut sirasinda saglik veya oksijen 0'a dustuyse oyun derhal kaybedilir */
            if (saglik <= 0 || oksijen <= 0) {
                printf("\n[OYUN BITTI - KAYBETTINIZ] Hayati degerleriniz tukendi (Saglik: %d, Oksijen: %d)!\n", saglik, oksijen);
                oyunDevam = 0;
            } else if (turGecti == 1) {
                /* Gecerli her komut tur sayacini 1 artirir (D ve tanimsiz komutlar haric) */
                tur = tur + 1;

                /* Her 3 turda bir (tur % 3 == 0) yeni bir gun baslar */
                if (tur % 3 == 0) {
                    /* 15. gun tamamlandiysa kurtarma ekibi gelir ve oyun kazanilIr */
                    if (gun >= 15) {
                        printf("\n====================================================================\n");
                        printf("[TEBRIKLER - KAZANDINIZ!] 15. gunu basariyla tamamladiniz!\n");
                        printf("Kurtarma ekibi Mars istasyonuna ulasti ve sizi guvenle tahliye etti!\n");
                        printf("====================================================================\n");
                        oyunDevam = 0;
                    } else {
                        gun = gun + 1;
                        printf("\n********************************************************************\n");
                        printf("[YENI GUN BASLADI -> GUN %d] (Toplam Tur: %d, %d %% 3 == 0)\n", gun, tur, tur);

                        /* Gun basinda oksijen 8 azalir */
                        oksijen = oksijen - 8;
                        printf("  -> Gunluk yasam destek tuketimi: Oksijen -8 azaldi.\n");

                        /* Modul hasari 70'in uzerindeyse ek olarak 5 saglik kaybedilir */
                        if (modulHasari > 70) {
                            saglik = saglik - 5;
                            printf("  -> [AGIR HASAR ETKISI] Modul hasari 70'in uzerinde (%d) oldugu icin ek olarak Saglik -5 azaldi!\n", modulHasari);
                        }

                        /* Yeni gunde hava kilidi sifresi degistigi icin güvenlik kilidi guncellenir */
                        if (kilitMuhurlu == 1) {
                            printf("  -> Hava kilidi muhuru aktif (kilitMuhurlu == 1).\n");
                        }
                        printf("********************************************************************\n");

                        /* Gun basi kesintileri sonrasi tekrar 0-100 sinirlandirma ve olum kontrolu */
                        if (oksijen < 0) {
                            oksijen = 0;
                        }
                        if (saglik < 0) {
                            saglik = 0;
                        }

                        if (saglik <= 0 || oksijen <= 0) {
                            printf("\n[OYUN BITTI - KAYBETTINIZ] Yeni gun baslangicindaki tuketim sonucu hayati degerleriniz 0'a dustu (Saglik: %d, Oksijen: %d)!\n",
                                   saglik, oksijen);
                            oyunDevam = 0;
                        }
                    }
                }
            }
        }

    } while (oyunDevam == 1);

    /* ========================================================================
     * OYUN SONU RAPORU VE PUAN HESAPLAMA (ZORUNLU FORMUL)
     * Puan = (gun * 100) + saglik + oksijen - modulHasari
     * ======================================================================== */
    puan = (gun * 100) + saglik + oksijen - modulHasari;

    printf("\n====================================================================\n");
    printf("                     SIMULASYON SONUC RAPORU                        \n");
    printf("====================================================================\n");
    if (komut == 'q' || komut == 'Q') {
        printf("  Bitis Nedeni         : Oyuncu Istegiyle Cikis (Q Komutu)\n");
    } else if (saglik <= 0 || oksijen <= 0) {
        printf("  Bitis Nedeni         : Hayati Degerlerin Tukenmesi (KAYBETME)\n");
    } else {
        printf("  Bitis Nedeni         : 15. Gun Tamamlandi - Kurtarma Ekibi Geldi (KAZANMA)\n");
    }
    printf("--------------------------------------------------------------------\n");
    printf("  Hayatta Kalinan Gun  : %d\n", gun);
    printf("  Toplam Gecen Tur     : %d\n", tur);
    printf("  Son Saglik Durumu    : %d / 100\n", saglik);
    printf("  Son Enerji Durumu    : %d / 100\n", enerji);
    printf("  Son Oksijen Durumu   : %d / 100\n", oksijen);
    printf("  Kalan Su Miktari     : %d birim\n", su);
    printf("  Kalan Yedek Parca    : %d adet\n", yedekParca);
    printf("  Son Modul Hasari     : %d / 100\n", modulHasari);
    printf("  Hava Kilidi Durumu   : %s (%d)\n", (kilitMuhurlu == 1) ? "MUHURLU" : "ACIK", kilitMuhurlu);
    printf("--------------------------------------------------------------------\n");
    printf("  Puan Hesabi          : (Gun x 100) + Saglik + Oksijen - ModulHasari\n");
    printf("  Hesaplama            : (%d x 100) + %d + %d - %d\n", gun, saglik, oksijen, modulHasari);
    printf("  TOPLAM PUANINIZ      : %d\n", puan);
    printf("====================================================================\n");

    return 0;
}
