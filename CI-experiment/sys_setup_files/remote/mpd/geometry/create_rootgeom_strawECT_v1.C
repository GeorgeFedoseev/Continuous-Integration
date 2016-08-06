//---------------------------
#include "TGeoManager.h"
#include "TGeoVolume.h"
#include "TGeoMedium.h"
#include "TFile.h"


//Detector's construct parameters

//Global dimensions for straw ECT in cm
Double_t strawECT_InnerRadius = 50.0; // ECT inner radius
Double_t strawECT_OuterRadius = 110.0; // ECT outer radius

//modules
Double_t strawECT_Module_dz = 30.0; // ECT module length
Double_t distance_between_modules = 13.0;

//submodules and layers
Double_t NSubModules_in_module = 5;
Double_t NLayers_in_submodule = 6;

Double_t Submodule_thickness = strawECT_Module_dz/NSubModules_in_module;
Double_t layer_thickness = Submodule_thickness/NLayers_in_submodule;

Double_t layer_rot_angle_radial_stereo = 0.141937308; //rotation angle between radial and stereo layer (degrees)
Double_t layer_rot_angle_stereo_stereo = 0.046357496; //rotation angle between stereo and stereo layer (degrees)

//straw tubes
Double_t tube_radius = 0.21;
Double_t gas_radius = 0.2;
Double_t wire_radius = 0.001;
Double_t tube_length = strawECT_OuterRadius - strawECT_InnerRadius;

Int_t straws_per_layer = 600;
Double_t straw_angle = 360.0/straws_per_layer; //degrees

Double_t straw_stereo_angle = 7.0;


//Detector's position
const Double_t ECT_Xpos = 0.0;
const Double_t ECT_Ypos = 0.0;
const Double_t ECT_Zpos_right_part = 200.0 + (2*strawECT_Module_dz+distance_between_modules)/2 + 13.0;

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
TGeoMedium *pMedKapton = 0;
TGeoMedium *pMedDCHmixture = 0;

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

    //kapton medium
    FairGeoMedium* mKapton = geoMedia->getMedium("kapton");
    if ( ! mKapton ) Fatal("Main", "FairMedium kapton not found");
    geoBuild->createMedium(mKapton);
    pMedKapton = gGeoManager->GetMedium("kapton");
    if ( ! pMedKapton ) Fatal("Main", "Medium kapton not found");

    //DCHmixture medium
    FairGeoMedium* mDCHmixture = geoMedia->getMedium("DCHmixture");
    if ( ! mDCHmixture ) Fatal("Main", "FairMedium DCHmixture not found");
    geoBuild->createMedium(mDCHmixture);
    pMedDCHmixture = gGeoManager->GetMedium("DCHmixture");
    if ( ! pMedDCHmixture ) Fatal("Main", "Medium DCHmixture not found");

    //gold medium
    FairGeoMedium* mGold = geoMedia->getMedium("gold");
    if ( ! mGold) Fatal("Main", "FairMedium gold not found");
    geoBuild->createMedium(mGold);
    pMedGold = gGeoManager->GetMedium("gold");
    if ( ! pMedGold ) Fatal("Main", "Medium gold not found");
}

