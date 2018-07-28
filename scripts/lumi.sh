#This script needs to run from an athena testarea, run like this:
#../../testCxAODFramework/00-00-06/HbbAnalysis/scripts/lumi.sh /afs/cern.ch/work/b/benitezj/CxTupleSamples/Zee/00-00-06/samples.txt 

#Input file contains a list of sample names in one column, eg.:
#data12_8TeV.00202660.physics_Muons.merge.AOD.r5724_p1751
#..
#..

#remove output file 
rm -f lumi.txt

#loop over the input samples and calculate lumi for each
for s in `cat $1 | grep -v "#" | grep data`; do
export RUN=`echo ${s} | awk -F'.' '{print $2}'`
export RESULT=`iLumiCalc.exe --runnumber=$RUN --quiet --lumitag=OflLumi-8TeV-003 --livetrigger=L1_EM30 --trigger=None --xml=/afs/cern.ch/user/b/benitezj/scratch0/testCxAODFramework/00-00-06/HbbAnalysis/data/data12_8TeV.periodAllYear_DetStatus-v61-pro14-02_DQDefects-00-01-00_PHYS_StandardGRL_All_Good.PeriodB.xml --lar --lartag=LARBadChannelsOflEventVeto-UPD4-04 | grep 'Total IntL recorded'`
export LUM=`echo $RESULT | awk -F' ' '{print $6}'`

if [ "$LUM" == "" ]; then
echo "0 $s" >> lumi.txt
fi 
if [ "$LUM" != "" ]; then
echo "${LUM} $s" >> lumi.txt
fi

done


###Add up to get total luminosity
export TOTLUM=`gawk '{ sum += $1 }; END { print sum }' lumi.txt`
echo "Total Luminosity: ${TOTLUM}/1000000" >> lumi.txt
cat lumi.txt

