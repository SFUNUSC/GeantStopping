#ifndef Results_h
#define Results_h 1

#include "globals.hh"
#include "TROOT.h"
#include "TTree.h"
#include "TBranch.h"
#include "TStyle.h"
#include "TFile.h"
#include "TCanvas.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "TrackerIonSD.hh"
#include "Projectile.hh"
#include "Recoil.hh"
#include "Flags.hh"
#include "DetectorConstruction.hh"
#include "Materials.hh"
#include "TH1.h"
#include "TH2.h"
#include "TGraph.h"

#define PI     3.14159
#define S16K   16384
#define RADIAN 57.29583

typedef struct{
  Int_t evNb;
  Int_t Ap;
  Int_t Zp;
 } IonStat;

typedef struct{
    Double_t x;
    Double_t y;
    Double_t z;
    Double_t px;
    Double_t py;
    Double_t pz;
    Double_t E;
    Double_t b;
    Double_t w;
 } IonInf;
 
typedef struct{
    Double_t z;
    Double_t E;
    Double_t t;
    Double_t b;
 } IonDepthTracker;

class Results
{
public:
  Results(Projectile*,DetectorConstruction*);
  ~Results();

public:
  
  void SetupRun();

  void FillTree(G4int,TrackerIonHitsCollection*);
  void TreeSave(G4String);
  void TreeClear();
  void TreeCreate();
  void TreeReport();
  G4double CalculatePath(G4ThreeVector,G4ThreeVector);
private:
  
 // ROOT Tree stuff
  TTree *tree,*depthtree;
  G4int  IonFill;

  Projectile*           theProjectile;
  DetectorConstruction* theDetector;

  IonStat       stat;
  IonInf        gun,rTIn,rTOut,rStop; //ion tracking (projectile)
  IonDepthTracker       depthTracker;
  G4int         Ap,Zp;

  size_t soi,sos;
  
  G4double TargetFaceCrossSection;

  G4Material* a;
};

#endif


           
