#ifndef userConfig_h
#define userConfig_h

/////////////////////////////////////////////////
//
// userConfig: main place for user input
// define all needed stuff here
//
/////////////////////////////////////////////////

#include "configInfo.h"

// flags for testing
bool verbose = false;
bool testPlotting = false;

// draw signal as overlaying curve (or stacked on top)
bool overlaySignal = true;

// set default legend position
bool defaultLegOnTop = true;

// create configInfo struct
double lumi = 19712.;

// inclusive selection, default
//TString infile = "/net/scratch_cms/institut_3b/kargoll/workdirInclusive3ProngAug_05_2016/LOCAL_COMBINED_inclusive_default_LumiScaled.root";
// inclusive selection, 3prong + flight length cut
//TString infile = "/net/scratch_cms/institut_3b/kargoll/workdirInclusive_3ProngOnlyAug_16_2016/Results_3Prong_FlightLength/LOCAL_COMBINED_inclusive_default_LumiScaled.root";
// inclusive selection, 3prong + flight length cut, only few plots, SVFit mass
TString infile = "/net/scratch_cms/institut_3b/kargoll/workdirInclusive_3ProngOnly_SVFitAug_24_2016/LOCAL_COMBINED_zerojet3prong_default_LumiScaled.root";
TString ident = "zerojet3prong_default_";

//TString ident = "inclusive_default_";

bool isLumiScaled = true; // specify if input root file is already scaled to lumi
// define user-specific config
configInfo conf(infile, isLumiScaled, ident, lumi);

#endif
