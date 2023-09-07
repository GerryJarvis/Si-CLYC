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
/// \file SteppingAction.cc
/// \brief Implementation of the B1::SteppingAction class

#include "SteppingAction.hh"
#include "EventAction.hh"
#include "DetectorConstruction.hh"

#include "G4Step.hh"
#include "G4Event.hh"
#include "G4RunManager.hh"
#include "G4LogicalVolume.hh"
#include "G4UnitsTable.hh"
#include "G4SteppingManager.hh"

#include "G4Scintillation.hh"
#include "G4SystemOfUnits.hh"

#include <vector>


namespace CLYC
{
G4String ParticleName;
G4double EnergyCLYC;
G4double EnergySi;
G4double EdepCLYC,EdepSi;
G4double StartTime,StopTime;
G4double time1,time2;
std::vector<double> timelist1,timelist2;
G4int ParentID;
G4int Charge;
G4double originalE;
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

SteppingAction::SteppingAction(EventAction* eventAction)
: fEventAction(eventAction)
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

SteppingAction::~SteppingAction()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void SteppingAction::UserSteppingAction(const G4Step* aStep)
{


  G4Track* track = aStep->GetTrack();
  ParentID = track->GetParentID();


  G4String preVol = aStep->GetPreStepPoint()->GetTouchableHandle()->GetVolume()->GetLogicalVolume()->GetName();
 // ParticleName = track->GetDefinition()->GetParticleName();
if (ParentID == 0){
  if (preVol == "Si_LV" ){//&& postVol != "logicSi" && postVol == "Scint_LV"
    time1 = track->GetGlobalTime();
    if (timelist2.size() == 0 || time1 < static_cast<double>(*std::min_element(timelist2.begin(), timelist2.end()))){
      timelist1.push_back(time1);
      EdepSi = aStep->GetTotalEnergyDeposit();
      EnergySi += EdepSi;
      ParticleName = track->GetDefinition()->GetParticleName();
      Charge = track->GetDefinition()->GetPDGCharge();
      originalE = track->GetKineticEnergy();
    }else{
      return ;
    }
    
   // G4cout<<"Particle Name :"<<ParticleName<<G4endl;
    // G4cout<<"startTime : "<<StartTime << "  edepStepSi : " <<EdepSi<<G4endl;
  }else if (preVol == "CLYC_LV" ){
    time2 = track->GetGlobalTime();
    timelist2.push_back(time2);
    EdepCLYC = aStep->GetTotalEnergyDeposit();
    EnergyCLYC += EdepCLYC;
    // G4cout<<"stopTime : "<<StopTime << "  edepStepCLYC : " <<EdepCLYC<<G4endl;
  }
}

  
  // else  if (preVol == "Be_LV"){
  //   G4cout<<"Volumn Name : " << preVol<<G4endl;
  // }


  // G4Track *track = aStep->GetTrack();
  // G4String particleName = track->GetDefinition()->GetParticleName();
  // G4double energy = track->GetKineticEnergy();
  // G4double stepLength = aStep->GetStepLength();
  // G4double EnergyDeposit = aStep->GetTotalEnergyDeposit();
  // G4ThreeVector position = track->GetPosition();
  // G4double time = track->GetGlobalTime();
  // G4int parentId = track->GetParentID();
  // G4int trackId = track->GetTrackID();
  // // G4double totalEnergy = track->GetTotalEnergy();
  // G4String VolumeName = aStep->GetPreStepPoint()->GetTouchableHandle()->GetVolume()->GetLogicalVolume()->GetName();


  //    G4cout << particleName <<" from track " << parentId<<"  "
  //       << ", Its TrackID :" << trackId
  //       << ", Energy: " << energy / eV << " eV"
  //       << ", Step length: " << stepLength / mm << " mm"
  //       << ", Energy Deposit: " << EnergyDeposit / eV << " eV"
  //       << ", Position: (" << position.x() / mm << ", " << position.y() / mm << ", " << position.z() / mm << ") mm"
  //       << ", Time: " << time / ns << " ns"
  //       << ", VolumeName: " << VolumeName;

  //          if(track->GetNextVolume()){
  //     G4cout << ", NextVolume: " << track->GetVolume()->GetName();
  //   } else {
  //     G4cout << ", OutOfWorld";
  //   }
  //   G4cout   << G4endl;

}
  
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo



