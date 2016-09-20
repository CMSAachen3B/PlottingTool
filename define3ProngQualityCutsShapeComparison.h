#ifndef define3ProngQualityCutsShapeComparison_h
#define define3ProngQualityCutsShapeComparison_h

/////////////////////////////////////////////////
//
// define3ProngQualityCutsShapeComparison.h:
// define samples and plot to compare 3-prong quality cuts
//   between different signals and backgrounds
//
/////////////////////////////////////////////////

#include "userConfig.h"
#include "sample.h"
#include "plotInfo.h"
#include "plottingHelpers.h"

// define samples to use
std::vector<sample> defineCompSamples(){
	sample s_ggHiggs	("H_{gg}"				, 632, "MC_ggFHTauTauM125");
	sample s_vbfHiggs	("H_{VBF}"				, 633, "MC_VBFHTauTauM125");
	sample s_ztt		("Z#rightarrow#tau#tau"	, col_htt_Ztt, "MC_DY_embedded"); //"MC_DY_tautau");
	sample s_qcd		("QCD"					, col_rwth_violett, "QCD");
	//sample s_Wlnu		("W#rightarrowl#nu"		, 876, "MC_W_lnu");

	// combine samples
	sample s_higgs(s_ggHiggs, "H#rightarrow#tau#tau", col_rwth_petrol);
	s_higgs += s_vbfHiggs;

	//sample s_fake(s_qcd, "fake #tau", col_rwth_violett);
	//s_fake += s_Wlnu;


	// define which samples to plot and in which order:
	// sample pushed back later will be drawn later, i.e. on top.
	// All signal samples MUST be added after all background samples! Add them last.
	std::vector<sample> samples;
	//samples.push_back(s_ztt);
	//samples.push_back(s_higgs);
	//samples.push_back(s_qcd);
	//samples.push_back(s_Wlnu);
	//samples.push_back(s_Wtaunu);
	samples.push_back(s_ztt);
	samples.push_back(s_higgs);
	samples.push_back(s_qcd);

	// all samples have to be defined as signal for shape comparison
	for (unsigned s = 0; s < samples.size(); s++) samples.at(s).isSignal = true;

	if (verbose){
		std::cout << "###>-- The following samples will be plotted:" << std::endl;
		for(unsigned i = 0; i<samples.size(); i++){
			printSample(samples.at(i), conf);
		}
	}

	return samples;
}


// define which plots to draw
// look at plotInfo.h to see which constructors exist
std::vector<plotInfo> defineCompPlots(){
	std::vector<plotInfo> plots;


	plotInfo flightLengthSig("Tau3p_FlightLengthSignificance", "", false, 2, -11., 29.);
	flightLengthSig.xAxisLabel = "f / #sigma_{f}";
	flightLengthSig.compareShapes = true;
	plots.push_back( flightLengthSig );

	plotInfo rotationSig("Tau3p_Zero_RotSignificance", "", false, 4, 0, 9);
	rotationSig.xAxisLabel = "r / #sigma_{r}";
	rotationSig.compareShapes = true;
	plots.push_back( rotationSig );

	return plots;
}


#endif
