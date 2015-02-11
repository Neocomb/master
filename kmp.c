/*************************************************************************
	> File Name: kmp.c
	> Author: 
	> Mail: 
	> Created Time: Mon 02 Feb 2015 07:17:11 AM PST
 ************************************************************************/

#include<stdio.h>
#include<errno.h>
#include<stdlib.h>

#define LOGD(str, ...) fprintf(stdout,str,##__VA_ARGS__)
#define LOGE(str) perror(str)

int getkey( char* src , int a[] );
int kmp_match( char* match , char* src );

int main( int argc , char** argv )
{
    char* filename = NULL;
    char* str = NULL ;
    char* match = NULL;
    int i = 1 , ret = 0;

    if( argc == 1 )
    {
        LOGD("Usage :\n");
        LOGD("-f : find the match str in file \n");
        LOGD("-s : find the match str in string\n");
        LOGD("-m : the string you wanna match with\n");
    }

    while( i+1 < argc )
    {
        if( !strcmp( "-f" , argv[i] ) )
        {
            filename = argv[++i];
            i++;
            LOGD("filename : %s!\n",filename);
        }
        else if( !strcmp( "-s" , argv[i] )){
            str = argv[++i];
            i++;
            LOGD("string  : %s!\n", str);
        }
        else if( !strcmp( "-m" , argv[i] )){
            match = argv[++i];
            i++;
            LOGD("match   : %s!\n", match );
        }else
            i++;
    }

    if( str != NULL && match != NULL){
        LOGD("start match : \n");
        ret =  kmp_match( match , str );
        if( ret >= 0 )
            LOGD("find match from %d : %s -> %c\n" , ret , str , str[ret] );
    }
    return 0;
}

int kmp_match( char* match , char* src ){
  
    int j = 0 , i = 0;
    int slen = strlen(src);
    int mlen = strlen(match);
    int* key = (int*)calloc( 1 , strlen(match) );
    getkey( match , key );

    while( i < slen && j < mlen ){
        if( j == -1 || match[j] == src[i] ){
            i++;
            j++;
        }else
            j = key[j];
    }
    free(key);
    
    if( j == mlen ) return i-j;
    return -1;
}

int getkey( char* src , int a[] ){
    int i = 0, j = -1;
    int size = strlen(src)-1;

    a[0] = -1;

    LOGD("str(%s) keyArray is : \n",src);
    LOGD("a[%d] = %d  ",0,a[0]);
    while( i < size  && j < size ){
        if( j == -1 || src[i] == src[j] ){
            j++;
            i++;
            a[i] = j;
            LOGD("a[%d] = %d  ",i,j);
        }else
            j = a[j];
    }
    LOGD("\n");
}
