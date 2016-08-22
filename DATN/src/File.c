#include "../include/File.h"

void toLower(wchar_t* string){
    int i=0;
    wchar_t c;
    while (string[i])
    {
      c = string[i];
      string[i]=towlower(c);
      i++;
    }
}

void copyData(char *pathFile){
	setlocale(LC_CTYPE,"");
    FILE * pFile1, *pFile2;
   	wchar_t mystring [1024];

   	pFile1 = fopen (pathFile , "r"); 
   	pFile2 = fopen ("log26101992.txt","a");

   	if (pFile1 != NULL)
   	{
     	if(fgetws (mystring , 1024 , pFile1) != NULL){
	     	toLower(mystring);
	       	fputws (mystring, pFile2);
	    }
     	fclose (pFile1); fclose (pFile2);
   	}
}