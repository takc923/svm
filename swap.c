#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*
 値を返すswap
 */
char* swap(char* s,int a, int alen, int b, int blen);

int main(){
	int i,j,k;
	char s[] = "abcdefghijklmn";
	char *new;
	int a=3,alen=3,b=8,blen=4; //a:始点 alen:前半の長さ b:後半の始点 blen:後半の長さ
	printf("before\ns=%s\n",s);
	new = swap(s,a,alen,b,blen);
	printf("after\nnew=%s\n",new);
	return 0;
}

/**
 * スワップする
 * sRNA
 * a:前半の始点 alen:前半の長さ b:後半の始点 blen:後半の長さ
 **/
char* swap(char* s,int a, int alen, int b, int blen){
	//bは始まる方。
	int i;
	int n=strlen(s);
	
	//入れ替える部分を取っておく
	char *new = (char*)malloc(sizeof(char)*n);
	
	for(i=0;i<a;i++)		new[i]				= s[i];
	for(i=0;i<blen;i++)		new[a+i]			= s[b+i];
	for(i=0;i<b-a-alen;i++)	new[a+blen+i]		= s[a+alen+i];
	for(i=0;i<alen;i++)		new[b+blen-alen+i]	= s[a+i];
	for(i=0;i<n;i++)		new[b+blen+i]		= s[b+blen+i];
	
	return new;
}

