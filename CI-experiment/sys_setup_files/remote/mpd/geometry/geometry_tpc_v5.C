//  RO
//  Mon Sep 3 2012


#define SENSIT   // build sensitive sectors
#define PADPLANE    // build pad plane simulation
#define ENDCAP   // build endcaps with ribs
#define FEESIM    // build FEE simulation

class Mpdshape;

 // Global dimensions for TPC in mm
  Double_t TpcInnRad = 270.0; // mm   tpc inner radius
  Double_t TpcOutRad = 1500.0; // mm  tpc outer radius  (1200)
  Double_t tpc_z = .5*4000.0; //     tpc length      (.5*3400)
  Double_t tpc_chamber_z = .5*3400.0; // 

  // membrane
  Double_t mem_thick = .5*8.; // mm honeycomb

  // for barrel walls mm
  Double_t thick_al = .05; // 
  Double_t thick_tedlar = .05; //
  Double_t kevlar = 3.; //
  Double_t CO_2_gap = 120.; //
  Double_t wall_thickness = 2.* (2.*(thick_al + thick_tedlar) + kevlar)
                           + CO_2_gap;

  // flanches inside tpc_chamber_z

  Double_t outer_flanch_width = 268.; //mm
  Double_t inner_flanch_width = 132.; //mm

  Double_t outer_flanch_in_rad =
    TpcOutRad - outer_flanch_width; //mm
  Double_t inner_flanch_out_rad =
    TpcInnRad + inner_flanch_width; //mm
  Double_t flanch_thickness = 25.; //mm

  Double_t tpc_drift_z = tpc_chamber_z - flanch_thickness; // 

  Int_t Nsect = 12; 
  Double_t step = 360./Nsect; // degree
  Double_t phi_step = TMath::DegToRad()*step; //radian


// fieldcage

  Double_t fc_out_rmax = 1295.95; // mm
  Double_t fc_out_rmin = 1295.9; // mm
  Double_t fc_in_rmax = 426.05; // mm
  Double_t fc_in_rmin = 426.; // mm

// pins for fieldcage
  Double_t fc_r[2] = {1300.2, 434.1};  //  out, in
  Double_t fc_pin_r[2] = {40., 6.7}; //
  Double_t fc_wall_thick = 3.;
  Double_t fc_phi_shift = 7.*TMath::DegToRad();

// sensitive volume trapezoid

  Double_t sv_X = .5*659.1; // mm
  Double_t sv_x = .5*241.3; // mm
  Double_t sv_Y = .5*780.; // mm
  Double_t sv_Y_center = 846.; // mm

 // ====== Ribs ====
  Double_t rib_width_x = 40.;
  Double_t rib_width_z = 40.;
  Double_t rib_pos_z = 60.; // distance from tpc_chamber_z

  // FEE simulation
  Double_t zG10 = 2.8; // mm
  Double_t zCu = .822; // mm
  Double_t zAl = 1.; // mm cooling

  // pad plane simulation
  Double_t pad_plane = 3.;   // 
  Double_t back_plane_Al = 4.;   // 
  Double_t back_plane_G10 = 3.;   // 

  ofstream* f ;

  std::ostringstream points, position, rotation;


  //=====================================================================
  //=====================================================================
  //=====================================================================


//______________________________________________________________
void Clear() {
  points.str(""); position.str(""); rotation.str("");
}

//______________________________________________________________
void Fill_TUBE(Double_t length_z, Double_t r_max, Double_t r_min) {
  //
  Clear();
  points << 0.0 << " " << 0.0 << " " << length_z << endl;
  points <<  r_max << " " << r_min << endl;
  points << 0.0 << " " << 0.0 << " " << -length_z;
}


//______________________________________________________________
void Fill_TRAP(Double_t x_small, Double_t x_large,
	       Double_t yWidth, Double_t zWidth) {
  //
  Clear();

  // trapezoid
           // _____________
           // \           / ^     
           //  \         /  | y  /z   
           //   \       /
           //    \_____/
           //       x

  points << x_small << " " << -yWidth << " " << -zWidth << endl;
  points << x_large << " " << yWidth << " " << -zWidth << endl;
  points << -x_large << " " << yWidth << " " << -zWidth << endl;
  points << -x_small << " " << -yWidth << " " << -zWidth << endl;

  points << x_small << " " << -yWidth << " " << zWidth << endl;
  points << x_large << " " << yWidth << " " << zWidth << endl;
  points << -x_large << " " << yWidth << " " << zWidth << endl;
  points << -x_small << " " << -yWidth << " " << zWidth << endl;

}

