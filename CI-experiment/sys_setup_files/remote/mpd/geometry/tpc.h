 // Global dimensions for TPC in mm
  Double_t TpcInnRad = 270.0; // mm   tpc inner radius
  Double_t TpcOutRad = 1405.0; // mm  tpc outer radius
  Double_t tpc_z = .5*4000.0; //     tpc length
  Double_t tpc_chamber_z = .5*3400.0; // 

  // membrane
  Double_t mem_thick = .5*8.; // mm honeycomb

  // for barrel walls mm
  Double_t thick_al = .05; // 
  Double_t thick_tedlar = .05; //
  Double_t kevlar = 3.; //
  Double_t CO_2_gap[2] = {67., 65.};  //  out, in

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

  Double_t fc_out_rmax = 1250.9; // mm
  Double_t fc_out_rmin = 1250.85; // mm
  Double_t fc_in_rmax = 371.0; // mm
  Double_t fc_in_rmin = 370.95; // mm

// pins for fieldcage
  Double_t fc_r[2] = {1264., 377.2};  //  out, in
  Double_t fc_pin_r[2] = {30., 6.7}; //
  Double_t fc_wall_thick = 3.;
  Double_t fc_phi_shift = 7.*TMath::DegToRad();

// sensitive volume trapezoid

  Double_t sv_X = .5*641.6; // mm
  Double_t sv_x = .5*212.9; // mm
  Double_t sv_Y = .5*800.; // mm
  Double_t sv_Y_center = 803.; // mm


 // ====== Ribs ====
  Double_t rib_width_x = 40.;
  Double_t rib_width_z = 40.;
  Double_t rib_pos_z = 60.; // distance from flanches

  // FEE simulation
  Double_t zG10 = 2.8; // mm
  Double_t zCu = .822; // mm
  Double_t zAl = 1.; // mm cooling

  // pad plane simulation
  Double_t pad_plane = 3.;   // 
  Double_t back_plane_Al = 4.;   // 
  Double_t back_plane_G10 = 3.;   // 

