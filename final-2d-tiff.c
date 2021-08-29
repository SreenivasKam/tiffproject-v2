#include<stdio.h>
#include<stdlib.h>
#include<math.h>
int a[10];
int p;




struct TIFF_header{
char FOR[2];
short int ARB;
int IFD_OFFSET;
};

struct DIR_header{
short int TAG;
short int Type;
int count;
int value;
};

    
struct IFD_header{
    struct DIR_header *Taglist;
};
int power(int exponent)
{
    int result=1;
    for (exponent; exponent>0; exponent--)
        {
        result = result * 2;
        }
    return result;
}

void maketiff(){
    FILE *txt,*ptr;
    char c;
    char one = 255;
    char zero = 0;
    int sum = 0,num=1,m=0;
    
    //txt=fopen("D:/FINAL YEAR PROJECT/maketiffer2.tiff","wb");
    txt=fopen("D:/FINAL YEAR PROJECT/R-7.tiff","wb");
    //FILE *fp = fopen("C:/Users/sreen/Downloads/SampleUncompressed.tiff","rb");
    //ptr=fopen("D:/FINAL YEAR PROJECT/work/mod_cmp_1.5d_3.txt","rb");
    //ptr=fopen("D:/FINAL YEAR PROJECT/work/mod_cmp_1.5d_1.txt","rb");
    ptr=fopen("D:/FINAL YEAR PROJECT/work/edittedcode2d_1.txt","rb");
    fseek(txt,0,SEEK_SET);
    if (txt == NULL) {
        printf("Error!");
        exit(1);
    }
    else{
        // 186 IS THE MAGIC NUMBER REQUIRED 
        struct TIFF_header header = {"II",42,8};
        fseek(txt,0,SEEK_SET);
        fwrite(&header, sizeof(header), 1, txt);

        fseek(txt,8,SEEK_SET);
        short int value2 = 15 | (0<<8);// number of ifd entries
        fputc(value2,txt);
        //tags
        struct DIR_header tags[15] ={ {254,4,1,2},
        {255,3,1,3},
        {256,3,1,1728},
        {257,3,1,2707},
        {258,3,1,1},
        {259,3,1,3},
        {262,3,1,0},
        {273,4,1,240},
        {278,3,1,2707},
        //{279,4,1,741682},
        {279,4,1,742896},
        {274,3,1,1},
        {277,3,1,1},
        {292,4,1,5},
        {284,3,1,1},
        {296,3,1,2}}; 
        long d[1] ={6912};
        long b[1] ={216};
        printf("\nTHE UPDATED PARAMETER OF IFD\n");
        printf("\033[1;32m");
        for(int i=0;i<15;i++){
            if(i==2 || i==3 ||i==5||i==7||i==8||i==9||i==12){
                printf("\033[1;31m");
            }
            printf("TAG:%d TYPE:%d VALUE:%d\n",tags[i].TAG,tags[i].Type,tags[i].value);
            printf("\033[1;32m");
        }
        printf("\033[0m"); 
        printf("\n\n\n\n\n\n");
         

        fseek(txt,10,SEEK_SET);
        fwrite(tags, sizeof(tags), 1, txt);
        fseek(txt,190,SEEK_SET);

        //next ifd offset
        int value3 = 0 | (0<<8) | (0<<16) | (0<<24); 
        fputc(value3,txt);

        unsigned long r[2]={200,1};
        unsigned long i[2]={70,1};
        fseek(txt,200,SEEK_SET);
        fwrite(r,sizeof(r),1,txt);
        fseek(txt,220,SEEK_SET);
        fwrite(i,sizeof(i),1,txt);
        fseek(txt,240,SEEK_SET);
        if (ptr == NULL)
        {
            printf("File is not available \n");
        }
        else{
            while ((c = fgetc(ptr)) != EOF)
            {   
                ///p++;
                fseek(ptr,8*m,SEEK_SET);
                m++;
                for(int k=7;k>=0;k--){
                    fread(&c,sizeof(char),1,ptr);
                    //printf("%d",c-48);
                    //printf("%d\t",power(k));
                    num = (c-48)*power(k);
                    sum +=num;
                    p++;
                    //printf("%d\t",c-48);
                    
                }
                //printf("\n");
                fseek(ptr,8*(m+1),SEEK_SET);
                //printf("\n%d\n",sum);
                fputc(sum,txt);
                sum=0;
            }
        }
        p+=8;
        printf("%d",p);
        fseek(txt,240+p,SEEK_SET);
        fputc(EOF,txt);
       //value2 = 13 | (0<<8);// number of ifd entries
       //fputc(value2,txt);
    }
       fclose(txt);
       fclose(ptr);




}
int binary(int n){
    int d,i;
    //printf("Enter the number");
    //scanf("%d", &n);
    //printf("the number is %d\n",n);
    
    for(i = 7;n>0;i--){
        a[i] = n%2;
        n = n/2;
        //printf("%d\t %d\n",a[i],i);
    }
    //sprintf("\n%d\n",i);
    
    for(d=0;d<=i;d++){
        a[d]=0;
    }
    for(int k=0;k<=57;k++){
        //printf("%d",a[k]);
    }
}



int main(){
    maketiff();
}