#include <string.h>
#include <stdlib.h>

#include "../include/nlp.h"

#define MAXBUFLEN 1024

char ** get_labeldata(char *buff, int *num_line){

	while(buff[strlen(buff)-1] == 10 && buff[strlen(buff)-2] == 32){
		buff[strlen(buff)-2] = 10; buff[strlen(buff)-1] = '\0';
	} 

	char **label_data = NULL;
	int label_size = 0;

	int num_sen = 0;
	sentence *hSen = get_sentence(buff, &num_sen);

	word *hWord = hSen->words;
	syllable *hSyl = hWord->syllables;	

	int checkOutSen[num_sen]; int id = 0;
	sentence *nSen = hSen;
	while(nSen){
		label_size += nSen->num_words; checkOutSen[id++] = nSen->num_words;
		nSen = nSen->nextSen;
	}

	int checkOutWord[label_size];
	word *nWord = hWord; int idx1 = 0; int sumSyl = 0;
	while(nWord){
		checkOutWord[idx1] = nWord->num_syll; sumSyl += nWord->num_syll;
		idx1++;
		nWord = nWord->nextWord;
	}
	
	syllable *nSyl = hSyl; 
	int checkOutSyl[sumSyl]; idx1 = 0;
	while(nSyl){
		label_size += nSyl->num_phone; checkOutSyl[idx1] = nSyl->num_phone;
		nSyl = nSyl->nextSyl; idx1++;
	}
	
	nSyl = hSyl; 
	char **phs = (char **) calloc(label_size+4, sizeof(char*));
	int idx2 = 0; int flag = 0; int dem = 0;  

	phs[idx2] = (char *)malloc(6*sizeof(char)); phs[idx2] = "x"; idx2++;
	phs[idx2] = (char *)malloc(6*sizeof(char)); phs[idx2] = "x"; idx2++;
	while(nSyl){
		dem++;
		char **phonemes = nSyl->phonemes; int i = 0;
		while(*(phonemes+i)){
			phs[idx2] = strdup(*(phonemes+i));
			i++; idx2++;
		} 
		if(dem == checkOutWord[flag]){
			dem = 0;
			phs[idx2] = (char *)malloc(6*sizeof(char)); phs[idx2] = "pau"; 
			flag++; idx2++;
		}
		nSyl = nSyl->nextSyl; 
	}
	phs[idx2] = (char *)malloc(6*sizeof(char)); phs[idx2] = "x"; idx2++;
	phs[idx2] = (char *)malloc(6*sizeof(char)); phs[idx2] = "x"; idx2++;

	if(label_size!=0){
		nSen = hSen; nWord = hWord; nSyl = hSyl;
		label_data = (char **) calloc(label_size, sizeof(char*));
		int i=2, demSyl = 0, demWord = 0, demSen = 0, flagSyl = 0, flagWord = 0, flagSen = 0;

		while(i<label_size+2){

			label_data[i-2] = (char *) calloc(MAXBUFLEN, sizeof(char));
			char *p1 = (char *)malloc(6*sizeof(char));
			char *p2 = (char *)malloc(6*sizeof(char));
			char *p3 = (char *)malloc(6*sizeof(char));
			char *p4 = (char *)malloc(6*sizeof(char));
			char *p5 = (char *)malloc(6*sizeof(char));

			// if(i==0){
			// 	p1 = "x";
			// 	p2 = "x";
			// 	strcpy(p3, phs[i]);
			// 	strcpy(p4, phs[i+1]);
			// 	strcpy(p5, phs[i+2]);
			// } else if(i==1){
			// 	p1 = "x";
			// 	strcpy(p2, phs[i-1]);
			// 	strcpy(p3, phs[i]);
			// 	strcpy(p4, phs[i+1]);
			// 	strcpy(p5, phs[i+2]);
			// } else if(i == label_size-2){
			// 	strcpy(p1, phs[i-2]);
			// 	strcpy(p2, phs[i-1]);
			// 	strcpy(p3, phs[i]);
			// 	strcpy(p4, phs[i+1]);
			// 	p5 = "x";
			// } else if(i == label_size-1){
			// 	strcpy(p1, phs[i-2]);
			// 	strcpy(p2, phs[i-1]);
			// 	strcpy(p3, phs[i]);
			// 	p4 = "x";
			// 	p5 = "x";
			// } else{
				strcpy(p1, phs[i-2]);
				strcpy(p2, phs[i-1]);
				strcpy(p3, phs[i]);
				strcpy(p4, phs[i+1]);
				strcpy(p5, phs[i+2]);
			//}
			
			int k;
			int j1 = 0; for(k=0;k<checkOutSen[flagSen];k++){ j1 += checkOutWord[k]; }
			int j2 = j1;
			int j3 = nSen->num_words; 

			if(strcmp(p3, "pau") == 0){
				int a3, c3, g1, i1;
				char *a1;
				if(i==label_size+1){
					a1 = strdup(nSyl->tone);
					a3 = (nSyl == NULL) ? 0 : nSyl->num_phone;
					c3 = (nSyl->nextSyl == NULL) ? 0 : nSyl->nextSyl->num_phone;
					g1 = (nWord == NULL) ? 0 : nWord->num_syll; 
					i1 = (nWord->nextWord == NULL) ? 0 : nWord->nextWord->num_syll;			
				}else{
					a1 = strdup(nSyl->preSyl->tone);
					a3 = (nSyl->preSyl == NULL) ? 0 : nSyl->preSyl->num_phone;
					c3 = (nSyl == NULL) ? 0 : nSyl->num_phone;
					g1 = (nWord->preWord == NULL) ? 0 : nWord->preWord->num_syll; 
					i1 = (nWord == NULL) ? 0 : nWord->num_syll;		
				}		

				char buff_a3[5]; sprintf(buff_a3, "%d", a3); 
				char buff_c3[5]; sprintf(buff_c3, "%d", c3);
				char buff_g1[5]; sprintf(buff_g1, "%d", g1);
				char buff_i1[5]; sprintf(buff_i1, "%d", i1);
				

				sprintf(label_data[i-2],"%s^%s-%s+%s=%s@x_x/A:%s_%s/B:x-x@x-x&x-x|x/C:%s+%s/D:%s_%s/E:x+x@x+x&x+x#x+x/F:%s_%s/G:%s_%s/H:x=x^x=x/I:%s=%s/J:%d+%d-%d\n",     /* */
					            p1,  /* p1 */
					            p2,  /* p2 */
					            p3,  /* p3 */
					            p4,  /* p4 */
					            p5,  /* p5 */
					            a1,       /* a1 */				        
					            (a3 == 0) ? "x" : buff_a3,                               /* a3 */
					            (nSyl == NULL) ? "x" : nSyl->tone,					     /* c1 */
					            (c3 == 0) ? "x" : buff_c3,                               /* c3 */
					            (nSyl->preSyl == NULL) ? "0" : "content",                /* d1 */
					            (nSyl->preSyl == NULL) ? "0" : "1",                      /* d2 */
					            (nSyl == NULL) ? "0" : "content",               /* f1 */
					            (nSyl == NULL) ? "0" : "1",                     /* f2 */
					            (g1 == 0) ? "x" : buff_g1,     /* g1 */
					            (g1 == 0) ? "x" : buff_g1,     /* g2 */
					            (i1 == 0) ? "x" : buff_i1,     /* i1 */
					            (i1 == 0) ? "x" : buff_i1,     /* i2 */
					         	j1,               /* j1 */
					            j2,               /* j2 */
					            j3);              /* j3 */  	

			}else{ 	demSyl++; 

				int p6 = demSyl;
				int a3 = (nSyl->preSyl == NULL) ? 0 : nSyl->preSyl->num_phone; char buff_a3[5]; sprintf(buff_a3, "%d", a3);
				int b3 = checkOutSyl[flagSyl];
				int b6 = demWord + 1;
				int b7 = checkOutWord[flagWord] - demWord;
				char *b16 = strdup(nSyl->vowel);
				int c3 = (nSyl->nextSyl == NULL) ? 0 : nSyl->nextSyl->num_phone; char buff_c3[5]; sprintf(buff_c3, "%d", c3);
				int d2 = (nSyl->preSyl == NULL) ? 0 : 1;
				int e3 = b6;
				int e4 = b7;
				int e5 = demWord;
				int e6 = checkOutWord[flagWord] - demWord;
				int e7 = (nSyl->preSyl == NULL) ? 0 : 1;
				int e8 = (nSyl->nextSyl == NULL) ? 0 : 1;
				int f2 = (nSyl->nextSyl == NULL) ? 0 : 1;
				int g1 = (nWord->preWord == NULL) ? 0 : nWord->preWord->num_syll; 
				int h1 = nWord->num_syll;
				int h3 = demSen+1;
				int h4 = checkOutSen[flagSen] - demSen;
				int i1 = (nWord->nextWord == NULL) ? 0 : nWord->nextWord->num_syll; char buff_i1[5]; sprintf(buff_i1, "%d", i1);

				sprintf(label_data[i-2],"%s^%s-%s+%s=%s@%d_%d/A:%s_%s/B:%s-%d@1-1&%d-%d|%s/C:%s+%s/D:%s_%d/E:content+1@%d+%d&%d+%d#%s+%s/F:%s_%s/G:%d_%d/H:%d=%d^%d=%d/I:%s=%s/J:%d+%d-%d\n",
								p1,					/* p1 */
								p2,					/* p2 */
								p3,               	/* p3 */
								p4,    				/* p4 */
								p5,  				/* p5 */
								p6,               	/* p6 */
								b3 - p6 + 1,      	/* p7 */
								(nSyl->preSyl == NULL) ? "x" : nSyl->preSyl->tone,       /* a1 */
								a3 == 0 ? "x" : buff_a3, 							     /* a3 */
								nSyl->tone,       /* b1 */
								b3,               /* b3 */
								b6,        		  /* b6 */
								b7,               /* b7 */
								b16,			  /* b16 */
								(nSyl->nextSyl == NULL) ? "x" : nSyl->nextSyl->tone,       /* c1 */
								c3 == 0 ? "x" : buff_c3,     							   /* c3 */
								d2 == 0 ? "x" : "content",      /* d1 */
								d2,     						/* d2 */
								e3,               				/* e3 */
								e4,      		  				/* e4 */
								e5,       						/* e5 */
								e6,       						/* e6 */	
								e7 == 0 ? "x" : "1",			/* e7 */
								e8 == 0 ? "x" : "1",			/* e8 */
								f2 == 0 ? "x" : "content",      /* f1 */
								f2 == 0 ? "x" : "1",		    /* f2 */
								g1,     			/* g1 */
								g1,     			/* g2 */
								h1,      			/* h1 */
								h1,               	/* h2 */
								h3,               	/* h3 */
								h4,			      	/* h4 */
								i1 == 0 ? "x" : buff_i1,     /* i1 */
								i1 == 0 ? "x" : buff_i1,     /* i2 */
								j1,               /* j1 */
								j2,               /* j2 */
								j3);              /* j3 */


				if(i<label_size){ 
					if(demSyl == checkOutSyl[flagSyl]){ 
						demSyl = 0; flagSyl++; demWord++; 

						if(demWord == checkOutWord[flagWord]){
							demWord = 0; flagWord++; demSen++; 

							if(demSen == checkOutSen[flagSen]){ 
								demSen = 0; flagSen++;
								nSen = nSen->nextSen;
							}
							nWord = nWord->nextWord;
						}
						nSyl = nSyl->nextSyl; 
					}
				}
			}
			i++; 
		}	
	}
	*num_line=label_size;
	return label_data;
}

