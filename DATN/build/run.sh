#!/bin/bash

ext1=txt
ext2=lab

for file in /home/hoan/Desktop/NA-NEW/textN/NA-NEW_slt_*.$ext1
do	
	filename=${file%.*}
	IFS='/' eval 'array=($filename)'
	./VTEDlite_hts_engine -m /home/hoan/Documents/voices/demen_slt.htsvoice -ow output.wav $file > /home/hoan/Desktop/NA-NEW/gen/${array[6]}.$ext2
	echo ${array[6]}.$ext2
	sleep 1
done
