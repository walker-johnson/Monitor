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
/// \file HistoManager.cc
/// \brief Implementation of the HistoManager class
//
// 
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "HistoManager.hh"
#include "G4UnitsTable.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

HistoManager::HistoManager()
  : fFileName("Hadr04")
{
  Book();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

HistoManager::~HistoManager()
{
  delete G4AnalysisManager::Instance();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void HistoManager::Book()
{
  // Create or get analysis manager
  // The choice of analysis technology is done via selection of a namespace
  // in HistoManager.hh
  G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
  analysisManager->SetFileName(fFileName);
  analysisManager->SetVerboseLevel(1);
  analysisManager->SetActivation(true);     //enable inactivation of histograms
  
  // Define histograms start values
  const G4int kMaxHisto = 11;
  const G4String id[] = {"0","1","2","3","4","5","6","7","8","9","10"};
  const G4String title[] = 
                { "dummy",                                           //0
                  "KE of neutrons leaving sheilding",                //1 
                  "KE of neutrons leaving test volume 1",            //2     
                  "KE of neutrons leaving test volume 2",            //3       
                  "KE of neutrons leaving test volume 3",            //4       
                  "KE of Neutrons leaving test volume 4",            //5
                  "KE of gammas leaving sheilding",                //6
                  "KE of gammas leaving test volume 1",            //7  
                  "KE of gammas leaving test volume 2",            //8 
                  "KE of gammas leaving test volume 3",            //9
                  "KE of gammas leaving test volume 4",            //10
                 };  

  // Default values (to be reset via /analysis/h1/set command)               
  G4int nbins = 100;
  G4double vmin = 0.;
  G4double vmax = 10.;

  // Create all histograms as inactivated 
  // as we have not yet set nbins, vmin, vmax
  for (G4int k=0; k<kMaxHisto; k++) {
    G4int ih = analysisManager->CreateH1(id[k], title[k], nbins, vmin, vmax);
    analysisManager->SetH1Activation(ih, true);
  }

  // ID=0, neutron transport
  analysisManager->CreateNtuple("nPoly", "Neutrons leaving polyethylene"); //id = 0
  analysisManager->CreateNtupleDColumn("x");
  analysisManager->CreateNtupleDColumn("y");
  analysisManager->CreateNtupleDColumn("z");
  analysisManager->CreateNtupleDColumn("KE");
  analysisManager->CreateNtupleIColumn("tag"); 
  analysisManager->FinishNtuple();

    // ID=1, gamma transport
  analysisManager->CreateNtuple("gPoly", "Gammas leaving polyethelyne"); //id = 1
  analysisManager->CreateNtupleDColumn("x");
  analysisManager->CreateNtupleDColumn("y");
  analysisManager->CreateNtupleDColumn("z");
  analysisManager->CreateNtupleDColumn("E");
  analysisManager->CreateNtupleIColumn("tag"); 
  analysisManager->FinishNtuple();

  // ID=2, neutron transport
  analysisManager->CreateNtuple("nShield", "Neutrons crossing shield boundary"); //id = 2
  analysisManager->CreateNtupleDColumn("x");
  analysisManager->CreateNtupleDColumn("y");
  analysisManager->CreateNtupleDColumn("z");
  analysisManager->CreateNtupleDColumn("KE");
  analysisManager->CreateNtupleIColumn("tag"); 
  analysisManager->FinishNtuple();

  // ID=3, gamma transport
  analysisManager->CreateNtuple("gShield", "Gammas crossing shield boundary"); //id = 3
  analysisManager->CreateNtupleDColumn("x");
  analysisManager->CreateNtupleDColumn("y");
  analysisManager->CreateNtupleDColumn("z");
  analysisManager->CreateNtupleDColumn("KE");
  analysisManager->CreateNtupleIColumn("tag"); 
  analysisManager->FinishNtuple();

  // ID=4, gamma transport
  analysisManager->CreateNtuple("nTV1", "Neutrons leaving test volume 1"); //id = 4
  analysisManager->CreateNtupleDColumn("x");
  analysisManager->CreateNtupleDColumn("y");
  analysisManager->CreateNtupleDColumn("z");
  analysisManager->CreateNtupleDColumn("KE");
  analysisManager->CreateNtupleIColumn("tag"); 
  analysisManager->FinishNtuple();

  // ID=5, gamma transport
  analysisManager->CreateNtuple("nTV2", "Neutrons leaving test volume 2"); //id = 5
  analysisManager->CreateNtupleDColumn("x");
  analysisManager->CreateNtupleDColumn("y");
  analysisManager->CreateNtupleDColumn("z");
  analysisManager->CreateNtupleDColumn("KE");
  analysisManager->CreateNtupleIColumn("tag"); 
  analysisManager->FinishNtuple();

  // ID=6, gamma transport
  analysisManager->CreateNtuple("nTV3", "Neutrons leaving test volume 3"); //id = 6
  analysisManager->CreateNtupleDColumn("x");
  analysisManager->CreateNtupleDColumn("y");
  analysisManager->CreateNtupleDColumn("z");
  analysisManager->CreateNtupleDColumn("KE");
  analysisManager->CreateNtupleIColumn("tag"); 
  analysisManager->FinishNtuple();

  // ID=7, gamma transport
  analysisManager->CreateNtuple("nTV4", "Neutrons leaving test volume 4"); //id = 7
  analysisManager->CreateNtupleDColumn("x");
  analysisManager->CreateNtupleDColumn("y");
  analysisManager->CreateNtupleDColumn("z");
  analysisManager->CreateNtupleDColumn("KE");
  analysisManager->CreateNtupleIColumn("tag"); 
  analysisManager->FinishNtuple();

  // ID=8, gamma transport
  analysisManager->CreateNtuple("gTV1", "Gammas leaving test volume 1"); //id = 8
  analysisManager->CreateNtupleDColumn("x");
  analysisManager->CreateNtupleDColumn("y");
  analysisManager->CreateNtupleDColumn("z");
  analysisManager->CreateNtupleDColumn("KE");
  analysisManager->CreateNtupleIColumn("tag"); 
  analysisManager->FinishNtuple();

  // ID=9, gamma transport
  analysisManager->CreateNtuple("gTV2", "Gammas leaving test volume 2"); //id = 9
  analysisManager->CreateNtupleDColumn("x");
  analysisManager->CreateNtupleDColumn("y");
  analysisManager->CreateNtupleDColumn("z");
  analysisManager->CreateNtupleDColumn("KE");
  analysisManager->CreateNtupleIColumn("tag"); 
  analysisManager->FinishNtuple();

  // ID=10, gamma transport
  analysisManager->CreateNtuple("gTV3", "Gammas leaving test volume 3"); //id = 10
  analysisManager->CreateNtupleDColumn("x");
  analysisManager->CreateNtupleDColumn("y");
  analysisManager->CreateNtupleDColumn("z");
  analysisManager->CreateNtupleDColumn("KE");
  analysisManager->CreateNtupleIColumn("tag"); 
  analysisManager->FinishNtuple();

  // ID=11, gamma transport
  analysisManager->CreateNtuple("gTV4", "Gammas leaving test volume 4"); //id = 11
  analysisManager->CreateNtupleDColumn("x");
  analysisManager->CreateNtupleDColumn("y");
  analysisManager->CreateNtupleDColumn("z");
  analysisManager->CreateNtupleDColumn("KE");
  analysisManager->CreateNtupleIColumn("tag"); 
  analysisManager->FinishNtuple();

  // ID=12, plane locations
  analysisManager->CreateNtuple("PlaneLoc", "The locations of each test plane"); //id = 12
  analysisManager->CreateNtupleDColumn("x1");
  analysisManager->CreateNtupleDColumn("x2");
  analysisManager->CreateNtupleDColumn("y1");
  analysisManager->CreateNtupleDColumn("y2");
  analysisManager->CreateNtupleDColumn("z1");
  analysisManager->CreateNtupleDColumn("z2");
  analysisManager->CreateNtupleDColumn("Test Volume Number");
  analysisManager->FinishNtuple();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
