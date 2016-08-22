#include"../inc/bt.h"
#include<stdio.h>
#include<string.h>
void search (BTA* tree1)
{
  int size;
  char ta[100],tv[256];
  printf("English:");
  gets(ta);
  if(btsel(tree1,ta,tv,256*sizeof(char),&size)==0)
   printf("%s: %s\n",ta,tv);
  else 
    printf("can't search\n");
}
int main(){
  BTA * tree;
  tree = btopn("mytree1",0,FALSE);
  search(tree);
}
