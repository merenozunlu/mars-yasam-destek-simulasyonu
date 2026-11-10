# 🎥 Video Sunumu ve Teknik Anlatım Rehberi (Max 15 Dakika)

Ödev kriterlerine göre videoda **"şunu yaptım, bunu kullandım, böyle çıktı"** gibi yüzeysel ifadeler yerine **kodun teknik olarak nasıl çalıştığını** anlatman ve ardından programı çalıştırarak tüm komutları, geçersiz girişleri ve en az bir kaybetme senaryosunu göstermen gerekiyor.

Aşağıdaki akışı takip ederek videonu **8 - 10 dakika** içinde tam puan alacak şekilde çekebilirsin:

---

## BÖLÜM 1: Kod Mantığının Teknik Anlatımı (`main.c` üzerinden - Yaklaşık 4-5 dk)

Ekranda `main.c` dosyasını aç ve yukarıdan aşağıya doğru şu teknik noktaları göstererek anlat:

1. **Rastgelelik ve Durum Değişkenleri (Satır 19-35):**
   - *"Programın başında `srand((unsigned int)time(NULL))` fonksiyonu ile rastgele sayı üretecini zamana bağlı olarak başlatıyorum. Böylece her çalıştırmada `rand() % 100` ifadesi 0 ile 99 arasında farklı rastgele sayılar üretiyor."*
   - *"Durum yönetiminde sağlık, enerji, oksijen, su, yedek parça, modül hasarı, `kilitMuhurlu`, `gun` ve `tur` değişkenlerini `int` veri tipinde tanımladım."*

2. **Zorluk Seviyesi Seçimi (Satır 57-126):**
   - *"Zorluk seçimini `do-while` döngüsü içinde ayrı bir `switch-case` yapısıyla kurguladım. `case 'k': case 'K':` şeklinde **fall-through** yapısı kullanarak büyük/küçük harf duyarsızlığı sağladım. Seçilen zorluğa göre başlangıç suyu, keşif eşikleri ve kum fırtınasının tur sayısı değişiyor. Geçersiz bir harf girilirse `default` bloğu çalışıyor ve `zorlukGecerli == 0` kaldığı için döngü tekrar seçim istiyor."*

3. **Ana Komut Döngüsü ve Komutlar (`switch (komut)` - Satır 131-485):**
   - **`G` (Keşif Görevi - Satır 153-209):** *"Önce `if (enerji < 15)` ile kaynak kontrolü yapıyorum. Yeterliyse mantıksal VE (`&&`) operatörüyle `(enerji > 40 && oksijen > 30)` koşulunu kontrol ederek arama eşiğini belirliyorum. Enerjiyi 15, oksijeni 10 azaltıp `zar = rand() % 100` üretiyorum. Zar eşikten küçükse su bulma veya yedek parça bulma, büyükse eli boş dönme olmak üzere 3 farklı sonuç üretiliyor. Ayrıca `(zar < 10 || modulHasari > 70)` mantıksal VEYA (`||`) koşulu sağlanırsa oyuncu yaralanıyor ve sağlığı 10 azalıyor."*
   - **`O` (Oksijen Üretimi - Satır 214-273):** *"Girilen su miktarının çift mi tek mi olduğunu **mod (`%`) operatörü** ile `if (girilenSu % 2 == 0)` satırında kontrol ediyorum. Tek sayı girildiyse `kullanilanSu = girilenSu - 1` yaparak 1 birimi depoda artık olarak bırakıyorum ve `(kullanilanSu / 2) * 3` aritmetik formülüyle her 2 birim suyu 3 birim oksijene dönüştürüyorum."*
   - **`T` (Tamir - Satır 278-365):** *"Yedek parça yoksa işlemi iptal ediyorum. Varsa `if - else if - else` zinciri ile modül hasarını `<= 30` (hafif), `<= 70` (orta) ve `> 70` (ağır) olmak üzere 3 kademeye ayırıyorum; her kademede harcanan yedek parça ve onarılan hasar miktarı farklılaşıyor."*
   - **`D` (Durum Raporu - Satır 370-415):** *"Tüm değişkenleri ekrana yazdırıyorum. Kritik değerler için ayrı `if` bloklarıyla uyarı veriyorum. Tüm değerler güvenli aralıktaysa `&&` operatörüyle birleştirilmiş tek bir `if` koşuluyla `TUM SISTEMLER NORMAL` mesajını yazdırıyorum ve `turGecti = 0` bırakarak bu komutun tur harcamamasını sağlıyorum."*
   - **`U` (Dinlenme - Satır 420-458):** *"Burada **iç içe `if` (nested `if`)** yapısını kullandım. Dış `if` bloğunda enerjiyi artırırken, içteki `if (oksijen < 20)` kontrolüyle oksijen 20'nin altındaysa sağlığı artırmak yerine 10 azaltıyorum."*
   - **`K` (Kum Fırtınası - Satır 463-548):** *"Zorluk seviyesine göre belirlenen tur sayısı kadar çalışan bir **`for` döngüsü** kurdum. `if (i % 2 == 0)` ile çift numaralı turlarda hasar çarpanını 2 katına çıkarıyorum. Oksijen sızıntısı geldiğinde eğer hava kilidi önceden mühürlenmişse (`kilitMuhurlu == 1`) **`continue`** komutuyla o turdaki sızıntıyı atlıyorum. Eğer fırtına sırasında sağlık veya oksijen 0'a düşerse **`break`** komutuyla döngüyü derhal sonlandırıp fırtına özetini yazdırıyorum."*
   - **`H` (Hava Kilidi Şifresi - Satır 553-616):** *"Şifreyi o anki gün sayısından `dogruSifre = 'A' + (gun % 26)` aritmetik işlemiyle türetiyorum. **`do-while` döngüsü** içinde oyuncudan tahmin alıyorum; küçük harf girerse aritmetik olarak büyük harfe çeviriyorum. Yanlış tahminde enerjiyi 5 azaltıp alfabetik karşılaştırmayla 'İLERİ GİT' veya 'GERİ GİT' ipucu veriyorum. Döngü koşulunu `while (buyukGirilen != dogruSifre && kalanHak > 0)` şeklinde **tek bir mantıksal ifadeyle** kontrol ediyorum."*
   - **`default` Bloğu (Satır 632-637):** *"Tanımsız bir komut girildiğinde uyarı veriyor ve `turGecti = 0` olduğu için süre harcamıyor."*

