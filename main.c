#include <stdio.h>
#include <stdlib.h>
#include <time.h>


long int rozmiary[7] = {10000,25000,50000,75000,100000,250000,500000};
long long int temp=0;

void zapelnianie(int *m, int size, int zakres){
     srand(time (0));
     int i;
     for(i=0;i<size;i++){
        m[i]=rand()%zakres;
     }
}

void zamiana(int *p, long int i, long int j){
int c;
c=*(p+i);
*(p+i)=*(p+j);
*(p+j)=c;
}

int szukaj(int *p, int size, long int k){
    long int i;
    int min=p[k];
    long int adres=k;
    for(i=k+1;i<size;i++){
        if(p[i]<=min){
            adres=i;
        }
    }
    return adres;
}

void selection(int *m, long int size){
   long int i;
   for(i=0;i<size-1;i++){
        zamiana(m, szukaj(m,size,i),i);
        temp++;

   }
}


/*void pokaz(int *m, int size, int zakres){
    int i,j;
    for(i=0;i<zakres;i++){
        printf("%3i |", zakres-i);
        for(j=0;j<size;j++){
            if(m[j]==zakres-i){
                printf("*");
            }else{
                printf(" ");
            }
        }
        printf("\n");
    }
    printf("   ");
    for(j=0;j<size;j++){
            printf("_");
        }
}
*/
void bubble(int *m, long int size){
   long int licznik=0;
   long int i;
    while(licznik<size-1){
            licznik=0;
        for(i=0;i<size-1;i++){
            if(m[i]>m[i+1]){
                zamiana(m,i,i+1);
                temp++;
                }else{
                    licznik++;
                }
            }

        }

    }


void insertion(int *m,long int size){
    long int i,j;
    int buf;
    for(i=1;i<size;i++){
            buf=m[i];
            for(j=i-1;j>=0 && m[j]>buf;--j){
                m[j+1]=m[j];
                temp++;
            }
            m[j+1]=buf;
            temp++;
    }
}



void wypisywanie(int *m, long int size){
    long int i;
    for(i=0;i<size;i++){
        printf("%i \n",m[i]);
    }
}

void do_pliku(int * m,long int size, FILE * file){
    long int i;
    for(i=0;i<size;i++){
       fprintf(file,"%i ",m[i]);
    }
}

void copymatrix(int *in,int *out, int size){
    long int i;
    for(i=0;i<size;i++){
        out[i]=in[i];
    }
}

int main()
{
    FILE * in = fopen("in.txt","w");
    FILE * out = fopen("out.txt","w");

    FILE * dane = fopen("dane.txt","w");
    clock_t start;
    clock_t end;

    int i;
    for(i=0;i<6;i++){


        int * origin;

        origin = (int*)calloc(rozmiary[i],sizeof(int));

        int * matrix;

        matrix = (int*)calloc(rozmiary[i],sizeof(int));

        zapelnianie(origin,rozmiary[i],32000);
        do_pliku(origin,rozmiary[i],in);


        copymatrix(origin,matrix,rozmiary[i]);


            printf("bubble rozmiar:%i " , rozmiary[i]);
            start=clock();
            bubble(matrix,rozmiary[i]);
            end=clock();
            fprintf(dane, "%lli %f ",temp , (float)(end - start) / CLOCKS_PER_SEC);
            temp =0;
            do_pliku(matrix,rozmiary[i],out);
           // system("pause");
            rewind(out);

        copymatrix(origin,matrix,rozmiary[i]);

            printf("selection rozmiar:%i " , rozmiary[i]);
            start=clock();
            selection(matrix,rozmiary[i]);
            end=clock();
            fprintf(dane, "%lli %f ",temp , (float)(end - start) / CLOCKS_PER_SEC);
            temp =0;
            do_pliku(matrix,rozmiary[i],out);
           // system("pause");
            rewind(out);

        copymatrix(origin,matrix,rozmiary[i]);

            printf("insertion rozmiar:%i " , rozmiary[i]);
            start=clock();
            insertion(matrix,rozmiary[i]);
            end=clock();
            fprintf(dane, "%lli %f \n",temp , (float)(end - start) / CLOCKS_PER_SEC);
            temp =0;
            do_pliku(matrix,rozmiary[i],out);
           // system("pause");
            rewind(out);


    }

    fclose(in);
    fclose(out);
    fclose(dane);
    return 0;
}
