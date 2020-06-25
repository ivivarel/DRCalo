#! /bin/bash 

if [ $# -ne 1 ] 
then 
    echo 'USAGE: UpdateG4Tree.sh [INPUTDIR]' 
    echo 'where INPUTDIR is the directory containing the reco and truth trees' 
else

    inputdir=$1
    for file in `ls ${inputdir}/*_truth.root`
    do 
	recofilename=`echo $file | sed 's/_truth//g'`
	newfilename=`echo $file | sed 's/_truth/_merged/g'`
	root -b -x -q "UpdateG4tree.cxx(\"${recofilename}\",\"${file}\",\"${newfilename}\")"
    done 
fi
