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
/// \file DetectorConstruction.hh
/// \brief Definition of the DetectorConstruction class
//
// 

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#ifndef DetectorConstruction_h
#define DetectorConstruction_h 1

#include "G4VUserDetectorConstruction.hh"
#include "globals.hh"

class G4LogicalVolume;
class G4Material;
class DetectorMessenger;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class DetectorConstruction : public G4VUserDetectorConstruction
{
  public:
  
    DetectorConstruction();
   ~DetectorConstruction();

  public:
  
    virtual G4VPhysicalVolume* Construct();

    G4Material* 
    MaterialWithSingleIsotope(G4String, G4String, G4double, G4int, G4int);
         
    void SetSize     (G4double, G4double, G4double);              
    void SetMaterial (G4String);
    void SetPolyThickness (G4double);
    void SetLeadThickness (G4double);
    void SetWindow (G4bool);
    void SetWindowSize (G4double);
    void SetMonitorRadius (G4double);
    void SetMonitorDistance (G4double);
    void SetWaterThickness (G4double);
    void IsWaterTank (G4bool);
  G4double getCenterX(){return centerX;};
  G4double getCenterY(){return centerY;};
  G4double getCenterZ(){return centerZ;};
  G4double getTP1X(){return tp1X;};
  G4double getTP1Y(){return tp1Y;};
  G4double getTP1Z(){return tp1Z;};
    
  
  public:
  
     const
     G4VPhysicalVolume* GetWorld()      {return worldP;};           
                          
     G4Material*        GetMaterial()   {return fMaterial;};
     G4double           GetSize()       {return fBoxX;};
     void               PrintParameters();

  

     G4Material* LiPE;
     G4Material* BPE;
     G4Material* Fe;
     G4Material* Al;

     G4VPhysicalVolume* wallP;
     G4LogicalVolume*   wallL;

     G4VPhysicalVolume* labP;
     G4LogicalVolume* labL;

     G4VPhysicalVolume* win1P;
     G4LogicalVolume* win1L;

     G4VPhysicalVolume* win2P;
     G4LogicalVolume* win2L;

     G4VPhysicalVolume* win3P;
     G4LogicalVolume* win3L;

     G4VPhysicalVolume* win4P;
     G4LogicalVolume* win4L;

     G4VPhysicalVolume* win5P;
     G4LogicalVolume* win5L;

     G4VPhysicalVolume* doorP;
     G4LogicalVolume* doorL;
  
     G4VPhysicalVolume* shieldP;
     G4LogicalVolume* shieldL;

     G4VPhysicalVolume* worldP;
     G4LogicalVolume*   worldL;

  G4VPhysicalVolume* ironfilterP;
  G4LogicalVolume* ironfilterL;

  G4VPhysicalVolume* aluminumfilterP;
  G4LogicalVolume* aluminumfilterL;

  G4VPhysicalVolume* polyShieldP;
  G4LogicalVolume* polyShieldL;

  G4VPhysicalVolume* pbShieldP;
  G4LogicalVolume* pbShieldL;

  G4VPhysicalVolume* monitorP;
  G4LogicalVolume* monitorL;

  G4VPhysicalVolume* testPlane1P;
  G4LogicalVolume* testPlane1L;

  G4VPhysicalVolume* testPlane2P;
  G4LogicalVolume* testPlane2L;

  G4VPhysicalVolume* testPlane3P;
  G4LogicalVolume* testPlane3L;

  G4VPhysicalVolume* testPlane4P;
  G4LogicalVolume* testPlane4L;

  G4VPhysicalVolume* waterTankP;
  G4LogicalVolume* waterTankL;
  
  private:

  G4bool window;
  G4bool waterTank;
  G4double monitorR;
  G4double monitorD;
  G4double windowX;
  G4double windowY;
  G4double waterThickness;
  G4double           polyThickness;
  G4double           pbThickness;
  G4double           fBoxX;
  G4double           fBoxY;
  G4double           fBoxZ;
  G4Material*        fMaterial;
  DetectorMessenger* fDetectorMessenger;
  G4double centerX;
  G4double centerY;
  G4double centerZ;
  G4double tp1X;
  G4double tp1Y;
  G4double tp1Z;

  private:
    
     void               DefineMaterials();
     G4VPhysicalVolume* ConstructVolumes();     
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......


#endif

