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
/// \file RunAction.cc
/// \brief Implementation of the RunAction class
//
// 
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "RunAction.hh"
#include "Run.hh"
#include "DetectorConstruction.hh"
#include "PrimaryGeneratorAction.hh"
#include "HistoManager.hh"

#include "G4Run.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"

#include "Randomize.hh"
#include <iomanip>

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

RunAction::RunAction(DetectorConstruction* det, PrimaryGeneratorAction* prim)
  : G4UserRunAction(),
    fDetector(det), fPrimary(prim), fRun(0), fHistoManager(0)
{
 // Book predefined histograms
 fHistoManager = new HistoManager(); 
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

RunAction::~RunAction()
{
 delete fHistoManager;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4Run* RunAction::GenerateRun()
{ 
  fRun = new Run(fDetector); 
  return fRun;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void RunAction::BeginOfRunAction(const G4Run*)
{    
  // show Rndm status
  if (isMaster) G4Random::showEngineStatus();
  
  // keep run condition
  if (fPrimary) { 
    G4ParticleDefinition* particle 
      = fPrimary->GetParticleGun()->GetParticleDefinition();
    G4double energy = fPrimary->GetParticleGun()->GetParticleEnergy();
    fRun->SetPrimary(particle, energy);
  }
             
  //histograms
  //
  G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
  if ( analysisManager->IsActive() ) {
    analysisManager->OpenFile();
    G4double tp1X = fDetector->getTP1X();
    G4double tp1Y = fDetector->getTP1Y();
    G4double tp1Z = fDetector->getTP1Z();
    analysisManager->FillNtupleDColumn(12, 0, (fDetector->getCenterX() + tp1X/2 +2*m)/1000);
    analysisManager->FillNtupleDColumn(12, 1, (fDetector->getCenterX() - tp1X/2 -2*m)/1000);
    analysisManager->FillNtupleDColumn(12, 2, (fDetector->getCenterY() + tp1Y/2 +2*m)/1000);
    analysisManager->FillNtupleDColumn(12, 3, (fDetector->getCenterY() - tp1Y/2 -2*m)/1000);
    analysisManager->FillNtupleDColumn(12, 4, (fDetector->getCenterZ() + tp1Z/2 +1*m)/1000);
    analysisManager->FillNtupleDColumn(12, 5, (fDetector->getCenterZ() - tp1Z/2 -1*m)/1000);
    analysisManager->FillNtupleDColumn(12, 6, 4.0);
    analysisManager->AddNtupleRow(12);

    analysisManager->FillNtupleDColumn(12, 0, (fDetector->getCenterX() + tp1X/2 +1.5*m)/1000);
    analysisManager->FillNtupleDColumn(12, 1, (fDetector->getCenterX() - tp1X/2 -1.5*m)/1000);
    analysisManager->FillNtupleDColumn(12, 2, (fDetector->getCenterY() + tp1Y/2 +1.5*m)/1000);
    analysisManager->FillNtupleDColumn(12, 3, (fDetector->getCenterY() - tp1Y/2 -1.5*m)/1000);
    analysisManager->FillNtupleDColumn(12, 4, (fDetector->getCenterZ() + tp1Z/2 +0.5*m)/1000);
    analysisManager->FillNtupleDColumn(12, 5, (fDetector->getCenterZ() - tp1Z/2 -1.0*m)/1000);
    analysisManager->FillNtupleDColumn(12, 6, 3.0);
    analysisManager->AddNtupleRow(12);

    analysisManager->FillNtupleDColumn(12, 0, (fDetector->getCenterX() + tp1X/2 +1.0*m)/1000);
    analysisManager->FillNtupleDColumn(12, 1, (fDetector->getCenterX() - tp1X/2 -1.0*m)/1000);
    analysisManager->FillNtupleDColumn(12, 2, (fDetector->getCenterY() + tp1Y/2 +1.0*m)/1000);
    analysisManager->FillNtupleDColumn(12, 3, (fDetector->getCenterY() - tp1Y/2 -1.0*m)/1000);
    analysisManager->FillNtupleDColumn(12, 4, (fDetector->getCenterZ() + tp1Z/2)/1000);
    analysisManager->FillNtupleDColumn(12, 5, (fDetector->getCenterZ() - tp1Z/2 -1.0*m)/1000);
    analysisManager->FillNtupleDColumn(12, 6, 2.0);
    analysisManager->AddNtupleRow(12);

    analysisManager->FillNtupleDColumn(12, 0, (fDetector->getCenterX() + tp1X/2 +0.5*m)/1000);
    analysisManager->FillNtupleDColumn(12, 1, (fDetector->getCenterX() - tp1X/2 -0.5*m)/1000);
    analysisManager->FillNtupleDColumn(12, 2, (fDetector->getCenterY() + tp1Y/2 +0.5*m)/1000);
    analysisManager->FillNtupleDColumn(12, 3, (fDetector->getCenterY() - tp1Y/2 -0.5*m)/1000);
    analysisManager->FillNtupleDColumn(12, 4, (fDetector->getCenterZ() + tp1Z/2 -0.5*m)/1000);
    analysisManager->FillNtupleDColumn(12, 5, (fDetector->getCenterZ() - tp1Z/2 -1.0*m)/1000);
    analysisManager->FillNtupleDColumn(12, 6, 1.0);
    analysisManager->AddNtupleRow(12);
  }  
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void RunAction::EndOfRunAction(const G4Run*)
{
  if (isMaster) fRun->EndOfRun();    
  
  //save histograms      
  G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
  if ( analysisManager->IsActive() ) {
    analysisManager->Write();
    analysisManager->CloseFile();
  }
      
  // show Rndm status
  if (isMaster) G4Random::showEngineStatus();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
