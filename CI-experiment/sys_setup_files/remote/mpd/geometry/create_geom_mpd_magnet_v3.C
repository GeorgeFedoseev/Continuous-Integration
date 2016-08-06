/*************************************************************************************
*  Author:     Elena Litvinenko (EL)
*  Project:    mpd.jinr.ru
*  Created:    09-Jun-2012
************************************************************************************/ 

#include "mpdshape.class.C"

void fix_pgon_coord( std::ostringstream &points_,Double_t zmin,Double_t zmax, Double_t rmin, Double_t rmax)
{
   points_ << "2 " << endl;
   points_ << "15 360 12 " << endl;
   points_ << zmin << " " << rmin << " " << rmax << endl;
   points_ << zmax << " " << rmin << " " << rmax << endl;
}

void create_geom_mpd_magnet_v3(const char* filename = "",const char *version_index="3_0")
{

  //#define MPD_MAGNET_VERSION_V2  // uncomment this line to create previous geo version

#ifdef MPD_MAGNET_VERSION_V2

  Double_t

    Lz_min    = 2600.*2,  // min for ms01yokeendin
    Lz_sol    = 2690.*2,  // ms01solenoid
    Lz_cryo   = 2695.*2,  // ms01cryostatbarrelin, ms01cryostatbarrelout, min for ms01cryostatendcap
    Lz_barrel = 2700.*2,  // ms01yokebarrel, ms01cryostat, 
                          // max for ms01yokeendin, min for ms01yokeendout, max for ms01cryostatendcap
    Lz_max    = 3150.*2,  // max for ms01yokeendout

    lz_cec_min = Lz_cryo/2,         // min for ms01cryostatendcap
    lz_cec_max = Lz_barrel/2,       // max for ms01cryostatendcap

    R_min_1  =  800.,   // min for ms01yokeendin, ms01yokeendout 
    delta    =    0.,   // min for ms01yokeendout = R_min_1 + delta
    R_max_1  = 1800.,   // max for ms01yokeendin
    R_min_2  = 2000.,   // min for ms01cryostat, ms01cryostatbarrelin, ms01cryostatendcap 
    R_max_2  = 2005.,   // max for ms01cryostatbarrelin
    R_min_3  = 2010.,   // min for ms01solenoid, 
    R_max_3  = 2190.,   // max for ms01solenoid
    R_min_4  = 2195.,   // min for ms01cryostatbarrelout
    R_max_4  = 2200.,   // max for ms01cryostat, ms01cryostatbarrelout, ms01cryostatendcap
    R_min_5  = 2305.,   // min for ms01yokebarrel
    R_max_5  = 2755;    // max for ms01yokebarrel, ms01yokeendout             

#else

  Double_t

    Lz_min    = 6340.,      // min for ms01yokeendin
    Lz_sol    = 6520,       // ms01solenoid                  (value suggested by EL)
    Lz_cryo   = 6900.,      // ms01cryostatbarrelin, ms01cryostatbarrelout
    Lz_barrel = 7300.,      // ms01yokebarrel, ms01cryostat, (value suggested by EL)
                            // max for ms01yokeendin, min for ms01yokeendout
    Lz_max    = 7860.,      // max for ms01yokeendout

//     lz_cec_min = Lz_min/2,         // min for ms01cryostatendcap
//     lz_cec_max = lz_cec_min+120,   // max for ms01cryostatendcap
    lz_cec_min = Lz_cryo/2,         // min for ms01cryostatendcap
    lz_cec_max = Lz_barrel/2,       // max for ms01cryostatendcap

    R_min_1  =  660.,   // min for ms01yokeendin 
    delta    =  790.,   // min for ms01yokeendout = R_min_1 + delta
    R_max_1  = 1600.,   // max for ms01yokeendin
    R_min_2  = 2020.,   // min for ms01cryostat, ms01cryostatbarrelin, ms01cryostatendcap 
    R_max_2  = 2025.,   // max for ms01cryostatbarrelin
    R_min_3  = 2030.,   // min for ms01solenoid, 
    R_max_3  = 2210.,   // max for ms01solenoid
    R_min_4  = 2215.,   // min for ms01cryostatbarrelout
    R_max_4  = 2220.,   // max for ms01cryostat, ms01cryostatbarrelout, ms01cryostatendcap
    R_min_5  = 2322.,   // min for ms01yokebarrel
    R_max_5  = 2772;    // max for ms01yokebarrel, ms01yokeendout             

#endif

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

   fix_pgon_coord(points ,-Lz_barrel/2,Lz_barrel/2,R_min_5,R_max_5);	
   Mpdshape* ms01yokebarrel= new Mpdshape(f, "ms01yokebarrel","cave", "PGON", "iron", points.str()); 
   ms01yokebarrel->DumpToFile();
   points.str(""); 

   fix_pgon_coord(points ,Lz_min/2,Lz_barrel/2,R_min_1,R_max_1);	
   Mpdshape* ms01yokeendin= new Mpdshape(f, "ms01yokeendin","cave", "PGON", "iron", points.str());
   ms01yokeendin->SetSegment(1);
   ms01yokeendin->DumpWithIncrement();
   points.str(""); 

   fix_pgon_coord(points ,Lz_barrel/2,Lz_max/2,R_min_1+delta,R_max_5);	
   Mpdshape* ms01yokeendout= new Mpdshape(f, "ms01yokeendout","cave", "PGON", "iron", points.str());
   ms01yokeendout->SetSegment(1);
   ms01yokeendout->DumpWithIncrement();
   points.str(""); 

   ms01yokeendin->SetRotation("1. 0. 0. 0. 1. 0. 0. 0.  -1.");
   ms01yokeendin->DumpToFile();

   ms01yokeendout->SetRotation("1. 0. 0. 0. 1. 0. 0. 0.  -1.");
   ms01yokeendout->DumpToFile();

   // cryostat

   fix_pgon_coord(points ,-Lz_barrel/2,Lz_barrel/2,R_min_2,R_max_4);	
   Mpdshape* ms01cryostat= new Mpdshape(f, "ms01cryostat","cave", "PGON", "vacuum", points.str()); 
   ms01cryostat->DumpToFile();
   points.str(""); 

   fix_pgon_coord(points ,-Lz_sol/2,Lz_sol/2,R_min_3,R_max_3);	
   Mpdshape* ms01solenoid= new Mpdshape(f, "ms01solenoid","ms01cryostat", "PGON", "copper", points.str()); 
   ms01solenoid->DumpToFile();
   points.str(""); 

   fix_pgon_coord(points ,-Lz_cryo/2,Lz_cryo/2,R_min_2,R_max_2);	
   Mpdshape* ms01cryostatbarrelin= new Mpdshape(f, "ms01cryostatbarrelin","ms01cryostat", "PGON", 
						"steel", points.str()); 
   ms01cryostatbarrelin->DumpToFile();
   points.str(""); 

   fix_pgon_coord(points ,-Lz_cryo/2,Lz_cryo/2,R_min_4,R_max_4);	
   Mpdshape* ms01cryostatbarrelout= new Mpdshape(f, "ms01cryostatbarrelout","ms01cryostat", "PGON",
						 "steel", points.str()); 
   ms01cryostatbarrelout->DumpToFile();
   points.str(""); 

   fix_pgon_coord(points ,lz_cec_min,lz_cec_max,R_min_2,R_max_4);	
   Mpdshape* ms01cryostatendcap= new Mpdshape(f, "ms01cryostatendcap","ms01cryostat", "PGON", 
					      "steel", points.str()); 
   ms01cryostatendcap->SetSegment(1);
   ms01cryostatendcap->DumpWithIncrement();
   points.str(""); 

   ms01cryostatendcap->SetRotation("1. 0. 0. 0. 1. 0. 0. 0.  -1.");
   ms01cryostatendcap->DumpToFile();


   f->close(); 
}
