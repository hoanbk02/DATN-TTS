/*
 * syllable.h
 *
 *  Created on: Apr 6, 2016
 *      Author: hoan
 */

#ifndef SYLLABLE_H_
#define SYLLABLE_H_

#include "../include/phoneme.h"

typedef struct syllable_struct{
	char * name;
	char** phonemes;
	char *vowel;
	
	int num_phone;
	char * tone;
	int stressed;
	
	struct syllable_struct * preSyl;
	struct syllable_struct * nextSyl;
}syllable;

syllable* get_syllable(char* a_str, int *num_phone);

#endif /* SYLLABLE_H_ */