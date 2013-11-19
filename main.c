#include <stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX 1000
int endtag;
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
	   if(tmp.c)
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
char char_to_bits(char*buff)//将长度为8到字符串变为二进制位
{
	int i;
	char bits=0;
//	printf("buff=%s\n",buff);
	int sum=(buff[1]-48)*64+(buff[2]-48)*32+(buff[3]-48)*16+(buff[4]-48)*8+(buff[5]-48)*4+(buff[6]-48)*2+buff[7]-48;
        if(buff[0]-48)
	{
		bits=-sum;
	}
	else bits=sum;



//	printf("bits=%d\n",bits);
	return bits;

};

 void ChangeToHccode(char*tmp,char*tmp2,htcode*hc,int len)
{

	char buff[8];
	int bufflen=0;
      for(int i=0;i<strlen(tmp);i++)
      {
	      for(int j=0;j<len;j++)
	      {
		      if(tmp[i]==hc[j].c)     
		      { 
			      for(int l=0;l<hc[j].len;l++)
		                  {
                                      if(bufflen==8)
				      {
					      tmp2[strlen(tmp2)]=char_to_bits(buff);
					      memset(buff,0,sizeof(buff));
					      bufflen=0;
		
				      }
				      buff[bufflen]=hc[j].bits[l];
				      bufflen++;
				      
				  }
		      }
              }
      }
      for(int i=0;i<len;i++)//添加结束标志，此处有问题
  {
	  if(hc[i].c==27)
	  {
		  for(int l=0;l<hc[i].len;l++)
		  {
			   if(bufflen==8)
				      {
					      tmp2[strlen(tmp2)]=char_to_bits(buff);
					      memset(buff,0,sizeof(buff));
					      bufflen=0;
	
				      }
				      buff[bufflen]=hc[i].bits[l];
				      bufflen++;
				      

		  }
		  endtag=i;
          }
 }

     if(bufflen<8)
     {
	     for(int i=bufflen;i<8;i++)
	     {
		     buff[i]='0';
	     }
	     tmp2[strlen(tmp2)]=char_to_bits(buff);
     } 
};
  void Translate(char*tmp2,char*tmp3,htcode*hc,int len)
{
	int maxlen;
   for(int i=0;i<len;i++)
  {
	  if(hc[i].len>maxlen)
		  maxlen=hc[i].len;

  }
   int tmp3len=0;
   char*tmpbits=(char*)malloc(maxlen*sizeof(char));
	   int tblen=0;
   for(int i=0;i<strlen(tmp2);i++)
   {
	   int tag=0;
	   tmpbits[tblen]=tmp2[i];
	   for(int j=0;j<len;j++)
	   {
		   if(strcmp(tmpbits,hc[endtag].bits)==0)
                         {
				 i=strlen(tmp2);
				 break;
			 }

		   if(strcmp(hc[j].bits,tmpbits)==0)
		   {
                       tmp3[tmp3len]=hc[j].c;
		       tmp3len++;
		       tag=1;
		       break;
                   }
	   }
	   if(tag)
	   {
		   memset(tmpbits,0.,sizeof(tmpbits));
		   tblen=0;
	   }
	   else
	   {
		   tblen++;
	   }

   }
                   
};
void bits_to_char(char*tmp,char a)
{
       //	printf("%c\n",a);
	for(int i=0;i<8;i++)
	{
		tmp[i]='0';
	}
	int len=0;
	int value=(int)a;
      // printf("%d\n",a);
	for(int i=a;a!=0;a=a/2)
	{
		if(a%2==1)
		{
		    tmp[7-len]='1';
		    len++;
		}
		else
		{
			tmp[7-len]='0';
			len++;
		}
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
 // printf("tmp=%s\n",tmp);
  int*weight=(int*)malloc(file_size*sizeof(int));
  char*c=(char*)malloc(file_size*sizeof(char));
  int len=getCW(tmp,c,weight);//get char and weight
  c[len]=27;
  weight[len]=1;
  len++;//留出一位作结束位
  // printf("%d\n",len);
  /*  for(int i=0;i<len;i++)
 {
      printf("%c\n",c[i]);
 }*/
  int m=2*len-1;
  htnode*ht=(htnode*)malloc(m*sizeof(htnode));//begin to build the tree
  creatHT(m,len,c,weight,ht);//creat the tree
 // printf("%d\n",ht[0].c);
  htcode*hc=(htcode*)malloc((len+1)*sizeof(htcode));//get diy_acssi
  gethtcode(len,hc,ht);//getthecode
  for(int i=0;i<len;i++)
  {
	  printf("%d,%s\n",hc[i].c,hc[i].bits);
  }
  int maxlen=hc[0].len;
  for(int i=0;i<len;i++)
  {
	  if(hc[i].len>maxlen)
		  maxlen=hc[i].len;
          
  }
  char*tmp2=(char*)malloc(maxlen*file_size*sizeof(char));
  ChangeToHccode(tmp,tmp2,hc,len);//转化为ascii编码并且储存,可能有问题
/* for(int i=0;i<strlen(tmp2);i++)
  {
	  printf("%d\n",tmp2[i]);
  } */
  FILE*f1;
  if((f1=fopen("test2.txt","a+"))==NULL)
  {
	  printf("error!");
	  exit(0);
  }
  fputs(tmp2,f1);
  fputs("\n",f1);
  fclose(f1);
  char* tmp3=(char*)malloc(8*maxlen*strlen(tmp2)*sizeof(char));
  memset(tmp3,0,sizeof(tmp3));
  int len3=0;
  for(int i=0;i<strlen(tmp2);i++)
  {
	char tmpbits[8];
	memset(tmpbits,0,sizeof(tmpbits));
       bits_to_char(tmpbits,tmp2[i]);
	  strcat(tmp3,tmpbits);
  }
// printf("%s\n",tmp3);
 char*tmp4=(char*)malloc(maxlen*file_size*sizeof(char));
 Translate(tmp3,tmp4,hc,len);
  printf("%s\n",tmp4);
  return 0;

}
