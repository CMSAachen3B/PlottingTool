/////////////////////////////////////////////////
//
// runShapeComparison.cc: main macro to run in ROOT
// call like "root runShapeComparison.cc+" in your shell
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
#include "defineSVFitMassComparison.h"
#include "plottingHelpers.h"

void runShapeComparison(){
	if(verbose) std::cout << "--> plotting()" << std::endl;
	gROOT->LoadMacro("tdrstyle.C");
	setTDRStyle();
	gROOT->LoadMacro("CMS_lumi.C");
	cmsText = "";
	writeExtraText = false;
	gStyle->SetOptStat(0);
	TGaxis::SetMaxDigits(3);

	// define which samples to use
	std::vector<sample> samples = defineSVFitCompSamples();

	// define which plots to draw
	std::vector<plotInfo> plots = defineSVFitCompPlots();

	// test validity of structs
	testInputs(conf, samples, plots);
	
	// dummy datahists
	TH1D* datahist = 0;

	// create plots

	for(unsigned p = 0; p < plots.size(); p++){
		drawPlot(conf, plots.at(p), datahist, samples);
	}

	std::cout << "Plots created." << std::endl;

	convertAllEpsToPdf();
}

