/*
 * sentence.h
 *
 *  Created on: Apr 6, 2016
 *      Author: hoan
 */

#ifndef SENTENCE_H_
#define SENTENCE_H_

#include "../include/word.h"

typedef struct sentence_struct{
	char *name;	
	word *words;
	int num_words;

	struct sentence_struct * preSen;
	struct sentence_struct * nextSen;
} sentence;

sentence* get_sentence(char * a_str, int *num_sen);

#endif /* SENTENCE_H_ */