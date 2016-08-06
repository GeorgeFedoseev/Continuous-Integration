// Macro for displaying the tracks for the STT1 simulation
// only the STT1 detector is ON
// input file testrun.root contains the MC information
//13/09/2006 Pablo Genova
{

  gROOT->LoadMacro("$VMCWORKDIR/macro/mpd/mpdloadlibs.C");
  mpdloadlibs();                      // load main libraries

  gROOT->LoadMacro("$VMCWORKDIR/macro/mpd/geometry_v2.C");
  geometry_v2(0x0, kFALSE);
 
 
  TFile* f = new TFile("evetest.root");
  //  TGeoManager *geoMan = (TGeoManager*) f->Get("FAIRGeom");

  //TFile* f = new TFile("testparams.root");
  f->Get("FairBaseParSet");
  TGeoManager *geoMan = gGeoManager;

  
//   gPad->x3d("OPENGL");
//   viewGL3D = (TPadOpenGLView*)gPad->GetView3D();
//   viewGL3D->MoveModelView('t'); // switch to natural light mode

  TCanvas* c1 = new TCanvas("c1", "", 100, 100, 800, 800);
  //  viewGL3D->GetViewer3D();
  //  viewGL3D = (TPadOpenGLView*)c1->GetView3D();
  //  viewGL3D->MoveModelView('t'); // switch to natural light mode
  //c1->SetFillColor(10);

  geoMan->SetVisLevel(4);
  geoMan->GetMasterVolume()->Draw("same");
  

  TView* view = c1->GetView();
  view->Top();
  view->Zoom();
  //  view->SetRange(-5.,-5., 0., 5., 5., 0., 1);
  //  view->Centered();
  view->SetParallel();

  //drawing tracks

#if 0
/*   gamma
    * pi+
    * K+
    * proton
    * pi-
    * K-
    * pi0
    * K0
    * neutron
    * e-
    * mu-
    * e+
    * mu+ 
*/



  TTree *t=file->Get("cbmsim") ;
   
  TClonesArray *fT = new TClonesArray("TGeoTrack");

  t->SetBranchAddress("GeoTracks",&fT) ;

  TGeoTrack *tr;
  TGeoTrack *tr1;
  
  //  for (Int_t j=0; j< t->GetEntriesFast(); j++)	{
  for (Int_t j=0; j< 1; j++)	{
    t->GetEntry(j,0);
#if 1
    for (Int_t i=0; i<fT->GetEntriesFast(); i++)	{
      tr=(TGeoTrack *)fT->At(i);
      tr->Draw("/proton same");
    }
#endif
  }

#endif

}
