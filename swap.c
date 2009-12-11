#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*
 値を返すswap
 */
void* swap(char* s,int a, int alen, int b, int blen);

int main(){
	int i,j,k;
	char s[1000];
	char *new;
	int a=3,alen=3,b=8,blen=4; //a:始点 alen:前半の長さ b:後半の始点 blen:後半の長さ
	FILE *fp;
	if((fp = fopen("original.txt","r")) == NULL){
		printf("file can't open\n");
		exit(EXIT_FAILURE);
	}
	while(fgets(s,256,fp) != NULL) swap(s,a,alen,b,blen);

	return 0;
}

/**
 * スワップする
 * sRNA
 * a:前半の始点 alen:前半の長さ b:後半の始点 blen:後半の長さ
 **/
void* swap(char* s,int a, int alen, int b, int blen){
	//bは始まる方。
	int i;
	int n=strlen(s);
	FILE *fp;
	//毎回ファイルオープンするのは健全じゃないよな。
	if((fp = fopen("train.txt","a")) == NULL){
		printf("file can't open\n");
		exit(EXIT_FAILURE);
	}
	//入れ替える部分を取っておく
	char mae[a+blen];
	char usiro[n-b-blen+alen];
	//スワップした前半をmaeにコピー
	for(i=0;i<a;i++)		mae[i]	= s[4+i];
	for(i=0;i<blen;i++)		mae[a+i]= s[4+b+i];
	mae[a+i] = '\0';
	fprintf(fp,"%c1 #%s\n",s[0],mae);
	//for(i=0;i<b-a-alen;i++)	new[a+blen+i]		= s[a+alen+i];
	//後半をusiroにコピー
	for(i=0;i<alen;i++)		usiro[i]		= s[4+a+i];
	for(i=0;i<n;i++)		usiro[alen+i]	= s[4+b+blen+i];
	usiro[alen+i] = '\0';
	fprintf(fp,"%c1 #%s",s[0],usiro);
	
	return;
}

