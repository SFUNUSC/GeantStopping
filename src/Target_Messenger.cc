#include "Target_Messenger.hh"


Target_Messenger::Target_Messenger(Target* Tar)
:aTarget(Tar)
{ 
 
  TargetDir = new G4UIdirectory("/Target/");
  TargetDir->SetGuidance("Target control.");

  TMatCmd = new G4UIcmdWithAString("/Target/Material",this);
  TMatCmd->SetGuidance("Select material for the target.");
  TMatCmd->SetParameterName("choice",false);
  TMatCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  TMCmd = new G4UIcmdWithAnInteger("/Target/MassNumber",this);
  TMCmd->SetGuidance("Set the mass number A for the target.");
  TMCmd->SetParameterName("choice",false);
  TMCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  TQCmd = new G4UIcmdWithAnInteger("/Target/AtomicNumber",this);
  TQCmd->SetGuidance("Set the atomic number Z for the target.");
  TQCmd->SetParameterName("choice",false);
  TQCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  TExCmd = new G4UIcmdWithADoubleAndUnit("/Target/Excitation",this);
  TExCmd->SetGuidance("Set energy for target recoil excitation.");
  TExCmd->SetParameterName("choice",false);
  TExCmd->AvailableForStates(G4State_PreInit,G4State_Idle);
  
  TTauCmd = new G4UIcmdWithADoubleAndUnit("/Target/Lifetime",this);
  TTauCmd->SetGuidance("Set lifetime for target recoil excitation.");
  TTauCmd->SetParameterName("choice",false);
  TTauCmd->AvailableForStates(G4State_PreInit,G4State_Idle);
  
  TRCmd = new G4UIcmdWithADoubleAndUnit("/Target/Radius",this);
  TRCmd->SetGuidance("Select radius of the target.");
  TRCmd->SetParameterName("choice",false);
  TRCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  TZCmd = new G4UIcmdWithADoubleAndUnit("/Target/Thickness",this);
  TZCmd->SetGuidance("Select the thickness for the target.");
  TZCmd->SetParameterName("choice",false);
  TZCmd->AvailableForStates(G4State_PreInit,G4State_Idle);
 

  TFrCmd = new G4UIcmdWithADouble("/Target/ReactionFraction",this);
  TFrCmd->SetGuidance("Set reaction fraction on the target.");
  TFrCmd->SetParameterName("choice",false);
  TFrCmd->AvailableForStates(G4State_PreInit,G4State_Idle); 

  NTSCmd = new G4UIcmdWithAnInteger("/Target/NStep",this);
  NTSCmd->SetGuidance("Select the number of steps in the target.");
  NTSCmd->SetParameterName("choice",false);
  NTSCmd->AvailableForStates(G4State_PreInit,G4State_Idle);
 

 
  TRepCmd = new G4UIcmdWithoutParameter("/Target/Report",this);
  TRepCmd->SetGuidance("Report target parameters.");  
}



Target_Messenger::~Target_Messenger()
{
  delete TFrCmd;
  delete TMCmd;
  delete TQCmd;
  delete TExCmd;
  delete TTauCmd;
  delete TRCmd;
  delete TZCmd;
  delete TMatCmd;
  delete TargetDir;
  delete TRepCmd;
  delete NTSCmd;
}


void Target_Messenger::SetNewValue(G4UIcommand* command,G4String newValue)
{ 

if( command == TFrCmd )
   { aTarget->setFracReactionTarget(TFrCmd->GetNewDoubleValue(newValue));}


 if( command == TMCmd )
   { aTarget->setTargetMass(TMCmd->GetNewIntValue(newValue));}
 if( command == TQCmd )
   { aTarget->setTargetCharge(TQCmd->GetNewIntValue(newValue));}
  if( command == TExCmd )
   { aTarget->setTargetEx(TExCmd->GetNewDoubleValue(newValue));}
 if( command == TTauCmd )
   { aTarget->setTargetTau(TTauCmd->GetNewDoubleValue(newValue));}

 if( command == NTSCmd )
   { aTarget->setNTStep(NTSCmd->GetNewIntValue(newValue));}
 if( command == TRepCmd )
   { aTarget->Report();}

  if( command == TMatCmd )
   { aTarget->setTargetMaterial(newValue);} 
  if( command == TRCmd )
   { aTarget->setTargetR(TRCmd->GetNewDoubleValue(newValue));}
  if( command == TZCmd )
   { aTarget->setTargetZ(TZCmd->GetNewDoubleValue(newValue));}

}

