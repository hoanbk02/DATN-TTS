#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <dirent.h>
#include <time.h>

#include "../hts_engine_API-1.10/HTS_engine.h"

#include "../include/nlp.h"
#include "../include/File.h"

#define TEXT_INPUT "/home/hoan/Desktop/TT-TQDT/text/"
#define LAB_OUTPUT "/home/hoan/Desktop/TT-TQDT/gen/"

#define INPUT_BUFF_SIZE 1024

static void usage(void)
{
   fprintf(stderr, "The Vietnamese TTS System \"VTEDlite+hts_engine\"\n");
   fprintf(stderr, "\n");
   fprintf(stderr, "VTEDlite_hts_engine - The Vietnamese TTS system \"VTEDlite+hts_engine\"\n");
   fprintf(stderr, "\n");
   fprintf(stderr, "  usage:\n");
   fprintf(stderr, "       VTEDlite_hts_engine [ options ] [ infile ] \n");
   fprintf(stderr, "  options:                                                           [  def][ min-- max]\n");
   fprintf(stderr, "    -m  htsvoice   : HTS voice                                       [  N/A]\n");
   fprintf(stderr, "    -o  wav        : filename of output wav audio (generated speech) [  N/A]\n");
   fprintf(stderr, "    -s  i          : sampling frequency                              [ auto][   1--    ]\n");
   fprintf(stderr, "    -p  i          : frame period (point)                            [ auto][   1--    ]\n");
   fprintf(stderr, "    -a  f          : all-pass constant                               [ auto][ 0.0-- 1.0]\n");
   fprintf(stderr, "    -b  f          : postfiltering coefficient                       [  0.0][ 0.0-- 1.0]\n");
   fprintf(stderr, "    -r  f          : speech speed rate                               [  1.0][ 0.0--    ]\n");
   fprintf(stderr, "    -fm            : additional half-tone                            [  0.0][    --    ]\n");
   fprintf(stderr, "    -u  f          : voiced/unvoiced threshold                       [  0.5][ 0.0-- 1.0]\n");
   fprintf(stderr, "    -jm f          : weight of GV for spectrum                       [  1.0][ 0.0--    ]\n");
   fprintf(stderr, "    -jf f          : weight of GV for Log F0                         [  1.0][ 0.0--    ]\n");
   fprintf(stderr, "    -g  f          : volume (dB)                                     [  0.0][    --    ]\n");
   fprintf(stderr, "    -z  i          : audio buffer size (if i==0, turn off)           [    0][   0--    ]\n");
   fprintf(stderr, "  infile:\n");
   fprintf(stderr, "    text file                                                                [stdin]\n");
   fprintf(stderr, "\n");

   exit(0);
}

int main(int argc, char* argv[]){

    char buff[INPUT_BUFF_SIZE];
    FILE *fp_txt = stdin;
    char *fn_txt = NULL;
    char *fn_wav = NULL;
    char *fn_voice = NULL;
    int i;
    /* HTS Engine API */
    HTS_Engine engine;

    if(argc == 1) usage();

    /* get HTS voice file name */
    for (i = 0; i < argc; i++) {
      if (argv[i][0] == '-' && argv[i][1] == 'm')
         fn_voice = argv[++i];
      if (argv[i][0] == '-' && argv[i][1] == 'h')
         usage();
    }
    if (fn_voice == NULL) {
        fprintf(stderr, "TEDlite_hts_engine: HTS voice must be specified.\n");
        exit(1);
    }

    HTS_Engine_initialize(&engine); 

   /* load HTS voice */
    if( HTS_Engine_load(&engine, &fn_voice, 1) != TRUE){
        fprintf(stderr, "TEDlite_hts_engine: HTS voice cannot be loaded.\n");
        HTS_Engine_clear(&engine);
        exit(1);
    }

    /* read command */
    while (--argc) {
        if (**++argv == '-') {
            switch (*(*argv + 1)) {
            case 'm':             /* HTS voice was already loaded */
                ++argv;
                --argc;
                break;
            case 'o':
                fn_wav = *++argv;
                --argc;
                break;
            case 'h':
                usage();
                break;
            case 's':
                //HTS_Engine_set_sampling_frequency(&engine, (size_t) atoi(*++argv));
                --argc;
                break;
            case 'p':
                //HTS_Engine_set_fperiod(&engine, (size_t) atoi(*++argv));
                --argc;
                break;
            case 'a':
                //HTS_Engine_set_alpha(&engine, atof(*++argv));
                --argc;
                break;
            case 'b':
                //HTS_Engine_set_beta(&engine, atof(*++argv));
                --argc;
                break;
            case 'r':
                //HTS_Engine_set_speed(&engine, atof(*++argv));
                --argc;
                break;
            case 'f':
                switch (*(*argv + 2)) {
                case 'm':
                   //HTS_Engine_add_half_tone(&engine, atof(*++argv));
                   break;
                default:
                   fprintf(stderr, "TEDlite_hts_engine: Invalid option '-f%c'.\n", *(*argv + 2));
                   exit(1);
                }
                --argc;
                break;
            case 'u':
                //HTS_Engine_set_msd_threshold(&engine, 1, atof(*++argv));
                --argc;
                break;
            case 'j':
                switch (*(*argv + 2)) {
                case 'm':
                   //HTS_Engine_set_gv_weight(&engine, 0, atof(*++argv));
                   break;
            case 'f':
            case 'p':
                //HTS_Engine_set_gv_weight(&engine, 1, atof(*++argv));
                break;
            default:
                fprintf(stderr, "TEDlite_hts_engine: Invalid option '-j%c'.\n", *(*argv + 2));
                exit(1);
            }
            --argc;
            break;
            case 'g':
                //HTS_Engine_set_volume(&engine, atof(*++argv));
                --argc;
                break;
            case 'z':
                //HTS_Engine_set_audio_buff_size(&engine, atoi(*++argv));
                --argc;
                break;
            default:
                fprintf(stderr, "TEDlite_hts_engine: Invalid option '-%c'.\n", *(*argv + 1));
                exit(1);
            }
        } else {
            fn_txt = *argv;
        }
    }

    /* synthesis */
    if (fn_txt != NULL){
        remove("../build/log26101992.txt");
        copyData(fn_txt);
        fp_txt = fopen("../build/log26101992.txt", "r");       
    }

    clock_t tic = clock();

    if (fgets(buff, INPUT_BUFF_SIZE, fp_txt) != NULL && strlen(buff) > 0){
        int num_line = 0;
        char **label_data = get_labeldata(buff, &num_line);
        if(HTS_Engine_synthesize_from_strings(&engine, label_data, num_line) != TRUE){
            fprintf(stderr, "Error: waveform cannot be synthesized.\n");
        }
        
        if (fn_wav != NULL) {
            FILE *fp = fopen(fn_wav, "wb");
            HTS_Engine_save_riff(&engine, fp);
            fclose(fp);
        }
    }
    
    clock_t toc = clock();
   // printf("Elapsed: %f seconds\n", (double)(toc - tic) / CLOCKS_PER_SEC);

    fclose(fp_txt);
    remove("../build/log26101992.txt");
}