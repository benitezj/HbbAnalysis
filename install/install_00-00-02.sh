 ##setup ATLAS environment
 setupATLAS
 
 # make some working direcory
 mkdir 00-00-02
 cd 00-00-02/
 
 # setup RootCore
 rcSetup Base,2.0.18
 
 # check out CxAODFramework
 svn co svn+ssh://svn.cern.ch/reps/atlasphys/Physics/Higgs/HSG5/software/VHAnalysis/LHCRun2/CxAODFramework/CxAODMaker/tags/CxAODMaker-00-00-02 CxAODMaker
 svn co svn+ssh://svn.cern.ch/reps/atlasphys/Physics/Higgs/HSG5/software/VHAnalysis/LHCRun2/CxAODFramework/CxAODTools/tags/CxAODTools-00-00-02 CxAODTools
 svn co svn+ssh://svn.cern.ch/reps/atlasphys/Physics/Higgs/HSG5/software/VHAnalysis/LHCRun2/CxAODFramework/CxAODReader/tags/CxAODReader-00-00-02 CxAODReader
 svn co svn+ssh://svn.cern.ch/reps/atlasphys/Physics/Higgs/HSG5/software/VHAnalysis/LHCRun2/CxAODFramework/FrameworkExe/tags/FrameworkExe-00-00-02 FrameworkExe
 svn co svn+ssh://svn.cern.ch/reps/atlasphys/Physics/Higgs/HSG5/software/VHAnalysis/LHCRun2/CxAODFramework/TupleMaker/tags/TupleMaker-00-00-02 TupleMaker
 svn co svn+ssh://svn.cern.ch/reps/atlasphys/Physics/Higgs/HSG5/software/VHAnalysis/LHCRun2/CxAODFramework/TupleReader/tags/TupleReader-00-00-02 TupleReader
 svn co svn+ssh://svn.cern.ch/reps/atlasphys/Physics/Higgs/HSG5/software/VHAnalysis/LHCRun2/CxAODFramework/FrameworkSub/trunk FrameworkSub
 svn co svn+ssh://svn.cern.ch/reps/atlasoff/PhysicsAnalysis/MuonID/MuonIDAnalysis/MuonMomentumCorrections/tags/MuonMomentumCorrections-01-00-13 MuonMomentumCorrections

##compile
rc find_packages
rc compile

