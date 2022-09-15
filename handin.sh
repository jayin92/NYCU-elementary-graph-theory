#!/bin/bash

id=110550088
folderName=$1
cntFile=$(ls $folderName | grep .cpp | wc -l)

mkdir -p tmp/$folderName-$id
mkdir -p hw-zip

for ((i=1;i<=$cntFile;i++)); do
    cp $folderName/p$i.cpp tmp/$folderName-$id/${folderName}_$i-$id.cpp
done

zip -r -j hw-zip/$folderName-$id.zip tmp/$folderName-$id
