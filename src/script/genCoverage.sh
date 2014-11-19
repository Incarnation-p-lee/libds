#!/bin/sh
basedir=./obj_out
reportdir="$basedir/coverage"
outputdir="$reportdir/output"
rawdatafile="coverage.info"
binary="Data Structure"

root_dir=`pwd | xargs basename`

if [ "$root_dir" != "libds" ]
then
  echo "Please execute script under root dir: libds/"
  exit 1
fi

if [ ! -x "$basedir" ]; then
  echo 'Failed to locate BASEDIR'
  exit 1
fi

if [ ! -x "$reportdir" ];then
  mkdir "$reportdir"
fi

mv -v ./src/*.gc[dn][ao] "$reportdir"
mv -v ./src/*/*.gc[dn][ao] "$reportdir"
cp -v ./src/*.c "$reportdir"
cp -v ./src/*/*.c "$reportdir"

lcov --capture --directory "$reportdir" --output-file "$rawdatafile" --test-name "$binary"

mv "$rawdatafile" "$reportdir"

echo '---------'

if [ -x "$ouputdir" ];then
  rm -rf "$outputdir"
fi


genhtml --output-directory "$outputdir" --title "LIBDS" --show-details --legend "$reportdir/$rawdatafile"
