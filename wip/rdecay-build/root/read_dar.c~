{
  //read the dar file to calculate and plot particle energy
  TFile *MyFile1 = new TFile("e_orig.root","RECREATE");
  

  TH1F *H10 = new TH1F("H10","Energy deposit (MeV) in the target (electrons total energy)", 100, 0, 50);

  ifstream in;

  in.open("dar_events.dat",std::fstream::in);
  
  Float_t energy,NHEP,ISTHEP,IDHEP,JDAHEP1,JDAHEP2,PHEP1,PHEP2,PHEP3,PHEP5;
  
  while(1){
    in >> NHEP;
    if (!in.good()) break;
    for(int i = 0; i < NHEP; i++){
      in >> ISTHEP >> IDHEP >> JDAHEP1 >> JDAHEP2 >> PHEP1 >> PHEP2 >> PHEP3 >> PHEP5;
      energy = sqrt(pow(PHEP1*1000,2)+pow(PHEP2*1000,2)+pow(PHEP3*1000,2));
      if (IDHEP == 11) H10->Fill(energy);
    }
  }

  in.close();

  MyFile1->Write();
  
}
