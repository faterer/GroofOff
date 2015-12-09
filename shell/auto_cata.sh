#!/bin/sh


mkdir -p ./nopassed/
for i in `ls *.html`
do
 echo $i
 SCORE=`sed -n 48p $i|sed -re 's/[^0-9]*([0-9]*).*$/\1/;'`
 if [ $SCORE -ge 40 ]; then
  STUDENTNO=`echo $i|sed -re 's/[^0-9]*([0-9]*).*$/\1/;'`
  CLASSNO=`grep "^$STUDENTNO" number.txt|awk -F " " '{print $2}'`
  echo $CLASSNO
  mkdir -p $CLASSNO
  mv $i $CLASSNO
 else
  mv $i ./nopassed/ 
 fi
done

