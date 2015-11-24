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
  void setTargetR(G4double);
  void setTargetZ(G4double);
  void setTargetMaterial(G4String);
  void setTargetCharge(G4int);
  void setTargetMass(G4int);
  void setTargetEx(G4double);
  void setTargetTau(G4double);
  void setNTStep(G4int);
  void setFracReactionTarget(G4double);
  void setFlagReactionTarget(G4bool flag){flagReactionTarget=flag;}
  void Report();
  G4LogicalVolume* GetTargetLog(){return Target_log;}
  G4Tubs* GetTarget(){return aTarget;}
  G4int getTargetMass(){return TargetA;}
  G4int getTargetCharge(){return TargetZ;}
  G4double getTargetEx(){return TargetEx;}
  G4double getTargetTau(){return TargetTau;}
  G4VPhysicalVolume* GetTargetPlacement(){return Target_phys;} 
  void setTargetReactionDepth(G4double);
  G4double GetFracReactionTarget(){return fracReactionTarget;};
  G4bool getFlagReactionTarget(){return flagReactionTarget;}


    private:
  // dimensions
  G4double Target_radius;
  G4double Target_thickness;


  //materials
  Materials* materials;
  G4Material* TargetMaterial;
  G4int TargetA,TargetZ;
  G4double TargetEx;
  G4double TargetTau;
  //default position
  G4RotationMatrix NoRot;
  G4ThreeVector *Pos;

  //the tube
  G4Tubs* aTarget;

  //logical volume
  G4LogicalVolume* Target_log;
 
  //physical volume
  G4VPhysicalVolume* Target_phys;

  G4UserLimits *backing_limits;
  //Number of simulation steps
  G4int NTStep;

  G4double fracReactionTarget;
  G4bool   flagReactionTarget;
};

#endif

