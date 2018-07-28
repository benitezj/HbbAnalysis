#!/usr/bin/perl
# -w
use File::Basename;
$eos="/afs/cern.ch/project/eos/installation/0.3.15/bin/eos.select";

$samplesfile=shift;#must be a full path in AFS
$option=shift;

####
$AFSDIR=$ENV{'OUTPUTDIR'};
$CLUSTERDIR=$ENV{'OUTPUTDIRCLUSTER'};
$EOSDIR=$ENV{'EOSDIR'};

##where the tuples will be written is the place where samplesfile is (currently only in afs or cluster)
$samplesfile = `readlink -e $samplesfile`;
chomp($samplesfile);
$outpath = dirname($samplesfile);

##variable needed to avoid reading from a wrong version
$CXTAG=`echo \$\{PWD\#\#\*/\}`; # $ENV{'CXTAG'};  ### $CXTAG is not set on a fresh term
chomp($CXTAG);

#read the samples list
@samples=`cat $samplesfile | grep '.' | grep -v "#"`;
foreach $samp (@samples){
	chomp($samp);
	$samp =~ s/^\s+|\s+$//g; ##remove beg/end spaces
	print "$option $samp\n";
}

####Clean out the directory
if($option eq "clean"){#create the batch executables    
    foreach $samp (@samples){
	chomp($samp);
	$samp =~ s/^\s+|\s+$//g; ##remove beg/end spaces
	$command="rm -rf ${outpath}/${samp}";
	print "$command \n";
	system($command);
    }
    $command="ls ${outpath}";
    print "$command\n";
    system($command);
}

######Make the shell scripts
if($option eq "create"){#create the batch executables    
    ##path to input files
    $storage=shift;#afs or eos
    ##Number of files to merge
    $nmerge=shift; 
    ##Algorithm to run
    $algo=shift;  
    #use algo=CxAOD to create CxAODs

    #overide the input CXTAG
    $cxtag=shift;
    if( $cxtag ne "" ){$CXTAG = $cxtag;}


    ###Determine the input path
    if($algo eq "CxAOD"){
	if($storage eq "afs"){ $inpath="$AFSDIR/xAODSamples"; }
	if($storage eq "cluster"){ $inpath="$CLUSTERDIR/xAODSamples"; }
	if($storage eq "eos"){ $inpath="$EOSDIR/xAODSamples"; }
    }else{
	if($storage eq "afs"){ $inpath="$AFSDIR/CxAODSamples/$CXTAG"; }
	if($storage eq "cluster"){ $inpath="$CLUSTERDIR/CxAODSamples/$CXTAG"; }
	if($storage eq "eos"){ $inpath="$EOSDIR/CxAODSamples/$CXTAG"; }
    }

    
    foreach $samp (@samples){
	chomp($samp);
	$samp =~ s/^\s+|\s+$//g; ##remove beg/end spaces

	system("mkdir ${outpath}/${samp}");

	##get list of files in storage
	if($storage eq "afs" ){ @dirlist=`/bin/ls $inpath/$samp | grep .root` }
	if($storage eq "cluster" ){ @dirlist=`/bin/ls $inpath/$samp | grep .root` }
	if($storage eq "eos" ){ @dirlist=`$eos ls $inpath/$samp | grep .root` }


	$filelist="";
	$mergecounter=0;
	$idx=0;	
	for $f (@dirlist){
	    chomp($f);
	    #print "$f\n";
	    #$filelist = "$filelist,${f}";
	    $filelist = "${filelist} ${inpath}/${samp}/${f}";
	    $mergecounter++;

	    if($mergecounter==$nmerge){
		if( $algo eq "CxAOD"){
		    $command="./HbbAnalysis/scripts/makeClusterJobCxAOD.pl ${storage} ${samp} ${outpath} ${idx} '${filelist}'";	
		}else {
		    $command="./HbbAnalysis/scripts/makeClusterJob.pl ${storage} ${samp} ${outpath} ${algo} ${idx} '${filelist}'";	
		}
		#print "$command\n";
		system("$command");
		$filelist="";
		$mergecounter=0;
		$idx++;
	    }
	}
	if($mergecounter>0){
	    if( $algo eq "CxAOD"){
		$command="./HbbAnalysis/scripts/makeClusterJobCxAOD.pl ${storage} ${samp} ${outpath} ${idx} '${filelist}'";	
	    }else{
		$command="./HbbAnalysis/scripts/makeClusterJob.pl ${storage} ${samp} ${outpath} ${algo} ${idx} '${filelist}'";	
	    }
	    #print "$command\n";
	    system("$command");
	    $idx++;
	}

	print "\n Created $idx jobs for ${outpath}/${samp}\n";
    }
}