//______________________________________________________________
void Fill_BOX(Double_t xWidth, Double_t yWidth, Double_t zWidth) {

  // box
  Clear();
  points << xWidth << " " << -yWidth << " " << -zWidth << endl;
  points << xWidth << " " << yWidth << " " << -zWidth << endl;
  points << -xWidth << " " << yWidth << " " << -zWidth << endl;
  points << -xWidth << " " << -yWidth << " " << -zWidth << endl;

  points << xWidth << " " << -yWidth << " " << zWidth << endl;
  points << xWidth << " " << yWidth << " " << zWidth << endl;
  points << -xWidth << " " << yWidth << " " << zWidth << endl;
  points << -xWidth << " " << -yWidth << " " << zWidth;
}


//_______________________________________________________________
void Fill_PGON( Double_t zmin, Double_t zmax, Double_t rmin, Double_t rmax) {
  Clear();
   points << "2 " << endl;
   points << "7 360 12 " << endl;
   points << zmin << " " << rmin << " " << rmax << endl;
   points << zmax << " " << rmin << " " << rmax;
}

//_______________________________________________________________
int build_wall (TString which = "In", Float_t radius = 100) {

  
  TString wallname = "tpc01" + which + "Wall";
  Fill_TUBE(tpc_drift_z, radius, radius + wall_thickness);
  
  Mpdshape* wall = new Mpdshape(f,wallname.Data(), "tpcChamber1", "TUBE",
				"air", points.str());
  wall->DumpToFile();

  Double_t R_old, R_cur;

  for (Int_t section = 1; section < 3; section++) {
    
    if (section == 1)  {
      R_old = radius;}
    else {
      R_old = R_cur;}
    
  // add  Alum
    R_cur = R_old + thick_al;
    
    Fill_TUBE(tpc_drift_z,  R_old, R_cur);

    // std::cout << points.str() << endl;
    TString volume = "tpc01" + which + "Sct";
  
    volume += section;
    TString volname = volume + "Al1";

    //    std::cout << volume << endl;
  
    wall->SetVolumeName(volname.Data());
    wall->SetMotherVolumeName(wallname.Data());
    wall->SetMedia("aluminium");
    wall->SetPoints(points.str());
    wall->DumpToFile();

    // tpc wall inner tube

    Double_t R_old = R_cur;
    R_cur = R_cur + thick_tedlar;

    Fill_TUBE(tpc_drift_z, R_old, R_cur);

    // std::cout << points.str() << endl;

    volname = volume + "Tdl1";
    wall->SetVolumeName(volname.Data());
    wall->SetMedia("tedlar");
    wall->SetPoints(points.str());
    wall->DumpToFile();

    // tpc wall inner tube kevlar

    R_old = R_cur;
    R_cur = R_cur + kevlar;

    Fill_TUBE(tpc_drift_z,  R_old, R_cur);

    // std::cout << points.str() << endl;

    volname = volume + "Kvl";
    wall->SetVolumeName(volname.Data());
    wall->SetMedia("kevlar");
    wall->SetPoints(points.str());
    wall->DumpToFile();

    // tpc  inner wall tedlar

    R_old = R_cur;
    R_cur = R_cur + thick_tedlar;

    Fill_TUBE(tpc_drift_z,  R_old, R_cur);

    volname = volume + "Tdl2";
    wall->SetVolumeName(volname.Data());
    wall->SetMedia("tedlar");
    wall->SetPoints(points.str());
    wall->DumpToFile();

    // tpc inner wall al

    R_old = R_cur;
    R_cur = R_cur + thick_al;
    Fill_TUBE(tpc_drift_z,  R_old, R_cur);

    volname = volume + "Al2";
    wall->SetVolumeName(volname.Data());
    wall->SetMedia("aluminium");
    wall->SetPoints(points.str());
    wall->SetSegment(0);
    wall->DumpToFile();

    // tpc co2 gap inner wall

    if (section == 2) continue;
  
    R_old = R_cur;
    R_cur = R_cur + CO_2_gap;

    Fill_TUBE(tpc_drift_z,  R_old, R_cur);

    volname = volume + "CO2";
    wall->SetVolumeName(volname.Data());
    wall->SetMedia("CO2");
    wall->SetPoints(points.str());
    wall->SetSegment(0);
    wall->DumpToFile();
    
  }
  delete  wall;

  cout << "==== " << which << " wall filled ====\n";
  

}

