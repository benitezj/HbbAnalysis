#!/bin/bash
export eos='/afs/cern.ch/project/eos/installation/0.3.15/bin/eos.select'

##
#export XAODCONFIG=data/HbbAnalysis/CxAODMaker-job.cfg
##config file changed for 00-07-00
export XAODCONFIG=data/HbbAnalysis/framework-run.cfg
echo "XAODCONFIG $XAODCONFIG"

export XAODOUTPATH=$OUTPUTDIR/CxAODGrid 
echo "XAODOUTPATH $XAODOUTPATH"

#for local jobs 
export XAODSAMPLEPATH=""
echo "XAODSAMPLEPATH $XAODSAMPLEPATH"

#for grid jobs
export XAODNFILES=1
echo "XAODNFILES $XAODNFILES"
export XAODOUTTAG=$3
echo "XAODOUTTAG $XAODOUTTAG"
export XAODNOSUBMIT=0
echo "XAODNOSUBMIT $XAODNOSUBMIT"

export XAODBLACKLIST=""
##CxAODMaker does not compile here at SiGNET:
export XAODBLACKLIST="ANALY_SiGNET"
#export XAODBLACKLIST="ANALY_SiGNET,ANALY_SARA,ANALY_INFN-T1"
#export XAODBLACKLIST="ANALY_SiGNET,ANALY_LUNARC,ANALY_NSC"
export XAODBLACKLIST="ANALY_SiGNET,ANALY_UIO,ANALY_LRZ"
echo "XAODBLACKLIST $XAODBLACKLIST"

###print sample list
if [ "$2" != "" ]; then 
for s in `cat $2 | grep -v "#" `; do
echo "$s"
done
fi


####################
###CxAOD Grid Production  
###################
if [ "$1" == "clean" ]; then 
echo "Cleaning grid submission directories"
for s in `cat $2 | grep -v "#" `; do
echo "rm $XAODOUTPATH/${s}*"
rm -rf $XAODOUTPATH/${s}*
done
fi

########list sites 
if [ "$1" == "replicas" ]; then 
echo "Check replicas"
for s in `cat $2 | grep -v "#" `; do
dq2-ls -r $s
#export scope=`echo $s | awk -F'.' '{print $1}'`
#rucio list-dataset-replicas ${scope}:$s
done
fi

#####submit
if [ "$1" == "grid" ]; then 
echo "Running grid submission"
for s in `cat $2 | grep -v "#" `; do
export XAODSAMPLENAME=$s
cxaodproducer grid
done
fi

######check pbook status
if [ "$1" == "pcheck" ]; then 
echo "Checking Panda Status"
rm -f pbook.tmp
rm -f pcheck_done.tmp
rm -f pcheck_notdone.tmp

echo "exit()" | pbook
pbook -c "show()" >> pbook.tmp

touch pcheck_done.tmp
touch pcheck_notdone.tmp

for s in `cat $2 | grep -v "#" `; do
echo "====$s===="
export done=`searchPBOOK.pl pbook.tmp $s | grep done`
if [ "$done" != "" ]; then
echo $s >> pcheck_done.tmp
else
echo $s >> pcheck_notdone.tmp
fi
done

echo "=====Done samples======"
cat pcheck_done.tmp
echo "=====Not done samples=="
cat pcheck_notdone.tmp
fi


###########################
#####download samples to afs
##########################
if [ "$1" == "dafs" ]; then 
for s in `cat $2 | grep -v "#" `; do

export gridname=`echo $s | awk -F'.' '{print $1"."$2"."$3}'`
if [ "$XAODOUTTAG" != "" ]; then
export gridname=${gridname}_${XAODOUTTAG}
fi

echo "Running Grid download for $sample"
mkdir $OUTPUTDIR/CxAODSamples/$CXTAG/$s
dq2-get -H $OUTPUTDIR/CxAODSamples/$CXTAG/$s user.benitezj.${gridname}_outputLabel.root/
##dq2-get -H $OUTPUTDIR/CxAODSamples/$CXTAG/$s user.benitezj.${s}.log/
##dq2-get -H $OUTPUTDIR/CxAODSamples/$CXTAG/$s user.benitezj.${s}_hist-output.root/
done
fi

###########################
#####download samples to cluster
##########################
if [ "$1" == "dcluster" ]; then 
echo "Downloading samples to cluster."
for s in `cat $2 | grep -v "#" `; do

export gridname=`echo $s | awk -F'.' '{print $1"."$2"."$3}'`
if [ "$XAODOUTTAG" != "" ]; then
export gridname=${gridname}_${XAODOUTTAG}
fi

echo "Running Grid download for $sample"
mkdir $OUTPUTDIRCLUSTER/CxAODSamples/$CXTAG/$s
dq2-get -H $OUTPUTDIRCLUSTER/CxAODSamples/$CXTAG/$s user.benitezj.${gridname}_outputLabel.root/
done
fi



