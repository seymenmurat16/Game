/** 
@file 
BBG2 spring2016 Semester Project.   

Oyunda oyun tablosunda tüm elemanlarý birbiri ile eþleþtirmeye çalýþýlýyor.

@author   

Name:           Murat Seymen   

Student no:     14011018   

Date:           05.06.2016

E-Mail:         seymenmurat16@hotmail.com  

Compiler used:  GCC  

IDE:            Dev-C++  

Operating System Windows 8.1 
*/   
#include<stdio.h>
#include<time.h>
#include<string.h>
#define N 5

void drawBoard(int [][20]);
int readFile2Matrix(int [][20], int [][20]);
void oyna(int [ ][20],int [][20],int[][20],int);
void elemanikaldir(int [ ][20],int [][20]);
int alankontrolet(int [ ][20]);
int eslemekontrol(int [ ][20],int [][20],int [][20],int);
int elemankontrol(int [ ][20],int [][20],int);
void menu(int [ ][20],int [][20],int [][20],int);

int main()
{
    int alan[20][20],sakla[20][20],i,j,x,mtr[4][20],sure[10],baslangic,bitis,sayac=1,temp,sayac2,eleman;
    char isim[10][10],son,tmp[10][10];
	do {
 	system("CLS"); // Yeni bir oyuna baþladýðýnda ekraný temizliyor
	clock_t baslangic,bitis; 
    baslangic=clock();// Oyuna baþlangýç zamaný
	readFile2Matrix(alan,mtr); 
    drawBoard(alan);
	sayac2=0;
	for(i=0;i<N;i++){
 		for (j=0;j<N;j++){
			if(alan[i][j]!=0){ // Alanda kac tane eleman olduðunu buluyorum
				sayac2++;			  
			}
		}
	}
	eleman=(sayac2)/2; // Alanda her elemandan 2 tane olduðu için 2'ye bölüyorum
	oyna(alan,sakla,mtr,eleman);
	bitis=clock(); // Oyunun bitiþ zamaný
 	sure[sayac]=(bitis-baslangic)/CLOCKS_PER_SEC;
	printf("Sure : %d\n",sure[sayac]); 
    printf("Ýsim giriniz:\n");
    scanf("%s",&isim[sayac]);
    printf("Yeni bir oyun oynamak icin E'ye oyunu sonlandirmak icin herhangi bir tusa basiniz\n");
    scanf ("%s",&son); 
    sayac++; // Oyunun her oynandýðýnda sayacý bir arttýrarak oyunun kaç tur oynandýðýný buluyorum
	}while (son == 'E'); // E tuþuna bastýkcça oyun devam ediyor farklý bir tuþa basýlýnca oyunu bitiriyor
  	system("CLS");
 	printf("Zaman Tablosu \n");
	for(i=2;i<sayac+1;i++){
		for(j=1;j<sayac+1-i;j++){
 			if(sure[j]>sure[j+1]){ // Zamanlarý ve isimleri sýraya dizdim  
			 temp=sure[j];
			 sure[j]=sure[j+1];
			 sure[j+1]=temp; 
			 strcpy( tmp[j], isim[j] ); 
			 strcpy( isim[j], isim[j+1] ); 
			 strcpy( isim[j+1], tmp[j] );  
			  }				 
		}				 
	}
	for (i=1;i<sayac;i++){ // Puan tablosunu yazdýrýyorum
	  	printf("%d %10s %3d",i,isim[i],sure[i]);			  
		printf("\n");
	} 
  return 0;	
}
/**
 Bu fonksiyonda hem txt dosyasýný okuyorum hem de her elemanýn koordinatýný mtr matrisinde saklýyorum 
 örnek verecek olursa boyutu 5 olan oyun alaný için aþaðýdaki gibi oluyor 
 1 1 2 2 3 3 4 4 5 5 ( Hangi elemanýn koordinatlarýnýn olduðu )
 0 1 1 3 1 1 2 3 4 4 ( Satýr koordinatlarý )
 0 4 0 3 1 3 1 4 0 4 ( Sutun koordinatlarý )
 @param alan  Oyun alaný
 @param mtr   Oyun alanýndaki elemanlarýn koordinatlarýný sakladýðým matris
*/	
int readFile2Matrix(int alan[][20],int mtr[][20])
{
	int i,j,temp,k=0;
	for(i=0;i<N;i++)
  	   {
  		  for(j=0;j<N;j++)
  				alan[i][j]=0;
  	   }
	FILE *data = fopen("5x5.txt","r");
	if(!data){
        printf("Dosya Acilamadi!");
        return 0;
    }
    while(!feof(data)){
        fscanf(data,"%d %d %d\n",&i,&j,&temp);  
		mtr[0][k]=temp;
		mtr[1][k]=i;
		mtr[2][k]=j;
		alan[i][j]=temp; 
		k=k+1;
    }  
  	fclose(data);
}
void drawBoard(int alan[][20])
{
    int i,j,k;
    printf("Oyun Tablosu");
	for(i=0;i<N;i++){
        printf("\n");
        for (k=0;k<N;k++)
            printf("-------");
        printf("\n");
		for(j=0;j<N;j++)
            if (alan[i][j]!=0)
                printf("  %d   |",alan[i][j]);
            else
                 printf("      |",k);
    }
	printf("\n\n");	 
}
/**
 Bu fonksiyon oyuncunun oyunu oynamasýný saðlýyor girilen koordinatlara göre elemanlarý yerleþtiriyor
 @param alan   Oyun alaný
 @param sakla  Oyunu geri almak için son hamleyi sakladýðým matris
 @param mtr    Oyun alanýndaki elemanlarýn koordinatlarýný sakladýðým matris
 @param eleman Oyun alanýndaki eleman sayisi
*/
void oyna(int alan[ ][20],int sakla[][20],int mtr[][20],int eleman){
	 int x,x1,y1,x2,y2,i,j;	
	 char cevap;	
		
	 	  	 printf ("Baslangic noktasi: \n"); // Oyuncu baþlamak istediði koordinatlarý giriyor
   		   		  scanf("%d %d",&x1,&y1); 
   		   		  x=alan[x1][y1]; // Girdiði koordinattaki elemaný x'e eþitliyor 
				printf ("Bitis noktasi: \n");
   		   		  scanf("%d %d",&x2,&y2); // Oyuncu bitirmek istediði koordinatlarý giriyor   
	  	for( i = 0; i < N; i++ ) { 
			 for( j = 0; j < N; j++ ) {
		  	 	 sakla[i][j]=alan[i][j]; // Oyuncunun son hamleyi geri alma ihtimaline karþý oynamadan önceki oyun alanýný sakla matrisinde saklýyor
			}
		}
		  if (x1==x2){ // Oyuncunun girdiði satýr koordinatlarý eþitliðine bakýyor  
   			   if(y1 < y2){ // Eðer satýr koordinatlarý eþit ise ilk girilen sutun koordinatý ikinci girilenden kucuk olup olmadýðýný kontrol ediyor
			   while (y1 <= y2){ // Eðer küçükse küçük olan koordinat büyük olan koordinata eþit olana kadar devam ediyor  
 		   			 alan[x1][y1]=x; // Baslangic koordinatýndan bitis koordinatýna kadar baþlangýç koordinatýndaki elemana eþitliyor
						 y1=y1+1;
						}		 
			   }
			   else if(y1 > y2){ // Ýlk girilen sutun koordinatý son girilinden sutun koordinatýndan büyük olup olmadýðýný kontrol ediyor
			   while (y1 >= y2){ // Eðer büyükse küçük olan koordinat büyük olan koordinata eþit olana kadar devam ediyor 
 		   			 alan[x1][y2]=x; // Baslangic koordinatýndan bitis koordinatýna kadar baþlangýç koordinatýndaki elemana eþitliyor
						 y2=y2+1;
					}
			}
		}
		if (y1==y2){ // Oyuncunun girdiði sutun koordinatlarý eþitliðine bakýyor  
   			   if(x1 < x2){ // Eðer sutun koordinatlarý eþit ise ilk girilen satýr koordinatý ikinci girilenden kucuk olup olmadýðýný kontrol ediyor
			   while (x1 <= x2){ // Eðer küçükse küçük olan koordinat büyük olan koordinata eþit olana kadar devam ediyor  
 		   			 alan[x1][y1]=x; // Baslangic koordinatýndan bitis koordinatýna kadar baþlangýç koordinatýndaki elemana eþitliyor
						 x1=x1+1;
						}		 
			   }
			   else if(x1 > x2){ // Ýlk girilen satýr koordinatý son girilinden satýr koordinatýndan büyük olup olmadýðýný kontrol ediyor
			   while (x1 >= x2){ // Eðer büyükse küçük olan koordinat büyük olan koordinata eþit olana kadar devam ediyor 
 		   			 alan[x2][y1]=x; // Baslangic koordinatýndan bitis koordinatýna kadar baþlangýç koordinatýndaki elemana eþitliyor
						 x2=x2+1;
					 }			  
			    }
		}			
	if (elemankontrol(alan,mtr,eleman)==1){ 
	   	for( i = 0; i < N; i++ ) { // 
		 		 for( j = 0; j < N; j++ ) {
		   	 	 	  alan[i][j]=sakla[i][j]; // Geçersiz hamleden önceki oyun alanýna geri dönüyor
					  }
			  }
	   system("CLS");
 	   drawBoard(alan);
	   printf("Gecersiz Hamle\n");
	   oyna(alan,sakla,mtr,eleman);
	}
	system("CLS");
 	drawBoard(alan);
 	menu(alan,sakla,mtr,eleman);
}
/**
 Bu fonksiyonda ise seçtiði bir elemaný oyun alanýndan oyun baþlanýcýndaki iki koordinat haricinde kaldýrýyor
 @param alan  Oyun alaný
 @param mtr   Oyun alanýndaki elemanlarýn koordinatlarýný sakladýðým matris
*/	
void elemanikaldir(int alan[ ][20],int mtr[][20]){
	 int eleman,i,j;
	 printf("Kaldirmak istediginiz elemani seciniz:\n");
	 scanf("%d",&eleman);
	 for( i = 0; i < N; i++ ) {
			 for( j = 0; j < N; j++ ) {
			 	  if(alan[i][j]==eleman){ // Eðer i j koordinatlarýndaki eleman seçilen elemana eþit ise i j koordinatýný sýfýrlýyor
				   		alan[i][j]=0;			 
				   }
			  }
	}
	 for( i = 0; i < 2*eleman; i++ ) { 
	  	  if (mtr[0][i]==eleman){ // mtr matrisinde sakladýðým ilk 2 koordinatýda sýfýrladýðým için burada ikisinide yine alana yazdýrýyorum
			 	alan[mtr[1][i]][mtr[2][i]]=eleman;  
		   }
	 }
}
/**
 Bu fonksiyonda oyun bitirildiðinde boþ alan var mý diye kontrol ediyor 
 @param alan  Oyun alaný
 @return 0    
*/	
int alankontrolet(int alan[ ][20]){
	 int i,j,sayac=0;
	 for( i = 0; i < N; i++ ) {
			 for( j = 0; j <N; j++ ) {
			 	if (alan[i][j]==0){ // Eðer i j koordinatlari 0a eþit ise sayacý arttýrýyorum
				 sayac++;
				 }
		}
	}
	if (sayac>0){ // Eðer sayac 0dan buyukse 0 olarak dönüyor 
	   return 0; 
	}
}
/**
 Bu fonksiyonda elemanlarýn birbiri ile eþleþip eþlemediðine bakýyorum yani oyun alanýnda baþlangýç koordinatýndaki ayný 2 elemanýn birbiri
 ile eþlemesini kontrol ediyorum 
 @param alan   Oyun alaný
 @param mtr    Oyun alanýndaki elemanlarýn koordinatlarýný sakladýðým matris
 @param eleman Oyun alanýndaki eleman sayisi
 @return 0    
*/	
int eslemekontrol(int alan[ ][20],int mtr[][20],int sakla[][20],int eleman){
	int i,j,m,k,sayac;
	for( i = 0; i < N; i++ ) { // eslesmekontrol fonksiyonunda oyun alanýnda deðiþiklik yaptýðým için oyun alanýný deðiþtirmeden
			 for( j = 0; j < N; j++ ) { // sakla matrisinde deðiþiklikleri yapýyorum 
		  	 	 sakla[i][j]=alan[i][j]; 
			}
		}
	for(k=0;k<2*eleman;k+=2){ 
	m=mtr[0][k]; // Elemanýn numarasý
	i=mtr[1][k]; // Elemanýn satýr koordinatý
	j=mtr[2][k]; // Elemanýn sutun koordinatý 
	while((i!=mtr[1][k+1])||(j!=mtr[2][k+1])){ // Elemandan saklada 2 tane bulunuyor  i ve j yi bir tane koordinata eþitlerken burada
											   // i ve j diðer koordinata eþit olana kadar döngünün devam etmesini saðlýyorum 
		sayac=0;
		if(sakla[i][j-1]==m){ // Elemanýn solunda ayný elemandan olup olmadýðýný kontrol ediyorum
	 	    sakla[i][j]=0;	// Sola gittikten sonra tekrar saða dönmemesi için i j koordinatýný sýfýrlýyorum	
			j=j-1;	// Sutunu azaltarak soldan devam etmesini saðlýyorum				 							 
			sayac++;
		}		 
		if(sakla[i][j+1]==m) { // Elemanýn saðýnda ayný elemandan olup olmadýðýný kontrol ediyorum
			sakla[i][j]=0; // Saða gittikren sonra tekrar sola dönmemesi için i j koordinatýný sýfýrlýyorum
			j=j+1;	// Sutunu arttýrarak saðdan devam etmesini saðlýyorum				 							 
			sayac++;		
		}											
		if(sakla[i-1][j]==m){ // Elemanýn yukarýsýnda ayný elemandan olup olmadýðýný kontrol ediyorum
			sakla[i][j]=0;	// Yukarý çýktýktan sonra tekrar aþaðýya inmemesi için i j koordinatýný sýfýrlýyorum
			i=i-1;	// Satýrý azaltarak yukarýdan devam etmesini saðlýyorum				 							 
			sayac++;
		}			
		if(sakla[i+1][j]==m){ // Elemanýn aþaðýsýnda ayný elemandan olup olmadýðýný kontrol ediyorum
			sakla[i][j]=0; // Aþaðý indikten sonra tekrar yukarý çýkmamasý için i j koordinatýný sýfýrlýyorum
			i=i+1;	// Satýrý arttýrak aþaðýdan devam etmesini saðlýyorum					 							 
	    	sayac++;
	    }
		if (sayac==0){ // Kontrol edilirken oyun alanýnýn durumuna göre while döngüsünden çýkacak koordinatlarý sýfýrlýyor 
		   if (sakla[mtr[1][k+1]][mtr[2][k+1]]==0){ // Eðer çýkýþ koordinatlarý 0 ise döngüden çýkmasý için
		   	  	i=mtr[1][k+1]; // i ve j yi döngüden çýkacak koordinatlara eþitliyorum
				j=mtr[2][k+1];
				sayac++;	 							   
				 }
		   }
		if (sayac==0){ // eðer etrafýnda ayný elamandan bulamazsa fonksiyondan çýkýyor
		return 0;
		}	
	}
	}
}
/**
 Bu fonksiyonda oyuncunun elemanlarýn oyunun baþlangýcýndaki koordinatlarýný deðiþtirip deðiþtirmediðine bakýyor 
 @param alan   Oyun alaný
 @param mtr    Oyun alanýndaki elemanlarýn koordinatlarýný sakladýðým matris
 @param eleman Oyun alanýndaki eleman sayisi
 @return 1    
*/	
int elemankontrol(int alan[ ][20],int mtr[][20],int eleman){
	int i ,sayac, x, y ;
	sayac=0;
	for (i=0;i<2*eleman;i++){
		x=mtr[1][i]; // Elemanýn satýr sayýsýný x'e eþitliyor 
		y=mtr[2][i]; // Elemanýn sutun sayýsýný y'ye eþitliyor
		if(alan[x][y]!=mtr[0][i]){ // Oyunun baþlangýcýndaki koordinatlarý sakladýðým mtr matrisine göre alandaki baþlangýç koordinatlarýndaki
			sayac++;               // elemanlarýn deðiþip deðiþmediðini kontrol ediyor eðer deðiþmiþse sayacý arttýrýyor					  
		}
	}
	if (sayac!=0){ // Eðer sayac 0a eþit deðilse  1 olarak dönüyor 
	   return 1;
	}
}
/**
 Bu fonksiyonda oyuncunun her hamlesi sonrasý  ne yapmak istediðine göre oyunu devam ettiriyor 
 @param alan   Oyun alaný
 @param mtr    Oyun alanýndaki elemanlarýn koordinatlarýný sakladýðým matris 
 @param sakla  Oyunu geri almak için son hamleyi sakladýðým matris   
 @param eleman Oyun alanýndaki eleman sayisi
*/	
void menu(int alan[ ][20],int sakla[][20],int mtr[][20],int eleman){
	int i,j,k;
	char cevap ;
	printf("Devam etmek icin E'ye ,geri almak icin G'ye basiniz,elemani kaldirmak icin K'ya basinin,bitirmek icin B'ye basiniz' ");
	scanf("%s",&cevap);
	if (cevap =='E'){ // cevap E ise oynamaya devam ediyor
 	oyna(alan,sakla,mtr,eleman);
	}		
	 else if  (cevap =='G'){ // cevap G ise son hamleyi geri alýyor 
	   	for( i = 0; i < N; i++ ) {
			 for( j = 0; j < N; j++ ) {
		  	 	 alan[i][j]=sakla[i][j]; 	
			}
		}
		system("CLS");
		drawBoard(alan);
    	oyna(alan,sakla,mtr,eleman);
	}	
	else if  (cevap =='K'){ // Cevap K ise alandan istediðini elemaný kaldýrýyor 
		elemanikaldir(alan,mtr);
		system("CLS");
		drawBoard(alan);
    	oyna(alan,sakla,mtr,eleman);
	}
	else if  (cevap =='B'){ // Cevap B ise oyunun bitirilip bitirilmediðini kontrol ediyor 
		if(alankontrolet(alan)==0){ // Eðer alankontrolet fonksiyonu 0 ise oyunda boþ alan olduðu anlaþýlýyor 
			printf("Oyunda bos alan var\n");
			oyna(alan,sakla,mtr,eleman);
		}
		if(eslemekontrol(alan,mtr,sakla,eleman)==0){ // Eðer eslesmekontrol 0 ise oyunda eþleþmemiþ eleman olduðu anlaþýlýyor
			printf("Oyunda eslesmemis eleman var\n");
			elemanikaldir(alan,mtr);
			system("CLS");
			drawBoard(alan);
			oyna(alan,sakla,mtr,eleman);							 
			}
	
	}
	else {
	printf("Yanlis harf girildi\n"); // Yukarýdaki harfler dýþýnda bir harf girilirse uyarý verdirtiyorum
	menu(alan,sakla,mtr,eleman);
    }
}
