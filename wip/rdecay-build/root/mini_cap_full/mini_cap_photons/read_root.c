{
  gROOT->Reset();
  TCanvas *c1 = new TCanvas();

  ifstream start;
  start.open("photon_starting_energy.txt",std::fstream::in);
  
  ifstream dep;
  dep.open("photon_deposited_energy.txt",std::fstream::in);
    
  TH2F *photon_efficiency_hist = new TH2F("photon_efficiency_hist","Photon efficiency", 56, 0, 56, 56, 0, 56);

  Int_t e_line = 0;
  Double_t e_start[6000000], e_dep[6000000];

    
  while (1){
    
    start >> e_start[e_line];
    dep >> e_dep[e_line];
 
    photon_efficiency_hist->Fill(e_start[e_line],e_dep[e_line]);

    if (!start.good()) break;
    if (!dep.good()) break;
    e_line++;
  }
  
  c1->cd();
  photon_efficiency_hist->Draw("COLZ");
  photon_efficiency_hist->SetTitle("Photon efficiency");
  photon_efficiency_hist->GetYaxis()->SetTitle("Deposited energy (MeV)");
  photon_efficiency_hist->GetXaxis()->SetTitle("Initial energy (MeV)");
}
