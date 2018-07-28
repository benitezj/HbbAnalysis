#!/usr/bin/perl
# -w
use File::Basename;
$eos="/afs/cern.ch/project/eos/installation/0.3.15/bin/eos.select";

$samplesfile=shift;#must be a full path in AFS
$option=shift;

##necesary environment variables
$CXTAG=`echo \$\{PWD\#\#\*/\}`; # $ENV{'CXTAG'};  ### $CXTAG is not set on a fresh term
chomp($CXTAG);
$OUTPUTDIR=$ENV{'OUTPUTDIR'};
$EOSDIR=$ENV{'EOSDIR'};

##where the tuples will be written
$outpath=dirname($samplesfile);

#read the samples list
@samples=`cat $samplesfile | grep -v "#"`;
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

    ###Determine the input path based on storage
    if($storage eq "afs"){ $inpath="$OUTPUTDIR/CxAODSamples/$CXTAG"; }
    if($storage eq "eos"){ $inpath="$EOSDIR/CxAODSamples/$CXTAG"; }

    
    foreach $samp (@samples){
	chomp($samp);
	$samp =~ s/^\s+|\s+$//g; ##remove beg/end spaces

	system("mkdir ${outpath}/${samp}");

	##get list of files in storage
	if($storage eq "afs"){ @dirlist=`/bin/ls $inpath/$samp | grep .root` }
	if($storage eq "eos"){ @dirlist=`$eos ls $inpath/$samp | grep .root` }


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
		$command="./HbbAnalysis/scripts/makeBsubJob.pl ${storage} ${samp} ${outpath} ${algo} ${idx} '${filelist}'";	
		#print "$command\n";
		system("$command");
		$filelist="";
		$mergecounter=0;
		$idx++;
	    }
	}
	if($mergecounter>0){
	    $command="./HbbAnalysis/scripts/makeBsubJob.pl ${storage} ${samp} ${outpath} ${algo} ${idx} '${filelist}'";	
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
    $qu= $_[2];

    if($qu ne "1nh" && $qu ne "8nh" && $qu ne "1nd" && $qu ne "2nd"){ 
	$qu="8nh";
    }
    
    system("rm -f ${path}/tuple_${idx}.root");
    system("rm -f ${path}/tuple_${idx}.log");
    $command="bsub -C 0 -R \"pool>10000\" -q ${qu} -J ${idx} -o ${path}/tuple_${idx}.log < ${path}/tuple_${idx}.sh";	
    print "$command\n";
    system("$command");
}

    
#submit all jobs
if($option eq "sub" ){
    $qu=shift;

    foreach $samp (@samples){
	chomp($samp);
	$samp =~ s/^\s+|\s+$//g; ##remove beg/end spaces

	$idx=0;	
	for $f (`/bin/ls $outpath/$samp | grep tuple_ | grep .sh`){
	    chomp($f);
	    submit("${outpath}/${samp}",$idx,$qu);
	    $idx++;
	}
	
	print "\n Submitted $idx jobs for ${outpath}/${samp}\n";
    }

}


if($option eq "check"){
    $qu=shift;

    foreach $samp (@samples){
	chomp($samp);
	$samp =~ s/^\s+|\s+$//g; ##remove beg/end spaces

	$idx=0;	
	$failcounter=0;
	for $f (`/bin/ls $outpath/$samp | grep tuple_ | grep .sh | grep -v "~" `){
	    chomp($f);
	    $job="${outpath}/${samp}/tuple_${idx}";

	    $failed=0;

	    #check a log file was produced
	    if(!(-e "${job}.log")){ 
		print "No log file \n ${job}\n"; 
		$failed = 1; 
	    }

	    # there were input events: inputCounter = 100000
	    if( $failed == 0){ 
		$inputEvents=`cat  ${job}.log | grep inputCounter`;
		chomp($inputEvents);
		@evtsproc=split(" ",$inputEvents);
		if( !($evtsproc[2] > 0)){
		    print "No input events \n ${job}\n"; 
		    $failed = 1;
		}
	    }
	
	    # check Successfully completed.
	    if( $failed == 0){
		$success = `cat ${job}.log | grep "Successfully completed."`;
		if($success eq "" ){
		    print "Not successfully completed \n ${job}\n";
		    $failed = 1;
		}
	    } 

	
	    #check the root file exists 
	    if($failed == 0){
		if(!(-e "${job}.root")){
		    print "No root file \n ${job}\n";
		    $failed = 1; 
		}
	    }
	    
	    ###Resubmit
	    if($failed == 1){
		$failcounter++;		
		if($qu ne ""){
		    ##if queue is provided then resubmit
		    submit("${outpath}/${samp}",$idx,$qu);
		    print "Job $idx resubmitted.\n";
		}
	    }
	    
	    $idx++;
	}
	print "Failed $failcounter / $idx : ${samp} \n";
    }
}