//__________________________________________________________________
void sector_layers(Double_t x_small, Double_t x_large,
		   Double_t yWidth, TList *layers) {

  TIter next(layers);
  Mpdshape *obj;
  Double_t zWidth = 0;
  
  while (obj = (Mpdshape *)next()) {
    //    std::cout << obj->GetVolumeName();
    if (obj->GetVolumeName() == "tpc01bpG10") {
      zWidth = .5*back_plane_G10; //  mm
    }
    
    if (obj->GetVolumeName() == "tpc01bpPp") {
      zWidth = .5*pad_plane; //
    }
    
    if (obj->GetVolumeName() == "tpc01bpAl") {
      zWidth = .5*back_plane_Al; //  mm
    }

    if (zWidth == 0.) continue;
    Fill_TRAP(x_small, x_large, yWidth, zWidth);
    position << 0.0 << " " << 0.0 << " " << 0.0;

    obj->SetPoints(points.str());
  }

}

//__________________________________________________________________
void internal_sector() {
  // sensitive volume with pad plane

  Double_t zSector = tpc_drift_z - mem_thick; // z thickness of sv
  Double_t zWidth = .5*(tpc_drift_z - mem_thick); //

  //make  a sens sector
  Fill_TRAP(sv_x, sv_X, sv_Y, zWidth);

  position << 0.0 << " " << 0.0 << " " << 0.0;

  Double_t center_rad = sv_Y_center;

   cout << "sens sector size : " << "X " << 2*sv_X << 
     " x " << 2*sv_x << " Y " << 2*sv_Y << " ";

   cout << " center_rad : " << sv_Y_center << "\n";

  Mpdshape* tpcsect = new Mpdshape(f, "tpc01sv", "tpc01mod#1", "TRAP",
				   "TPCmixture", points.str(), position.str());
  tpcsect->SetSegment(1);

  TList *layers = new TList();
  
  Mpdshape *layer_G10 = new Mpdshape(f, "tpc01bpG10", "tpc01sv#1", "TRAP", "G10",
			     points.str(), position.str());
  layer_G10->SetSegment(1);
  layers->Add(layer_G10);
  

  Mpdshape *layer_Pad = new Mpdshape(f, "tpc01bpPp", "tpc01sv#1",
			    "TRAP", "G10", points.str(), position.str());
  layer_Pad->SetSegment(1);
  layers->Add(layer_Pad);

  Mpdshape *layer_Al = new Mpdshape(f, "tpc01bpAl", "tpc01sv#1", "TRAP",
			    "aluminium ",points.str(), position.str());
  layer_Al->SetSegment(1);
  layers->Add(layer_Al);

  //  layers->Print();
  
  Int_t imodule=1;
  Double_t zCurrent,zRot;
  Double_t kx,my,phi_cent;
  Double_t kz = .0;

  for (Int_t k = 0; k < Nsect; k++) {

    phi_cent = k*phi_step;
    kx = center_rad* TMath::Cos(phi_cent);
    my = center_rad* TMath::Sin(phi_cent);
    zRot = step*k  - 90.;

    //    cout << " X " << kx << " Y " << my << "Z  " << kz << endl;
    tpcsect->SetPosition(kx, my, kz);
    tpcsect->SetRotation(zRot, 0.0, 0.0);
    tpcsect->DumpWithIncrement();

#ifdef PADPLANE
      if (imodule == 1) {
	//	sector_layers(x_small, x_large, yWidth,layers);
	sector_layers(sv_x, sv_X, sv_Y,layers);
      }

      imodule++;

      zCurrent =  .5*zSector - 0.5*back_plane_Al;
      layer_Al->SetPosition(0., 0.,zCurrent);
      layer_Al->DumpWithIncrement();

      zCurrent =  zCurrent - 0.5*(back_plane_Al + back_plane_G10);
      layer_G10->SetPosition(0., 0., zCurrent);
      layer_G10->DumpWithIncrement();
      
      zCurrent =  zCurrent - 0.5*( back_plane_G10 + pad_plane);
      layer_Pad->SetPosition(0., 0., zCurrent);
      layer_Pad->DumpWithIncrement();
#endif    
  }
  cout << "==== internal sectors filled ====\n";
}

