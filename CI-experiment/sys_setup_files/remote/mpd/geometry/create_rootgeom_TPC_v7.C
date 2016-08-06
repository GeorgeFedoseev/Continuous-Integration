//---------------------------
#include "TGeoManager.h"
#include "TGeoVolume.h"
#include "TGeoMedium.h"
#include "TFile.h"

#include "TPC_geom_par.h"

//Detector's position
const Double_t TPC_Xpos = 0.0;
const Double_t TPC_Ypos = 0.0;
const Double_t TPC_Zpos = 0.0;

//Detector's construct parameters

//Global dimensions for TPC in cm
Double_t TpcInnerRadius = TPC::TpcInnerRadius; // tpc inner radius
Double_t TpcOuterRadius = TPC::TpcOuterRadius; // tpc outer radius
Double_t Container_tpc_z = TPC::Container_tpc_z; // common tpc length
Double_t Chamber_tpc_z = TPC::Chamber_tpc_z;

//Barrel walls in cm
Double_t Thick_aluminium_layer = TPC::Thick_aluminium_layer; // aluminium layer
Double_t Thick_tedlar_layer = TPC::Thick_tedlar_layer; // tedlar layer
Double_t Thick_kevlar_layer = TPC::Thick_kevlar_layer; // kevlar layer
Double_t Thick_CO2_outer_layer = TPC::Thick_CO2_layer[0]; // outer barrel
Double_t Thick_CO2_inner_layer = TPC::Thick_CO2_layer[1]; // innner barrel

//Membrane in cm
Double_t Membrane_thickness = TPC::Membrane_thickness; // honeycomb

//Field cage in cm
Double_t Fieldcage_out_rmax = TPC::Fieldcage_out_rmax;
Double_t Fieldcage_out_rmin = TPC::Fieldcage_out_rmin;
Double_t Fieldcage_in_rmax = TPC::Fieldcage_in_rmax;
Double_t Fieldcage_in_rmin = TPC::Fieldcage_in_rmin;

//pins for fieldcage in cm
Double_t OuterFieldcage_r = TPC::Fieldcage_r[0]; // outer field cage
Double_t InnerFieldcage_r = TPC::Fieldcage_r[1]; // inner field cage
Double_t OuterFieldcage_pin_r = TPC::Fieldcage_pin_r[0]; // outer field cage pin
Double_t InnerFieldcage_pin_r = TPC::Fieldcage_pin_r[1]; // inner field cage pin

Double_t Fieldcage_wall_thick = TPC::Fieldcage_wall_thick;
Double_t Fieldcage_phi_shift = TPC::Fieldcage_phi_shift;

//TPC pars
Int_t Nsections = TPC::Nsections;
Double_t Section_step = TPC::Section_step; // degree
Double_t Section_phi_step = TPC::Section_phi_step; //radian

//sensitive volume trapezoid in cm
Double_t Sens_vol_X = TPC::Sens_vol_X;
Double_t Sens_vol_x = TPC::Sens_vol_x;
Double_t Sens_vol_Y = TPC::Sens_vol_Y;
Double_t Sens_vol_Y_center = TPC::Sens_vol_Y_center;

//pad plane simulation in cm
Double_t Plane_Pp = TPC::Plane_Pp;
Double_t Plane_G10 = TPC::Plane_G10;
Double_t Plane_Al = TPC::Plane_Al;

//flanches inside chamber_tpc_z in cm
Double_t OuterFlanch_width = TPC::OuterFlanch_width;
Double_t InnerFlanch_width = TPC::InnerFlanch_width;
Double_t OuterFlanch_inner_radius = TPC::OuterFlanch_inner_radius;
Double_t InnerFlanch_outer_radius = TPC::InnerFlanch_outer_radius;
Double_t Flanch_thickness = TPC::Flanch_thickness;

//ribs in cm
Double_t Rib_width_x = TPC::Rib_width_x;
Double_t Rib_width_z = TPC::Rib_width_z;
Double_t Rib_position_z = TPC::Rib_position_z; // distance from flanches

//inner wall extension part in cm
Double_t Flange_thickness = TPC::Flange_thickness;
Double_t ExtPart_length = TPC::ExtPart_length;
Double_t Flange_width = TPC::Flange_width;

//frames im cm
Double_t Stiffening_rib_thickness = TPC::Stiffening_rib_thickness;
Double_t Frame_big_part_y_width = TPC::Frame_big_part_y_width;
Double_t Frame_small_part_y_width = TPC::Frame_small_part_y_width;

Double_t xy_frame_common_width = TPC::xy_frame_common_width;
Double_t z_frame_common_width = TPC::z_frame_common_width;

Double_t xy_frame_out_width = TPC::xy_frame_out_width;
Double_t xy_frame_in_width = TPC::xy_frame_in_width;

Double_t z_frame_in_width = TPC::z_frame_in_width;
Double_t z_frame_out_width = TPC::z_frame_out_width;

//PCB in cm
Double_t PCB_thickness = TPC::PCB_thickness;
//Double_t PCB_x_width = TPC::PCB_x_width;
//Double_t PCB_y_width = TPC::PCB_y_width;
Double_t PCB_Cu_layer_thickness = TPC::PCB_Cu_layer_thickness;
Double_t PCB_FR_layer_thickness = TPC::PCB_FR_layer_thickness;

//media
TGeoMedium *pMedAir = 0;
TGeoMedium *pMedAluminium = 0;
TGeoMedium *pMedTedlar = 0;
TGeoMedium *pMedKevlar = 0;
TGeoMedium *pMedMylar = 0;
TGeoMedium *pMedCO2 = 0;
TGeoMedium *pMedRohacellhf71 = 0;
TGeoMedium *pMedPolypropylene= 0;
TGeoMedium *pMedTPCmixture = 0;
TGeoMedium *pMedG10 = 0;
TGeoMedium *pMedFiberGlass = 0;
TGeoMedium *pMedCopper = 0;

TGeoMedium *pMedGold = 0;

class FairGeoMedia;
class FairGeoBuilder;

