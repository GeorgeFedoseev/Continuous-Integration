geometry_v2 (FairRunSim *fRun, Bool_t build){
  // load libs and build detector geometry

  if (!build) {
    gSystem->Load("libtpc");
    gSystem->Load("libTof");
    gSystem->Load("libEtof");
    gSystem->Load("libEmc");
    gSystem->Load("libZdc");
    gSystem->Load("libStrawendcap");
    gSystem->Load("libStt");
    gSystem->Load("libSts");

    gSystem->Load("libBbc");
    gSystem->Load("libCpc");
    gSystem->Load("libFsa");
    gSystem->Load("libFfd");
  }
  else {
    // Set Material file Name
    fRun->SetMaterials("media.geo");
  
    // Create and add detectors
    //-------------------------

    FairModule *Cave= new FairCave("CAVE");
    Cave->SetGeometryFileName("cave.geo");
    fRun->AddModule(Cave);

    FairModule *Pipe= new FairPipe("PIPE");
    Pipe->SetGeometryFileName("pipe.geo");
    fRun->AddModule(Pipe);
  
    FairModule *Magnet= new FairMagnet("MAGNET");
    Magnet->SetGeometryFileName("magnet_v4_0.geo");
    fRun->AddModule(Magnet);

    //   Silicon Tracker Stations
    FairDetector *Sts= new MpdSts("STS", kTRUE);
    Sts->SetGeometryFileName("its_cables.geo");
    fRun->AddModule(Sts);

     FairDetector *Ffd = new MpdFfd("FFD",kTRUE );
     Ffd->SetGeometryFileName("ffd.geo");
     fRun->AddModule(Ffd);

    FairDetector *Tpc = new TpcDetector("TPC", kTRUE);
   Tpc->SetGeometryFileName("tpc_v6.geo");
    fRun->AddModule(Tpc);
  
    FairDetector *Tof= new MpdTof("TOF", kTRUE );
    Tof->SetGeometryFileName("tof_v3.geo");
    fRun->AddModule(Tof);
	
    FairDetector *eTof= new MpdEtof("ETOF", kTRUE );
    eTof->SetGeometryFileName("etof_v4.geo");
    fRun->AddModule(eTof);

    FairDetector *Emc= new MpdEmc("ECAL", kTRUE);
    Emc->SetGeometryFileName("emc_tr.geo");
    fRun->AddModule(Emc);

    FairDetector *straw_ecStt= new MpdStrawendcap("ESTT", kTRUE);
    straw_ecStt->SetGeometryFileName("ect_v2.geo");
    fRun->AddModule(straw_ecStt);

//     FairDetector *Bbc = new MpdBbc("BBC",kTRUE );
//     Bbc->SetGeometryFileName("bbc.geo");
//     fRun->AddModule(Bbc);

    FairDetector *Cpc = new MpdCpc("CPC",kTRUE );
    Cpc->SetGeometryFileName("cpc.geo");
    fRun->AddModule(Cpc);
	
    FairDetector *Zdc = new MpdZdc("ZDC",kTRUE );
    Zdc->SetGeometryFileName("zdc_10x10_modules96_layers40_16_4.geo");
    fRun->AddModule(Zdc);

    //FairDetector *Fsa = new MpdFsa("FSA",kTRUE );
    //Fsa->SetGeometryFileName("fsa.geo");
    //fRun->AddModule(Fsa);

  }

}
