#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct Kullanici {
    char isim[50];
    char soyisim[50];
    char tcKimlik[50];
};

struct Hesap {
    int hesapNo;
    float bakiye;
    int hesapDurumu; 
    char işlemGeçmisi[500]; 
};

struct Kullanici kullanici;
struct Hesap hesaplar[100];
int hesapSayisi = 0;

// Döviz kurları
const float DOLAR_KURU = 35.0;
const float EURO_KURU = 37.0;
const float ALTIN_KURU = 3000.0;

void anaMenu();
void dosyayaKaydet();
void dosyadanYukle();
int hesapNoKontrol(int hesapNo);
void devamEtmeSecenegi();
void yeniHesapAc();
void hesapKapat();
void bakiyeSorgula();
void paraYatir();
void paraCek();
void faizHesapla();
void yoneticiKontrol();
void dovizIslemleri();  

int main() {
    dosyadanYukle();

    int secim;
    while (1) {
        anaMenu();
        printf("Seçiminizi yapın: ");
        scanf("%d", &secim);

        switch (secim) {
            case 1: 
                yeniHesapAc(); 
                break;
            case 2: 
                hesapKapat(); 
                break;
            case 3: 
                bakiyeSorgula(); 
                break;
            case 4: 
                paraYatir(); 
                break;
            case 5: 
                paraCek(); 
                break;
            case 6: 
                faizHesapla(); 
                break;
            case 7:
                yoneticiKontrol();
                break;
            case 8: 
                dovizIslemleri();  
                break;
            case 9: 
                dosyayaKaydet();
                printf("Çıkılıyor...\n");
                printf("Bizi kullandığınız için teşekkür ederiz.\n");
                return 0;
            default: 
                printf("Geçersiz seçim, lütfen tekrar deneyin.\n");
        }

        devamEtmeSecenegi();  
    }
}

// Ana menüyü 
void anaMenu() {
    printf("\033[2J\033[H"); 
    printf("*********************************************\n");
    printf("*        BANKA HESAP YÖNETİMİ SİSTEMİ       *\n");
    printf("*********************************************\n");
    printf("1. Yeni Hesap Aç\n");
    printf("2. Hesap Kapat\n");
    printf("3. Bakiye Sorgula\n");
    printf("4. Para Yatır\n");
    printf("5. Para Çek\n");
    printf("6. Faiz Hesapla\n");
    printf("7. Yönetici Kontrol\n");
    printf("8. Döviz İşlemleri\n");
    printf("9. Çıkış\n");
    printf("*********************************************\n");
}

void dovizIslemleri() {
    printf("Döviz İşlemleri\n");
    printf("1. Dolar\n");
    printf("2. Euro\n");
    printf("3. Altın\n");
    printf("Seçiminizi yapın: ");
    int secim;
    scanf("%d", &secim);

    printf("Dolar Kuru: %.2f TL\n", DOLAR_KURU);
    printf("Euro Kuru: %.2f TL\n", EURO_KURU);
    printf("Altın Kuru: %.2f TL\n", ALTIN_KURU);

    int hesapNo;
    printf("Bakiyenizi görmek istediğiniz hesap numarasını girin: ");
    scanf("%d", &hesapNo);

    int kontrol = 0; 
    for (int i = 0; i < hesapSayisi; i++) {
        if (hesaplar[i].hesapNo == hesapNo && hesaplar[i].hesapDurumu == 1) {
            printf("Hesap Bakiyesi: %.2f TL\n", hesaplar[i].bakiye);
            kontrol = 1;

            float donusturulmusTutar;
            switch (secim) {
                case 1: 
                    donusturulmusTutar = hesaplar[i].bakiye / DOLAR_KURU;
                    printf("Hesabınızdaki %.2f TL, %.2f USD'ye eşdeğerdir.\n", hesaplar[i].bakiye, donusturulmusTutar);
                    break;
                case 2: 
                    donusturulmusTutar = hesaplar[i].bakiye / EURO_KURU;
                    printf("Hesabınızdaki %.2f TL, %.2f EUR'ya eşdeğerdir.\n", hesaplar[i].bakiye, donusturulmusTutar);
                    break;
                case 3: 
                    donusturulmusTutar = hesaplar[i].bakiye / ALTIN_KURU;
                    printf("Hesabınızdaki %.2f TL, %.2f Altın'a eşdeğerdir.\n", hesaplar[i].bakiye, donusturulmusTutar);
                    break;
                default:
                    printf("Geçersiz seçim.\n");
                    break;
            }
            break;
        }
    }

    if (!kontrol) {
        printf("Hesap bulunamadı veya kapalı.\n");
    }
}

