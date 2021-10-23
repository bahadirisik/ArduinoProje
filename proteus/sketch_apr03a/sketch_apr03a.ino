#include <SPI.h>
#include <SD.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>


File dosya;
int kasadaki_para[5];
char line2[22];
int bilgiler2[8];
 int b=0;
 int e=0;
 int tut=0;
 int para_bilgisi[5]={0,0,0,0,0};
 int secilen_islem[4]={0,0,0,0};
 int a;
 int bilgiler3[8];
 int yuklenen_para;
 int hizmet_parasi;
 int verilecek_para;


void kasa_parasi(char cumle[])
{
  int c=0;
 const char *d;
  d = strtok (cumle, ",");
  while (d != NULL)  {
      kasadaki_para[c]=atoi(d);
      c++;
      d = strtok (NULL, ",");
    }
}
void bilgiler(char cumle[])
{
    
   const char *d;
   d = strtok (cumle, ", ");
  while (d != NULL)  {
      if(b==2||b==3||b==7||b==8||b==12||b==13||b==17||b==18)
      {
        bilgiler2[e]=atoi(d);
        bilgiler3[e]=atoi(d);
        e++;
      }
      b++;
      d = strtok (NULL, ", ");
    }
    
}
void setup() {
  pinMode(A0,OUTPUT);
  pinMode(A1,OUTPUT);
  Serial.begin(9600);
  while (!Serial) {
    ;
  }
  if (!SD.begin()) {
    Serial.println("kart bulunamadı");
    while (1);
  }
 
  dosya = SD.open("proje.txt", FILE_READ);
    for(int i =0;i<5;i++)
    {
      String line= dosya.readStringUntil('\n');
       for(int j=0;j<22 ;j++)
      {
        line2[j]=line[j];
      }
      if(i==0)
      {
        kasa_parasi(line2);
      }
      else
      {
        bilgiler(line2);
      }
    }
  
   
    
}
void loop() {
    int b1=digitalRead(9);
    int b2=digitalRead(8);
    int b3=digitalRead(7);
    int b4=digitalRead(6);
    int b5=digitalRead(5);
    int b6=digitalRead(3);
    int b7=digitalRead(2);
    int b8=digitalRead(0);
   
     
   if(b1==HIGH)
   {
    if(tut==0)
    {
     para_bilgisi[0]++;
     kasadaki_para[0]++;
     delay(500);
    }
    if(tut==1)
    {
      secilen_islem[0]++;
      bilgiler2[0]--;
      delay(500);
    }
    
   }
    if(b2==HIGH)
   {
   if(tut==0)
    {
     para_bilgisi[1]++;
     kasadaki_para[1]++;
     delay(500);
    }
    if(tut==1)
    {
     secilen_islem[1]++;
     bilgiler2[2]--;
      delay(500);
    }
    
   }
   if(b3==HIGH)
   {
    if(tut==0)
    {
     para_bilgisi[2]++;
     kasadaki_para[2]++;
     delay(500);
    }
    if(tut==1)
    {
      secilen_islem[2]++;
      bilgiler2[4]--;
      delay(500);
    }
   }
   if(b4==HIGH)
   {
   if(tut==0)
    {
     para_bilgisi[3]++;
     kasadaki_para[3]++;
     delay(500);
    }
    if(tut==1)
    {
      secilen_islem[3]++;
      bilgiler2[6]--;
      delay(500);
    }
   }
   if(b5==HIGH)
   {
    if(tut==0)
    {
     para_bilgisi[4]++;
     kasadaki_para[4]++;
     delay(500);
    }
    
   }
   if(b6==HIGH)
   {
    if(tut==0)
    {
      tut=1;
      
    }
    else if(tut==1)
    {
      tut=2;
    }
   delay(500);
   }
   if(b7==HIGH)
   {
    for(int i=0;i<4;i++)
    {
       secilen_islem[i]=0;
    }
    for(int i=0;i<8;i++)
    {
       bilgiler2[i]=bilgiler3[i];
    }
    Serial.println("Res Attiniz Lutfen Tekrar Islem Seciniz.");
    tut=1;
    delay(500);
   }
    if(b8==HIGH)
   {
    for(int i=0;i<4;i++)
    {
       secilen_islem[i]=0;
    }
    for(int i=0;i<4;i++)
    {
       Serial.println(para_bilgisi[i]);
    }
    for(int i=0;i<5;i++)
    {
     kasadaki_para[i]=kasadaki_para[i]-para_bilgisi[i];
    }
     for(int i=0;i<5;i++)
    {
      para_bilgisi[i]=0;
    }
     for(int i=0;i<8;i++)
    {
       bilgiler2[i]=bilgiler3[i];
    }
    Serial.println("Full Res Attiniz Lutfen Tekrar Para Atıp Islam Seciniz.");
    digitalWrite(A0,LOW);
    tut=0;
    delay(500);
   
   }
    a=rand()%4+1;
   if(tut==2)
   {
    
    Serial.println(a);
    
    if(a==2)
    {
      digitalWrite(A0,HIGH);
      Serial.println("Paraniz Sikisti Lutfen Full Res Tusuna Basiniz");
      
    }
    else
    {
      digitalWrite(A1,HIGH);
      yuklenen_para=para_bilgisi[0]*5+para_bilgisi[1]*10+para_bilgisi[2]*20+para_bilgisi[3]*50+para_bilgisi[4]*100;
      hizmet_parasi=secilen_islem[0]*bilgiler2[1]+secilen_islem[1]*bilgiler2[3]+secilen_islem[2]*bilgiler2[5]+secilen_islem[3]*bilgiler2[7];
      verilecek_para=yuklenen_para-hizmet_parasi;
      Serial.print("Kisinin Yukledigi Para:");
      Serial.println(yuklenen_para);
      Serial.print("Hizmet parasi:");
      Serial.println(hizmet_parasi);
      Serial.print("Verilecek Para:");
      Serial.println(verilecek_para);
      Serial.println("****************************");
    for(int i=0;i<5;i++)
    {
      Serial.println(kasadaki_para[i]);
    }

   if(verilecek_para<0)
   {
    Serial.println("Verdiginiz para secilen islemler icin yetersiz lutfen Full Res tusuna basınız.");
   }
   else
   {
    if(verilecek_para==0)
    {
      Serial.println("Alacagınız yok.");
    }
    else
    {
      while(1)
      {
        if(verilecek_para>=100&&kasadaki_para[4]>0)
        {
          verilecek_para-=100;
          kasadaki_para[4]--;
          if(verilecek_para==0)
          {
            break;
          }
        }
        else if(verilecek_para>=50&&kasadaki_para[3]>0)
        {
          verilecek_para-=50;
          kasadaki_para[3]--;
          if(verilecek_para==0)
          {
            break;
          }
        }
         else if(verilecek_para>=20&&kasadaki_para[2]>0)
        {
          verilecek_para-=20;
          kasadaki_para[2]--;
          if(verilecek_para==0)
          {
            break;
          }
        }
         else if(verilecek_para>=10&&kasadaki_para[1]>0)
        {
          verilecek_para-=10;
          kasadaki_para[1]--;
          if(verilecek_para==0)
          {
            break;
          }
        }
         else if(verilecek_para>=5&&kasadaki_para[0]>0)
        {
          verilecek_para-=5;
          kasadaki_para[0]--;
          if(verilecek_para==0)
          {
            break;
          }
        }
        else
        {
          Serial.println("Kasada Yeteri Kadar Para Yoktur!!!!");
          break;
        }
        
      }
      Serial.println("****************************");
   for(int i=0;i<5;i++)
    {
      Serial.println(kasadaki_para[i]);
    }
     
    }
    }
    for(int i=0;i<4;i++)
    {
     secilen_islem[i]=0;
    }
    for(int i=0;i<5;i++)
    {
     para_bilgisi[i]=0;
    }
   }
   
    
    tut=0;
    
   }
   
    
   
   
 
}
