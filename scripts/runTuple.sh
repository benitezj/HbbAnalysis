
###Config
export TUPLECONFIG=data/HbbAnalysis/TupleMaker-job.cfg
export TUPLENFILES=1

###Input path
#export TUPLEINPATH=$OUTPUTDIRCLUSTER/CxAODSamples/$CXTAG
#export TUPLEINPATH=$OUTPUTDIRCLUSTER/CxAODSamples/00-00-06
#export TUPLEINPATH=$OUTPUTDIRCLUSTER/CxAODSamples/00-00-06_Test
#export TUPLEINPATH=$OUTPUTDIRCLUSTER/CxAODSamples/00-07-00_rho
#export TUPLEINPATH=$OUTPUTDIRCLUSTER/CxAODSamples/00-07-00_Test_JetCalibTools-00-04-30
#export TUPLEINPATH=$OUTPUTDIRCLUSTER/CxAODSamples/00-07-00_Test_JetCalibTools-00-04-30_rho
#export TUPLEINPATH=$OUTPUTDIRCLUSTER/CxAODSamples/00-07-00_Test_JetCalibTools-00-04-30_rho_passAny
#export TUPLEINPATH=$OUTPUTDIRCLUSTER/CxAODSamples/00-07-00_Test_JetCalibTools-00-04-30_rho_passAny_OR
export TUPLEINPATH=$OUTPUTDIRCLUSTER/CxAODSamples/00-07-00_Test_JetCalibTools-00-04-30_rho_passAny_ORnoPhoton

###Output path
#export outpath=$OUTPUTDIR/CxTupleSamples
export outpath=$OUTPUTDIRCLUSTER/CxTupleSamples

# export TUPLESAMPLENAME=data12_8TeV.00202660.physics_Muons.merge.AOD.r5724_p1751
# export TUPLESAMPLENAME=data12_8TeV.00202660.physics_Egamma.merge.AOD.r5723_p1751
# export TUPLESAMPLENAME=data12_8TeV.00202660.physics_Muons.merge.AOD.r5724_p1751
# export TUPLESAMPLENAME=data12_8TeV.00202660.physics_Egamma.merge.AOD.r5723_p1751

# export TUPLESAMPLENAME=mc14_8TeV.167754.Sherpa_CT10_ZmumuMassiveCBPt0_CVetoBVeto.merge.AOD.e1585_s1933_s1911_r5591_r5625
# export TUPLESAMPLENAME=mc14_8TeV.167753.Sherpa_CT10_ZmumuMassiveCBPt0_CFilterBVeto.merge.AOD.e1585_s1933_s1911_r5591_r5625
# export TUPLESAMPLENAME=mc14_8TeV.167753.Sherpa_CT10_ZmumuMassiveCBPt0_CFilterBVeto.merge.AOD.e1585_s1933_s1911_r5591_r5625

# export TUPLESAMPLENAME=mc14_8TeV.147806.PowhegPythia8_AU2CT10_Zee.merge.AOD.e1169_s1896_s1912_r5591_r5625
# export TUPLESAMPLENAME=mc14_8TeV.147807.PowhegPythia8_AU2CT10_Zmumu.merge.AOD.e1852_s1896_s1912_r5591_r5625 
# export TUPLESAMPLENAME=mc14_8TeV.189427.PowhegPythia8_AU2CT10_ZH125J_MINLO_mumubb_VpT_Weighted.merge.AOD.e2698_s1933_s1911_r5591_r5625
# export TUPLESAMPLENAME=mc14_8TeV.189426.PowhegPythia8_AU2CT10_ZH125J_MINLO_eebb_VpT_Weighted.merge.AOD.e2698_s1933_s1911_r5591_r5625
# export TUPLESAMPLENAME=mc14_8TeV.189421.PowhegPythia8_AU2CT10_WpH125J_MINLO_munubb_VpT_Weighted.merge.AOD.e2698_s1933_s1911_r5591_r5625

# export TUPLESAMPLENAME=mc14_13TeV.161827.Pythia8_AU2CTEQ6L1_ZH125_llbb.merge.AOD.e3292_s1982_s2008_r5787_r5853
# export TUPLESAMPLENAME=mc14_13TeV.203921.MadgraphPythia8_AU2MSTW2008LO_HVT_Zh_llbb_500GeV_126.merge.AOD.e3318_s1982_s2008_r5787_r5853
export TUPLESAMPLENAME=mc14_13TeV.203917.MadgraphPythia8_AU2MSTW2008LO_HVT_Zh_llbb_1000GeV_126.merge.AOD.e3318_s1982_s2008_r5787_r5853


###########################################3
####Make and plot a ntuple
############################################


runTupleMaker(){
 export TUPLEOUTPATH=$outpath/$TUPLECHANNEL/${CXTAG}_Test
 mkdir $TUPLEOUTPATH
 rm -rf $TUPLEOUTPATH/$TUPLESAMPLENAME
 cxtupleproducer local
}


 ##############BaseTupleMaker
 if [ "$1" == "base" ]; then
 export TUPLECHANNEL=base
 runTupleMaker
 fi

 if [ "$1" == "base_plot" ]; then
 export TUPLEOUTPATH=$outpath/base/$CXTAG
 root -b HbbAnalysis/macros/plotBaseCmdLine.C\(\"$TUPLEOUTPATH/$TUPLESAMPLENAME/data-output/tuple.root\"\)
 fi


 ##############RecoTupleMaker
 if [ "$1" == "reco" ] ; then
 export TUPLECHANNEL=reco
 runTupleMaker
 fi

 if [ "$1" == "reco_plot" ] ; then
 export TUPLEOUTPATH=$outpath/reco/$CXTAG
 root -b HbbAnalysis/macros/plotRecoCmdLine.C\(\"$TUPLEOUTPATH/$TUPLESAMPLENAME/data-output/tuple.root\"\)
 fi


 ############Z -> l l
 if [ "$1" == "Zmm" ] ||  [ "$1" == "all" ]; then
 export TUPLECHANNEL=Zmm
 runTupleMaker
 fi

 if [ "$1" == "Zee" ] ||  [ "$1" == "all" ]; then
 export TUPLECHANNEL=Zee
 runTupleMaker
 fi
 
 
 ############W->l nu
 if [ "$1" == "Wmunu" ] ||  [ "$1" == "all" ]; then
 export TUPLECHANNEL=Wmunu
 runTupleMaker
 fi
 
 if [ "$1" == "Wenu" ] ||  [ "$1" == "all" ]; then
 export TUPLECHANNEL=Wenu
 runTupleMaker
 fi


 #########VH anlysis
 if [ "$1" == "ZHmmbb" ] ||  [ "$1" == "all" ]; then
 export TUPLECHANNEL=ZHmmbb
 runTupleMaker
 fi

 if [ "$1" == "ZHeebb" ] ||  [ "$1" == "all" ]; then
 export TUPLECHANNEL=ZHeebb
 runTupleMaker
 fi

 if [ "$1" == "WHmnubb" ] ||  [ "$1" == "all" ]; then
 export TUPLECHANNEL=WHmnubb
 runTupleMaker
 fi

 if [ "$1" == "WHenubb" ] ||  [ "$1" == "all" ]; then
 export TUPLECHANNEL=WHenubb
 runTupleMaker
 fi
