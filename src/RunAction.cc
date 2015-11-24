#include "RunAction.hh"

 
RunAction::RunAction(PhysicsList* PL,Results* Res,DetectorConstruction* Det): thePhysicsList(PL), theResults(Res), theDetector(Det)
{
  
}


RunAction::~RunAction()
{

}

void RunAction::BeginOfRunAction(const G4Run*)
{
  //G4double At,Zt;
  G4cout<<" Beginning of run "<<G4endl;
  gettimeofday(&ts,NULL);

  theResults->SetupRun();
}


 
void RunAction::EndOfRunAction(const G4Run*)
{
  G4cout<<" End of run "<<G4endl;
}

