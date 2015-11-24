#ifndef DetectorConstruction_H
#define DetectorConstruction_H 1

#include "G4AssemblyVolume.hh"
#include "G4VUserDetectorConstruction.hh"
#include "G4SDManager.hh"
#include "Materials.hh"
#include "Experimental_Hall.hh"
#include "Experimental_Hall_Messenger.hh"
#include "Target.hh"
#include "Target_Messenger.hh"
#include "TrackerIonSD.hh"
#include "TrackerIonSD_Messenger.hh"
#include "G4NistManager.hh"

class DetectorConstruction : public G4VUserDetectorConstruction
{
  public:

    DetectorConstruction();
    ~DetectorConstruction();

    G4VPhysicalVolume* Construct();
 
    Target* GetTarget(){return theTarget;};

    void UpdateGeometry();
  
  private:
  
  G4LogicalVolume* ExpHall_log;
  G4VPhysicalVolume* ExpHall_phys;
  Target* theTarget;

  Experimental_Hall_Messenger* ExperimentalHallMessenger;
  Target_Messenger*    TargetMessenger;

  TrackerIonSD* TrackerIon;
  TrackerIonSD_Messenger* TrackerIonSDMessenger;

};

#endif

