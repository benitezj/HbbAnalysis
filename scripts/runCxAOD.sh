# export XAODCONFIG=data/HbbAnalysis/framework-run.cfg
 export XAODCONFIG=data/HbbAnalysis/framework-run_test.cfg
 export XAODNFILES=1
 export XAODNEVENTS=1000

 #####Define input
 #export XAODSAMPLEPATH=/afs/cern.ch/atlas/project/PAT/xAODs/r5591
 #export XAODSAMPLENAME=mc14_8TeV.147807.PowhegPythia8_AU2CT10_Zmumu.merge.AOD.e1852_s1896_s1912_r5591_r5625_tid01512432_00

 #export XAODSAMPLEPATH=/afs/cern.ch/atlas/project/PAT/xAODs/r5787
 #export XAODSAMPLENAME=mc14_13TeV.110401.PowhegPythia_P2012_ttbar_nonallhad.merge.AOD.e2928_s1982_s2008_r5787_r5853_tid01597980_00

 export XAODSAMPLEPATH=$OUTPUTDIRCLUSTER/xAODSamples
 #export XAODSAMPLENAME=mc14_13TeV.203917.MadgraphPythia8_AU2MSTW2008LO_HVT_Zh_llbb_1000GeV_126.merge.AOD.e3318_s1982_s2008_r5787_r5853
 export XAODSAMPLENAME=mc14_13TeV.161827.Pythia8_AU2CTEQ6L1_ZH125_llbb.merge.AOD.e3292_s1982_s2008_r5787_r5853_Test

 #####OUTPUT path
 export XAODOUTPATH=$OUTPUTDIRCLUSTER/CxAODSamples/${CXTAG}_Test

 rm -rf ${XAODOUTPATH}/${XAODSAMPLENAME}
 cxaodproducer local
 mv $XAODOUTPATH/$XAODSAMPLENAME/data-outputLabel/outputLabel.root  $XAODOUTPATH/$XAODSAMPLENAME/outputLabel_0.root
 ls -l $XAODOUTPATH/$XAODSAMPLENAME/outputLabel_0.root
