#include "EventAction_Messenger.hh"


EventAction_Messenger::EventAction_Messenger(EventAction* Chamb)
  :aEventAction(Chamb)
{ 
 
  EventActionDir = new G4UIdirectory("/Trigger/");
  EventActionDir->SetGuidance("Trigger control.");
 

  STCmd = new G4UIcmdWithAnInteger("/Trigger/SetTrigger",this);
  STCmd->SetGuidance("Select the trigger to use.");
  //STCmd->SetParameterName(Trigger Z",false);
  STCmd->AvailableForStates(G4State_PreInit,G4State_Idle);



}



EventAction_Messenger::~EventAction_Messenger()
{

  delete EventActionDir;
  delete STCmd;
}


void EventAction_Messenger::SetNewValue(G4UIcommand* command,G4String newValue)
{ 

 if( command == STCmd )
   { aEventAction->SetTriggerValue(STCmd->GetNewIntValue(newValue));}

}

