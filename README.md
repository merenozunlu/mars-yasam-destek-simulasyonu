# 🚀 Karakter Tabanlı Mars Kolonisi Yaşam Destek Simülatörü

C programlama dilinin temel yapıları (aritmetik ve mantıksal operatörler, `if-else if-else` karar yapıları, `fall-through` özellikli `switch-case`, `break` ve `continue` içeren `for` döngüsü ve birleşik koşullu `do-while` döngüleri) kullanılarak geliştirilmiş metin tabanlı bir hayatta kalma ve kaynak yönetimi simülasyonudur.

---

## 📌 Proje Amacı ve Senaryo

Oyuncu, Mars'taki küçük bir araştırma istasyonunda tek başına kalmış bir mühendisi yönetir ve kurtarma ekibi gelene kadar **15 gün boyunca** hayatta kalmaya çalışır. Simülasyon boyunca oyuncunun **sağlık, enerji, oksijen, su, yedek parça, modül hasarı, hava kilidi mührü, gün ve tur** değerleri dinamik olarak takip edilir.

---

## ⚙️ Zorunlu Teknik Özellikler ve Mimari

1. **Rastgelelik ve Eşik Sistemi (`srand` & `rand`)**:
   - Program başında `srand((unsigned int)time(NULL))` ile rastgele sayı üreteci başlatılır.
   - Rastgelelik gerektiren tüm durumlarda `rand() % 100` kullanılır ve üretilen zar ile eşik değeri ekrana açıkça yazdırılır (`Zar: 37 / Esik: 45 -> BASARILI`).
2. **Zorluk Seviyesi Seçimi (`SWITCH-CASE` & `DO-WHILE`)**:
   - Oyun başında **Kolay (`K`)**, **Normal (`N`)** veya **Zor (`Z`)** seviyelerinden biri seçilir.
   - Seçilen zorluk seviyesi; başlangıç kaynaklarını, keşif başarı eşiklerini ve kum fırtınasının tur sayısı ile hasar şiddetini doğrudan değiştirir. Geçersiz girişlerde seçim tekrar istenir.
3. **Büyük/Küçük Harf Duyarsız Komut Sistemi (`Fall-Through SWITCH-CASE`)**:
   - Tüm komutlar `case 'g': case 'G':` şeklinde `fall-through` yapısıyla kontrol edilir.
   - Tanımsız bir komut girildiğinde `default` bloğu uyarı verir ve **tur/süre harcamaz**.

---

## 🎮 Komut Tablosu ve İşlevleri

