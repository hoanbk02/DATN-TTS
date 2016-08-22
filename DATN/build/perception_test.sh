#!/bin/bash

ext=txt

voice1=/home/hoan/Documents/voices/demen_slt.htsvoice
ext1=-TS1.wav

voice2=/home/hoan/Documents/voices/TT-TQDT_trangntt.htsvoice
ext2=-TS2.wav

for file in /home/hoan/Dropbox/PerceptionTest/FinalTest/MOS/*.$ext
do	
	filename=${file%.*}	
	./VTEDlite_hts_engine -m $voice2 -o ${filename}$ext2 ${file}
	echo ${filename}$ext2
done

#chuan bi du lieu cho Perception Test
