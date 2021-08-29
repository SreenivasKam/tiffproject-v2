#include<stdio.h>
#include<stdlib.h>
#include<string.h>

char refline[1728];
char codingline[2560][1728];

int a[7];

struct codewords{
    int number;
    char codew[25];
};

struct elements{
    int number;
    int value;
};



struct codewords terminalb[65];
struct codewords terminalw[65];
struct codewords makeupb[41];
struct codewords makeupw[41];

void assign(struct elements temp){
    temp.number = -1;
    temp.value = 0;
}

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
void encode2d(int count,int p,FILE* txt){
    //printf("\n\n\n\n%d\n\n\n\n",count);
    char e[]="0000000000010";
    //printf("\n\n\nfirst time bro\n\n\n%d\t%d\t%d\t%d\t%d\t%d",a0.number,a0.value,a1.number,a1.value,a2.number,a2.value);
    fputs(e,txt);
    //fputc('\n',txt);
    //printf("\n\n");
    int tsum = 0;
    int k1=-1,sum=0,k2=-1,k3 =-1,sum1=0,sum2=0,temp=-1,temp1=-1,n=0,o=0,v=0,once=0,once1=0;
    char H[]="001",P[]="0001";
    char q_1[]="011",q_2[]="00011",q_3[]="0000011",q1[]="010",q2[]="000010",q3[]="0000010";
    struct elements a0;
    struct elements a1;
    struct elements a2;
    struct elements b1;
    struct elements pa;
    struct elements b2;
    pa.number=-1;pa.value=0;
    a0.number = -1;a0.value=0;
    a1.number = -1;a1.value=0;
    a2.number = -1;a2.value=0;
    b1.number = -1;b1.value=0;
    b2.number = -1;b2.value=0;
    while(a0.value<=1728 & a1.value<=1728){
        pa = a0;
        //printf("\n--------------------------------------------------------------------------\n");
        for(int i=a0.value;i<1728;i++){
            if(i==1727){
                sum = 1728;
                break;
            }
            if(sum>1728){
                a1.value = 1728;
                break;
            }
            if(k1==-1){
                k1 = 0;
                temp = codingline[count][i];
                sum = sum+1;
            }else{
                if(codingline[count][i]== temp){
                    sum = sum+1;
                }
                else{
                    //printf("%d->%d\t",temp,sum);
                    temp = codingline[count][i];
                    //printf("temp = %d\n",temp);
                    if(a1.number==-1){
                        a1.number = temp;
                        if(temp ==1){
                            a0.number = 0;
                        }else{
                            a0.number = 1;
                        }
                        a1.value = sum;

                        break;
                    }
                    sum = sum+1;
                }
            }
            if(i==1727){
                once=1;
                
            }
        }
        if(once== 1 | sum == 1728){
            once =0;
            temp = codingline[count][1727];
                if(a1.number==-1){
                    a1.number = temp;
                    if(temp ==1){
                        a0.number = 0;
                    }else{
                        a0.number = 1;
                    }
                    a1.value = sum;
                }
        }
        //printf("\nNumbers of \ta0=%d\t\ta1=%d\n",a0.number,a1.number);
        //printf("Values of \ta0=%d\ta1=%d\tsum=%d\n",a0.value,a1.value,sum);
        
        for(int i=b2.value;i<1728;i++){
            if(k2==-1){
                k2 = 0;
                if(p>=2){
                    temp1 = codingline[count-1][i];
                } 
                else{
                    temp1 = refline[i];
                    //printf("temp1===%d\n",temp1);
                }
                sum1 = sum1 +1;
            }
            else{
                if(p>=2){
                    if(codingline[count-1][i]==temp1){
                        sum1 = sum1 +1;
                    }
                    else{
                        //printf("%d->%d\t",temp1,sum1);
                        temp1 = codingline[count-1][i];
                        if(b1.number==-1){
                            b1.number = temp1;
                            b1.value = sum1;
                        }
                        else{
                            if(b2.number==-1){
                                b2.number = temp1;
                                b2.value = sum1;
                                break;
                            }
                        }
                        sum1 = sum1+1;
                    }


                }
                else{
                    if(refline[i]==temp1){
                        sum1 = sum1 +1;
                    }
                    else{
                        //printf("%d->%d\t",temp1,sum1);
                        temp1 = refline[i];
                        
                        if(b1.number==-1){
                            if(temp1 != a0.number & once1 == 0){
                                once1=1;
                                b1.number = temp1;
                                b1.value = sum1;
                            }
                            else{
                                b1.number = temp1;
                                b1.value = sum1;
                            }
                        }
                        else{
                            if(b2.number==-1){
                                b2.number = temp1;
                                b2.value = sum1;
                                break;
                            }
                        }
                        sum1 = sum1+1;
                    }

                }
            }
        }
        if(sum1>=1728 && b1.number==-1){
            b1.value = 1728;
            b2.value = 1728;
        }
        if(sum1 >= 1728){
            b2.value = 1728;
        }
        //printf("\nNumbers of \tb1=%d\tb2=%d\n",b1.number,b2.number);
        //printf("Values of \tb1=%d\tb2=%d\tsum = %d\n",b1.value,b2.value,sum1);
        
        if((b2.value - a1.value) <0){
            fputs(P,txt);
            a0.value = b2.value;
            a0.number = codingline[count][b2.value-1];
            //printf("\nPass mode\n");
            b1.number = -1;
            a1.number = -1;
            b2.number = -1;
            k1 = -1;
            k2 = -1;
        }
        else{
            v = (a1.value - b1.value);
            if(v<=3 && v>=-3){
                //printf("\nVertical mode V(%d)\n",v);
                switch (v)
                {
                    case 0:
                        fputc('1',txt);
                        break;
                    
                    case 1:
                        fputs(q_1,txt);
                        break;
                    
                    case 2:
                        fputs(q_2,txt);
                        break;
                    
                    case 3:
                        fputs(q_3,txt);
                        break;
                    
                    case -1:
                        fputs(q1,txt);
                        break;
                    case -2:
                        fputs(q2,txt);
                        break;
                    case -3:
                        fputs(q3,txt);
                        break;
                }   
                a0 = a1;
                a1.number = -1;
                b1.number = -1;
                b2.number = -1;
                k1 = -1;
                k2 = -1;
            }
            else{
                //printf("\nHozriontal Mode\n");
                for(int j=a1.value;j<1728;j++){
                    if(k3 == -1){
                        k3 = 0;
                        temp = a1.number;
                        sum = sum +1;
                    }
                    else{
                        if(codingline[count][j] == temp){
                            sum = sum +1;
                        }
                        else{
                            //printf("\nA2 detected %d->%d\n",temp,sum);
                            temp = codingline[count][j];
                            if(a2.number == -1){
                                a2.number = temp;
                                a2.value = sum;
                                break;
                            }
                            sum = sum +1;
                        }
                    }
                    if(j==1727){
                        once = 1;
                    }
                }
                if(once){
                    once = 0;
                    if(a1.number ==0){
                        a2.number = 1;
                        //printf("\nA2 detected %d->%d\n",a2.number,sum);
                    }
                    else{
                        a2.number = 0;
                       // printf("\nA2 detected %d->%d\n",a2.number,sum);
                    }
                    a2.value = 1728;
                }
                fputs(H,txt);
                printandwrite(a1.value - a0.value,a0.number,txt);
                printandwrite(a2.value - a1.value,a1.number,txt);
                a0 = a2;
                a1.number = -1;
                a2.number = -1;
                k1 = -1;
                k3 = -1;
                b1.number = -1;
                b2.number = -1;
                k2 =-1;
                //write horizonatal here and i think i fixed the end of line 1728 check for if condition a
                // after the initialization of a1s
            }
        }
        if(a0.value>=1728 & a1.value>=1728){
            break;
        }
        /*
        if(o<29){
            o++;
            continue;
        }
        else{
            a0.value = 1728;
        }
        */
    }
    printandwrite(a0.value - pa.value,pa.number,txt);
    /*
    printf("\n------------%%%%%%%%%%%%%%%%%%%%%%%%%%-------------------\n\nAfter the While loop\n\nNumbers of \ta0=%d\t\ta1=%d\n",a0.number,a1.number);
    printf("Values of \tpan=%d\tpav=%d\t\n",pa.number,pa.value);
    
    printf("Values of \ta0=%d\ta1=%d\tsum=%d\n",a0.value,a1.value,sum);
    printf("\nNumbers of \tb1=%d\tb2=%d\n",b1.number,b2.number);
    printf("Values of \tb1=%d\tb2=%d\tsum = %d\n",b1.value,b2.value,sum1);
*/
}


