#include "Results.hh"

Results::Results(Projectile* proj,DetectorConstruction* det):theProjectile(proj),theDetector(det)
{
  TreeCreate();
  IonFill=0;
  soi=sizeof(gun);
  sos=sizeof(stat);
}

Results::~Results()
{
tree->Delete();
}
//---------------------------------------------------------
void Results::SetupRun()
{
  //Get A, Z of the projectile and recoiling residual (needed for particle identification when saving data to tree)
  Ap=theProjectile->getA();
  Zp=theProjectile->getZ();
  G4cout << "Results: backing A: " << theDetector->GetTarget()->getBackingMass() << ", backing Z: " << theDetector->GetTarget()->getBackingCharge() << G4endl; 
  G4cout << "Results: projectile A: " << Ap << ", projectile Z: " << Zp << G4endl;
  //getc(stdin);
}
//---------------------------------------------------------
void Results::TreeCreate()
{
  tree= new TTree("tree","tree");
  tree->Branch("stat",&stat,"evNb/I:Ap/I:Zp/I");
  tree->Branch("projGun",&gun,"x/D:y/D:z/D:px/D:py/D:pz/D:E/D:b/D:w/D"); //projectile when shot from the particle gun
  tree->Branch("resBackingIn",&rBIn,"x/D:y/D:z/D:px/D:py/D:pz/D:E/D:b/D:w/D"); //residual upon leaving the target/entering the backing
  tree->Branch("resBackingOut",&rBOut,"x/D:y/D:z/D:px/D:py/D:pz/D:E/D:b/D:w/D"); //residual upon leaving the backing (if it makes it that far)
  tree->Branch("resStop",&rStop,"x/D:y/D:z/D:px/D:py/D:pz/D:E/D:b/D:w/D"); //residual upon decaying via gamma emission (decay flag not yet implemented)
}
//---------------------------------------------------------
void Results::TreeClear()
{
  tree->Delete("all");
  tree=NULL;
  TreeCreate();
}
//---------------------------------------------------------
void Results::TreeReport()
{
  tree->Print(); 
}
//---------------------------------------------------------
void Results::TreeSave(G4String name)
{
  TDirectory *dir=new TDirectory();
  dir=gDirectory;
  TFile f(name,"recreate");
  f.cd();
  //tree->AutoSave();
  //tree->SetDirectory(dir);
  tree->Write();
  f.Close();
  dir->cd();
  G4cout<<"Tree of simulated parameters saved in file "<<name<<G4endl;
  
}
//---------------------------------------------------------
void Results::FillTree(G4int evtNb, TrackerIonHitsCollection* IonCollection)
{

 G4int Nt=IonCollection->entries();
 
 memset(&stat,0,sizeof(stat));
 memset(&gun,0,sizeof(gun));
 memset(&rBIn,0,sizeof(rBIn));
 memset(&rBOut,0,sizeof(rBOut));
 memset(&rStop,0,sizeof(rStop));

  if(Nt>0)
    {
      //G4cout << "Saving ion collection data..." << G4endl; 
      stat.evNb=evtNb;
      stat.Ap=Ap;
      stat.Zp=Zp;
 
      for(Int_t i=0;i<Nt;i++)
        switch((*IonCollection)[i]->GetFlag())
          {
	          case GUN_FLAG:
	            if((*IonCollection)[i]->GetA()==Ap)
	              if((*IonCollection)[i]->GetZ()==Zp)
	                {
		                gun.x=(*IonCollection)[i]->GetPos().getX()/mm;
		                gun.y=(*IonCollection)[i]->GetPos().getY()/mm;
		                gun.z=(*IonCollection)[i]->GetPos().getZ()/mm;
		                gun.px=(*IonCollection)[i]->GetMom().getX()/MeV;
		                gun.py=(*IonCollection)[i]->GetMom().getY()/MeV;
		                gun.pz=(*IonCollection)[i]->GetMom().getZ()/MeV;
		                gun.b=(*IonCollection)[i]->GetBeta();
		                gun.E=(*IonCollection)[i]->GetKE()/MeV;		 
		                gun.w=(*IonCollection)[i]->GetWeight();

		              }
	          break;
	          case BACKING_IN_FLAG:
	            if((*IonCollection)[i]->GetA()==Ap)
	              if((*IonCollection)[i]->GetZ()==Zp)
	                {
		                rBIn.x=(*IonCollection)[i]->GetPos().getX()/mm;
		                rBIn.y=(*IonCollection)[i]->GetPos().getY()/mm;
		                rBIn.z=(*IonCollection)[i]->GetPos().getZ()/mm;
		                rBIn.px=(*IonCollection)[i]->GetMom().getX()/MeV;
		                rBIn.py=(*IonCollection)[i]->GetMom().getY()/MeV;
		                rBIn.pz=(*IonCollection)[i]->GetMom().getZ()/MeV;
		                rBIn.b=(*IonCollection)[i]->GetBeta();
		                rBIn.E=(*IonCollection)[i]->GetKE()/MeV;		 
		                rBIn.w=(*IonCollection)[i]->GetWeight();
		              }
	          break;
	          case BACKING_OUT_FLAG:
	            if((*IonCollection)[i]->GetA()==Ap)
	              if((*IonCollection)[i]->GetZ()==Zp)
		              {
		                rBOut.x=(*IonCollection)[i]->GetPos().getX()/mm;
		                rBOut.y=(*IonCollection)[i]->GetPos().getY()/mm;
		                rBOut.z=(*IonCollection)[i]->GetPos().getZ()/mm;
		                rBOut.px=(*IonCollection)[i]->GetMom().getX()/MeV;
		                rBOut.py=(*IonCollection)[i]->GetMom().getY()/MeV;
		                rBOut.pz=(*IonCollection)[i]->GetMom().getZ()/MeV;
		                rBOut.b=(*IonCollection)[i]->GetBeta();
		                rBOut.E=(*IonCollection)[i]->GetKE()/MeV;		 
		                rBOut.w=(*IonCollection)[i]->GetWeight();
	                }
		        break;
		        case STOPPED_FLAG:	   
	            if((*IonCollection)[i]->GetA()==Ap)
                if((*IonCollection)[i]->GetZ()==Zp)
	                {
		                rStop.x=(*IonCollection)[i]->GetPos().getX()/mm;
		                rStop.y=(*IonCollection)[i]->GetPos().getY()/mm;
		                rStop.z=(*IonCollection)[i]->GetPos().getZ()/mm;
		                rStop.px=(*IonCollection)[i]->GetMom().getX()/MeV;
		                rStop.py=(*IonCollection)[i]->GetMom().getY()/MeV;
		                rStop.pz=(*IonCollection)[i]->GetMom().getZ()/MeV;
		                rStop.b=(*IonCollection)[i]->GetBeta();
		                rStop.E=(*IonCollection)[i]->GetKE()/MeV;		 
		                rStop.w=(*IonCollection)[i]->GetWeight();
                  }
	          break;

            default:
	            break;
	        }
    }
   
  tree->Fill();
  IonFill++;
}
