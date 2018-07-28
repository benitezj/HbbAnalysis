export tag=00-00-04

##setup ATLAS environment
setupATLAS
 
# make release directory
mkdir $tag
cd $tag/
 
# checkout setup.sh
svn co svn+ssh://svn.cern.ch/reps/atlasphys/Physics/Higgs/HSG5/software/VHAnalysis/LHCRun2/CxAODFramework/FrameworkSub/tags/FrameworkSub-${tag} FrameworkSub

# setup RootCore and checkout packages
source FrameworkSub/bootstrap/setup.sh

# checkout my packages
svn co svn+ssh://svn.cern.ch/reps/atlas-benitezj/HbbAnalysis/trunk HbbAnalysis

##compile
rc build