void make1d(int q,FILE* txt){
    int sum=0,tsum=0;
    int temp =-1;
    char e[]="0000000000011";
    fputs(e,txt);
    for(int i=0;i<1728;i++){
        if(temp==-1){
            temp =0;
            temp = refline[i];
            sum = sum+1;
        }
        else
        {
            if(refline[i]==temp){
                sum = sum+1;
            }
            else{
               // printf("%d->%d\t",temp,sum);
                printandwrite(sum,temp,txt);
                temp = refline[i];
                tsum = tsum +sum;
                sum = 1;
            }
        }
    }
    tsum = tsum +sum;
    //printf("%d->%d\t",temp,sum);
    printandwrite(sum,temp,txt);
    //fputc('\n',txt);
    //printf("\ntotal sum: %d\n",q);
}

void make2d(int k){
    int d=0,count=0,p=1,q=0;
    d = k;
    char c;
    FILE *txt,*ptr;
    ptr=fopen("D:/FINAL YEAR PROJECT/sample_bin_uc16.txt","rb");
    //ptr=fopen("D:/FINAL YEAR PROJECT/work/conter.txt","rb");
    txt=fopen("D:/FINAL YEAR PROJECT/new_2d.txt","wb");
    char e[]="0000000000011";
    //fputs(e,txt);
    if (txt == NULL) {
        printf("Error!");
        exit(1);
    }
    else
    {
        while((c = fgetc(ptr)) != EOF )//&& count!=48)
        {   
            while(k!=0)
            {
                if(k==d){
                    fseek(ptr,count*1729,SEEK_SET);
                    count++;
                    //printf("\n@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n\nref line %d\n",count);
                    for(int i=0;i<1728;i++){
                        c = fgetc(ptr);
                        if(c<0){
                            continue;
                        }
                        c=c-'0';
                        refline[i]=c;
                        //printf("%d",refline[i]);
                    }
                   // printf("\n");
                    make1d(count-1,txt);
                    //printf("1d worked\n");
                    q=+d;
                
                }
                else
                {
                    //fread(&refline,sizeof(char),1728,txt);
                    
                    fseek(ptr,count*1729,SEEK_SET);
                    count++;
                    //printf("\ncoding line %d %d",count,p++);
                    for(int i=0;i<1728;i++){
                        c = fgetc(ptr);
                        if(c<0){
                            continue;
                        }
                        c=c-'0';
                        codingline[count][i]=c;
                        ///printf("%d",codingline[count][i]);
                    }
                    //printf("%d",p);
                    encode2d(count,p-1,txt);
                    //printf("\n2d worked");
                    

                }
                k--;
            
            }
            fputc('\n',txt);
            k=d;
            p=1;
            
            c = fgetc(ptr);
            //fseek(ptr,count*1728,SEEK_SET);
            
        }
    }
    fclose(txt);
    fclose(ptr);
}
void append_zeros(int n,FILE* txt){
    for(int i=0;i<n;i++){
        fputc('0',txt);
    }

}

