void show(Int_t flag_what=0)
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

  TCanvas* c1 = new TCanvas("c1", "", 100, 100, 800, 800);
  c1->SetFillColor(10);

  geoMan->SetVolumeAttribute("*","colo fill",kYellow-10); 
  geoMan->SetVolumeAttribute("pipe1","colo fill",9);
  geoMan->SetVolumeAttribute("ms01yokebarrel","colo fill",kGray+1);
  geoMan->SetVolumeAttribute("ms01yokeendin","colo fill",kRed-8); 
  geoMan->SetVolumeAttribute("ms01yokeendout","colo fill",kRed-8); 
  geoMan->SetVolumeAttribute("ms01cryostat","colo fill",kSpring+4); // kCyan-8);
  geoMan->SetVolumeAttribute("ms01solenoid","colo fill",kRed+1);
  geoMan->SetVolumeAttribute("etof1","colo fill",kAzure-6);
  geoMan->SetVolumeAttribute("tof1","colo fill",kAzure+2);
  geoMan->SetVolumeAttribute("tpcChamber1","colo fill",kOrange+2);
  geoMan->SetVolumeAttribute("tpc01","colo fill",25);
  geoMan->SetVolumeAttribute("stt01layer","colo fill",kMagenta);
  geoMan->SetVolumeAttribute("zdc01m","colo fill",kRed+1);

  geoMan->GetMasterVolume()->Draw("ogl");
  TView* view = c1->GetView();
  view->SideView();

  geoMan->SetVisLevel(2);   // comment this line for some sub-detectors
}