//_________________________________________________________
void external_sector_layers(Double_t x_small, Double_t x_large,
			    Double_t yWidth, Mpdshape *layer_G10,
			    Mpdshape *layer_Cu, Mpdshape *layer_Al) {

  // G10 plane

  Double_t zWidth = .5*zG10; //  mm
  Fill_TRAP(x_small, x_large, yWidth, zWidth);

  position << 0.0 << " " << 0.0 << " " << 0.0;

  layer_G10->SetPoints(points.str());
  
  // Cu plane


  zWidth = .5*zCu; //

  Fill_TRAP(x_small, x_large, yWidth, zWidth);

  position << 0.0 << " " << 0.0 << " " << 0.0;

  layer_Cu->SetPoints(points.str());

 // Al plane

  zWidth = .5*zAl; //  mm
  Fill_TRAP(x_small, x_large, yWidth, zWidth);

  position << 0.0 << " " << 0.0 << " " << 0.0;
  layer_Al->SetPoints(points.str());

}

//__________________________________________________________________
void external_sector() {

  // Sector volume
  TVector3 CircleCenter = TVector3(0.,0.,0.);
  TVector3 LineStart = TVector3( 0.5*rib_width_x,0.,0.);
  TVector3 LineEnd = TVector3( 0.5*rib_width_x, 500.,0.);

  TVector3 crosspoint = LineCrossesCircle(CircleCenter, outer_flanch_in_rad,
					  LineStart, LineEnd);

  Double_t yWidth, zWidth, kz;
  Double_t kx,my,phi_cent;
  //  crosspoint.Print();

  Double_t x_large = (crosspoint.Y()-.5*rib_width_x/TMath::Tan(phi_step/2.))*
    TMath::Sin(phi_step/2.);
  Double_t x_small = (inner_flanch_out_rad*TMath::Sin(phi_step/2.) -
    .5*rib_width_x)/TMath::Cos(phi_step/2.) ;

  Double_t zSector = tpc_z - tpc_drift_z; // z thickness of trap

  yWidth = .5*(x_large - x_small)/TMath::Tan(phi_step/2.);

  zWidth = .5*zSector; // 

  kz = 0.;

  //  make sector

  Fill_TRAP(x_small, x_large, yWidth, zWidth);

  position << 0.0 << " " << 0.0 << " " << 0.0;

  Double_t center_rad = inner_flanch_out_rad + yWidth;

  Mpdshape* extsect = new Mpdshape(f, "tpc01ES", "tpc01ec#1", "TRAP", "air",
				   points.str(), position.str());
  extsect->SetSegment(1);

  Int_t imodule=1;

  Double_t zCurrent,zRot;

  Mpdshape *layer_G10 = new Mpdshape(f, "tpc01ESG10", "tpc01ES#1", "TRAP", "G10",
			     points.str(), position.str());
  layer_G10->SetSegment(1);

  Mpdshape *layer_Cu = new Mpdshape(f, "tpc01ESCu", "tpc01ES#1",
			    "TRAP", "copper", points.str(), position.str());
  layer_Cu->SetSegment(1);

  Mpdshape *layer_Al = new Mpdshape(f, "tpc01ESAl", "tpc01ES#1", "TRAP",
			    "aluminium ",points.str(), position.str());
  layer_Al->SetSegment(1);
  // ========================================

    for (Int_t k = 0; k < Nsect; k++) {

      phi_cent = k*phi_step; // radians
      kx = center_rad* TMath::Cos(phi_cent);
      my = center_rad* TMath::Sin(phi_cent);
      zRot = step*k  - 90.;
      //      cout << " X " << kx << " Y " << my << "Z  " << kz << endl;
      extsect->SetPosition(kx, my, kz);
      extsect->SetRotation(zRot, 0.0, 0.0);
      extsect->DumpWithIncrement();

      //+++++++++++++++++==================
#ifdef FEESIM
      if (imodule == 1) {
	external_sector_layers(x_small, x_large, yWidth,
			       layer_G10, layer_Cu, layer_Al);
      }

      imodule++;

      zCurrent =  -.5*zSector + 0.5*zG10;

      layer_G10->SetPosition(0., 0., zCurrent);
      layer_G10->DumpWithIncrement();

      zCurrent =  zCurrent + 0.5*(zG10 + zCu);
      layer_Cu->SetPosition(0., 0., zCurrent);
      layer_Cu->DumpWithIncrement();
      
      zCurrent =  zCurrent + 0.5*(zAl + zCu);
      layer_Al->SetPosition(0., 0.,zCurrent);
      layer_Al->DumpWithIncrement();
#endif      
    }
  cout << "==== external sectors filled ====\n";
}


  //================== FieldCage===================================
