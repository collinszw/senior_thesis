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
/// \file PrimaryGeneratorAction.hh
/// \brief Definition of the PrimaryGeneratorAction class
//
//
// $Id: PrimaryGeneratorAction.hh 66241 2012-12-13 18:34:42Z gunter $
//
// 

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#ifndef PrimaryGeneratorAction_h
#define PrimaryGeneratorAction_h 1

// standard library includes
#include <memory>

#include <iostream>
#include <fstream>
#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4ParticleGun.hh"
#include "globals.hh"

// MARLEY includes
#include "marley/Generator.hh"

class G4Event;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class PrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction
{
  /*
public:
  PrimaryGeneratorAction();    
  ~PrimaryGeneratorAction();

public:
  virtual void GeneratePrimaries(G4Event*);
  G4ParticleGun* GetParticleGun() {return fParticleGun;};

private:
  G4ParticleGun*  fParticleGun;        //pointer a to G4 service class

  G4String fileName;
  std::ifstream inputFile;
  */

  //new
public:
  PrimaryGeneratorAction(const std::string& config_file_name);
  ~PrimaryGeneratorAction();
  
  virtual void GeneratePrimaries(G4Event*) override;
  G4PrimaryParticle* GetPrimaryParticle() {return fPrimaryParticle;};
  
private:
  G4double k_energy;
  G4ParticleGun*  fParticleGun;        //pointer a to G4 service class
  G4int event_count;
  std::ofstream e_start_energy; //just electrons tonight
  //std::ofstream y_start_energy;
  //std::ofstream n_start_energy;
  
  std::ofstream neut_file;
  std::ofstream e_file;
  std::ofstream n_file;
  std::ofstream p_file;
  std::ofstream y_file;
  std::ofstream ind_y_file;

  std::ofstream n_count_file;
  std::ofstream p_count_file;

  G4double total_e;
  G4double electron_e;
  G4double neutron_e;
  G4double proton_e;
  G4double photon_e;
  G4double ind_photon_e;
  
  G4double n_count;
  G4double p_count;
  
  G4PrimaryParticle*  fPrimaryParticle;        //pointer a to G4 service class
  G4PrimaryVertex* vertex; 
protected:
    // Pointer to the MARLEY event generator object
  std::unique_ptr<marley::Generator> marley_generator_;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif


