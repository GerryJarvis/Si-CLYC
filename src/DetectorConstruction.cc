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
/// \file DetectorConstruction.cc
/// \brief Implementation of the B1::DetectorConstruction class

#include "DetectorConstruction.hh"
// #include "TrackerSD.hh"

#include "G4RunManager.hh"
#include "G4NistManager.hh"
#include "G4Box.hh"
#include "G4Cons.hh"
#include "G4Orb.hh"
#include "G4Sphere.hh"
#include "G4Trd.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"
#include "G4Tubs.hh"

#include "G4OpticalSurface.hh"
#include "G4LogicalBorderSurface.hh"

#include "G4SDManager.hh"
#include "G4UserLimits.hh"

namespace CLYC
{

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

DetectorConstruction::DetectorConstruction()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

DetectorConstruction::~DetectorConstruction()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4VPhysicalVolume* DetectorConstruction::Construct()
{
  G4bool fCheckOverlaps = true;
  // Get nist material manager
  G4NistManager* nist = G4NistManager::Instance();

  //CLYC材料
  G4Element* elCs = new G4Element("Caesium","Cs",55.,132.905*g/mole);
  G4Element* elLi = new G4Element("Lithium","Li",3.,6.94003*g/mole);
  G4Element* elY = new G4Element("Yttrium","Y",39.,88.9058*g/mole);
  G4Element* elCl = new G4Element("Chlorine","Cl",17.,35.4527*g/mole);
  G4Element* elCe = new G4Element("Cerium","Ce",58.,140.115*g/mole);   //铈单质密度6.773g/cm3
  G4double density = 3.203*g/cm3;
  G4Material* CLYC = new G4Material("CLYC",density,4);
  CLYC->AddElement(elCs,2);
  CLYC->AddElement(elLi,1);
  CLYC->AddElement(elY,1);
  CLYC->AddElement(elCl,6);
  G4Material* CLYC_Ce = new G4Material("CLYC_Ce",3.31*g/cm3,2);
  CLYC_Ce->AddElement(elCe,3*perCent);   //3%铈掺杂 经查文献
  CLYC_Ce->AddMaterial(CLYC,97*perCent); 

  //CLYC的光学属性
  const G4int nEntries = 2;  
  G4double PhotonEnergy[nEntries] = {4.417*eV,7.228*eV};//275nm--450nm   E = hc/lambda

  G4double CLYCReflectionIndex[nEntries] = {1.81,1.81};  
  G4double CLYCAbsordptioinLength[nEntries] = {3.42*cm,3.42*cm};  // 使用了文件给出的radiation length
  G4double ScintFast[nEntries] = {0.0,1.0};

  G4MaterialPropertiesTable* CLYCMPT = new G4MaterialPropertiesTable();

  G4MaterialPropertyVector* rIndex = new G4MaterialPropertyVector(PhotonEnergy,CLYCReflectionIndex,nEntries);
  G4MaterialPropertyVector* absLength = new G4MaterialPropertyVector(PhotonEnergy,CLYCAbsordptioinLength,nEntries);
  G4MaterialPropertyVector* fComponent = new G4MaterialPropertyVector(PhotonEnergy,ScintFast,nEntries);


// 随波长变化的属性
  CLYCMPT->AddProperty("RINDEX",rIndex,true);        //折射率,true,true,true,true,true,true,true,true
  CLYCMPT->AddProperty("ABSLENGTH",absLength,true);  //吸收长度
  CLYCMPT->AddProperty("FCOMPONENT",fComponent,true);           //快成分

// 本征属性
  CLYCMPT->AddConstProperty("SCINTILLATIONYIELD",20./keV,true);                         //光产额
  CLYCMPT->AddConstProperty("RESOLUTIONSCALE",1.,true);                                 //晶体本征分辨
  CLYCMPT->AddConstProperty("FTIMECONSTANT",50.*ns,true);                             //时间常数
  CLYCMPT->AddConstProperty("YIELDRATIO",1.,true);                                      //快慢响应之比

  CLYC_Ce->SetMaterialPropertiesTable(CLYCMPT);



  // Si
  G4Material *Si = nist->FindOrBuildMaterial("G4_Si");

  // Be
  G4Material *Be = nist->FindOrBuildMaterial("G4_Be");

// World
  //
  G4double world_sizeXY = 50*cm;
  G4double world_sizeZ  = 50*cm;
  G4Material* world_mat = nist->FindOrBuildMaterial("G4_AIR");  //   G4_Galactic

  G4Box* solidWorld =
    new G4Box("World",                       //its name
       0.5*world_sizeXY, 0.5*world_sizeXY, 0.5*world_sizeZ);     //its size

  G4LogicalVolume* logicWorld =
    new G4LogicalVolume(solidWorld,          //its solid
                        world_mat,           //its material
                        "World");            //its name

  G4VPhysicalVolume* physWorld =
    new G4PVPlacement(0,                     //no rotation
                      G4ThreeVector(),       //at (0,0,0)
                      logicWorld,            //its logical volume
                      "World",               //its name
                      0,                     //its mother  volume
                      false,                 //no boolean operation
                      0,                     //copy number
                      fCheckOverlaps);        //overlaps checking


 
G4double distance = 10*cm;

//CLYC实体    
//
  G4ThreeVector pos0 = G4ThreeVector(0,0,distance);
  
  G4double scint_rmin = 0.*cm, scint_rmax = 1.9*cm;
  G4double scint_z = 2.25*cm;
  G4double scint_phimin = 0.*deg,scint_phimax = 360.*deg;
  G4Tubs* solidScint = new G4Tubs("ScintSd",scint_rmin,scint_rmax,scint_z,scint_phimin,scint_phimax);
  
  G4LogicalVolume* logicScint = new G4LogicalVolume(solidScint,CLYC_Ce,"CLYC_LV");    //材料设置为CLYC_Ce
  G4VPhysicalVolume* physScint = new G4PVPlacement(0,pos0,logicScint,"CLYCDetector",logicWorld,false,0,fCheckOverlaps); 

// 2cm厚聚乙烯慢化剂
  // G4Material* moder_mat = nist->FindOrBuildMaterial("G4_POLYETHYLENE");
  // G4ThreeVector pos_moder = G4ThreeVector(0,0,distance-2.095*cm - 20*cm);

  // G4double moder_XY = 2.105*cm;
  // G4double moder_Z = 0.1*cm;
  // G4Box* solidModer = new G4Box("Moder",moder_XY,moder_XY,moder_Z);
  
  // G4LogicalVolume* logicModer =
  //   new G4LogicalVolume(solidModer,          
  //                       moder_mat,           //its material
  //                       "Moder");            //its name

  // G4VPhysicalVolume* physModer =
  //   new G4PVPlacement(0,                     //no rotation
  //                     pos_moder ,       //at (0,0,0)
  //                     logicModer,            //its logical volume
  //                     "Moder",               //its name
  //                     logicWorld,                     //its mother  volume
  //                     false,                 //no boolean operation
  //                     0,                     //copy number
  //                     fCheckOverlaps);        //overlaps checking

//铝入射窗entrWin1,entrWin2
  G4Material* entrWin_mat = nist->FindOrBuildMaterial("G4_Al");
  G4ThreeVector pos_entrWin = G4ThreeVector(0,0,distance-2.25*cm-0.05*cm);//
   
  G4double entrWin1_rmin = 1.9*cm, entrWin1_rmax = 2.275*cm;
  G4double entrWin1_z = 2.25*cm;
  G4double entrWin_phimin = 0.*deg,entrWin_phimax = 360.*deg;
  G4Tubs* solidentrWin1 = new G4Tubs("entrWin1",entrWin1_rmin,entrWin1_rmax,entrWin1_z,entrWin_phimin,entrWin_phimax);
  
  G4LogicalVolume* logicentrWin1 = new G4LogicalVolume(solidentrWin1,entrWin_mat,"entrWin1");
  
  G4VPhysicalVolume* physentrWin1 = new G4PVPlacement(0,pos0,logicentrWin1,"entrWin1",logicWorld,false,0,fCheckOverlaps); 
  
  G4double entrWin2_rmin = 0*cm, entrWin2_rmax = 2.275*cm;
  G4double entrWin2_z = 0.05*cm;
  G4Tubs* solidentrWin2 = new G4Tubs("entrWin2",entrWin2_rmin,entrWin2_rmax,entrWin2_z,entrWin_phimin,entrWin_phimax);
  
  G4LogicalVolume* logicentrWin2 = new G4LogicalVolume(solidentrWin2,entrWin_mat,"entrWin2");
  G4VPhysicalVolume* physentrWin2 = new G4PVPlacement(0,pos_entrWin,logicentrWin2,"entrWin2",logicWorld,false,0,fCheckOverlaps); 
  
// //铝壳shell
//   G4ThreeVector pos_shell = G4ThreeVector(0,0,distance+2.8275*cm);//+4*cm
//   G4double shell_rmin = 2.03*cm, shell_rmax = 2.225*cm;
//   G4double shell_z = 0.9225*cm;
//   G4Tubs* solidShell = new G4Tubs("Shell1",shell_rmin,shell_rmax,shell_z,entrWin_phimin,entrWin_phimax);

//   G4LogicalVolume* logicShell = new G4LogicalVolume(solidShell,entrWin_mat,"Shell1");
//   new G4PVPlacement(0,pos_shell,logicShell,"Shell1",logicWorld,false,0,fCheckOverlaps);
  

//CLYC与封装材料边界的光学属性
  G4OpticalSurface* OpRefCrySurface = new G4OpticalSurface("RefCrySurface");
  OpRefCrySurface->SetType(dielectric_metal);   // 边界类型
  OpRefCrySurface->SetModel(glisur);            // 边界计算模型
  OpRefCrySurface->SetFinish(polished);         // 边界表面处理

  G4LogicalBorderSurface* RefCrySurface1 = new G4LogicalBorderSurface("RefCrySurface1",physScint,physentrWin1,OpRefCrySurface);
  G4LogicalBorderSurface* RefCrySurface2 = new G4LogicalBorderSurface("RefCrySurface1",physScint,physentrWin2,OpRefCrySurface);
  
  // fScoringVolume = logicScint;

// 平面硅
 //Si detector 300微米 有效直径35mm
  G4double Rmin_Si=0., Rmax_Si=17.5*mm, deltaZ_Si= 0.015*cm;
  G4double Phimin=0., deltaPhi=360*degree;

  auto solidSi=new G4Tubs("SolidSi",Rmin_Si,Rmax_Si,deltaZ_Si,Phimin,deltaPhi);
  G4LogicalVolume* logic_Si = new G4LogicalVolume(solidSi,Si,"Si_LV");

  new G4PVPlacement(0,                        //no rotation
                    G4ThreeVector(0,0,distance-2.25*cm-0.1*cm-0.16*cm ),        //position-2.5574*cm
                    logic_Si,                //its logical volume
                    "SiDetector",                //its name
                    logicWorld,                        //its mother  volume
                    false,                        //no boolean operation    
                    0,
                    fCheckOverlaps); 

  fScoringVolume = logic_Si;

  // 铍窗 厚度待确定
  G4double  BeThicknessHalf = 0.15*mm;
  G4double Rmin_Be=0., Rmax_Be=27.5*mm;
  G4double PhiMin=0., PhiMax=360*degree;

  auto solidBe=new G4Tubs("SolidBe",    Rmin_Be ,   Rmax_Be,   BeThicknessHalf ,  PhiMin ,   PhiMax);
  G4LogicalVolume* logic_Be = new G4LogicalVolume(solidBe,Be,"Be_LV");

  new G4PVPlacement(0,                        //no rotation
                    G4ThreeVector(0,0,distance-2.25*cm-0.1*cm-0.16*cm-0.16*cm ),        //position-2.5574*cm
                    logic_Be,                //its logical volume
                    "BeWindow",                //its name
                    logicWorld,                        //its mother  volume
                    false,                        //no boolean operation    
                    0,
                    fCheckOverlaps); 




  // // G4UserLimits用来限制逻辑体中的步数或步长
  // G4UserLimits* stepLimit = new G4UserLimits(0.8*mm);

  // //logicWorld->SetUserLimits(stepLimit);
  // logic_Si->SetUserLimits(stepLimit);

  // //
  // print parameters
  //
  
  // G4cout
  //   << G4endl
  //   << "------------------------------------------------------------" << G4endl
  //   << "---> The calorimeter is " //<< nofLayers << " layers of: [ "
  //   << scint_z*2/cm << "cm of " << logicScint->GetName()
  //   // << " + "
  //   // << gapThickness/mm << "mm of " << gapMaterial->GetName() << " ] " << G4endl
  //   << "------------------------------------------------------------" << G4endl;

  //
  //always return the physical World
  //
  return physWorld;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void DetectorConstruction::ConstructSDandField()
{
  // G4cout<<"*****************************"<<G4endl;
}
}
