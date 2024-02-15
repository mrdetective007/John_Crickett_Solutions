#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


long number_of_bytes(FILE *ptr){
    fseek(ptr, 0, SEEK_END);
    long n=ftell(ptr);
    fseek(ptr,0,SEEK_SET);
    return n;
}

int number_of_lines(FILE *ptr){
    int cnt=0;
    char curr;
    for(curr=getc(ptr);curr!=EOF;curr=getc(ptr)){
        if(curr=='\n'){
            cnt=cnt+1;
        }
    }
    fseek(ptr,0,SEEK_SET);
    return cnt;
}

int number_of_words(FILE *ptr){
    int cnt=0;
    char curr;
    for(curr=getc(ptr);curr!=EOF;curr=getc(ptr)){
        if(curr==' '){
            cnt=cnt+1;
        }
    }
    fseek(ptr,0,SEEK_SET);
    return cnt;
}

int number_of_characters(FILE *ptr){
    int n=0;
    char ch;
    do{
        ch=fgetc(ptr);
        n++;
    }while(ch!=EOF);
    fseek(ptr,0,SEEK_SET);
    return n;
}

int main(void){
    char *cmd=NULL;
    size_t n=0;
    int nos=getline(&cmd,&n,stdin);
    FILE *ptr;
    char file_name[100];
    char first_command[4];
    char second_command[2];
    strncpy(first_command,cmd,4);
    first_command[4]='\0';
    int val=strcmp(first_command,"cwcc");
    if(val==0){
        strncpy(second_command,cmd+5,2);
        second_command[2]='\0';

        int value_c=strcmp(second_command,"-c");
        int value_l=strcmp(second_command,"-l");
        int value_w=strcmp(second_command,"-w");
        int value_m=strcmp(second_command,"-m");

        if(value_c==0 || value_l==0 || value_w==0 || value_m==0){
            strncpy(file_name,cmd+8,strlen(cmd)-9);
            file_name[strlen(cmd)-9]='\0';
            ptr=fopen(file_name,"r");        
            if(value_c==0){
                long nos_bytes=number_of_bytes(ptr);
                printf("%ld %s",nos_bytes,file_name);
            }
            if(value_l==0){
                int nos_lines=number_of_lines(ptr);
                printf("%d %s",nos_lines,file_name);
            }
            if(value_w==0){
                int nos_words=number_of_words(ptr);
                printf("%d %s",nos_words,file_name);
            }
            if(value_m==0){
                int nos_chars=number_of_characters(ptr);
                printf("%d %s",nos_chars,file_name);
            }
        }else{
            strncpy(file_name,cmd+5,strlen(cmd)-6);
            file_name[strlen(cmd)-6]='\0';
            ptr=fopen(file_name,"r");
            printf("%ld %d %d %d %s", number_of_bytes(ptr), number_of_lines(ptr), number_of_words(ptr), number_of_characters(ptr), file_name);
        }
    }else{
        strncpy(file_name,cmd+4,strlen(cmd)-15);
        file_name[strlen(cmd)-15]='\0';
        ptr=fopen(file_name,"r");

        strncpy(second_command,cmd+20,2);
        second_command[2]='\0';

        int value_c=strcmp(second_command,"-c");
        int value_l=strcmp(second_command,"-l");
        int value_w=strcmp(second_command,"-w");
        int value_m=strcmp(second_command,"-m");

        if(value_c==0){
            long nos_bytes=number_of_bytes(ptr);
            printf("%ld %s",nos_bytes,file_name);
        }
        if(value_l==0){
            int nos_lines=number_of_lines(ptr);
            printf("%d %s",nos_lines,file_name);
        }
        if(value_w==0){
            int nos_words=number_of_words(ptr);
            printf("%d %s",nos_words,file_name);
        }
        if(value_m==0){
            int nos_chars=number_of_characters(ptr);
            printf("%d %s",nos_chars,file_name);
        }
    }
    return 0;
}