#include "PrimaryGeneratorAction.hh"


PrimaryGeneratorAction::PrimaryGeneratorAction(DetectorConstruction *Det,Projectile* Proj): theProjectile(Proj), theDetector(Det)
{

  n_particle = 1;
  particleGun = new G4ParticleGun(n_particle);
 

}

PrimaryGeneratorAction::~PrimaryGeneratorAction()
{
  delete particleGun;
}

void PrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{
  



  particleTable = G4ParticleTable::GetParticleTable();

 
  ion =  particleTable->GetIon(theProjectile->getZ(),theProjectile->getA(),0.);
  particleGun->SetParticleDefinition(ion);
  
  
  position=theProjectile->getPosition();
  particleGun->SetParticlePosition(position);
      
  direction=theProjectile->getDirection();
  particleGun->SetParticleMomentumDirection(direction);
  
  KE=theProjectile->getKE();
  particleGun->SetParticleEnergy(KE);

  // G4cout<<" +++++ Generating an event "<<G4endl;
  particleGun->GeneratePrimaryVertex(anEvent);
  // G4cout<<" +++++ Out Generate Primaries "<<G4endl;
}