4. **Sınırlandırma, Gün Akışı ve Oyun Sonu (Satır 643-736):**
   - *"Her komuttan sonra `if` yapılarıyla sağlık, enerji, oksijen ve modül hasarını 0-100 aralığında sınırlandırıyorum."*
   - *"Geçerli her komutta `tur` sayacını 1 artırıyorum ve `if (tur % 3 == 0)` koşuluyla her 3 turda bir günü 1 artırıp oksijeni 8 azaltıyorum; modül hasarı 70'in üzerindeyse sağlığı da 5 azaltıyorum."*
   - *"Oyun sonunda `(gun * 100) + saglik + oksijen - modulHasari` aritmetik formülüyle toplam puanı hesaplayıp sonuç raporunu yazdırıyorum."*

---

## BÖLÜM 2: Uygulamanın Çalıştırılması ve Senaryo Gösterimi (Yaklaşık 4-5 dk)

Terminali açıp `./mars_simulator.exe` programını çalıştır ve sırasıyla şunları canlı olarak göster:

1. **Geçersiz Zorluk ve Geçersiz Komut Gösterimi:**
   - Zorluk seçiminde önce `X` gir -> Uyarı verdiğini ve tekrar sorduğunu göster.
   - Ardından `N` (Normal) veya `Z` (Zor) seçerek oyuna başla.
   - Komut ekranında önce `X` gir -> Default bloğunun uyarı verdiğini ve `TUR: 0` kaldığını (tur harcamadığını) göster.
2. **Tüm Komutların Tek Tek Gösterimi:**
   - **`D`** gir -> Durum raporunu, `TUM SISTEMLER NORMAL` çıktısını ve turun hâlâ `0` kaldığını göster.
   - **`G`** gir -> Enerjinin 15, oksijenin 10 azaldığını, zar/eşik çıktısını ve bulunan su/parça sonucunu göster (`TUR: 1` oldu).
   - **`O`** gir -> Tek sayı (örneğin `3` veya `5`) su miktarı girerek mod (`%`) operatörünün 1 birimi depoda bıraktığını ve her 2 suyu 3 oksijene dönüştürdüğünü göster (`TUR: 2` oldu).
   - **`T`** gir -> Yedek parça harcanarak modül hasarının düştüğünü ve **3. tur tamamlandığı için (`3 % 3 == 0`) Yeni Gün (Gün 2) başladığını**, gün başında oksijenin 8 azaldığını göster.
   - **`H`** gir -> Gün 2 olduğu için şifrenin `'A' + 2 = 'C'` olduğunu söyle. Önce yanlış harf (`A`) girip `"ILERI GIT"` ipucunu ve enerjinin 5 azaldığını göster, sonra `c` (küçük harf) girerek kabul ettiğini ve `kilitMuhurlu = 1` olduğunu göster.
   - **`K`** gir -> Kum fırtınasının `for` döngüsüyle tur tur çalıştığını, çift turlarda (`2 % 2 == 0`) hasarın 2 katına çıktığını, hava kilidi mühürlü olduğu için oksijen sızıntısı gelirse `continue` ile atlandığını ve sonunda fırtına özetinin basıldığını göster.
   - **`U`** gir -> Enerji ve sağlığın arttığını, oksijenin 5 azaldığını göster.
3. **Kaybetme Senaryosu (Zorunlu):**
   - Arka arkaya **`K`** (Kum Fırtınası) ve **`G`** (Keşif) komutlarını çalıştırarak (enerji biterse `U` ile uyuyarak) oksijenin veya sağlığın `0`'a düşmesini sağla.
   - Ekranda `[OYUN BITTI - KAYBETTINIZ]` mesajının ve en alttaki **Simülasyon Sonuç Raporu** ile **Toplam Puan** hesabının çıktığını göstererek videoyu tamamla.
