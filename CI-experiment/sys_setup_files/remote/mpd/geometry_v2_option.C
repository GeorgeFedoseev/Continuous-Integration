geometry_v2_option (FairRunSim *fRun, Bool_t build,
		    char *option_changed_one="",char *option_geometry_file="",
		    Bool_t use_other_detectors=kTRUE)
{
  //
  //  Created 26-Dec-2008  litvin  (extended from geometry_v2.C)
  //  edited by gertsen for geometry version №2
  //
  //     Usage:
  //  geometry_v2_option (0x0, kFALSE)  - simply load libraries for MPD detectors;
  //  geometry_v2_option (fRun,kTRUE)   - use standard geometries for all detectors;
  //  geometry_v2_option (fRun,kTRUE,"ETOF","tst_etof_geometry.geo") - change only ETOF geometry;
  //  geometry_v2_option (fRun,kTRUE,"TPC","tst_tpc_geometry.geo",kFALSE) - change only TPC
  //                                                   geometry and switch OFF other detectors.
  //  option_changed_one possible values: "STS","TPC","TOF","ETOF","ESTT","ZDC","BBC","FSA","CPC","FFD"


  if (!build) {   // do the same as geometry_v2.C lo load the libraries

    gROOT->LoadMacro("$VMCWORKDIR/macro/mpd/geometry_v2.C");
    geometry_v2(0x0, kFALSE);

  }
  else {

Bool_t
  use_TPC = kTRUE,
  use_TOF = kTRUE,
  use_ETOF = kTRUE,
  use_EMC = kTRUE,
  use_ESTT = kTRUE,
  use_STS = kTRUE,
  use_ZDC = kTRUE,
  use_BBC = kFALSE , // kTRUE,
  use_FSA = kTRUE,
  use_CPC = kTRUE,
  use_FFD = kTRUE,
;


 TString toption_changed_one = option_changed_one;

 if (!use_other_detectors) {
   use_TPC = (toption_changed_one=="TPC");
   use_TOF = (toption_changed_one=="TOF");
   use_ETOF =(toption_changed_one=="ETOF");
   use_EMC = (toption_changed_one=="EMC");
   use_ESTT =(toption_changed_one=="ESTT");
   use_ZDC = (toption_changed_one=="ZDC");
   use_STS = (toption_changed_one=="STS");
   use_BBC = (toption_changed_one=="BBC");
   use_FSA = (toption_changed_one=="FSA");
   use_CPC = (toption_changed_one=="CPC");
   use_FFD = (toption_changed_one=="FFD");
 }

 TString sts_geometry = "its_cables.geo";
 TString tpc_geometry = "tpc_v6.geo";
 TString tof_geometry = "tof_v3.geo";
 TString etof_geometry = "etof_v43.geo";
 TString emc_geometry = "emc_tr.geo";
 TString estt_geometry = "ect_v2.geo";    // "straw_60_layers.geo";
 TString zdc_geometry = "zdc_10x10_modules96_layers40_16_4.geo";
 TString bbc_geometry = "bbc.geo";
 TString fsa_geometry = "fsa.geo";
 TString cpc_geometry = "cpc.geo";
 TString ffd_geometry = "ffd.geo";

 if ((!(toption_changed_one==""))&&(!(option_geometry_file==""))) {
   if (toption_changed_one=="STS") sts_geometry = option_geometry_file;
   else
     if (toption_changed_one=="TPC") tpc_geometry = option_geometry_file;
     else
       if (toption_changed_one=="TOF") tof_geometry = option_geometry_file;
       else
	 if (toption_changed_one=="ETOF") etof_geometry = option_geometry_file;
	 else
	   if (toption_changed_one=="EMC") emc_geometry = option_geometry_file;
	   else
	     if (toption_changed_one=="ESTT") estt_geometry = option_geometry_file;
	     else
	       if (toption_changed_one=="ZDC") zdc_geometry = option_geometry_file;
	       else
		 if (toption_changed_one=="BBC") bbc_geometry = option_geometry_file;
		 else
		   if (toption_changed_one=="FSA") fsa_geometry = option_geometry_file;
		   else
		     if (toption_changed_one=="CPC") cpc_geometry = option_geometry_file;
		     else
		       if (toption_changed_one=="FFD") ffd_geometry = option_geometry_file;
 }

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

    if (use_STS) {
      FairDetector *Sts= new MpdSts("STS", kTRUE);
      Sts->SetGeometryFileName(sts_geometry);
      fRun->AddModule(Sts);
    }

    if (use_FFD) {
      FairDetector *Ffd = new MpdFfd("FFD",kTRUE );
      Ffd->SetGeometryFileName(ffd_geometry);
      fRun->AddModule(Ffd);
    }

    if (use_TPC) {
      FairDetector *Tpc = new TpcDetector("TPC", kTRUE);
      Tpc->SetGeometryFileName(tpc_geometry);
      fRun->AddModule(Tpc);
    }
  
    if (use_TOF) {
      FairDetector *Tof= new MpdTof("TOF", kTRUE );
      Tof->SetGeometryFileName(tof_geometry);
      fRun->AddModule(Tof);
    }
	
    if (use_ETOF) {
      FairDetector *eTof= new MpdEtof("ETOF", kTRUE );
      eTof->SetGeometryFileName(etof_geometry);
      fRun->AddModule(eTof);
    }

  
    if (use_EMC) {
      FairDetector *Emc= new MpdEmc("ECAL", kTRUE);
      Emc->SetGeometryFileName(emc_geometry);
      fRun->AddModule(Emc);
    }
    	
    if (use_ESTT) {
      FairDetector *straw_ecStt= new MpdStrawendcap("ESTT", kTRUE);
      straw_ecStt->SetGeometryFileName(estt_geometry);
      fRun->AddModule(straw_ecStt);
    }
	
    	
    if (use_BBC) {
      FairDetector *Bbc = new MpdBbc("BBC",kTRUE );
      Bbc->SetGeometryFileName(bbc_geometry);
      fRun->AddModule(Bbc);
    }
	
    if (use_CPC) {
      FairDetector *Cpc = new MpdCpc("CPC",kTRUE );
      Cpc->SetGeometryFileName(cpc_geometry);
      fRun->AddModule(Cpc);
    }
    	
    if (use_ZDC) {
      FairDetector *Zdc = new MpdZdc("ZDC",kTRUE );
      Zdc->SetGeometryFileName(zdc_geometry);
      fRun->AddModule(Zdc);
    }

    if (use_FSA) {
      FairDetector *Fsa = new MpdFsa("FSA",kTRUE );
      Fsa->SetGeometryFileName(fsa_geometry);
      fRun->AddModule(Fsa);
    }
  }
}