void FieldCage(Double_t zWidth) {

  // make out fieldcage
  Fill_PGON(-zWidth, zWidth, fc_out_rmin, fc_out_rmax);
  Mpdshape* cage = new Mpdshape(f, "tpc01outfc","tpc01mod#1", "PGON", "mylar",
				points.str());
  cage->SetSegment(1);
  cage->SetPosition(0., 0., 0.);
  cage->DumpWithIncrement();

  // make inner fieldcage
  Fill_PGON(-zWidth, zWidth, fc_in_rmin, fc_in_rmax);
  cage->SetVolumeName("tpc01infc");
  cage->SetSegment(1);
  cage->SetPoints(points.str());
  cage->DumpWithIncrement();

  delete cage;

  std::string name[2] ={"tpc01outpin","tpc01inpin"};
  
  Double_t phi_cent, kx, my, center_rad;
  
  Mpdshape* pin = new Mpdshape(f, "tpc01inpin", "tpc01mod#1", "TUBE",
			       "polypropylene", points.str());
  for (Int_t j = 0; j < 2; j++) {
    center_rad = fc_r[j];
    
    Fill_TUBE(zWidth, fc_pin_r[j] - fc_wall_thick, fc_pin_r[j] );

    pin->SetSegment(1);
    pin->SetPoints(points.str());
    pin->SetVolumeName(name[j]);
    
    for (Int_t k = 0; k < Nsect; k++) {
      
      phi_cent = k*phi_step + fc_phi_shift; // radians
      kx = center_rad* TMath::Cos(phi_cent);
      my = center_rad* TMath::Sin(phi_cent);
      //      cout << " X " << kx << " Y " << my << "Z  " << kz << endl;
      pin->SetPosition(kx, my, 0.);
      pin->DumpWithIncrement();
    }
  }
  delete pin;
}

