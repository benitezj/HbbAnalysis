#!/usr/bin/perl
# -w

##NOTES:
#1. This script must be executed from the analysis directory containing ./rcSetup.sh
#2. condor needs a HOME directory where it can write to.

$storage=shift;
$sample=shift;
$outpath=shift;
$idx=shift;
$filelist=shift;

$HOME="/nfs/home/condor";


###############ATLAS Job execution##########################
system("rm -f ${outpath}/${sample}/tuple_${idx}.sh");
open OUTFILE, "> ${outpath}/${sample}/tuple_${idx}.sh" or die "@_";


print OUTFILE "echo '+++++++++++++User+++++++++++:'; whoami;\n";
print OUTFILE "echo '+++++++++++++Machine+++++++++++:'; echo \$HOSTNAME \n";
print OUTFILE "echo '+++++++++++++Tokens+++++++++++:'; tokens \n";
print OUTFILE "echo '+++++++++++++Initial Dir+++++++++++:'; pwd; /bin/ls -l \n";
print OUTFILE "export HOME=${HOME}\n";
print OUTFILE "source \$HOME/.bash_profile \n";
print OUTFILE "echo '+++++++++++++PATH+++++++++++++:'; echo \$PATH \n";

print OUTFILE "echo '+++++++++++++ATLAS Setup+++++++++++:'\n";
print OUTFILE "export ATLAS_LOCAL_ROOT_BASE=/cvmfs/atlas.cern.ch/repo/ATLASLocalRootBase \n";
print OUTFILE "source \$ATLAS_LOCAL_ROOT_BASE/user/atlasLocalSetup.sh \n";
print OUTFILE "source \$PWD/rcSetup.sh \n";


print OUTFILE "echo '+++++++++++++Downloading files+++++++++++:';\n";
print OUTFILE "mkdir -p /tmp/${sample}_${idx}/${sample}\n";
if($storage eq "eos"){
    print OUTFILE "export eos='/afs/cern.ch/project/eos/installation/0.3.15/bin/eos.select'\n";
    print OUTFILE "\$eos cp ${filelist} /tmp/${sample}_${idx}/${sample}\n";
}
if($storage eq "afs"){
    print OUTFILE "cp ${filelist} /tmp/${sample}_${idx}/${sample}\n";
}
if($storage eq "cluster"){
    print OUTFILE "cp ${filelist} /tmp/${sample}_${idx}/${sample}\n";
}
print OUTFILE "echo '+++++++++++++Download Dir+++++++++++:'; /bin/ls -l /tmp/${sample}_${idx}/${sample} \n";



print OUTFILE "export XAODCONFIG=data/HbbAnalysis/framework-run.cfg\n";
print OUTFILE "export XAODSAMPLEPATH=/tmp/${sample}_${idx} \n";
print OUTFILE "export XAODSAMPLENAME=${sample} \n";
print OUTFILE "export XAODOUTPATH=. \n";
print OUTFILE "echo '+++++++++++++Enviroment+++++++:'; printenv \n";
print OUTFILE "echo '+++++++++++++Executing+++++++++++:';\n";
print OUTFILE "cd \$TMPDIR\n";
print OUTFILE "cxaodproducer local\n";
print OUTFILE "echo '+++++++++++++Execute Dir+++++++++++:'; pwd; /bin/ls -l \n";
print OUTFILE "mv ${sample}/data-outputLabel/outputLabel.root ${outpath}/${sample}/outputLabel_${idx}.root \n";
print OUTFILE "echo '+++++++++++++Output File+++++++++++:'; /bin/ls -l ${outpath}/${sample}/outputLabel_${idx}.root \n";
print OUTFILE "rm -rf /tmp/${sample}_${idx} \n";
close OUTFILE;


system("./HbbAnalysis/scripts/makeCondorSub.pl ${sample} ${outpath} ${idx}");
