/** 
@file 
BBG2 spring2016 Semester Project.   

Oyunda oyun tablosunda t�m elemanlar� birbiri ile e�le�tirmeye �al���l�yor.

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
 	system("CLS"); // Yeni bir oyuna ba�lad���nda ekran� temizliyor
	clock_t baslangic,bitis; 
    baslangic=clock();// Oyuna ba�lang�� zaman�
	readFile2Matrix(alan,mtr); 
    drawBoard(alan);
	sayac2=0;
	for(i=0;i<N;i++){
 		for (j=0;j<N;j++){
			if(alan[i][j]!=0){ // Alanda kac tane eleman oldu�unu buluyorum
				sayac2++;			  
			}
		}
	}
	eleman=(sayac2)/2; // Alanda her elemandan 2 tane oldu�u i�in 2'ye b�l�yorum
	oyna(alan,sakla,mtr,eleman);
	bitis=clock(); // Oyunun biti� zaman�
 	sure[sayac]=(bitis-baslangic)/CLOCKS_PER_SEC;
	printf("Sure : %d\n",sure[sayac]); 
    printf("�sim giriniz:\n");
    scanf("%s",&isim[sayac]);
    printf("Yeni bir oyun oynamak icin E'ye oyunu sonlandirmak icin herhangi bir tusa basiniz\n");
    scanf ("%s",&son); 
    sayac++; // Oyunun her oynand���nda sayac� bir artt�rarak oyunun ka� tur oynand���n� buluyorum
	}while (son == 'E'); // E tu�una bast�kc�a oyun devam ediyor farkl� bir tu�a bas�l�nca oyunu bitiriyor
  	system("CLS");
 	printf("Zaman Tablosu \n");
	for(i=2;i<sayac+1;i++){
		for(j=1;j<sayac+1-i;j++){
 			if(sure[j]>sure[j+1]){ // Zamanlar� ve isimleri s�raya dizdim  
			 temp=sure[j];
			 sure[j]=sure[j+1];
			 sure[j+1]=temp; 
			 strcpy( tmp[j], isim[j] ); 
			 strcpy( isim[j], isim[j+1] ); 
			 strcpy( isim[j+1], tmp[j] );  
			  }				 
		}				 
	}
	for (i=1;i<sayac;i++){ // Puan tablosunu yazd�r�yorum
	  	printf("%d %10s %3d",i,isim[i],sure[i]);			  
		printf("\n");
	} 
  return 0;	
}
/**
 Bu fonksiyonda hem txt dosyas�n� okuyorum hem de her eleman�n koordinat�n� mtr matrisinde sakl�yorum 
 �rnek verecek olursa boyutu 5 olan oyun alan� i�in a�a��daki gibi oluyor 
 1 1 2 2 3 3 4 4 5 5 ( Hangi eleman�n koordinatlar�n�n oldu�u )
 0 1 1 3 1 1 2 3 4 4 ( Sat�r koordinatlar� )
 0 4 0 3 1 3 1 4 0 4 ( Sutun koordinatlar� )
 @param alan  Oyun alan�
 @param mtr   Oyun alan�ndaki elemanlar�n koordinatlar�n� saklad���m matris
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
 Bu fonksiyon oyuncunun oyunu oynamas�n� sa�l�yor girilen koordinatlara g�re elemanlar� yerle�tiriyor
 @param alan   Oyun alan�
 @param sakla  Oyunu geri almak i�in son hamleyi saklad���m matris
 @param mtr    Oyun alan�ndaki elemanlar�n koordinatlar�n� saklad���m matris
 @param eleman Oyun alan�ndaki eleman sayisi
*/
void oyna(int alan[ ][20],int sakla[][20],int mtr[][20],int eleman){
	 int x,x1,y1,x2,y2,i,j;	
	 char cevap;	
		
	 	  	 printf ("Baslangic noktasi: \n"); // Oyuncu ba�lamak istedi�i koordinatlar� giriyor
   		   		  scanf("%d %d",&x1,&y1); 
   		   		  x=alan[x1][y1]; // Girdi�i koordinattaki eleman� x'e e�itliyor 
				printf ("Bitis noktasi: \n");
   		   		  scanf("%d %d",&x2,&y2); // Oyuncu bitirmek istedi�i koordinatlar� giriyor   
	  	for( i = 0; i < N; i++ ) { 
			 for( j = 0; j < N; j++ ) {
		  	 	 sakla[i][j]=alan[i][j]; // Oyuncunun son hamleyi geri alma ihtimaline kar�� oynamadan �nceki oyun alan�n� sakla matrisinde sakl�yor
			}
		}
		  if (x1==x2){ // Oyuncunun girdi�i sat�r koordinatlar� e�itli�ine bak�yor  
   			   if(y1 < y2){ // E�er sat�r koordinatlar� e�it ise ilk girilen sutun koordinat� ikinci girilenden kucuk olup olmad���n� kontrol ediyor
			   while (y1 <= y2){ // E�er k���kse k���k olan koordinat b�y�k olan koordinata e�it olana kadar devam ediyor  
 		   			 alan[x1][y1]=x; // Baslangic koordinat�ndan bitis koordinat�na kadar ba�lang�� koordinat�ndaki elemana e�itliyor
						 y1=y1+1;
						}		 
			   }
			   else if(y1 > y2){ // �lk girilen sutun koordinat� son girilinden sutun koordinat�ndan b�y�k olup olmad���n� kontrol ediyor
			   while (y1 >= y2){ // E�er b�y�kse k���k olan koordinat b�y�k olan koordinata e�it olana kadar devam ediyor 
 		   			 alan[x1][y2]=x; // Baslangic koordinat�ndan bitis koordinat�na kadar ba�lang�� koordinat�ndaki elemana e�itliyor
						 y2=y2+1;
					}
			}
		}
		if (y1==y2){ // Oyuncunun girdi�i sutun koordinatlar� e�itli�ine bak�yor  
   			   if(x1 < x2){ // E�er sutun koordinatlar� e�it ise ilk girilen sat�r koordinat� ikinci girilenden kucuk olup olmad���n� kontrol ediyor
			   while (x1 <= x2){ // E�er k���kse k���k olan koordinat b�y�k olan koordinata e�it olana kadar devam ediyor  
 		   			 alan[x1][y1]=x; // Baslangic koordinat�ndan bitis koordinat�na kadar ba�lang�� koordinat�ndaki elemana e�itliyor
						 x1=x1+1;
						}		 
			   }
			   else if(x1 > x2){ // �lk girilen sat�r koordinat� son girilinden sat�r koordinat�ndan b�y�k olup olmad���n� kontrol ediyor
			   while (x1 >= x2){ // E�er b�y�kse k���k olan koordinat b�y�k olan koordinata e�it olana kadar devam ediyor 
 		   			 alan[x2][y1]=x; // Baslangic koordinat�ndan bitis koordinat�na kadar ba�lang�� koordinat�ndaki elemana e�itliyor
						 x2=x2+1;
					 }			  
			    }
		}			
	if (elemankontrol(alan,mtr,eleman)==1){ 
	   	for( i = 0; i < N; i++ ) { // 
		 		 for( j = 0; j < N; j++ ) {
		   	 	 	  alan[i][j]=sakla[i][j]; // Ge�ersiz hamleden �nceki oyun alan�na geri d�n�yor
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
 Bu fonksiyonda ise se�ti�i bir eleman� oyun alan�ndan oyun ba�lan�c�ndaki iki koordinat haricinde kald�r�yor
 @param alan  Oyun alan�
 @param mtr   Oyun alan�ndaki elemanlar�n koordinatlar�n� saklad���m matris
*/	
void elemanikaldir(int alan[ ][20],int mtr[][20]){
	 int eleman,i,j;
	 printf("Kaldirmak istediginiz elemani seciniz:\n");
	 scanf("%d",&eleman);
	 for( i = 0; i < N; i++ ) {
			 for( j = 0; j < N; j++ ) {
			 	  if(alan[i][j]==eleman){ // E�er i j koordinatlar�ndaki eleman se�ilen elemana e�it ise i j koordinat�n� s�f�rl�yor
				   		alan[i][j]=0;			 
				   }
			  }
	}
	 for( i = 0; i < 2*eleman; i++ ) { 
	  	  if (mtr[0][i]==eleman){ // mtr matrisinde saklad���m ilk 2 koordinat�da s�f�rlad���m i�in burada ikisinide yine alana yazd�r�yorum
			 	alan[mtr[1][i]][mtr[2][i]]=eleman;  
		   }
	 }
}
/**
 Bu fonksiyonda oyun bitirildi�inde bo� alan var m� diye kontrol ediyor 
 @param alan  Oyun alan�
 @return 0    
*/	
int alankontrolet(int alan[ ][20]){
	 int i,j,sayac=0;
	 for( i = 0; i < N; i++ ) {
			 for( j = 0; j <N; j++ ) {
			 	if (alan[i][j]==0){ // E�er i j koordinatlari 0a e�it ise sayac� artt�r�yorum
				 sayac++;
				 }
		}
	}
	if (sayac>0){ // E�er sayac 0dan buyukse 0 olarak d�n�yor 
	   return 0; 
	}
}
/**
 Bu fonksiyonda elemanlar�n birbiri ile e�le�ip e�lemedi�ine bak�yorum yani oyun alan�nda ba�lang�� koordinat�ndaki ayn� 2 eleman�n birbiri
 ile e�lemesini kontrol ediyorum 
 @param alan   Oyun alan�
 @param mtr    Oyun alan�ndaki elemanlar�n koordinatlar�n� saklad���m matris
 @param eleman Oyun alan�ndaki eleman sayisi
 @return 0    
*/	
int eslemekontrol(int alan[ ][20],int mtr[][20],int sakla[][20],int eleman){
	int i,j,m,k,sayac;
	for( i = 0; i < N; i++ ) { // eslesmekontrol fonksiyonunda oyun alan�nda de�i�iklik yapt���m i�in oyun alan�n� de�i�tirmeden
			 for( j = 0; j < N; j++ ) { // sakla matrisinde de�i�iklikleri yap�yorum 
		  	 	 sakla[i][j]=alan[i][j]; 
			}
		}
	for(k=0;k<2*eleman;k+=2){ 
	m=mtr[0][k]; // Eleman�n numaras�
	i=mtr[1][k]; // Eleman�n sat�r koordinat�
	j=mtr[2][k]; // Eleman�n sutun koordinat� 
	while((i!=mtr[1][k+1])||(j!=mtr[2][k+1])){ // Elemandan saklada 2 tane bulunuyor  i ve j yi bir tane koordinata e�itlerken burada
											   // i ve j di�er koordinata e�it olana kadar d�ng�n�n devam etmesini sa�l�yorum 
		sayac=0;
		if(sakla[i][j-1]==m){ // Eleman�n solunda ayn� elemandan olup olmad���n� kontrol ediyorum
	 	    sakla[i][j]=0;	// Sola gittikten sonra tekrar sa�a d�nmemesi i�in i j koordinat�n� s�f�rl�yorum	
			j=j-1;	// Sutunu azaltarak soldan devam etmesini sa�l�yorum				 							 
			sayac++;
		}		 
		if(sakla[i][j+1]==m) { // Eleman�n sa��nda ayn� elemandan olup olmad���n� kontrol ediyorum
			sakla[i][j]=0; // Sa�a gittikren sonra tekrar sola d�nmemesi i�in i j koordinat�n� s�f�rl�yorum
			j=j+1;	// Sutunu artt�rarak sa�dan devam etmesini sa�l�yorum				 							 
			sayac++;		
		}											
		if(sakla[i-1][j]==m){ // Eleman�n yukar�s�nda ayn� elemandan olup olmad���n� kontrol ediyorum
			sakla[i][j]=0;	// Yukar� ��kt�ktan sonra tekrar a�a��ya inmemesi i�in i j koordinat�n� s�f�rl�yorum
			i=i-1;	// Sat�r� azaltarak yukar�dan devam etmesini sa�l�yorum				 							 
			sayac++;
		}			
		if(sakla[i+1][j]==m){ // Eleman�n a�a��s�nda ayn� elemandan olup olmad���n� kontrol ediyorum
			sakla[i][j]=0; // A�a�� indikten sonra tekrar yukar� ��kmamas� i�in i j koordinat�n� s�f�rl�yorum
			i=i+1;	// Sat�r� artt�rak a�a��dan devam etmesini sa�l�yorum					 							 
	    	sayac++;
	    }
		if (sayac==0){ // Kontrol edilirken oyun alan�n�n durumuna g�re while d�ng�s�nden ��kacak koordinatlar� s�f�rl�yor 
		   if (sakla[mtr[1][k+1]][mtr[2][k+1]]==0){ // E�er ��k�� koordinatlar� 0 ise d�ng�den ��kmas� i�in
		   	  	i=mtr[1][k+1]; // i ve j yi d�ng�den ��kacak koordinatlara e�itliyorum
				j=mtr[2][k+1];
				sayac++;	 							   
				 }
		   }
		if (sayac==0){ // e�er etraf�nda ayn� elamandan bulamazsa fonksiyondan ��k�yor
		return 0;
		}	
	}
	}
}
/**
 Bu fonksiyonda oyuncunun elemanlar�n oyunun ba�lang�c�ndaki koordinatlar�n� de�i�tirip de�i�tirmedi�ine bak�yor 
 @param alan   Oyun alan�
 @param mtr    Oyun alan�ndaki elemanlar�n koordinatlar�n� saklad���m matris
 @param eleman Oyun alan�ndaki eleman sayisi
 @return 1    
*/	
int elemankontrol(int alan[ ][20],int mtr[][20],int eleman){
	int i ,sayac, x, y ;
	sayac=0;
	for (i=0;i<2*eleman;i++){
		x=mtr[1][i]; // Eleman�n sat�r say�s�n� x'e e�itliyor 
		y=mtr[2][i]; // Eleman�n sutun say�s�n� y'ye e�itliyor
		if(alan[x][y]!=mtr[0][i]){ // Oyunun ba�lang�c�ndaki koordinatlar� saklad���m mtr matrisine g�re alandaki ba�lang�� koordinatlar�ndaki
			sayac++;               // elemanlar�n de�i�ip de�i�medi�ini kontrol ediyor e�er de�i�mi�se sayac� artt�r�yor					  
		}
	}
	if (sayac!=0){ // E�er sayac 0a e�it de�ilse  1 olarak d�n�yor 
	   return 1;
	}
}
/**
 Bu fonksiyonda oyuncunun her hamlesi sonras�  ne yapmak istedi�ine g�re oyunu devam ettiriyor 
 @param alan   Oyun alan�
 @param mtr    Oyun alan�ndaki elemanlar�n koordinatlar�n� saklad���m matris 
 @param sakla  Oyunu geri almak i�in son hamleyi saklad���m matris   
 @param eleman Oyun alan�ndaki eleman sayisi
*/	
void menu(int alan[ ][20],int sakla[][20],int mtr[][20],int eleman){
	int i,j,k;
	char cevap ;
	printf("Devam etmek icin E'ye ,geri almak icin G'ye basiniz,elemani kaldirmak icin K'ya basinin,bitirmek icin B'ye basiniz' ");
	scanf("%s",&cevap);
	if (cevap =='E'){ // cevap E ise oynamaya devam ediyor
 	oyna(alan,sakla,mtr,eleman);
	}		
	 else if  (cevap =='G'){ // cevap G ise son hamleyi geri al�yor 
	   	for( i = 0; i < N; i++ ) {
			 for( j = 0; j < N; j++ ) {
		  	 	 alan[i][j]=sakla[i][j]; 	
			}
		}
		system("CLS");
		drawBoard(alan);
    	oyna(alan,sakla,mtr,eleman);
	}	
	else if  (cevap =='K'){ // Cevap K ise alandan istedi�ini eleman� kald�r�yor 
		elemanikaldir(alan,mtr);
		system("CLS");
		drawBoard(alan);
    	oyna(alan,sakla,mtr,eleman);
	}
	else if  (cevap =='B'){ // Cevap B ise oyunun bitirilip bitirilmedi�ini kontrol ediyor 
		if(alankontrolet(alan)==0){ // E�er alankontrolet fonksiyonu 0 ise oyunda bo� alan oldu�u anla��l�yor 
			printf("Oyunda bos alan var\n");
			oyna(alan,sakla,mtr,eleman);
		}
		if(eslemekontrol(alan,mtr,sakla,eleman)==0){ // E�er eslesmekontrol 0 ise oyunda e�le�memi� eleman oldu�u anla��l�yor
			printf("Oyunda eslesmemis eleman var\n");
			elemanikaldir(alan,mtr);
			system("CLS");
			drawBoard(alan);
			oyna(alan,sakla,mtr,eleman);							 
			}
	
	}
	else {
	printf("Yanlis harf girildi\n"); // Yukar�daki harfler d���nda bir harf girilirse uyar� verdirtiyorum
	menu(alan,sakla,mtr,eleman);
    }
}