void DefineRequiredMedia(FairGeoMedia* geoMedia, FairGeoBuilder* geoBuild) {
    //air medium
    FairGeoMedium* mAir = geoMedia->getMedium("air");
    if ( ! mAir ) Fatal("Main", "FairMedium air not found");
    geoBuild->createMedium(mAir);
    pMedAir = gGeoManager->GetMedium("air");
    if ( ! pMedAir ) Fatal("Main", "Medium air not found");

    //aluminium medium
    FairGeoMedium* mAluminium = geoMedia->getMedium("aluminium");
    if ( ! mAluminium  ) Fatal("Main", "FairMedium aluminium not found");
    geoBuild->createMedium(mAluminium);
    pMedAluminium  = gGeoManager->GetMedium("aluminium");
    if ( ! pMedAluminium  ) Fatal("Main", "Medium aluminium not found");

    //tedlar medium
    FairGeoMedium* mTedlar = geoMedia->getMedium("tedlar");
    if ( ! mTedlar  ) Fatal("Main", "FairMedium tedlar not found");
    geoBuild->createMedium(mTedlar);
    pMedTedlar = gGeoManager->GetMedium("tedlar");
    if ( ! pMedTedlar  ) Fatal("Main", "Medium tedlar not found");

    //kevlar medium
    FairGeoMedium* mKevlar = geoMedia->getMedium("kevlar");
    if ( ! mKevlar  ) Fatal("Main", "FairMedium kevlar not found");
    geoBuild->createMedium(mKevlar);
    pMedKevlar = gGeoManager->GetMedium("kevlar");
    if ( ! pMedKevlar  ) Fatal("Main", "Medium kevlar not found");

    //mylar medium
    FairGeoMedium* mMylar = geoMedia->getMedium("mylar");
    if ( ! mMylar  ) Fatal("Main", "FairMedium mylar not found");
    geoBuild->createMedium(mMylar);
    pMedMylar = gGeoManager->GetMedium("mylar");
    if ( ! pMedMylar  ) Fatal("Main", "Medium mylar not found");

    //CO2 medium
    FairGeoMedium* mCO2 = geoMedia->getMedium("CO2");
    if ( ! mCO2  ) Fatal("Main", "FairMedium CO2 not found");
    geoBuild->createMedium(mCO2);
    pMedCO2 = gGeoManager->GetMedium("CO2");
    if ( ! pMedCO2  ) Fatal("Main", "Medium CO2 not found");

    //rohacellhf71 medium
    FairGeoMedium* mRohacellhf71 = geoMedia->getMedium("rohacellhf71");
    if ( ! mRohacellhf71 ) Fatal("Main", "FairMedium rohacellhf71 not found");
    geoBuild->createMedium(mRohacellhf71);
    pMedRohacellhf71 = gGeoManager->GetMedium("rohacellhf71");
    if ( ! pMedRohacellhf71  ) Fatal("Main", "Medium rohacellhf71 not found");

    //polypropylene medium
    FairGeoMedium* mPolypropylene = geoMedia->getMedium("polypropylene");
    if ( ! mPolypropylene ) Fatal("Main", "FairMedium polypropylene not found");
    geoBuild->createMedium(mPolypropylene);
    pMedPolypropylene = gGeoManager->GetMedium("polypropylene");
    if ( ! pMedPolypropylene ) Fatal("Main", "Medium polypropylene not found");

    //TPCmixture medium
    FairGeoMedium* mTPCmixture = geoMedia->getMedium("TPCmixture");
    if ( ! mTPCmixture ) Fatal("Main", "FairMedium TPCmixture not found");
    geoBuild->createMedium(mTPCmixture);
    pMedTPCmixture = gGeoManager->GetMedium("TPCmixture");
    if ( ! pMedTPCmixture ) Fatal("Main", "Medium TPCmixture not found");

    //G10 medium
    FairGeoMedium* mG10 = geoMedia->getMedium("G10");
    if ( ! mG10 ) Fatal("Main", "FairMedium G10 not found");
    geoBuild->createMedium(mG10);
    pMedG10 = gGeoManager->GetMedium("G10");
    if ( ! pMedG10 ) Fatal("Main", "Medium G10 not found");

    //fiberglass medium
    FairGeoMedium* mFiberGlass = geoMedia->getMedium("fiberglass");
    if ( ! mFiberGlass ) Fatal("Main", "FairMedium fiberglass not found");
    geoBuild->createMedium(mFiberGlass);
    pMedFiberGlass = gGeoManager->GetMedium("fiberglass");
    if ( ! pMedFiberGlass ) Fatal("Main", "Medium fiberglass not found");

    //copper medium
    FairGeoMedium* mCopper = geoMedia->getMedium("copper");
    if ( ! mCopper ) Fatal("Main", "FairMedium copper not found");
    geoBuild->createMedium(mCopper);
    pMedCopper = gGeoManager->GetMedium("copper");
    if ( ! pMedCopper ) Fatal("Main", "Medium copper not found");

    //gold medium
    FairGeoMedium* mGold = geoMedia->getMedium("gold");
    if ( ! mGold) Fatal("Main", "FairMedium gold not found");
    geoBuild->createMedium(mGold);
    pMedGold = gGeoManager->GetMedium("gold");
    if ( ! pMedGold ) Fatal("Main", "Medium gold not found");
}

void create_rootgeom_TPC_v7() {

    // Load necessary libraries
    gROOT->LoadMacro("$VMCWORKDIR/macro/mpd/mpdloadlibs.C");
    mpdloadlibs(); // load libraries

    // ----  set working directory  --------------------------------------------
    TString gPath = gSystem->Getenv("VMCWORKDIR");

    // -------   Geometry file name (output)   ---------------------------------
    const TString geoDetectorName = "tpc";
    const TString geoDetectorVersion = "v7";
    TString geoFileName = gPath + "/geometry/" + geoDetectorName + "_"+ geoDetectorVersion + ".root";
    // -------------------------------------------------------------------------

    // ----  global geometry parameters  ---------------------------------------
    FairGeoLoader*    geoLoad = new FairGeoLoader("TGeo","FairGeoLoader");
    FairGeoInterface* geoFace = geoLoad->getGeoInterface();

    // -------   Load media from media file   ----------------------------------
    TString medFile = gPath + "/geometry/media.geo";
    geoFace->setMediaFile(medFile);
    geoFace->readMedia();
    FairGeoMedia*   geoMedia = geoFace->getMedia();
    FairGeoBuilder* geoBuild = geoLoad->getGeoBuilder();

    DefineRequiredMedia(geoMedia, geoBuild);
    // -------------------------------------------------------------------------

    // --------------   Create geometry and global top volume  ------------------------
    gGeoManager = (TGeoManager*)gROOT->FindObject("FAIRGeom");
    gGeoManager->SetName(geoDetectorName + "_geom");
    TGeoVolume* top = new TGeoVolumeAssembly("TOP");
    top->SetMedium(pMedAir);
    gGeoManager->SetTopVolume(top);
    //gGeoMan->SetTopVisible(1);
    // --------------------------------------------------------------------------

    // Define TPC Geometry
    TString tpc_chamber_name = "tpcChamber1";
    TGeoTube *tpcChamberS = new TGeoTube(tpc_chamber_name, TpcInnerRadius, TpcOuterRadius, Container_tpc_z/2);
    TGeoVolume *tpcChamberV = new TGeoVolume(tpc_chamber_name, tpcChamberS);
    tpcChamberV->SetMedium(pMedAir);
    //tpcChamberV->SetVisibility(kTRUE);
    tpcChamberV->SetTransparency(95);

    //TPC position
    TGeoTranslation *tpc_position= new TGeoTranslation("tpc_position", TPC_Xpos, TPC_Ypos, TPC_Zpos);
    //tpc_position->RegisterYourself();

    CreateOuterWall(tpcChamberV);
    CreateInnerWall(tpcChamberV);

    CreateMembrane(tpcChamberV);

    CreateTPCModule(tpcChamberV);

    CreateEndCaps(tpcChamberV);

    //Adding the tpc mother valume to the global TOP Volume
    top->AddNode(tpcChamberV, 0, tpc_position);

    top->SetVisContainers(kTRUE);


    // ---------------   Finish   ----------------------------------------------
    gGeoManager->CloseGeometry();
    gGeoManager->CheckOverlaps(0.001);
    gGeoManager->PrintOverlaps();

    gGeoManager->Test();

    TFile* geoFile = new TFile(geoFileName, "RECREATE");
    top->Write();
    geoFile->Close();

    //TString gdmlname = gPath + "/geometry/tpc_v7.gdml";
    //gGeoManager->Export(gdmlname);

    top->Draw("ogl");
    TGLViewer *v = (TGLViewer*)gPad->GetViewer3D();
    v->SetStyle(TGLRnrCtx::kOutline);
    //top->Draw("");
}

