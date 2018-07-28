#!/usr/bin/perl
# -w

$sample=shift;
$outpath=shift;
$idx=shift;


#########Condor submission script
system("rm -f ${outpath}/${sample}/tuple_${idx}.sub");
open SUBFILE, "> ${outpath}/${sample}/tuple_${idx}.sub" or die "@_";
print SUBFILE "Universe   = vanilla \n"; 
print SUBFILE "Executable = /bin/bash \n"; 
print SUBFILE "Arguments  = ${outpath}/${sample}/tuple_${idx}.sh \n"; 
print SUBFILE "Log        = ${outpath}/${sample}/tuple_${idx}.log \n"; 
print SUBFILE "Output     = ${outpath}/${sample}/tuple_${idx}.log \n"; 
print SUBFILE "Error      = ${outpath}/${sample}/tuple_${idx}.log \n"; 
print SUBFILE "Queue \n"; 
close SUBFILE;
