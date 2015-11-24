#ifndef Target_Messenger_h
#define Target_Messenger_h 1

#include "Target.hh"
#include "globals.hh"
#include "G4UImessenger.hh"
#include "G4UIdirectory.hh"
#include "G4UIcmdWithAString.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"
#include "G4UIcmdWithADouble.hh"
#include "G4UIcmdWithoutParameter.hh"
#include "G4UIcmdWithAnInteger.hh"

class Target_Messenger: public G4UImessenger
{
  public:
    Target_Messenger(Target*);
   ~Target_Messenger();
    
    void SetNewValue(G4UIcommand*, G4String);
    
  private:
    Target* aTarget;
    
    G4UIdirectory*             BackingDir;
    G4UIcmdWithAString*        BMatCmd;  
    G4UIcmdWithAnInteger*      BMCmd;
    G4UIcmdWithAnInteger*      BQCmd;
    G4UIcmdWithADoubleAndUnit* BExCmd;
    G4UIcmdWithADoubleAndUnit* BTauCmd;
    G4UIcmdWithADoubleAndUnit* BRCmd;
    G4UIcmdWithADoubleAndUnit* BZCmd;
    G4UIcmdWithoutParameter*   BRepCmd;
    G4UIcmdWithAnInteger*      NBSCmd;
    G4UIcmdWithADouble*        BFrCmd;

};


#endif