void makeeols(int sum,FILE* txt){
    char c,q[]="0000000000000001",oned[]="0000000000011",twod[]="0000000000010";
    int n=0;
    sum = sum-1;
    if(sum%8!=0){
        n = sum%8;
        //printf("%d\n",n);
        if(n==4){
            append_zeros(4,txt);
        }
        else
        {
          switch(n) {
                case 1 :
                    fputc('0',txt);
                    fputc('0',txt);
                    fputc('0',txt);
                    break;
                case 2 :
                    fputc('0',txt);
                    fputc('0',txt);
                    //fputs(e,txt);
                    break;
                case 3 :
                    fputc('0',txt);
                    //fputs(e,txt);
                    break;
                case 5 :
                    fputc('0',txt);
                    fputc('0',txt);
                    fputc('0',txt);
                    //fputs(q,txt);
                    break;
                case 6 :
                    fputc('0',txt);
                    fputc('0',txt);
                    //fputs(q,txt);
                    break;
                case 7 :
                    fputc('0',txt);
                    //fputs(q,txt);
                    break;
            } 
        }
    }

}
void byteboundaryfixing(int k)
{
    FILE *txt,*ftr;
    char c,q[]="0000000000000001",e[]="0000000000011",z[]="000000000001",r=0,t=1;
    int sum=0,p=0,n=0;
    ftr = fopen("D:/FINAL YEAR PROJECT/new_2d.txt","rb");
    txt = fopen("D:/FINAL YEAR PROJECT/work/edittedcode2d_1.txt","wb");
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
        //printf("%d",sum);
        makeeols(sum+1,txt);
    }
    
    for(int i=0;i<6;i++){
        fputs(e,txt);
    }
    
    fclose(txt);
    fclose(ftr);
}

int main(){
    int k = 2;
    readbterminal();
    //printf("%d\t%s\n",terminalb[0].number,terminalb[0].codew);
    readwterminal();
    //printf("%d\t%s\n",terminalw[0].number,terminalw[0].codew);
    readbmakeup();
    printf("%d\t%s\n",makeupb[26].number,makeupb[26].codew);
    readwmakeup();
    make2d(k);
    int count = 2560;
    byteboundaryfixing(k);
    /*
    printf("\n\n\n\n\nust for confirmation \ncoding line %d\n",count);
    for(int i=0;i<1728;i++){
        printf("%d",codingline[count][i]);
    }
    */
}