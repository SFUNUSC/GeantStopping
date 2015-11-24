#ifndef Target_H
#define Target_H 1

#include "G4RunManager.hh"
#include "G4Material.hh"
#include "Materials.hh"
#include "G4Tubs.hh"
#include "G4LogicalVolume.hh"
#include "G4VPhysicalVolume.hh"
#include "G4ThreeVector.hh"
#include "G4PVPlacement.hh"
#include "G4VisAttributes.hh"
#include "G4Colour.hh"
#include "G4RotationMatrix.hh"
#include "G4Transform3D.hh"
#include "G4UnitsTable.hh"
#include "G4UserLimits.hh"

class Target 
{
  public:

  G4LogicalVolume *expHall_log;

  Target(G4LogicalVolume*,Materials*);
  ~Target();
  
  G4VPhysicalVolume *Construct();
  void setBackingR(G4double);
  void setBackingZ(G4double);
  void setBackingMaterial(G4String);
  void setBackingCharge(G4int);
  void setBackingMass(G4int);
  void setBackingEx(G4double);
  void setBackingTau(G4double);
  void setNBStep(G4int);
  void setFracReactionBacking(G4double);
  void setFlagReactionBacking(G4bool flag){flagReactionBacking=flag;}
  void Report();
  G4LogicalVolume* GetBackingLog(){return Backing_log;}
  G4Tubs* GetBacking(){return aBacking;}
  G4int getBackingMass(){return BackingA;}
  G4int getBackingCharge(){return BackingZ;}
  G4double getBackingEx(){return BackingEx;}
  G4double getBackingTau(){return BackingTau;}
  G4VPhysicalVolume* GetBackingPlacement(){return Backing_phys;} 
  void setBackingReactionDepth(G4double);
  G4double GetFracReactionBacking(){return fracReactionBacking;};
  G4bool getFlagReactionBacking(){return flagReactionBacking;}


    private:
  // dimensions
  G4double Backing_radius;
  G4double Backing_thickness;


  //materials
  Materials* materials;
  G4Material* BackingMaterial;
  G4int BackingA,BackingZ;
  G4double BackingEx;
  G4double BackingTau;
  //default position
  G4RotationMatrix NoRot;
  G4ThreeVector *Pos;

  //the tube
  G4Tubs* aBacking;

  //logical volume
  G4LogicalVolume* Backing_log;
 
  //physical volume
  G4VPhysicalVolume* Backing_phys;

  G4UserLimits *backing_limits;
  //Number of simulation steps
  G4int NBStep;

  G4double fracReactionBacking;
  G4bool   flagReactionBacking;
};

#endif