void CreateOuterWall(TGeoVolume* mother_volume) {
    TString wall_name = "tpc01OutWall";

    Double_t wall_thickness = 0.0;
    Double_t wall_rmin = 0.0;
    Double_t wall_rmax = 0.0;

    const Int_t NLayers = 11;
    Int_t Layer[NLayers]; //rmin->rmax
    enum {Al,Tdl,Kvl,CO2};
    Layer[0] = Al;
    Layer[1] = Tdl;
    Layer[2] = Kvl;
    Layer[3] = Tdl;
    Layer[4] = Al;
    Layer[5] = CO2;
    Layer[6] = Al;
    Layer[7] = Tdl;
    Layer[8] = Kvl;
    Layer[9] = Tdl;
    Layer[10] = Al;

    //Calculate wall thickness
    for(Int_t i = 0; i < NLayers; i++) {
        switch (Layer[i]) {
            case Al:
                wall_thickness += Thick_aluminium_layer;
                break;
            case Tdl:
                wall_thickness += Thick_tedlar_layer;
                break;
            case Kvl:
                wall_thickness += Thick_kevlar_layer;
                break;
            case CO2:
                wall_thickness += Thick_CO2_outer_layer;
                break;
            default:
                cout << "unknown layer type!\n";
                break;
        }
    }

    wall_rmin = TpcOuterRadius - wall_thickness;

    wall_rmax = wall_rmin + wall_thickness;

    cout << "Outer wall thickness = " <<  wall_thickness << "\n";

    //Solids
    TGeoTube *tpcWallS = new TGeoTube(wall_name, wall_rmin, wall_rmax, Chamber_tpc_z/2);

    //Volumes
    TGeoVolume *tpcWallV = new TGeoVolume(wall_name, tpcWallS);

    //medium
    TGeoMedium *wall_medium = pMedAir; //set medium
    if(wall_medium) tpcWallV->SetMedium(wall_medium);
    else Fatal("Main", "Invalid medium for outer wall!");

    //visual attributes
    tpcWallV->SetLineColor(TColor::GetColor("#b6e1fc"));

    //Attach wall to mother volume
    mother_volume->AddNode(tpcWallV, 0);

//----  Create layers in Wall  -------------------------------------------------
    Double_t layer_rmin = wall_rmin;
    Double_t layer_rmax;
    Int_t section = 1;
    EColor layer_color;
    TGeoMedium *layer_medium = 0;

    for(Int_t ilayer = 0; ilayer < NLayers; ilayer++) {
        TString layer_name = "tpc01InSct";
        layer_name += section;
        switch (Layer[ilayer]) {
            case Al:
                layer_rmax = layer_rmin + Thick_aluminium_layer;
                layer_name += "Al";
                layer_color = kGray;
                layer_medium = pMedAluminium;
                break;
            case Tdl:
                layer_rmax = layer_rmin + Thick_tedlar_layer;
                layer_name += "Tdl";
                layer_color = kGreen;
                layer_medium = pMedTedlar;
                break;
            case Kvl:
                layer_rmax = layer_rmin + Thick_kevlar_layer;
                layer_name += "Kvl";
                layer_color = kOrange;
                layer_medium = pMedKevlar;
                break;
            case CO2:
                layer_rmax = layer_rmin + Thick_CO2_outer_layer;
                layer_name += "CO2";
                layer_color = kYellow;
                layer_medium = pMedCO2;
                section++;
                break;
            default:
                layer_rmax = layer_rmin;
                cout << "unknown layer type!\n";
                layer_name += "Unknown";
                layer_color = kRed;
                layer_medium = pMedAir;
                break;
        }

        //cout << "  layer(name : rmin : rmax : length) = "<< layer_name << " : " << layer_rmin << " : " << layer_rmax << " : " << chamber_tpc_z << "\n";

        TGeoTube *tpcSctS = new TGeoTube(layer_name, layer_rmin, layer_rmax, Chamber_tpc_z/2);
        TGeoVolume *tpcSctV = new TGeoVolume(layer_name, tpcSctS);

        if(layer_medium) tpcSctV->SetMedium(layer_medium);
        else Fatal("Main", "Invalid medium for Sct layer!");

        tpcSctV->SetLineColor(layer_color);

        tpcWallV->AddNode(tpcSctV, 0);

        layer_rmin = layer_rmax;
    }
//------------------------------------------------------------------------------
}

void CreateInnerWall(TGeoVolume* mother_volume) {
    TString wall_name = "tpc01InWall";

    Double_t wall_thickness = 0.0;
    Double_t wall_rmin = 0.0;
    Double_t wall_rmax = 0.0;

    const Int_t NLayers = 11;
    Int_t Layer[NLayers]; //rmin->rmax
    enum {Al,Tdl,Kvl,CO2};
    Layer[0] = Al;
    Layer[1] = Tdl;
    Layer[2] = Kvl;
    Layer[3] = Tdl;
    Layer[4] = Al;
    Layer[5] = CO2;
    Layer[6] = Al;
    Layer[7] = Tdl;
    Layer[8] = Kvl;
    Layer[9] = Tdl;
    Layer[10] = Al;

    //Calculate wall thickness
    for(Int_t i = 0; i < NLayers; i++) {
        switch (Layer[i]) {
            case Al:
                wall_thickness += Thick_aluminium_layer;
                break;
            case Tdl:
                wall_thickness += Thick_tedlar_layer;
                break;
            case Kvl:
                wall_thickness += Thick_kevlar_layer;
                break;
            case CO2:
                wall_thickness += Thick_CO2_inner_layer;
                break;
            default:
                cout << "unknown layer type!\n";
                break;
        }
    }

    wall_rmin = TpcInnerRadius;
    wall_rmax = wall_rmin + wall_thickness;

    cout << "Inner wall thickness = " <<  wall_thickness << "\n";

    //Solids
    TGeoTube *tpcWallS = new TGeoTube(wall_name, wall_rmin, wall_rmax, Chamber_tpc_z/2);

    //Volumes
    TGeoVolume *tpcWallV = new TGeoVolume(wall_name, tpcWallS);

    //medium
    TGeoMedium *wall_medium = pMedCO2; //set medium
    if(wall_medium) tpcWallV->SetMedium(wall_medium);
    else Fatal("Main", "Invalid medium for inner wall!");

    //visual attributes
    tpcWallV->SetLineColor(TColor::GetColor("#b6e1fc"));

    //Attach wall to mother volume
    mother_volume->AddNode(tpcWallV, 0);

    //Create outer tube in Wall
    CreateOuterTubeInInnerWall(tpcWallV, wall_rmax);

    //Create inner tube in wall
    CreateInnerTubeInInnerWall(tpcWallV, wall_rmin);

//------------------------------------------------------------------------------
}

