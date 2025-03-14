#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

// Hasta oncelik seviyeleri
#define KRITIK 1
#define ORTA 2
#define NORMAL 3

// HL7 hasta bilgilerini tutacak yapi
struct Hasta {
    int hastaNo;
    char ad[50];
    char soyad[50];
    char dogumTarihi[20];
    char cinsiyet;
    char adres[100];
    char telefon[15];
    int oncelikSeviyesi;
    char sikayet[100];
    char receteNo[15];
    char kayitZamani[20];
    struct Hasta* next;
};

// Acil servis kuyrugu icin baslangic dugumu
struct Hasta* kuyrukBasi = NULL;

// Muayene edilen hastalar için baslangic dugumu
struct Hasta* muayeneEdilenBasi = NULL;

// Buffer'i temizleme fonksiyonu
void bufferTemizle() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Yeni hasta olusturma fonksiyonu
struct Hasta* yeniHastaOlustur() {
    static int hastaNumarasi = 1000;
    struct Hasta* yeniHasta = (struct Hasta*)malloc(sizeof(struct Hasta));
    
    printf("\nHasta Bilgileri:\n");
    printf("Ad: ");
    scanf("%49s", yeniHasta->ad);
    bufferTemizle();
    
    printf("Soyad: ");
    scanf("%49s", yeniHasta->soyad);
    bufferTemizle();
    
    do {
        printf("Dogum Tarihi (YYYYMMDD): ");
        scanf("%19s", yeniHasta->dogumTarihi);
        bufferTemizle();
        if (strlen(yeniHasta->dogumTarihi) != 8) {
            printf("Hata: Dogum tarihi 8 haneli olmali (YYYYMMDD)!\n");
        }
    } while (strlen(yeniHasta->dogumTarihi) != 8);
    
    do {
        printf("Cinsiyet (M/F): ");
        scanf("%c", &yeniHasta->cinsiyet);
        bufferTemizle();
        yeniHasta->cinsiyet = toupper(yeniHasta->cinsiyet);
        if (yeniHasta->cinsiyet != 'M' && yeniHasta->cinsiyet != 'F') {
            printf("Hata: Cinsiyet M veya F olmali!\n");
        }
    } while (yeniHasta->cinsiyet != 'M' && yeniHasta->cinsiyet != 'F');
    
    printf("Adres: ");
    fgets(yeniHasta->adres, sizeof(yeniHasta->adres), stdin);
    yeniHasta->adres[strcspn(yeniHasta->adres, "\n")] = 0; // Remove newline
    
    do {
        printf("Telefon (10 haneli): ");
        scanf("%14s", yeniHasta->telefon);
        bufferTemizle();
        if (strlen(yeniHasta->telefon) != 10) {
            printf("Hata: Telefon numarasi 10 haneli olmali!\n");
        }
    } while (strlen(yeniHasta->telefon) != 10);
    
    printf("Sikayet: ");
    fgets(yeniHasta->sikayet, sizeof(yeniHasta->sikayet), stdin);
    yeniHasta->sikayet[strcspn(yeniHasta->sikayet, "\n")] = 0; // Remove newline
    
    do {
        printf("\nOncelik Seviyesi Secin:\n");
        printf("1 - Kritik\n");
        printf("2 - Orta\n");
        printf("3 - Normal\n");
        printf("Seciminiz: ");
        if (scanf("%d", &yeniHasta->oncelikSeviyesi) != 1) {
            bufferTemizle();
            printf("Hata: Gecersiz giris!\n");
            continue;
        }
        bufferTemizle();
        if (yeniHasta->oncelikSeviyesi < 1 || yeniHasta->oncelikSeviyesi > 3) {
            printf("Hata: Oncelik seviyesi 1-3 arasinda olmali!\n");
        }
    } while (yeniHasta->oncelikSeviyesi < 1 || yeniHasta->oncelikSeviyesi > 3);
    
    yeniHasta->hastaNo = hastaNumarasi++;
    sprintf(yeniHasta->receteNo, "RX%d", rand() % 90000 + 10000);
    
