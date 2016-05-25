#include "EventAction.hh"

 
EventAction::EventAction(Results* RE,RunAction* RA,Projectile* proj):results(RE),run_action(RA),theProjectile(proj)
  {
    ionCollectionID=-1;
    SetTriggerValue(1);
  }


EventAction::~EventAction()
  {
    ;
  }

void EventAction::BeginOfEventAction(const G4Event*)
  { 
    G4SDManager * SDman = G4SDManager::GetSDMpointer();

    if(ionCollectionID<0)
      ionCollectionID=SDman->GetCollectionID("ionCollection");

    // G4cout<<"+++++ Begin of event "<<evt->GetEventID()<<G4endl;
  }


 
void EventAction::EndOfEventAction(const G4Event* evt)
{
  // G4cout<<"+++++ End of event "<<evt->GetEventID()<<G4endl;

  G4int evtNb=evt->GetEventID();

  if (evtNb%100 == 0) 
    {
      gettimeofday(&tc,NULL);
      ts=run_action->GetStartTime();
      timersub(&tc,&ts,&td);
      t=td.tv_sec;
      rate=(float)evtNb/t;
      G4cout<<" Number of processed events "<<std::setw(9)<<evtNb<<" in "<<std::setw(9)<<t<<" sec. at "<<std::fixed<<std::setw(9)<<std::setprecision(2)<<rate<<" events per second\r"<<std::flush;

  }

  //G4cout<<"ion collection ID: " << ionCollectionID << G4endl;
  one=1;
  eventTrigger=1;

  G4HCofThisEvent * HCE = evt->GetHCofThisEvent();
  TrackerIonHitsCollection* HI = new TrackerIonHitsCollection();
  //G4int Np;
  
  if(HCE!=NULL)
    HI=(TrackerIonHitsCollection*)(HCE->GetHC(ionCollectionID));
  
  // Trigger 1 (for now always true)
  if(true)
    eventTrigger|=(one<<1);
  
  if(eventTrigger&(one<<setTrigger))
    {
	    results->FillTree(evtNb,HI);
      //G4cout<<"Event fulfills trigger condition "<<setTrigger<<G4endl;
    }
  //getc(stdin);
}