##################################
#####download samples to eos via afs mount
################################### 
#NOTE: eos must be mounted in this path: $OUTPUTDIR/eos
if [ "$1" == "deos" ]; then 
for s in `cat $2 | grep -v "#" `; do
echo "===$s==="

export gridname=`echo $s | awk -F'.' '{print $1"."$2"."$3}'`
if [ "$XAODOUTTAG" != "" ]; then
export gridname=${gridname}_${XAODOUTTAG}
fi

$eos mkdir $EOSDIR/CxAODSamples/$CXTAG/$s
dq2-get -H $OUTPUTDIR/$EOSDIR/CxAODSamples/$CXTAG/$s user.benitezj.${gridname}_outputLabel.root/

done
fi


#####################################
###add datasets to container
####################################
if [ "$1" == "cont" ]; then
echo "Datasets in container before:"
dq2-list-datasets-container user.benitezj.CxAOD.$CXTAG/ | grep .root | wc -l
for s in `cat $2 | grep -v "#" `; do
echo "============$s=========="

export gridname=`echo $s | awk -F'.' '{print $1"."$2"."$3}'`
if [ "$XAODOUTTAG" != "" ]; then
export gridname=${gridname}_${XAODOUTTAG}
fi

export datasetContainer=user.benitezj.${gridname}_outputLabel.root/

for ds in `dq2-list-datasets-container ${datasetContainer}`; do 
echo "register: $ds"
dq2-register-datasets-container user.benitezj.CxAOD.$CXTAG/ $ds
done

echo "======================================================="
done 
echo "Datasets in container after:"
dq2-list-datasets-container user.benitezj.CxAOD.$CXTAG/ | grep .root | wc -l
fi

#####################################
###Copy from CERN-PROD_SCRATCHDISK to eos 
#####################################
if [ "$1" == "cern2eos" ]; then
#loop over the samples
for s in `cat $2 | grep -v "#" `; do
echo "============Copying $s=========="

export gridname=`echo $s | awk -F'.' '{print $1"."$2"."$3}'`
if [ "$XAODOUTTAG" != "" ]; then
export gridname=${gridname}_${XAODOUTTAG}
fi

export datasetContainer=user.benitezj.${gridname}_outputLabel.root/

#print out the list of datasets in each sample
dq2-list-datasets-container $datasetContainer

#loop over the datasets in the sample
for ds in `dq2-list-datasets-container $datasetContainer`; do

#check if the dataset is at CERN
export atcern=`dq2-list-dataset-replicas $ds | grep COMPLETE: | grep CERN-PROD_SCRATCHDISK`
if [ "$atcern" != "" ]; then
echo "$ds is at CERN"

#loop over the root files 
for file in `dq2-ls -L CERN-PROD_SCRATCHDISK -fp $ds  |  grep srm://` ; do


##NOTE the following relies on this type of fullpath:
##/eos/atlas/atlasscratchdisk/rucio/user/benitezj/26/ef/user.benitezj.4644211._000024.outputLabel.root
export fullpath=`echo $file | awk -F'cern.ch' '{print $2}'`
export filename=`echo $fullpath | awk -F'/' '{print $10}'`
if [ "`echo $filename | grep .root`" == "" ];then
echo "Something is wrong with the filename from file path $fullpath"
exit 1
fi

#check the file is not already there from a previous transfer
if [ "`$eos ls $EOSDIR/CxAODSamples/$CXTAG/$s/$filename`" == "" ]; then
$eos cp $fullpath $EOSDIR/CxAODSamples/$CXTAG/$s/
fi

done #rootfiles

fi # if dataset at CERN

done #datasets

echo "======================================================="
done #samples
fi



###################################
############Verify afs downloads
##################################
if [ "$1" == "vafs" ]; then 
for s in `cat $2 | grep -v "#" `; do
echo "Verifying download for $s:"

export gridname=`echo $s | awk -F'.' '{print $1"."$2"."$3}'`
if [ "$XAODOUTTAG" != "" ]; then
export gridname=${gridname}_${XAODOUTTAG}
fi

echo "From dq2-ls:"
dq2-ls -f user.benitezj.${gridname}_outputLabel.root/ | grep .root | wc -l
echo "From afs:"
/bin/ls $OUTPUTDIR/CxAODSamples/$CXTAG/$s | grep outputLabel.root | wc -l
done 
fi


###################################
############Verify downloads to eos
##################################
if [ "$1" == "veos" ]; then 
echo "Verifying EOS downloads:"

rm -f veos_complete.tmp
rm -f veos_incomplete.tmp

touch veos_complete.tmp
touch veos_incomplete.tmp

for s in `cat $2 | grep -v "#" `; do

export gridname=`echo $s | awk -F'.' '{print $1"."$2"."$3}'`
if [ "$XAODOUTTAG" != "" ]; then
export gridname=${gridname}_${XAODOUTTAG}
fi

