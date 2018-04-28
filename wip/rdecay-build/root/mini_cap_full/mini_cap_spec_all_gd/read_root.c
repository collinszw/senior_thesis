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
  TCanvas *c10 = new TCanvas();
  //TCanvas *c11 = new TCanvas();
  //TCanvas *c12 = new TCanvas();


  //Some efficiency plots

  
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
  n_count.open("neutron_count.txt",std::fstream::in);
  ifstream n_cap;
  n_cap.open("neutron_capture_ar.txt",std::fstream::in);

  TH1F *neut_e_hist = new TH1F("neut_e_hist", "Total energy of the neutrino", 56,0,56);
  TH1F *rec_ar_e_hist = new TH1F("rec_ar_e_hist", "Recovered energy of the neutrino", 56,0,56);

  TH1F *electron_ar_e_hist = new TH1F("electron_ar_e_hist", "Deposited electron energy for an event (liquid argon)", 56,0,56);
  TH1F *neutron_ar_e_hist = new TH1F("neutron_ar_e_hist", "Deposited electron and neutron energy for an event (liquid argon)", 56,0,56);
  TH1F *proton_ar_e_hist = new TH1F("proton_ar_e_hist", "Deposited electron, neutron, and proton energy for an event (liquid argon)", 56,0,56);
  TH1F *photon_ar_e_hist = new TH1F("photon_ar_e_hist", "Deposited electron, neutron, proton, and photon energy for an event (liquid argon)", 56,0,56);
  TH1F *neutron_count_hist = new TH1F("neutron_count_hist", "Adjustment of total energy spectrum for neutron seperation energy (liquid argon)", 56,0,56);
  TH1F *proton_count_hist = new TH1F("proton_count_hist", "Adjustment of total energy spectrum for proton seperation energy (liquid argon)", 56,0,56);
  
  Int_t e_line = 0;
  Double_t neut_e[10000000], rec_ar_e[10000000], electron_ar_e[10000000], neutron_ar_e[10000000], proton_ar_e[10000000], photon_ar_e[10000000], neutron_count[10000000], proton_count[10000000], n_cap_count_ar[10000000], n_tot_ar, n_cap_ar;

  n_cap_ar = 0;
  while(1){ 
    neut >> neut_e[e_line];
    //std::cout<<neut_e[e_line]<<"\n";
    out >> rec_ar_e[e_line];
    electron >> electron_ar_e[e_line];
    if(electron_ar_e[e_line] <  10){
      //std::cout<<electron_ar_e[e_line]<<"\n";
    }
    neutron >> neutron_ar_e[e_line];
    proton >> proton_ar_e[e_line];
    photon >> photon_ar_e[e_line];


    // source for energies: https://arxiv.org/pdf/1704.08906.pdf
    n_count >> neutron_count[e_line];
    n_tot_ar+= neutron_count[e_line];
    
    
    /*if(neutron_count[e_line] == 1){
      neutron_count[e_line] = 7.62; //now it's energy
    }else if(neutron_count[e_line] == 2){
      neutron_count[e_line] = 22.11; //now it's energy
    }
    p_count >> proton_count[e_line];
    if(proton_count[e_line] == 1){
      proton_count[e_line] = 8.03; //now it's energy
    }else if(proton_count[e_line] == 2){
      proton_count[e_line] = 19.73; //now it's energy
    }*/
    

    neut_e_hist->Fill(neut_e[e_line]);
    rec_ar_e_hist->Fill(rec_ar_e[e_line]);
    
    
    electron_ar_e_hist->Fill(electron_ar_e[e_line]);
    neutron_ar_e_hist->Fill(electron_ar_e[e_line]+neutron_ar_e[e_line]);
    proton_ar_e_hist->Fill(electron_ar_e[e_line]+neutron_ar_e[e_line]+proton_ar_e[e_line]);
    photon_ar_e_hist->Fill(electron_ar_e[e_line]+neutron_ar_e[e_line]+proton_ar_e[e_line]+photon_ar_e[e_line]);
    //neutron_count_hist->Fill(electron_ar_e[e_line]+neutron_ar_e[e_line]+photon_ar_e[e_line]+photon_ar_e[e_line]+neutron_count[e_line]);
    //proton_count_hist->Fill(electron_ar_e[e_line]+neutron_ar_e[e_line]+photon_ar_e[e_line]+photon_ar_e[e_line]+neutron_count[e_line]+proton_count[e_line]);

    if (!neut.good()) break;
    if (!out.good()) break;
    if (!electron.good()) break;
    if (!neutron.good()) break;
    if (!proton.good()) break;
    if (!photon.good()) break;
    e_line++;
  }
  
  n_cap >> n_cap_ar;
  
  std::cout<<"Neutron efficiency in ar: "<< n_cap_ar/n_tot_ar<< " , with " << n_cap_ar <<" neutrons captured, out of "<< n_tot_ar <<" total neutrons \n";
  
  c8->cd();
  neut_e_hist->Draw("");
  neut_e_hist->SetMarkerColor(kBlue);
  neut_e_hist->SetLineColor(kBlue);
  neut_e_hist->GetYaxis()->SetTitle("Counts");
  neut_e_hist->GetXaxis()->SetTitle("Energy (MEv)");
  //rec_ar_e_hist->Draw("PC* SAME");
  rec_ar_e_hist->SetMarkerColor(kRed);
  rec_ar_e_hist->SetLineColor(kRed);
  electron_ar_e_hist->Draw("SAME");
  electron_ar_e_hist->SetMarkerColor(kGreen);
  electron_ar_e_hist->SetLineColor(kGreen);
  neutron_ar_e_hist->Draw("SAME");
  neutron_ar_e_hist->SetMarkerColor(kYellow);
  neutron_ar_e_hist->SetLineColor(kYellow);
  proton_ar_e_hist->Draw("SAME");
  proton_ar_e_hist->SetMarkerColor(kCyan);
  proton_ar_e_hist->SetLineColor(kCyan);
  photon_ar_e_hist->Draw("SAME");
  photon_ar_e_hist->SetMarkerColor(kMagenta);
  photon_ar_e_hist->SetLineColor(kMagenta);


  c8->BuildLegend(0.1,0.9,0.4,0.75);
  //neut_e_hist->SetTitle("Incoming neutrino energy vs energy deposited in the TPC volume (only liquid argon)");
  c8->SetTitle("Incoming neutrino energy vs energy deposited in the TPC volume (liquid argon)");

  out.close();
  electron.close();
  neutron.close();
  proton.close();
  photon.close();
  n_cap.close();
  
  out.open("recovered_gd_energy_spectrum.txt",std::fstream::in);
  electron.open("electron_gd_energy_spectrum.txt",std::fstream::in);
  neutron.open("neutron_gd_energy_spectrum.txt",std::fstream::in);
  proton.open("proton_gd_energy_spectrum.txt",std::fstream::in);
  photon.open("photon_gd_energy_spectrum.txt",std::fstream::in);

  n_cap.open("neutron_capture_gd.txt",std::fstream::in);
  
  TH1F *rec_gd_e_hist = new TH1F("rec_e_hist", "Recovered energy of the neutrino", 56,0,56);

  TH1F *electron_gd_e_hist = new TH1F("electron_gd_e_hist", "Deposited electron energy for an event (LAr with plastic scinitllator)", 56,0,56);
  TH1F *neutron_gd_e_hist = new TH1F("neutron_gd_e_hist", "Deposited electron and neutron energy for an event (LAr with plastic scinitllator)", 56,0,56);
  TH1F *proton_gd_e_hist = new TH1F("proton_gd_e_hist", "Deposted electron, neutron, and proton energy for an event (LAr with plastic scinitllator)", 56,0,56);
  TH1F *photon_gd_e_hist = new TH1F("photon_gd_e_hist", "Deposited electron, neutron, proton, and photon energy for an event (LAr with plastic scinitllator)", 56,0,56);
  
  e_line = 0;
  Double_t rec_gd_e[10000000], electron_gd_e[10000000], neutron_gd_e[10000000], proton_gd_e[10000000], photon_gd_e[10000000], n_cap_count_gd[10000000], n_cap_gd, n_tot_gd;

  n_cap_gd = 0;
  while(1){
    out >> rec_gd_e[e_line];
    electron >> electron_gd_e[e_line];
    neutron >> neutron_gd_e[e_line];
    proton >> proton_gd_e[e_line];
    photon >> photon_gd_e[e_line];

    rec_gd_e_hist->Fill(rec_ar_e[e_line]+rec_gd_e[e_line]);

    n_count >> neutron_count[e_line];
    n_tot_gd+= neutron_count[e_line];
        
    electron_gd_e_hist->Fill(electron_ar_e[e_line]+electron_gd_e[e_line]);
    neutron_gd_e_hist->Fill(electron_ar_e[e_line]+neutron_ar_e[e_line]+electron_gd_e[e_line]+neutron_gd_e[e_line]);
    proton_gd_e_hist->Fill(electron_ar_e[e_line]+neutron_ar_e[e_line]+proton_ar_e[e_line]+electron_gd_e[e_line]+neutron_gd_e[e_line]+proton_gd_e[e_line]);
    photon_gd_e_hist->Fill(electron_ar_e[e_line]+neutron_ar_e[e_line]+proton_ar_e[e_line]+photon_ar_e[e_line]+electron_gd_e[e_line]+neutron_gd_e[e_line]+proton_gd_e[e_line]+photon_gd_e[e_line]);
    
    if (!out.good()) break;
    if (!electron.good()) break;
    if (!neutron.good()) break;
    if (!proton.good()) break;
    if (!photon.good()) break;
    e_line++;
  }

  n_cap >> n_cap_gd;
  
  std::cout<<"Neutron efficiency in gd: "<< (n_cap_ar + n_cap_gd)/n_tot_gd<< " , with " << n_cap_gd+n_cap_ar <<" neutrons captured, out of "<< n_tot_gd <<" total neutrons \n";
  
  c9->cd();
  neut_e_hist->Draw("");
  neut_e_hist->SetMarkerColor(kBlue);
  neut_e_hist->SetLineColor(kBlue);
  neut_e_hist->GetYaxis()->SetTitle("Counts");
  neut_e_hist->GetXaxis()->SetTitle("Energy (MEv)");
  //rec_gd_e_hist->Draw("PC* SAME");
  rec_gd_e_hist->SetMarkerColor(kRed);
  rec_gd_e_hist->SetLineColor(kRed);
  electron_gd_e_hist->Draw("SAME");
  electron_gd_e_hist->SetMarkerColor(kGreen);
  electron_gd_e_hist->SetLineColor(kGreen);
  neutron_gd_e_hist->Draw("SAME");
  neutron_gd_e_hist->SetMarkerColor(kYellow);
  neutron_gd_e_hist->SetLineColor(kYellow);
  proton_gd_e_hist->Draw("SAME");
  proton_gd_e_hist->SetMarkerColor(kCyan);
  proton_gd_e_hist->SetLineColor(kCyan);
  photon_gd_e_hist->Draw("SAME");
  photon_gd_e_hist->SetMarkerColor(kMagenta);
  photon_gd_e_hist->SetLineColor(kMagenta);


  c9->BuildLegend(0.1,0.9,0.4,0.75);
  //neut_e_hist->SetTitle("Incoming neutrino energy vs energy deposited in the TPC volume (LAr with plastic scintillator)");
  c9->SetTitle("Incoming neutrino energy vs energy deposited in the TPC volume (with plastic scintillator) ");  

  
  out.close();
  electron.close();
  neutron.close();
  proton.close();
  photon.close();
  n_cap.close();
  
  
  electron.open("electron_energy_spectrum.txt",std::fstream::in);
  neutron.open("neutron_energy_spectrum.txt",std::fstream::in);
  proton.open("proton_energy_spectrum.txt",std::fstream::in);
  photon.open("photon_energy_spectrum.txt",std::fstream::in);

    
  TH1F *electron_e_hist = new TH1F("electron_e_hist", "Initial electron energy for an event", 56,0,56);
  TH1F *neutron_e_hist = new TH1F("neutron_e_hist", "Initial electron and neutron energy for an event", 56,0,56);
  TH1F *proton_e_hist = new TH1F("proton_e_hist", "Initial electron, neutron, and proton energy for an event", 56,0,56);
  TH1F *photon_e_hist = new TH1F("photon_e_hist", "Initial electron, neutron, proton, and photon energy for an event", 56,0,56);
  
  e_line = 0;
  Double_t rec_e[10000000], electron_e[10000000], neutron_e[10000000], proton_e[10000000], photon_e[10000000];

  
  while(1){
    
    electron >> electron_e[e_line];
    neutron >> neutron_e[e_line];
    proton >> proton_e[e_line];
    photon >> photon_e[e_line];

    electron_e_hist->Fill(electron_e[e_line]);
    neutron_e_hist->Fill(electron_e[e_line]+neutron_e[e_line]);
    proton_e_hist->Fill(electron_e[e_line]+neutron_e[e_line]+proton_e[e_line]);
    photon_e_hist->Fill(electron_e[e_line]+neutron_e[e_line]+proton_e[e_line]+photon_e[e_line]);
    
    if (!electron.good()) break;
    if (!neutron.good()) break;
    if (!proton.good()) break;
    if (!photon.good()) break;
    e_line++;
  }

  c10->cd();
  neut_e_hist->Draw("");
  neut_e_hist->SetMarkerColor(kBlue);
  neut_e_hist->SetLineColor(kBlue);
  neut_e_hist->GetYaxis()->SetTitle("Counts");
  neut_e_hist->GetXaxis()->SetTitle("Energy (MEv)");
  electron_e_hist->Draw("SAME");
  electron_e_hist->SetMarkerColor(kGreen);
  electron_e_hist->SetLineColor(kGreen);
  neutron_e_hist->Draw("SAME");
  neutron_e_hist->SetMarkerColor(kYellow);
  neutron_e_hist->SetLineColor(kYellow);
  proton_e_hist->Draw("SAME");
  proton_e_hist->SetMarkerColor(kCyan);
  proton_e_hist->SetLineColor(kCyan);
  photon_e_hist->Draw("SAME");
  photon_e_hist->SetMarkerColor(kMagenta);
  photon_e_hist->SetLineColor(kMagenta);


  c10->BuildLegend(0.1,0.9,0.4,0.75);
  neut_e_hist->SetTitle("Incoming neutrino energy and the initial energy of particles produced from the neutrino interaction");
  c10->SetTitle("Incoming neutrino energy vs energy deposited in the TPC volume (with plastic scintillator) ");

}

//Efficiency = (total energy deposited)/(total energy)