    // Kayit zamanini ayarla
    time_t t = time(NULL);
    struct tm* tm_info = localtime(&t);
    strftime(yeniHasta->kayitZamani, 20, "%Y%m%d%H%M%S", tm_info);
    
    yeniHasta->next = NULL;
    
    return yeniHasta;
}

// Hastayi oncelik sirasina gore kuyruga ekleme
void hastaEkle(struct Hasta* yeniHasta) {
    if (kuyrukBasi == NULL || yeniHasta->oncelikSeviyesi < kuyrukBasi->oncelikSeviyesi) {
        yeniHasta->next = kuyrukBasi;
        kuyrukBasi = yeniHasta;
        return;
    }
    
    struct Hasta* current = kuyrukBasi;
    while (current->next != NULL && current->next->oncelikSeviyesi <= yeniHasta->oncelikSeviyesi) {
        current = current->next;
    }
    yeniHasta->next = current->next;
    current->next = yeniHasta;
}

// Muayene edilen hastayi listeye ekleme
void muayeneEdilenEkle(struct Hasta* muayeneEdilen) {
    muayeneEdilen->next = muayeneEdilenBasi;
    muayeneEdilenBasi = muayeneEdilen;
}

// Siradaki hastayi muayene etme (kuyruktan cikarma)
void hastaMuayene() {
    if (kuyrukBasi == NULL) {
        printf("Bekleyen hasta yok!\n");
        return;
    }
    
    struct Hasta* muayeneEdilen = kuyrukBasi;
    kuyrukBasi = kuyrukBasi->next;
    printf("Muayene edilen hasta: %s %s, Recete No: %s\n", muayeneEdilen->ad, muayeneEdilen->soyad, muayeneEdilen->receteNo);
    muayeneEdilenEkle(muayeneEdilen);
}

// Muayene edilen hastalari listeleme
void muayeneEdilenleriListele() {
    if (muayeneEdilenBasi == NULL) {
        printf("Muayene edilen hasta yok!\n");
        return;
    }
    
    struct Hasta* current = muayeneEdilenBasi;
    printf("\nMuayene Edilen Hastalar:\n");
    while (current != NULL) {
        printf("Hasta No: %d, Ad: %s %s, Recete No: %s\n", current->hastaNo, current->ad, current->soyad, current->receteNo);
        current = current->next;
    }
}

// Bekleyen hastalari listeleme
void hastalariListele() {
    if (kuyrukBasi == NULL) {
        printf("Bekleyen hasta yok!\n");
        return;
    }
    
    struct Hasta* current = kuyrukBasi;
    printf("\nBekleyen Hastalar:\n");
    while (current != NULL) {
        printf("Hasta No: %d, Ad: %s %s, Oncelik: %d\n", current->hastaNo, current->ad, current->soyad, current->oncelikSeviyesi);
        current = current->next;
    }
}

// Ana menu
void menuGoster() {
    printf("\n1. Yeni Hasta Ekle\n");
    printf("2. Hastayi Muayene Et\n");
    printf("3. Bekleyen Hastalari Listele\n");
    printf("4. Muayene Edilen Hastalari Listele\n");
    printf("5. Cikis\n");
}

int main() {
    srand(time(NULL)); // Recete numarasi icin rastgele sayi uretimi
    int secim;
    do {
        menuGoster();
        printf("Seciminiz: ");
        if (scanf("%d", &secim) != 1) {
            bufferTemizle();
            printf("Hata: Gecersiz giris!\n");
            continue;
        }
        bufferTemizle();
        switch (secim) {
            case 1:
                hastaEkle(yeniHastaOlustur());
                break;
            case 2:
                hastaMuayene();
                break;
            case 3:
                hastalariListele();
                break;
            case 4:
                muayeneEdilenleriListele();
                break;
            case 5:
                printf("Cikis yapiliyor...\n");
                break;
            default:
                printf("Hata: Gecersiz secim!\n");
        }
    } while (secim != 5);
    return 0;
}

