# Hastane Acil Servis Sistemi

Bu proje, bir hastane acil servis sistemini simüle eden basit bir C uygulamasıdır. Proje, hasta kayıtları, öncelik sırası, reçete numarası üretimi ve muayene edilen hastaların yönetimi gibi temel işlevleri içermektedir.

## Özellikler

- **Hasta Kayıtları**: Hasta bilgileri, HL7 formatına uygun bir yapıda saklanır. Bu, hasta bilgilerini standart bir formatta saklamayı ve paylaşmayı kolaylaştırır.
- **Öncelik Sırası**: Hastalar, aciliyet durumlarına göre öncelik sırasına alınır. Bu, acil durumlarda hangi hastanın önce tedavi edileceğini belirlemeye yardımcı olur.
- **Reçete Numarası Üretimi**: Her hasta için benzersiz bir reçete numarası üretilir. Bu, reçetelerin takibini kolaylaştırır.
- **Muayene Edilen Hastalar**: Muayene edilen hastalar bir listede saklanır ve geçmiş muayeneler kolayca görüntülenebilir.

## Kurulum

1. Proje dosyalarını yerel makinenize klonlayın:
   ```bash
   git clone <repository-url>
   ```
2. Proje dizinine gidin:
   ```bash
   cd HastaneAcilServis
   ```
3. Derleyin:
   ```bash
   gcc -o hastane main.c
   ```
4. Uygulamayı çalıştırın:
   ```bash
   ./hastane
   ```

## Kullanım

- **Yeni Hasta Ekle**: Sisteme yeni bir hasta ekler.
- **Hastayı Muayene Et**: Sıradaki hastayı muayene eder ve bilgilerini gösterir.
- **Bekleyen Hastaları Listele**: Bekleyen hastaların listesini görüntüler.
- **Muayene Edilen Hastaları Listele**: Muayene edilen hastaların listesini görüntüler.
- **Çıkış**: Uygulamadan çıkar.