echo "check $s"
export ndq2=`dq2-ls -f user.benitezj.${gridname}_outputLabel.root/ | grep "\[" | grep .root | wc -l`
export neos=`$eos ls $EOSDIR/CxAODSamples/$CXTAG/$s/ | grep outputLabel.root | wc -l`
echo "From dq2: $ndq2"
echo "From eos: $neos"

if [ "$neos" == "$ndq2" ]; then
echo $s >> veos_complete.tmp
fi

if [ "$neos" != "$ndq2" ]; then
echo $s >> veos_incomplete.tmp
fi

done 

echo "Complete samples:"
cat veos_complete.tmp
echo "Incomplete samples:"
cat veos_incomplete.tmp

fi

###################################
############remove afs sample
##################################
if [ "$1" == "rmafs" ]; then 
echo "Removing samples on /afs"
for s in `cat $2 | grep -v "#" `; do
echo "Removing $s:"
rm -rf $OUTPUTDIR/CxAODSamples/$CXTAG/$s
done 
fi


###################################
############list samples in afs
##################################
if [ "$1" == "lafs" ]; then 
echo "Samples in $XAODOUTPATH/CxAODSamples/$CXTAG/:"
for s in `cat $2 | grep -v "#" `; do
echo "====$s==="
/bin/ls $OUTPUTDIR/CxAODSamples/$CXTAG/$s
done
fi

###################################
############list samples in eos
##################################
if [ "$1" == "leos" ]; then 
echo "Samples in $EOSDIR/CxAODSamples/$CXTAG/:"
for s in `cat $2 | grep -v "#" `; do
echo "======$s========"
$eos ls $EOSDIR/CxAODSamples/$CXTAG/$s
done 
fi

#################################
#####Copy from EOS to afs#######
#################################
if [ "$1" == "eos2afs" ]; then 
echo "Copying from eos to afs:"
for s in `cat $2 | grep -v "#" `; do
echo "$EOSDIR/CxAODSamples/$CXTAG/$s/ \n"
rm -rf $OUTPUTDIR/CxAODSamples/$CXTAG/$s
mkdir $OUTPUTDIR/CxAODSamples/$CXTAG/$s
$eos cp -r $EOSDIR/CxAODSamples/$CXTAG/$s/ $OUTPUTDIR/CxAODSamples/$CXTAG/$s/
done
fi

##################################
############remove eos sample
##################################
if [ "$1" == "rmeos" ]; then 
echo "Removing samples on eos"
for s in `cat $2 | grep -v "#" `; do
echo "Removing $s:"
for f in `$eos ls $EOSDIR/CxAODSamples/$CXTAG/$s | grep outputLabel.root`; do
$eos rm $EOSDIR/CxAODSamples/$CXTAG/$s/$f;
done
$eos rmdir $EOSDIR/CxAODSamples/$CXTAG/$s/
done 
fi


######################################
#####Remove datasets from the container
######################################
if [ "$1" == "clean_cont" ]; then 
echo "Removing samples from container user.benitezj.CxAOD.$CXTAG/"
for d in `dq2-list-datasets-container user.benitezj.CxAOD.$CXTAG/`; do
#see if this dataset is in the list of the samples to be removed
for s in `cat $2 | grep -v "#" `; do
#use the run number as uniqe identifier
export runid=`echo $s | awk -F'.' '{print "."$2"."}'`
if [ "`echo $d | grep $runid`" != "" ]; then
export command="rucio detach user.benitezj:user.benitezj.CxAOD.$CXTAG/ $d"
echo $command
$command
fi
done
done
fi


#################################
#####Cluster #######
#################################
export CLUSTERDIR=/nfs/uiowapc00/data/benitezj
if [ "$1" == "eos2cluster" ]; then 
echo "Copying from eos to cluster:"
for s in `cat $2 | grep -v "#" `; do
echo "$EOSDIR/CxAODSamples/$CXTAG/$s \n"
rm -rf $CLUSTERDIR/CxAODSamples/$CXTAG/$s
mkdir $CLUSTERDIR/CxAODSamples/$CXTAG/$s
#xrdcp -f -R root://eosatlas.cern.ch/$EOSDIR/CxAODSamples/$CXTAG/$s $CLUSTERDIR/CxAODSamples/$CXTAG/
$eos cp -r $EOSDIR/CxAODSamples/$CXTAG/$s/ $CLUSTERDIR/CxAODSamples/$CXTAG/$s/
done
fi



###########################
#####download xAOD samples to cluster
##########################
if [ "$1" == "dclusterxAOD" ]; then 
echo "Downloading xAOD samples to cluster."
for s in `cat $2 | grep -v "#" `; do
echo "Running Grid download for $sample"
mkdir $OUTPUTDIRCLUSTER/xAODSamples/$s
dq2-get -H $OUTPUTDIRCLUSTER/xAODSamples/$s $s/
done
fi
