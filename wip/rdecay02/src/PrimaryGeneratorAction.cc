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
/// \file PrimaryGeneratorAction.cc
/// \brief Implementation of the PrimaryGeneratorAction class
//
//
// $Id: PrimaryGeneratorAction.cc 67268 2013-02-13 11:38:40Z ihrivnac $
//
// 

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "PrimaryGeneratorAction.hh"
#include "HistoManager.hh"

#include "G4Event.hh"
#include "G4ParticleTable.hh"
#include "G4IonTable.hh"
#include "G4ParticleDefinition.hh"
#include "G4Geantino.hh"
#include "G4SystemOfUnits.hh"
#include "Randomize.hh"

// MARLEY includes
#include "marley/Event.hh"
#include "marley/JSON.hh"
#include "marley/Logger.hh"
#include "marley/RootJSONConfig.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

PrimaryGeneratorAction::PrimaryGeneratorAction(const std::string& config_file_name)
  : G4VUserPrimaryGeneratorAction(),marley_generator_(nullptr) //fParticleGun(0)
{
  //these are all initial energy spectrums, by event
  
  neut_file.close();
  e_file.close();
  n_file.close();
  p_file.close();
  y_file.close();

  neut_file.open ("neutrino_energy_spectrum.txt");
  e_file.open ("electron_energy_spectrum.txt");
  n_file.open ("neutron_energy_spectrum.txt");
  p_file.open ("proton_energy_spectrum.txt");
  y_file.open ("photon_energy_spectrum.txt");
  ind_y_file.open ("individual_photon_energy_spectrum.txt");

  n_count_file.open ("neutron_count.txt");
  p_count_file.open ("proton_count.txt");
  
  /*
  //old way
  e_start_energy.close();
  e_start_energy.open ("photon_starting_energy.txt");
  
  G4int n_particle = 1;
  fParticleGun  = new G4ParticleGun(n_particle);
  k_energy = 0.5;
  event_count = 0;
  */
  //new way
  
  fPrimaryParticle = new G4PrimaryParticle();
  
  // Initialize the MARLEY logger
  marley::Logger::Instance().add_stream(std::cout,
    marley::Logger::LogLevel::INFO);

  // Create a new generator object using the configuration stored in
  // the given file
  marley::JSON json = marley::JSON::load_file(config_file_name);
  marley::RootJSONConfig config(json);

  marley_generator_= std::make_unique<marley::Generator>(config.create_generator() );
  
  
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

PrimaryGeneratorAction::~PrimaryGeneratorAction()
{
  /*
  delete fParticleGun;
  e_start_energy.close();
  */
  neut_file.close();
  e_file.close();
  n_file.close();
  p_file.close();
  y_file.close();
  delete fPrimaryParticle;
  
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void PrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{
  //generate a random position within the target
  //mini captain
  /*
  G4int fid_rad = 50;
  G4int fid_len = 16;
  //G4int particle_to_check = 22; //photons
  
  G4double radius = G4UniformRand() * fid_rad;
  G4double theta = G4UniformRand() * 2 * 3.14159265; //probably a better pi somewhere
  G4int z_dir = 1;
  
  if (G4UniformRand() < 0.5){
    z_dir = -1;
  }
  
  G4double x_pos = radius * std::sin(theta) * cm;
  G4double y_pos = radius * std::cos(theta) * cm;
  G4double z_pos = G4UniformRand() * z_dir * fid_len * cm;

  */

  //DUNE
  
  G4double x_pos = G4UniformRand() * 14.5 * m;
  G4double y_pos = G4UniformRand() * 12 * m;
  G4double z_pos = G4UniformRand() * 58 * m;
  
   
  //old
  /*
  event_count++;
  if(event_count % 100000 == 0){ //10,000 events per energy, max e == 55.5
    k_energy +=1;
  }

  
  
  
  G4double norm_const = 0;
  
  G4double x_dir = 1;
  G4double x_mag = G4UniformRand();

  if(G4UniformRand() >= 0.5){
    x_dir *= -1;
  }

  G4double y_dir = 1;
  G4double y_mag = G4UniformRand();

  if(G4UniformRand() >= 0.5){
    y_dir *= -1;
  }

  G4int z_dir = 1;
  G4double z_mag = G4UniformRand();

  if(G4UniformRand() >= 0.5){
    z_dir *= -1;
  }

  norm_const = 1/(sqrt(pow(x_mag,2)+pow(y_mag,2)+pow(z_mag,2)));

  G4double x_mom = x_dir * x_mag * norm_const * k_energy;
  G4double y_mom = y_dir * y_mag * norm_const * k_energy;
  G4double z_mom = z_dir * z_mag * norm_const * k_energy;

  e_start_energy << sqrt(pow(x_mom,2) + pow(y_mom,2) + pow(z_mom,2)) << "\n";
  
  G4int PDG_code = 22; //electrons = 11; photons = 22
  G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
  G4ParticleDefinition* particle = particleTable->FindParticle(PDG_code);
  fParticleGun->SetParticleDefinition(particle);

  fParticleGun->SetParticleEnergy(sqrt(pow(x_mom,2) + pow(y_mom,2) + pow(z_mom,2)));
  fParticleGun->SetParticleMomentumDirection(G4ThreeVector(x_mom,y_mom,z_mom));
  
  fParticleGun->SetParticlePosition(G4ThreeVector(x_pos,y_pos,z_pos));
  //create vertex
  fParticleGun->GeneratePrimaryVertex(anEvent);

  */
  //new way
  
  vertex = new G4PrimaryVertex(x_pos, y_pos, z_pos, 0); // x,y,z,t0

  marley::Event ev = marley_generator_->create_event();

  G4double neutrino_energy;
  for ( const auto& ip: ev.get_initial_particles() ){
    if (ip->pdg_code() == 12){ //electron neutrino
      neutrino_energy = ip->total_energy();
    }
  }
  
  neut_file<<neutrino_energy<<"\n"; //energy spectrum of the neutrino
  
  //std::cout << ev << '\n'; 


  electron_e = 0;
  neutron_e = 0;
  proton_e = 0;
  photon_e = 0;
  n_count = 0;
  p_count = 0;
  
  for ( const auto& fp : ev.get_final_particles() ) {
    if (fp->pdg_code() == 11){ //electron
      electron_e += fp->kinetic_energy();
    }else if (fp->pdg_code() == 2112){ //neutron
      neutron_e += fp->kinetic_energy();
      n_count++;
    }else if (fp->pdg_code() == 2212){ //proton
      proton_e += fp->kinetic_energy();
      p_count++;
    }else if (fp->pdg_code() == 22){ //photon
      ind_photon_e = fp->kinetic_energy();
      photon_e += ind_photon_e;
      ind_y_file<<photon_e<<"\n"; //energy spectrum of the photon
    }else{
      //std::cout<<"I DON'T KNOW THIS PARTICLE: "<<fp->pdg_code()<<"\n";
    }
    G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
    G4ParticleDefinition* particledef = particleTable->FindParticle(fp->pdg_code());
    fPrimaryParticle = new G4PrimaryParticle(particledef,fp->px(), fp->py(), fp->pz(), fp->total_energy());
    
    fPrimaryParticle->SetCharge(fp->charge());
    
    vertex->SetPrimary(fPrimaryParticle);
  }
  
  anEvent->AddPrimaryVertex(vertex);

  e_file<<electron_e<<"\n"; //energy spectrum of the electron
  n_file<<neutron_e<<"\n"; //energy spectrum of the neutron
  p_file<<proton_e<<"\n"; //energy spectrum of the proton
  y_file<<photon_e<<"\n"; //energy spectrum of the photon
  ind_y_file<<"\n"; //energy spectrum of the photon
  n_count_file<<n_count<<"\n"; //number of neutrons per event
  p_count_file<<n_count<<"\n"; //number of neutrons per event
  
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

