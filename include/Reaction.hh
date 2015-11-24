
#ifndef Reaction_h
#define Reaction_h 1
//atomic mass unit in MeV/c^2 
#define xamu 931.494061 

#include "G4ios.hh"
#include "globals.hh"
#include "G4VProcess.hh"
#include "DetectorConstruction.hh"
#include "GammaDecayChannel.hh"
#include "Projectile.hh"
#include "G4VParticleChange.hh"
#include "G4ParticleChange.hh"
#include "G4Track.hh"
#include "G4Step.hh"
#include "G4UnitsTable.hh"
#include "G4UserLimits.hh"
#include "G4DecayTable.hh"
#include "G4DynamicParticle.hh"
#include "G4ParticleTable.hh"
#include "G4Proton.hh"
#include "G4Neutron.hh"
#include "G4Alpha.hh"
#include "G4Track.hh"
#include "G4Decay.hh"
#include "G4RandomDirection.hh"
#include <math.h>

#include "CLHEP/Random/RandGamma.h" //for generating random numbers with a gaussian dist.

using namespace std;

#define  eps 0.00001
#define  MAXNUMEVAP 8
#define  MAXNUMDISTS 2

typedef struct
{
  G4String particle;
  G4double energy;
  G4double fwhm;
} evaporation;

class Reaction : public G4VProcess 
{
  public:     
   G4bool reaction_here;

  Reaction(Projectile*, const G4String& processName ="Reaction" );

     virtual ~Reaction();

 
 
    virtual G4double PostStepGetPhysicalInteractionLength(
                             const G4Track& track,
			     G4double   previousStepSize,
			     G4ForceCondition* condition
			    );

     virtual G4VParticleChange* PostStepDoIt(
			     const G4Track& ,
			     const G4Step& 
			    );
			    
     //  no operation in  AtRestGPIL
     virtual G4double AtRestGetPhysicalInteractionLength(
                             const G4Track& ,
			     G4ForceCondition* 
			    ){ return -1.0; };
			    
     //  no operation in  AtRestDoIt      
     virtual G4VParticleChange* AtRestDoIt(
			     const G4Track& ,
			     const G4Step&
			    ){return NULL;};

     //  no operation in  AlongStepGPIL
     virtual G4double AlongStepGetPhysicalInteractionLength(
                             const G4Track&,
			     G4double  ,
			     G4double  ,
			     G4double& ,
                             G4GPILSelection*
			    ){ return -1.0; };

     //  no operation in  AlongStepDoIt
     virtual G4VParticleChange* AlongStepDoIt(
			     const G4Track& ,
			     const G4Step& 
			    ) {return NULL;};

  
  void TargetFaceCrossSection();

  private:
 
  Projectile *theProjectile;

  G4ParticleDefinition* residual; //the residual nucleus after particles have evaporated from the compund nucleus
  G4ParticleDefinition* proton,*alpha,*neutron;
  G4ThreeVector posIn;
  G4double A1,Z1,A2,Z2;
  vector<evaporation> *history;
  
  G4int  loopCounter;
};

#endif