void yoneticiKontrol() {
    char adminKullaniciAdi[50] = "admin";
    char adminSifre[50] = "1234";
    char kullaniciAdi[50], sifre[50];
    printf("Yönetici Girişi (admin,1234)\n  ");
    printf("Kullanıcı Adı: ");
    scanf("%s", kullaniciAdi);
    printf("Şifre: ");
    scanf("%s", sifre);
    if (strcmp(kullaniciAdi, adminKullaniciAdi) == 0 && strcmp(sifre, adminSifre) == 0) {
        printf("Yönetici girişi başarılı.\n");
        // Yönetici menüsü
        printf("Yönetici Menüsü:\n");
        printf("1. Tüm Hesapları Görüntüle\n");
        printf("2. İşlem Geçmişini Görüntüle\n");
        printf("3. Geri Dön\n");
        int secim;
        printf("Seçiminizi yapın: ");
        scanf("%d", &secim);
        switch (secim) {
            case 1:
                for (int i = 0; i < hesapSayisi; i++) {
                    printf("Hesap No: %d, Bakiye: %.2f TL, Durum: %s\n", hesaplar[i].hesapNo, hesaplar[i].bakiye,
                           hesaplar[i].hesapDurumu == 1 ? "Açık" : "Kapalı");
                }
                break;
            case 2:
                for (int i = 0; i < hesapSayisi; i++) {
                    printf("Hesap No: %d - İşlem Geçmişi:\n%s\n", hesaplar[i].hesapNo, hesaplar[i].işlemGeçmisi);
                }
                break;
            case 3:
                return; 
            default:
                printf("Geçersiz seçim.\n");
        }
    } else {
        printf("Geçersiz kullanıcı adı veya şifre!\n");
    }
}

void yeniHesapAc() {
    if (hesapSayisi >= 100) {
        printf("Maksimum hesap sayısına ulaşıldı!\n");
        return;
    }

    struct Hesap yeniHesap;

    printf("Hesap numarasını girin: ");
    scanf("%d", &yeniHesap.hesapNo);

    if (hesapNoKontrol(yeniHesap.hesapNo)) {
        printf("Bu hesap numarası zaten var!\n");
        return;
    }

    printf("Başlangıç bakiyesi girin: ");
    scanf("%f", &yeniHesap.bakiye);

    yeniHesap.hesapDurumu = 1;
    strcpy(yeniHesap.işlemGeçmisi, "Hesap açıldı.\n");

    hesaplar[hesapSayisi++] = yeniHesap;

    printf("Hesap başarıyla açıldı!\n");
}

void hesapKapat() {
    int hesapNo;
    printf("Kapamak istediğiniz hesap numarasını girin: ");
    scanf("%d", &hesapNo);

    int kontrol = 0;
    for (int i = 0; i < hesapSayisi; i++) {
        if (hesaplar[i].hesapNo == hesapNo) {
            if (hesaplar[i].hesapDurumu == 0) {
                printf("Bu hesap zaten kapalı.\n");
                return;
            }
            hesaplar[i].hesapDurumu = 0;
            printf("Hesap başarıyla kapatıldı.\n");
            kontrol = 1;
            break;
        }
    }

    if (!kontrol) {
        printf("Hesap bulunamadı.\n");
    }
}

void bakiyeSorgula() {
    int hesapNo;
    printf("Bakiye sorgulamak için hesap numaranızı girin: ");
    scanf("%d", &hesapNo);

    int kontrol = 0;
    for (int i = 0; i < hesapSayisi; i++) {
        if (hesaplar[i].hesapNo == hesapNo && hesaplar[i].hesapDurumu == 1) {
            printf("Hesabınızın bakiyesi: %.2f TL\n", hesaplar[i].bakiye);
            kontrol = 1;
            break;
        }
    }

    if (!kontrol) {
        printf("Hesap bulunamadı veya kapalı.\n");
    }
}

