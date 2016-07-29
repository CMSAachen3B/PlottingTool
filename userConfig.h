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

// create configInfo struct
double lumi = 19712.;
TString infile = "/net/scratch_cms/institut_3b/kargoll/workdirInclusiveSelectionJul_28_2016/LOCAL_COMBINED_inclusive_default_LumiScaled.root";
TString ident = "inclusive_default_";
bool isLumiScaled = true; // specify if input root file is already scaled to lumi
// define user-specific config
configInfo conf(infile, isLumiScaled, ident, lumi);

#endif
