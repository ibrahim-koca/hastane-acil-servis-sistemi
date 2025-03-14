# Proje Analiz Dökümanı

## Giriş

Bu döküman, Hastane Acil Servis Sistemi projesinin tasarımını, işleyişini ve kullanılan teknolojileri detaylandırmaktadır. Proje, hasta kayıtları, öncelik sırası, reçete numarası üretimi ve muayene edilen hastaların yönetimi gibi temel işlevleri içermektedir.

## Proje Amacı

Projenin amacı, bir hastane acil servis sisteminin temel işlevlerini simüle eden bir uygulama geliştirmektir. Bu uygulama, hasta kayıtlarının HL7 formatında saklanmasını, hastaların aciliyet durumlarına göre öncelik sırasına alınmasını ve muayene edilen hastaların yönetimini sağlamaktadır.

## Tasarım

### Veri Yapıları

- **Hasta Yapısı**: Hasta bilgilerini saklamak için bir yapı kullanılmıştır. Bu yapı, hastanın adı, soyadı, doğum tarihi, cinsiyeti, adresi, telefonu, aciliyet durumu, şikayeti ve reçete numarasını içermektedir.

### Algoritmalar

- **Öncelik Sırası**: Hastalar, aciliyet durumlarına göre bir öncelik sırasına alınmaktadır. Bu, acil durumlarda hangi hastanın önce tedavi edileceğini belirlemeye yardımcı olur.
- **Reçete Numarası Üretimi**: Her hasta için benzersiz bir reçete numarası üretilmektedir.

## İşleyiş

1. **Hasta Kaydı**: Kullanıcı, hasta bilgilerini girer ve sistem bu bilgileri HL7 formatında saklar.
2. **Öncelik Sırası Belirleme**: Hastalar, aciliyet durumlarına göre sıralanır.
3. **Muayene Etme**: Sıradaki hasta muayene edilir ve reçete numarası oluşturulur.
4. **Muayene Edilen Hastaları Listeleme**: Muayene edilen hastalar listelenir.
5. **Bekleyen Hastaları Listeleme**: Bekleyen hastalar listelenir.

## Sonuç

Bu proje, temel bir hastane acil servis sisteminin işleyişini simüle etmektedir. Gelecekteki geliştirmeler, daha karmaşık HL7 mesajları ve kullanıcı arayüzü iyileştirmelerini içerebilir. Proje, yazılım mühendisliği öğrencileri için pratik bir öğrenme deneyimi sunmaktadır.
