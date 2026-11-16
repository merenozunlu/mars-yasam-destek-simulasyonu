<div align="center">

# ğŸš€ Mars Kolonisi YaÅŸam Destek SimÃ¼latÃ¶rÃ¼

**Mars'ta 15 gÃ¼n hayatta kalmaya Ã§alÄ±ÅŸan bir mÃ¼hendisin kaynak ve kriz yÃ¶netimi simÃ¼lasyonu**

![Language](https://img.shields.io/badge/Dil-C-00599C?style=for-the-badge&logo=c&logoColor=white)
![Standard](https://img.shields.io/badge/Standart-C99%20%2F%20C11-blue?style=for-the-badge)
![Platform](https://img.shields.io/badge/Platform-Konsol-lightgrey?style=for-the-badge&logo=windowsterminal&logoColor=white)
![Status](https://img.shields.io/badge/Durum-Tamamland%C4%B1-success?style=for-the-badge)

</div>

---

## ğŸ‘¤ GeliÅŸtirici

| | |
| :--- | :--- |
| **Ad Soyad** | Muammer Eren ÃœzÃ¼mlÃ¼ |
| **Ã–ÄŸrenci No** | 1260505013 |
| **Ders** | Algoritma ve Programlama |
| **KÃ¼tÃ¼phaneler** | `stdio.h`, `stdlib.h`, `time.h`, `locale.h` |

---

## ğŸ“– Proje HakkÄ±nda

Mars'taki bir araÅŸtÄ±rma istasyonunda tek baÅŸÄ±na kalan bir mÃ¼hendissiniz. Kurtarma ekibi **15 gÃ¼n** sonra gelecek. O zamana kadar **saÄŸlÄ±k, enerji, oksijen, su, yedek parÃ§a** ve **modÃ¼l hasarÄ±nÄ±** dengede tutarak hayatta kalmanÄ±z gerekiyor.

Program, oyuncunun tek karakterlik komutlarÄ±na gÃ¶re aritmetik ve mantÄ±ksal operatÃ¶rlerle sonuÃ§ Ã¼retir; rastgele olaylar `srand(time(NULL))` ve `rand() % 100` ile simÃ¼le edilir. Her rastgele kontrolde **zar** ve **eÅŸik** deÄŸeri ekrana yazdÄ±rÄ±lÄ±r.

### ğŸ¯ Kazanma / Kaybetme

- âœ… **Kazanma:** 15. gÃ¼nÃ¼ tamamlamak â†’ kurtarma ekibi gelir.
- âŒ **Kaybetme:** SaÄŸlÄ±k veya oksijen `0`'a dÃ¼ÅŸerse.
- ğŸ† **Puan:** `Puan = (gÃ¼n Ã— 100) + saÄŸlÄ±k + oksijen âˆ’ modÃ¼lHasarÄ±`

---

## ğŸ® Komutlar

> Komutlar bÃ¼yÃ¼k/kÃ¼Ã§Ã¼k harf duyarsÄ±zdÄ±r (`g` ve `G` aynÄ±dÄ±r).

| TuÅŸ | Komut | AÃ§Ä±klama | Tur Harcar mÄ±? |
| :---: | :--- | :--- | :---: |
| `G` | ğŸ”­ KeÅŸif | Su veya yedek parÃ§a arar; yaralanma riski vardÄ±r. (15 enerji gerekir) | âœ… |
| `O` | ğŸ’¨ Oksijen Ãœret | Her 2 birim su â†’ 3 birim oksijen. Tek sayÄ± girilirse 1 birim artar. | âœ… |
| `T` | ğŸ”§ Tamir | Hasar kademesine (Hafif / Orta / AÄŸÄ±r) gÃ¶re yedek parÃ§a harcar. | âœ… |
| `D` | ğŸ“Š Durum Raporu | TÃ¼m deÄŸerleri ve kritik uyarÄ±larÄ± gÃ¶sterir. | âŒ |
| `U` | ğŸ˜´ Uyu | Enerji ve saÄŸlÄ±k yeniler (oksijen < 20 ise saÄŸlÄ±k azalÄ±r!). | âœ… |
| `K` | ğŸŒªï¸ Kum FÄ±rtÄ±nasÄ± | ZorluÄŸa gÃ¶re 3/5/7 tur sÃ¼ren fÄ±rtÄ±na simÃ¼lasyonu. | âœ… |
| `H` | ğŸ” Hava Kilidi | Harf ÅŸifresini 3 denemede bul, kilidi mÃ¼hÃ¼rle. | âœ… |
| `Q` | ğŸšª Ã‡Ä±kÄ±ÅŸ | Oyunu bitirir ve sonuÃ§ raporunu gÃ¶sterir. | âŒ |

â±ï¸ Her **3 geÃ§erli turda** bir yeni gÃ¼n baÅŸlar: `Oksijen âˆ’8`, modÃ¼l hasarÄ± 70'in Ã¼zerindeyse ayrÄ±ca `SaÄŸlÄ±k âˆ’5`.

---

## âš™ï¸ Zorluk Seviyeleri

| Seviye | SaÄŸlÄ±k | Enerji | Oksijen | Su | ParÃ§a | BaÅŸlangÄ±Ã§ HasarÄ± | FÄ±rtÄ±na SÃ¼resi |
| :--- | :---: | :---: | :---: | :---: | :---: | :---: | :---: |
| ğŸŸ¢ **Kolay (K)** | 100 | 100 | 100 | 20 | 5 | 10 | 3 tur |
| ğŸŸ¡ **Normal (N)** | 100 | 90 | 90 | 14 | 3 | 20 | 5 tur |
| ğŸ”´ **Zor (Z)** | 90 | 80 | 85 | 8 | 2 | 35 | 7 tur |

---

## ğŸ§  KullanÄ±lan C YapÄ±larÄ±

| YapÄ± | KullanÄ±ldÄ±ÄŸÄ± Yer | AÃ§Ä±klama |
| :--- | :--- | :--- |
| **Rastgele sayÄ±** | TÃ¼m komutlar | `srand(time(NULL))` + `rand() % 100`, zar/eÅŸik karÅŸÄ±laÅŸtÄ±rmasÄ± |
| **`switch-case` + `do-while`** | Zorluk seÃ§imi | GeÃ§ersiz giriÅŸte seÃ§im tekrarlanÄ±r |
| **Fall-through** | Ana komut `switch`'i | `case 'g': case 'G':` ile harf duyarsÄ±zlÄ±ÄŸÄ± |
| **`&&` ve `\|\|`** | `[G]` KeÅŸif | `(enerji > 40 && oksijen > 30)` eÅŸik; `(zar < 10 \|\| modulHasari > 70)` yaralanma |
| **`%` (mod)** | `[O]` Oksijen, `[K]` FÄ±rtÄ±na | Ã‡ift/tek su kontrolÃ¼; Ã§ift turlarda hasar Ã—2 |
| **`if â€“ else if â€“ else`** | `[T]` Tamir | 0-30 / 31-70 / 71-100 hasar kademeleri |
| **BirleÅŸik `&&` koÅŸulu** | `[D]` Durum | 5 koÅŸul tek ifadede â†’ `TÃœM SÄ°STEMLER NORMAL` |
| **Ä°Ã§ iÃ§e `if`** | `[U]` Uyku | Oksijen < 20 ise hipoksi, saÄŸlÄ±k âˆ’10 |
| **`for` + `continue` + `break`** | `[K]` Kum FÄ±rtÄ±nasÄ± | MÃ¼hÃ¼rlÃ¼ kilitte sÄ±zÄ±ntÄ± `continue` ile atlanÄ±r; Ã¶lÃ¼mde `break` |
| **`do-while` (tek mantÄ±ksal ifade)** | `[H]` Hava Kilidi | `while (buyukGirilen != dogruSifre && kalanHak > 0);` |
| **Karakter aritmetiÄŸi** | `[H]` Hava Kilidi | Åifre `'A' + (gun % 26)`, kÃ¼Ã§Ã¼k â†’ bÃ¼yÃ¼k harf dÃ¶nÃ¼ÅŸÃ¼mÃ¼ |
| **SÄ±nÄ±rlandÄ±rma** | Her tur sonu | TÃ¼m deÄŸerler `0â€“100` aralÄ±ÄŸÄ±nda tutulur |

---

## ğŸ› ï¸ Derleme ve Ã‡alÄ±ÅŸtÄ±rma

**Gereksinim:** GCC (MinGW / Linux / macOS) veya herhangi bir C99 uyumlu derleyici.

```bash
# Depoyu klonla
git clone <repo-url>
cd <repo-klasoru>

# Derle
gcc main.c -o mars_kolonisi

# Ã‡alÄ±ÅŸtÄ±r (Windows)
mars_kolonisi.exe

# Ã‡alÄ±ÅŸtÄ±r (Linux / macOS)
./mars_kolonisi
```

---

## ğŸ“ Dosya YapÄ±sÄ±

```
ğŸ“¦ mars-kolonisi
 â”£ ğŸ“œ main.c                    â†’ SimÃ¼latÃ¶rÃ¼n tÃ¼m kaynak kodu (detaylÄ± yorumlarla)
 â”£ ğŸ“„ Proje_Raporu.pdf          â†’ Proje raporu
 â”— ğŸ“˜ README.md                 â†’ Bu dosya
```

---

<div align="center">

ğŸ”´ *"Mars'ta hayatta kalmak matematik meselesidir."* ğŸ”´

</div>
