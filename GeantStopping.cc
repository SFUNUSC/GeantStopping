//Program for testing different stopping powers in GEANT4

#include "G4RunManager.hh"
#include "G4UImanager.hh"

#ifdef G4UI_USE_ROOT
#include "G4UIRoot.hh"
#else
#include "G4UIterminal.hh"
#include "G4UItcsh.hh"
#endif

#ifdef G4UI_USE_XM
#include "G4UIXm.hh"
#endif


#ifdef G4VIS_USE
#include "VisManager.hh"
#endif


#include "DetectorConstruction.hh"
#include "PhysicsList.hh"
#include "PrimaryGeneratorAction.hh"
#include "EventAction.hh"
#include "EventAction_Messenger.hh"
#include "Results.hh"
#include "Results_Messenger.hh"
#include "Projectile.hh"
#include "Projectile_Messenger.hh"
#include "Run_Messenger.hh"
#include "RunAction.hh"

int main(int argc,char** argv) 
{
  if(argc<=1)
    {
      G4cout<<G4endl<<"GeantStopping batch_file"<<G4endl;
      G4cout<<"------------------------"<<G4endl<<G4endl;
      G4cout<<"Simulates the stopping of a user defined ion with user defined energy distribution in a stopper made of user defined material.  It is possible to specify custom stopping power tables."<<G4endl<<G4endl;
      exit(-1);
    }

 // Seed the random number generator manually
  G4long myseed = time(NULL);
  //myseed=1388637269;
  CLHEP::HepRandom::setTheSeed(myseed);
  G4cout<<" Seed set to  "<<myseed<<G4endl;


  // Construct the default run manager
  G4RunManager* runManager = new G4RunManager;
 
  // set mandatory initialization classes
  DetectorConstruction* theDetector=new DetectorConstruction();
  runManager->SetUserInitialization(theDetector);
 
  // Construct the incoming beam
  Projectile* theProjectile=new Projectile();
  Projectile_Messenger* ProjectileMessenger;
  ProjectileMessenger=new Projectile_Messenger(theProjectile);
  theProjectile->Report();
 
  // set mandatory user action clas
  PhysicsList *thePhysicsList = new PhysicsList(theProjectile);
  runManager->SetUserInitialization(thePhysicsList);
  
  Run_Messenger* runMessenger;
  runMessenger = new Run_Messenger(runManager,thePhysicsList);
 
  PrimaryGeneratorAction* generatorAction= new PrimaryGeneratorAction(theDetector,theProjectile);
  runManager->SetUserAction(generatorAction);

  Results* results = new Results(theProjectile,theDetector);
  Results_Messenger* resultsMessenger;
  resultsMessenger = new Results_Messenger(results);

  RunAction* theRunAction=new RunAction(thePhysicsList,results,theDetector);
  runManager->SetUserAction(theRunAction);
 
  //EventAction* eventAction = new EventAction(results,theRunAction);
  EventAction* eventAction = new EventAction(results,theRunAction,theProjectile);
  runManager->SetUserAction(eventAction);
  EventAction_Messenger* eventActionMessenger;
  eventActionMessenger = new EventAction_Messenger(eventAction); 

  // get the pointer to the UI manager and set verbosities
  G4UImanager* UI = G4UImanager::GetUIpointer();

  // Read batch file
  G4String command = "/control/execute ";
  G4String fileName = argv[1];
  UI->ApplyCommand(command+fileName);
  
  
  delete ProjectileMessenger;
  delete resultsMessenger;
  delete eventActionMessenger;
  delete runMessenger;
  delete runManager;

  return 0;
}
