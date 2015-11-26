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
  G4cout << "Results: target A: " << theDetector->GetTarget()->getTargetMass() << ", target Z: " << theDetector->GetTarget()->getTargetCharge() << G4endl; 
  G4cout << "Results: projectile A: " << Ap << ", projectile Z: " << Zp << G4endl;
  //getc(stdin);
}
//---------------------------------------------------------
void Results::TreeCreate()
{
  tree= new TTree("tree","tree");
  tree->Branch("stat",&stat,"evNb/I:Ap/I:Zp/I");
  tree->Branch("projGun",&gun,"x/D:y/D:z/D:px/D:py/D:pz/D:E/D:b/D:w/D"); //projectile when shot from the particle gun
  tree->Branch("projTargetIn",&rTIn,"x/D:y/D:z/D:px/D:py/D:pz/D:E/D:b/D:w/D"); //projectile upon entering the target
  tree->Branch("projTargetOut",&rTOut,"x/D:y/D:z/D:px/D:py/D:pz/D:E/D:b/D:w/D"); //projectile upon leaving the target (if it makes it that far)
  tree->Branch("projStop",&rStop,"x/D:y/D:z/D:px/D:py/D:pz/D:E/D:b/D:w/D"); //projectile upon stopping
  depthtree= new TTree("depthtree","depthtree");
  depthtree->Branch("projStepData",&depthTracker,"z/D:E/D"); //data of the projectile depth/energy at each step of the simulation
}
//---------------------------------------------------------
void Results::TreeClear()
{
  tree->Delete("all");
  tree=NULL;
  depthtree->Delete("all");
  depthtree=NULL;
  TreeCreate();
}
//---------------------------------------------------------
void Results::TreeReport()
{
  tree->Print();
  depthtree->Print();
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
  depthtree->Write();
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
 memset(&rTIn,0,sizeof(rTIn));
 memset(&rTOut,0,sizeof(rTOut));
 memset(&rStop,0,sizeof(rStop));
 memset(&depthTracker,0,sizeof(depthTracker));

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
		                rTIn.x=(*IonCollection)[i]->GetPos().getX()/mm;
		                rTIn.y=(*IonCollection)[i]->GetPos().getY()/mm;
		                rTIn.z=(*IonCollection)[i]->GetPos().getZ()/mm;
		                rTIn.px=(*IonCollection)[i]->GetMom().getX()/MeV;
		                rTIn.py=(*IonCollection)[i]->GetMom().getY()/MeV;
		                rTIn.pz=(*IonCollection)[i]->GetMom().getZ()/MeV;
		                rTIn.b=(*IonCollection)[i]->GetBeta();
		                rTIn.E=(*IonCollection)[i]->GetKE()/MeV;		 
		                rTIn.w=(*IonCollection)[i]->GetWeight();
		              }
	          break;
	          case BACKING_OUT_FLAG:
	            if((*IonCollection)[i]->GetA()==Ap)
	              if((*IonCollection)[i]->GetZ()==Zp)
		              {
		                rTOut.x=(*IonCollection)[i]->GetPos().getX()/mm;
		                rTOut.y=(*IonCollection)[i]->GetPos().getY()/mm;
		                rTOut.z=(*IonCollection)[i]->GetPos().getZ()/mm;
		                rTOut.px=(*IonCollection)[i]->GetMom().getX()/MeV;
		                rTOut.py=(*IonCollection)[i]->GetMom().getY()/MeV;
		                rTOut.pz=(*IonCollection)[i]->GetMom().getZ()/MeV;
		                rTOut.b=(*IonCollection)[i]->GetBeta();
		                rTOut.E=(*IonCollection)[i]->GetKE()/MeV;		 
		                rTOut.w=(*IonCollection)[i]->GetWeight();
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
  
  //put all data for depth/energy along the track into the depthtree
  for(Int_t i=0;i<Nt;i++)
	  {
	    depthTracker.z=(*IonCollection)[i]->GetPos().getZ()/mm;
	    depthTracker.E=(*IonCollection)[i]->GetKE()/MeV;
	    depthtree->Fill();
	  }
	  
}
