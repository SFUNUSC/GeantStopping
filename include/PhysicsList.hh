#ifndef PhysicsList_h
#define PhysicsList_h 1

#include "G4VUserPhysicsList.hh"
#include "G4ParticleTypes.hh"
#include "G4ProcessManager.hh"


//gamma

#include "G4ComptonScattering.hh"
#include "G4GammaConversion.hh"
#include "G4PhotoElectricEffect.hh"

//e-/e+
#include "G4eBremsstrahlung.hh"
#include "G4eIonisation.hh"
#include "G4eMultipleScattering.hh"
#include "G4eplusAnnihilation.hh"
// ions
#include "G4ionIonisation.hh"
#include "G4hIonisation.hh"
#include "G4IonTable.hh"
#include "G4IonConstructor.hh"
#include "G4StepLimiter.hh"
#include "G4hMultipleScattering.hh"
#include "G4IonCustomModel.hh"
#include "G4NuclearStopping.hh"
#include "G4IonCustomStoppingData.hh"
#include "G4IonDEDXScalingICRU73.hh"

//neutrons
#include "G4LElastic.hh"
#include "G4LFission.hh"
#include "G4LCapture.hh"
#include "G4LENeutronInelastic.hh"
#include "G4NeutronInelasticProcess.hh"
#include "G4HadronFissionProcess.hh"
#include "G4HadronCaptureProcess.hh"
#include "G4HadronElasticProcess.hh"

#include "G4BosonConstructor.hh"
#include "G4LeptonConstructor.hh"
#include "G4MesonConstructor.hh"
#include "G4BaryonConstructor.hh"


#include "Projectile.hh"
#include "Reaction.hh"

class PhysicsList: public G4VUserPhysicsList
{
  public:
  PhysicsList(Projectile*);
    ~PhysicsList();
  
  Reaction* getReaction(){return theReaction;};
  void setStepSize(double ss){stepSize=ss;};
  void setcs(){customStopping=true;};
  void setcspath(const char * csp){strcpy(cspath,csp);};

  protected:
    // Construct particle and physics process
  void ConstructParticle();
  void ConstructProcess();
  void ConstructEM();
  void SetCuts();
  

 private:
  Projectile *theProjectile;
  Reaction *theReaction;
  double stepSize;
  bool customStopping;
  char cspath[256];
};

#endif







