#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){
	int i,j,k;
	int total;
	char s[1000],t[1000],u[1000];
	char *new;
	char *space;
	FILE *model1,*model2,*output1,*output2,*output3,*test;
	float told;//thresh old
	int acc;	//正しく判断された数
	int pseikai;	//閾値より高く、正解。
	int p;		//閾値より高い。
	int seikai;	//本当の正解の数。つまり＋の数
	float accuracy,precision,recall;
	float sum;

	//最初に全てファイルオープン
	if((model1 = fopen("model1.txt","r")) == NULL){
		printf("file can't open\n");
		exit(EXIT_FAILURE);
	}
	if((model2 = fopen("model2.txt","r")) == NULL){
		printf("file can't open\n");
		exit(EXIT_FAILURE);
	}
	if((output1 = fopen("output1.txt","r")) == NULL){
		printf("file can't open\n");
		exit(EXIT_FAILURE);
	}
	if((output2 = fopen("output2.txt","r")) == NULL){
		printf("file can't open\n");
		exit(EXIT_FAILURE);
	}
	if((output3 = fopen("output3.txt","w")) == NULL){
		printf("file can't open\n");
		exit(EXIT_FAILURE);
	}
	if((test = fopen("test1.txt","r")) == NULL){
		printf("file can't open\n");
		exit(EXIT_FAILURE);
	}
	//配列の数を取得
	for(i=0;i!=9;i++){
		fgets(s,256,model1);
		fgets(t,256,model2);
	}
	space = strchr(s,' ');	
	*space = '\0';
	space = strchr(t,' ');	
	*space = '\0';
	total = atoi(s);

	//閾値を取得
	for(i=0;i!=2;i++){
		fgets(s,256,model1);
		fgets(t,256,model2);
	}
	space = strchr(s,' ');	
	*space = '\0';
	space = strchr(t,' ');	
	*space = '\0';
	told = atof(s)+atof(t);

	fclose(model1);
	fclose(model2);

	//2つの値を足す。
	for(i=0;i<total;i++){
		fgets(s,256,output1);
		fgets(t,256,output2);
		fgets(u,256,test);
		sum = atof(s)+atof(t);
		if(sum>told){
			p++;
			if(u[0]=='+'){
				pseikai++;
				seikai++;
				acc++;
			}
		}else{
			if(u[0]=='-'){
				acc++;	
			}else{
				seikai++;
			}
		}
	}
	accuracy = (float)acc/total;
	precision = (float)pseikai/p;
	recall = (float)pseikai/seikai;
	printf("acc=%d\npseikai=%d\nseikai=%d\np=%d\n",acc,pseikai,seikai,p);
	printf("accuracy=%f\nprecision=%f\nrecall=%f\n",accuracy,precision,recall);

	
	fclose(output1);
	fclose(output2);
	fclose(output3);
	fclose(test);
	return 0;
}
