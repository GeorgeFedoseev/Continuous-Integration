//Geometry parameters for TPC detector
#ifndef TPC_GEOM_PAR_H
#define	TPC_GEOM_PAr_H

namespace TPC {
    //Global dimensions for TPC in cm
    Double_t TpcInnerRadius = 27.0; // tpc inner radius
    Double_t TpcOuterRadius = 140.5; // tpc outer radius
    Double_t Container_tpc_z = 400.0; // common tpc length
    Double_t Chamber_tpc_z = 340.0;

    //Barrel walls in cm
    Double_t Thick_aluminium_layer = 0.005; // aluminium layer
    Double_t Thick_tedlar_layer = 0.005; // tedlar layer
    Double_t Thick_kevlar_layer = 0.3; // kevlar layer
    Double_t Thick_CO2_layer[2] = {6.7, 6.5};  //  outer barrel, innner barrel

    //Membrane in cm
    Double_t Membrane_thickness = 0.8; // honeycomb

    //Field cage in cm
    Double_t Fieldcage_out_rmax = 125.09;
    Double_t Fieldcage_out_rmin = 125.085;
    Double_t Fieldcage_in_rmax = 37.1;
    Double_t Fieldcage_in_rmin = 37.095;

    //pins for fieldcage in cm
    Double_t Fieldcage_r[2] = {126.4, 37.70};  //  out, in
    Double_t Fieldcage_pin_r[2] = {3.0, 0.67}; // out, in
    Double_t Fieldcage_wall_thick = 0.3;
    Double_t Fieldcage_phi_shift = 7.*TMath::DegToRad();

    //TPC pars
    Int_t Nsections = 12;
    Double_t Section_step = 360./Nsections; // degree
    Double_t Section_phi_step = TMath::DegToRad()*Section_step; //radian

    //sensitive volume trapezoid in cm
    Double_t Sens_vol_X = .5*64.16; //half
    Double_t Sens_vol_x = .5*21.29; //half
    Double_t Sens_vol_Y = .5*80.0; //half
    Double_t Sens_vol_Y_center = 80.3;

    //pad plane simulation in cm
    Double_t Plane_Pp = 0.3;
    Double_t Plane_G10 = 0.3;
    Double_t Plane_Al = 0.5;

    //flanches inside chamber_tpc_z in cm
    Double_t OuterFlanch_width = 26.8;
    Double_t InnerFlanch_width = 13.2;
    Double_t OuterFlanch_inner_radius = TpcOuterRadius - OuterFlanch_width;
    Double_t InnerFlanch_outer_radius = TpcInnerRadius + InnerFlanch_width;
    Double_t Flanch_thickness = 2.5;

    //ribs in cm
    Double_t Rib_width_x = 4.0;
    Double_t Rib_width_z = 4.0;
    Double_t Rib_position_z = 6.0; // distance from flanches

    //inner wall extension part in cm
    Double_t Flange_thickness = 5.0;
    Double_t ExtPart_length = 20.0;
    Double_t Flange_width = 2.85;

    //frames im cm
    Double_t Stiffening_rib_thickness = 1.0;
    Double_t Frame_big_part_y_width = 35.4;
    Double_t Frame_small_part_y_width = Sens_vol_Y*2.0 - Frame_big_part_y_width -Stiffening_rib_thickness;

    Double_t xy_frame_common_width = 3.9;
    Double_t z_frame_common_width = 5.5;

    Double_t xy_frame_out_width = 2.0;
    Double_t xy_frame_in_width = 1.9;

    Double_t z_frame_in_width = 1.0;
    Double_t z_frame_out_width = z_frame_common_width - z_frame_in_width;

    //PCB in cm
    Double_t PCB_thickness = 0.1716;
    //Double_t PCB_x_width = 9.5;
    //Double_t PCB_y_width = 16.7;
    Double_t PCB_Cu_layer_thickness = 0.0246; //cm
    Double_t PCB_FR_layer_thickness = PCB_thickness - PCB_Cu_layer_thickness; //cm
}

#endif	/* TPC_GEOM_PAR_H */

