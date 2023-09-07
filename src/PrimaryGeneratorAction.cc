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
//
/// \file PrimaryGeneratorAction.cc
/// \brief Implementation of the B1::PrimaryGeneratorAction class

#include "PrimaryGeneratorAction.hh"


#include "G4LogicalVolumeStore.hh"
#include "G4LogicalVolume.hh"
#include "G4Box.hh"
#include "G4RunManager.hh"
#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "G4SystemOfUnits.hh"
#include "Randomize.hh"

namespace CLYC
{

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

PrimaryGeneratorAction::PrimaryGeneratorAction()
{
//   G4int n_particle = 1;
//   fParticleGun  = new G4ParticleGun(n_particle);

//   // default particle kinematic
//   G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
//   G4String particleName;
//   G4ParticleDefinition* particle
//     = particleTable->FindParticle(particleName="gamma");  
//   fParticleGun->SetParticleDefinition(particle);
//   fParticleGun->SetParticleMomentumDirection(G4ThreeVector(0.,0.,1.));
// // fParticleGun->SetParticleMomentumDirection(GenerateDirection());
//   fParticleGun->SetParticleEnergy(1.*MeV);
  fGPS = new G4GeneralParticleSource(); 
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

PrimaryGeneratorAction::~PrimaryGeneratorAction()
{
  delete fParticleGun;
  // delete fGPS;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void PrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{
  //this function is called at the begining of each event
  //

  // In order to avoid dependence of PrimaryGeneratorAction
  // on DetectorConstruction class we get Envelope volume
  // from G4LogicalVolumeStore.

 /* G4double envSizeXY = 0;
  G4double envSizeZ = 0;

  if (!fEnvelopeBox)
  {
    G4LogicalVolume* envLV
      = G4LogicalVolumeStore::GetInstance()->GetVolume("Envelope");
    if ( envLV ) fEnvelopeBox = dynamic_cast<G4Box*>(envLV->GetSolid());
  }

  if ( fEnvelopeBox ) {
    envSizeXY = fEnvelopeBox->GetXHalfLength()*2.;
    envSizeZ = fEnvelopeBox->GetZHalfLength()*2.;
  }
  else  {
    G4ExceptionDescription msg;
    msg << "Envelope volume of box shape not found.\n";
    msg << "Perhaps you have changed geometry.\n";
    msg << "The gun will be place at the center.";
    G4Exception("PrimaryGeneratorAction::GeneratePrimaries()",
     "MyCode0002",JustWarning,msg);
  }

  G4double size = 0.8;
  G4double x0 = size * envSizeXY * (G4UniformRand()-0.5);
  G4double y0 = size * envSizeXY * (G4UniformRand()-0.5);
  G4double z0 = -0.5 * envSizeZ;*/

  //fParticleGun->SetParticlePosition(G4ThreeVector(-10.*cm,0,0));
  //fParticleGun->SetParticleMomentumDirection(GenerateDirection());   //放在前面初始化使得每次出射方向都相同，放在此处进入循环
  // fParticleGun->SetParticlePosition(GeneratePosition());
  // fParticleGun->GeneratePrimaryVertex(anEvent);
  fGPS->GeneratePrimaryVertex(anEvent);//将fGPS作为粒子源
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
G4ThreeVector PrimaryGeneratorAction::GenerateDirection()
{
  G4double PX,PY,PZ;
  G4double phi = CLHEP::pi/4*rad;
  G4double theta = G4UniformRand()*2*CLHEP::pi*rad;
  PZ = cos(phi);
  PY = sin(phi)*sin(theta);
  PX = sin(phi)*cos(theta);
 // PX = 0.,PY = 0.,PZ = 1.;
  return G4ThreeVector(PX,PY,PZ); 
}
G4ThreeVector PrimaryGeneratorAction::GeneratePosition()
{
  G4double x,y,z;
  y = 0.,z = -5.*cm;
  x = 0.;  //(G4UniformRand()-0.5)*1.905*cm;
  return G4ThreeVector(x,y,z);
}
}


