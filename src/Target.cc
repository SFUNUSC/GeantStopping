#include "Target.hh"

Target::Target(G4LogicalVolume* experimentalHall_log,Materials* mat)
{
  materials=mat;
  expHall_log=experimentalHall_log;
  Backing_radius=6*mm;
  Backing_thickness=5*um;
  BackingZ=79;
  BackingA=197;
  BackingEx=547.5*keV;
  BackingTau=6.65/1000.*ns;//4.61 ps half life
  Pos = new G4ThreeVector(0.,0.,0.);
  BackingMaterial = materials->FindMaterial("G4_Au");//gold
  NBStep=20;
  fracReactionBacking=1.;
}

Target::~Target()
{ delete backing_limits;}
//-----------------------------------------------------------------------------
G4VPhysicalVolume* Target::Construct()
{
  
    G4ThreeVector shift;

    aBacking = new G4Tubs("backing",0.,Backing_radius,Backing_thickness/2.,-1.*deg,361.*deg);
    Backing_log = new G4LogicalVolume(aBacking,BackingMaterial,"backing_log",0,0,0);
    backing_limits= new G4UserLimits();
    backing_limits->SetMaxAllowedStep(Backing_thickness/NBStep);
    Backing_log->SetUserLimits(backing_limits);

    Backing_phys = new G4PVPlacement(G4Transform3D(NoRot,*Pos),Backing_log,"backing",expHall_log,false,0);
    shift.setZ(0.5*Backing_thickness);
    Backing_phys->SetTranslation(shift);

    G4Colour white (1.0,1.0,1.0); 
    G4VisAttributes* Vis_5 = new G4VisAttributes(white);
    Vis_5->SetVisibility(true);
    Vis_5->SetForceSolid(true);
    Backing_log->SetVisAttributes(Vis_5);
 
   return Backing_phys;
}

//-----------------------------------------------------------------------------
void Target::setBackingR(G4double X)
{
   Backing_radius=X;
   aBacking->SetOuterRadius(Backing_radius);
   G4cout<<"----> Backing radius is set to "<<G4BestUnit(2.*aBacking->GetOuterRadius(),"Length")<<G4endl;
   G4RunManager::GetRunManager()->GeometryHasBeenModified();
}
//-----------------------------------------------------------------------------
void Target::setBackingZ(G4double Z)
{
  G4ThreeVector d;
  Backing_thickness=Z;
  aBacking->SetZHalfLength(Backing_thickness/2.);
  d.setX(Pos->getX());
  d.setY(Pos->getY());
  d.setZ(Pos->getZ()+0.5*Z);
  Backing_phys->SetTranslation(d);
  backing_limits->SetMaxAllowedStep(Backing_thickness/NBStep);
  Backing_log->SetUserLimits(backing_limits);
  G4cout<<"----> Backing thickness is set to "<<G4BestUnit(2.*aBacking->GetZHalfLength(),"Length")<<G4endl;
   G4RunManager::GetRunManager()->GeometryHasBeenModified();
}
//-----------------------------------------------------------------------------
void Target::setNBStep(G4int n)
{
   NBStep=n;
   backing_limits->SetMaxAllowedStep(Backing_thickness/NBStep);
   Backing_log->SetUserLimits(backing_limits);
   G4cout<<"----> Number of simulation steps in the backing is set to "<<NBStep<<G4endl;
}

//-----------------------------------------------------------------------------
void Target::Report()
{
  G4cout<<""<<G4endl;
  G4cout<<"---->                Backing material set to "<<Backing_log->GetMaterial()->GetName()<< G4endl;   
  G4cout<<"---->           Backing mass number A set to "<<BackingA<< G4endl; 
  G4cout<<"---->         Backing atomic number Z set to "<<BackingZ<< G4endl;  
  G4cout<<"---->Backing recoil excitation energy set to "<<BackingEx/keV<<" keV"<<G4endl;   
  G4cout<<"---->               Backing radius is set to "<<G4BestUnit(aBacking->GetOuterRadius(),"Length")<<G4endl;
  G4cout<<"---->            Backing thickness is set to "<<G4BestUnit(2.*aBacking->GetZHalfLength(),"Length")<<G4endl;
  G4cout<<"----> Fraction of reaction on backing set to "<<fracReactionBacking<<G4endl;  
  G4cout<<"----> Number of simulation steps in the backing is set to "<<NBStep<<G4endl;
}
//---------------------------------------------------------------------
void Target::setBackingMaterial(G4String materialName)
{
  // search the material by its name 
  BackingMaterial = materials->FindMaterial(materialName);  
  Backing_log->SetMaterial(BackingMaterial);
  G4cout<<"----> Backing material set to     "<<Backing_log->GetMaterial()->GetName()<< G4endl;                 
}
//-------------------------------------------------------------------
void Target::setBackingReactionDepth(G4double depth)
{
  //  G4cout<<"\n----> The depth is "<<G4BestUnit(depth,"Length")<< G4endl;;
  backing_limits->SetUserMinRange(depth);
}
//-----------------------------------------------------------------------------
void Target::setBackingMass(G4int n)
{
    BackingA=n;
    G4cout<<"---->  Backing mass number A set to "<<BackingA<< G4endl;  
}
//-----------------------------------------------------------------------------
void Target::setBackingCharge(G4int n)
{
    BackingZ=n;
    G4cout<<"---->Backing atomic number A set to "<<BackingA<< G4endl;  
}
//-----------------------------------------------------------------------------
void Target::setBackingEx(G4double x)
{
    BackingEx=x;
    G4cout<<"---->Backing recoil excitation energy set to "<<BackingEx/keV<<" keV"<<G4endl;  
}
//-----------------------------------------------------------------------------
void Target::setBackingTau(G4double x)
{
    BackingTau=x;
    G4cout<<"---->Backing recoil lifetime energy set to "<<BackingTau/1000./ns<<" ps"<<G4endl;  
}
//-----------------------------------------------------------------------------
void Target::setFracReactionBacking(G4double x)
{
  if(x<0.) x=0.;
  if(x>1.) x=1.;
  fracReactionBacking=x;
  G4cout<<"---->Fraction of reaction on backing set to "<<fracReactionBacking<<G4endl;  
}
