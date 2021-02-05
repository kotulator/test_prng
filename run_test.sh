#!/bin/bash
FILE_TO_USE=$1
COUNT=$2
REPORT_FILE="Report__${FILE_TO_USE}"
END=16;
echo "Diehard Test on sample ${COUNT}" > $REPORT_FILE
for ((i=0;i<=END;i++)); do
	echo "Test ${i} on file ${FILE_TO_USE}"
	dieharder -d $i -f $FILE_TO_USE -g 202 -D 3071 >> $REPORT_FILE
done

