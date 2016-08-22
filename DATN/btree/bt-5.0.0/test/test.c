#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../inc/bt.h"
//bo dau cach o dau
char* trim (char*a){
  int i=0;
  char *s;
  while(a[i]==' '){
    i++;
  }
  s=a+i;
  return s;
}
int main()
{
  btinit();
  BTA *tree1;
  
  int i,j,n,l;
  FILE *f1,*f2,*f3,*f4;
  char ta[100],tv[256],s[256],*str1,*str2,str[256],*a;
  f1 = fopen("file1.txt","rt");
  f2 = fopen("file2.txt","rt");
  f3 = fopen("file3.txt","rt");
  f4=fopen("file4.txt","wt");
  tree1 = btcrt("mytree1",0,0);
  while(fscanf(f1,"    %s\n",ta)>0)
{
  str1 = (char*)malloc(50);
  str2 = (char*)malloc(50);
  if( fgets(tv,256,f2) != NULL){
    tv[strlen(tv)-1] = '\0';
    a=trim(tv); 
  }
  if(fgets(s,256,f3)!=NULL)
    {
      n= strlen(s);
      for(i=0; i<n;i++)
	if(s[i]!=ta[i])
	    break;
      for(j=(i+1);j<n;j++)
	if(s[j]=='/')
	    break;
 
      str2=(s+j);
      l=strlen(str2);
      str2[l-1]='\n';
    //printf("%s\n",str2);
      strcpy(str,str2);
       str1=(s+i);
      l=strlen(str1);
      for(i=0;i<l;i++)
	if(str1[i]=='/')
	  {
	    str1[i-1]='\n';
	    str1[i]='\0';
	   // printf("%s\n",str2);
	  }
	  str1=trim(str1);
      strcat(str,str1);
      strcat(str,a);
    printf("%s\n",str);
    fprintf(f4,"%s\n",str);
    }
    btins(tree1,ta,str,356);
}
fclose(f1);
fclose(f2);
fclose(f3);
fclose(f4);
btcls(tree1);
 }
