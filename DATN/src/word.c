#include <stddef.h>
#include <string.h>
#include "../include/word.h"

static const char * const punctuationW = "\"'`,:;(){}[]";

word *headWord, *tailWord;

void append_nodeWord(word* word);
void remove_nodeWord(word* node);

word* get_word(char * a_str, int *num_word){	

	char **words = get_token(a_str, punctuationW);
	if(words){
		int idx = 0;		
		char *wd = *(words+idx++); int x = 0;
		while(wd){
            if (strcmp(wd," ")==0) { 
                wd = *(words+idx++); x++;
                continue;
            }

			word * w = (word *) malloc(sizeof(word));
			w->name = strdup(wd); 

			int num_syl = 0;
			syllable * sylls = get_syllable(wd, &num_syl);
			w->syllables = sylls;
			w->num_syll = num_syl;

			append_nodeWord(w);
			wd = *(words+idx++);
		}
		*num_word = idx - 1 - x;
	}	

	return headWord;
}

void append_nodeWord(word* word){
    if(headWord == NULL){
        headWord=word;
        word->preWord=NULL;
    }else{
        tailWord->nextWord=word;
        word->preWord=tailWord;
    }
    tailWord=word;
    word->nextWord=NULL;
}

void remove_nodeWord(word *node){
    if(node->preWord == NULL){
        headWord = node->nextWord;
    }else{
        node->preWord->nextWord = node->nextWord;
    }
    if (node->nextWord == NULL){
        tailWord = node->preWord;
    }else{
        node->nextWord->preWord = node->preWord;
    }
}