void paraYatir() {
    int hesapNo;
    float tutar;
    printf("Yatırmak istediğiniz hesap numarasını girin: ");
    scanf("%d", &hesapNo);

    printf("Yatırmak istediğiniz tutarı girin: ");
    scanf("%f", &tutar);

    int kontrol = 0;
    for (int i = 0; i < hesapSayisi; i++) {
        if (hesaplar[i].hesapNo == hesapNo && hesaplar[i].hesapDurumu == 1) {
            hesaplar[i].bakiye += tutar;
            strcat(hesaplar[i].işlemGeçmisi, "Para yatırıldı.\n");
            printf("Para başarıyla yatırıldı.\n");
            kontrol = 1;
            break;
        }
    }

    if (!kontrol) {
        printf("Hesap bulunamadı veya kapalı.\n");
    }
}

void paraCek() {
    int hesapNo;
    float tutar;
    printf("Çekmek istediğiniz hesap numarasını girin: ");
    scanf("%d", &hesapNo);

    printf("Çekmek istediğiniz tutarı girin: ");
    scanf("%f", &tutar);

    int kontrol = 0;
    for (int i = 0; i < hesapSayisi; i++) {
        if (hesaplar[i].hesapNo == hesapNo && hesaplar[i].hesapDurumu == 1) {
            if (hesaplar[i].bakiye >= tutar) {
                hesaplar[i].bakiye -= tutar;
                strcat(hesaplar[i].işlemGeçmisi, "Para çekildi.\n");
                printf("Para başarıyla çekildi.\n");
            } else {
                printf("Yetersiz bakiye.\n");
            }
            kontrol = 1;
            break;
        }
    }

    if (!kontrol) {
        printf("Hesap bulunamadı veya kapalı.\n");
    }
}

void faizHesapla() {
    int hesapNo;
    float faizOrani = 0.05;
    printf("Faiz hesaplamak istediğiniz hesap numarasını girin: ");
    scanf("%d", &hesapNo);

    int kontrol = 0;
    for (int i = 0; i < hesapSayisi; i++) {
        if (hesaplar[i].hesapNo == hesapNo && hesaplar[i].hesapDurumu == 1) {
            float faiz = hesaplar[i].bakiye * faizOrani;
            printf("Hesabınızdaki %.2f TL, %.2f TL faiz kazandıracaktır.\n", hesaplar[i].bakiye, faiz);
            kontrol = 1;
            break;
        }
    }

    if (!kontrol) {
        printf("Hesap bulunamadı veya kapalı.\n");
    }
}

int hesapNoKontrol(int hesapNo) {
    for (int i = 0; i < hesapSayisi; i++) {
        if (hesaplar[i].hesapNo == hesapNo) {
            return 1; 
        }
    }
    return 0; 
}

void dosyayaKaydet() {
    FILE *dosya = fopen("hesaplar.dat", "w");
    if (dosya == NULL) {
        printf("Dosya kaydedilemedi.\n");
        return;
    }

    for (int i = 0; i < hesapSayisi; i++) {
        fprintf(dosya, "%d %.2f %d %s\n", hesaplar[i].hesapNo, hesaplar[i].bakiye, hesaplar[i].hesapDurumu,
                hesaplar[i].işlemGeçmisi);
    }

    fclose(dosya);
}


void dosyadanYukle() {
    FILE *dosya = fopen("hesaplar.dat", "r");
    if (dosya == NULL) {
        return;
    }

    while (fscanf(dosya, "%d %f %d %[^\n]", &hesaplar[hesapSayisi].hesapNo, &hesaplar[hesapSayisi].bakiye,
                   &hesaplar[hesapSayisi].hesapDurumu, hesaplar[hesapSayisi].işlemGeçmisi) != EOF) {
        hesapSayisi++;
    }

    fclose(dosya);
}


void devamEtmeSecenegi() {
    printf("Ana menüye dönmek ister misiniz? (1): ");
    int secim;
    scanf("%d", &secim);
    if (secim == 1) {
        printf("\033[2J\033[H");  
        anaMenu();  
    } else {
        printf("Çıkılıyor...\n");
    }
}