| Komut | İşlev | Kullanılan C Yapıları ve Kurallar |
| :---: | :--- | :--- |
| **`G`** | **Keşif Görevi** | Enerji `15`, oksijen `10` azalır. `(enerji > 40 && oksijen > 30)` ise su/parça bulma eşiği yüksek, aksi halde düşüktür. En az 3 farklı sonuç üretir (su bulma, yedek parça bulma, eli boş dönme). `(zar < 10 \|\| modulHasari > 70)` ise oyuncu yaralanır ve `-10` sağlık kaybeder. |
| **`O`** | **Oksijen Üret** | Her **2 birim su, 3 birim oksijene** dönüşür. Girilen su miktarı mod (`%`) operatörü ile kontrol edilir (`girilenSu % 2 == 0`); çiftse tamamı kullanılır, tekse `1` birimi depoda artık olarak kalır. Mevcut sudan fazla miktar girilemez. |
| **`T`** | **Tamir** | Yedek parça yoksa tamir yapılamaz. Modül hasarı `if - else if - else` zinciriyle 3 kademeye ayrılır: **0-30 Hafif**, **31-70 Orta**, **71-100 Ağır**. Her kademede harcanan yedek parça ve onarılan hasar miktarı farklıdır. |
| **`D`** | **Durum Raporu** | Tüm değişkenleri listeler. Kritik seviyedeki değerler (`oksijen < 25`, `saglik < 30`, `modulHasari > 70` vb.) için ayrı uyarılar verir. Tüm değerler güvenli aralıktaysa `&&` ile birleştirilmiş **tek bir koşulla** `"TUM SISTEMLER NORMAL"` mesajı yazdırır. **Tur harcamaz.** |
| **`U`** | **Uyu / Dinlen** | Enerji ve sağlık artışı aritmetik işlemlerle hesaplanır; oksijen `-5` tüketilir. **İç içe `IF` (Nested `IF`)** ile kontrol edilir: Oksijen `20`'nin altındaysa sağlık artmaz, aksine `-10` azalır. |
| **`K`** | **Kum Fırtınası** | `for` döngüsü ile simüle edilir (Kolay: 3, Normal: 5, Zor: 7 tur). Çift numaralı turlarda (`i % 2 == 0`) rüzgar şiddetlenir ve hasar **2 katına** çıkar. Hava kilidi mühürlüyse (`kilitMuhurlu == 1`) oksijen sızıntısı `continue` ile atlanır. Sağlık veya oksijen `0`'a düşerse döngü `break` ile derhal sonlandırılır. |
| **`H`** | **Hava Kilidi Şifresi** | `do-while` doğrulama döngüsü ile çalışır. Şifre o anki gün sayısından aritmetik olarak türetilir: `sifre = 'A' + (gun % 26)`. En fazla **3 deneme hakkı** vardır. Döngü koşulu `(buyukGirilen != dogruSifre && kalanHak > 0)` şeklinde tek bir mantıksal ifadeyle kontrol edilir. Yanlış denemede enerji `-5` azalır ve `"ileri git"` / `"geri git"` ipucu verilir. 3 deneme de başarısız olursa modül hasarı `+20` artar. |
| **`Q`** | **Çıkış** | Simülasyonu sonlandırır ve sonuç raporunu ekrana yazdırır. |

---

## ⏳ Zaman Akışı ve Oyun Sonu Koşulları

- **Tur ve Gün Geçişi**: Geçerli her komut (`D` ve tanımsız komutlar hariç) tur sayacını `1` artırır. Her **3 turda bir (`tur % 3 == 0`)** yeni bir gün başlar. Gün başında oksijen `8` azalır; modül hasarı `70`'in üzerindeyse ek olarak `5` sağlık kaybedilir.
- **Sınırlandırma (`0 - 100`)**: Sağlık, enerji, oksijen ve modül hasarı her komuttan sonra `if` kontrolleriyle `0` ile `100` aralığında sınırlandırılır.
- **Kazanma / Kaybetme ve Puan Formülü**:
  - Sağlık veya oksijen `0`'a düşerse oyun kaybedilir.
  - `15.` gün tamamlanırsa kurtarma ekibi gelir ve oyun kazanılır.
  - Oyun sonunda aşağıdaki aritmetik formülle toplam puan hesaplanır:
    $$\text{Puan} = (\text{gun} \times 100) + \text{saglik} + \text{oksijen} - \text{modulHasari}$$

---

## 🛠️ Derleme ve Çalıştırma

Projeyi herhangi bir standart C derleyicisi (`gcc`, `clang`, Dev-C++ vb.) ile derleyip çalıştırabilirsiniz:

```bash
gcc -Wall -Wextra -pedantic main.c -o mars_simulator.exe
./mars_simulator.exe
```

---

## 📂 Proje Dosyaları

- `main.c`: Simülasyonun tüm gereksinimlerini içeren C kaynak kodu.
- `Proje_Raporu.pdf`: Kod mantığını, kullanılan C yapılarını ve örnek simülasyon çıktılarını açıklayan teknik proje raporu.
- `VIDEO_ANLATIM_REHBERI.md`: Video sunumu sırasında adım adım anlatılacak teknik detaylar ve senaryo akışı.

---

## 🔗 GitHub Deposu

- **GitHub Linki**: [https://github.com/merenozunlu/mars-yasam-destek-simulasyonu](https://github.com/merenozunlu/mars-yasam-destek-simulasyonu)
