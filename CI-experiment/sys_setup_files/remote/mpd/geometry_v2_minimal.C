//*************************************************
//  Version:    09-Jun-2012   (EL)
//*************************************************
geometry_v2_minimal (FairRunSim *fRun)
{

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

    FairDetector *Tpc = new TpcDetector("TPC", kTRUE);
    Tpc->SetGeometryFileName("tpc_v6.geo");
    fRun->AddModule(Tpc);
  
//     FairDetector *Tof= new MpdTof("TOF", kTRUE );
//     Tof->SetGeometryFileName("tof_v3.geo");
//     fRun->AddModule(Tof);

	
     FairDetector *Zdc = new MpdZdc("ZDC",kTRUE );
     //     Zdc->SetGeometryFileName("zdc_modules420_layers60_610_50new.geo");
     Zdc->SetGeometryFileName("zdc_10x10_modules96_layers40_16_4.geo");
     fRun->AddModule(Zdc);
}
