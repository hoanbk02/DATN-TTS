#include <stddef.h>
#include <string.h>

#include "../include/sentence.h"
#include "../include/split.h"

static const char * const punctuationS = ".!?\n\r";

sentence *headSen, *tailSen;

void append_nodeSen(sentence *sen);
void remove_nodeSen(sentence *node);

sentence* get_sentence(char * a_str, int *num_sen){
	
	char **sens = get_token(a_str, punctuationS);

	if(sens){
		size_t count = 0;
		char *sen = *(sens+count++); int x = 0;
		while(sen){
			if (strcmp(sen," ")==0) { 
                sen = *(sens+count++);  x++;
                continue;
            }
			int num_word = 0; 
			sentence * senten = (sentence *) malloc(sizeof(sentence));
			senten->name = strdup(sen);

			word * words = get_word(sen, &num_word); 
			senten->words = words;
			senten->num_words = num_word;	
					
			append_nodeSen(senten);
			sen = *(sens+count++); 
		}
		*num_sen = count-1-x;
	}

	return headSen;	
}

void append_nodeSen(sentence* sen){
    if(headSen == NULL){
        headSen=sen;
        sen->preSen=NULL;
    }else{
        tailSen->nextSen=sen;
        sen->preSen=tailSen;
    }
    tailSen=sen;
    sen->nextSen=NULL;
}

void remove_nodeSen(sentence *node){
    if(node->preSen == NULL){
        headSen = node->nextSen;
    }else{
        node->preSen->nextSen = node->nextSen;
    }
    if (node->nextSen == NULL){
        tailSen = node->preSen;
    }else{
        node->nextSen->preSen = node->preSen;
    }
}