CreateOuterTubeInInnerWall(TGeoVolume *mother_volume, Double_t wall_rmax) {
    Double_t outer_layers_thickness = 0.0;

    const Int_t NLayers = 5;
    Int_t Layer[NLayers]; //rmin->rmax
    enum {Al,Tdl,Kvl};
    Layer[0] = Al;
    Layer[1] = Tdl;
    Layer[2] = Kvl;
    Layer[3] = Tdl;
    Layer[4] = Al;

    //Calculate outer layers thickness
    for(Int_t i = 0; i < NLayers; i++) {
        switch (Layer[i]) {
            case Al:
                outer_layers_thickness += Thick_aluminium_layer;
                break;
            case Tdl:
                outer_layers_thickness += Thick_tedlar_layer;
                break;
            case Kvl:
                outer_layers_thickness += Thick_kevlar_layer;
                break;
            default:
                cout << "unknown layer type!\n";
                break;
        }
    }

    Double_t tube_rmax = wall_rmax;
    Double_t tube_rmin = wall_rmax - outer_layers_thickness;

    //Create tube
    TString tube_name = "tpc01OuterTube";
    Double_t tube_length = Chamber_tpc_z;
    TGeoTube *tubeS = new TGeoTube(tube_name, tube_rmin, tube_rmax, tube_length/2);

    TGeoVolume *tubeV = new TGeoVolume(tube_name, tubeS);

    TGeoMedium *tube_medium = pMedAir; //set medium
    if(tube_medium) tubeV->SetMedium(tube_medium);
    else Fatal("Main", "Invalid medium for outer tube!");

    tubeV->SetLineColor(TColor::GetColor("#fba0e3"));
    //tubeV->SetTransparency(0);

    mother_volume->AddNode(tubeV, 0);

    //fill tubs with layers
    FillTubeWithLayers(tubeV, tube_length, tube_rmin, tube_rmax, 2);
}

CreateInnerTubeInInnerWall(TGeoVolume *mother_volume, Double_t wall_rmin) {

    Double_t inner_layers_thickness = 0.0;

    const Int_t NLayers = 5;
    Int_t Layer[NLayers]; //rmin->rmax
    enum {Al,Tdl,Kvl};
    Layer[0] = Al;
    Layer[1] = Tdl;
    Layer[2] = Kvl;
    Layer[3] = Tdl;
    Layer[4] = Al;

    //Calculate outer layers thickness
    for(Int_t i = 0; i < NLayers; i++) {
        switch (Layer[i]) {
            case Al:
                inner_layers_thickness += Thick_aluminium_layer;
                break;
            case Tdl:
                inner_layers_thickness += Thick_tedlar_layer;
                break;
            case Kvl:
                inner_layers_thickness += Thick_kevlar_layer;
                break;
            default:
                cout << "unknown layer type!\n";
                break;
        }
    }

    Double_t tube_rmin = wall_rmin;
    Double_t tube_rmax = wall_rmin + inner_layers_thickness;

    //Create tube
    TString tube_name = "tpc01InnerTube";
    Double_t tube_length = Chamber_tpc_z;
    TGeoTube *tubeS = new TGeoTube(tube_name, tube_rmin, tube_rmax, tube_length/2);

    TGeoVolume *tubeV = new TGeoVolume(tube_name, tubeS);

    TGeoMedium *tube_medium = pMedAir; //set medium
    if(tube_medium) tubeV->SetMedium(tube_medium);
    else Fatal("Main", "Invalid medium for inner tube!");

    tubeV->SetLineColor(TColor::GetColor("#fba0e3"));
    //tubeV->SetTransparency(0);

    mother_volume->AddNode(tubeV, 0);

    //fill tubs with layers
    FillTubeWithLayers(tubeV, tube_length, tube_rmin, tube_rmax, 1);

    //create flanges of inner tubs
    TString tube_flange_name = "tpc01TubeFlange";
    Double_t tube_flange_rmin = TpcInnerRadius + inner_layers_thickness;
    Double_t tube_flange_rmax = tube_flange_rmin + Flange_width;

    TGeoTube * TubeFlangeS = new TGeoTube (tube_flange_name, tube_flange_rmin, tube_flange_rmax, Flange_thickness/2);

    TGeoVolume *TubeFlangeV = new TGeoVolume(tube_flange_name, TubeFlangeS);

    TGeoMedium *tube_flange_medium = pMedFiberGlass; //set medium
    if(tube_flange_medium) TubeFlangeV->SetMedium(tube_flange_medium);
    else Fatal("Main", "Invalid medium for inner tube flange!");

    TubeFlangeV->SetLineColor(TColor::GetColor("#c7fcec"));

    //positions
    Double_t long_tube_length = Chamber_tpc_z - 2*ExtPart_length;
    Double_t short_tube_length = ExtPart_length;
    TGeoTranslation *tube_flange_pos1 = new TGeoTranslation("tube_flane_pos1", 0, 0, Flange_thickness/2 + long_tube_length/2 - Flange_thickness);
    TGeoTranslation *tube_flange_pos2 = new TGeoTranslation("tube_flane_pos2", 0, 0, Flange_thickness/2 + long_tube_length/2);
    TGeoTranslation *tube_flange_pos3 = new TGeoTranslation("tube_flane_pos3", 0, 0, Flange_thickness/2 + long_tube_length/2 + short_tube_length - Flange_thickness);
    TGeoTranslation *tube_flange_pos1refl = new TGeoTranslation("tube_flane_pos1", 0, 0, -(Flange_thickness/2 + long_tube_length/2 - Flange_thickness));
    TGeoTranslation *tube_flange_pos2refl = new TGeoTranslation("tube_flane_pos2", 0, 0, -(Flange_thickness/2 + long_tube_length/2));
    TGeoTranslation *tube_flange_pos3refl = new TGeoTranslation("tube_flane_pos3", 0, 0, -(Flange_thickness/2 + long_tube_length/2 + short_tube_length - Flange_thickness));

    mother_volume->AddNode(TubeFlangeV, 0, tube_flange_pos1);
    mother_volume->AddNode(TubeFlangeV, 0, tube_flange_pos2);
    mother_volume->AddNode(TubeFlangeV, 0, tube_flange_pos3);
    mother_volume->AddNode(TubeFlangeV, 0, tube_flange_pos1refl);
    mother_volume->AddNode(TubeFlangeV, 0, tube_flange_pos2refl);
    mother_volume->AddNode(TubeFlangeV, 0, tube_flange_pos3refl);
}

void FillTubeWithLayers(TGeoVolume *mother_volume, Double_t tube_length, Double_t tube_rmin, Double_t tube_rmax, Int_t section) {
    const Int_t NLayers = 5;
    Int_t Layer[NLayers]; //rmin->rmax
    enum {Al,Tdl,Kvl};
    Layer[0] = Al;
    Layer[1] = Tdl;
    Layer[2] = Kvl;
    Layer[3] = Tdl;
    Layer[4] = Al;

    Double_t layer_rmin = tube_rmin;
    Double_t layer_rmax = 0.0;
    EColor layer_color;
    TGeoMedium *layer_medium = 0;

    for(Int_t ilayer = 0; ilayer < NLayers; ilayer++) {
        TString layer_name = "tpc01InSct";
        layer_name += section;
        switch (Layer[ilayer]) {
            case Al:
                layer_rmax = layer_rmin + Thick_aluminium_layer;
                layer_name += "Al";
                layer_color = kGray;
                layer_medium = pMedAluminium;
                break;
            case Tdl:
                layer_rmax = layer_rmin + Thick_tedlar_layer;
                layer_name += "Tdl";
                layer_color = kGreen;
                layer_medium = pMedTedlar;
                break;
            case Kvl:
                layer_rmax = layer_rmin + Thick_kevlar_layer;
                layer_name += "Kvl";
                layer_color = kOrange;
                layer_medium = pMedKevlar;
                break;
            default:
                layer_rmax = layer_rmin;
                cout << "unknown layer type!\n";
                layer_name += "Unknown";
                layer_color = kRed;
                layer_medium = pMedAir;
                break;
        }

        TGeoTube *tpcSctS = new TGeoTube(layer_name, layer_rmin, layer_rmax, tube_length/2);
        TGeoVolume *tpcSctV = new TGeoVolume(layer_name, tpcSctS);

        if(layer_medium) tpcSctV->SetMedium(layer_medium);
        else Fatal("Main", "Invalid medium for Sct layer!");

        tpcSctV->SetLineColor(layer_color);

        mother_volume->AddNode(tpcSctV, 0);

        layer_rmin = layer_rmax;
    }
}


