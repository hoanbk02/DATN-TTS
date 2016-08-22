/*
 * word.h
 *
 *  Created on: Apr 6, 2016
 *      Author: hoan
 */

#ifndef WORD_H_
#define WORD_H_

#include "../include/syllable.h"

typedef struct word_struct{
	char * name;
	syllable *syllables;
	int num_syll;

	struct word_struct * preWord;
	struct word_struct * nextWord;
}word;

word* get_word(char * a_str, int *num_word);

#endif /* WORD_H_ */