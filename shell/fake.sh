#!/bin/sh

COUNT=1
mkdir -p result
for i in `ls *.html`
do
STUDENTNO=`sed -n ${COUNT}p number.txt|awk -F " " '{print $2}'`
STUDENTNAME=`sed -n ${COUNT}p number.txt|awk -F " " '{print $1}'`
echo "$STUDENTNO $STUDENTNAME"
REPLACESTR="${STUDENTNAME}的答卷信息"
echo $REPLACESTR
sed '34d' $i|sed "34i\\\t\t\t\t<td>$STUDENTNAME</td>"|sed '40d'|sed "40i\\\t\t\t\t<td>$STUDENTNO</td>"|sed '3d'|sed "3i\\\t<title>$REPLACESTR</title>" > ${STUDENTNO}.html
mv ${STUDENTNO}.html result
COUNT=`expr $COUNT + 1`
done