void CreateMembrane(TGeoVolume *mother_volume) {
    TString membrane_name = "tpc01mb";

    Double_t membrane_rmin = TpcInnerRadius + 7.14; // consider inner wall thickness
    Double_t membrane_rmax = TpcOuterRadius - 7.5; // consider outer wall thickness

    //Solids
    TGeoTube *tpcMembraneS = new TGeoTube(membrane_name, membrane_rmin, membrane_rmax, Membrane_thickness/2);

    //Volumes
    TGeoVolume *tpcMembraneV = new TGeoVolume(membrane_name, tpcMembraneS);

    //medium
    TGeoMedium *membrane_medium = pMedRohacellhf71; //set medium
    if(membrane_medium) tpcMembraneV->SetMedium(membrane_medium);
    else Fatal("Main", "Invalid medium for membrane!");

    //visual attributes
    tpcMembraneV->SetLineColor(TColor::GetColor("#ffc7c7"));

    //Attach membrane to mother volume
    mother_volume->AddNode(tpcMembraneV, 0);
}

void CreateTPCModule(TGeoVolume *mother_volume) {
    TString module_name = "tpc01mod";

    //make half of module
    Double_t half_width_module = (Chamber_tpc_z - Membrane_thickness)/2;

    Double_t module_rmin = TpcInnerRadius + 7.14; // consider inner wall thickness
    Double_t module_rmax = TpcOuterRadius - 7.5; // consider outer wall thickness

    //Solids
    TGeoTube *tpcHalfModuleS = new TGeoTube(module_name, module_rmin, module_rmax, half_width_module/2);

    //Volumes
    TGeoVolume *tpcHalfModuleV = new TGeoVolume(module_name, tpcHalfModuleS);

    //medium
    TGeoMedium *module_medium = pMedAir; //set medium
    if(module_medium) tpcHalfModuleV->SetMedium(module_medium);
    else Fatal("Main", "Invalid medium for tpc module!");

    //visual attributes
    tpcHalfModuleV->SetLineColor(TColor::GetColor("#adff2f"));
    //tpcHalfModuleV->SetVisibility(kFALSE);

    //position
    TGeoTranslation *module_position1 = new TGeoTranslation("module_position", 0., 0., (Chamber_tpc_z-half_width_module)/2);

    //reflection
    TGeoCombiTrans *module_position2 = new TGeoCombiTrans();
    module_position2->ReflectZ(true);
    module_position2->SetTranslation(0, 0, -(Chamber_tpc_z-half_width_module)/2);

    //Attach module to mother volume
    mother_volume->AddNode(tpcHalfModuleV, 1, module_position1);
    mother_volume->AddNode(tpcHalfModuleV, 2, module_position2);

    //make field cage
    CreateFieldCage(tpcHalfModuleV, half_width_module);

    //make sensitive volume
    CreateSensitiveVolume(tpcHalfModuleV, half_width_module);

    //make pad planes
    CreatePadPlanes(tpcHalfModuleV, half_width_module);

    //Create frames;
    CreateFrames(tpcHalfModuleV, half_width_module);

    //Create PCB FEC
    CreatePCB(tpcHalfModuleV, half_width_module);
}

void CreateFieldCage(TGeoVolume *mother_volume, Double_t half_module_width) {
    TString FieldCageOut_name = "tpc01outfc";
    TString FieldCageIn_name = "tpc01infc";

    Double_t cage_width = half_module_width;

    Double_t  fielgcage_phi_shift_deg = Fieldcage_phi_shift*TMath::RadToDeg(); //angle shift in degrees (it`s 7.0 deg now))

    //Solids
    TGeoPgon *tpcFieldCageOutS = new TGeoPgon(FieldCageOut_name, fielgcage_phi_shift_deg, 360., 12, 2);
        tpcFieldCageOutS->DefineSection(0, -cage_width/2, Fieldcage_out_rmin, Fieldcage_out_rmax);
        tpcFieldCageOutS->DefineSection(1, cage_width/2, Fieldcage_out_rmin, Fieldcage_out_rmax);

    TGeoPgon *tpcFieldCageInS = new TGeoPgon(FieldCageIn_name, fielgcage_phi_shift_deg, 360., 12, 2);
        tpcFieldCageInS->DefineSection(0, -cage_width/2, Fieldcage_in_rmin, Fieldcage_in_rmax);
        tpcFieldCageInS->DefineSection(1, cage_width/2, Fieldcage_in_rmin, Fieldcage_in_rmax);

    //Volumes
    TGeoVolume *tpcFieldCageOutV = new TGeoVolume(FieldCageOut_name, tpcFieldCageOutS);
    TGeoVolume *tpcFieldCageInV = new TGeoVolume(FieldCageIn_name, tpcFieldCageInS);

    //medium
    TGeoMedium *FieldCage_medium = pMedMylar; //set medium
    if(FieldCage_medium) {
        tpcFieldCageOutV->SetMedium(FieldCage_medium);
        tpcFieldCageInV->SetMedium(FieldCage_medium);
    }
    else Fatal("Main", "Invalid medium for field cage!");

    //visual attributes
    tpcFieldCageOutV->SetLineColor(TColor::GetColor("#edff21"));
    tpcFieldCageInV->SetLineColor(TColor::GetColor("#edff21"));

    //Attach module to mother volume
    mother_volume->AddNode(tpcFieldCageOutV, 1);
    mother_volume->AddNode(tpcFieldCageInV, 1);

//----  Create pins for field cage  --------------------------------------
    for(Int_t isec = 0; isec < Nsections; isec++) {
        TString out_pin_name = "tpc01outpin";
        TString in_pin_name = "tpc01inpin";

        TGeoTube *tpcOutPinS = new TGeoTube(out_pin_name, OuterFieldcage_pin_r - Fieldcage_wall_thick, OuterFieldcage_pin_r, cage_width/2);
        TGeoTube *tpcInPinS = new TGeoTube(in_pin_name, InnerFieldcage_pin_r - Fieldcage_wall_thick, InnerFieldcage_pin_r, cage_width/2);

        TGeoVolume *tpcOutPinV = new TGeoVolume(out_pin_name, tpcOutPinS);
        TGeoVolume *tpcInPinV = new TGeoVolume(in_pin_name, tpcInPinS);

        tpcOutPinV->SetLineColor(TColor::GetColor("#edaa21"));
        tpcInPinV->SetLineColor(TColor::GetColor("#edaa21"));

        TGeoMedium *pin_medium = pMedPolypropylene; //set medium
        if(pin_medium) {
            tpcOutPinV->SetMedium(pin_medium);
            tpcInPinV->SetMedium(pin_medium);
        }
        else Fatal("Main", "Invalid medium for pin!");

        //calculate position
        Double_t center_rad_outpin = OuterFieldcage_r;
        Double_t center_rad_inpin = InnerFieldcage_r;
        Double_t kx_outpin;
        Double_t my_outpin;
        Double_t kx_inpin;
        Double_t my_inpin;
        Double_t phi_cent;

        phi_cent = isec*Section_phi_step + Fieldcage_phi_shift; // radians
        kx_outpin = center_rad_outpin* TMath::Cos(phi_cent);
        my_outpin = center_rad_outpin* TMath::Sin(phi_cent);
        kx_inpin = center_rad_inpin* TMath::Cos(phi_cent);
        my_inpin = center_rad_inpin* TMath::Sin(phi_cent);

        TGeoTranslation *out_pin_position= new TGeoTranslation("out_pin_position", kx_outpin, my_outpin, 0.);
        TGeoTranslation *in_pin_position= new TGeoTranslation("in_pin_position", kx_inpin, my_inpin, 0.);

        mother_volume->AddNode(tpcOutPinV, isec+1, out_pin_position);
        mother_volume->AddNode(tpcInPinV, isec+1, in_pin_position);
    }
//------------------------------------------------------------------------------
}