####define batch submit function
sub submit {
    $path = $_[0];
    $idx= $_[1];
    system("rm -f ${path}/tuple_${idx}.root");
    system("rm -f ${path}/tuple_${idx}.log");
    $command="condor_submit ${path}/tuple_${idx}.sub";	
    print "$command\n";
    system("$command");
}

    
###submit all jobs
if($option eq "sub" ){
    foreach $samp (@samples){
	chomp($samp);
	$samp =~ s/^\s+|\s+$//g; ##remove beg/end spaces
	$idx=0;	
	for $f (`/bin/ls $outpath/$samp | grep tuple_ | grep .sh`){
	    chomp($f);
	    submit("${outpath}/${samp}",$idx);
	    $idx++;
	}
	print "\n Submitted $idx jobs for ${outpath}/${samp}\n";
    }
}

####Check the job output
if($option eq "check"){
    $resub=shift;

    foreach $samp (@samples){
	chomp($samp);
	$samp =~ s/^\s+|\s+$//g; ##remove beg/end spaces

	$idx=0;	
	$failcounter=0;
	for $f (`/bin/ls $outpath/$samp | grep tuple_ | grep .sh | grep -v "~" `){
	    chomp($f);
	    $job="${outpath}/${samp}/tuple_${idx}";

	    $failed=0;

 	    #check the root file was produced
 	    if($failed == 0){

# 		if(!(-e "${job}.root")){
# 		    print "No root file \n ${job}\n";
# 		    $failed = 1; 
# 		}
####The above does not work on CxAOD job		

		$rootfile=`/bin/ls ${outpath}/${samp} |  grep _${idx}.root`;
		chomp($rootfile);
		if($rootfile eq ""){
		    print "No root file \n ${job}\n";
		    $failed = 1; 
		}
 	    }

	    #check a log file was produced
	    if($failed == 0 && !(-e "${job}.log")){ 
		print "No log file \n ${job}\n"; 
		$failed = 1; 
	    }

 	    # there were input events: inputCounter = 100000
 	    if( $failed == 0){ 
		
		$failedTuple=0;
 		$inputEvents=`cat  ${job}.log | grep inputCounter`;
 		chomp($inputEvents);
 		@evtsproc=split(" ",$inputEvents);
 		if( !($evtsproc[2] > 0)){
 		    $failedTuple = 1;
 		}
 
		##in case of CxAOD job:
		#do not use cat as some log files have binary format at the beggining 
		$inputEvents=`tail -n 100  ${job}.log | grep 'Info in <AnalysisBase::finalize()>:   processed'`;
		chomp($inputEvents);
		@evtsproc=split(" ",$inputEvents);
		if( !($evtsproc[5] > 0) ){
		    $failedCxAOD = 1;
		}

		#####if neither passed
		$failed = $failedTuple && $failedCxAOD;
		if($failed){
		    print "No input events \n ${job}\n"; 
 		}

 	    }
	
	    # check Successfully completed.
	    if( $failed == 0){
		$success = `cat ${job}.log | grep "Normal termination"`;
		if($success eq "" ){
		    print "Not successfully completed \n ${job}\n";
		    $failed = 1;
		}
	    } 
	    
	    ###Resubmit
	    if($failed == 1){
		$failcounter++;		
		if($resub eq "sub"){
		    submit("${outpath}/${samp}",$idx);
		    print "Job $idx resubmitted.\n";
		}
	    }
	    
	    $idx++;
	}
	print "Failed $failcounter / $idx : ${samp} \n";
    }
}



if($option eq "counters"){
    foreach $samp (@samples){
	chomp($samp);
	$samp =~ s/^\s+|\s+$//g; ##remove beg/end spaces

	$outfile="${outpath}/${samp}/counters.txt";

	$idx=0;	
	$failcounter=0;
	for $f (`/bin/ls $outpath/$samp | grep tuple_ | grep .sh | grep -v "~" `){
	    chomp($f);
	    $job="${outpath}/${samp}/tuple_${idx}";
	    system("rm -f $outfile");
	    system("cat ${job}.log | grep inputCounter >> $outfile");
	    system("cat ${job}.log | grep eventCounter_ >> $outfile");
	    $idx++;
	}
    }
}
