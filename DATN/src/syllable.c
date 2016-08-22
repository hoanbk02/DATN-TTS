#include "../include/split.h"
#include "../include/syllable.h"
#include "../btree/tree.h"

#define P "pau"

syllable *headSyl, *tailSyl;

static const char * const punctuationSl = "- \t\n\r";
static const char *vowels[128] = {"vi12","vi143","vi146","vi147","vi114","vi115","vi144","vi145","vi161","vi190","vi191","vi192","vi188","vi189","vi193","vi194","vi110","vi157","vi187","vi160","vi158","vi159","vi185","vi186","vi113","vi126","vi127","vi128","vi124","vi125","vi129","vi130","vi116","vi139","vi140","vi141","vi138","vi183","vi142","vi184","vi112","vi119","vi120","vi121","vi118","vi117","vi123","vi122","vi154","vi178","vi179","vi180","vi176","vi177","vi181","vi182","vi11","vi79","vi105","vi106","vi80","vi81","vi103","vi104","vi6","vi61","vi98","vi76","vi70","vi68","vi92","vi90","vi0","vi59","vi96","vi74","vi65","vi67","vi87","vi89","vi9","vi63","vi100","vi78","vi72","vi101","vi94","vi102","vi54","vi82","vi109","vi85","vi84","vi83","vi108","vi107","vi56","vi148","vi174","vi155","vi152","vi150","vi172","vi170","vi13","vi25","vi31","vi37","vi17","vi14","vi46","vi43","vi162","vi165","vi166","vi167","vi164","vi163","vi169","vi168","vi111","vi133","vi134","vi135","vi132","vi131","vi137","vi136"};

void append_nodeSyl(syllable* syl);
void remove_nodeSyl(syllable* node);

syllable* get_syllable(char* a_str, int *num_phones)
{
    char** tokens = get_token(a_str,punctuationSl);
    size_t idx = 0;

    if (tokens)
    {
        BTA* tree = btopn("../btree/tree_xsampa_tone_in_side_tricky",0,0);

        char* token = *(tokens+idx++);
        while (token)
        {
            char* output;
            search(tree,token,&output);
            if(output!=NULL){
                syllable * syl = (syllable *) malloc(sizeof(syllable));
                syl->name = token;

                char** phonemes = get_token(output,"-");                   
                size_t count = 0;
             
                while(*(phonemes+count)){
                    int i;
                    for(i=0;i<128;i++){
                        if(strcmp(*(phonemes+count),*(vowels+i)) == 0){
                            syl->vowel = strdup(*(phonemes+count));
                            break;
                        }
                    }
                    count++;
                }

                count--;
                char * tone = *(phonemes+count);
                *(phonemes+count) = '\0';

                syl->tone = tone;
                syl->phonemes = phonemes;
                syl->num_phone = count;

                append_nodeSyl(syl);
            }   
            token = *(tokens+idx++);      
        }        
        *num_phones = idx-1; 
        btcls(tree);
    }
    return headSyl;
}

void append_nodeSyl(syllable* syl){
    if(headSyl == NULL){
        headSyl=syl;
        syl->preSyl=NULL;
    }else{
        tailSyl->nextSyl=syl;
        syl->preSyl=tailSyl;
    }
    tailSyl=syl;
    syl->nextSyl=NULL;
}

void remove_nodeSyl(syllable *node){
    if(node->preSyl == NULL){
        headSyl = node->nextSyl;
    }else{
        node->preSyl->nextSyl = node->nextSyl;
    }
    if (node->nextSyl == NULL){
        tailSyl = node->preSyl;
    }else{
        node->nextSyl->preSyl = node->preSyl;
    }
}