void CreateSensitiveVolume(TGeoVolume *mother_volume, Double_t half_module_width) {
    TString SensitiveVolume_name = "tpc01sv";

    Double_t shift = Plane_Al + Plane_G10 + Plane_Pp + z_frame_common_width + PCB_thickness;
    Double_t sv_width = half_module_width - shift;

    //Solids
    TGeoPgon *tpcSensitiveVolumeS = new TGeoPgon(SensitiveVolume_name, 15., 360., 12, 2);
        tpcSensitiveVolumeS->DefineSection(0, -sv_width/2, Sens_vol_Y_center-Sens_vol_Y, Sens_vol_Y_center+Sens_vol_Y);
        tpcSensitiveVolumeS->DefineSection(1, sv_width/2, Sens_vol_Y_center-Sens_vol_Y, Sens_vol_Y_center+Sens_vol_Y);

    //Volumes
    TGeoVolume *tpcSensitiveVolumeV = new TGeoVolume(SensitiveVolume_name, tpcSensitiveVolumeS);

    //medium
    TGeoMedium *sv_medium = pMedTPCmixture; //set medium
    if(sv_medium) tpcSensitiveVolumeV->SetMedium(sv_medium);
    else Fatal("Main", "Invalid medium for sensitive volume!");

    //visual attributes
    tpcSensitiveVolumeV->SetLineColor(TColor::GetColor("#ff9494"));

    //position
    TGeoTranslation *sv_position = new TGeoTranslation("sv_position", 0., 0., -shift/2);

    //Attach module to mother volume
    mother_volume->AddNode(tpcSensitiveVolumeV, 1, sv_position);
}

void CreatePadPlanes(TGeoVolume *mother_volume, Double_t half_module_width) {
    TString plane_name = "tpc01bp";

    Double_t plane_thickness = Plane_Pp + Plane_G10 + Plane_Al;

    TGeoTrd1 *tpcPlaneS = new TGeoTrd1(plane_name, Sens_vol_x, Sens_vol_X, plane_thickness/2, Sens_vol_Y);

    TGeoVolume *tpcPlaneV = new TGeoVolume(plane_name, tpcPlaneS);

    TGeoMedium *plane_medium = pMedAir; //set medium
    if(plane_medium) tpcPlaneV->SetMedium(plane_medium);
    else Fatal("Main", "Invalid medium for plane!");

    tpcPlaneV->SetLineColor(TColor::GetColor("#ff8243"));
    //tpcPlaneV->SetVisibility(kFALSE);
    tpcPlaneV->SetTransparency(95);

    //fill plane with pad layers
    CreatePadLayersInPlane(tpcPlaneV, plane_thickness);

    for(Int_t isec = 0; isec < Nsections; isec++) {
        TGeoCombiTrans *combi_trans = new TGeoCombiTrans();
        combi_trans->RotateX(-90.0);
        combi_trans->SetTranslation(0, Sens_vol_Y_center, half_module_width/2 - plane_thickness/2 - z_frame_common_width - PCB_thickness);
        combi_trans->RotateZ(isec*Section_step);

        mother_volume->AddNode(tpcPlaneV, isec+1, combi_trans);
    }
}

void CreatePadLayersInPlane(TGeoVolume *mother_volume, Double_t plane_thickness) {
    TString bpPp_name = "tpc01bpPp";
    TString bpG10_name = "tpc01bpG10";
    TString bpAl_name = "tpc01bpAl";

    //create bpPp
    TGeoTrd1 *tpcbpPpS = new TGeoTrd1(bpPp_name, Sens_vol_x, Sens_vol_X, Plane_Pp/2, Sens_vol_Y);
    TGeoVolume *tpcbpPpV = new TGeoVolume(bpPp_name, tpcbpPpS);

    TGeoMedium *bpPp_medium = pMedG10; //set medium
    if(bpPp_medium) tpcbpPpV->SetMedium(bpPp_medium);
    else Fatal("Main", "Invalid medium for pbPp!");

    tpcbpPpV->SetLineColor(TColor::GetColor("#ff2400"));

    mother_volume->AddNode(tpcbpPpV, 0, new TGeoTranslation(0, plane_thickness/2 - Plane_Pp/2, 0));

    //create bpG10
    TGeoTrd1 *tpcbpG10S = new TGeoTrd1(bpG10_name, Sens_vol_x, Sens_vol_X, Plane_G10/2, Sens_vol_Y);
    TGeoVolume *tpcbpG10V = new TGeoVolume(bpG10_name, tpcbpG10S);

    TGeoMedium *bpG10_medium = pMedG10; //set medium
    if(bpG10_medium) tpcbpG10V->SetMedium(bpG10_medium);
    else Fatal("Main", "Invalid medium for pbG10!");

    tpcbpG10V->SetLineColor(TColor::GetColor("#34c924"));

    mother_volume->AddNode(tpcbpG10V, 0, new TGeoTranslation(0, plane_thickness/2 - Plane_G10/2 - Plane_Pp, 0));

    //create bpAl
    TGeoTrd1 *tpcbpAlS = new TGeoTrd1(bpAl_name, Sens_vol_x, Sens_vol_X, Plane_Al/2, Sens_vol_Y);
    TGeoVolume *tpcbpAlV = new TGeoVolume(bpAl_name, tpcbpAlS);

    TGeoMedium *bpAl_medium = pMedAluminium; //set medium
    if(bpAl_medium) tpcbpAlV->SetMedium(bpAl_medium);
    else Fatal("Main", "Invalid medium for pbAl!");

    tpcbpAlV->SetLineColor(TColor::GetColor("#c4c3be"));

    mother_volume->AddNode(tpcbpAlV, 0, new TGeoTranslation(0, -plane_thickness/2 + Plane_Al/2, 0));
}

