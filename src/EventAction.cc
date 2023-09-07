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
/// \file EventAction.cc
/// \brief Implementation of the B1::EventAction class

#include "EventAction.hh"
#include "RunAction.hh"
// #include "TrackerHit.hh"


#include "G4Event.hh"
#include "G4RunManager.hh"
#include "G4SDManager.hh"
#include "G4Scintillation.hh"
#include "G4THitsCollection.hh"
#include "G4VHit.hh"
#include "G4ProcessTable.hh"

#include "G4Trajectory.hh"

#include "G4PrimaryParticle.hh"

#include "G4THitsMap.hh"
#include "G4SystemOfUnits.hh"

namespace CLYC
{

using namespace std;
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
extern G4double EnergyCLYC,EnergySi;
extern std::vector<double> timelist1,timelist2;
extern G4String ParticleName;
extern G4int ParentID;
extern G4int Charge;
extern G4double originalE;
EventAction::EventAction(RunAction* runAction)
: fRunAction(runAction)
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

EventAction::~EventAction()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void EventAction::BeginOfEventAction(const G4Event* event)
{
  fEdep = 0.;
  // 获取当前事件的ID
  G4int eventID = event->GetEventID();
  // G4cout << "Starting event: " << eventID << G4endl;

  EnergyCLYC = 0.;
  EnergySi = 0.;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......



void EventAction::EndOfEventAction(const G4Event* event)
{
  
  // Get the scintillator sensitive detector

  // accumulate statistics in run action


G4double StartTime = timelist1[0];
G4double StopTime = timelist2[0];
timelist1.clear();
timelist2.clear();

// G4cout << "........................waveData......................"<<G4endl;

// G4cout << "EdepSi :  " << EnergySi/eV << " eV"<< "  EdepCLYC : " << EnergyCLYC /eV <<" eV"
//        << " start :" << StartTime/ns << "ns " << " stop :"<< StopTime /ns<< "ns "
//        << " TOF = " << StopTime/ns - StartTime/ns << "ns"
// <<G4endl;

std::fstream file("Particle.txt", std::ios::app);
//if (ParentID == 0){
  file << EnergySi/MeV  << "  "<< EnergyCLYC /MeV << "  "<<StopTime/ns - StartTime/ns<<"  "<<ParticleName<<"  "<<Charge<<"  "<< originalE /MeV <<G4endl;
//}
file.close();

}
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......


