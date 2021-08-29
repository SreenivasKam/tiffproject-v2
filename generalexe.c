#include<stdio.h>
#include<stdlib.h>
#include<math.h>

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


void opentifffile(){
    short int NumberofDirEntries;
    int i=0,StripsInImage,pixels;
    long *array,*barray;
    int Nextoffset;
    int minimunifd=1,k=0;
    long data1,data2;
    int Imagelength,Rowsperstrip,Stripoffset,Stripoffsetcount,StripBytecounts,StripoffsetType;
    int StripBytecountType,StripBytecountscount,ImageWidth,Sampleperpixel;
    char c;
    FILE *txt;
    txt=fopen("D:/FINAL YEAR PROJECT/sample_bin_uc16.txt","wb");
    struct TIFF_header Tiffheader;
    struct IFD_header Ifdheader;


    //FILE *fp = fopen("D:/FINAL YEAR PROJECT/work/faximage_aTw5.tif","rb");
    //D:/FINAL YEAR PROJECT/maketiff4.tiff
    //D:/FINAL YEAR PROJECT/maketiff45678.tiff
    //FILE *fp = fopen("D:/FINAL YEAR PROJECT/Sample3_3pg.tiff","rb");
    FILE *fp = fopen("C:/Users/sreen/Downloads/SampleUncompressed.tiff","rb");
    //FILE *fp = fopen("D:/FINAL YEAR PROJECT/maketiffer3.tiff","rb");
    //FILE *fp = fopen("D:/FINAL YEAR PROJECT/maketiff45678.tiff","rb");
    printf("\n----------------------TIFF FILE HEADER--------------------------\n\n");
    fread(&Tiffheader,sizeof(struct TIFF_header),1,fp);
    printf("Format: %c%c \n",Tiffheader.FOR[0],Tiffheader.FOR[1]);
    printf("Arbitary Value: %d\n",Tiffheader.ARB);
    printf("IFD OFFSET: %d \n",Tiffheader.IFD_OFFSET);

    while(minimunifd){


    printf("\n-------------------------IFD HEADER-----------------------------\n\n");
    fseek(fp,Tiffheader.IFD_OFFSET, SEEK_SET);
    fread(&NumberofDirEntries,sizeof(short int),1,fp);
    printf("The Number of Directories in the File is: %d\n",NumberofDirEntries);


    Ifdheader.Taglist = (struct DIR_header*)malloc(NumberofDirEntries*sizeof(struct DIR_header));
    for(i=0;i<NumberofDirEntries;i++){
    fread(&Ifdheader.Taglist[i],sizeof(struct DIR_header),1,fp);
    }
    
    printf("\n-------------------------DIRECTORIES-----------------------------\n\n");
    for (i=0;i<NumberofDirEntries;i++ ){
    //fread(&Ifdheader,NumberofDirEntries*sizeof(struct DIR_header),1,fp);
    
    printf("%d. Tag:  %d\n",i+1,Ifdheader.Taglist[i].TAG);
    printf("%d. Value:%d\n\n\n",i+1,Ifdheader.Taglist[i].value);
    if(Ifdheader.Taglist[i].TAG==257){
        Imagelength = Ifdheader.Taglist[i].value;
    }
    if(Ifdheader.Taglist[i].TAG==278){
        Rowsperstrip = Ifdheader.Taglist[i].value;
    }
     if(Ifdheader.Taglist[i].TAG==256){
        ImageWidth= Ifdheader.Taglist[i].value;
    }
    if(Ifdheader.Taglist[i].TAG==273){
        Stripoffset = Ifdheader.Taglist[i].value;
        StripoffsetType = Ifdheader.Taglist[i].Type;
        Stripoffsetcount = Ifdheader.Taglist[i].count;
    }
    if(Ifdheader.Taglist[i].TAG==279){
        StripBytecounts = Ifdheader.Taglist[i].value;
        StripBytecountType = Ifdheader.Taglist[i].Type;
        StripBytecountscount = Ifdheader.Taglist[i].count;
    }
    if(Ifdheader.Taglist[i].TAG==277){
        Sampleperpixel = Ifdheader.Taglist[i].value;
    }
    

    }
    fread(&Nextoffset,sizeof(int),1,fp);
    printf("Next Offset: %d\n\n",Nextoffset);

    minimunifd = Nextoffset;
    Tiffheader.IFD_OFFSET = Nextoffset;


    StripsInImage = floor((Imagelength +(Rowsperstrip  - 1)) / Rowsperstrip);
    printf("StripsInImage: %d\n",StripsInImage);



    if(StripoffsetType*Stripoffsetcount >=5){
        fseek(fp,Stripoffset,SEEK_SET);
        fread(&data1,sizeof(long),1,fp);
        printf("\n-------------------------OFFSET VALUES-----------------------------\n\n");
        printf("\nThe value of is:\n");
        array =(long*)malloc(Stripoffsetcount*sizeof(long));
        array[0]=data1;

        for(i=1;i<Stripoffsetcount;i++){
            fread(&data1,sizeof(long),1,fp);
            array[i] =  data1;
        }
         for(i=0;i<Stripoffsetcount;i++){
             printf("%d\t",array[i]);
        }

    }

    if(StripBytecountscount*StripBytecountType>=5){
        // configure next line 
        fseek(fp,StripBytecounts,SEEK_SET);
        fread(&data2,sizeof(long),1,fp);
        printf("\n\n\n-------------------------OFFSET BYTE COUNT VALUES-----------------------------\n");
        printf("\n\nThe value of is bytes:\n");
        barray =(long*)malloc(Stripoffsetcount*sizeof(long));
        barray[0] = data2;
        for(i=1;i<Stripoffsetcount;i++){
            fread(&data2,sizeof(long),1,fp);
            barray[i] =  data2;
        }
        for(i=0;i<Stripoffsetcount;i++){
            printf("%d\t",barray[i]);
            }
    }


    if(Stripoffsetcount>2){
        int width = 1;
        for(int i=0;i<Stripoffsetcount;i++){
            if(i){
                fputc('\n',txt);
            }
            pixels=0;
            width =1;
            fseek(fp,array[i],SEEK_SET);
            while(pixels!=barray[i]){
                pixels++;
                if((width)%((ImageWidth*Sampleperpixel)+1)==0){
                    fputc('\n',txt);
                    width = 1;
                }
            width++;
            fread(&c,sizeof(char),1,fp);
            if(c&&1 == 1)
                {
                        fputc('0',txt);
                    
                    //fputc('1',txt);//before the changes
                }
            else
                {
                        fputc('1',txt);
                    //fputc('0',txt);//before the changes
                }
            }
        }
        //fputc(EOF,txt);
        k=1;
    }
    else
    {
        int width = 1;
        pixels =0;
        fseek(fp,Stripoffset,SEEK_SET);
        while(pixels!=StripBytecounts){
            pixels++;
            if(width%(ImageWidth+1)==0){
                //fputc('\n',txt); // add this line if u wat it to be in lines
                
                width = 1;

            }
            width++;
            fread(&c,sizeof(char),1,fp);
            if(c&&1 == 1)
            {
                fputc('1',txt);
            }
            else
            {
                fputc('0',txt);
            }
        }
        k=1;
    }



    }

    if(k){
        printf("\n\n\n\n\n\t\t\t\t~~~~~~~ Successfully Written to sample_bin_uc6.txt ~~~~~~~~\n\n\n");
    }
    else{
        printf("\n\n\n\n\n\t\t\t\t~~~~~~~~ Error Couldn't Write the Extracted data ~~~~~~~\n\n\n");
    }
    fclose(fp);
    //fputc(EOF,txt);
    fclose(txt);




    

} 



int main(){
    opentifffile();
}
