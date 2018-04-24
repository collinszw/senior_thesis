//
// ********************************************************************
// * License and Disclaimer                                           *
// *                                                                  *
// * The  Geant4 software  is  copyright of the Copyright Holders  of *
// * the Geant4 Collaboration.  It is provided  under  the terms  and *
// * conditions of the Geant4 Software License,  included in the file *
// * LICENSE and available at  http://cern.ch/geant4/license .  These *
// * include a list of copyright holders.                             *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.  Please see the license in the file  LICENSE  and URL above *
// * for the full disclaimer and the limitation of liability.         *
// *                                                                  *
// * This  code  implementation is the result of  the  scientific and *
// * technical work of the GEANT4 collaboration.                      *
// * By using,  copying,  modifying or  distributing the software (or *
// * any work based  on the software)  you  agree  to acknowledge its *
// * use  in  resulting  scientific  publications,  and indicate your *
// * acceptance of all terms of the Geant4 Software license.          *
// ********************************************************************
//
/// \file EventAction.cc
/// \brief Implementation of the EventAction class
//
// $Id: EventAction.cc 76293 2013-11-08 13:11:23Z gcosmo $
//

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "EventAction.hh"

#include "Run.hh"
#include "HistoManager.hh"

#include "G4Event.hh"
#include "G4RunManager.hh"
#include "G4SystemOfUnits.hh"
#include "G4UnitsTable.hh"


std::ofstream ar_out_file;
std::ofstream ar_electron_file;
std::ofstream ar_neutron_file;
std::ofstream ar_proton_file;
std::ofstream ar_photon_file;
std::ofstream ar_ind_photon_file;

std::ofstream ar_extra_file;

std::ofstream gd_out_file;
std::ofstream gd_electron_file;
std::ofstream gd_neutron_file;
std::ofstream gd_proton_file;
std::ofstream gd_photon_file;
std::ofstream gd_ind_photon_file;
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

EventAction::EventAction()
  :G4UserEventAction(),
   fEdep1(0.), fEdep2(0.), fWeight1(0.), fWeight2(0.),
   fTime0(-1*s)
{
  ar_out_file.open ("recovered_ar_energy_spectrum.txt");
  ar_electron_file.open ("electron_ar_energy_spectrum.txt");
  ar_neutron_file.open ("neutron_ar_energy_spectrum.txt");
  ar_proton_file.open ("proton_ar_energy_spectrum.txt");
  ar_photon_file.open ("photon_ar_energy_spectrum.txt");
  ar_ind_photon_file.open ("individual_photon_ar_energy_spectrum.txt");

  ar_extra_file.open ("extra_ar_energy_spectrum.txt");
  
  gd_out_file.open ("recovered_gd_energy_spectrum.txt");
  gd_electron_file.open ("electron_gd_energy_spectrum.txt");
  gd_neutron_file.open ("neutron_gd_energy_spectrum.txt");
  gd_proton_file.open ("proton_gd_energy_spectrum.txt");
  gd_photon_file.open ("photon_gd_energy_spectrum.txt");
  gd_ind_photon_file.open ("individual_photon_gd_energy_spectrum.txt");
 
  //leaving this for posterity
  //std::ofstream blorfile;
  //blorfile.open("BLOOOORRRR.txt");
  //ar_out_file<<"WHATDAFUQQ\n";
} 

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

