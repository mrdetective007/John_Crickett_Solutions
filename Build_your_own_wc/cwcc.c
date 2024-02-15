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

char* return_file_name(int argc, char** argv){
    char* file_name=NULL;
    char* extension=".txt";
    for(int i=0;i<argc;i++){
        if(strstr(argv[i],extension)){
            file_name=argv[i];
            break;
        }
    }
    return file_name;
}

char* return_command_name(int argc, char** argv){
    char* command=NULL;
    char* identification="-";
    for(int i=0;i<argc;i++){
        if(strstr(argv[i],identification)){
            command=argv[i];
            break;
        }
    }
    return command;
}

int count_words_in_string(char *str){
    int length=strlen(str);
    int cnt=0;
    for(int i=0;i<=length;i++){
        if(str[i]==' '){
            cnt++;
        }
    }
    return cnt;
}

int main(int argc, char **argv){
    if(argc==2 || argc==3){
        char* file_name=return_file_name(argc,argv);
        char* command=return_command_name(argc,argv);
        FILE *ptr=fopen(file_name,"r");
        if(file_name!=NULL){
            if(command!=NULL){
                int value_c=strcmp(command,"-c");
                int value_l=strcmp(command,"-l");
                int value_w=strcmp(command,"-w");
                int value_m=strcmp(command,"-m");

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
                printf("%ld %d %d %d %s", number_of_bytes(ptr),number_of_lines(ptr),number_of_words(ptr),number_of_characters(ptr),file_name);
            }
        }else{
            char* command=return_command_name(argc,argv);
            char* str=NULL;
            size_t len=0;
            int number_of_bytes_from_stdin=0, number_of_lines_from_stdin=0, number_of_words_from_stdin=0, number_of_characters_from_stdin=0;
            while(getline(&str,&len,stdin)!=EOF){
                number_of_bytes_from_stdin+=strlen(str);
                number_of_lines_from_stdin++;
                number_of_words_from_stdin+=count_words_in_string(str);
                number_of_characters_from_stdin+=strlen(str);
            }
            int value_c=strcmp(command,"-c");
            int value_l=strcmp(command,"-l");
            int value_w=strcmp(command,"-w");
            int value_m=strcmp(command,"-m");

            if(value_c==0){
                printf("%d",number_of_bytes_from_stdin);
            }
            if(value_l==0){
                printf("%d",number_of_lines_from_stdin);
            }
            if(value_w==0){
                printf("%d",number_of_words_from_stdin);
            }
            if(value_m==0){
                printf("%d",number_of_characters_from_stdin);
            }
        }
    }
    return 0;
}