void mpdloadlibs (Bool_t reco=kFALSE,Bool_t detectors=kFALSE )
{
  // Load basic libraries
  gROOT->LoadMacro("$VMCWORKDIR/gconfig/basiclibs.C");
  basiclibs();
  // Load other libraries
  gSystem->Load("libFairTools");
  gSystem->Load("libGeoBase");
  gSystem->Load("libParBase");
  gSystem->Load("libBase");
  gSystem->Load("libMCStack");
  gSystem->Load("libMpdField");
  gSystem->Load("libPassive");
  gSystem->Load("libGen");
  gSystem->Load("libTrkBase");
  gSystem->Load("libMpdBase");
  gSystem->Load("libMpdData");
  gSystem->Load("libMpdgenerators");

  // gSystem->Load("libHADGEN.so");
  // gSystem->Load("libTHadgen.so");
  //  gSystem->Load("libMpdGeneralGenerator.so");

  gSystem->Load("libMpdFemto.so");
     
  if (reco) {
    gSystem->Load("libKalman");
    gSystem->Load("libtpc");
    gSystem->Load("libLHETrack");
    gSystem->Load("libGeane");
  }

  if (detectors) {
    gSystem->Load("libtpc");
    gSystem->Load("libTof");
    //gSystem->Load("libEtof");
    gSystem->Load("libEmc");
    //gSystem->Load("libStrawendcap");
    //gSystem->Load("libStt");
    //gSystem->Load("libSts");
    //gSystem->Load("libBbc");
    gSystem->Load("libZdc");
    //gSystem->Load("libFsa");
    gSystem->Load("libFfd");
    //gSystem->Load("libCpc");
    //gSystem->Load("libNDet");
    //gSystem->Load("libSft");
	 gSystem->Load("libStrawECT");
  }
}

TString find_path_to_URQMD_files ()
{
  TString hostname = gSystem->HostName();
  TString path_to_URQMD_files;

  if ((hostname=="nc2.jinr.ru")||(hostname=="nc3.jinr.ru") ||
      (hostname=="nc8.jinr.ru")||(hostname=="nc9.jinr.ru") || 
      (hostname=="nc10.jinr.ru")||(hostname=="nc11.jinr.ru")) {
    path_to_URQMD_files="/nica/mpd1/data4mpd/UrQMD/1.3/";
  }
  else {
    if ((hostname=="lxmpd-ui.jinr.ru")||(hostname=="lxmpd-ui"))    // linux farm
      path_to_URQMD_files = "/opt/exp_soft/mpd/urqmd/";
    else {
      if ( (hostname=="mpd")||(hostname=="mpd.jinr.ru")
           ||(hostname=="nc12.jinr.ru")||(hostname=="nc13.jinr.ru")||(hostname=="se63-36.jinr.ru")
	   ||(hostname=="se63-37.jinr.ru")||(hostname=="se63-40.jinr.ru")||(hostname=="se51-99.jinr.ru") )
	path_to_URQMD_files = "/opt/data/";                        // mpd, nc11
      else{
	if (hostname == "seashore")
          path_to_URQMD_files = "/data/mpd/";
	else {
	  if ((hostname=="kanske")||(hostname=="kanske.itep.ru"))     // Moscow
	    path_to_URQMD_files ="/scratch2/kmikhail/data4mpd/UrQMD/1.3/";
	  else 
            path_to_URQMD_files = gSystem->Getenv("HOME") + TString("/");
	}
      }
    }
  }
  return  path_to_URQMD_files;
}

// check whether file exists
bool CheckFileExist(TString fileName){
    gSystem->ExpandPathName(fileName);
    if (gSystem->AccessPathName(fileName.Data()) == true)
    {
        cout<<endl<<"no specified file: "<<fileName<<endl;
        return false;
    }

    return true;
}
