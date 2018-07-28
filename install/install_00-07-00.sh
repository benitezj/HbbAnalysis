export tag=${PWD##*/}
echo "Installing CxAODFramework $tag\n"

# setup ATLAS environment
source $ATLAS_LOCAL_ROOT_BASE/user/atlasLocalSetup.sh
 
# checkout setup.sh
svn co svn+ssh://svn.cern.ch/reps/atlasoff/PhysicsAnalysis/HiggsPhys/Run2/Hbb/CxAODFramework/FrameworkSub/tags/FrameworkSub-${tag} FrameworkSub

# setup RootCore and checkout packages
source FrameworkSub/bootstrap/setup-tag.sh


###For rho computation
#already in release AnalysisBase/2.0.27
#xAODEventShape-00-00-04
#EventShapeInterface-00-00-08
rc checkout_pkg atlasoff/Reconstruction/EventShapes/EventShapeTools/tags/EventShapeTools-00-01-09

# compile
rc build

