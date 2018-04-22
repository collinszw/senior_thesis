{
  gROOT->Reset();
  
  //TCanvas *c1 = new TCanvas();
  //TCanvas *c2 = new TCanvas();
  //TCanvas *c3 = new TCanvas();
  //TCanvas *c4 = new TCanvas();
  //TCanvas *c5 = new TCanvas();
  //TCanvas *c6 = new TCanvas();
  //TCanvas *c7 = new TCanvas();
  TCanvas *c8 = new TCanvas();
  TCanvas *c9 = new TCanvas();
  //TCanvas *c10 = new TCanvas();
  //TCanvas *c11 = new TCanvas();
  //TCanvas *c12 = new TCanvas();

  /*
    TFile *MyFile1 = new TFile("e_orig.root","OLD");
    TFile *MyFile2 = new TFile("e_rand.root","OLD");
    TFile *MyFile3 = new TFile("e_rand_5.root","OLD");
    TFile *MyFile4 = new TFile("e_rand_10.root","OLD");
  
    TH1F *hist1  = (TH1F*) MyFile1->Get("H10");
    TH1F *hist2  = (TH1F*) MyFile2->Get("H10");
    TH1F *hist3  = (TH1F*) MyFile3->Get("H10");
    TH1F *hist4  = (TH1F*) MyFile4->Get("H10");

    c1->cd();
    hist1->SetMarkerColor(kBlue);
    hist1->SetMarkerStyle(kMultiply);
    hist1->SetMarkerSize(2);
    hist1->Draw("e");
    hist2->SetMarkerColor(kRed);
    hist2->SetMarkerStyle(kStar);
    hist2->Draw("Same");
    hist3->SetMarkerColor(kGreen);
    hist3->SetMarkerStyle(kCircle);
    hist3->Draw("Same");
    hist4->SetMarkerColor(kYellow);
    hist4->SetMarkerStyle(kFullSquare);
    hist4->Draw("Same");

    c1->BuildLegend(0.4,0.9,0.1,0.75);
  
    TFile *MyFile5 = new TFile("neut_orig.root","OLD");
    TFile *MyFile6 = new TFile("neut_rand.root","OLD");
    TFile *MyFile7 = new TFile("neut_rand_5.root","OLD");
    TFile *MyFile8 = new TFile("neut_rand_10.root","OLD");
  
    TH1F *hist5  = (TH1F*) MyFile5->Get("H10");
    TH1F *hist6  = (TH1F*) MyFile6->Get("H10");
    TH1F *hist7  = (TH1F*) MyFile7->Get("H10");
    TH1F *hist8  = (TH1F*) MyFile8->Get("H10");

    c2->cd();
    hist5->SetMarkerColor(kBlue);
    hist5->SetMarkerStyle(kMultiply);
    hist5->SetMarkerSize(2);
    hist5->Draw("e");
    hist6->SetMarkerColor(kRed);
    hist6->SetMarkerStyle(kStar);
    hist6->Draw("Same");
    hist7->SetMarkerColor(kGreen);
    hist7->SetMarkerStyle(kCircle);
    hist7->Draw("Same");
    hist8->SetMarkerColor(kYellow);
    hist8->SetMarkerStyle(kFullSquare);
    hist8->Draw("Same");

    c2->BuildLegend(0.9,0.75,0.6,0.6);
  
    TFile *MyFile9 = new TFile("gamma_orig.root","OLD");
    TFile *MyFile10 = new TFile("gamma_rand.root","OLD");
    TFile *MyFile11 = new TFile("gamma_rand_5.root","OLD");
    TFile *MyFile12 = new TFile("gamma_rand_10.root","OLD");
  
    TH1F *hist9  = (TH1F*) MyFile9->Get("H10");
    TH1F *hist10  = (TH1F*) MyFile10->Get("H10");
    TH1F *hist11  = (TH1F*) MyFile11->Get("H10");
    TH1F *hist12  = (TH1F*) MyFile12->Get("H10");

    c3->cd();
    hist9->SetMarkerColor(kBlue);
    hist9->SetMarkerStyle(kMultiply);
    hist9->SetMarkerSize(2);
    hist9->Draw("e");
    hist10->SetMarkerColor(kRed);
    hist10->SetMarkerStyle(kStar);
    hist10->Draw("Same");
    hist11->SetMarkerColor(kGreen);
    hist11->SetMarkerStyle(kCircle);
    hist11->Draw("Same");
    hist12->SetMarkerColor(kYellow);
    hist12->SetMarkerStyle(kFullSquare);
    hist12->Draw("Same");

    c3->BuildLegend(0.9,0.75,0.6,0.6);



  
    ifstream in;
    ifstream out;
    Int_t n; //this is number  of bins
    int x_range;
  
    Double_t ntest1,test2,lost[10000000],total[10000000],avg_lost[100],avg_total[100],avg_count[100],avg_eff[100],y_error[100], y_mean_error;
    //gamma = 13, neutron = 13, electron = 50

    int lines = 0;

    TH1F* loss_dist = new TH1F("H100", "histogram of electron energy lost for total energy 30-32 MeV", 32000, 0, 32);
  
    for(int k = 0;k<9;k++){
    lines = 0;

    //new format
    *//*
	if(k == 0){
	in.open("electron_energy_spectrum",std::fstream::in);
	out.open("electron_energy_spectrum",std::fstream::in);
	n = 25;
	x_range = n*2;
	}else if(k == 1){
	in.open("neutron_energy_spectrum",std::fstream::in);
	out.open("neutron_energy_spectrum",std::fstream::in);
	n = 13;
	x_range = n;
	}else if(k == 2){
	in.open("proton_energy_spectrum",std::fstream::in);
	out.open("proton_energy_spectrum",std::fstream::in);
	n = 13;
	x_range = n;
	}else if(k == 3){
	in.open("photon_energy_spectrum",std::fstream::in);
	out.open("photon_energy_spectrum",std::fstream::in);
	n = 13;
	x_range = n;
	}

      *//*
    
	//old format 
	if(k==0){
	in.open("energy_lost_vs_total_y.txt",std::fstream::in);
	n = 13;
	x_range = n;
	}else if(k==1){
	in.open("energy_lost_vs_total_y_5.txt",std::fstream::in);
	n = 13;
	x_range = n;
	}else if(k==2){
	in.open("energy_lost_vs_total_y_10.txt",std::fstream::in);
	n = 13;
	x_range = n;
	}else if(k==3){
	in.open("energy_lost_vs_total_e.txt",std::fstream::in);
	n = 25;
	x_range = n*2;
	}else if(k==4){
	in.open("energy_lost_vs_total_e_5.txt",std::fstream::in);
	n = 25;
	x_range = n*2;
	}else if(k==5){
	in.open("energy_lost_vs_total_e_10.txt",std::fstream::in);
	n = 25;
	x_range = n*2;
	}else if(k==6){
	in.open("energy_lost_vs_total_n.txt",std::fstream::in);
	n = 13;
	x_range = n;
	}else if(k==7){
	in.open("energy_lost_vs_total_n_5.txt",std::fstream::in);
	n = 13;
	x_range = n;
	}else if(k==8){
	in.open("energy_lost_vs_total_n_10.txt",std::fstream::in);
	n = 13;
	x_range = n;
	}
    
	//TH2F* energy = new TH2F("H1","total energy versus energy lost",130,0,13,130,0,13);

	while(1){
	in  >> total[lines] >> lost[lines];
	//out >> lost[lines]; //new way
	if (!in.good()) break;
	//energy->Fill(total[lines],lost[lines]);
	lines++;
	}
	//cout<<lines<<"\n";
	for(int j=0;j<n;j++){
	avg_total[j] = 0;
	avg_lost[j] = 0;
	avg_count[j] = 0;
	avg_eff[j] = 0;
	}

	for(int j=0;j<n;j++){
	loss_dist->Reset();
	for(int i=0;i<lines;i++){
	if(total[i] < (Double_t)x_range*(j+1)/n  && total[i] > (Double_t)x_range*(j)/n){
	avg_total[j] += total[i];
	avg_lost[j]  += lost[i];
	loss_dist->Fill(total[i]-lost[i]);
	  	  
	avg_eff[j] += (total[i]-lost[i])/(total[i]);
	  
	avg_count[j] += 1;
	
	}
	}
	if(avg_total[j] && avg_count[j]) avg_total[j]/=avg_count[j];
	if(avg_lost[j]  && avg_count[j]) avg_lost[j]/=avg_count[j];
	if(avg_eff[j]   && avg_count[j]) avg_eff[j]/=avg_count[j];
      
	y_mean_error = loss_dist->GetStdDev();
	y_error[j] = sqrt(y_mean_error)/avg_total[j];
	}
    
	if(k == 0){
	c4->cd();
	//TGraphErrors* energy_y = new TGraphErrors(n,avg_total,avg_lost);
	TGraphErrors* energy_y = new TGraphErrors(n,avg_total,avg_eff, 0, y_error);
	energy_y->Draw("A*");
	energy_y->SetTitle("Photon energy efficiency");
	energy_y->GetXaxis()->SetTitle("Total energy of a particle");
	//energy_y->GetYaxis()->SetTitle("Energy lost in liquid argon");
	energy_y->GetYaxis()->SetTitle("Efficiency");
	energy_y->SetMarkerColor(kBlue);
	energy_y->SetLineColor(kBlue);
	}else if(k==1){
	//c5->cd();
	//TGraphErrors* energy_y_5 = new TGraphErrors(n,avg_total,avg_lost);
	TGraphErrors* energy_y_5 = new TGraphErrors(n,avg_total,avg_eff, 0, y_error);
	energy_y_5->Draw("* SAME");
	energy_y_5->SetTitle("Photon energy efficiency 5 cm in");
	energy_y_5->GetXaxis()->SetTitle("Total energy of a particle");
	//energy_y_5->GetYaxis()->SetTitle("Energy lost in liquid argon");
	energy_y_5->GetYaxis()->SetTitle("Efficiency");
	energy_y_5->SetMarkerColor(kRed);
	energy_y_5->SetLineColor(kRed);
	}else if(k==2){
	//c6->cd();
	//TGraphErrors* energy_y_10 = new TGraphErrors(n,avg_total,avg_lost);
	TGraphErrors* energy_y_10 = new TGraphErrors(n,avg_total,avg_eff, 0, y_error);
	energy_y_10->Draw("* SAME");
	energy_y_10->SetTitle("Photon energy efficiency 10 cm in");
	energy_y_10->GetXaxis()->SetTitle("Total energy of a particle");
	//energy_y_10->GetYaxis()->SetTitle("Energy lost in liquid argon");
	energy_y_10->GetYaxis()->SetTitle("Efficiency");
	energy_y_10->SetMarkerColor(kGreen);
	energy_y_10->SetLineColor(kGreen);
	c4->BuildLegend(0.3,0.9,0.6,0.75);
	}else if(k==3){
	c5->cd();
	//TGraphErrors* energy_e = new TGraphErrors(n,avg_total,avg_lost);
	TGraphErrors* energy_e = new TGraphErrors(n,avg_total,avg_eff, 0, y_error);
	energy_e->Draw("A*");
	energy_e->SetTitle("Electron energy efficiency");
	energy_e->GetXaxis()->SetTitle("Total energy of a particle");
	//energy_e->GetYaxis()->SetTitle("Energy lost in liquid argon");
	energy_e->GetYaxis()->SetTitle("Efficiency");
	energy_e->SetMarkerColor(kBlue);
	energy_e->SetLineColor(kBlue);
	}else if(k==4){
	//c8->cd();
	//TGraphErrors* energy_e_5 = new TGraphErrors(n,avg_total,avg_lost);
	TGraphErrors* energy_e_5 = new TGraphErrors(n,avg_total,avg_eff, 0, y_error);
	energy_e_5->Draw("* SAME");
	energy_e_5->SetTitle("Electron energy efficiency 5 cm in");
	energy_e_5->GetXaxis()->SetTitle("Total energy of a particle");
	//energy_e_5->GetYaxis()->SetTitle("Energy lost in liquid argon");
	energy_e_5->GetYaxis()->SetTitle("Efficiency");
	energy_e_5->SetMarkerColor(kRed);
	energy_e_5->SetLineColor(kRed);
	}else if(k==5){
	//c9->cd();
	//TGraphErrors* energy_e_10 = new TGraphErrors(n,avg_total,avg_lost);
	TGraphErrors* energy_e_10 = new TGraphErrors(n,avg_total,avg_eff, 0, y_error);
	energy_e_10->Draw("* SAME");
	energy_e_10->SetTitle("Electron energy efficiency 10 cm in");
	energy_e_10->GetXaxis()->SetTitle("Total energy of a particle");
	//energy_e_10->GetYaxis()->SetTitle("Energy lost in liquid argon");
	energy_e_10->GetYaxis()->SetTitle("Efficiency");
	energy_e_10->SetMarkerColor(kGreen);
	energy_e_10->SetLineColor(kGreen);
	c5->BuildLegend(0.9,0.55,0.6,0.4);
	}else if(k==6){
	c6->cd();
	//TGraphErrors* energy_n = new TGraphErrors(n,avg_total,avg_lost);
	TGraphErrors* energy_n = new TGraphErrors(n,avg_total,avg_eff, 0, y_error);
	energy_n->Draw("A*");
	energy_n->SetTitle("Neutron energy efficiency");
	energy_n->GetXaxis()->SetTitle("Total energy of a particle");
	//energy_n->GetYaxis()->SetTitle("Energy lost in liquid argon");
	energy_n->GetYaxis()->SetTitle("Efficiency");
	energy_n->SetMarkerColor(kBlue);
	energy_n->SetLineColor(kBlue);
	}else if(k==7){
	//c11->cd();
	//TGraphErrors* energy_n_5 = new TGraphErrors(n,avg_total,avg_lost);
	TGraphErrors* energy_n_5 = new TGraphErrors(n,avg_total,avg_eff, 0, y_error);
	energy_n_5->Draw("* SAME");
	energy_n_5->SetTitle("Neutron energy efficiency 5 cm in");
	energy_n_5->GetXaxis()->SetTitle("Total energy of a particle");
	//energy_n_5->GetYaxis()->SetTitle("Energy lost in liquid argon");
	energy_n_5->GetYaxis()->SetTitle("Efficiency");
	energy_n_5->SetMarkerColor(kRed);
	energy_n_5->SetLineColor(kRed);
	}else if(k==8){
	//c12->cd();
	//TGraphErrors* energy_n_10 = new TGraphErrors(n,avg_total,avg_lost);
	TGraphErrors* energy_n_10 = new TGraphErrors(n,avg_total,avg_eff, 0, y_error);
	energy_n_10->Draw("* SAME");
	energy_n_10->SetTitle("Neutron energy efficiency 10 cm in");
	energy_n_10->GetXaxis()->SetTitle("Total energy of a particle");
	//energy_n_10->GetYaxis()->SetTitle("Energy lost in liquid argon");
	energy_n_10->GetYaxis()->SetTitle("Efficiency");
	energy_n_10->SetMarkerColor(kGreen);
	energy_n_10->SetLineColor(kGreen);
	c6->BuildLegend(0.1,0.9,0.4,0.75);
	}
	in.close();
	out.close();
	}
	c7->cd();
	//std::cout<<y_mean_error<<"\n";
	loss_dist->Draw();

	*/

  //neutrino energies vs total recovered energy
  
  
  ifstream neut;
  neut.open("neutrino_energy_spectrum.txt",std::fstream::in);

  ifstream out;
  out.open("recovered_ar_energy_spectrum.txt",std::fstream::in);
  ifstream electron;
  electron.open("electron_ar_energy_spectrum.txt",std::fstream::in);
  ifstream neutron;
  neutron.open("neutron_ar_energy_spectrum.txt",std::fstream::in);
  ifstream proton;
  proton.open("proton_ar_energy_spectrum.txt",std::fstream::in);
  ifstream photon;
  photon.open("photon_ar_energy_spectrum.txt",std::fstream::in);

  ifstream n_count;
  n_count.open("extra_ar_energy_spectrum.txt",std::fstream::in);

  TH1F *neut_e_hist = new TH1F("neut_e_hist", "Total energy of the neutrino", 55,0,55);
  TH1F *rec_ar_e_hist = new TH1F("rec_ar_e_hist", "Recovered energy of the neutrino", 55,0,55);

  TH1F *electron_ar_e_hist = new TH1F("electron_ar_e_hist", "Deposited electron energy for an event", 55,0,55);
  TH1F *neutron_ar_e_hist = new TH1F("neutron_ar_e_hist", "Deposited electron and neutron energy for an event", 55,0,55);
  TH1F *proton_ar_e_hist = new TH1F("proton_ar_e_hist", "Deposited electron, neutron, and proton energy for an event", 55,0,55);
  TH1F *photon_ar_e_hist = new TH1F("photon_ar_e_hist", "Deposited electron, neutron, proton, and photon energy for an event", 55,0,55);
  TH1F *neutron_count_hist = new TH1F("neutron_count_hist", "Adjustment of total energy spectrum for neutron seperation energy", 55,0,55);
  
  Int_t e_line = 0;
  Double_t neut_e[10000000], rec_ar_e[10000000], electron_ar_e[10000000], neutron_ar_e[10000000], proton_ar_e[10000000], photon_ar_e[10000000], neutron_count[10000000];

  while(1){
    neut >> neut_e[e_line];
    //std::cout<<neut_e[e_line]<<"\n";
    out >> rec_ar_e[e_line];
    electron >> electron_ar_e[e_line];
    neutron >> neutron_ar_e[e_line];
    proton >> proton_ar_e[e_line];
    photon >> photon_ar_e[e_line];

    n_count >> neutron_count[e_line];
    if(neutron_count[e_line] == 1){
      neutron_count[e_line] = 9.04; //now it's energy
    }else if(neutron_count[e_line] == 2){
      neutron_count[e_line] = 22.64; //now it's energy
    }
    
    

    neut_e_hist->Fill(neut_e[e_line]);
    rec_ar_e_hist->Fill(rec_ar_e[e_line]);

    
    
    electron_ar_e_hist->Fill(electron_ar_e[e_line]);
    neutron_ar_e_hist->Fill(electron_ar_e[e_line]+neutron_ar_e[e_line]);
    proton_ar_e_hist->Fill(electron_ar_e[e_line]+neutron_ar_e[e_line]+proton_ar_e[e_line]);
    photon_ar_e_hist->Fill(electron_ar_e[e_line]+neutron_ar_e[e_line]+photon_ar_e[e_line]+photon_ar_e[e_line]);
    neutron_count_hist->Fill(electron_ar_e[e_line]+neutron_ar_e[e_line]+photon_ar_e[e_line]+photon_ar_e[e_line]+neutron_count[e_line]);

    if (!neut.good()) break;
    if (!out.good()) break;
    if (!electron.good()) break;
    if (!neutron.good()) break;
    if (!proton.good()) break;
    if (!photon.good()) break;
    e_line++;
  }

  c8->cd();
  neut_e_hist->Draw("PC*");
  neut_e_hist->SetMarkerColor(kBlue);
  neut_e_hist->SetLineColor(kBlue);
  neut_e_hist->GetXaxis()->SetTitle("Energy (MEv)");
  //rec_ar_e_hist->Draw("PC* SAME");
  rec_ar_e_hist->SetMarkerColor(kRed);
  rec_ar_e_hist->SetLineColor(kRed);
  electron_ar_e_hist->Draw("PC* SAME");
  electron_ar_e_hist->SetMarkerColor(kGreen);
  electron_ar_e_hist->SetLineColor(kGreen);
  neutron_ar_e_hist->Draw("PC* SAME");
  neutron_ar_e_hist->SetMarkerColor(kYellow);
  neutron_ar_e_hist->SetLineColor(kYellow);
  proton_ar_e_hist->Draw("PC* SAME");
  proton_ar_e_hist->SetMarkerColor(kCyan);
  proton_ar_e_hist->SetLineColor(kCyan);
  photon_ar_e_hist->Draw("PC* SAME");
  photon_ar_e_hist->SetMarkerColor(kMagenta);
  photon_ar_e_hist->SetLineColor(kMagenta);
  neutron_count_hist->Draw("PC* SAME");
  neutron_count_hist->SetMarkerColor(kRed);
  neutron_count_hist->SetLineColor(kRed);


  c8->BuildLegend(0.1,0.9,0.4,0.75);
  neut_e_hist->SetTitle("Incoming neutrino energy vs energy deposited in the TPC volume (liquid argon)");
  c8->SetTitle("Incoming neutrino energy vs energy deposited in the TPC volume (liquid argon)");
  

  out.close();
  electron.close();
  neutron.close();
  proton.close();
  photon.close();
  
  out.open("recovered_energy_spectrum.txt",std::fstream::in);
  electron.open("electron_energy_spectrum.txt",std::fstream::in);
  neutron.open("neutron_energy_spectrum.txt",std::fstream::in);
  proton.open("proton_energy_spectrum.txt",std::fstream::in);
  photon.open("photon_energy_spectrum.txt",std::fstream::in);

  TH1F *rec_gd_e_hist = new TH1F("rec_e_hist", "Recovered energy of the neutrino", 55,0,55);

  TH1F *electron_gd_e_hist = new TH1F("electron_gd_e_hist", "Deposited electron energy for an event", 55,0,55);
  TH1F *neutron_gd_e_hist = new TH1F("neutron_gd_e_hist", "Deposited electron and neutron energy for an event", 55,0,55);
  TH1F *proton_gd_e_hist = new TH1F("proton_gd_e_hist", "Deposited electron, neutron, and proton energy for an event", 55,0,55);
  TH1F *photon_gd_e_hist = new TH1F("photon_gd_e_hist", "Deposited electron, neutron, proton, and photon energy for an event", 55,0,55);
  
  e_line = 0;
  Double_t rec_gd_e[10000000], electron_gd_e[10000000], neutron_gd_e[10000000], proton_gd_e[10000000], photon_gd_e[10000000];

  while(1){
    out >> rec_gd_e[e_line];
    electron >> electron_gd_e[e_line];
    neutron >> neutron_gd_e[e_line];
    proton >> proton_gd_e[e_line];
    photon >> photon_gd_e[e_line];

    rec_gd_e_hist->Fill(rec_ar_e[e_line]+rec_gd_e[e_line]);

    electron_gd_e_hist->Fill(/*electron_ar_e[e_line]+*/electron_gd_e[e_line]);
    neutron_gd_e_hist->Fill(/*electron_ar_e[e_line]+neutron_ar_e[e_line]+*/electron_gd_e[e_line]+neutron_gd_e[e_line]);
    proton_gd_e_hist->Fill(/*electron_ar_e[e_line]+neutron_ar_e[e_line]+proton_ar_e[e_line]+*/electron_gd_e[e_line]+neutron_gd_e[e_line]+proton_gd_e[e_line]);
    photon_gd_e_hist->Fill(/*electron_ar_e[e_line]+neutron_ar_e[e_line]+photon_ar_e[e_line]+photon_ar_e[e_line]+*/electron_gd_e[e_line]+neutron_gd_e[e_line]+photon_gd_e[e_line]+photon_gd_e[e_line]);
    
    if (!out.good()) break;
    if (!electron.good()) break;
    if (!neutron.good()) break;
    if (!proton.good()) break;
    if (!photon.good()) break;
    e_line++;
  }

  c9->cd();
  neut_e_hist->Draw("PC*");
  neut_e_hist->SetMarkerColor(kBlue);
  neut_e_hist->SetLineColor(kBlue);
  neut_e_hist->GetXaxis()->SetTitle("Energy (MEv)");
  //rec_gd_e_hist->Draw("PC* SAME");
  rec_gd_e_hist->SetMarkerColor(kRed);
  rec_gd_e_hist->SetLineColor(kRed);
  electron_gd_e_hist->Draw("PC* SAME");
  electron_gd_e_hist->SetMarkerColor(kGreen);
  electron_gd_e_hist->SetLineColor(kGreen);
  neutron_gd_e_hist->Draw("PC* SAME");
  neutron_gd_e_hist->SetMarkerColor(kYellow);
  neutron_gd_e_hist->SetLineColor(kYellow);
  proton_gd_e_hist->Draw("PC* SAME");
  proton_gd_e_hist->SetMarkerColor(kCyan);
  proton_gd_e_hist->SetLineColor(kCyan);
  photon_gd_e_hist->Draw("PC* SAME");
  photon_gd_e_hist->SetMarkerColor(kMagenta);
  photon_gd_e_hist->SetLineColor(kMagenta);


  c9->BuildLegend(0.1,0.9,0.4,0.75);
  //neut_e_hist->SetTitle("Incoming neutrino energy vs energy deposited in the TPC volume (with plastic scintillator)");
  c9->SetTitle("Incoming neutrino energy vs energy deposited in the TPC volume (with plastic scintillator) ");
  
}

//Efficiency = (total energy deposited)/(total energy)
