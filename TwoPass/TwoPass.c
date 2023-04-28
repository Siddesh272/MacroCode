#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main() {
    FILE *ptr1,*ptr2,*ptr3;
    char opcode[20],label[20],operand[20],mnemonic[3],code[20],mcode[3],index1[2],adr[3],symbol[2],dubmcode[3];
    int lc,start;
    int index=0;
    ptr1=fopen("input.txt","r");
    ptr2=fopen("opcode.txt","r");
    ptr3=fopen("symtab.txt","w+");
    fscanf(ptr1,"%s\t%s\t%s",label,opcode,operand);
    fscanf(ptr2,"%s\t%s\t%s",code,mnemonic,mcode);
    printf("LC \t INTERMEDIATE CODE\tTARGETCODE\t\n\n"); 
    if(strcmp(opcode,"START")==0)
    {
        start=atoi(operand);
        lc=start;
        while(strcmp(code,"START")!=0)
        {
            fscanf(ptr2,"%s\t%s\t%s",code,mnemonic,mcode);
        }
        printf("\t(%s , %s)(C , %d)",mnemonic,mcode,lc);
        printf("\t\t-\n");
        fscanf(ptr1,"%s\t%s\t%s",label,opcode,operand); 
    }
    while(strcmp(opcode,"END")!=0)
    { 
        if(strcmp(opcode,"DS")==0)
        {
            while(strcmp(code,"DS")!=0)
            {
                fscanf(ptr2,"%s\t%s\t%s",code,mnemonic,mcode);
            }
            printf("\n%d\t(S , %d)(%s , %s)(C , %s)",lc,index,mnemonic,mcode,operand);
            fprintf(ptr3,"%d\t%s\t%d\n",index,label,lc);
            printf("\t\t-\n");
            index+=1;
            lc+=1;
            }
        if(strcmp(opcode,"READ")==0 || strcmp(opcode,"PRINT")==0)
        {
            rewind(ptr2);
            while(strcmp(code,opcode)!=0)
            {
                fscanf(ptr2,"%s\t%s\t%s",code,mnemonic,mcode);
            }
            printf("\n%d\t(%s , %s)",lc,mnemonic,mcode);
            rewind(ptr3);
            while(strcmp(symbol,operand)!=0)
            {
                fscanf(ptr3,"%s\t%s\t%s",index1,symbol,adr);
            }
            printf("(S , %s)",index1); 
            printf("\t\t%s 00 %s\n",mcode,adr);
            lc+=1;
        }
        if(strcmp(label,"MOVER")==0 || strcmp(label,"MOVEM")==0 || strcmp(label,"ADD")==0)
        {
            rewind(ptr2);
            while(strcmp(code,label)!=0)
            {
                fscanf(ptr2,"%s\t%s\t%s",code,mnemonic,mcode);
            }
            printf("\n%d\t(%s , %s)",lc,mnemonic,mcode);
            strcpy(dubmcode,mcode);
            rewind(ptr2);
            while(strcmp(code,opcode)!=0)
            {
                fscanf(ptr2,"%s\t%s\t%s",code,mnemonic,mcode);
            }
            printf("(%s , %s)",mnemonic,mcode);
            rewind(ptr3);
            while(strcmp(symbol,operand)!=0)
            {
                fscanf(ptr3,"%s\t%s\t%s",index1,symbol,adr);
            }
            printf("(S , %s)",index1);
            printf("%s %s %s\n",dubmcode,mcode,adr);
            lc+=1;
        } 
        fscanf(ptr1,"%s\t%s\t%s",label,opcode,operand);     
    }
    if(strcmp(opcode,"END")==0)
    {
        rewind(ptr2);
        while(strcmp(code,opcode)!=0)
        {
            fscanf(ptr2,"%s\t%s\t%s",code,mnemonic,mcode);
        }
        printf("\n%d\t(%s , %s)",lc,mnemonic,mcode);
        printf("\t\t\t-");
    }
    fclose(ptr1);
    fclose(ptr2);
    fclose(ptr3);
    return 0;
}

