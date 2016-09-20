/////////////////////////////////////////////////
//
// runComparisonBetweenPlots.cc: main macro to run in ROOT
// call like "root runComparisonBetweenPlots.cc+" in your shell
//
/////////////////////////////////////////////////

#include "TROOT.h"
#include "TFile.h"
#include "TCanvas.h"
#include "TH1D.h"
#include "TLegend.h"
#include "TColor.h"
#include "TGaxis.h"

#include <vector>

#include "tdrstyle.C"
#include "CMS_lumi.C"

#include "userConfig.h"
#include "define3ProngResolutionComparison.h"
#include "plottingHelpers.h"

void runComparisonBetweenPlots(){
	if(verbose) std::cout << "--> plotting()" << std::endl;
	gROOT->LoadMacro("tdrstyle.C");
	setTDRStyle();
	gROOT->LoadMacro("CMS_lumi.C");
	cmsText = "";
	writeExtraText = false;
	gStyle->SetOptStat(0);
	TGaxis::SetMaxDigits(3);

	// define which samples to use
	sample sam = defineSample();

	// define which plots to draw
	std::vector< std::vector<plotInfo> > plots = defineComparisonPlots();

	// test validity of structs
	std::vector<sample> samInVector;
	samInVector.push_back(sam);
	for (unsigned p = 0; p< plots.size(); p++)
		testInputs(conf, samInVector, plots.at(p));
	
	// create plots
	for(unsigned p = 0; p < plots.size(); p++){
		drawPlotComparison(conf, plots.at(p), sam);
	}

	std::cout << "Plots created." << std::endl;

	convertAllEpsToPdf();
}

