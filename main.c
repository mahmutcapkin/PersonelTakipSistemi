#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

struct personel
{
    char isim[100];
    char telefon[12];
    char TCKimlikNo[12];
    char eposta[100];
    char adres[100];
}personel_bilgi;

int kayitsayisi=0;
void menu();
void Kayit_ekle();
void Personel_listele();
void Kayit_duzenle();
void TC_bul();
void Isim_bul();
void Kayit_sil();
void Say();


int main()
{  setlocale(LC_ALL,"Turkish");
     Say();
     menu();
    return 0;
}

void Say()
{
    FILE *pers;
    pers= fopen("personel.txt","r");
    if(pers!=NULL)
    {
       int sayi=0,karakter=0;
    while((fgetc(pers))!=EOF)
       {
        karakter++;
        if(karakter==sizeof(personel_bilgi))
        {
            sayi++;
            karakter=0;
        }
       }
       kayitsayisi=sayi;
      }
    else
        printf("Dosya Bulunamadi...\n");

    fclose(pers);
}

void menu()
{
    int sec;
    printf("PERSONEL BILGI SISTEMI\n\n");
    printf("ISLEMLER\n\n");
    printf("1.Kayit Ekle\n2.Personel Listele\n3.Kaydi Duzenle\n4.TC Kimlik No ile Kayit Bul\n5.Isim ile Kayit Bul\n6.Kayit Sil\n0.Cikis\n");
    scanf("%d",&sec);
    switch(sec)
    {
         case 0: printf("Cikis yapiliyor..."); exit(1); break;
         case 1: Kayit_ekle(); break;
         case 2:
             if(kayitsayisi!=0)
                Personel_listele();
            else
              {
                 printf("kayit bulunamadi..\nLutfen kayit girisi yapiniz...\n\n");
                 menu();
              }break;
         case 3: Kayit_duzenle(); break;
         case 4: TC_bul(); break;
         case 5: Isim_bul(); break;
         case 6: Kayit_sil(); break;
         default: printf("HATALI DEGER GIRDINIZ!!");
    }
}
void Kayit_ekle()
{
    FILE *pers;
    pers=fopen("personel.txt","a+");
    if((pers=fopen("personel.txt","a+"))!=NULL)
    {
        kayitsayisi++;
        printf("Lutfen Personel ismini Giriniz: ");
        scanf("%s",personel_bilgi.isim);
        printf("Lutfen Personel Telefon Giriniz: ");
        scanf("%s",personel_bilgi.telefon);
        printf("Lutfen Personel TCKimlikNo Giriniz: ");
        scanf("%s",personel_bilgi.TCKimlikNo);
        printf("Lutfen Personel eposta Giriniz: ");
        scanf("%s",personel_bilgi.eposta);
        printf("Lutfen Personel Adres Giriniz: ");
        scanf("%s",personel_bilgi.adres);
        fwrite(&personel_bilgi,sizeof(personel_bilgi),1,pers);
        fclose(pers);
        Say();
        menu();
    }
}
void Personel_listele()
{


    FILE *pers;
    pers=fopen("personel.txt","r");
    while((fread(&personel_bilgi, sizeof(personel_bilgi), 1, pers)) !=0)
    {
      printf("Isim: %s\n",personel_bilgi.isim);
      printf("Telefon: %s\n",personel_bilgi.telefon);
      printf("TCKimlikNo: %s\n",personel_bilgi.TCKimlikNo);
      printf("Eposta: %s\n",personel_bilgi.eposta);
      printf("Adres: %s\n",personel_bilgi.adres);
      printf("\n");
    }
     fclose(pers);
     Say();
     menu();
}
void Kayit_duzenle()
{
    char isim_duzenle[100];
    int sayac=0,a=0;
    FILE *pers;
    pers=fopen("personel.txt","r");
    printf("kaydi duzenlenecek ismi giriniz:\n");
    scanf("%s",&isim_duzenle);
    while((fread(&personel_bilgi, sizeof(personel_bilgi), 1, pers)) !=0)
    {
        sayac++;
        if(strcmp(isim_duzenle,personel_bilgi.isim)==0)
        {
            a++;
            printf("  BULUNAN KAYIT\n");
            printf("Isim : %s\n",personel_bilgi.isim);
            printf("Telefon : %s\n",personel_bilgi.telefon);
            printf("TCKimlikNo : %s\n",personel_bilgi.TCKimlikNo);
            printf("Eposta : %s\n",personel_bilgi.eposta);
            printf("Adres : %s\n\n",personel_bilgi.adres);
        }
        if(a==1)
        {
            break;
        }
    }
    fclose(pers);

      if(a<=0)
        {
            char tus;
            printf("Isim kaydi bulunamadi yeniden arama yapmak ister misiniz?(e/h)\n");
            scanf("%s",&tus);
            if(tus=='e' || tus=='E')
                Kayit_duzenle();
        }
      else if(a==1)
      {
          FILE *pers;
          pers=fopen("personel.txt","r+");
          printf("Lutfen personel Yeni isimini giriniz: ");
          scanf("%s",&personel_bilgi.isim);
          printf("Lutfen personel Yeni telefonunu giriniz: ");
          scanf("%s",&personel_bilgi.telefon);
          printf("Lutfen personel Yeni TCKimlikNo giriniz: ");
          scanf("%s",&personel_bilgi.TCKimlikNo);
          printf("Lutfen personel Yeni epostayi giriniz: ");
          scanf("%s",&personel_bilgi.eposta);
          printf("Lutfen personel Yeni  adresi giriniz: ");
          scanf("%s",&personel_bilgi.adres);
          fseek(pers, (sayac - 1) * sizeof(personel_bilgi), SEEK_SET);
          fwrite(&personel_bilgi, sizeof(personel_bilgi), 1, pers);
          fclose(pers);
          Say();
      }
      menu();
}
void TC_bul()
{
    char tc_bul[12];
    int bulunan=0;
    printf("Lutfen TC Kimlik No giriniz:");
    scanf("%s",&tc_bul);
    FILE *pers;
    pers = fopen("personel.txt","r");
    while((fread(&personel_bilgi, sizeof(personel_bilgi), 1, pers)) !=0)
    {
      if(strcmp(tc_bul,personel_bilgi.TCKimlikNo)==0)
        {
             bulunan++;
             printf("  BULUNAN KAYIT\n");
             printf("Isim: %s\n",personel_bilgi.isim);
             printf("Telefon: %s\n",personel_bilgi.telefon);
             printf("TCKimlikNo: %s\n",personel_bilgi.TCKimlikNo);
             printf("Eposta: %s\n",personel_bilgi.eposta);
             printf("Adres: %s\n",personel_bilgi.adres);
             printf("\n");
        }
    }
        if(bulunan<=0)
            printf("Aranan TC Kimlik No bulunamadi...\n");
        fclose(pers);
        menu();
}

