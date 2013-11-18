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
	for(int i=0;i<n;i++)
	{
		if(ht[i].parent==-1)
		{
			p1=i;
			break;
		}
	}
	for(int j=0;j<n;j++)
	{
		if((ht[j].weight<ht[p1].weight)&&(ht[j].parent==-1)) p1=j;
        }
	ht[p1].parent=n;
	ht[n].lchild=p1;
	ht[p1].tag='0';
	for(int i=0;i<n;i++)
	{
                if(ht[i].parent==-1)
		{
			p2=i;
			break;
		}
	}
	for(int j=0;j<n;j++)
	{
		if((ht[j].weight<ht[p2].weight)&&(ht[j].parent==-1)) p2=j;
	}
	ht[p2].parent=n;
	ht[p2].tag='1';
	ht[n].rchild=p2;
	ht[n].weight=ht[p1].weight+ht[p2].weight;
};
void creatHT(int m,int len,char*c,int*w,htnode*ht)
{
	int i,p1,p2;
	InitHT(w,c, m, len,ht);
	for(i=len;i<m;i++)
	{
		SelectMin(ht,i,p1,p2);
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
weight[len]=1;
len++;
}
}

return len;
};
void gethtcode(int n,htcode*hc,htnode*ht)
{
   for(int i=0;i<n;i++)
   {
	   htnode tmp;
	   tmp=ht[i];
	   hc[i].len=0;
	   hc[i].c=tmp.c;
	   while(tmp.parent!=-1)
	   {
		   int len=hc[i].len;
		   hc[i].bits[len]=tmp.tag;
		   hc[i].len++;
		   tmp=ht[tmp.parent];
           }
	 //  printf("%s\n",hc[i].bits);
	 //  printf("%d\n",hc[i].len);
	   char tmpc;
	   int len=hc[i].len;
	   for(int j=0;j<len/2;j++)
	   {
		   tmpc=hc[i].bits[j];
		   hc[i].bits[j]=hc[i].bits[len-j-1];
		   hc[i].bits[len-j-1]=tmpc;
	   }
	 //  printf("%s\n",hc[i].bits);
   }
  
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
  /*  for(int i=0;i<len;i++)
 {
      printf("%c\n",c[i]);
 }*/
  int m=2*len-1;
  htnode*ht=(htnode*)malloc(m*sizeof(htnode));//begin to build the tree
  creatHT(m,len,c,weight,ht);//creat the tree
 // printf("%d\n",ht[0].c);
  htcode*hc=(htcode*)malloc(len*sizeof(htcode));//get diy_acssi
  gethtcode(len,hc,ht);//getthecode
  for(int i=0;i<len;i++)
  {
	  printf("%d,%s\n",hc[i].c,hc[i].bits);
  }
  //change the char tmp
  int maxlen=hc[0].len;
  for(i=0;i<len;i++)
  {
	  if(hc[i].len>maxlen)
		  maxlen=hc[i].len;

  }
return 0;
}
