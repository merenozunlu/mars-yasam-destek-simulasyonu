<div align="center">

# 🚀 Mars Kolonisi Yaşam Destek Simülatörü

**Mars'ta 15 gün hayatta kalmaya çalışan bir mühendisin kaynak ve kriz yönetimi simülasyonu**

![Language](https://img.shields.io/badge/Dil-C-00599C?style=for-the-badge&logo=c&logoColor=white)
![Standard](https://img.shields.io/badge/Standart-C99%20%2F%20C11-blue?style=for-the-badge)
![Platform](https://img.shields.io/badge/Platform-Konsol-lightgrey?style=for-the-badge&logo=windowsterminal&logoColor=white)
![Status](https://img.shields.io/badge/Durum-Tamamland%C4%B1-success?style=for-the-badge)

</div>

---

## 👤 Geliştirici

| | |
| :--- | :--- |
| **Ad Soyad** | Muammer Eren Üzümlü |
| **Öğrenci No** | 1260505013 |
| **Ders** | Algoritma ve Programlama |
| **Kütüphaneler** | `stdio.h`, `stdlib.h`, `time.h`, `locale.h` |

---

## 📖 Proje Hakkında

Mars'taki bir araştırma istasyonunda tek başına kalan bir mühendissiniz. Kurtarma ekibi **15 gün** sonra gelecek. O zamana kadar **sağlık, enerji, oksijen, su, yedek parça** ve **modül hasarını** dengede tutarak hayatta kalmanız gerekiyor.

Program, oyuncunun tek karakterlik komutlarına göre aritmetik ve mantıksal operatörlerle sonuç üretir; rastgele olaylar `srand(time(NULL))` ve `rand() % 100` ile simüle edilir. Her rastgele kontrolde **zar** ve **eşik** değeri ekrana yazdırılır.

### 🎯 Kazanma / Kaybetme

- ✅ **Kazanma:** 15. günü tamamlamak → kurtarma ekibi gelir.
- ❌ **Kaybetme:** Sağlık veya oksijen `0`'a düşerse.
- 🏆 **Puan:** `Puan = (gün × 100) + sağlık + oksijen − modülHasarı`

---

## 🎮 Komutlar

> Komutlar büyük/küçük harf duyarsızdır (`g` ve `G` aynıdır).

| Tuş | Komut | Açıklama | Tur Harcar mı? |
| :---: | :--- | :--- | :---: |
| `G` | 🔭 Keşif | Su veya yedek parça arar; yaralanma riski vardır. (15 enerji gerekir) | ✅ |
| `O` | 💨 Oksijen Üret | Her 2 birim su → 3 birim oksijen. Tek sayı girilirse 1 birim artar. | ✅ |
| `T` | 🔧 Tamir | Hasar kademesine (Hafif / Orta / Ağır) göre yedek parça harcar. | ✅ |
| `D` | 📊 Durum Raporu | Tüm değerleri ve kritik uyarıları gösterir. | ❌ |
| `U` | 😴 Uyu | Enerji ve sağlık yeniler (oksijen < 20 ise sağlık azalır!). | ✅ |
| `K` | 🌪️ Kum Fırtınası | Zorluğa göre 3/5/7 tur süren fırtına simülasyonu. | ✅ |
| `H` | 🔐 Hava Kilidi | Harf şifresini 3 denemede bul, kilidi mühürle. | ✅ |
| `Q` | 🚪 Çıkış | Oyunu bitirir ve sonuç raporunu gösterir. | ❌ |

⏱️ Her **3 geçerli turda** bir yeni gün başlar: `Oksijen −8`, modül hasarı 70'in üzerindeyse ayrıca `Sağlık −5`.

---

## ⚙️ Zorluk Seviyeleri

| Seviye | Sağlık | Enerji | Oksijen | Su | Parça | Başlangıç Hasarı | Fırtına Süresi |
| :--- | :---: | :---: | :---: | :---: | :---: | :---: | :---: |
| 🟢 **Kolay (K)** | 100 | 100 | 100 | 20 | 5 | 10 | 3 tur |
| 🟡 **Normal (N)** | 100 | 90 | 90 | 14 | 3 | 20 | 5 tur |
| 🔴 **Zor (Z)** | 90 | 80 | 85 | 8 | 2 | 35 | 7 tur |

---

## 🧠 Kullanılan C Yapıları

| Yapı | Kullanıldığı Yer | Açıklama |
| :--- | :--- | :--- |
| **Rastgele sayı** | Tüm komutlar | `srand(time(NULL))` + `rand() % 100`, zar/eşik karşılaştırması |
| **`switch-case` + `do-while`** | Zorluk seçimi | Geçersiz girişte seçim tekrarlanır |
| **Fall-through** | Ana komut `switch`'i | `case 'g': case 'G':` ile harf duyarsızlığı |
| **`&&` ve `\|\|`** | `[G]` Keşif | `(enerji > 40 && oksijen > 30)` eşik; `(zar < 10 \|\| modulHasari > 70)` yaralanma |
| **`%` (mod)** | `[O]` Oksijen, `[K]` Fırtına | Çift/tek su kontrolü; çift turlarda hasar ×2 |
| **`if – else if – else`** | `[T]` Tamir | 0-30 / 31-70 / 71-100 hasar kademeleri |
| **Birleşik `&&` koşulu** | `[D]` Durum | 5 koşul tek ifadede → `TÜM SİSTEMLER NORMAL` |
| **İç içe `if`** | `[U]` Uyku | Oksijen < 20 ise hipoksi, sağlık −10 |
| **`for` + `continue` + `break`** | `[K]` Kum Fırtınası | Mühürlü kilitte sızıntı `continue` ile atlanır; ölümde `break` |
| **`do-while` (tek mantıksal ifade)** | `[H]` Hava Kilidi | `while (buyukGirilen != dogruSifre && kalanHak > 0);` |
| **Karakter aritmetiği** | `[H]` Hava Kilidi | Şifre `'A' + (gun % 26)`, küçük → büyük harf dönüşümü |
| **Sınırlandırma** | Her tur sonu | Tüm değerler `0–100` aralığında tutulur |

---

## 🛠️ Derleme ve Çalıştırma

**Gereksinim:** GCC (MinGW / Linux / macOS) veya herhangi bir C99 uyumlu derleyici.

```bash
# Depoyu klonla
git clone https://github.com/merenozunlu/mars-yasam-destek-simulasyonu.git
cd mars-yasam-destek-simulasyonu

# Derle
gcc main.c -o mars_kolonisi

# Çalıştır (Windows)
mars_kolonisi.exe

# Çalıştır (Linux / macOS)
./mars_kolonisi
```

---

## 📁 Dosya Yapısı

```
📦 mars-yasam-destek-simulasyonu
 ┣ 📜 main.c                    → Simülatörün tüm kaynak kodu (detaylı yorumlarla)
 ┣ 📄 Proje_Raporu.pdf          → Proje raporu
 ┗ 📘 README.md                 → Bu dosya
```

---

<div align="center">

🔴 *"Mars'ta hayatta kalmak matematik meselesidir."* 🔴

</div>
