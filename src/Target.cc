#include "Target.hh"

Target::Target(G4LogicalVolume* experimentalHall_log,Materials* mat)
{
  materials=mat;
  expHall_log=experimentalHall_log;
  Target_radius=6*mm;
  Target_thickness=5*um;
  TargetZ=79;
  TargetA=197;
  TargetEx=547.5*keV;
  TargetTau=6.65/1000.*ns;//4.61 ps half life
  Pos = new G4ThreeVector(0.,0.,0.);
  TargetMaterial = materials->FindMaterial("G4_Au");//gold
  NTStep=20;
  fracReactionTarget=1.;
}

Target::~Target()
{ delete backing_limits;}
//-----------------------------------------------------------------------------
G4VPhysicalVolume* Target::Construct()
{
  
    G4ThreeVector shift;

    aTarget = new G4Tubs("backing",0.,Target_radius,Target_thickness/2.,-1.*deg,361.*deg);
    Target_log = new G4LogicalVolume(aTarget,TargetMaterial,"backing_log",0,0,0);
    backing_limits= new G4UserLimits();
    backing_limits->SetMaxAllowedStep(Target_thickness/NTStep);
    Target_log->SetUserLimits(backing_limits);

    Target_phys = new G4PVPlacement(G4Transform3D(NoRot,*Pos),Target_log,"backing",expHall_log,false,0);
    shift.setZ(0.5*Target_thickness);
    Target_phys->SetTranslation(shift);

    G4Colour white (1.0,1.0,1.0); 
    G4VisAttributes* Vis_5 = new G4VisAttributes(white);
    Vis_5->SetVisibility(true);
    Vis_5->SetForceSolid(true);
    Target_log->SetVisAttributes(Vis_5);
 
   return Target_phys;
}

//-----------------------------------------------------------------------------
void Target::setTargetR(G4double X)
{
   Target_radius=X;
   aTarget->SetOuterRadius(Target_radius);
   G4cout<<"----> Target radius is set to "<<G4BestUnit(2.*aTarget->GetOuterRadius(),"Length")<<G4endl;
   G4RunManager::GetRunManager()->GeometryHasBeenModified();
}
//-----------------------------------------------------------------------------
void Target::setTargetZ(G4double Z)
{
  G4ThreeVector d;
  Target_thickness=Z;
  aTarget->SetZHalfLength(Target_thickness/2.);
  d.setX(Pos->getX());
  d.setY(Pos->getY());
  d.setZ(Pos->getZ()+0.5*Z);
  Target_phys->SetTranslation(d);
  backing_limits->SetMaxAllowedStep(Target_thickness/NTStep);
  Target_log->SetUserLimits(backing_limits);
  G4cout<<"----> Target thickness is set to "<<G4BestUnit(2.*aTarget->GetZHalfLength(),"Length")<<G4endl;
   G4RunManager::GetRunManager()->GeometryHasBeenModified();
}
//-----------------------------------------------------------------------------
void Target::setNTStep(G4int n)
{
   NTStep=n;
   backing_limits->SetMaxAllowedStep(Target_thickness/NTStep);
   Target_log->SetUserLimits(backing_limits);
   G4cout<<"----> Number of simulation steps in the backing is set to "<<NTStep<<G4endl;
}

//-----------------------------------------------------------------------------
void Target::Report()
{
  G4cout<<""<<G4endl;
  G4cout<<"---->                Target material set to "<<Target_log->GetMaterial()->GetName()<< G4endl;   
  G4cout<<"---->           Target mass number A set to "<<TargetA<< G4endl; 
  G4cout<<"---->         Target atomic number Z set to "<<TargetZ<< G4endl;  
  G4cout<<"---->Target recoil excitation energy set to "<<TargetEx/keV<<" keV"<<G4endl;   
  G4cout<<"---->               Target radius is set to "<<G4BestUnit(aTarget->GetOuterRadius(),"Length")<<G4endl;
  G4cout<<"---->            Target thickness is set to "<<G4BestUnit(2.*aTarget->GetZHalfLength(),"Length")<<G4endl;
  G4cout<<"----> Fraction of reaction on backing set to "<<fracReactionTarget<<G4endl;  
  G4cout<<"----> Number of simulation steps in the backing is set to "<<NTStep<<G4endl;
}
//---------------------------------------------------------------------
void Target::setTargetMaterial(G4String materialName)
{
  // search the material by its name 
  TargetMaterial = materials->FindMaterial(materialName);  
  Target_log->SetMaterial(TargetMaterial);
  TargetA=Target_log->GetMaterial()->GetA();
  TargetZ=Target_log->GetMaterial()->GetZ();
  G4cout<<"----> Target material set to     "<<Target_log->GetMaterial()->GetName()<< G4endl;                 
}
//-------------------------------------------------------------------
void Target::setTargetReactionDepth(G4double depth)
{
  //  G4cout<<"\n----> The depth is "<<G4BestUnit(depth,"Length")<< G4endl;;
  backing_limits->SetUserMinRange(depth);
}
//-----------------------------------------------------------------------------
void Target::setTargetMass(G4int n)
{
    TargetA=n;
    G4cout<<"---->  Target mass number A set to "<<TargetA<< G4endl;  
}
//-----------------------------------------------------------------------------
void Target::setTargetCharge(G4int n)
{
    TargetZ=n;
    G4cout<<"---->Target atomic number A set to "<<TargetA<< G4endl;  
}
//-----------------------------------------------------------------------------
void Target::setTargetEx(G4double x)
{
    TargetEx=x;
    G4cout<<"---->Target recoil excitation energy set to "<<TargetEx/keV<<" keV"<<G4endl;  
}
//-----------------------------------------------------------------------------
void Target::setTargetTau(G4double x)
{
    TargetTau=x;
    G4cout<<"---->Target recoil lifetime energy set to "<<TargetTau/1000./ns<<" ps"<<G4endl;  
}
//-----------------------------------------------------------------------------
void Target::setFracReactionTarget(G4double x)
{
  if(x<0.) x=0.;
  if(x>1.) x=1.;
  fracReactionTarget=x;
  G4cout<<"---->Fraction of reaction on backing set to "<<fracReactionTarget<<G4endl;  
}
