##setup ATLAS environment
setupATLAS
 
# make release directory
mkdir 00-00-03
cd 00-00-03/
 
# checkout setup.sh
svn co svn+ssh://svn.cern.ch/reps/atlasphys/Physics/Higgs/HSG5/software/VHAnalysis/LHCRun2/CxAODFramework/FrameworkSub/tags/FrameworkSub-00-00-03 FrameworkSub

# setup RootCore and checkout packages
source FrameworkSub/bootstrap/setup.sh

##compile
rc build

