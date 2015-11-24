#ifndef EventAction_h
#define EventAction_h 1

#include "G4UserEventAction.hh"
#include "TrackerIonSD.hh"
#include "G4Event.hh"
#include "G4TrajectoryContainer.hh"
#include "G4Trajectory.hh"
#include "G4ios.hh"
#include "globals.hh"
#include "G4UnitsTable.hh"
#include "Results.hh"
#include <sys/time.h>
#include "RunAction.hh"

/*
  Trigger settings notes:
  Gamma singles                      1
  user defined particle singles     10
  CsI particle-particle coinc       11
  trigger 10 AND 11                 12 (defined particle-particle coinc)
  trigger 1 AND 12                  13 (defined particle-particle coinc AND gamma singles)
 */

class EventAction : public G4UserEventAction
{
  public:
  EventAction(Results*,RunAction*,Projectile*);
   ~EventAction();
  void BeginOfEventAction(const G4Event*);
  void EndOfEventAction(const G4Event*);
  void SetTriggerValue(G4int value){setTrigger=value;};

  private:
  Results*      results;
  G4int         ionCollectionID;
  timeval       tc,ts,td;
  double        t,rate;
  RunAction*    run_action;
  size_t        soa,sov;
  unsigned long long int  one,eventTrigger,setTrigger,systemTrigger;
  Projectile* theProjectile;
  
};

#endif //EVENTACTION_H

    