void Isim_bul()
{
    char isim_bul[100];
    int bulunan2=0;
    printf("Lutfen aradiginiz ismi giriniz:");
    scanf("%s",&isim_bul);
    FILE *pers;
    pers = fopen("personel.txt","r");
    while((fread(&personel_bilgi,sizeof(personel_bilgi),1,pers))!=0)
    {
      if(strcmp(isim_bul,personel_bilgi.isim)==0)
        {
             bulunan2++;
             printf("  BULUNAN KAYIT\n");
             printf("Isim: %s\n",personel_bilgi.isim);
             printf("Telefon: %s\n",personel_bilgi.telefon);
             printf("TCKimlikNo: %s\n",personel_bilgi.TCKimlikNo);
             printf("Eposta: %s\n",personel_bilgi.eposta);
             printf("Adres: %s\n",personel_bilgi.adres);
             printf("\n");
        }
    }
        if(bulunan2<=0)
            printf("Aranan Isim bulunamadi...\n");

        fclose(pers);
        menu();
}

void Kayit_sil()
{
    char tc_sil[12],tus3;
    int bulunan3=0;
    printf("Lutfen silinecek TC Kimlik No giriniz:");
    scanf("%s",&tc_sil);
    FILE *pers;
    pers = fopen("personel.txt","r");
    while((fread(&personel_bilgi, sizeof(personel_bilgi), 1, pers)) !=0)
    {
      if(strcmp(tc_sil,personel_bilgi.TCKimlikNo)==0)
        {
             bulunan3++;
             printf("  SILINECEK KAYIT\n");
             printf("Isim: %s\n",personel_bilgi.isim);
             printf("Telefon: %s\n",personel_bilgi.telefon);
             printf("TCKimlikNo: %s\n",personel_bilgi.TCKimlikNo);
             printf("Eposta: %s\n",personel_bilgi.eposta);
             printf("Adres: %s\n",personel_bilgi.adres);
             printf("\n");
        }
    }
    fclose(pers);
     if(bulunan3<=0)
     {
         char tus2;
         printf("Silinecek TC Kimlik No bulunamadi yeniden arama yapmak ister misiniz?(e/h)\n");
         scanf("%s",&tus2);
         if(tus2=='e' || tus2=='E')
             Kayit_sil();
     }
     else if(bulunan3>0)
     {
         printf("bulunan kaydi silmek istediginize emin misiniz?(e/h)\n");
         scanf("%s",&tus3);
         if(tus3=='e' || tus3=='E')
         {
             FILE *pers;
             pers=fopen("personel.txt","r");
             FILE *aktarma;
             aktarma=fopen("aktarma.txt","a+");
              while((fread(&personel_bilgi,sizeof(personel_bilgi),1,pers))!=0)
               {
                if(strcmp(tc_sil,personel_bilgi.TCKimlikNo)==0)
                   {
                     continue;
                   }
                fwrite(&personel_bilgi,sizeof(personel_bilgi),1,aktarma);
               }
                fclose(pers);
                fclose(aktarma);
                remove(pers);
                Say();
          }
     }
     menu();
}
