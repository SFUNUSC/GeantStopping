#include "DetectorConstruction.hh"

DetectorConstruction::DetectorConstruction()
  {
    // use G4-NIST materials data base
    //
    G4NistManager* man = G4NistManager::Instance();
    man->FindOrBuildMaterial("G4_Galactic");
    man->FindOrBuildMaterial("G4_Pb");
    man->FindOrBuildMaterial("G4_lAr");
    man->FindOrBuildMaterial("G4_STAINLESS-STEEL");
  
  
    man->FindOrBuildMaterial("G4_Al");
    man->FindOrBuildMaterial("G4_POLYETHYLENE");
    man->FindOrBuildMaterial("G4_RUBBER_NEOPRENE");
    man->FindOrBuildMaterial("G4_ALUMINUM_OXIDE");
    man->FindOrBuildMaterial("G4_ALUMINUM_OXIDE");
    man->FindOrBuildMaterial("G4_BGO");
    man->FindOrBuildMaterial("G4_CESIUM_IODIDE");
    man->FindOrBuildMaterial("G4_Ge");
    man->FindOrBuildMaterial("G4_Cu");
    
    man->FindOrBuildMaterial("G4_AIR");
  }

DetectorConstruction::~DetectorConstruction()
{
  delete ExperimentalHallMessenger;
 
}

G4VPhysicalVolume* DetectorConstruction::Construct()
{

  Materials* materials=new Materials();

//Experimental Hall

   Experimental_Hall* ExperimentalHall = new Experimental_Hall(materials);
   ExpHall_phys=ExperimentalHall->Construct();
   ExpHall_log=ExperimentalHall->GetLogVolume();
   ExperimentalHall->Report();
   ExperimentalHallMessenger = new Experimental_Hall_Messenger(ExperimentalHall);

   theTarget = new Target(ExpHall_log,materials);
   theTarget->Construct();
   theTarget->Report();
   TargetMessenger = new Target_Messenger(theTarget);
   
   //------------------------------------------------ 
  // Sensitive detectors
  //------------------------------------------------ 

   G4SDManager* SDman = G4SDManager::GetSDMpointer();
 
   //------------------------------------------------
   // Detectors sensitive for ion tracking
   //------------------------------------------------
   TrackerIon = new TrackerIonSD("IonTracker");
   TrackerIonSDMessenger = new TrackerIonSD_Messenger(TrackerIon);
   SDman->AddNewDetector( TrackerIon );
   
   //make everything sensitive to ions
   theTarget->GetTargetLog()->SetSensitiveDetector(TrackerIon);
   ExpHall_log->SetSensitiveDetector(TrackerIon);
 
   return ExpHall_phys;
}
/*====================================================================*/
void DetectorConstruction::UpdateGeometry()
{
  G4RunManager::GetRunManager()->DefineWorldVolume(Construct());
}
