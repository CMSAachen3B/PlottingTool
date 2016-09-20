#ifndef define3ProngResolutionComparison_h
#define define3ProngResolutionComparison_h

/////////////////////////////////////////////////
//
// define3ProngResolutionComparison.h:
// define sample and plots to compare
//   different histograms from the same sample
//
/////////////////////////////////////////////////

#include "userConfig.h"
#include "sample.h"
#include "plotInfo.h"
#include "plottingHelpers.h"

// define samples to use
sample defineSample(){
	sample s_ztt		("Z#rightarrow#tau#tau"	, col_htt_Ztt, "MC_DY_embedded"); //"MC_DY_tautau");

	return s_ztt;
}


// define which plots to draw
// look at plotInfo.h to see which constructors exist
std::vector< std::vector<plotInfo> > defineComparisonPlots(){
	std::vector< std::vector<plotInfo> > vplots;
	std::vector<plotInfo> dummy;

	int rebin = 5;

	// relative energy resolution
	vplots.push_back(dummy);

	plotInfo trueEResol("Tau3p_True_E_Resol", "", false, rebin);
	trueEResol.xAxisLabel = "[E(#tau_{3#pi}) - E(#tau_{gen})] / E(#tau_{gen})";
	vplots.back().push_back( trueEResol );

	plotInfo plusEResol("Tau3p_Plus_E_Resol", "", false, rebin);
	vplots.back().push_back( plusEResol );

	plotInfo zeroEResol("Tau3p_Zero_E_Resol", "", false, rebin);
	vplots.back().push_back( zeroEResol );

	plotInfo minusEResol("Tau3p_Minus_E_Resol", "", false, rebin);
	vplots.back().push_back( minusEResol );

	// absolute energy resolution
	vplots.push_back(dummy);

	plotInfo trueEAbsResol("Tau3p_True_E_AbsResol", "", false, rebin, -50., 95.);
	trueEAbsResol.xAxisLabel = "[E(#tau_{3#pi}) - E(#tau_{gen})] / GeV";
	vplots.back().push_back( trueEAbsResol );

	plotInfo plusEAbsResol("Tau3p_Plus_E_AbsResol", "", false, rebin);
	vplots.back().push_back( plusEAbsResol );

	plotInfo zeroEAbsResol("Tau3p_Zero_E_AbsResol", "", false, rebin);
	vplots.back().push_back( zeroEAbsResol );

	plotInfo minusEAbsResol("Tau3p_Minus_E_AbsResol", "", false, rebin);
	vplots.back().push_back( minusEAbsResol );

	return vplots;
}


#endif
