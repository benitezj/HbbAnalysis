export tag=00-00-06

##setup ATLAS environment
source $ATLAS_LOCAL_ROOT_BASE/user/atlasLocalSetup.sh
 
# checkout setup.sh
svn co svn+ssh://svn.cern.ch/reps/atlasphys/Physics/Higgs/HSG5/software/VHAnalysis/LHCRun2/CxAODFramework/FrameworkSub/tags/FrameworkSub-${tag} FrameworkSub

# setup RootCore and checkout packages
source FrameworkSub/bootstrap/setup.sh

##compile
rc build

