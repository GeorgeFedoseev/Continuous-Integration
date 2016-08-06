// Macro for running MPD simulation with GEANTINO to exclude interactions

void RadLenSim(Int_t nStartEvent = 0, Int_t nEvents = 500, TString outFile = "RadLenSim.root") {

  gROOT->LoadMacro("$VMCWORKDIR/macro/mpd/mpdloadlibs.C");
  mpdloadlibs(1,1);                 // load main libraries

  FairRunSim *fRun = new FairRunSim();
  
  fRun->SetName("TGeant3");
  fRun->SetOutputFile(outFile.Data()); //output file
  gROOT->LoadMacro("$VMCWORKDIR/macro/mpd/geometry_stage1.C");
  geometry_stage1(fRun, kTRUE);    // load mpd standard geometries

  FairPrimaryGenerator* primGen = new FairPrimaryGenerator();
  fRun->SetGenerator(primGen); 
  
  FairBoxGenerator* boxGen = new FairBoxGenerator(0, 100); // 0 = geantino - required for RadLen Simulation
  boxGen->SetPRange(.2,.2); // GeV/c
  boxGen->SetPhiRange(0, 360); 
  boxGen->SetThetaRange(0, 180); 
  boxGen->SetXYZ(0., 0., 0.);
  primGen->AddGenerator(boxGen); 

  fRun->SetStoreTraj(kFALSE);
  fRun->SetRadLenRegister(kTRUE); // radiation length manager 

  fRun->Init(); 


  // Fill the Parameter containers for this run
  //-------------------------------------------

  FairRuntimeDb *rtdb=fRun->GetRuntimeDb();
  rtdb->print();


  fRun->Run(nEvents); 
}  
