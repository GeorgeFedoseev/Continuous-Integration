//  RO
//  Mar 13  2013

class Mpdshape;


  ofstream* f ;

  std::ostringstream points, position, rotation;


  //=====================================================================
  //=====================================================================
  //=====================================================================


//____________________________________________________________________
int tpc_geom() {

  //  gROOT->ProcessLine(".include $VMCWORKDIR/geobase ");
  gROOT->ProcessLine(".include /home/roleg/Soft4Ex/mpd/mpdroot/geobase ");

  gROOT->LoadMacro("$VMCWORKDIR/macro/mpd/mpdloadlibs.C");
  mpdloadlibs(0,0);                 // load main libraries
  
  gROOT->ProcessLine(".L mpdshape.class.C");
  //  gROOT->LoadMacro("$VMCWORKDIR/macro/tpc/mpdshape.class.C");
  gROOT->LoadClass("Mpdshape");

  const char* filename = "tpc_v6.geo";

  // output file
  f = new ofstream(filename, ios::out | ios::trunc);


  gROOT->ProcessLine(".L TpcGeom.cxx");

  TpcGeom* tpc = new TpcGeom(f);

  tpc->BuildTPC();
 


  // close geometry file                                                       
  f->close(); 

}
