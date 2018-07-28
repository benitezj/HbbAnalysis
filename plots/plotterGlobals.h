#include <TString.h>
#include <TFile.h>
#include <TH1F.h>
#include <TDirectory.h>
#include <TString.h>
#include "Sample.h"

//TString inputDir_=getenv("OUTPUTDIR");
TString inputDir_ ="./NTUPLES";
TString outputDir_=getenv("WWWDIR");
TString CXTAG=getenv("CXTAG");//Version of the CxAOD's

TString lumisfile="HbbAnalysis/data/lumis.txt";
TString crossectionsfile="HbbAnalysis/data/crossections_8TeV.txt";

char atlasInternal8TeV[100]="ATLAS Internal,  #sqrt{s} = 8 TeV,  %.1f fb^{-1}";

Float_t c1[4]={.65,.5,.9,.87};//X1,Y1,X2,Y2 : x1,y1 is bottom left , x2,y2 is top right
Float_t c2[4]={.65,.5,.9,.87};
Float_t c3[4]={.65,.5,.9,.87};
Float_t c4[4]={.65,.5,.9,.87};

TString titleZmm="Z#rightarrow#mu^{+}#mu^{-}";
TString titleZee="Z#rightarrowe^{+}e^{-}";
TString titleWmunu="W#rightarrow#mu#nu";
TString titleWenu="W#rightarrowe#nu";
TString titleTTbar="t#bar{t}";

int colorZmm=kAzure;
int colorZee=kAzure;
int colorWmunu=kGreen;
int colorWenu=kGreen;
int colorTTbar=kOrange;

int colorZ=kAzure;
int colorW=kGreen;

int colorZl=kAzure - 9;
int colorZc=kAzure - 4;
int colorZb=kAzure + 2;

int colorWl=kGreen - 9;
int colorWc=kGreen - 6;
int colorWb=kGreen + 3;

int colorQCD=kPink + 1;

TString titleZl="Z+l";
TString titleZc="Z+c";
TString titleZb="Z+b";

TString titleWl="W+l";
TString titleWc="W+c";
TString titleWb="W+b";


// ///Official Hbb colors
//     Zbb: kAzure + 2
//     Zbl: kAzure + 1
//     Zcc: kAzure - 4
//     Zcl: kAzure - 8
//     Zl: kAzure - 9 

//     Wbb: kGreen + 3
//     Wbl: kGreen + 2
//     Wcc: kGreen + 1
//     Wcl: kGreen - 6
//     Wl: kGreen - 9 

//     ttbar: kOrange
//     Wt: kYellow -7
//     s-chan: kOrange-1
//     t-chan: kOrange-3 

//     WW: kGray+3
//     ZZ: kGray+1
//     WZ: kGray 

//     signal: kRed+1 

//     multijet: kPink + 1 

// If we combine things, then it is as follows:

//     Zb: kAzure + 2
//     Zc: kAzure - 4
//     Zl: kAzure - 9 

//     Wb: kGreen + 3
//     Wcc: kGreen + 1
//     Wc: kGreen - 6
//     Wl: kGreen - 9 
