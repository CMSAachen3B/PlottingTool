#ifndef defineSVFitMassComparison_h
#define defineSVFitMassComparison_h

/////////////////////////////////////////////////
//
// defineSVFitMassComparison.h:
// define samples and plot to compare SVFit shapes of Higgs and DY
//
/////////////////////////////////////////////////

#include "userConfig.h"
#include "sample.h"
#include "plotInfo.h"
#include "plottingHelpers.h"

// define samples to use
std::vector<sample> defineSVFitCompSamples(){
	sample s_ggHiggs	("H_{gg}"				, 632, "MC_ggFHTauTauM125");
	sample s_vbfHiggs	("H_{VBF}"				, 633, "MC_VBFHTauTauM125");
	sample s_ztt		("Z#rightarrow#tau#tau"	, col_htt_Ztt, "MC_DY_embedded"); //"MC_DY_tautau");

	// combine samples
	sample s_higgs(s_ggHiggs, "H#rightarrow#tau#tau", col_rwth_petrol);
	s_higgs += s_vbfHiggs;
	s_higgs.isSignal = true;

	s_ztt.isSignal = true;

	// define which samples to plot and in which order:
	// sample pushed back later will be drawn later, i.e. on top.
	// All signal samples MUST be added after all background samples! Add them last.
	std::vector<sample> samples;
	samples.push_back(s_ztt);
	samples.push_back(s_higgs);

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
std::vector<plotInfo> defineSVFitCompPlots(){
	std::vector<plotInfo> plots;


	plotInfo svfitComp("shape_SVfitM", "GeV", false, 4, 0., 190.);
	svfitComp.xAxisLabel = "m_{#tau#tau} / GeV";
	svfitComp.compareShapes = true;
	plots.push_back( svfitComp );

	plotInfo visMComp("shape_VisM", "GeV", false, 4, 0., 190.);
	visMComp.xAxisLabel = "m_{vis} / GeV";
	visMComp.compareShapes = true;
	plots.push_back( visMComp );

	return plots;
}


#endif
