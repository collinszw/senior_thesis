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
/// \file DetectorConstruction.cc
/// \brief Implementation of the DetectorConstruction class
//
// $Id: DetectorConstruction.cc 70755 2013-06-05 12:17:48Z ihrivnac $
//

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "DetectorConstruction.hh"
#include "DetectorMessenger.hh"

#include "G4Material.hh"
#include "G4NistManager.hh"

#include "G4Polyhedra.hh"
#include "G4Box.hh"
#include "G4SubtractionSolid.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"

#include "G4GeometryManager.hh"
#include "G4PhysicalVolumeStore.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4SolidStore.hh"
#include "G4RunManager.hh"

#include "G4SystemOfUnits.hh"
#include "G4PhysicalConstants.hh"
#include "G4UnitsTable.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

DetectorConstruction::DetectorConstruction()
  :G4VUserDetectorConstruction(),
   fTargetMater(0), fLogicTarget(0),
   fDetectorMater(0), fLogicDetector(0), 
   fWorldMater(0), fPhysiWorld(0),
   fDetectorMessenger(0)
{
  fTargetLength      = 32*cm; //target is argon
  fTargetRadius      = 50*cm;
  fDetectorLength    = 32*cm; //detector is doped plastic 
  fDetectorThickness = 14*cm;
  
  fWorldLength = std::max(fTargetLength,fDetectorLength);
  fWorldRadius = fTargetRadius + fDetectorThickness;
      
  DefineMaterials();
    
  fDetectorMessenger = new DetectorMessenger(this);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

DetectorConstruction::~DetectorConstruction()
{ delete fDetectorMessenger;}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4VPhysicalVolume* DetectorConstruction::Construct()
{
  return ConstructVolumes();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void DetectorConstruction::DefineMaterials()
{
  // build materials
 
  G4Element* N  = new G4Element("Nitrogen", "N", 7, 14.01*g/mole);
  G4Element* O  = new G4Element("Oxygen",   "O", 8, 16.00*g/mole);
  //
  G4int ncomponents; G4double fractionmass;      
  G4Material* Air20 = new G4Material("Air", 1.205*mg/cm3, ncomponents=2, kStateGas, 293.*kelvin, 1.*atmosphere);
  Air20->AddElement(N, fractionmass=0.7);
  Air20->AddElement(O, fractionmass=0.3);

  G4double density = 1.390*g/cm3;
  G4double a = 39.95*g/mole;
  G4Material* lAr = new G4Material("liquidArgon", 18., a, density);


  a = 1.01*g/mole;
  G4Element* elH = new G4Element("Hydrogen", "H2", 1., a);
    
  a = 12.01*g/mole;
  G4Element* elC = new G4Element("Carbon", "C", 6., a);

  density = 1.032*g/cm3;
  G4Material* Polystyrene = new G4Material("Polystyrene", density,  ncomponents=2, kStateSolid, 293.*kelvin, 1.*atmosphere);
  
  Polystyrene->AddElement(elH, 8);
  Polystyrene->AddElement(elC, 8);

  a = 157.25*g/mole;
  G4Element* Gd = new G4Element("Gadolinium", "Gd", 64., a);

  density = 1.238*g/cm3;
  G4Material* Polystyrene_Gd = new G4Material("Gadolinium doped polystyrene", density, ncomponents=2, kStateSolid, 293.*kelvin, 1.*atmosphere);
  Polystyrene_Gd->AddMaterial(Polystyrene, fractionmass=0.97); //used to be .97
  Polystyrene_Gd->AddElement(Gd, fractionmass=0.03); //used to be .03
    

  fWorldMater = Air20;
  fDetectorMater = Air20;//Polystyrene_Gd; //needs to be  polystyrene + Gd
  fTargetMater = lAr;  

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4VPhysicalVolume* DetectorConstruction::ConstructVolumes()
{
  // Cleanup old geometry
  G4GeometryManager::GetInstance()->OpenGeometry();
  G4PhysicalVolumeStore::GetInstance()->Clean();
  G4LogicalVolumeStore::GetInstance()->Clean();
  G4SolidStore::GetInstance()->Clean();
  
  // World
  //
  // (re) compute World dimensions if necessary
  fWorldLength = std::max(fTargetLength,fDetectorLength);
  fWorldRadius = fTargetRadius + fDetectorThickness;

  G4double* zPlane = new G4double[2];
  G4double* rInner = new G4double[2];
  G4double* rOuter = new G4double[2];

  zPlane[0] = -0.5*fWorldLength;
  zPlane[1] = 0.5*fWorldLength;
  for(int i = 0; i<2; i++){
    rInner[i] = 0;
    rOuter[i] = fWorldRadius;
  }

  //mini captain
  /*
  G4Polyhedra* sWorld = new G4Polyhedra( "World",//const G4String& pName,
					 0.,     //G4double        phiStart,
					 twopi,  //G4double        phiTotal,
					 6,      //G4int           numSide,
					 2,      //G4int           numZPlanes,
					 zPlane, //const G4double  zPlane[],
					 rInner, //const G4double  rInner[],
					 rOuter);//const G4double  rOuter[] )
  
  */
  //DUNE
  
  G4Box* sWorld = new G4Box("World", //name
			    15.5*m,
			    13*m,
			    59*m);
                   
  G4LogicalVolume*
    lWorld = new G4LogicalVolume(sWorld,                  //shape
				 fWorldMater,               //material
				 "World");                  //name

  fPhysiWorld = new G4PVPlacement(0,                    //no rotation
				  G4ThreeVector(),            //at (0,0,0)
				  lWorld,                     //logical volume
				  "World",                    //name
				  0,                          //mother volume
				  false,                      //no boolean operation
				  0);                         //copy number
                            
  // Target
  //

  zPlane[0] = -0.5*fTargetLength;
  zPlane[1] = 0.5*fTargetLength;
  for(int i = 0; i<2; i++){
    rInner[i] = 0;
    rOuter[i] = fTargetRadius;
  }

  //mini captain
  /*
  G4Polyhedra* sTarget = new G4Polyhedra( "Target",//const G4String& pName,
					  0.,     //G4double        phiStart,
					  twopi,  //G4double        phiTotal,
					  6,      //G4int           numSide,
					  2,      //G4int           numZPlanes,
					  zPlane, //const G4double  zPlane[],
					  rInner, //const G4double  rInner[],
					  rOuter);//const G4double  rOuter[] )
  
  */
  //DUNE
  
  G4Box* sTarget = new G4Box("Target", //name
			      14.5*m,
			      12*m,
			      58*m);
  

  fLogicTarget = new G4LogicalVolume(sTarget,           //shape
				     fTargetMater,              //material
				     "Target");                 //name
                               
  new G4PVPlacement(0,                         //no rotation
		    G4ThreeVector(),             //at (0,0,0)
		    fLogicTarget,                //logical volume
		    "Target",                    //name
		    lWorld,                      //mother  volume
		    false,                       //no boolean operation
		    0);                          //copy number

  // Detector
  //

  zPlane[0] = -0.5*fDetectorLength;
  zPlane[1] = 0.5*fDetectorLength;
  for(int i = 0; i<2; i++){
    rInner[i] = fTargetRadius;
    rOuter[i] = fTargetRadius+fDetectorThickness;
  }
    
  //mini captain
  /*
  G4Polyhedra* sDetector = new G4Polyhedra( "Detector",//const G4String& pName,
					    0.,     //G4double        phiStart,
					    twopi,  //G4double        phiTotal,
					    6,      //G4int           numSide,
					    2,      //G4int           numZPlanes,
					    zPlane, //const G4double  zPlane[],
					    rInner, //const G4double  rInner[],
					    rOuter);//const G4double  rOuter[] )
  				       
  */
  //DUNE
  G4SubtractionSolid *sDetector = new G4SubtractionSolid("Detector",sWorld,sTarget);
 
  fLogicDetector = new G4LogicalVolume(sDetector,       //shape
				       fDetectorMater,            //material
				       "Detector");               //name
                               
  new G4PVPlacement(0,                         //no rotation
		    G4ThreeVector(),             //at (0,0,0)
		    fLogicDetector,              //logical volume
		    "Detector",                  //name
		    lWorld,                      //mother  volume
		    false,                       //no boolean operation
		    0);                          //copy number


  PrintParameters();
  
  //always return the root volume
  //
  return fPhysiWorld;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void DetectorConstruction::PrintParameters()
{
  G4cout << "\n Target : Length = " << G4BestUnit(fTargetLength,"Length")
         << " Radius = " << G4BestUnit(fTargetRadius,"Length")  
         << " Material = " << fTargetMater->GetName();
  G4cout << "\n Detector : Length = " << G4BestUnit(fDetectorLength,"Length")
         << " Tickness = " << G4BestUnit(fDetectorThickness,"Length")  
         << " Material = " << fDetectorMater->GetName() << G4endl;          
  G4cout << "\n" << fTargetMater << "\n" << fDetectorMater << G4endl;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void DetectorConstruction::SetTargetMaterial(G4String materialChoice)
{
  // search the material by its name
  G4Material* pttoMaterial =
    G4NistManager::Instance()->FindOrBuildMaterial(materialChoice);   
  
  if (pttoMaterial) { 
    fTargetMater = pttoMaterial;
    if(fLogicTarget) { fLogicTarget->SetMaterial(fTargetMater); }
    G4RunManager::GetRunManager()->PhysicsHasBeenModified();
  } else {
    G4cout << "\n--> warning from DetectorConstruction::SetTargetMaterial : "
           << materialChoice << " not found" << G4endl;
  }              
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void DetectorConstruction::SetDetectorMaterial(G4String materialChoice)
{
  // search the material by its name
  G4Material* pttoMaterial =
    G4NistManager::Instance()->FindOrBuildMaterial(materialChoice);   
  
  if (pttoMaterial) { 
    fDetectorMater = pttoMaterial;
    if(fLogicDetector) { fLogicDetector->SetMaterial(fDetectorMater); }
    G4RunManager::GetRunManager()->PhysicsHasBeenModified();
  } else {
    G4cout << "\n--> warning from DetectorConstruction::SetDetectorMaterial : "
           << materialChoice << " not found" << G4endl;
  }              
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void DetectorConstruction::SetTargetRadius(G4double value)
{
  fTargetRadius = value;
  G4RunManager::GetRunManager()->ReinitializeGeometry();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void DetectorConstruction::SetTargetLength(G4double value)
{
  fTargetLength = value;
  G4RunManager::GetRunManager()->ReinitializeGeometry();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void DetectorConstruction::SetDetectorThickness(G4double value)
{
  fDetectorThickness = value;
  G4RunManager::GetRunManager()->ReinitializeGeometry();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void DetectorConstruction::SetDetectorLength(G4double value)
{
  fDetectorLength = value;
  G4RunManager::GetRunManager()->ReinitializeGeometry();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4double DetectorConstruction::GetTargetLength()
{
  return fTargetLength;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4double DetectorConstruction::GetTargetRadius()
{
  return fTargetRadius;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4Material* DetectorConstruction::GetTargetMaterial()
{
  return fTargetMater;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4LogicalVolume* DetectorConstruction::GetLogicTarget()
{
  return fLogicTarget;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4double DetectorConstruction::GetDetectorLength()
{
  return fDetectorLength;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4double DetectorConstruction::GetDetectorThickness()
{
  return fDetectorThickness;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4Material* DetectorConstruction::GetDetectorMaterial()
{
  return fDetectorMater;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4LogicalVolume* DetectorConstruction::GetLogicDetector()
{
  return fLogicDetector;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
