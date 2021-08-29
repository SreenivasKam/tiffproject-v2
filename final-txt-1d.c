#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int a[7];

struct codewords{
    int number;
    char codew[25];
};

struct codewords terminalb[65];
struct codewords terminalw[65];
struct codewords makeupb[41];
struct codewords makeupw[41];

void readbterminal(){
    FILE *txt;
    int r; char c[25];
    txt = fopen("C:/Users/sreen/Downloads/terminal_cw_b.txt","rb");
    if(txt == NULL){
        printf("Error in opening the file");
    }
    else{
        for(int i =0;i<64;i++){
            fscanf(txt,"%d",&r);
            fscanf(txt,"%s",&c);
            terminalb[i].number=r;
            strcpy(terminalb[i].codew,c);
        }
        /*
        for(int i=0;i<64;i++){
            printf("%d\t%s\n",terminalb[i].number,terminalb[i].codew);
        }
        */
    }
    fclose(txt);
}
void readwterminal(){
    FILE *txt;
    int r; char c[25];
    txt = fopen("C:/Users/sreen/Downloads/terminal_cw_w.txt","rb");
    if(txt == NULL){
        printf("Error in opening the file");
    }
    else{
        for(int i =0;i<64;i++){
            fscanf(txt,"%d",&r);
            fscanf(txt,"%s",&c);
            terminalw[i].number=r;
            strcpy(terminalw[i].codew,c);
        }
        /*
        for(int i=0;i<64;i++){
            printf("%d\t%s\n",terminalw[i].number,terminalw[i].codew);
        }
        */
    }
    fclose(txt);
}
void readbmakeup(){
    FILE *txt;
    int r; char c[25];
    txt = fopen("C:/Users/sreen/Downloads/makeup_cw_b.txt","rb");
    if(txt == NULL){
        printf("Error in opening the file");
    }
    else{
        for(int i =0;i<40;i++){
            fscanf(txt,"%d",&r);
            fscanf(txt,"%s",&c);
            makeupb[i].number=r;
            strcpy(makeupb[i].codew,c);
        }
        /*
        for(int i=0;i<40;i++){
            printf("%d\t%s\n",makeupb[i].number,makeupb[i].codew);
        }*/
    }
    fclose(txt);
}
void readwmakeup(){
    FILE *txt;
    int r; char c[25];
    txt = fopen("C:/Users/sreen/Downloads/makeup_cw_w.txt","rb");
    if(txt == NULL){
        printf("Error in opening the file");
    }
    else{
        for(int i =0;i<40;i++){
            fscanf(txt,"%d",&r);
            fscanf(txt,"%s",&c);
            makeupw[i].number=r;
            strcpy(makeupw[i].codew,c);
        }
        /*
        for(int i=0;i<40;i++){
            printf("%d\t%s\n",makeupw[i].number,makeupw[i].codew);
        }
        */
    }
    fclose(txt);
}
char putsss[25];
char binary(int n){
    int d,i;
    char *s;
    
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
    for(int k=0;k<=7;k++){
        //printf("%d",a[k]);
    }
    for (i = 0; i <=7; i++) {
        s = s + a[i];
    }
    return *s;

}
void printandwrite(int csum,int temp,FILE* txt){
    //printf("%d->%d\t",temp,csum);
    if(temp == 0){
        if(csum <=63){
            fputs(terminalw[csum].codew,txt);

        }
        else{
            if(csum%64==0){
                fputs(makeupw[(csum/64)-1].codew,txt);
                fputs(terminalw[0].codew,txt);
            }
            else{
                fputs(makeupw[(csum/64)-1].codew,txt);
                fputs(terminalw[(csum%64)].codew,txt);
            }

        }


    }
    else{
        if(csum <=63){
            fputs(terminalb[csum].codew,txt);

        }
        else{
            if(csum%64==0){
                fputs(makeupb[(csum/64)-1].codew,txt);
                fputs(terminalb[0].codew,txt);
            }
            else{
                fputs(makeupb[(csum/64)-1].codew,txt);
                fputs(terminalb[(csum%64)].codew,txt);
            }

        }

    }
}
void makerle3(){
    FILE *txt,*ftr;
    char c,q[]="0000000000000001",e[]="000000000001";
    int  sum =0,y=1,csum=0,count =1800,width,imagewidth = 3456;
    int temp =-1,ones=1;
    ftr = fopen("D:/FINAL YEAR PROJECT/sample_bin_uc16.txt","rb");
    txt = fopen("D:/FINAL YEAR PROJECT/work/rled11.txt","wb");
    if(ftr == NULL){
        printf("Error in opening the file");
    }
    else{
        fputs(q,txt);
        //fputc('\n',txt);
        while((c=fgetc(ftr)) !=EOF){
            c = c-'0';
            if(c<0){
                continue;
            }
            if(ones==1){
                ones = 0;
                if(c!=0){
                    printf("0->0\t");
                    fputs(terminalw[0].codew,txt);

                }
                //csum = csum+1;
                temp = c;
            }
            else
            {
                if(c == temp && csum+sum<=1726){
                    csum = csum+1;
                }
                else
                {
                    
                    csum = csum+1;
                    printandwrite(csum,temp,txt);
                    temp = c;
                    if(!(csum+sum<=1727)){
                        sum = 0;
                        csum =0;
                        fputc('\n',txt);
                    }
                    sum = sum + csum;
                    csum =0;
                }
            }
            

        }
        csum = csum+1;
        printandwrite(csum,temp,txt);
          
        
    }
    fclose(txt);
    fclose(ftr);
}
char d[50];
void makeeols(int sum,FILE* txt){
    char c,q[]="0000000000000001",e[]="000000000001",z[]="000000000001";
    int n=0;
    sum = sum-1;
    if(sum%8==0){
        fputs(q,txt);
    }
    else
    {
        n = sum%8;
        //printf("%d\n",n);
        if(n==4){
            fputs(e,txt);
            
        }
        else
        {
            switch(n) {
                case 1 :
                    fputc('0',txt);
                    fputc('0',txt);
                    fputc('0',txt);
                    fputs(e,txt);
                    break;
                case 2 :
                    fputc('0',txt);
                    fputc('0',txt);
                    fputs(e,txt);
                    break;
                case 3 :
                    fputc('0',txt);
                    fputs(e,txt);
                    break;
                case 5 :
                    fputc('0',txt);
                    fputc('0',txt);
                    fputc('0',txt);
                    fputs(q,txt);
                    break;
                case 6 :
                    fputc('0',txt);
                    fputc('0',txt);
                    fputs(q,txt);
                    break;
                case 7 :
                    fputc('0',txt);
                    fputs(q,txt);
                    break;
            }
        }
    }

}
void byteboundaryfixing()
{
    FILE *txt,*ftr;
    char c,q[]="0000000000000001",e[]="000000000001",z[]="000000000001",r=0,t=1;
    int sum=0,p=0,n=0;
    ftr = fopen("D:/FINAL YEAR PROJECT/work/rled11.txt","rb");
    txt = fopen("D:/FINAL YEAR PROJECT/work/edittedcode-1d-4.txt","wb");
    if(ftr == NULL){
        printf("Error in opening the file");
    }
    else
    {
        while((c=fgetc(ftr)) !=EOF){
            c= c-'0';
            sum = sum+1;
            //printf("%d",c);
            if(c==-38){
                makeeols(sum,txt);
                sum =0;
            }
            if(c==0){
                fputc('0',txt);
            }
            else
            {
                if(c==1)
                {
                    fputc('1',txt);
                }
            }
        }
        printf("%d",sum);
        makeeols(sum+1,txt);
    }
    for(int i=0;i<5;i++){
        fputs(e,txt);
    }
    fclose(txt);
    fclose(ftr);
}

int main(){
    readbterminal();
    //printf("%d\t%s\n",terminalb[0].number,terminalb[0].codew);
    readwterminal();
    //printf("%d\t%s\n",terminalw[0].number,terminalw[0].codew);
    readbmakeup();
    printf("%d\t%s\n",makeupb[26].number,makeupb[26].codew);
    readwmakeup();
    //printf("%d\t%s\n",makeupw[1].number,makeupw[1].codew);
    makerle3();
    byteboundaryfixing();

}