EventAction::~EventAction()
{

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void EventAction::BeginOfEventAction(const G4Event*)
{
  fEdep1 = fEdep2 = fWeight1 = fWeight2 = 0.;
  fTime0 = -1*s;

  total_e_ar = 0;
  electron_e_ar = 0;
  neutron_e_ar = 0;
  proton_e_ar = 0;
  photon_e_ar = 0;
  ind_photon_e_ar = 0;

  extra_e_ar = 0;
  
  total_e_gd = 0;
  electron_e_gd = 0;
  neutron_e_gd = 0;
  proton_e_gd = 0;
  photon_e_gd = 0;
  ind_photon_e_gd = 0; 
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void EventAction::AddEdep(G4int iVol, G4double edep,
			  G4double time, G4double weight, G4int PDG, G4int parent)
{
  // initialize t0
  if (fTime0 < 0.) fTime0 = time;
  
  // out of time window ?
  const G4double TimeWindow (1*microsecond); //still trying to figure this thing out
  if (std::fabs(time - fTime0) > TimeWindow) return;
    
  if (iVol == 1) {
    fEdep1 += edep;
    fWeight1 += edep*weight;
    if (PDG == 11){ //electron
      electron_e_ar+=edep;
      total_e_ar+=edep;
    }else if (PDG == 2112){ //neutron
      neutron_e_ar+=edep;
      total_e_ar+=edep;
    }else if (PDG == 2212){ //proton
      proton_e_ar+=edep;
      total_e_ar+=edep;
    }else if (PDG == 22){ //photon
      photon_e_ar+=edep;
      ind_photon_e_ar+=edep;
      total_e_ar+=edep;
      if(parent){ //new photon
	ar_ind_photon_file<<ind_photon_e_ar<<"\n"; //energy spectrum of the photon
	ind_photon_e_ar = 0;
      }
    }
  }
  if (iVol == 2) {
    fEdep2 += edep;
    fWeight2 += edep*weight;
    if (PDG == 11){ //electron
      electron_e_gd+=edep;
      total_e_gd+=edep;
    }else if (PDG == 2112){ //neutron
      neutron_e_gd+=edep;
      total_e_gd+=edep;
    }else if (PDG == 2212){ //proton
      proton_e_gd+=edep;
      total_e_gd+=edep;
    }else if (PDG == 22){ //photon
      photon_e_gd+=edep;
      ind_photon_e_gd+=edep;
      total_e_gd+=edep;
      if(parent){ //new photon
	ar_ind_photon_file<<ind_photon_e_gd<<"\n"; //energy spectrum of the photon
	ind_photon_e_gd = 0;
      }
    }
  }  
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void EventAction::EndOfEventAction(const G4Event* Event)
{
  G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
 
  G4double Etot = fEdep1 + fEdep2;
  G4double Wtot = (fWeight1 + fWeight2)/Etot;
 
  // pulse height in target
  //

  if (fEdep1 > 0.) {
    fWeight1 /= fEdep1;
    //analysisManager->FillH1(0, fEdep1, fWeight1);   
    //old way of collecting event energy
    /*for(G4int i = 0;i<Event->GetPrimaryVertex()->GetNumberOfParticle();i++){
      if(Event->GetPrimaryVertex()->GetPrimary(i)->GetPDGcode() == 11){ //electron
      electron_e_ar += Event->GetPrimaryVertex()->GetPrimary(i)->GetKineticEnergy();
      }else if(Event->GetPrimaryVertex()->GetPrimary(i)->GetPDGcode() == 2112){ //neutron
      neutron_e_ar += Event->GetPrimaryVertex()->GetPrimary(i)->GetKineticEnergy();
      }else if(Event->GetPrimaryVertex()->GetPrimary(i)->GetPDGcode() == 2212){ //proton
      proton_e_ar += Event->GetPrimaryVertex()->GetPrimary(i)->GetKineticEnergy();
      }else if(Event->GetPrimaryVertex()->GetPrimary(i)->GetPDGcode() == 22){//photon
      photon_e_ar += Event->GetPrimaryVertex()->GetPrimary(i)->GetKineticEnergy();
      }else if(Event->GetPrimaryVertex()->GetPrimary(i)->GetPDGcode() == 0){//??
      //std::cout<<"I DON'T KNOW THIS PARTICLE: "<<Event->GetPrimaryVertex()->GetPrimary(i)->GetPDGcode()<<"\n";
      extra_e_ar += Event->GetPrimaryVertex()->GetPrimary(i)->GetKineticEnergy();
      }
      total_e_ar += Event->GetPrimaryVertex()->GetPrimary(i)->GetKineticEnergy();
      }*/
  }
 
  // pulse height in detector
  //   
  if (fEdep2 > 0.) {
    fWeight2 /= fEdep2;
    analysisManager->FillH1(1, fEdep2, fWeight2);

  }

 
  ar_out_file<<total_e_ar<<"\n"; //energy spectrum of the neutrino
  ar_electron_file<<electron_e_ar<<"\n"; //energy spectrum of the electron
  ar_neutron_file<<neutron_e_ar<<"\n"; //energy spectrum of the neutron
  ar_proton_file<<proton_e_ar<<"\n"; //energy spectrum of the proton
  ar_photon_file<<photon_e_ar<<"\n"; //energy spectrum of the photon
  ar_ind_photon_file<<"\n"; //energy spectrum of the photon

  ar_extra_file<<extra_e_ar<<"\n";
 
  gd_out_file<<total_e_gd<<"\n"; //energy spectrum of the neutrino
  gd_electron_file<<electron_e_gd<<"\n"; //energy spectrum of the electron
  gd_neutron_file<<neutron_e_gd<<"\n"; //energy spectrum of the neutron
  gd_proton_file<<proton_e_gd<<"\n"; //energy spectrum of the proton
  gd_photon_file<<photon_e_gd<<"\n"; //energy spectrum of the photon
  ar_ind_photon_file<<"\n"; //energy spectrum of the photon
  
  // total
  //
  analysisManager->FillH1(2, Etot, Wtot);
 
  // threshold in target and detector        
  const G4double Threshold1(10*keV), Threshold2(10*keV);
  
  //coincidence, anti-coincidences 
  //  
  G4bool coincidence       = ((fEdep1 >= Threshold1) && (fEdep2 >= Threshold2));
  G4bool anti_coincidence1 = ((fEdep1 >= Threshold1) && (fEdep2 <  Threshold2));
  G4bool anti_coincidence2 = ((fEdep1 <  Threshold1) && (fEdep2 >= Threshold2)); 

  if (coincidence)       analysisManager->FillH1(3, fEdep2, fWeight2);
  if (anti_coincidence1) analysisManager->FillH1(4, fEdep1, fWeight1);
  if (anti_coincidence2) analysisManager->FillH1(5, fEdep2, fWeight2); 

  // pass energies to Run
  //  
  Run* run = static_cast<Run*>(
			       G4RunManager::GetRunManager()->GetNonConstCurrentRun());
             
  run->AddEdep (fEdep1, fEdep2);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......


