#include "Target_Messenger.hh"


Target_Messenger::Target_Messenger(Target* Tar)
:aTarget(Tar)
{ 
 
  BackingDir = new G4UIdirectory("/Backing/");
  BackingDir->SetGuidance("Backing control.");

  BMatCmd = new G4UIcmdWithAString("/Backing/Material",this);
  BMatCmd->SetGuidance("Select material for the backing.");
  BMatCmd->SetParameterName("choice",false);
  BMatCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  BMCmd = new G4UIcmdWithAnInteger("/Backing/MassNumber",this);
  BMCmd->SetGuidance("Set the mass number A for the target");
  BMCmd->SetParameterName("choice",false);
  BMCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  BQCmd = new G4UIcmdWithAnInteger("/Backing/AtomicNumber",this);
  BQCmd->SetGuidance("Set the atomic number Z for the backing");
  BQCmd->SetParameterName("choice",false);
  BQCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  BExCmd = new G4UIcmdWithADoubleAndUnit("/Backing/Excitation",this);
  BExCmd->SetGuidance("Set energy for backing recoil excitation");
  BExCmd->SetParameterName("choice",false);
  BExCmd->AvailableForStates(G4State_PreInit,G4State_Idle);
  
  BTauCmd = new G4UIcmdWithADoubleAndUnit("/Backing/Lifetime",this);
  BTauCmd->SetGuidance("Set lifetime for backing recoil excitation");
  BTauCmd->SetParameterName("choice",false);
  BTauCmd->AvailableForStates(G4State_PreInit,G4State_Idle);
  
  BRCmd = new G4UIcmdWithADoubleAndUnit("/Backing/Radius",this);
  BRCmd->SetGuidance("Select radius of the backing");
  BRCmd->SetParameterName("choice",false);
  BRCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  BZCmd = new G4UIcmdWithADoubleAndUnit("/Backing/Thickness",this);
  BZCmd->SetGuidance("Select the thickness for the backing");
  BZCmd->SetParameterName("choice",false);
  BZCmd->AvailableForStates(G4State_PreInit,G4State_Idle);
 

  BFrCmd = new G4UIcmdWithADouble("/Backing/ReactionFraction",this);
  BFrCmd->SetGuidance("Set reaction fraction on the backing");
  BFrCmd->SetParameterName("choice",false);
  BFrCmd->AvailableForStates(G4State_PreInit,G4State_Idle); 

  NBSCmd = new G4UIcmdWithAnInteger("/Backing/NStep",this);
  NBSCmd->SetGuidance("Select the number of steps in the backing");
  NBSCmd->SetParameterName("choice",false);
  NBSCmd->AvailableForStates(G4State_PreInit,G4State_Idle);
 

 
  BRepCmd = new G4UIcmdWithoutParameter("/Backing/Report",this);
  BRepCmd->SetGuidance("Report target and backing parameters");  
}



Target_Messenger::~Target_Messenger()
{
  delete BFrCmd;
  delete BMCmd;
  delete BQCmd;
  delete BExCmd;
  delete BTauCmd;
  delete BRCmd;
  delete BZCmd;
  delete BMatCmd;
  delete BackingDir;
  delete BRepCmd;
  delete NBSCmd;
}


void Target_Messenger::SetNewValue(G4UIcommand* command,G4String newValue)
{ 

if( command == BFrCmd )
   { aTarget->setFracReactionBacking(BFrCmd->GetNewDoubleValue(newValue));}


 if( command == BMCmd )
   { aTarget->setBackingMass(BMCmd->GetNewIntValue(newValue));}
 if( command == BQCmd )
   { aTarget->setBackingCharge(BQCmd->GetNewIntValue(newValue));}
  if( command == BExCmd )
   { aTarget->setBackingEx(BExCmd->GetNewDoubleValue(newValue));}
 if( command == BTauCmd )
   { aTarget->setBackingTau(BTauCmd->GetNewDoubleValue(newValue));}

 if( command == NBSCmd )
   { aTarget->setNBStep(NBSCmd->GetNewIntValue(newValue));}
 if( command == BRepCmd )
   { aTarget->Report();}

  if( command == BMatCmd )
   { aTarget->setBackingMaterial(newValue);} 
  if( command == BRCmd )
   { aTarget->setBackingR(BRCmd->GetNewDoubleValue(newValue));}
  if( command == BZCmd )
   { aTarget->setBackingZ(BZCmd->GetNewDoubleValue(newValue));}

}

