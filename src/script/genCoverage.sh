#!/bin/sh
binarydir="./"
reportdir="./report"
outputdir="/output"
rawdatafile="coverage.info"
basedir="./"
binary="dsaaa.out"
reportname="report.tar.gz"
archivedir="archive/"

if [ ! -x "$reportdir" ];then
  mkdir "$reportdir"
fi

mv *.gcda "$reportdir"
mv *.gcno "$reportdir"

lcov --capture --directory "$reportdir" --base-directory "$basedir" --output-file "$rawdatafile" --test-name "$binary"

mv "$rawdatafile" "$archivedir"

if [ -x "$reportdir$ouputdir" ];then
  rm -rf "$reportdir$outputdir"
fi

genhtml --output-directory "$reportdir$outputdir" --title "DSAAA" --show-details --legend "$archivedir$rawdatafile"
cp -rp $reportdir/output/ .
tar -zcf "$reportname" "$reportdir$outputdir"
mv "$reportname" "$archivedir"
