#include <stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX 1000
typedef struct{
int weight;
int lchild;
int rchild;
int parent;
char tag;
char c;
}htnode;
typedef struct{
	char c;
	char bits[MAX];
	int len;
}htcode;
void InitHT(int*w,char*c,int m,int len,htnode*ht)
{
      for(int i=0;i<m;i++)
      {
	      ht[i].parent=-1;
	      ht[i].tag=-1;
	      ht[i].lchild=-1;
	      ht[i].rchild=-1;
      }
      for(int i=0;i<len;i++)
      {
	      ht[i].weight=w[i];
	      ht[i].c=c[i];
      }

};
void SelectMin(htnode*ht,int n,int &p1,int &p2)
{
	int i,j;
	for(i=1;i<=n;i++)
		if(ht[i].parent==-1){p1=i;break;}
	for(j=i+1;j<=n;j++)
		if(ht[j].parent==-1){p2=j;break;}
	for(i=1;i<=n;i++)
		if((ht[p1].weight>ht[i].weight)&&(ht[i].parent==-1)&&(p2!=i)) p1=i;
	for(j=1;j<=n;j++)
		if((ht[p2].weight>ht[j].weight)&&(ht[j].parent==-1)&&(p1!=i)) p2=i;
};
void creatHT(int m,int len,char*c,int*w,htnode*ht)
{
	int i,p1,p2;
	InitHT(w,c, m, len,ht);
	for(i=len;i<=m;i++)
	{
		SelectMin(ht,i-1,p1,p2);
		ht[p1].parent=i;
		ht[p2].parent=i;
		ht[i].lchild=p1;
		ht[i].rchild=p2;
		ht[p1].tag='0';
		ht[p2].tag='1';
	}
};
int getCW(char*tmp,char*c,int* weight)
{
int len=0;
int i=0;
   // printf("%d\n",len);
for( i=0;i<strlen(tmp);i++)
{
int  ifnew=1;
int j=0;
for(j=0;j<len;j++)
{ 
if(tmp[i]==c[j])
{
ifnew=0;
weight[j]++;
break;
}
}
if(ifnew)
{
c[len]=tmp[i];
weight[len]=0;
len++;
}
}

return len;
};
int main()//main fanction,read the files,use other function
{
FILE*f;
f=fopen("test.txt","r");
fseek(f,0,SEEK_END);
int file_size=ftell(f);
//printf("%d",file_size);
char*tmp;
fseek(f,0,SEEK_SET);
tmp=(char*)malloc(file_size*sizeof(char));
fread(tmp,file_size,sizeof(char),f);
//printf("%s\n",tmp);
int*weight=(int*)malloc(file_size*sizeof(int));
char*c=(char*)malloc(file_size*sizeof(char));
int len=getCW(tmp,c,weight);//get char and weight
// printf("%d\n",len);
/* for(int i=0;i<len;i++)
 {
      printf("%c\n",c[i]);
 }*/
int m=2*file_size-1;
htnode*ht=(htnode*)malloc(m*sizeof(htnode));//begin to build the tree
creatHT(m,strlen(tmp),c,weight,ht);//creat the tree
printf("%d/n",ht[m-1].parent);
htcode*hc=(htcode*)malloc(m*sizeof(htcode));//get diy_acssi
return 0;
}