void create_rootgeom_strawECT_v1() {

    // Load necessary libraries
    gROOT->LoadMacro("$VMCWORKDIR/macro/mpd/mpdloadlibs.C");
    mpdloadlibs(); // load libraries

    // ----  set working directory  --------------------------------------------
    TString gPath = gSystem->Getenv("VMCWORKDIR");

    // -------   Geometry file name (output)   ---------------------------------
    const TString geoDetectorName = "strawECT";
    const TString geoDetectorVersion = "v1";
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
    TString ect_name = "strawECT";

    TGeoVolume *ectA = new TGeoVolumeAssembly(ect_name);
    ectA->SetMedium(pMedAir);

    TString ectModule_name = "module";

    TGeoTube *ectModuleS = new TGeoTube(ectModule_name, strawECT_InnerRadius, strawECT_OuterRadius, strawECT_Module_dz/2);
    TGeoVolume *ectModuleV = new TGeoVolume(ectModule_name, ectModuleS);

    ectModuleV->SetMedium(pMedAir);

    ectModuleV->SetLineColor(TColor::GetColor("#fefe22"));
    //ectModuleV->SetVisibility(false);
    ectModuleV->SetTransparency(95);

    Double_t part_shift = ECT_Zpos_right_part;

    TGeoTranslation *ect_right_module1_position = new TGeoTranslation("ect_module1_position", ECT_Xpos, ECT_Ypos, -(distance_between_modules/2 + strawECT_Module_dz/2) + part_shift);
    TGeoTranslation *ect_right_module2_position = new TGeoTranslation("ect_module2_position", ECT_Xpos, ECT_Ypos, (distance_between_modules/2 + strawECT_Module_dz/2) + part_shift);

    TGeoCombiTrans *ect_left_module1_position = new TGeoCombiTrans(*ect_right_module1_position);
    ect_left_module1_position->ReflectZ(true);

    TGeoCombiTrans *ect_left_module2_position = new TGeoCombiTrans(*ect_right_module2_position);
    ect_left_module2_position->ReflectZ(true);

    ectA->AddNode(ectModuleV, 0, ect_right_module1_position);
    ectA->AddNode(ectModuleV, 1, ect_right_module2_position);
    ectA->AddNode(ectModuleV, 2, ect_left_module1_position);
    ectA->AddNode(ectModuleV, 3, ect_left_module2_position);

    //fill module with submodules
    FillModuleWithSubmodules(ectModuleV);


    //Adding the tpc mother valume to the global TOP Volume
    top->AddNode(ectA, 0);

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

void FillModuleWithSubmodules(TGeoVolume *mother_volume) {

    TString submodule_name = "sub_module";

    TGeoShape *submoduleS = new TGeoTube(submodule_name, strawECT_InnerRadius, strawECT_OuterRadius, Submodule_thickness/2);

    TGeoVolume *submoduleV = new TGeoVolume(submodule_name, submoduleS);

    TGeoMedium *submodule_medium = pMedAir; //set medium
    if(submodule_medium) submoduleV->SetMedium(submodule_medium);
    else Fatal("Main", "Invalid medium for submodule!");

    submoduleV->SetLineColor(TColor::GetColor("#fab700"));
    //submoduleV->SetVisibility(false);
    //submoduleV->SetTransparency(0);

    Double_t submodule_shift = 0.0;

    for(Int_t i = 0; i < NSubModules_in_module; i++) {
    //for(Int_t i = 0; i < 1; i++) {
        mother_volume->AddNode(submoduleV, i, new TGeoTranslation(0, 0, -strawECT_Module_dz/2 + Submodule_thickness/2 + submodule_shift));
        submodule_shift += Submodule_thickness;
    }

    //Fill submodule with layers
    FillSubModuleWithLayers(submoduleV);
}

void FillSubModuleWithLayers(TGeoVolume *mother_volume) {

    //Radial layer
    TString radial_layer_name = "layer_radial";
    TGeoShape *radial_layerS = new TGeoTube(radial_layer_name, strawECT_InnerRadius, strawECT_OuterRadius, layer_thickness/2);
    TGeoVolume *radial_layerV = new TGeoVolume(radial_layer_name, radial_layerS);

    TGeoMedium *layer_medium = pMedAir; //set medium
    if(layer_medium) radial_layerV->SetMedium(layer_medium);
    else Fatal("Main", "Invalid medium for layer!");

    radial_layerV->SetLineColor(TColor::GetColor("#9999ff"));
    //--------------------------------------------------------------------------

    //R-stereo angle layer (+alpha angle)
    TString rstereo_layer_name = "layer_stereoR";
    TGeoShape *rstereo_layerS = new TGeoTube(rstereo_layer_name, strawECT_InnerRadius, strawECT_OuterRadius, layer_thickness/2);
    TGeoVolume *rstereo_layerV = new TGeoVolume(rstereo_layer_name, rstereo_layerS);

    TGeoMedium *layer_medium = pMedAir; //set medium
    if(layer_medium) rstereo_layerV->SetMedium(layer_medium);
    else Fatal("Main", "Invalid medium for layer!");

    rstereo_layerV->SetLineColor(TColor::GetColor("#ff9494"));
    //--------------------------------------------------------------------------

    //L-stereo angle layer (-alpha angle)
    TString lstereo_layer_name = "layer_stereoL";
    TGeoShape *lstereo_layerS = new TGeoTube(lstereo_layer_name, strawECT_InnerRadius, strawECT_OuterRadius, layer_thickness/2);
    TGeoVolume *lstereo_layerV = new TGeoVolume(lstereo_layer_name, lstereo_layerS);

    TGeoMedium *layer_medium = pMedAir; //set medium
    if(layer_medium) lstereo_layerV->SetMedium(layer_medium);
    else Fatal("Main", "Invalid medium for layer!");

    lstereo_layerV->SetLineColor(TColor::GetColor("#a3ff66"));
    //lstereo_layerV->SetTransparency(0);
    //--------------------------------------------------------------------------

    Double_t layer_shift = 0.0;
    Double_t layer_rot_shift = 0.0;

    TGeoCombiTrans *layer_combi;

    for(Int_t i = 0; i < NLayers_in_submodule; i+=3) {
    //for(Int_t i = 0; i < 1; i++) {

        layer_combi = new TGeoCombiTrans();
        layer_combi->RotateZ(layer_rot_shift);
        layer_combi->SetTranslation(0, 0, -Submodule_thickness/2 + layer_thickness/2 + layer_shift);

        mother_volume->AddNode(radial_layerV, i+0, layer_combi);
        layer_shift += layer_thickness;
        layer_rot_shift += layer_rot_angle_radial_stereo;

        layer_combi = new TGeoCombiTrans();
        layer_combi->RotateZ(layer_rot_shift);
        layer_combi->SetTranslation(0, 0, -Submodule_thickness/2 + layer_thickness/2 + layer_shift);

        //mother_volume->AddNode(radial_layerV, i+1, layer_combi);
        mother_volume->AddNode(rstereo_layerV, i+1, layer_combi);
        layer_shift += layer_thickness;
        layer_rot_shift += layer_rot_angle_stereo_stereo;

        layer_combi = new TGeoCombiTrans();
        layer_combi->RotateZ(layer_rot_shift);
        layer_combi->SetTranslation(0, 0, -Submodule_thickness/2 + layer_thickness/2 + layer_shift);

        //mother_volume->AddNode(radial_layerV, i+2, layer_combi);
        mother_volume->AddNode(lstereo_layerV, i+2, layer_combi);
        layer_shift += layer_thickness;
        layer_rot_shift += layer_rot_angle_radial_stereo;
    }

    //fill radial layer with straw tubes
    FillRadialLayerWithTubes(radial_layerV);

    //fill R stereo layer with straw tubes
    FillRStereoLayerWithTubes(rstereo_layerV);

    //fill L stereo layer with straw tubes
    FillLStereoLayerWithTubes(lstereo_layerV);
}

TGeoVolume* CreateStrawTube() {
    TString straw_tube_name = "straw_tube";

    TGeoShape *strawTubeS = new TGeoTube(straw_tube_name, 0, tube_radius, tube_length/2);
    TGeoVolume *strawTubeV = new TGeoVolume(straw_tube_name, strawTubeS);

    TGeoMedium *strawTube_medium = pMedKapton; //set medium
    if(strawTube_medium) strawTubeV->SetMedium(strawTube_medium);
    else Fatal("Main", "Invalid medium for straw tube!");

    strawTubeV->SetLineColor(TColor::GetColor("#afdafc"));

    //fill tube with active gas
    FillTubeWithActiveGas(strawTubeV);

    //create wire
    CreateWireInStrawTube(strawTubeV);

    return strawTubeV;
}

void FillTubeWithActiveGas(TGeoVolume *mother_volume) {
    TString straw_gas_name = "straw_gas";

    TGeoShape *strawGasS = new TGeoTube(straw_gas_name, wire_radius, gas_radius, tube_length/2);
    TGeoVolume *strawGasV = new TGeoVolume(straw_gas_name, strawGasS);

    TGeoMedium *strawGas_medium = pMedDCHmixture; //set medium
    if(strawGas_medium) strawGasV->SetMedium(strawGas_medium);
    else Fatal("Main", "Invalid medium for straw gas!");

    strawGasV->SetLineColor(TColor::GetColor("#1cd3a2"));

    mother_volume->AddNode(strawGasV, 0);
}

void CreateWireInStrawTube(TGeoVolume *mother_volume) {
    TString straw_wire_name = "straw_wire";

    TGeoShape *strawWireS = new TGeoTube(straw_wire_name, 0, wire_radius, tube_length/2);
    TGeoVolume *strawWireV = new TGeoVolume(straw_wire_name, strawWireS);

    TGeoMedium *strawWire_medium = pMedCopper; //set medium
    if(strawWire_medium) strawWireV->SetMedium(strawWire_medium);
    else Fatal("Main", "Invalid medium for straw wire!");

    strawWireV->SetLineColor(TColor::GetColor("#ffc757"));

    mother_volume->AddNode(strawWireV, 0);
}

void FillRadialLayerWithTubes(TGeoVolume *mother_volume) {

    TGeoVolume *strawTubeV = CreateStrawTube();
    strawTubeV->SetLineColor(TColor::GetColor("#afdafc"));

    Double_t rot_angle_shift = 0.0;

    for(Int_t i = 0; i < straws_per_layer; i++) {
    //for(Int_t i = 0; i < 1; i++) {
        TGeoCombiTrans *tube_combi = new TGeoCombiTrans();
        tube_combi->RotateX(90.0);
        tube_combi->SetTranslation(0, tube_length/2 + strawECT_InnerRadius, 0);
        tube_combi->RotateZ(rot_angle_shift);

        rot_angle_shift += straw_angle;

        mother_volume->AddNode(strawTubeV, i, tube_combi);
    }

}

void FillRStereoLayerWithTubes(TGeoVolume *mother_volume) {

    TGeoVolume *strawTubeV = CreateStrawTube();
    strawTubeV->SetLineColor(TColor::GetColor("#f76dd2"));

    Double_t rot_angle_shift = 0.0;

    for(Int_t i = 0; i < straws_per_layer; i++) {
    //for(Int_t i = 0; i < 1; i++) {
        TGeoCombiTrans *tube_combi = new TGeoCombiTrans();
        tube_combi->RotateX(90.0);
        tube_combi->RotateZ(straw_stereo_angle);
        tube_combi->SetTranslation(0, tube_length/2 + strawECT_InnerRadius, 0);
        tube_combi->RotateZ(rot_angle_shift);

        rot_angle_shift += straw_angle;

        mother_volume->AddNode(strawTubeV, i, tube_combi);
    }
}

void FillLStereoLayerWithTubes(TGeoVolume *mother_volume) {
    TGeoVolume *strawTubeV = CreateStrawTube();
    strawTubeV->SetLineColor(TColor::GetColor("#5ad65a"));

    Double_t rot_angle_shift = 0.0;

    for(Int_t i = 0; i < straws_per_layer; i++) {
    //for(Int_t i = 0; i < 1; i++) {
        TGeoCombiTrans *tube_combi = new TGeoCombiTrans();
        tube_combi->RotateX(90.0);
        tube_combi->RotateZ(-straw_stereo_angle);
        tube_combi->SetTranslation(0, tube_length/2 + strawECT_InnerRadius, 0);
        tube_combi->RotateZ(rot_angle_shift);

        rot_angle_shift += straw_angle;

        mother_volume->AddNode(strawTubeV, i, tube_combi);
    }
}