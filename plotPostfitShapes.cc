/////////////////////////////////////////////////
//
// plotPostfitShapes.cc: macro to draw postfit mtautau distributions
//
/////////////////////////////////////////////////

#include "TROOT.h"
#include "TFile.h"
#include "TCanvas.h"
#include "TH1D.h"
#include "TLegend.h"
#include "TColor.h"
#include "TString.h"

#include <vector>
#include <map>

#include "tdrstyle.C"
#include "CMS_lumi.C"

#include "postfitShapeHelpers.h"

int errorBandFillStyle = 3013;
int errorBandColor = kGray + 2;

TString folder = "htt_mt_<bin>_8TeV_postfit/";

void plotPostfitShapes(TString inputFile = "") {
	// set input root file
	if (inputFile == "")
		inputFile = "/home/home2/institut_3b/kargoll/TauAnalysis/LimitSetting/CMSSW_7_1_5/src/CombineHarvester/CombineTools/bin/output/aachen_cards/mt/125/htt_mt_125_shapes.root";
	TFile* inFile = new TFile(inputFile, "READ");

	//gROOT->LoadMacro("tdrstyle.C");
	setTDRStyle();
	//gROOT->LoadMacro("CMS_lumi.C");
	cmsText = "";
	writeExtraText = false;
	gStyle->SetOptStat(0);

	// Set tick marks on all 4 sides of pad
	gStyle->SetPadTickX(1);
	gStyle->SetPadTickY(1);
	gStyle->SetPalette(1);
	gROOT->ForceStyle(true);

	std::vector<TString> processName;
	processName.push_back("QCD");
	processName.push_back("TT");
	processName.push_back("VV");
	processName.push_back("W");
	processName.push_back("ZL");
	processName.push_back("ZTT");

	std::vector<TString> backgroundNames;
	backgroundNames.push_back("QCD");
	backgroundNames.push_back("top");
	backgroundNames.push_back("electroweak");
	backgroundNames.push_back("DY");

	std::map<int, TString> catNames;
	catNames[1] = "0-jet low-p_{T}(#tau_{h})";
	catNames[2] = "0-jet high-p_{T}(#tau_{h})";
	catNames[3] = "1-jet low-p_{T}(#tau_{h})";
	catNames[4] = "1-jet high-p_{T}(#tau_{h})";
	catNames[5] = "1-jet boosted";
	catNames[6] = "loose VBF";
	catNames[7] = "tight VBF";

	for (int bin = 1; bin <= 7; bin++) {
		// read histograms from input file
		TString hName = folder;
		hName.ReplaceAll("<bin>", TString::Itoa(bin, 10));
		std::vector<TH1D*> backgrounds;
		for (unsigned i = 0; i < processName.size(); i++) {
			TString name = processName.at(i);
			TH1D* hist = (TH1D*) inFile->Get(hName + name);
			hist->SetLineColor(1);
			hist->SetLineWidth(1);
			if (name == "QCD"){
				hist->SetFillColor(col_htt_qcd);
				backgrounds.push_back(hist);
			}
			if (name == "TT"){
				hist->SetFillColor(col_htt_tt);
				backgrounds.push_back(hist);
			}
			if (name == "VV"){
				hist->SetFillColor(col_htt_W);
				backgrounds.push_back(hist);
			}
			if (name == "W"){
				backgrounds.back()->Add(hist);
			}
			if (name == "ZL"){
				hist->SetFillColor(col_htt_Ztt);
				backgrounds.push_back(hist);
			}
			if (name == "ZTT"){
				backgrounds.back()->Add(hist);
			}
		}
		TH1D* total = (TH1D*) inFile->Get(hName + "TotalBkg");
		TH1D* signal = (TH1D*) inFile->Get(hName + "TotalSig");
		TH1D* data = (TH1D*) inFile->Get(hName + "data_obs");

		normToBinWidth(total);
		normToBinWidth(signal);
		normToBinWidth(data);

		TH1D* ratio = getRatio(data, total, bin);

		//get correct xAxis range
		double xLow = 0;
		double xHigh = 350;

		TCanvas* can = new TCanvas();
		THStack* stack = new THStack("stack", "stack");
		for (unsigned i = 0; i < backgrounds.size(); i++) {
			normToBinWidth(backgrounds.at(i));
			stack->Add(backgrounds.at(i));
		}
		TPad* Pad1 = new TPad("Pad1", "Pad1", 0., 0.3, 1., 1.);
		Pad1->SetTopMargin(0.07);
		Pad1->SetLeftMargin(0.15);
		Pad1->SetRightMargin(0.05);
		Pad1->SetBottomMargin(0);

		double yAxisScaleFactor = 1.3; // for linear y-axis

		Pad1->Draw();
		Pad1->cd();
		CMS_lumi(Pad1, 2, 0);
		Pad1->Update();

		data->SetMinimum(0.0001);
		if (data->GetMaximum() >= total->GetMaximum()) {
			data->SetMaximum(data->GetMaximum() * yAxisScaleFactor);
		} else {
			data->SetMaximum(total->GetMaximum() * yAxisScaleFactor);
		}

		data->GetXaxis()->SetRangeUser(xLow, xHigh);
		data->GetYaxis()->SetLabelSize(0.07);
		data->GetYaxis()->SetTitleSize(0.07);
		data->GetYaxis()->SetTitleOffset(1.0);
		data->SetMarkerColor(kBlack);
		data->SetMarkerStyle(20);
		TString yTitle = "Events / GeV ";
		data->GetYaxis()->SetTitle(yTitle);
		data->Draw("E");
		stack->Draw("Histsame");

		total->SetFillStyle(errorBandFillStyle);
		total->SetFillColor(errorBandColor);
		total->SetLineColor(18);
		total->SetMarkerColor(1);
		total->SetMarkerSize(0.001);
		total->Draw("E2same");

		// draw signal sample overlayed
		int signalScale = 1;
		switch (bin) {
			case 1:
				signalScale = 100;
				break;
			case 2:
			case 3:
				signalScale = 25;
				break;
			case 4:
			case 5:
				signalScale = 10;
				break;
			case 6:
				signalScale = 5;
				break;
			default:
				break;
		}
		signal->Scale(signalScale);
		signal->SetFillStyle(0);
		signal->SetLineStyle(7);
		signal->SetLineWidth(3);
		signal->SetLineColor(col_rwth_petrol);
		signal->Draw("Histsame");

		data->Draw("Esame");
		data->Draw("axissame");

		TLegend* legend = new TLegend(0.68, 0.37, 0.93, 0.87);
		legend->SetFillColor(0);
		legend->SetBorderSize(0);
		legend->SetFillStyle(0);
		legend->AddEntry(data, "Data", "pe");
		legend->AddEntry(total, "Bkg uncertainty", "F");

		for (int j = backgrounds.size() - 1; j >= 0; j--) {
			legend->AddEntry(backgrounds.at(j), backgroundNames.at(j), "F");
		}
		TString sigName = "Signal";
		if (signalScale != 1) sigName = sigName + " x" + TString::Itoa(signalScale, 10);
		legend->AddEntry(signal, sigName, "l");
		legend->Draw("same");
		Pad1->RedrawAxis();

		// draw data-MC ratio plot
		can->cd();
		TH1D* ratioband = (TH1D*) total->Clone("ratioband");
		for (int k = 1; k <= ratioband->GetNbinsX(); k++) {
			ratioband->SetBinContent(k, 1);
			ratioband->SetBinError(k, total->GetBinError(k) / total->GetBinContent(k));
		}
		ratioband->SetFillStyle(errorBandFillStyle);
		ratioband->SetFillColor(errorBandColor);
		ratioband->SetLineColor(18);
		ratioband->SetMarkerColor(1);
		ratioband->SetMarkerSize(0.001);
		TPad* Pad2 = new TPad("Pad1", "Pad1", 0., 0., 1., 0.3);
		Pad2->SetTopMargin(0);
		Pad2->SetLeftMargin(0.15);
		Pad2->SetRightMargin(0.05);
		Pad2->SetBottomMargin(0.4);
		Pad2->SetTickx(kTRUE);
		Pad2->SetGridx();
		Pad2->SetGridy();
		Pad2->Draw();
		Pad2->cd();

		ratio->GetXaxis()->SetTitle("m_{#tau#tau} / GeV");
		ratio->GetXaxis()->SetTitleSize(0.15);
		ratio->GetXaxis()->SetTitleOffset(1.1);
		ratio->GetXaxis()->SetLabelSize(0.15);
		ratio->GetXaxis()->SetTickLength(0.075);
		ratio->GetXaxis()->SetRangeUser(xLow, xHigh);
		ratio->GetXaxis()->SetNoExponent(true);
		ratio->GetYaxis()->SetTitle("Data/MC");
		ratio->GetYaxis()->SetTitleSize(0.15);
		ratio->GetYaxis()->SetLabelSize(0.15);
		ratio->GetYaxis()->SetTitleOffset(0.42);
		ratio->GetYaxis()->CenterTitle();
		ratio->GetYaxis()->SetNdivisions(4, 5, 0, kTRUE);

		switch (bin) {
			case 4:
			case 5:
			case 6:
				ratio->GetYaxis()->SetRangeUser(0.4,1.6);
				break;
			case 7:
				ratio->GetYaxis()->SetRangeUser(0.4,5.3);
				break;
			default:
				break;
		}

		ratio->SetMarkerStyle(20);
		ratio->SetMarkerSize(0.7);
		ratio->SetLineColor(kBlack);

		// line at ratio = 1
		TLine* line = new TLine(xLow, 1, xHigh, 1);

		ratio->Draw("E");
		ratioband->Draw("E2same");
		line->Draw("same");
		ratio->Draw("Esame");
		can->cd();
		can->SetWindowSize(800, 800);
		CMS_lumi(Pad1, 2, 0);

		TLatex latex;
		latex.SetNDC();
		//latex.SetTextAngle(0);
		//latex.SetTextColor(kBlack);
		//latex.SetTextFont(42);
		//latex.SetTextAlign(31);
		//latex.SetTextSize(lumiTextSize*t);
		latex.DrawLatex(0.68, 0.3, catNames[bin]);

		TString fileName = "PostfitShape_bin" + TString::Itoa(bin, 10);
		savePlot(can, fileName, true);

	}

	convertAllEpsToPdf();
}
