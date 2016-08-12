TH1D* getRatio(TH1D* datahist, TH1D* bkghist, int bin){
	int nbins = datahist->GetNbinsX();
	TString name = TString(datahist->GetName())+"_MCRatio"+TString::Itoa(bin, 10);
	TH1D* hist = (TH1D*)datahist->Clone(name);

	for(int i=1;i<=nbins;i++){
		double data = datahist->GetBinContent(i);
		double dataerror = datahist->GetBinError(i);
		double mc = bkghist->GetBinContent(i);
		double mcerr = bkghist->GetBinError(i);
		if(mc>0){
			hist->SetBinContent(i,data/mc);
			hist->SetBinError(i,dataerror/mc);
		}
	}
	hist->GetYaxis()->SetRangeUser(0.7,1.3);
	hist->GetXaxis()->SetTitle(datahist->GetXaxis()->GetTitle());
	return hist;
}

void normToBinWidth(TH1D* hist){
	int nbins = hist->GetNbinsX();
	for(int i=1;i<=nbins;i++){
		double scale = 1. / hist->GetBinWidth(i);
		hist->SetBinContent(i, scale * hist->GetBinContent(i));
		hist->SetBinError(i, scale * hist->GetBinError(i));
	}
}

// get a TString from the current time
// stolen from http://www.cplusplus.com/reference/ctime/strftime/
static TString timeNow = "";
TString timeStamp(bool Date, bool Time){
	// use same timestamp for all plots
	if (timeNow != "")
		return timeNow;

	if (!Date && !Time){
		return "";
	}

	time_t rawtime;
	struct tm * timeinfo;
	char buffer [80];

	time (&rawtime);
	timeinfo = localtime (&rawtime);

	// output pattern
	TString pattern = "";
	if (Date)			pattern += "%F";
	if (Date && Time)	pattern += "_";
	if (Time) 			pattern += "%H-%M";

	strftime (buffer,80,pattern.Data(),timeinfo);
	timeNow = TString(buffer);
	return timeNow;
}

void savePlot(TCanvas* canvas, TString plotName, bool useTimedFolders = true){
	TString fileName = plotName + ".eps";

	// store plots in individual folder
	TString pwd = gSystem->WorkingDirectory();
	if (useTimedFolders){
		TString dirName = timeStamp(true, true);
		if (!gSystem->ChangeDirectory(dirName)){
			gSystem->MakeDirectory(dirName);
			gSystem->ChangeDirectory(dirName);
		}
	}

	canvas->cd();
	canvas->SaveAs(fileName.Data());

	if (useTimedFolders){
		gSystem->ChangeDirectory(pwd);
	}
}

void convertAllEpsToPdf(){
	std::cout << "Convert all eps into pdf..." << std::endl;

	const char* pwd = gSystem->pwd();
	if (timeNow != ""){
		gSystem->ChangeDirectory(timeNow);
		std::cout << "Plots are saved in folder " << timeNow << std::endl;
	}

	gSystem->Exec("for i in `ls -1 *.eps`; do epstopdf $i; done");

	gSystem->ChangeDirectory(pwd);
}

// === some useful color definitions ===
// htautau colors
int col_htt_qcd = TColor::GetColor(250,202,255);
int col_htt_W = TColor::GetColor(222,90,106);
int col_htt_ZJ = TColor::GetColor(222,90,106);
int col_htt_tt = TColor::GetColor(155,152,204);
int col_htt_Ztt = TColor::GetColor(248,206,104);

// RWTH colors
// http://www9.rwth-aachen.de/global/show_document.asp?id=aaaaaaaaaadpbhq
int col_rwth_darkblue	= TColor::GetColor(0,84,159);
int col_rwth_lightblue	= TColor::GetColor(142,186,229);
int col_rwth_magenta	= TColor::GetColor(227,0,102);
int col_rwth_yellow		= TColor::GetColor(255,237,0);
int col_rwth_petrol		= TColor::GetColor(0,97,101);
int col_rwth_turquoise	= TColor::GetColor(0,152,161);
int col_rwth_green		= TColor::GetColor(87,171,39);
int col_rwth_maygreen	= TColor::GetColor(189,205,0);
int col_rwth_orange		= TColor::GetColor(246,168,0);
int col_rwth_red		= TColor::GetColor(204,7,30);
int col_rwth_violett	= TColor::GetColor(97,33,88);
int col_rwth_purple		= TColor::GetColor(122,111,172);
