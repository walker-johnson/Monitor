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
/// \file DetectorMessenger.cc
/// \brief Implementation of the DetectorMessenger class
//
//
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "DetectorMessenger.hh"

#include "DetectorConstruction.hh"
#include "G4UIdirectory.hh"
#include "G4UIcommand.hh"
#include "G4UIparameter.hh"
#include "G4UIcmdWithAString.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"
#include "G4UIcmdWithoutParameter.hh"
#include "G4UIcmdWithABool.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

DetectorMessenger::DetectorMessenger(DetectorConstruction * Det)
:G4UImessenger(), 
 fDetector(Det), fTestemDir(0), fDetDir(0), fMaterCmd(0), fSizeCmd(0),
 fIsotopeCmd(0)
{ 
  fTestemDir = new G4UIdirectory("/testhadr/");
  fTestemDir->SetGuidance("commands specific to this example");
  
  G4bool broadcast = false;
  fDetDir = new G4UIdirectory("/testhadr/det/",broadcast);
  fDetDir->SetGuidance("detector construction commands");

  fMonitorRadius = new G4UIcmdWithADoubleAndUnit("/testhadr/det/setMonitorRadius",this);
  fMonitorRadius->SetGuidance("Input a monitor radius");
  fMonitorRadius->SetParameterName("Radius",false);
  fMonitorRadius->SetRange("Radius>0");
  fMonitorRadius->SetUnitCategory("Length");
  fMonitorRadius->AvailableForStates(G4State_PreInit, G4State_Idle);

  fMonitorDistance = new G4UIcmdWithADoubleAndUnit("/testhadr/det/setMonitorDistance",this);
  fMonitorDistance->SetGuidance("Input a distance for the monitor");
  fMonitorDistance->SetParameterName("Distance",false);
  fMonitorDistance->SetRange("Distance>0");
  fMonitorDistance->SetUnitCategory("Length");
  fMonitorDistance->AvailableForStates(G4State_PreInit, G4State_Idle);

  fWindowSize = new G4UIcmdWithADoubleAndUnit("/testhadr/det/setWindowSize",this);
  fWindowSize->SetGuidance("Input a window size");
  fWindowSize->SetParameterName("Size",false);
  fWindowSize->SetRange("Size>0");
  fWindowSize->SetUnitCategory("Length");
  fWindowSize->AvailableForStates(G4State_PreInit, G4State_Idle);

  fWindow = new G4UIcmdWithABool("/testhadr/det/setWindow",this);
  fWindow->SetGuidance("Make a window (true/false)");
  fWindow->SetParameterName("Window",false);
  fWindow->SetDefaultValue(true);
  fWindow->AvailableForStates(G4State_PreInit, G4State_Idle);

  fPolySheildCmd = new G4UIcmdWithADoubleAndUnit("/testhadr/det/setPolyThickness",this);
  fPolySheildCmd->SetGuidance("Input a sheild thickness");
  fPolySheildCmd->SetParameterName("Thickness",false);
  fPolySheildCmd->SetRange("Thickness>0");
  fPolySheildCmd->SetUnitCategory("Length");
  fPolySheildCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  fPbSheildCmd = new G4UIcmdWithADoubleAndUnit("/testhadr/det/setLeadThickness",this);
  fPbSheildCmd->SetGuidance("Input a sheild thickness");
  fPbSheildCmd->SetParameterName("Thickness",false);
  fPbSheildCmd->SetRange("Thickness>0");
  fPbSheildCmd->SetUnitCategory("Length");
  fPbSheildCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  
  fMaterCmd = new G4UIcmdWithAString("/testhadr/det/setMat",this);
  fMaterCmd->SetGuidance("Select material of the box.");
  fMaterCmd->SetParameterName("choice",false);
  fMaterCmd->AvailableForStates(G4State_PreInit,G4State_Idle);
  
  fSizeCmd = new G4UIcmdWithADoubleAndUnit("/testhadr/det/setSize",this);
  fSizeCmd->SetGuidance("Set size of the box");
  fSizeCmd->SetParameterName("Size",false);
  fSizeCmd->SetRange("Size>0.");
  fSizeCmd->SetUnitCategory("Length");
  fSizeCmd->AvailableForStates(G4State_PreInit,G4State_Idle);
       
  fIsotopeCmd = new G4UIcommand("/testhadr/det/setIsotopeMat",this);
  fIsotopeCmd->SetGuidance("Build and select a material with single isotope");
  fIsotopeCmd->SetGuidance("  symbol of isotope, Z, A, density of material");
  //
  G4UIparameter* symbPrm = new G4UIparameter("isotope",'s',false);
  symbPrm->SetGuidance("isotope symbol");
  fIsotopeCmd->SetParameter(symbPrm);
  //      
  G4UIparameter* ZPrm = new G4UIparameter("Z",'i',false);
  ZPrm->SetGuidance("Z");
  ZPrm->SetParameterRange("Z>0");
  fIsotopeCmd->SetParameter(ZPrm);
  //      
  G4UIparameter* APrm = new G4UIparameter("A",'i',false);
  APrm->SetGuidance("A");
  APrm->SetParameterRange("A>0");
  fIsotopeCmd->SetParameter(APrm);  
  //    
  G4UIparameter* densityPrm = new G4UIparameter("density",'d',false);
  densityPrm->SetGuidance("density of material");
  densityPrm->SetParameterRange("density>0.");
  fIsotopeCmd->SetParameter(densityPrm);
  //
  G4UIparameter* unitPrm = new G4UIparameter("unit",'s',false);
  unitPrm->SetGuidance("unit of density");
  G4String unitList = G4UIcommand::UnitsList(G4UIcommand::CategoryOf("g/cm3"));
  unitPrm->SetParameterCandidates(unitList);
  fIsotopeCmd->SetParameter(unitPrm);
  //
  fIsotopeCmd->AvailableForStates(G4State_PreInit,G4State_Idle);  
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

DetectorMessenger::~DetectorMessenger()
{
  delete fMaterCmd;
  delete fPolySheildCmd;
  delete fPbSheildCmd;
  delete fSizeCmd;
  delete fIsotopeCmd;
  delete fDetDir;
  delete fTestemDir;
  delete fMonitorRadius;
  delete fMonitorDistance;
  delete fWindowSize;
  delete fWindow;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void DetectorMessenger::SetNewValue(G4UIcommand* command,G4String newValue)
{ 
  if( command == fMaterCmd )
   { fDetector->SetMaterial(newValue);}
  if (command == fMonitorRadius )
    {fDetector->SetMonitorRadius(fMonitorRadius->GetNewDoubleValue(newValue));}
  if (command == fMonitorDistance )
    {fDetector->SetMonitorDistance(fMonitorDistance->GetNewDoubleValue(newValue));}
  if(command == fWindowSize)
    {fDetector->SetWindowSize(fWindowSize->GetNewDoubleValue(newValue));}
  if(command == fWindow)
    {fDetector->SetWindow(fWindow->GetNewBoolValue(newValue));}

  if( command == fPolySheildCmd )
    { fDetector->SetPolyThickness(fPolySheildCmd->GetNewDoubleValue(newValue)); }

  if( command == fPbSheildCmd )
    { fDetector->SetLeadThickness(fPbSheildCmd->GetNewDoubleValue(newValue)); }
  
  if( command == fSizeCmd )
    { fDetector->SetSize(fSizeCmd->GetNewDoubleValue(newValue), fSizeCmd->GetNewDoubleValue(newValue), fSizeCmd->GetNewDoubleValue(newValue));}
     
  if (command == fIsotopeCmd)
   {
     G4int Z; G4int A; G4double dens;
     G4String name, unt;
     std::istringstream is(newValue);
     is >> name >> Z >> A >> dens >> unt;
     dens *= G4UIcommand::ValueOf(unt);
     fDetector->MaterialWithSingleIsotope (name,name,dens,Z,A);
     fDetector->SetMaterial(name);    
   }   
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