//____________________________________________________________________
int geometry_tpc_v5() {

  gROOT->LoadMacro("$VMCWORKDIR/macro/mpd/geometry/mpdshape.class.C");
  gROOT->LoadClass("Mpdshape");

  const char* filename = "tpc_v5.geo";

  // output file
  f = new ofstream(filename, ios::out | ios::trunc);

  // streams
  std::ostringstream points, position, rotation;
  points.setf(ios::showpoint); points.setf(ios::fixed);
  points << setprecision(6);
  position.setf(ios::showpoint); position.setf(ios::fixed);
  position << setprecision(6);
  rotation.setf(ios::showpoint); rotation.setf(ios::fixed);
  rotation << setprecision(6);


  // create full tpc volume
  Fill_TUBE(tpc_z, TpcInnRad, TpcOutRad);
  // std::cout << points.str() << endl;
  Mpdshape* tube = new Mpdshape(f, "tpcChamber1", "cave", "TUBE",
				"air", points.str());
  tube->SetSegment(0);
  tube->DumpToFile();

  build_wall("In", TpcInnRad);
  build_wall("Out", TpcOutRad - wall_thickness);
  delete tube;
  

  // ===========================================================
  //     make TPC membrane

  Clear();
  Double_t xWidth,yWidth,zWidth,kx,my,kz,phi_cent;
  // make membrane
  zWidth = mem_thick;

  Fill_TUBE(zWidth, TpcInnRad + wall_thickness, TpcOutRad - wall_thickness);

  Mpdshape* membrane = new Mpdshape(f, "tpc01mb", "tpcChamber1", "TUBE",
				"rohacellhf71", points.str());
  membrane->SetPosition(0., 0., 0.);
  membrane->DumpToFile();

#ifdef SENSIT
  // ===========================================================
  //     TPC sensitive volume

  // make half of sensitive volume
  zWidth = .5*(tpc_drift_z - mem_thick);

  Fill_TUBE(zWidth, TpcInnRad + wall_thickness, TpcOutRad - wall_thickness);

  Mpdshape* tpchalf = new Mpdshape(f, "tpc01mod", "tpcChamber1", "TUBE",
				"air", points.str());
  tpchalf->SetSegment(1);
  tpchalf->SetPosition(0., 0., tpc_drift_z - zWidth);
  tpchalf->SetRotation(" 1. 0. 0. 0. 1. 0. 0. 0.  1.");
  tpchalf->DumpWithIncrement();

  // make field cage
  FieldCage(zWidth);
  
  // make sectors
  internal_sector();
  
  //  second half sens vol
  tpchalf->SetPosition(0., 0., -tpc_drift_z + zWidth);
  tpchalf->SetRotation(" 1. 0. 0. 0. 1. 0. 0. 0. -1.");
  tpchalf->DumpToFile();

#endif

#ifdef ENDCAP

  // ===========================================================
  //                          Begin EndCap
  // ===========================================================

  zWidth =.5*(tpc_z - tpc_drift_z); 
  
  Fill_TUBE(zWidth, TpcInnRad, TpcOutRad);
  
  //  endcap
  Mpdshape* tpcendcap = new Mpdshape(f, "tpc01ec", "tpcChamber1", "TUBE",
				"air", points.str());
  tpcendcap->SetSegment(1);
  
  Double_t z_ec = zWidth + tpc_drift_z;
  tpcendcap->SetPosition(0., 0., z_ec);
  tpcendcap->SetRotation(" 1. 0. 0. 0. 1. 0. 0. 0.  1.");
  tpcendcap->DumpWithIncrement();


  //============================================================
  //            Flanches
  //============================================================

  // al flanch outer

  Fill_TUBE(.5*flanch_thickness, outer_flanch_in_rad, TpcOutRad);

  Mpdshape* flanch = new Mpdshape(f, "tpc01of", "tpc01ec#1", "TUBE",
				"aluminium", points.str());
  flanch->SetPosition(0., 0., .5*flanch_thickness - zWidth );
  flanch->DumpToFile();

  // al flanch  inner South

  Fill_TUBE(.5*flanch_thickness, TpcInnRad, inner_flanch_out_rad);

  flanch->SetVolumeName("tpc01if");
  flanch->SetMedia("aluminium");
  flanch->SetPoints(points.str());
  flanch->DumpToFile();

 // ==========  Ribs  ============================

  xWidth = 0.5*rib_width_x; // x - half-dimension of block
  yWidth = .5*(TMath::Sqrt(TpcOutRad*TpcOutRad - xWidth*xWidth) -
			TpcInnRad); // y - half-dimension of block
  zWidth = .5*rib_width_z; // z - half-dimension of block

  kz = flanch_thickness + rib_pos_z - zWidth;

  // tpc ribs 
  Fill_BOX(xWidth, yWidth, zWidth);

  Mpdshape* tpcrib = new Mpdshape(f, "tpc01Rib", "tpc01ec#1", "BOX", "aluminium",
				   points.str(), position.str());
  tpcrib->SetSegment(1);

  Double_t center_rad = TpcInnRad + yWidth;
  //  cout << "center_rad_rib: " << center_rad << "\n";

  for (Int_t k = 0; k <  Nsect; k++) {

    phi_cent = k*phi_step + .5*phi_step;
    Double_t kx = center_rad* TMath::Cos(phi_cent);
    Double_t my = center_rad* TMath::Sin(phi_cent);
    Double_t zRot = step*k  - 90. + .5*step;

    tpcrib->SetPosition(kx, my, kz);
    tpcrib->SetRotation(zRot, 0.0, .0);

    tpcrib->DumpWithIncrement();
  }
  external_sector();                            
 
//  second end-cup:
  tpcendcap->SetPosition(0., 0., -z_ec);
  tpcendcap->SetRotation(" 1. 0. 0. 0. 1. 0. 0. 0. -1.");
  tpcendcap->DumpToFile();

#endif

  // close geometry file                                                       
  f->close(); 

}
