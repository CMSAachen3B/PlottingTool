#ifndef defineSamplesAndPlots_h
#define defineSamplesAndPlots_h

/////////////////////////////////////////////////
//
// defineSamplesAndPlots:
// declare which plots you want to draw using which samples
// this cannot go into userConfig.h, as it would cause circular dependencies
//
/////////////////////////////////////////////////

#include "userConfig.h"
#include "sample.h"
#include "plotInfo.h"
#include "plottingHelpers.h"

// define samples to use
std::vector<sample> defineSamples(){
	sample s_ggHiggs	("H_{gg}"				, 632, "MC_ggFHTauTauM125");
	sample s_vbfHiggs	("H_{VBF}"				, 633, "MC_VBFHTauTauM125");
	sample s_apHiggs	("H_{AP}"				, 634, "MC_WHZHTTHTauTauM125");
	sample s_qcd		("QCD"					, col_htt_qcd, "QCD");
	sample s_ztt		("Z#rightarrow#tau#tau"	, col_htt_Ztt, "MC_DY_embedded"); //"MC_DY_tautau");
	sample s_zll		("Z#rightarrowll"		, col_rwth_lightblue, "MC_DY_ll");
	sample s_ww			("WW"					, 417, "MC_WW_2l2nu");
	sample s_wz2l2q		("WZ#rightarrowllqq"	, 418, "MC_WZ_2l2q");
	sample s_wz3l1nu	("WZ#rightarrowlll#nu"	, 419, "MC_WZ_3l1nu");
	sample s_zz4l		("ZZ#rightarrowllll"	, 420, "MC_ZZ_4l");
	sample s_zz2l2nu	("ZZ#rightarrowll#nu#nu", 416, "MC_ZZ_2l2nu");
	sample s_zz2l2q		("ZZ#rightarrowllqq"	, 415, "MC_ZZ_2l2q");
	sample s_ttbar		("t#bar{t}"				, 600, "MC_ttbar");
	sample s_tw			("tW"					, 603, "MC_tw");
	sample s_tbarW		("#bar{t}W"				, 591, "MC_tbarw");
	sample s_Wlnu		("W#rightarrowl#nu"		, 876, "MC_W_lnu");
	sample s_Wtaunu		("W#rightarrow#tau#nu"	, 874, "MC_W_taunu");

	// *** examples for sample creation when scaling manually ***
	// std::map<int, int> MnEvents = readSkimSummary("mySkimSummary.log");
	// sample s_ggHiggs(11,"H_{gg}", 1.233664, lumi, 632, "MC_ggFHTauTauM125", MnEvents );
	// sample s_vbfHigg(12,"H_{VBF}", 0.0997296, lumi, 633, "MC_VBFHTauTauM125", MnEvents );
	// sample s_apHiggs(13,"H_{AP}", 0.0771792, lumi, 634, "MC_WHZHTTHTauTauM125", MnEvents );


	// combine samples as is done in Higgs analysis
	sample s_higgs(s_ggHiggs, "H", col_rwth_petrol);
	s_higgs += s_vbfHiggs;
	//s_higgs += s_apHiggs;
	s_higgs.isSignal = true;
	sample s_vv(s_ww, "VV", col_htt_W);
	s_vv += s_wz2l2q;
	s_vv += s_wz3l1nu;
	s_vv += s_zz4l;
	s_vv += s_zz2l2nu;
	s_vv += s_zz2l2q;
	sample s_W(s_Wlnu, "W", col_htt_W);
	s_W += s_Wtaunu;
	sample s_top(s_ttbar, "top", col_htt_tt);
	s_top += s_tw;
	s_top += s_tbarW;

	// add systematic uncertainties
	// systematics of signal samples are omitted
	// channel dependent systematics are omitted, unless identical for most categories
	double sys_muEff = 0.02;
	addSyst(s_ztt,	sys_muEff);
	addSyst(s_zll,	sys_muEff);
	addSyst(s_top,	sys_muEff);
	addSyst(s_vv,	sys_muEff);
	double sys_tauEff = 0.08;
	addSyst(s_ztt,	sys_tauEff);
	addSyst(s_top,	sys_tauEff);
	addSyst(s_vv,	sys_tauEff);
	double sys_zttNorm = 0.03;
	addSyst(s_ztt,	sys_zttNorm);
	addSyst(s_zll,	sys_zttNorm);
	double sys_extrap_ztt = 0.05; // channel dependent
	addSyst(s_ztt,	sys_extrap_ztt);
	double sys_ttbarNorm = 0.1; // channel dependent
	addSyst(s_top,	sys_ttbarNorm);
	double sys_WNorm = 0.2; // channel dependent
	addSyst(s_W,	sys_WNorm);
	double sys_DiBosonNorm = 0.15; // channel dependent
	addSyst(s_vv,	sys_DiBosonNorm);
	double sys_QCDSyst = 0.06; // channel dependent
	addSyst(s_qcd,	sys_QCDSyst);

	// lumi uncertainty is neglected in datacards
	// plot here anyway, might be important in sidebands
	double sys_lumi = 0.026;
	addSyst(s_vv,	sys_lumi);
	addSyst(s_top,	sys_lumi);

	// combine samples further for plotting
	sample s_dy(s_ztt, "DY", col_htt_Ztt);
	s_dy += s_zll;
	sample s_ewk(s_vv, "electroweak", col_htt_W);
	s_ewk += s_W;

	// define which samples to plot and in which order:
	// sample pushed back later will be drawn later, i.e. on top.
	// All signal samples MUST be added after all background samples! Add them last.
	std::vector<sample> samples;
	samples.push_back(s_qcd);
	samples.push_back(s_top);
	samples.push_back(s_ewk);
	samples.push_back(s_dy);
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

std::vector<plotInfo> definePlots(){
	std::vector<plotInfo> plots;

	// plots using full inclusive selection
	if (infile == "/net/scratch_cms/institut_3b/kargoll/workdirInclusive3ProngAug_05_2016/LOCAL_COMBINED_inclusive_default_LumiScaled.root"){
		int sigScale = 50;
		int logSigScale = 50;

		plotInfo mt("Cut_10_Nminus1_MT_", "GeV", false, 2, 0., 140.);
		mt.scaleSignal = 100;
		plots.push_back( mt );

		plotInfo tauSelPt("TauSelPt", "GeV", true, 2, 20, 100);
		tauSelPt.xAxisLabel = "p_{T}(#tau_{h})/GeV";
		tauSelPt.scaleSignal = logSigScale;
		plots.push_back( tauSelPt );

		plotInfo tauSelEta("TauSelEta", "", false, 2, -2.3, 2.3);
		tauSelEta.xAxisLabel = "#eta(#tau_{h})";
		tauSelEta.scaleSignal = sigScale;
		plots.push_back( tauSelEta );

		plotInfo muSelPt("MuSelPt", "GeV", true, 2, 20, 100);
		muSelPt.yRangeHigh = 2e6;
		muSelPt.yRangeLow = 5;
		muSelPt.xAxisLabel = "p_{T}(#mu)/GeV";
		muSelPt.scaleSignal = logSigScale;
		plots.push_back( muSelPt );

		plotInfo muSelEta("MuSelEta", "", false, 2, -2.1, 2.1);
		muSelEta.legOnTop = true;
		muSelEta.xAxisLabel = "#eta(#mu)";
		muSelEta.scaleSignal = 10;
		muSelEta.scaleSignal = sigScale;
		plots.push_back( muSelEta );

		plotInfo metPt("MetPt", "GeV", true, 2);
		metPt.scaleSignal = logSigScale;
		plots.push_back( metPt );

		plotInfo metPhi("MetPhi", "GeV", false, 2);
		metPhi.scaleSignal = sigScale;
		plots.push_back( metPhi );

		plotInfo visibleMass("visibleMass", "GeV", false, 2, 0., 140.);
		visibleMass.scaleSignal = sigScale;
		plots.push_back( visibleMass );

		plotInfo nJetsId("NJetsId", "", true, 1, -0.5, 7.5);
		nJetsId.scaleSignal = logSigScale;
		plots.push_back( nJetsId );

		plotInfo jetsDEta("JetsDEta", "", false, 4, -8.0, 8.0);
		jetsDEta.xAxisLabel = "#Delta#eta_{jj}";
		jetsDEta.scaleSignal = sigScale;
		plots.push_back( jetsDEta );

		plotInfo jetsInvM("JetsInvM", "GeV", true, 2, 0, 1400);
		jetsInvM.xAxisLabel = "m_{jj}/GeV";
		jetsInvM.scaleSignal = logSigScale;
		plots.push_back( jetsInvM );

		plotInfo higgsPt("HiggsPt", "GeV", true, 2);
		higgsPt.xAxisLabel = "p_{T}^{#tau#tau}/GeV";
		higgsPt.scaleSignal = logSigScale;
		plots.push_back( higgsPt );

		plotInfo flightLengthSig("Tau3p_FlightLengthSignificance", "", true, 1, -11, 23);
		flightLengthSig.xAxisLabel = "f / #sigma_{f}";
		flightLengthSig.scaleSignal = 100;
		flightLengthSig.drawSOverSB = true;
		plots.push_back( flightLengthSig );
	}
	// plots using 3prong only + flight length cut; inclusive selection
	else if(infile == "/net/scratch_cms/institut_3b/kargoll/workdirInclusive_3ProngOnlyAug_16_2016/Results_3Prong_FlightLength/LOCAL_COMBINED_inclusive_default_LumiScaled.root"){

		plotInfo rotationSig("Tau3p_Zero_RotSignificance", "", true, 4);//, 0., 6.);
		rotationSig.xAxisLabel = "r / #sigma_{r}";
		rotationSig.scaleSignal = 50;
		plots.push_back( rotationSig );

		plotInfo tau3PMinusE("Tau3p_Minus_E", "GeV", false, 2);
		tau3PMinusE.xAxisLabel = "E(#tau_{-})/GeV";
		tau3PMinusE.hideSignal = true;
		plots.push_back(tau3PMinusE);

		plotInfo tau3PPlusE("Tau3p_Plus_E", "GeV", false, 2);
		tau3PPlusE.xAxisLabel = "E(#tau_{+})/GeV";
		tau3PPlusE.hideSignal = true;
		plots.push_back(tau3PPlusE);

		plotInfo tau3PMinusEta("Tau3p_Minus_Eta", "", false, 2, -2.3, 2.3);
		tau3PMinusEta.xAxisLabel = "#eta(#tau_{+/-})";
		tau3PMinusEta.hideSignal = true;
		plots.push_back(tau3PMinusEta);

		plotInfo tau3PMinusPhi("Tau3p_Minus_Phi", "", false, 2);
		tau3PMinusPhi.xAxisLabel = "#varphi(#tau_{+/-})";
		tau3PMinusPhi.hideSignal = true;
		plots.push_back(tau3PMinusPhi);

		plotInfo tau3PZeroE("Tau3p_Zero_E", "GeV", false, 2);
		tau3PZeroE.xAxisLabel = "E(#tau_{0})/GeV";
		tau3PZeroE.hideSignal = true;
		plots.push_back(tau3PZeroE);

		plotInfo tau3PZeroEta("Tau3p_Zero_Eta", "", false, 2, -2.3, 2.3);
		tau3PZeroEta.xAxisLabel = "#eta(#tau_{0})";
		tau3PZeroEta.hideSignal = true;
		plots.push_back(tau3PZeroEta);

		plotInfo tau3PZeroPhi("Tau3p_Zero_Phi", "", false, 2);
		tau3PZeroPhi.xAxisLabel = "#varphi(#tau_{0})";
		tau3PZeroPhi.hideSignal = true;
		plots.push_back(tau3PZeroPhi);
	}
	// 3prong svfit mass plots
	else if(infile == "/net/scratch_cms/institut_3b/kargoll/workdirInclusive_3ProngOnly_SVFitAug_24_2016/LOCAL_COMBINED_zerojet3prong_default_LumiScaled.root"){

		plotInfo svFit3pMinus("svFit3pMass_MinusSol", "GeV", false, 4, 0., 350.);
		svFit3pMinus.xAxisLabel = "m_{#tau#tau}^{3#pi}/GeV";
		svFit3pMinus.scaleSignal = 100;
		plots.push_back(svFit3pMinus);

		plotInfo svFit3pPlus("svFit3pMass_PlusSol", "GeV", false, 4, 0., 350.);
		svFit3pPlus.xAxisLabel = "m_{#tau#tau}^{3#pi}/GeV";
		svFit3pPlus.scaleSignal = 100;
		plots.push_back(svFit3pPlus);

		plotInfo svFit3pZero("svFit3pMass_ZeroSol", "GeV", false, 4, 0., 350.);
		svFit3pZero.xAxisLabel = "m_{#tau#tau}^{3#pi}/GeV";
		svFit3pZero.scaleSignal = 100;
		plots.push_back(svFit3pZero);
	}
	return plots;
}

#endif