void CreateFrames(TGeoVolume *mother_volume, Double_t half_width_module) {
    TString frame_name = "tpcFrame";

    TGeoVolume *FrameAssemblyA = new TGeoVolumeAssembly("tpcFrameAssembly");

    TGeoTrd1 *tpcFrameContainerS = new TGeoTrd1(frame_name, Sens_vol_x, Sens_vol_X, z_frame_common_width/2, Sens_vol_Y);
    TGeoVolume *tpcFrameContainerV = new TGeoVolume(frame_name, tpcFrameContainerS);

    TGeoMedium *tpcFrameContainer_medium = pMedAir; //set medium
    if(tpcFrameContainer_medium) {
        tpcFrameContainerV->SetMedium(tpcFrameContainer_medium);
        FrameAssemblyA->SetMedium(tpcFrameContainer_medium);
    }
    else Fatal("Main", "Invalid medium for tpc frame container!");

    tpcFrameContainerV->SetLineColor(TColor::GetColor("#cccccc"));
    //tpcFrameContainerV->SetTransparency(0);

    for(Int_t isec = 0; isec < Nsections; isec++) {
    //for(Int_t isec = 0; isec < 1; isec++) {
        TGeoCombiTrans *combi_trans = new TGeoCombiTrans();
        combi_trans->RotateX(-90.0);
        combi_trans->SetTranslation(0, Sens_vol_Y_center, half_width_module/2 - z_frame_common_width/2 - PCB_thickness);
        combi_trans->RotateZ(isec*Section_step);

        FrameAssemblyA->AddNode(tpcFrameContainerV, isec+1, combi_trans);
    }

    mother_volume->AddNode(FrameAssemblyA, 1);

    //Create aluminium structure of frame
    FillFrames(tpcFrameContainerV);
}

void FillFrames(TGeoVolume *mother_volume) {
    TString frame_structure_name = "tpcFrameSkeleton";

    const Int_t npoints_structure = 12;

    TGeoXtru *tpcFrameStructureS = new TGeoXtru(2);
    Double_t x[npoints_structure];
    Double_t y[npoints_structure];

    x[0] = 0.0; y[0] = Sens_vol_Y;
    x[1] = Sens_vol_X - xy_frame_out_width; y[1] = Sens_vol_Y;
    x[2] = Sens_vol_x - xy_frame_out_width; y[2] = -Sens_vol_Y;
    x[3] = 0.0; y[3] = -Sens_vol_Y;
    x[4] = 0.0; y[4] = -Sens_vol_Y + xy_frame_in_width;

    Double_t x_shift = xy_frame_in_width/TMath::Tan(52.5*(TMath::DegToRad()));

    x[5] = Sens_vol_x - xy_frame_out_width - x_shift; y[5] = -Sens_vol_Y + xy_frame_in_width;

    Double_t xb = Frame_small_part_y_width/TMath::Tan(75*(TMath::DegToRad()));
    x_shift = xy_frame_in_width/TMath::Cos(15*TMath::DegToRad());

    x[6] = Sens_vol_x + xb - x_shift - xy_frame_in_width; y[6] = -Sens_vol_Y + Frame_small_part_y_width;
    x[7] = 0.0; y[7] = -Sens_vol_Y + Frame_small_part_y_width;
    x[8] = 0.0; y[8] = y[7] + Stiffening_rib_thickness;

    x_shift = TMath::Tan(15*(TMath::DegToRad()))*Stiffening_rib_thickness;
    x[9] = x[6] + x_shift; y[9] = y[8];

    x_shift = xy_frame_in_width/TMath::Tan(37.5*(TMath::DegToRad()));
    x[10] = Sens_vol_X - xy_frame_out_width - x_shift; y[10] = Sens_vol_Y - xy_frame_in_width;
    x[11] = 0.0; y[11] = y[10];

    tpcFrameStructureS->DefinePolygon(npoints_structure, x, y);

    tpcFrameStructureS->DefineSection(0, -z_frame_common_width/2);
    tpcFrameStructureS->DefineSection(1, z_frame_common_width/2);

    TGeoVolume *tpcFrameStructureV = new TGeoVolume(frame_structure_name, tpcFrameStructureS);

    TGeoMedium *tpcFrameStructure_medium = pMedAluminium; //set medium
    if(tpcFrameStructure_medium) tpcFrameStructureV->SetMedium(tpcFrameStructure_medium);
    else Fatal("Main", "Invalid medium for tpc frame structure!");

    tpcFrameStructureV->SetLineColor(TColor::GetColor("#84c3be"));

    TGeoCombiTrans *combi_trans1 = new TGeoCombiTrans();
    combi_trans1->RotateX(90.0);

    TGeoCombiTrans *combi_trans2 = new TGeoCombiTrans();
    combi_trans2->RotateX(90.0);
    combi_trans2->ReflectX(true);

    mother_volume->AddNode(tpcFrameStructureV, 1, combi_trans1);
    mother_volume->AddNode(tpcFrameStructureV, 2, combi_trans2);

//--------  create frame borders  ----------------------------------------------
    TString frame_border_name = "tpcFrameBorder";
    const Int_t npoints_border = 4;
    TGeoXtru *tpcFrameBorderS = new TGeoXtru(2);
    Double_t x[npoints_border];
    Double_t y[npoints_border];

    x[0] = Sens_vol_X - xy_frame_out_width; y[0] = Sens_vol_Y;
    x[1] = Sens_vol_X; y[1] = y[0];
    x[2] = Sens_vol_x; y[2] = -Sens_vol_Y;
    x[3] = Sens_vol_x - xy_frame_out_width; y[3] = y[2];

    tpcFrameBorderS->DefinePolygon(npoints_border, x, y);

    tpcFrameBorderS->DefineSection(0, -z_frame_common_width/2);
    tpcFrameBorderS->DefineSection(1, -z_frame_common_width/2 + z_frame_in_width);

    TGeoVolume *tpcFrameBorderV = new TGeoVolume(frame_border_name, tpcFrameBorderS);

    TGeoMedium *tpcFrameBorder_medium = pMedAluminium; //set medium
    if(tpcFrameBorder_medium) tpcFrameBorderV->SetMedium(tpcFrameBorder_medium);
    else Fatal("Main", "Invalid medium for tpc frame border!");

    tpcFrameBorderV->SetLineColor(TColor::GetColor("#84c3be"));

    TGeoCombiTrans *combi_trans3 = new TGeoCombiTrans();
    combi_trans3->RotateX(90.0);

    TGeoCombiTrans *combi_trans4 = new TGeoCombiTrans();
    combi_trans4->RotateX(90.0);
    combi_trans4->ReflectX(true);

    mother_volume->AddNode(tpcFrameBorderV, 1, combi_trans3);
    mother_volume->AddNode(tpcFrameBorderV, 2, combi_trans4);
//------------------------------------------------------------------------------
}

