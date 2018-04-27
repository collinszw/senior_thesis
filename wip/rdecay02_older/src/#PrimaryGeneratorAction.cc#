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

#include "G4Event.hh"
#include "G4ParticleTable.hh"
#include "G4IonTable.hh"
#include "G4ParticleDefinition.hh"
#include "G4Geantino.hh"
#include "G4SystemOfUnits.hh"
#include "Randomize.hh"

//#include <cmath>

// MARLEY includes
#include "marley/Event.hh"
#include "marley/JSON.hh"
#include "marley/Logger.hh"
#include "marley/RootJSONConfig.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

PrimaryGeneratorAction::PrimaryGeneratorAction(const std::string& config_file_name)
  : G4VUserPrimaryGeneratorAction(),marley_generator_(nullptr) //fParticleGun(0)
{

//Old geant primary particle initialization
/*
  G4int n_particle = 1;
  fParticleGun  = new G4ParticleGun(n_particle);

  //open a HEPevt file, read out an electron, generate a primary //this needs more checks in the future
  fileName = "dar_events.dat";
  inputFile.open(fileName,std::fstream::in);

  if(!inputFile){ //if it's really failed to open the file
    G4Exception("G4HEPEvtInterface::G4HEPEvtInterface","Event0201",FatalException,
		"G4HEPEvtInterface:: cannot open file.");
  }

*/

  //new way
  // Initialize the MARLEY logger
  marley::Logger::Instance().add_stream(std::cout,
    marley::Logger::LogLevel::INFO);

  // Create a new generator object using the configuration stored in
  // the given file
  marley::JSON json = marley::JSON::load_file(config_file_name);
  marley::RootJSONConfig config(json);

  marley_generator_= std::make_unique<marley::Generator>(
    config.create_generator() );

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
/*
PrimaryGeneratorAction::~PrimaryGeneratorAction()
{
  delete fParticleGun;
}
*/
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void PrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{
  /* old way
  G4int NHEP;  // number of entries
  inputFile >> NHEP;

  for( G4int IHEP=0; IHEP<NHEP; IHEP++ ){
    G4int ISTHEP;   // status code
    G4int IDHEP;    // PDG code
    G4int JDAHEP1;  // first daughter
    G4int JDAHEP2;  // last daughter
    G4double PHEP1; // px in GeV
    G4double PHEP2; // py in GeV
    G4double PHEP3; // pz in GeV
    G4double PHEP5; // mass in GeV
      
    inputFile >> ISTHEP >> IDHEP >> JDAHEP1 >> JDAHEP2
	      >> PHEP1 >> PHEP2 >> PHEP3 >> PHEP5;
  
    //should probably be a better check
    if(ISTHEP == 1 && IDHEP == 2112){ //if a neutron

      G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
      G4ParticleDefinition* particle = particleTable->FindParticle(IDHEP);

      fParticleGun->SetParticleDefinition(particle);

      //fParticleGun->SetParticleMass( PHEP5*GeV ); //mass is probably set in Definition
      fParticleGun->SetParticleEnergy(sqrt(pow(PHEP1*GeV,2) + pow(PHEP2*GeV,2) + pow(PHEP3*GeV,2)));
      fParticleGun->SetParticleMomentumDirection(G4ThreeVector(PHEP1*GeV,PHEP2*GeV,PHEP3*GeV));
    }
  }
  */
  //generate a random position within the target

  G4int fid_rad = 40;
  G4int fid_len = 5;
  
  G4int radius = G4UniformRand() * fid_rad;
  G4int theta = G4UniformRand() * 2 * 3.14159265; //probably a better pi somewhere
  G4int z_dir = 1;
  
  if (G4UniformRand() < 0.5){
    z_dir = -1;
  }
  
  G4int x_pos = radius * std::sin(theta) * cm;
  G4int y_pos = radius * std::cos(theta) * cm;
  G4int z_pos = G4UniformRand() * z_dir * fid_len * cm;

  //G4int origin = 0 * cm;
 
  //old way
  //fParticleGun->SetParticlePosition(G4ThreeVector(x_pos,y_pos,z_pos));
  //create vertex
  //fParticleGun->GeneratePrimaryVertex(anEvent);

  //new way
  G4PrimaryVertex* vertex = new G4PrimaryVertex(x_pos, y_pos, z_pos, 0.); // x,y,z,t0

  marley::Event ev = marley_generator_->create_event();

  std::cout << ev << '\n';

  for ( const auto& fp : ev.get_final_particles() ) {

    G4PrimaryParticle* particle = new G4PrimaryParticle( fp->pdg_code(),
      fp->px(), fp->py(), fp->pz(), fp->total_energy() );

    particle->SetCharge( fp->charge() );

    vertex->SetPrimary(particle);
  }
  
  anEvent->AddPrimaryVertex(vertex);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

