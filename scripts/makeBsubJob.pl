#!/usr/bin/perl
# -w

$storage=shift;
#$inpath=shift;
$sample=shift;
$outpath=shift;
$algo=shift;
$idx=shift;
$filelist=shift;

system("rm -f ${outpath}/${sample}/tuple_${idx}.sh");
open OUTFILE, "> ${outpath}/${sample}/tuple_${idx}.sh" or die "@_";

print OUTFILE "tokens \n";
print OUTFILE "printenv \n";
print OUTFILE "source /cvmfs/atlas.cern.ch/repo/ATLASLocalRootBase/user/atlasLocalSetup.sh \n";
print OUTFILE "source \$LS_SUBCWD/rcSetup.sh \n";

#####This setup works by reading the input from eos
#print OUTFILE "export TUPLENFILES=0 \n"; 
#print OUTFILE "export TUPLECONFIG=data/HbbAnalysis/TupleMaker-job.cfg \n";
#print OUTFILE "export TUPLECHANNEL=${algo} \n";
#print OUTFILE "export TUPLEINPATH=${inpath} \n";
#print OUTFILE "export TUPLESAMPLENAME=${sample} \n";
#print OUTFILE "export TUPLEOUTPATH=. \n";
#print OUTFILE "cxtupleproducer ${storage}select_lxplus $filelist \n";


###This setup copies the input to the worker and processes it locally
##Note file list had to be modified to include full eos path and separated by spaces
print OUTFILE "mkdir -p ./tmp/${sample} \n";

if($storage eq "eos"){
    print OUTFILE "export eos='/afs/cern.ch/project/eos/installation/0.3.15/bin/eos.select'\n";
    print OUTFILE "\$eos cp ${filelist} ./tmp/${sample}/ \n";
}
if($storage eq "afs"){
    print OUTFILE "cp ${filelist} ./tmp/${sample}/ \n";
}

print OUTFILE "export TUPLENFILES=0 \n"; 
print OUTFILE "export TUPLECONFIG=data/HbbAnalysis/TupleMaker-job.cfg \n";
print OUTFILE "export TUPLECHANNEL=${algo} \n";
print OUTFILE "export TUPLEINPATH=./tmp/ \n";
print OUTFILE "export TUPLESAMPLENAME=${sample} \n";
print OUTFILE "export TUPLEOUTPATH=. \n";
print OUTFILE "cxtupleproducer afs_lxplus \n";


###send the output 
print OUTFILE "mv ./${sample}/data-output/tuple.root ${outpath}/${sample}/tuple_${idx}.root \n";
close OUTFILE;
#print "Created ${outpath}/bsub_${idx}.sh \n";




########################################################
#print OUTFILE "cd \$LS_SUBCWD/ \n";
#print OUTFILE "pwd \n";
#print OUTFILE "ls . \n";

###Debugging:
#print OUTFILE "echo \$ROOTCOREBIN \n";
#print OUTFILE "echo \$ROOTCOREDIR \n";
#print OUTFILE "echo \$ROOTCORECONFIG \n";
#print OUTFILE "echo \$ATLAS_LOCAL_RCSETUP_PATH \n";
#print OUTFILE "ls /cvmfs/atlas.cern.ch/repo/ATLASLocalRootBase/x86_64/root/ \n";
#print OUTFILE "ls /usr/lib64/ | grep libstdc \n";
#print OUTFILE "nm -D /usr/lib64/libstdc++.so.6 | grep GLIB \n";

###ATLAS setup
#print OUTFILE "export ATLAS_LOCAL_ROOT_BASE=/cvmfs/atlas.cern.ch/repo/ATLASLocalRootBase \n";
#print OUTFILE "source \$ATLAS_LOCAL_ROOT_BASE/user/atlasLocalSetup.sh \n";

###This is already set correctly after rcSetup
#print OUTFILE "export ROOTCORECONFIG=x86_64-slc6-gcc48-opt \n";
#print OUTFILE "source \$ROOTCOREBIN/local_setup.sh \n";

#print OUTFILE "export ATLAS_LOCAL_RCSETUP_PATH=/cvmfs/atlas.cern.ch/repo/ATLASLocalRootBase/x86_64/rcSetup/00-04-09 \n";
#print OUTFILE "source \$ATLAS_LOCAL_RCSETUP_PATH/rcSetup.sh -u\n";
#print OUTFILE "source \$ATLAS_LOCAL_RCSETUP_PATH/rcSetup.sh \n";


######
#print OUTFILE "rc root -l -b -q \"\$ROOTCOREDIR/scripts/load_packages.C\" \"\$ROOTCOREBIN/user_scripts/EventLoop/batch_worker.C(${idx},\\\"${outpath}/submit/config.root\\\")\" \n";
