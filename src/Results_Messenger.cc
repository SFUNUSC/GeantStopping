#include "Results_Messenger.hh"


Results_Messenger::Results_Messenger(Results* Res) :results(Res) 
{ 

  ResDir = new G4UIdirectory("/Results/");
  ResDir->SetGuidance("Output control.");
 
  TreDir = new G4UIdirectory("/Results/Tree/");
  TreDir->SetGuidance("Root tree control.");

  TSCmd = new G4UIcmdWithAString("/Results/Tree/Save",this);
  TSCmd->SetGuidance("Save the ROOT tree of simulated parameters");
  TSCmd->SetParameterName("file name",false);
  TSCmd->AvailableForStates(G4State_PreInit,G4State_Idle);
  TSCmd->SetDefaultValue("test.root");
  
  TRepCmd = new G4UIcmdWithoutParameter("/Results/Tree/Report",this);
  TRepCmd->SetGuidance("Report parameters for the Root tree");

}

Results_Messenger::~Results_Messenger()
{
  delete ResDir;
  delete TreDir;
  delete TSCmd;
  delete TRepCmd;
}



void Results_Messenger::SetNewValue(G4UIcommand* command,G4String newValue)
{ 
 
  if( command == TSCmd )
    { results->TreeSave(newValue);}
    
  if( command == TRepCmd )
    { results->TreeReport();}

}
