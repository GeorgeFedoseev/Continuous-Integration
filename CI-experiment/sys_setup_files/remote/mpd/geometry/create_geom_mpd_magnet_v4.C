/*************************************************************************************
*  Author:     Elena Litvinenko (EL)
*  Project:    mpd.jinr.ru
*  Created:    30-Nov-2012
************************************************************************************/ 

#include "mpdshape.class.C"

void fix_pgon_coord( std::ostringstream &points_,Double_t zmin,Double_t zmax, Double_t rmin, Double_t rmax)
{
   points_ << "2 " << endl;
   points_ << "15 360 12 " << endl;
   points_ << zmin << " " << rmin << " " << rmax << endl;
   points_ << zmax << " " << rmin << " " << rmax << endl;
}

void fix_tube_coord( std::ostringstream &points_,Double_t zmin,Double_t zmax, Double_t rmin, Double_t rmax)
{
   points_ << "0. 0. "  << zmin<< endl;
   points_ << rmin << " " << rmax << endl;
   points_ << "0. 0. "  << zmax  << endl;
}

void create_geom_mpd_magnet_v4(const char* filename = "",const char *version_index="4_0")
{

  //  magnet elements in current version:
  //      ms01yokebarrel (iron) (1),
  //      ms01yokeend (iron) (6): '...in' - "eii","eio", '...mid' - "eim", and '...out' - "eoi", "eom", "eoo"
  //      ms01cryost (vacuum) (4 in 1): ms01cryostatbarrelin (steel) ,ms01cryostatbarrelout (steel), 
  //                                    ms01cryostatendcap - "cec" (steel), ms01solenoid (copper)

  Double_t

    Lz_min    = 7490.,      // min for ms01yokeendin
    Lz_sol    = 7750,       // ms01solenoid                  (value suggested by EL)
    Lz_cryo   = 8050.,      // ms01cryostatbarrelin, ms01cryostatbarrelout
    Lz_barrel = 8610.,      // ms01yokebarrel, =2*lz_min for ms01yokeendout "eoi", "eom", "eoo"
    Lz_max    = 9010.,      // =2*lz_max for ms01yokeendout "eoi", "eom", "eoo"

    wall_cryo = 5.,                     // wall thickness of the cryostat  (value suggested by EL)

    lz_cec_min = Lz_cryo/2,             // min for ms01cryostatendcap
    lz_cec_max = lz_cec_min+wall_cryo,  // max for ms01cryostatendcap

    // ms01yokeendin: "eii","eio"; ms01yokeendmid: "eim"; ms01yokeendout: "eoi", "eom", "eoo"

    lz_eio_min = 3745.,           // min for ms01yokeendin  "eio"
    lz_eii_min = lz_eio_min+50,   // min for ms01yokeendin  "eii" (value suggested by EL)
    lz_eim_min = 4025.,           // min for ms01yokeendmid "eim"
    lz_eoi_min = Lz_max/2-300.,  // min for ms01yokeendout "eoi", max for "eim"

    R_min_eii  = 1300./2,   // min for ms01yokeendin "eii"   (value suggested by EL)
    R_max_eii  = 2700./2,   // max for ms01yokeendin "eii", min for "eio"   (value suggested by EL)
    R_min_eim  = 2800./2,   // min for ms01yokeendmid "eim"  (value suggested by EL)
    R_min_eoi  = 2900./2,   // min for ms01yokeendout "eoi"  (value suggested by EL)
    R_max_eio  = 3100./2,   // max for ms01yokeendin  "eio"  (value suggested by EL)
    R_max_eim  = 3520./2,   // max for ms01yokeendmid "eim"  (value suggested by EL)
    R_max_eoi  = 3900./2,   // max for ms01yokeendout "eoi"   value suggested by EL)
    R_min_eom  = 4000./2,   // min for ms01yokeendout "eom"  (value suggested by EL)
    R_max_eom  = 6100./2-270,   // max for ms01yokeendout "eom", min for "eoo"
    R_max_eoo  = 6100./2,       // max for ms01yokeendout "eoo"
   
    width_sol = 200.,     // width of the solenoid           (value suggested by EL)
    width_yob  = 270.,    // width of the yok barrel

    R_min_2  = 4596./2,   // min for ms01cryostat, ms01cryostatbarrelin, ms01cryostatendcap 
    R_max_2  = R_min_2+wall_cryo,   // max for ms01cryostatbarrelin
    R_min_3  = R_max_2+66.,         // min for ms01solenoid,        (value suggested by EL)
    R_max_3  = R_min_3+width_sol,   // max for ms01solenoid
    R_min_4  = 5281./2-wall_cryo,   // min for ms01cryostatbarrelout
    R_max_4  = 5281./2,             // max for ms01cryostat, ms01cryostatbarrelout, ms01cryostatendcap

    R_min_5  = 6100./2-width_yob,   // min for ms01yokebarrel
    R_max_5  = 6100./2;             // max for ms01yokebarrel, ms01yokeendout             


   Int_t
     ix,
     iy,
     iz;

   ofstream* f;
   if (!strlen(filename)) {
     char filename1[200];
     sprintf(filename1,"magnet_v%s\.geo",version_index);   
     f = new ofstream(filename1, ios::out | ios::trunc);
     cout << "filename: " << filename1 << endl;
   }
   else {
     f = new ofstream(filename, ios::out | ios::trunc);
     cout << "filename: " << filename << endl;
   }

   std::ostringstream points;
   points.setf(ios::showpoint); points.setf(ios::fixed); points << setprecision(0);

   // yoke

   fix_pgon_coord(points,-Lz_barrel/2,Lz_barrel/2,R_min_5,R_max_5);	
   Mpdshape* ms01yokebarrel= new Mpdshape(f, "ms01yokebarrel","cave", "PGON", "iron", points.str()); 
   ms01yokebarrel->DumpToFile();
   points.str(""); 

   fix_tube_coord(points, lz_eii_min, lz_eim_min,R_min_eii,R_max_eii);	
   Mpdshape* ms01yokeend_eii= new Mpdshape(f, "ms01yokeendeii","cave", "TUBE", "iron", points.str());
   ms01yokeend_eii->SetSegment(1);
   ms01yokeend_eii->DumpWithIncrement();
   points.str(""); 

   fix_tube_coord(points, lz_eio_min, lz_eim_min,R_max_eii,R_max_eio);	
   Mpdshape* ms01yokeend_eio= new Mpdshape(f, "ms01yokeendeio","cave", "TUBE", "iron", points.str());
   ms01yokeend_eio->SetSegment(1);
   ms01yokeend_eio->DumpWithIncrement();
   points.str(""); 

   fix_tube_coord(points, lz_eim_min, lz_eoi_min,R_min_eim,R_max_eim);	
   Mpdshape* ms01yokeend_eim= new Mpdshape(f, "ms01yokeendeim","cave", "TUBE", "iron", points.str());
   ms01yokeend_eim->SetSegment(1);
   ms01yokeend_eim->DumpWithIncrement();
   points.str(""); 

   fix_tube_coord(points, lz_eoi_min, Lz_max/2.,R_min_eoi,R_max_eoi);	
   Mpdshape* ms01yokeend_eoi= new Mpdshape(f, "ms01yokeendeoi","cave", "TUBE", "iron", points.str());
   ms01yokeend_eoi->SetSegment(1);
   ms01yokeend_eoi->DumpWithIncrement();
   points.str(""); 

   fix_pgon_coord(points, lz_eoi_min, Lz_max/2.,R_min_eom,R_max_eom);	
   Mpdshape* ms01yokeend_eom= new Mpdshape(f, "ms01yokeendeom","cave", "PGON", "iron", points.str());
   ms01yokeend_eom->SetSegment(1);
   ms01yokeend_eom->DumpWithIncrement();
   points.str(""); 

   fix_pgon_coord(points, Lz_barrel/2., Lz_max/2.,R_max_eom,R_max_eoo);	
   Mpdshape* ms01yokeend_eoo= new Mpdshape(f, "ms01yokeendeoo","cave", "PGON", "iron", points.str());
   ms01yokeend_eoo->SetSegment(1);
   ms01yokeend_eoo->DumpWithIncrement();
   points.str(""); 

   ms01yokeend_eii->SetRotation("1. 0. 0. 0. 1. 0. 0. 0.  -1.");
   ms01yokeend_eii->DumpToFile();
   ms01yokeend_eio->SetRotation("1. 0. 0. 0. 1. 0. 0. 0.  -1.");
   ms01yokeend_eio->DumpToFile();
   ms01yokeend_eim->SetRotation("1. 0. 0. 0. 1. 0. 0. 0.  -1.");
   ms01yokeend_eim->DumpToFile();
   ms01yokeend_eoi->SetRotation("1. 0. 0. 0. 1. 0. 0. 0.  -1.");
   ms01yokeend_eoi->DumpToFile();
   ms01yokeend_eom->SetRotation("1. 0. 0. 0. 1. 0. 0. 0.  -1.");
   ms01yokeend_eom->DumpToFile();
   ms01yokeend_eoo->SetRotation("1. 0. 0. 0. 1. 0. 0. 0.  -1.");
   ms01yokeend_eoo->DumpToFile();

   // cryostat

   //   fix_tube_coord(points ,-Lz_cryo/2,Lz_cryo/2,R_min_2,R_max_4);	
   fix_tube_coord(points ,-Lz_cryo/2-5,Lz_cryo/2+5,R_min_2-1,R_max_4+1);	
   Mpdshape* ms01cryostat= new Mpdshape(f, "ms01cryostat","cave", "TUBE", "vacuum", points.str()); 
   ms01cryostat->DumpToFile();
   points.str(""); 

   fix_tube_coord(points ,-Lz_sol/2,Lz_sol/2,R_min_3,R_max_3);	
   Mpdshape* ms01solenoid= new Mpdshape(f, "ms01solenoid","ms01cryostat", "TUBE", "copper", points.str()); 
   ms01solenoid->DumpToFile();
   points.str(""); 

   fix_tube_coord(points ,-Lz_cryo/2,Lz_cryo/2,R_min_2,R_max_2);	
   Mpdshape* ms01cryostatbarrelin= new Mpdshape(f, "ms01cryostatbarrelin","ms01cryostat", "TUBE", 
						"steel", points.str()); 
   ms01cryostatbarrelin->DumpToFile();
   points.str(""); 

   fix_tube_coord(points ,-Lz_cryo/2,Lz_cryo/2,R_min_4,R_max_4);	
   Mpdshape* ms01cryostatbarrelout= new Mpdshape(f, "ms01cryostatbarrelout","ms01cryostat", "TUBE",
						 "steel", points.str()); 
   ms01cryostatbarrelout->DumpToFile();
   points.str(""); 

   fix_tube_coord(points ,lz_cec_min,lz_cec_max,R_min_2,R_max_4);	
   Mpdshape* ms01cryostatendcap= new Mpdshape(f, "ms01cryostatendcap","ms01cryostat", "TUBE", 
					      "steel", points.str()); 
   ms01cryostatendcap->SetSegment(1);
   ms01cryostatendcap->DumpWithIncrement();
   points.str(""); 

   ms01cryostatendcap->SetRotation("1. 0. 0. 0. 1. 0. 0. 0.  -1.");
   ms01cryostatendcap->DumpToFile();


   f->close(); 
}
