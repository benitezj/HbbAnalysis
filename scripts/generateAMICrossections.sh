
rm -f ./amiCrossections_${1}.txt

for d in `ami list datasets --type AOD ${1}%merge.AOD%`; do 
#echo $d

##id ("run")
export run=`echo $d | awk -F'.' '{print $2}'`
export name=`echo $d | awk -F'.' '{print $3}'`

##crossection (AMI gives nb) output in pb
export X=`ami show dataset info $d | grep approx_crossSection | awk '{print $3*1000}'`

#filter efficiency
export E=`ami show dataset info $d | grep approx_GenFiltEff | awk '{print $3}'`

#write out the final crossection after correctiong by efficiency and convert pb 
export XE=`echo "$X $E" | awk '{print $1*$2}'` 

echo "$run $XE $X $E $name" >> amiCrossections_${1}.txt 

done