void CreatePCB(TGeoVolume *mother_volume, Double_t half_module_width) {
    TString pcb_name = "tpcPCB";

    TGeoVolume *PCBAssemblyA = new TGeoVolumeAssembly("tpcPCBAssembly");

    TGeoTrd1 *tpc_pcbS = new TGeoTrd1(pcb_name, Sens_vol_x, Sens_vol_X, PCB_thickness/2, Sens_vol_Y);

    TGeoVolume *tpc_pcbV = new TGeoVolume(pcb_name, tpc_pcbS);

    TGeoMedium *pcb_medium = pMedAir; //set medium
    if(pcb_medium) {
        tpc_pcbV->SetMedium(pcb_medium);
        PCBAssemblyA->SetMedium(pcb_medium);
    }
    else Fatal("Main", "Invalid medium for PCB plane!");

    tpc_pcbV->SetLineColor(TColor::GetColor("#ed9121"));
    //tpc_pcbV->SetTransparency(0);

    for(Int_t isec = 0; isec < Nsections; isec++) {
    //for(Int_t isec = 0; isec < 1; isec++) {
        TGeoCombiTrans *combi_trans = new TGeoCombiTrans();
        combi_trans->RotateX(-90.0);
        combi_trans->SetTranslation(0, Sens_vol_Y_center, half_module_width/2 - PCB_thickness/2);
        combi_trans->RotateZ(isec*Section_step);

        PCBAssemblyA->AddNode(tpc_pcbV, isec+1, combi_trans);
    }

    mother_volume->AddNode(PCBAssemblyA, 0);

    //Fill PCB with layers
    FillPCBWithLayers(tpc_pcbV);
}

void FillPCBWithLayers(TGeoVolume *mother_volume) {
    TString pcb_cu_name = "PCB_Cu";
    TString pcb_fr_name = "PCB_FR";

    //create Cu layer
    TGeoTrd1 *pcbCuS = new TGeoTrd1(pcb_cu_name, Sens_vol_x, Sens_vol_X, PCB_Cu_layer_thickness/2, Sens_vol_Y);
    TGeoVolume *pcbCuV = new TGeoVolume(pcb_cu_name, pcbCuS);

    TGeoMedium *pcbCu_medium = pMedCopper; //set medium
    if(pcbCu_medium) pcbCuV->SetMedium(pcbCu_medium);
    else Fatal("Main", "Invalid medium for PCB Cu layer!");

    pcbCuV->SetLineColor(TColor::GetColor("#ffb841"));

    mother_volume->AddNode(pcbCuV, 0, new TGeoTranslation(0, PCB_thickness/2 - PCB_Cu_layer_thickness/2, 0));

    //create FR layer
    TGeoTrd1 *pcbFRS = new TGeoTrd1(pcb_fr_name, Sens_vol_x, Sens_vol_X, PCB_FR_layer_thickness/2, Sens_vol_Y);
    TGeoVolume *pcbFRV = new TGeoVolume(pcb_fr_name, pcbFRS);

    TGeoMedium *pcbFR_medium = pMedFiberGlass; //set medium
    if(pcbFR_medium) pcbFRV->SetMedium(pcbFR_medium);
    else Fatal("Main", "Invalid medium for PCB FR layer!");

    pcbFRV->SetLineColor(TColor::GetColor("#ccccff"));

    mother_volume->AddNode(pcbFRV, 0, new TGeoTranslation(0, -PCB_thickness/2 + PCB_FR_layer_thickness/2, 0));
}

void CreateEndCaps(TGeoVolume *mother_volume) {
    TString endcap_name = "tpc01ec";

    Double_t endcap_rmin = TpcInnerRadius;
    Double_t endcap_rmax = TpcOuterRadius;
    Double_t endcap_thickness = Container_tpc_z/2 - Chamber_tpc_z/2;

    //Solids
    TGeoTube *tpcEndCapS = new TGeoTube(endcap_name, endcap_rmin, endcap_rmax, endcap_thickness/2);

    //Volumes
    TGeoVolume *tpcEndCapV = new TGeoVolume(endcap_name, tpcEndCapS);

    //medium
    TGeoMedium *endcap_medium = pMedAir; //set medium
    if(endcap_medium) tpcEndCapV->SetMedium(endcap_medium);
    else Fatal("Main", "Invalid medium for endcap!");

    //visual attributes
    tpcEndCapV->SetLineColor(TColor::GetColor("#d0e3f7"));

    //position
    TGeoTranslation *endcap_position1 = new TGeoTranslation("endcap_position1", 0, 0, Chamber_tpc_z/2 + endcap_thickness/2);

    //reflection
    TGeoCombiTrans *endcap_position2 = new TGeoCombiTrans();
    endcap_position2->ReflectZ(true);
    endcap_position2->SetTranslation(0, 0, -(Chamber_tpc_z/2 + endcap_thickness/2));

    //Attach membrane to mother volume
    mother_volume->AddNode(tpcEndCapV, 1, endcap_position1);
    mother_volume->AddNode(tpcEndCapV, 2, endcap_position2);

    //create flanches
    CreateFlanches(tpcEndCapV, endcap_thickness);

    //create ribs
    CreateRibs(tpcEndCapV, endcap_thickness);
}

void CreateFlanches(TGeoVolume *mother_volume, Double_t endcap_zwidth) {
    TString out_flanch_name = "tpc01of";
    TString in_flanch_name = "tpc01if";

    TGeoTube *tpcOutFlanchS = new TGeoTube(out_flanch_name, OuterFlanch_inner_radius, TpcOuterRadius, Flanch_thickness/2);
    TGeoTube *tpcInFlanchS = new TGeoTube(in_flanch_name, TpcInnerRadius, InnerFlanch_outer_radius, Flanch_thickness/2);

    TGeoVolume *tpcOutFlanchV = new TGeoVolume(out_flanch_name, tpcOutFlanchS);
    TGeoVolume *tpcInFlanchV = new TGeoVolume(in_flanch_name, tpcInFlanchS);

    TGeoMedium *flanch_medium = pMedAluminium; //set medium
    if(flanch_medium) {
        tpcOutFlanchV->SetMedium(flanch_medium);
        tpcInFlanchV->SetMedium(flanch_medium);
    }
    else Fatal("Main", "Invalid medium for flanches!");

    tpcOutFlanchV->SetLineColor(TColor::GetColor("#d0e3f7"));
    tpcInFlanchV->SetLineColor(TColor::GetColor("#d0e3f7"));

    mother_volume->AddNode(tpcOutFlanchV, 0, new TGeoTranslation(0, 0, Flanch_thickness/2 - endcap_zwidth/2));
    mother_volume->AddNode(tpcInFlanchV, 0, new TGeoTranslation(0, 0, Flanch_thickness/2 - endcap_zwidth/2));
}

void CreateRibs(TGeoVolume *mother_volume, Double_t endcap_zwidth) {
    TString rib_name = "tpc01Rib";

    Double_t yWidth = TpcOuterRadius - TpcInnerRadius - (InnerFlanch_width/2 + OuterFlanch_width/2);
    Double_t zpos = -endcap_zwidth/2 + Rib_width_z/2 + Flanch_thickness + Rib_position_z;

    TGeoBBox *tpcRibS = new TGeoBBox(rib_name, Rib_width_x/2, yWidth/2, Rib_width_z/2);

    TGeoVolume *tpcRibV = new TGeoVolume(rib_name, tpcRibS);

    TGeoMedium *rib_medium = pMedAluminium; //set medium
    if(rib_medium) tpcRibV->SetMedium(rib_medium);
    else Fatal("Main", "Invalid medium for ribs!");

    tpcRibV->SetLineColor(TColor::GetColor("#d0e3f7"));

    for(Int_t isec = 0; isec < Nsections; isec++) {
        TGeoCombiTrans *rib_position = new TGeoCombiTrans();
        rib_position->SetTranslation(0, yWidth/2 + TpcInnerRadius + InnerFlanch_width/2, zpos);
        rib_position->RotateZ(isec*Section_step + Section_step/2);

        mother_volume->AddNode(tpcRibV, isec+1, rib_position);
    }
}