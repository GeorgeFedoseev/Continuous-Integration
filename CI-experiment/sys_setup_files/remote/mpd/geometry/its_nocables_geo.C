#if !defined(__CINT__) || defined(__MAKECINT__)
// MPD includes
// Fair includes
#include "FairGeoRotation.h"

// ROOT includes
#include <TROOT.h>
#include <TMath.h>
#include <TSystem.h>
#include <TVector3.h>

#include <Riostream.h>
#include <sstream>
#endif

#include "mpdshape.class.C"

void its_nocables_geo()
{
  // 16.04.2012  VK
  // rotate ladders
  // 07.08.12 VV - remove cables !!!!!!!!!!!!!!!!!!!!!

  // Sector's structure of STS with cables

  const Int_t Nlayer = 4; // Number of layers in barrel
  Double_t radiusPipe = 0.5*80.; //mm// Radius of pipe
  Double_t outerRadius =0.5*500.; //mm// Radius of pipe
  // silicon elements of barrel
  Double_t sensor_l1 = 62.0; //mm// Length of sensor#1
  Double_t sensor_l2 = 124.0; //mm// Length of sensor#2
  Double_t sensor_l3 = 186.0; //mm// Length of sensor#3
  Double_t sensor_h = 62.0; //mm// Height of sensor
  Double_t sensorThick = 0.3; //mm// Thickness of sensor
	
  const Int_t Nsensor = 5;	// Sensors in ledder
  Double_t cableThick = 0.116; //mm// Cable thickness, equiv. silicon value 116um	
  Double_t cable_yshift = 0.15;  //mm// Y-coordinate Shift rel. to sensor y coord.
  Double_t sry[Nsensor]; //Right half-ledder sensors y-coord. 
  Double_t sly[Nsensor]; // Left --
  Double_t crz[Nsensor]; // Right half-ledder z-edge of the sensors
  Double_t clz[Nsensor]; // Left --
 
  Double_t deltaSensor = 0.8; //mm// Distance between modules in ladder
  Double_t delta = 2.0; //mm// Overlaping of ladder along circle (d)
  Double_t stock = 0.3; //mm// Size of frame for mother volume

  Double_t radiusIn[Nlayer]; // Inner radius of layer (r1)
  Double_t radiusOut[Nlayer]; // Outer radius of layer (r2)
  radiusIn[0] = 51.4;
  radiusOut[0] = 52.5;
  radiusIn[1] = 111.7;
  radiusOut[1] = 112.2;
  radiusIn[2] = 170.0;
  radiusOut[2] = 170.3;
  radiusIn[3] = 227.3;
  radiusOut[3] = 227.5;

  Double_t halfZ[Nlayer]; // Half-size of layers of barrel along z
  halfZ[0] = 552.; //mm// in 1-st layer
  halfZ[1] = 612.; //mm// in 2-nd layer
  halfZ[2] = 674.; //mm// in 3-d layer
  halfZ[3] = 736.; //mm// in 4-d layer
  Double_t ladderThick = 5.0; //mm// Thickness of ladder

  Int_t Nladders[Nlayer]; // Number of ladders in each layer
  Nladders[0] = 6;  // in 1-st layer
  Nladders[1] = 12; // in 2-nd layer
  Nladders[2] = 18; // in 3-d layer
  Nladders[3] = 24; // in 4-th layer

  Int_t Nelements[Nlayer]; // Number of sensors in one ladder in each layer
  Nelements[0] = 18; // in 1-st layer
  Nelements[1] = 20; // in 2-nd layer
  Nelements[2] = 22; // in 3-d layer
  Nelements[3] = 24; // in 4-th layer

  Int_t nSec1[Nlayer]; // Number of sectors 1 in one ladder in each layer
  Int_t nSec2[Nlayer]; // Number of sectors 2 in one ladder in each layer
  Int_t nSec3[Nlayer]; // Number of sectors 3 in one ladder in each layer
  nSec1[0] = 4; // in 1-st layer
  nSec2[0] = 4; // in 1-st layer
  nSec3[0] = 2; // in 1-st layer
  nSec1[1] = 4; // in 2-nd layer
  nSec2[1] = 2; // in 2-nd layer
  nSec3[1] = 4; // in 2-nd layer
  nSec1[2] = 2; // in 3-d layer
  nSec2[2] = 4; // in 3-d layer
  nSec3[2] = 4; // in 3-d layer
  nSec1[3] = 2; // in 4-th layer
  nSec2[3] = 2; // in 4-th layer
  nSec3[3] = 6; // in 4-th layer
  
    std::ostringstream cablename;

  //====== end declaration =======================================

  // output file
  const char* filename = "its_nocables.geo";
  ofstream* f = new ofstream(filename, ios::out | ios::trunc);
  // helper streams
  std::ostringstream points, position, rotation;
  points.setf(ios::showpoint); points.setf(ios::fixed);
  points << setprecision(6);
  position.setf(ios::showpoint); position.setf(ios::fixed);
  position << setprecision(6);
  rotation.setf(ios::showpoint); rotation.setf(ios::fixed);
  rotation << setprecision(6);

  // sts volume tube
  points.str(""); position.str(""); rotation.str("");
  points << 0.0 << " " << 0.0 << " " << halfZ[3]+5.0 << endl;
  points << radiusPipe << " " << outerRadius << endl;
  points << 0.0 << " " << 0.0 << " " << -halfZ[3]-5.0;

  // sts tube definition
  Mpdshape* tube = new Mpdshape(f, "sts01", "cave", "TUBE", "air",
				points.str());
  tube->SetSegment(0);
  tube->DumpWithIncrement();

  tube->SetSegment(0);
  tube->SetMotherVolumeName("sts01");
  tube->SetPosition(0.,0.,0.);

  Double_t x, y, z;

  // Layer 111111111111111111111111111111111111111111111111111111111111111
 
  // Ladder of 1-st layer (ladder1)
  Double_t xWidth = 0.5*(sensor_h + stock);
  Double_t yWidth = 0.5*(ladderThick);
  Double_t zWidth = halfZ[0] + 0.5*stock;

  points.str(""); position.str(""); rotation.str("");
  points << xWidth << " " << -yWidth << " " << -zWidth << endl;
  points << xWidth << " " << yWidth << " " << -zWidth << endl;
  points << -xWidth << " " << yWidth << " " << -zWidth << endl;
  points << -xWidth << " " << -yWidth << " " << -zWidth << endl;
  points << xWidth << " " << -yWidth << " " << zWidth << endl;
  points << xWidth << " " << yWidth << " " << zWidth << endl;
  points << -xWidth << " " << yWidth << " " << zWidth << endl;
  points << -xWidth << " " << -yWidth << " " << zWidth;

  // ladder1 (ladder definition for layer#1)
  Mpdshape* ladder1 = new Mpdshape(f, "sts01ladder1", "sts01", "BOX", "air",
				   points.str(), position.str());
  ladder1->SetSegment(1);

  Double_t* phis = new Double_t [Nladders[3]];
  Mpdshape** lads = new Mpdshape* [Nladders[3]];
  Int_t* inds = new Int_t [Nladders[3]];
  Int_t ipos = 0;

  // ladder1 positioning
  Double_t beta = 360./Nladders[0];
  Double_t beta_rad = beta*TMath::DegToRad();
  Double_t gamma = 90.;
  Double_t gamma_rad = gamma*TMath::DegToRad();
  Double_t alpha = 90.;

  Double_t Radius = radiusOut[0]+0.5*ladderThick;
  for (Int_t i = 0; i < Nladders[0]/2; i++) {
    x = Radius * TMath::Cos(gamma_rad+2.*beta_rad*i);
    y = Radius * TMath::Sin(gamma_rad+2.*beta_rad*i);
    points.str(""); position.str(""); rotation.str("");
    points << xWidth << " " << -yWidth << " " << -zWidth << endl;
    points << xWidth << " " << yWidth << " " << -zWidth << endl;
    points << -xWidth << " " << yWidth << " " << -zWidth << endl;
    points << -xWidth << " " << -yWidth << " " << -zWidth << endl;
    points << xWidth << " " << -yWidth << " " << zWidth << endl;
    points << xWidth << " " << yWidth << " " << zWidth << endl;
    points << -xWidth << " " << yWidth << " " << zWidth << endl;
    points << -xWidth << " " << -yWidth << " " << zWidth;

    phis[ipos] = TMath::ATan2(y,x);
    if (phis[ipos] < 0) phis[ipos] += TMath::TwoPi();
    ladder1 = new Mpdshape(f, "sts01ladder1", "sts01", "BOX", "air", "", "", "");
    lads[ipos++] = ladder1;

    ladder1->SetPosition(x,y,0.);
    ladder1->SetRotation(alpha+(gamma+2.*beta*i),0.,180.);
    ladder1->SetPoints(points.str());
    //ladder1->DumpWithIncrement();
  }

  Radius = radiusIn[0]-0.5*ladderThick;
  for (Int_t i = 0; i < Nladders[0]/2; i++) {

    x = Radius * TMath::Cos(gamma_rad+beta_rad+2.*beta_rad*i);
    y = Radius * TMath::Sin(gamma_rad+beta_rad+2.*beta_rad*i);

    points.str(""); position.str(""); rotation.str("");
    points << xWidth << " " << -yWidth << " " << -zWidth << endl;
    points << xWidth << " " << yWidth << " " << -zWidth << endl;
    points << -xWidth << " " << yWidth << " " << -zWidth << endl;
    points << -xWidth << " " << -yWidth << " " << -zWidth << endl;
    points << xWidth << " " << -yWidth << " " << zWidth << endl;
    points << xWidth << " " << yWidth << " " << zWidth << endl;
    points << -xWidth << " " << yWidth << " " << zWidth << endl;
    points << -xWidth << " " << -yWidth << " " << zWidth;

    phis[ipos] = TMath::ATan2(y,x);
    if (phis[ipos] < 0) phis[ipos] += TMath::TwoPi();
    ladder1 = new Mpdshape(f, "sts01ladder1", "sts01", "BOX", "air", "", "", "");
    lads[ipos++] = ladder1;

    ladder1->SetPosition(x,y,0.);
    ladder1->SetRotation(alpha+(gamma+beta+2.*beta*i),0.,180.);
    ladder1->SetPoints(points.str());
    //ladder1->DumpWithIncrement();
  }
  // Sort ladders in Phi
  TMath::Sort(Nladders[0],phis,inds,kFALSE);
  for (Int_t i = 0; i < Nladders[0]; ++i) {
  //for (Int_t i = 0; i < 1; ++i) {
    //cout << Nladders[0] << " " << i << " " << inds[i] << " " << lads[inds[i]] << endl;
    lads[inds[i]]->SetSegment(i+1);
    lads[inds[i]]->DumpToFile();
  }

  Double_t* zpos = new Double_t [Nelements[3]];
  Mpdshape** sens = new Mpdshape* [Nelements[3]];
  Int_t* inds1 = new Int_t [Nelements[3]];
  ipos = 0;

  // one sector 11 of ladder1 (sector 62*62)
  xWidth = 0.5*sensor_h; 
  yWidth = 0.5*sensorThick; 
  zWidth = 0.5*sensor_l1;
  
  points.str(""); position.str(""); rotation.str("");
  points << xWidth << " " << -yWidth << " " << -zWidth << endl;
  points << xWidth << " " << yWidth << " " << -zWidth << endl;
  points << -xWidth << " " << yWidth << " " << -zWidth << endl;
  points << -xWidth << " " << -yWidth << " " << -zWidth << endl;  
  points << xWidth << " " << -yWidth << " " << zWidth << endl;
  points << xWidth << " " << yWidth << " " << zWidth << endl;
  points << -xWidth << " " << yWidth << " " << zWidth << endl;
  points << -xWidth << " " << -yWidth << " " << zWidth;
  
  // sector 11 definition
  Mpdshape* sector11 = new Mpdshape(f, "sts01sector11", "sts01ladder1", 
				    "BOX", "silicon", points.str(), position.str());
  sector11->SetSegment(1);
  sector11->SetMotherSegment(1);
  
  // sectors 11 positioning into 1-st layer  

  for (Int_t j = 0; j < nSec1[0]/2; j++) {    	      
    
     y = 4.7-0.8*j; 
     z = (-1.+0.5*sensor_l1) + j*(sensor_l1-delta);
	 
	sry[j] = y-0.5*ladderThick;
	crz[j] = z+zWidth;

    points.str(""); position.str(""); rotation.str("");
    points << xWidth << " " << -yWidth << " " << -zWidth << endl;
    points << xWidth << " " << yWidth << " " << -zWidth << endl;
    points << -xWidth << " " << yWidth << " " << -zWidth << endl;
    points << -xWidth << " " << -yWidth << " " << -zWidth << endl;	
    points << xWidth << " " << -yWidth << " " << zWidth << endl;
    points << xWidth << " " << yWidth << " " << zWidth << endl;
    points << -xWidth << " " << yWidth << " " << zWidth << endl;
    points << -xWidth << " " << -yWidth << " " << zWidth;
    
    zpos[ipos] = z;
    sector11 = new Mpdshape(f, "sts01sector11", "sts01ladder1", "BOX", "silicon", "", "");
    sector11->SetMotherSegment(1);
    sens[ipos++] = sector11;
    
    sector11->SetPosition(0.,y-0.5*ladderThick,z);
    sector11->SetPoints(points.str());
    //sector11->DumpWithIncrement();        	 
  }  

  for (Int_t j = 0; j < nSec1[0]/2; j++) {    	      
    
     y = 3.9-0.8*j; 
     z = (1.-0.5*sensor_l1) - j*(sensor_l1-delta);

	   
      	    sly[j] = y-0.5*ladderThick;
            clz[j] = z-zWidth;

    points.str(""); position.str(""); rotation.str("");
    points << xWidth << " " << -yWidth << " " << -zWidth << endl;
    points << xWidth << " " << yWidth << " " << -zWidth << endl;
    points << -xWidth << " " << yWidth << " " << -zWidth << endl;
    points << -xWidth << " " << -yWidth << " " << -zWidth << endl;	
    points << xWidth << " " << -yWidth << " " << zWidth << endl;
    points << xWidth << " " << yWidth << " " << zWidth << endl;
    points << -xWidth << " " << yWidth << " " << zWidth << endl;
    points << -xWidth << " " << -yWidth << " " << zWidth;
    
    zpos[ipos] = z;
    sector11 = new Mpdshape(f, "sts01sector11", "sts01ladder1", "BOX", "silicon", "", "");
    sector11->SetMotherSegment(1);
    sens[ipos++] = sector11;
    
    sector11->SetPosition(0.,y-0.5*ladderThick,z);
    sector11->SetPoints(points.str());
    //sector11->DumpWithIncrement();        	 
  }  

  // one sector 21 of ladder1 (sector 62*124)
  xWidth = 0.5*sensor_h; 
  yWidth = 0.5*sensorThick; 
  zWidth = 0.5*sensor_l2;
  
  points.str(""); position.str(""); rotation.str("");
  points << xWidth << " " << -yWidth << " " << -zWidth << endl;
  points << xWidth << " " << yWidth << " " << -zWidth << endl;
  points << -xWidth << " " << yWidth << " " << -zWidth << endl;
  points << -xWidth << " " << -yWidth << " " << -zWidth << endl;  
  points << xWidth << " " << -yWidth << " " << zWidth << endl;
  points << xWidth << " " << yWidth << " " << zWidth << endl;
  points << -xWidth << " " << yWidth << " " << zWidth << endl;
  points << -xWidth << " " << -yWidth << " " << zWidth;
  
  // sector 21 definition
  Mpdshape* sector21 = new Mpdshape(f, "sts01sector21", "sts01ladder1", 
				    "BOX", "silicon", points.str(), position.str());
  sector21->SetSegment(1);
  sector21->SetMotherSegment(1);

  // sectors 21 positioning into 1-st layer  

  for (Int_t j = 0; j < nSec2[0]/2; j++) {    	      
    
     y = 4.7-0.8*(j+nSec1[0]/2); 
     z = (-1.+0.5*sensor_l2) + j*(sensor_l2-delta) + nSec1[0]/2*(sensor_l1-delta);

	    sry[j+nSec1[0]/2] = y-0.5*ladderThick;
            crz[j+nSec1[0]/2] = z+zWidth;
	 
    points.str(""); position.str(""); rotation.str("");
    points << xWidth << " " << -yWidth << " " << -zWidth << endl;
    points << xWidth << " " << yWidth << " " << -zWidth << endl;
    points << -xWidth << " " << yWidth << " " << -zWidth << endl;
    points << -xWidth << " " << -yWidth << " " << -zWidth << endl;	
    points << xWidth << " " << -yWidth << " " << zWidth << endl;
    points << xWidth << " " << yWidth << " " << zWidth << endl;
    points << -xWidth << " " << yWidth << " " << zWidth << endl;
    points << -xWidth << " " << -yWidth << " " << zWidth;
    
    zpos[ipos] = z;
    sector21 = new Mpdshape(f, "sts01sector21", "sts01ladder1", "BOX", "silicon", "", "");
    sector21->SetMotherSegment(1);
    sens[ipos++] = sector21;
    
    sector21->SetPosition(0.,y-0.5*ladderThick,z);
    sector21->SetPoints(points.str());
    //sector21->DumpWithIncrement();        	 
  }  

  for (Int_t j = 0; j < nSec2[0]/2; j++) {    	      
    
     y = 3.9-0.8*(j+nSec1[0]/2); 
     z = (1.-0.5*sensor_l2) - j*(sensor_l2-delta) - nSec1[0]/2*(sensor_l1-delta);

	    sly[j+nSec1[0]/2] = y-0.5*ladderThick;
            clz[j+nSec1[0]/2] = z-zWidth;
	  
    points.str(""); position.str(""); rotation.str("");
    points << xWidth << " " << -yWidth << " " << -zWidth << endl;
    points << xWidth << " " << yWidth << " " << -zWidth << endl;
    points << -xWidth << " " << yWidth << " " << -zWidth << endl;
    points << -xWidth << " " << -yWidth << " " << -zWidth << endl;	
    points << xWidth << " " << -yWidth << " " << zWidth << endl;
    points << xWidth << " " << yWidth << " " << zWidth << endl;
    points << -xWidth << " " << yWidth << " " << zWidth << endl;
    points << -xWidth << " " << -yWidth << " " << zWidth;
    
    zpos[ipos] = z;
    sector21 = new Mpdshape(f, "sts01sector21", "sts01ladder1", "BOX", "silicon", "", "");
    sector21->SetMotherSegment(1);
    sens[ipos++] = sector21;
    
    sector21->SetPosition(0.,y-0.5*ladderThick,z);
    sector21->SetPoints(points.str());
    //sector21->DumpWithIncrement();        	 
  }  

  // one sector 31 of ladder1 (sector 62*186)
  xWidth = 0.5*sensor_h; 
  yWidth = 0.5*sensorThick; 
  zWidth = 0.5*sensor_l3;
  
  points.str(""); position.str(""); rotation.str("");
  points << xWidth << " " << -yWidth << " " << -zWidth << endl;
  points << xWidth << " " << yWidth << " " << -zWidth << endl;
  points << -xWidth << " " << yWidth << " " << -zWidth << endl;
  points << -xWidth << " " << -yWidth << " " << -zWidth << endl;  
  points << xWidth << " " << -yWidth << " " << zWidth << endl;
  points << xWidth << " " << yWidth << " " << zWidth << endl;
  points << -xWidth << " " << yWidth << " " << zWidth << endl;
  points << -xWidth << " " << -yWidth << " " << zWidth;
  
  // sector 31 definition
  Mpdshape* sector31 = new Mpdshape(f, "sts01sector31", "sts01ladder1", 
				    "BOX", "silicon", points.str(), position.str());
  sector31->SetSegment(1);
  sector31->SetMotherSegment(1);
 
  // sectors 31 positioning into 1-st layer  

  for (Int_t j = 0; j < nSec3[0]/2; j++) {    	      
    
     y = 4.7-0.8*(j+nSec1[0]/2+nSec2[0]/2); 
     z = (-1.+0.5*sensor_l3) + j*(sensor_l3-delta) + nSec1[0]/2*(sensor_l1-delta) +nSec2[0]/2*(sensor_l2-delta);

	    sry[j+nSec1[0]/2+nSec2[0]/2] = y-0.5*ladderThick;
            crz[j+nSec1[0]/2+nSec2[0]/2] = z+zWidth;
	 
    points.str(""); position.str(""); rotation.str("");
    points << xWidth << " " << -yWidth << " " << -zWidth << endl;
    points << xWidth << " " << yWidth << " " << -zWidth << endl;
    points << -xWidth << " " << yWidth << " " << -zWidth << endl;
    points << -xWidth << " " << -yWidth << " " << -zWidth << endl;	
    points << xWidth << " " << -yWidth << " " << zWidth << endl;
    points << xWidth << " " << yWidth << " " << zWidth << endl;
    points << -xWidth << " " << yWidth << " " << zWidth << endl;
    points << -xWidth << " " << -yWidth << " " << zWidth;
        
    zpos[ipos] = z;
    sector31 = new Mpdshape(f, "sts01sector31", "sts01ladder1", "BOX", "silicon", "", "");
    sector31->SetMotherSegment(1);
    sens[ipos++] = sector31;
    
    sector31->SetPosition(0.,y-0.5*ladderThick,z);
    sector31->SetPoints(points.str());
    //sector31->DumpWithIncrement();        	 
  }  
 
  for (Int_t j = 0; j < nSec3[0]/2; j++) {    	      
    
     y = 3.9-0.8*(j+nSec1[0]/2+nSec2[0]/2); 
     z = (1.-0.5*sensor_l3) - j*(sensor_l3-delta) - nSec1[0]/2*(sensor_l1-delta) - nSec2[0]/2*(sensor_l2-delta);

	    sly[j+nSec1[0]/2+nSec2[0]/2] = y-0.5*ladderThick;
            clz[j+nSec1[0]/2+nSec2[0]/2] = z-zWidth;
	   
    points.str(""); position.str(""); rotation.str("");
    points << xWidth << " " << -yWidth << " " << -zWidth << endl;
    points << xWidth << " " << yWidth << " " << -zWidth << endl;
    points << -xWidth << " " << yWidth << " " << -zWidth << endl;
    points << -xWidth << " " << -yWidth << " " << -zWidth << endl;	
    points << xWidth << " " << -yWidth << " " << zWidth << endl;
    points << xWidth << " " << yWidth << " " << zWidth << endl;
    points << -xWidth << " " << yWidth << " " << zWidth << endl;
    points << -xWidth << " " << -yWidth << " " << zWidth;
        
    zpos[ipos] = z;
    sector31 = new Mpdshape(f, "sts01sector31", "sts01ladder1", "BOX", "silicon", "", "");
    sector31->SetMotherSegment(1);
    sens[ipos++] = sector31;
    
    sector31->SetPosition(0.,y-0.5*ladderThick,z);
    sector31->SetPoints(points.str());
    //sector31->DumpWithIncrement();        	 
  } 

  // Sort sectors in Z
  Int_t segmNo[3] = {0}, indx = -1;
  TMath::Sort(ipos,zpos,inds1,kFALSE);
  for (Int_t i = 0; i < ipos; ++i) {
    Mpdshape *shape = sens[inds1[i]];
    TString vol(shape->GetVolumeName());
    if (vol.Contains("11")) indx = 0;
    else if (vol.Contains("21")) indx = 1;
    else if (vol.Contains("31")) indx = 2;
    ++segmNo[indx];
    shape->SetSegment(segmNo[indx]);
    shape->DumpToFile();
  }

   /*
// cables ccccccccccccccccccccccccccccccccccccccccccccccccccccccccc
 for (Int_t j = 0; j < Nsensor - 1; j++) {   // 4 
  
  Double_t xWidth = 0.5*sensor_h; // always 31mm
  Double_t yWidth = 0.5*cableThick; // always 0.058 mm
 
// Start with "right" side
  Double_t zWidth = (crz[4]-crz[j])/2.;
  
  points.str(""); position.str(""); rotation.str("");
  points << xWidth << " " << -yWidth << " " << -zWidth << endl;
  points << xWidth << " " << yWidth << " " << -zWidth << endl;
  points << -xWidth << " " << yWidth << " " << -zWidth << endl;
  points << -xWidth << " " << -yWidth << " " << -zWidth << endl;  
  points << xWidth << " " << -yWidth << " " << zWidth << endl;
  points << xWidth << " " << yWidth << " " << zWidth << endl;
  points << -xWidth << " " << yWidth << " " << zWidth << endl;
  points << -xWidth << " " << -yWidth << " " << zWidth;
 
  cablename.str("");	
  cablename << "sts01ladder01cable0" << j+1;
	cout <<cablename.str() << endl;
	cout << crz[j] << endl;
    Mpdshape* cable = new Mpdshape(f, cablename.str(), "sts01ladder1", 
				     "BOX", "silicon_dead", points.str(), position.str());
  cable->SetSegment(1);
  cable->SetMotherSegment(1);
  
  cable->SetPosition(0.,sry[j]+cable_yshift,crz[j]+zWidth);
  cable->SetPoints(points.str());
  cable->DumpWithIncrement();        	
  
  cable->SetPosition(0.,sry[j]-cable_yshift,crz[j]+zWidth);
  cable->SetPoints(points.str());
  cable->DumpWithIncrement(); 	
  
// Left side
  Double_t zWidth = (clz[j]-clz[4])/2.;
  
  points.str(""); position.str(""); rotation.str("");
  points << xWidth << " " << -yWidth << " " << -zWidth << endl;
  points << xWidth << " " << yWidth << " " << -zWidth << endl;
  points << -xWidth << " " << yWidth << " " << -zWidth << endl;
  points << -xWidth << " " << -yWidth << " " << -zWidth << endl;  
  points << xWidth << " " << -yWidth << " " << zWidth << endl;
  points << xWidth << " " << yWidth << " " << zWidth << endl;
  points << -xWidth << " " << yWidth << " " << zWidth << endl;
  points << -xWidth << " " << -yWidth << " " << zWidth;

  cablename.str("");	
  cablename << "sts01ladder01cable0" << j+5;
	cout <<cablename.str() << endl;
	cout << clz[j] << endl;
    Mpdshape* cable = new Mpdshape(f, cablename.str(), "sts01ladder1", 
				     "BOX", "silicon_dead", points.str(), position.str());
  cable->SetSegment(1);
  cable->SetMotherSegment(1);
  
  cable->SetPosition(0.,sly[j]+cable_yshift,clz[j]-zWidth);
  cable->SetPoints(points.str());
  cable->DumpWithIncrement();        	
  
  cable->SetPosition(0.,sly[j]-cable_yshift,clz[j]-zWidth);
  cable->SetPoints(points.str());
  cable->DumpWithIncrement(); 	
} 
   */

  // Layer 22222222222222222222222222222222222222222222222222222222
 
  // Ladder of 2-nd layer (ladder2)
  xWidth = 0.5*(sensor_h + stock);
  yWidth = 0.5*(ladderThick);
  zWidth = halfZ[1] + 0.5*stock;

  points.str(""); position.str(""); rotation.str("");
  points << xWidth << " " << -yWidth << " " << -zWidth << endl;
  points << xWidth << " " << yWidth << " " << -zWidth << endl;
  points << -xWidth << " " << yWidth << " " << -zWidth << endl;
  points << -xWidth << " " << -yWidth << " " << -zWidth << endl;
  points << xWidth << " " << -yWidth << " " << zWidth << endl;
  points << xWidth << " " << yWidth << " " << zWidth << endl;
  points << -xWidth << " " << yWidth << " " << zWidth << endl;
  points << -xWidth << " " << -yWidth << " " << zWidth;

  // ladder2 (ladder definition for layer#2)
  Mpdshape* ladder2 = new Mpdshape(f, "sts01ladder2", "sts01", "BOX", "air",
				   points.str(), position.str());
  ladder2->SetSegment(1);

  // ladder2 positioning
  beta = 360./Nladders[1];
  beta_rad = beta*TMath::DegToRad();
  gamma = 90.;
  gamma_rad = gamma*TMath::DegToRad();
  alpha = 90.;

  ipos = 0;
  Radius = radiusOut[1]+0.5*ladderThick;
  for (Int_t i = 0; i < Nladders[1]/2; i++) {
    x = Radius * TMath::Cos(gamma_rad+2.*beta_rad*i);
    y = Radius * TMath::Sin(gamma_rad+2.*beta_rad*i);
    points.str(""); position.str(""); rotation.str("");
    points << xWidth << " " << -yWidth << " " << -zWidth << endl;
    points << xWidth << " " << yWidth << " " << -zWidth << endl;
    points << -xWidth << " " << yWidth << " " << -zWidth << endl;
    points << -xWidth << " " << -yWidth << " " << -zWidth << endl;
    points << xWidth << " " << -yWidth << " " << zWidth << endl;
    points << xWidth << " " << yWidth << " " << zWidth << endl;
    points << -xWidth << " " << yWidth << " " << zWidth << endl;
    points << -xWidth << " " << -yWidth << " " << zWidth;

    phis[ipos] = TMath::ATan2(y,x);
    if (phis[ipos] < 0) phis[ipos] += TMath::TwoPi();
    ladder2 = new Mpdshape(f, "sts01ladder2", "sts01", "BOX", "air", "", "", "");
    lads[ipos++] = ladder2;

    ladder2->SetPosition(x,y,0.);
    ladder2->SetRotation(alpha+(gamma+2.*beta*i),0.,180.);
    ladder2->SetPoints(points.str());
    //ladder2->DumpWithIncrement();
  }

  Radius = radiusIn[1]-0.5*ladderThick;
  for (Int_t i = 0; i < Nladders[1]/2; i++) {

    x = Radius * TMath::Cos(gamma_rad+beta_rad+2.*beta_rad*i);
    y = Radius * TMath::Sin(gamma_rad+beta_rad+2.*beta_rad*i);

    points.str(""); position.str(""); rotation.str("");
    points << xWidth << " " << -yWidth << " " << -zWidth << endl;
    points << xWidth << " " << yWidth << " " << -zWidth << endl;
    points << -xWidth << " " << yWidth << " " << -zWidth << endl;
    points << -xWidth << " " << -yWidth << " " << -zWidth << endl;
    points << xWidth << " " << -yWidth << " " << zWidth << endl;
    points << xWidth << " " << yWidth << " " << zWidth << endl;
    points << -xWidth << " " << yWidth << " " << zWidth << endl;
    points << -xWidth << " " << -yWidth << " " << zWidth;

    phis[ipos] = TMath::ATan2(y,x);
    if (phis[ipos] < 0) phis[ipos] += TMath::TwoPi();
    ladder2 = new Mpdshape(f, "sts01ladder2", "sts01", "BOX", "air", "", "", "");
    lads[ipos++] = ladder2;

    ladder2->SetPosition(x,y,0.);
    ladder2->SetRotation(alpha+(gamma+beta+2.*beta*i),0.,180.);
    ladder2->SetPoints(points.str());
    //ladder2->DumpWithIncrement();
  }
  // Sort ladders in Phi
  TMath::Sort(Nladders[1],phis,inds,kFALSE);
  for (Int_t i = 0; i < Nladders[1]; ++i) {
    lads[inds[i]]->SetSegment(i+1);
    lads[inds[i]]->DumpToFile();
  }

  // one sector 12 of ladder2 (sector 62*62)
  xWidth = 0.5*sensor_h; 
  yWidth = 0.5*sensorThick; 
  zWidth = 0.5*sensor_l1;
  
  points.str(""); position.str(""); rotation.str("");
  points << xWidth << " " << -yWidth << " " << -zWidth << endl;
  points << xWidth << " " << yWidth << " " << -zWidth << endl;
  points << -xWidth << " " << yWidth << " " << -zWidth << endl;
  points << -xWidth << " " << -yWidth << " " << -zWidth << endl;  
  points << xWidth << " " << -yWidth << " " << zWidth << endl;
  points << xWidth << " " << yWidth << " " << zWidth << endl;
  points << -xWidth << " " << yWidth << " " << zWidth << endl;
  points << -xWidth << " " << -yWidth << " " << zWidth;
  
  // sector 12 definition
  Mpdshape* sector12 = new Mpdshape(f, "sts01sector12", "sts01ladder2", 
				    "BOX", "silicon", points.str(), position.str());
  sector12->SetSegment(1);
  sector12->SetMotherSegment(1);
  ipos = 0;
  
  // sectors 12 positioning into 2-nd layer  

  for (Int_t j = 0; j < nSec1[1]/2; j++) {    	      
    
     y = 4.7-0.8*j; 
     z = (-1.+0.5*sensor_l1) + j*(sensor_l1-delta);
	 
	sry[j] = y-0.5*ladderThick;
	crz[j] = z+zWidth;

    points.str(""); position.str(""); rotation.str("");
    points << xWidth << " " << -yWidth << " " << -zWidth << endl;
    points << xWidth << " " << yWidth << " " << -zWidth << endl;
    points << -xWidth << " " << yWidth << " " << -zWidth << endl;
    points << -xWidth << " " << -yWidth << " " << -zWidth << endl;	
    points << xWidth << " " << -yWidth << " " << zWidth << endl;
    points << xWidth << " " << yWidth << " " << zWidth << endl;
    points << -xWidth << " " << yWidth << " " << zWidth << endl;
    points << -xWidth << " " << -yWidth << " " << zWidth;
    
    zpos[ipos] = z;
    sector12 = new Mpdshape(f, "sts01sector12", "sts01ladder2", "BOX", "silicon", "", "");
    sector12->SetMotherSegment(1);
    sens[ipos++] = sector12;

    sector12->SetPosition(0.,y-0.5*ladderThick,z);
    sector12->SetPoints(points.str());
    //sector12->DumpWithIncrement();        	 
  }  

  for (Int_t j = 0; j < nSec1[1]/2; j++) {    	      
    
     y = 3.9-0.8*j; 
     z = (1.-0.5*sensor_l1) - j*(sensor_l1-delta);
	   
      	    sly[j] = y-0.5*ladderThick;
            clz[j] = z-zWidth;

    points.str(""); position.str(""); rotation.str("");
    points << xWidth << " " << -yWidth << " " << -zWidth << endl;
    points << xWidth << " " << yWidth << " " << -zWidth << endl;
    points << -xWidth << " " << yWidth << " " << -zWidth << endl;
    points << -xWidth << " " << -yWidth << " " << -zWidth << endl;	
    points << xWidth << " " << -yWidth << " " << zWidth << endl;
    points << xWidth << " " << yWidth << " " << zWidth << endl;
    points << -xWidth << " " << yWidth << " " << zWidth << endl;
    points << -xWidth << " " << -yWidth << " " << zWidth;
    
    zpos[ipos] = z;
    sector12 = new Mpdshape(f, "sts01sector12", "sts01ladder2", "BOX", "silicon", "", "");
    sector12->SetMotherSegment(1);
    sens[ipos++] = sector12;

    sector12->SetPosition(0.,y-0.5*ladderThick,z);
    sector12->SetPoints(points.str());
    //sector12->DumpWithIncrement();        	 
  }  

  // one sector 22 of ladder2 (sector 62*124)
  xWidth = 0.5*sensor_h; 
  yWidth = 0.5*sensorThick; 
  zWidth = 0.5*sensor_l2;
  
  points.str(""); position.str(""); rotation.str("");
  points << xWidth << " " << -yWidth << " " << -zWidth << endl;
  points << xWidth << " " << yWidth << " " << -zWidth << endl;
  points << -xWidth << " " << yWidth << " " << -zWidth << endl;
  points << -xWidth << " " << -yWidth << " " << -zWidth << endl;  
  points << xWidth << " " << -yWidth << " " << zWidth << endl;
  points << xWidth << " " << yWidth << " " << zWidth << endl;
  points << -xWidth << " " << yWidth << " " << zWidth << endl;
  points << -xWidth << " " << -yWidth << " " << zWidth;
  
  // sector 22 definition
  Mpdshape* sector22 = new Mpdshape(f, "sts01sector22", "sts01ladder2", 
				    "BOX", "silicon", points.str(), position.str());
  sector22->SetSegment(1);
  sector22->SetMotherSegment(1);

  // sectors 22 positioning into 2-nd layer  

  for (Int_t j = 0; j < nSec2[1]/2; j++) {    	      
    
     y = 4.7-0.8*(j+nSec1[1]/2); 
     z = (-1.+0.5*sensor_l2) + j*(sensor_l2-delta) + nSec1[1]/2*(sensor_l1-delta);

	sry[j+nSec1[1]/2] = y-0.5*ladderThick;
	crz[j+nSec1[1]/2] = z+zWidth;
	 
    points.str(""); position.str(""); rotation.str("");
    points << xWidth << " " << -yWidth << " " << -zWidth << endl;
    points << xWidth << " " << yWidth << " " << -zWidth << endl;
    points << -xWidth << " " << yWidth << " " << -zWidth << endl;
    points << -xWidth << " " << -yWidth << " " << -zWidth << endl;	
    points << xWidth << " " << -yWidth << " " << zWidth << endl;
    points << xWidth << " " << yWidth << " " << zWidth << endl;
    points << -xWidth << " " << yWidth << " " << zWidth << endl;
    points << -xWidth << " " << -yWidth << " " << zWidth;
    
    zpos[ipos] = z;
    sector22 = new Mpdshape(f, "sts01sector22", "sts01ladder2", "BOX", "silicon", "", "");
    sector22->SetMotherSegment(1);
    sens[ipos++] = sector22;

    sector22->SetPosition(0.,y-0.5*ladderThick,z);
    sector22->SetPoints(points.str());
    //sector22->DumpWithIncrement();        	 
  }  

  for (Int_t j = 0; j < nSec2[1]/2; j++) {    	      
    
     y = 3.9-0.8*(j+nSec1[1]/2); 
     z = (1.-0.5*sensor_l2) - j*(sensor_l2-delta) - nSec1[1]/2*(sensor_l1-delta);

     sly[j+nSec1[1]/2] = y-0.5*ladderThick;
     clz[j+nSec1[1]/2] = z-zWidth;
	  
    points.str(""); position.str(""); rotation.str("");
    points << xWidth << " " << -yWidth << " " << -zWidth << endl;
    points << xWidth << " " << yWidth << " " << -zWidth << endl;
    points << -xWidth << " " << yWidth << " " << -zWidth << endl;
    points << -xWidth << " " << -yWidth << " " << -zWidth << endl;	
    points << xWidth << " " << -yWidth << " " << zWidth << endl;
    points << xWidth << " " << yWidth << " " << zWidth << endl;
    points << -xWidth << " " << yWidth << " " << zWidth << endl;
    points << -xWidth << " " << -yWidth << " " << zWidth;
    
    zpos[ipos] = z;
    sector22 = new Mpdshape(f, "sts01sector22", "sts01ladder2", "BOX", "silicon", "", "");
    sector22->SetMotherSegment(1);
    sens[ipos++] = sector22;

    sector22->SetPosition(0.,y-0.5*ladderThick,z);
    sector22->SetPoints(points.str());
    //sector22->DumpWithIncrement();        	 
  }  

  // one sector 32 of ladder2 (sector 62*186)
  xWidth = 0.5*sensor_h; 
  yWidth = 0.5*sensorThick; 
  zWidth = 0.5*sensor_l3;
  
  points.str(""); position.str(""); rotation.str("");
  points << xWidth << " " << -yWidth << " " << -zWidth << endl;
  points << xWidth << " " << yWidth << " " << -zWidth << endl;
  points << -xWidth << " " << yWidth << " " << -zWidth << endl;
  points << -xWidth << " " << -yWidth << " " << -zWidth << endl;  
  points << xWidth << " " << -yWidth << " " << zWidth << endl;
  points << xWidth << " " << yWidth << " " << zWidth << endl;
  points << -xWidth << " " << yWidth << " " << zWidth << endl;
  points << -xWidth << " " << -yWidth << " " << zWidth;
  
  // sector 32 definition
  Mpdshape* sector32 = new Mpdshape(f, "sts01sector32", "sts01ladder2", 
				    "BOX", "silicon", points.str(), position.str());
  sector32->SetSegment(1);
  sector32->SetMotherSegment(1);
 
  // sectors 32 positioning into 2-nd layer  

  for (Int_t j = 0; j < nSec3[1]/2; j++) {    	      
    
     y = 4.7-0.8*(j+nSec1[1]/2+nSec2[1]/2); 
     z = (-1.+0.5*sensor_l3) + j*(sensor_l3-delta) + nSec1[1]/2*(sensor_l1-delta) +nSec2[1]/2*(sensor_l2-delta);

	    sry[j+nSec1[1]/2+nSec2[1]/2] = y-0.5*ladderThick;
            crz[j+nSec1[1]/2+nSec2[1]/2] = z+zWidth;	 
	 
    points.str(""); position.str(""); rotation.str("");
    points << xWidth << " " << -yWidth << " " << -zWidth << endl;
    points << xWidth << " " << yWidth << " " << -zWidth << endl;
    points << -xWidth << " " << yWidth << " " << -zWidth << endl;
    points << -xWidth << " " << -yWidth << " " << -zWidth << endl;	
    points << xWidth << " " << -yWidth << " " << zWidth << endl;
    points << xWidth << " " << yWidth << " " << zWidth << endl;
    points << -xWidth << " " << yWidth << " " << zWidth << endl;
    points << -xWidth << " " << -yWidth << " " << zWidth;
        
    zpos[ipos] = z;
    sector32 = new Mpdshape(f, "sts01sector32", "sts01ladder2", "BOX", "silicon", "", "");
    sector32->SetMotherSegment(1);
    sens[ipos++] = sector32;

    sector32->SetPosition(0.,y-0.5*ladderThick,z);
    sector32->SetPoints(points.str());
    //sector32->DumpWithIncrement();        	 
  }  
 
  for (Int_t j = 0; j < nSec3[1]/2; j++) {    	      
    
     y = 3.9-0.8*(j+nSec1[1]/2+nSec2[1]/2); 
     z = (1.-0.5*sensor_l3) - j*(sensor_l3-delta) - nSec1[1]/2*(sensor_l1-delta) - nSec2[1]/2*(sensor_l2-delta);

	    sly[j+nSec1[1]/2+nSec2[1]/2] = y-0.5*ladderThick;
            clz[j+nSec1[1]/2+nSec2[1]/2] = z-zWidth;
	   
    points.str(""); position.str(""); rotation.str("");
    points << xWidth << " " << -yWidth << " " << -zWidth << endl;
    points << xWidth << " " << yWidth << " " << -zWidth << endl;
    points << -xWidth << " " << yWidth << " " << -zWidth << endl;
    points << -xWidth << " " << -yWidth << " " << -zWidth << endl;	
    points << xWidth << " " << -yWidth << " " << zWidth << endl;
    points << xWidth << " " << yWidth << " " << zWidth << endl;
    points << -xWidth << " " << yWidth << " " << zWidth << endl;
    points << -xWidth << " " << -yWidth << " " << zWidth;
        
    zpos[ipos] = z;
    sector32 = new Mpdshape(f, "sts01sector32", "sts01ladder2", "BOX", "silicon", "", "");
    sector32->SetMotherSegment(1);
    sens[ipos++] = sector32;

    sector32->SetPosition(0.,y-0.5*ladderThick,z);
    sector32->SetPoints(points.str());
    //sector32->DumpWithIncrement();        	 
  } 

  // Sort sectors in Z
  segmNo[0] = segmNo[1] = segmNo[2] = 0; 
  TMath::Sort(ipos,zpos,inds1,kFALSE);
  for (Int_t i = 0; i < ipos; ++i) {
    Mpdshape *shape = sens[inds1[i]];
    TString vol(shape->GetVolumeName());
    if (vol.Contains("12")) indx = 0;
    else if (vol.Contains("22")) indx = 1;
    else if (vol.Contains("32")) indx = 2;
    ++segmNo[indx];
    shape->SetSegment(segmNo[indx]);
    shape->DumpToFile();
  }

   /*
// cables ccccccccccccccccccccccccccccccccccccccccccccccccccccccccc
 for (Int_t j = 0; j < Nsensor - 1; j++) {   // 4 
  
  Double_t xWidth = 0.5*sensor_h; // always 31mm
  Double_t yWidth = 0.5*cableThick; // always 0.058 mm
 
// Start with "right" side
  Double_t zWidth = (crz[4]-crz[j])/2.;
  
  points.str(""); position.str(""); rotation.str("");
  points << xWidth << " " << -yWidth << " " << -zWidth << endl;
  points << xWidth << " " << yWidth << " " << -zWidth << endl;
  points << -xWidth << " " << yWidth << " " << -zWidth << endl;
  points << -xWidth << " " << -yWidth << " " << -zWidth << endl;  
  points << xWidth << " " << -yWidth << " " << zWidth << endl;
  points << xWidth << " " << yWidth << " " << zWidth << endl;
  points << -xWidth << " " << yWidth << " " << zWidth << endl;
  points << -xWidth << " " << -yWidth << " " << zWidth;
 
  cablename.str("");	
  cablename << "sts01ladder02cable0" << j+1;
//	cout <<cablename.str() << endl;
//	cout << crz[j] << endl;
    Mpdshape* cable = new Mpdshape(f, cablename.str(), "sts01ladder2", 
				     "BOX", "silicon_dead", points.str(), position.str());
  cable->SetSegment(1);
  cable->SetMotherSegment(1);
  
  cable->SetPosition(0.,sry[j]+cable_yshift,crz[j]+zWidth);
  cable->SetPoints(points.str());
  cable->DumpWithIncrement();        	
  
  cable->SetPosition(0.,sry[j]-cable_yshift,crz[j]+zWidth);
  cable->SetPoints(points.str());
  cable->DumpWithIncrement(); 	
  
// Left side
  Double_t zWidth = (clz[j]-clz[4])/2.;
  
  points.str(""); position.str(""); rotation.str("");
  points << xWidth << " " << -yWidth << " " << -zWidth << endl;
  points << xWidth << " " << yWidth << " " << -zWidth << endl;
  points << -xWidth << " " << yWidth << " " << -zWidth << endl;
  points << -xWidth << " " << -yWidth << " " << -zWidth << endl;  
  points << xWidth << " " << -yWidth << " " << zWidth << endl;
  points << xWidth << " " << yWidth << " " << zWidth << endl;
  points << -xWidth << " " << yWidth << " " << zWidth << endl;
  points << -xWidth << " " << -yWidth << " " << zWidth;

  cablename.str("");	
  cablename << "sts01ladder02cable0" << j+5;
//	cout <<cablename.str() << endl;
//	cout << clz[j] << endl;
    Mpdshape* cable = new Mpdshape(f, cablename.str(), "sts01ladder2", 
				     "BOX", "silicon_dead", points.str(), position.str());
  cable->SetSegment(1);
  cable->SetMotherSegment(1);
  
  cable->SetPosition(0.,sly[j]+cable_yshift,clz[j]-zWidth);
  cable->SetPoints(points.str());
  cable->DumpWithIncrement();        	
  
  cable->SetPosition(0.,sly[j]-cable_yshift,clz[j]-zWidth);
  cable->SetPoints(points.str());
  cable->DumpWithIncrement(); 	
} 
   */
  
  // Layer 33333333333333333333333333333333333333333333333333333333333333333333
 
  // Ladder of 3-rd layer (ladder3)
  xWidth = 0.5*(sensor_h + stock);
  yWidth = 0.5*(ladderThick);
  zWidth = halfZ[2] + 0.5*stock;

  points.str(""); position.str(""); rotation.str("");
  points << xWidth << " " << -yWidth << " " << -zWidth << endl;
  points << xWidth << " " << yWidth << " " << -zWidth << endl;
  points << -xWidth << " " << yWidth << " " << -zWidth << endl;
  points << -xWidth << " " << -yWidth << " " << -zWidth << endl;
  points << xWidth << " " << -yWidth << " " << zWidth << endl;
  points << xWidth << " " << yWidth << " " << zWidth << endl;
  points << -xWidth << " " << yWidth << " " << zWidth << endl;
  points << -xWidth << " " << -yWidth << " " << zWidth;

  // ladder3 (ladder definition for layer#3)
  Mpdshape* ladder3 = new Mpdshape(f, "sts01ladder3", "sts01", "BOX", "air",
				   points.str(), position.str());
  ladder3->SetSegment(1);

  // ladder3 positioning
  beta = 360./Nladders[2];
  beta_rad = beta*TMath::DegToRad();
  gamma = 90.;
  gamma_rad = gamma*TMath::DegToRad();
  alpha = 90.;

  ipos = 0;
  Radius = radiusOut[2]+0.5*ladderThick;
  for (Int_t i = 0; i < Nladders[2]/2; i++) {
    x = Radius * TMath::Cos(gamma_rad+2.*beta_rad*i);
    y = Radius * TMath::Sin(gamma_rad+2.*beta_rad*i);
    points.str(""); position.str(""); rotation.str("");
    points << xWidth << " " << -yWidth << " " << -zWidth << endl;
    points << xWidth << " " << yWidth << " " << -zWidth << endl;
    points << -xWidth << " " << yWidth << " " << -zWidth << endl;
    points << -xWidth << " " << -yWidth << " " << -zWidth << endl;
    points << xWidth << " " << -yWidth << " " << zWidth << endl;
    points << xWidth << " " << yWidth << " " << zWidth << endl;
    points << -xWidth << " " << yWidth << " " << zWidth << endl;
    points << -xWidth << " " << -yWidth << " " << zWidth;

    phis[ipos] = TMath::ATan2(y,x);
    if (phis[ipos] < 0) phis[ipos] += TMath::TwoPi();
    ladder3 = new Mpdshape(f, "sts01ladder3", "sts01", "BOX", "air", "", "", "");
    lads[ipos++] = ladder3;

    ladder3->SetPosition(x,y,0.);
    ladder3->SetRotation(alpha+(gamma+2.*beta*i),0.,180.);
    ladder3->SetPoints(points.str());
    //ladder3->DumpWithIncrement();
  }

  Radius = radiusIn[2]-0.5*ladderThick;
  for (Int_t i = 0; i < Nladders[2]/2; i++) {

    x = Radius * TMath::Cos(gamma_rad+beta_rad+2.*beta_rad*i);
    y = Radius * TMath::Sin(gamma_rad+beta_rad+2.*beta_rad*i);

    points.str(""); position.str(""); rotation.str("");
    points << xWidth << " " << -yWidth << " " << -zWidth << endl;
    points << xWidth << " " << yWidth << " " << -zWidth << endl;
    points << -xWidth << " " << yWidth << " " << -zWidth << endl;
    points << -xWidth << " " << -yWidth << " " << -zWidth << endl;
    points << xWidth << " " << -yWidth << " " << zWidth << endl;
    points << xWidth << " " << yWidth << " " << zWidth << endl;
    points << -xWidth << " " << yWidth << " " << zWidth << endl;
    points << -xWidth << " " << -yWidth << " " << zWidth;

    phis[ipos] = TMath::ATan2(y,x);
    if (phis[ipos] < 0) phis[ipos] += TMath::TwoPi();
    ladder3 = new Mpdshape(f, "sts01ladder3", "sts01", "BOX", "air", "", "", "");
    lads[ipos++] = ladder3;

    ladder3->SetPosition(x,y,0.);
    ladder3->SetRotation(alpha+(gamma+beta+2.*beta*i),0.,180.);
    ladder3->SetPoints(points.str());
    //ladder3->DumpWithIncrement();
  }
  // Sort ladders in Phi
  TMath::Sort(Nladders[2],phis,inds,kFALSE);
  for (Int_t i = 0; i < Nladders[2]; ++i) {
    lads[inds[i]]->SetSegment(i+1);
    lads[inds[i]]->DumpToFile();
  }

  // one sector 13 of ladder3 (sector 62*62)
  xWidth = 0.5*sensor_h; 
  yWidth = 0.5*sensorThick; 
  zWidth = 0.5*sensor_l1;
  
  points.str(""); position.str(""); rotation.str("");
  points << xWidth << " " << -yWidth << " " << -zWidth << endl;
  points << xWidth << " " << yWidth << " " << -zWidth << endl;
  points << -xWidth << " " << yWidth << " " << -zWidth << endl;
  points << -xWidth << " " << -yWidth << " " << -zWidth << endl;  
  points << xWidth << " " << -yWidth << " " << zWidth << endl;
  points << xWidth << " " << yWidth << " " << zWidth << endl;
  points << -xWidth << " " << yWidth << " " << zWidth << endl;
  points << -xWidth << " " << -yWidth << " " << zWidth;
  
  // sector 13 definition
  Mpdshape* sector13 = new Mpdshape(f, "sts01sector13", "sts01ladder3", 
				    "BOX", "silicon", points.str(), position.str());
  sector13->SetSegment(1);
  sector13->SetMotherSegment(1);
  ipos = 0;
  
  // sectors 13 positioning into 3-rd layer  

  for (Int_t j = 0; j < nSec1[2]/2; j++) {    	      
    
     y = 4.7-0.8*j; 
     z = (-1.+0.5*sensor_l1) + j*(sensor_l1-delta);

	sry[j] = y-0.5*ladderThick;
	crz[j] = z+zWidth;

    points.str(""); position.str(""); rotation.str("");
    points << xWidth << " " << -yWidth << " " << -zWidth << endl;
    points << xWidth << " " << yWidth << " " << -zWidth << endl;
    points << -xWidth << " " << yWidth << " " << -zWidth << endl;
    points << -xWidth << " " << -yWidth << " " << -zWidth << endl;	
    points << xWidth << " " << -yWidth << " " << zWidth << endl;
    points << xWidth << " " << yWidth << " " << zWidth << endl;
    points << -xWidth << " " << yWidth << " " << zWidth << endl;
    points << -xWidth << " " << -yWidth << " " << zWidth;
    
    zpos[ipos] = z;
    sector13 = new Mpdshape(f, "sts01sector13", "sts01ladder3", "BOX", "silicon", "", "");
    sector13->SetMotherSegment(1);
    sens[ipos++] = sector13;

    sector13->SetPosition(0.,y-0.5*ladderThick,z);
    sector13->SetPoints(points.str());
    //sector13->DumpWithIncrement();        	 
  }  

  for (Int_t j = 0; j < nSec1[2]/2; j++) {    	      
    
     y = 3.9-0.8*j; 
     z = (1.-0.5*sensor_l1) - j*(sensor_l1-delta);
	   
      	    sly[j] = y-0.5*ladderThick;
            clz[j] = z-zWidth;

    points.str(""); position.str(""); rotation.str("");
    points << xWidth << " " << -yWidth << " " << -zWidth << endl;
    points << xWidth << " " << yWidth << " " << -zWidth << endl;
    points << -xWidth << " " << yWidth << " " << -zWidth << endl;
    points << -xWidth << " " << -yWidth << " " << -zWidth << endl;	
    points << xWidth << " " << -yWidth << " " << zWidth << endl;
    points << xWidth << " " << yWidth << " " << zWidth << endl;
    points << -xWidth << " " << yWidth << " " << zWidth << endl;
    points << -xWidth << " " << -yWidth << " " << zWidth;
    
    zpos[ipos] = z;
    sector13 = new Mpdshape(f, "sts01sector13", "sts01ladder3", "BOX", "silicon", "", "");
    sector13->SetMotherSegment(1);
    sens[ipos++] = sector13;

    sector13->SetPosition(0.,y-0.5*ladderThick,z);
    sector13->SetPoints(points.str());
    //sector13->DumpWithIncrement();        	 
  }  

  // one sector 23 of ladder3 (sector 62*124)
  xWidth = 0.5*sensor_h; 
  yWidth = 0.5*sensorThick; 
  zWidth = 0.5*sensor_l2;
  
  points.str(""); position.str(""); rotation.str("");
  points << xWidth << " " << -yWidth << " " << -zWidth << endl;
  points << xWidth << " " << yWidth << " " << -zWidth << endl;
  points << -xWidth << " " << yWidth << " " << -zWidth << endl;
  points << -xWidth << " " << -yWidth << " " << -zWidth << endl;  
  points << xWidth << " " << -yWidth << " " << zWidth << endl;
  points << xWidth << " " << yWidth << " " << zWidth << endl;
  points << -xWidth << " " << yWidth << " " << zWidth << endl;
  points << -xWidth << " " << -yWidth << " " << zWidth;
  
  // sector 23 definition
  Mpdshape* sector23 = new Mpdshape(f, "sts01sector23", "sts01ladder3", 
				    "BOX", "silicon", points.str(), position.str());
  sector23->SetSegment(1);
  sector23->SetMotherSegment(1);

  // sectors 23 positioning into 3-rd layer  

  for (Int_t j = 0; j < nSec2[2]/2; j++) {    	      
    
     y = 4.7-0.8*(j+nSec1[2]/2); 
     z = (-1.+0.5*sensor_l2) + j*(sensor_l2-delta) + nSec1[2]/2*(sensor_l1-delta);

	    sry[j+nSec1[2]/2] = y-0.5*ladderThick;
            crz[j+nSec1[2]/2] = z+zWidth;
	 
    points.str(""); position.str(""); rotation.str("");
    points << xWidth << " " << -yWidth << " " << -zWidth << endl;
    points << xWidth << " " << yWidth << " " << -zWidth << endl;
    points << -xWidth << " " << yWidth << " " << -zWidth << endl;
    points << -xWidth << " " << -yWidth << " " << -zWidth << endl;	
    points << xWidth << " " << -yWidth << " " << zWidth << endl;
    points << xWidth << " " << yWidth << " " << zWidth << endl;
    points << -xWidth << " " << yWidth << " " << zWidth << endl;
    points << -xWidth << " " << -yWidth << " " << zWidth;
    
    zpos[ipos] = z;
    sector23 = new Mpdshape(f, "sts01sector23", "sts01ladder3", "BOX", "silicon", "", "");
    sector23->SetMotherSegment(1);
    sens[ipos++] = sector23;

    sector23->SetPosition(0.,y-0.5*ladderThick,z);
    sector23->SetPoints(points.str());
    //sector23->DumpWithIncrement();        	 
  }  

  for (Int_t j = 0; j < nSec2[2]/2; j++) {    	      
    
     y = 3.9-0.8*(j+nSec1[2]/2); 
     z = (1.-0.5*sensor_l2) - j*(sensor_l2-delta) - nSec1[2]/2*(sensor_l1-delta);

	    sly[j+nSec1[2]/2] = y-0.5*ladderThick;
            clz[j+nSec1[2]/2] = z-zWidth;
	  
    points.str(""); position.str(""); rotation.str("");
    points << xWidth << " " << -yWidth << " " << -zWidth << endl;
    points << xWidth << " " << yWidth << " " << -zWidth << endl;
    points << -xWidth << " " << yWidth << " " << -zWidth << endl;
    points << -xWidth << " " << -yWidth << " " << -zWidth << endl;	
    points << xWidth << " " << -yWidth << " " << zWidth << endl;
    points << xWidth << " " << yWidth << " " << zWidth << endl;
    points << -xWidth << " " << yWidth << " " << zWidth << endl;
    points << -xWidth << " " << -yWidth << " " << zWidth;
    
    zpos[ipos] = z;
    sector23 = new Mpdshape(f, "sts01sector23", "sts01ladder3", "BOX", "silicon", "", "");
    sector23->SetMotherSegment(1);
    sens[ipos++] = sector23;

    sector23->SetPosition(0.,y-0.5*ladderThick,z);
    sector23->SetPoints(points.str());
    //sector23->DumpWithIncrement();        	 
  }  

  // one sector 33 of ladder3 (sector 62*186)
  xWidth = 0.5*sensor_h; 
  yWidth = 0.5*sensorThick; 
  zWidth = 0.5*sensor_l3;
  
  points.str(""); position.str(""); rotation.str("");
  points << xWidth << " " << -yWidth << " " << -zWidth << endl;
  points << xWidth << " " << yWidth << " " << -zWidth << endl;
  points << -xWidth << " " << yWidth << " " << -zWidth << endl;
  points << -xWidth << " " << -yWidth << " " << -zWidth << endl;  
  points << xWidth << " " << -yWidth << " " << zWidth << endl;
  points << xWidth << " " << yWidth << " " << zWidth << endl;
  points << -xWidth << " " << yWidth << " " << zWidth << endl;
  points << -xWidth << " " << -yWidth << " " << zWidth;
  
  // sector 33 definition
  Mpdshape* sector33 = new Mpdshape(f, "sts01sector33", "sts01ladder3", 
				    "BOX", "silicon", points.str(), position.str());
  sector33->SetSegment(1);
  sector33->SetMotherSegment(1);
 
  // sectors 33 positioning into 3-rd layer  

  for (Int_t j = 0; j < nSec3[2]/2; j++) {    	      
    
     y = 4.7-0.8*(j+nSec1[2]/2+nSec2[2]/2); 
     z = (-1.+0.5*sensor_l3) + j*(sensor_l3-delta) + nSec1[2]/2*(sensor_l1-delta) +nSec2[2]/2*(sensor_l2-delta);

	    sry[j+nSec1[2]/2+nSec2[2]/2] = y-0.5*ladderThick;
            crz[j+nSec1[2]/2+nSec2[2]/2] = z+zWidth;
	 
    points.str(""); position.str(""); rotation.str("");
    points << xWidth << " " << -yWidth << " " << -zWidth << endl;
    points << xWidth << " " << yWidth << " " << -zWidth << endl;
    points << -xWidth << " " << yWidth << " " << -zWidth << endl;
    points << -xWidth << " " << -yWidth << " " << -zWidth << endl;	
    points << xWidth << " " << -yWidth << " " << zWidth << endl;
    points << xWidth << " " << yWidth << " " << zWidth << endl;
    points << -xWidth << " " << yWidth << " " << zWidth << endl;
    points << -xWidth << " " << -yWidth << " " << zWidth;
        
    zpos[ipos] = z;
    sector33 = new Mpdshape(f, "sts01sector33", "sts01ladder3", "BOX", "silicon", "", "");
    sector33->SetMotherSegment(1);
    sens[ipos++] = sector33;

    sector33->SetPosition(0.,y-0.5*ladderThick,z);
    sector33->SetPoints(points.str());
    //sector33->DumpWithIncrement();        	 
  }  
 
  for (Int_t j = 0; j < nSec3[2]/2; j++) {    	      
    
     y = 3.9-0.8*(j+nSec1[2]/2+nSec2[2]/2); 
     z = (1.-0.5*sensor_l3) - j*(sensor_l3-delta) - nSec1[2]/2*(sensor_l1-delta) - nSec2[2]/2*(sensor_l2-delta);

	    sly[j+nSec1[2]/2+nSec2[2]/2] = y-0.5*ladderThick;
            clz[j+nSec1[2]/2+nSec2[2]/2] = z-zWidth;
	   
    points.str(""); position.str(""); rotation.str("");
    points << xWidth << " " << -yWidth << " " << -zWidth << endl;
    points << xWidth << " " << yWidth << " " << -zWidth << endl;
    points << -xWidth << " " << yWidth << " " << -zWidth << endl;
    points << -xWidth << " " << -yWidth << " " << -zWidth << endl;	
    points << xWidth << " " << -yWidth << " " << zWidth << endl;
    points << xWidth << " " << yWidth << " " << zWidth << endl;
    points << -xWidth << " " << yWidth << " " << zWidth << endl;
    points << -xWidth << " " << -yWidth << " " << zWidth;
        
    zpos[ipos] = z;
    sector33 = new Mpdshape(f, "sts01sector33", "sts01ladder3", "BOX", "silicon", "", "");
    sector33->SetMotherSegment(1);
    sens[ipos++] = sector33;

    sector33->SetPosition(0.,y-0.5*ladderThick,z);
    sector33->SetPoints(points.str());
    //sector33->DumpWithIncrement();        	 
  } 

  // Sort sectors in Z
  segmNo[0] = segmNo[1] = segmNo[2] = 0;
  TMath::Sort(ipos,zpos,inds1,kFALSE);
  for (Int_t i = 0; i < ipos; ++i) {
    Mpdshape *shape = sens[inds1[i]];
    TString vol(shape->GetVolumeName());
    if (vol.Contains("13")) indx = 0;
    else if (vol.Contains("23")) indx = 1;
    else if (vol.Contains("33")) indx = 2;
    ++segmNo[indx];
    shape->SetSegment(segmNo[indx]);
    shape->DumpToFile();
  }

   /*
// cables ccccccccccccccccccccccccccccccccccccccccccccccccccccccccc
 for (Int_t j = 0; j < Nsensor - 1; j++) {   // 4 
  
  Double_t xWidth = 0.5*sensor_h; // always 31mm
  Double_t yWidth = 0.5*cableThick; // always 0.058 mm
 
// Start with "right" side
  Double_t zWidth = (crz[4]-crz[j])/2.;
  
  points.str(""); position.str(""); rotation.str("");
  points << xWidth << " " << -yWidth << " " << -zWidth << endl;
  points << xWidth << " " << yWidth << " " << -zWidth << endl;
  points << -xWidth << " " << yWidth << " " << -zWidth << endl;
  points << -xWidth << " " << -yWidth << " " << -zWidth << endl;  
  points << xWidth << " " << -yWidth << " " << zWidth << endl;
  points << xWidth << " " << yWidth << " " << zWidth << endl;
  points << -xWidth << " " << yWidth << " " << zWidth << endl;
  points << -xWidth << " " << -yWidth << " " << zWidth;
 
  cablename.str("");	
  cablename << "sts01ladder03cable0" << j+1;
	cout <<cablename.str() << endl;
	cout << crz[j] << endl;
    Mpdshape* cable = new Mpdshape(f, cablename.str(), "sts01ladder3", 
				     "BOX", "silicon_dead", points.str(), position.str());
  cable->SetSegment(1);
  cable->SetMotherSegment(1);
  
  cable->SetPosition(0.,sry[j]+cable_yshift,crz[j]+zWidth);
  cable->SetPoints(points.str());
  cable->DumpWithIncrement();        	
  
  cable->SetPosition(0.,sry[j]-cable_yshift,crz[j]+zWidth);
  cable->SetPoints(points.str());
  cable->DumpWithIncrement(); 	
  
// Left side
  Double_t zWidth = (clz[j]-clz[4])/2.;
  
  points.str(""); position.str(""); rotation.str("");
  points << xWidth << " " << -yWidth << " " << -zWidth << endl;
  points << xWidth << " " << yWidth << " " << -zWidth << endl;
  points << -xWidth << " " << yWidth << " " << -zWidth << endl;
  points << -xWidth << " " << -yWidth << " " << -zWidth << endl;  
  points << xWidth << " " << -yWidth << " " << zWidth << endl;
  points << xWidth << " " << yWidth << " " << zWidth << endl;
  points << -xWidth << " " << yWidth << " " << zWidth << endl;
  points << -xWidth << " " << -yWidth << " " << zWidth;

  cablename.str("");	
  cablename << "sts01ladder03cable0" << j+5;
	cout <<cablename.str() << endl;
	cout << clz[j] << endl;
    Mpdshape* cable = new Mpdshape(f, cablename.str(), "sts01ladder3", 
				     "BOX", "silicon_dead", points.str(), position.str());
  cable->SetSegment(1);
  cable->SetMotherSegment(1);
  
  cable->SetPosition(0.,sly[j]+cable_yshift,clz[j]-zWidth);
  cable->SetPoints(points.str());
  cable->DumpWithIncrement();        	
  
  cable->SetPosition(0.,sly[j]-cable_yshift,clz[j]-zWidth);
  cable->SetPoints(points.str());
  cable->DumpWithIncrement(); 	
} 
   */
  
  // Layer 4444444444444444444444444444444444444444444444444444444444444444444444444444444444
 
  // Ladder of 4-th layer (ladder4)
  xWidth = 0.5*(sensor_h + stock);
  yWidth = 0.5*(ladderThick);
  zWidth = halfZ[3] + 0.5*stock;

  points.str(""); position.str(""); rotation.str("");
  points << xWidth << " " << -yWidth << " " << -zWidth << endl;
  points << xWidth << " " << yWidth << " " << -zWidth << endl;
  points << -xWidth << " " << yWidth << " " << -zWidth << endl;
  points << -xWidth << " " << -yWidth << " " << -zWidth << endl;
  points << xWidth << " " << -yWidth << " " << zWidth << endl;
  points << xWidth << " " << yWidth << " " << zWidth << endl;
  points << -xWidth << " " << yWidth << " " << zWidth << endl;
  points << -xWidth << " " << -yWidth << " " << zWidth;

  // ladder4 (ladder definition for layer#4)
  Mpdshape* ladder4 = new Mpdshape(f, "sts01ladder4", "sts01", "BOX", "air",
				   points.str(), position.str());
  ladder4->SetSegment(1);

  // ladder4 positioning
  beta = 360./Nladders[3];
  beta_rad = beta*TMath::DegToRad();
  gamma = 90.;
  gamma_rad = gamma*TMath::DegToRad();
  alpha = 90.;

  ipos = 0;
  Radius = radiusOut[3]+0.5*ladderThick;
  for (Int_t i = 0; i < Nladders[3]/2; i++) {
    x = Radius * TMath::Cos(gamma_rad+2.*beta_rad*i);
    y = Radius * TMath::Sin(gamma_rad+2.*beta_rad*i);
    points.str(""); position.str(""); rotation.str("");
    points << xWidth << " " << -yWidth << " " << -zWidth << endl;
    points << xWidth << " " << yWidth << " " << -zWidth << endl;
    points << -xWidth << " " << yWidth << " " << -zWidth << endl;
    points << -xWidth << " " << -yWidth << " " << -zWidth << endl;
    points << xWidth << " " << -yWidth << " " << zWidth << endl;
    points << xWidth << " " << yWidth << " " << zWidth << endl;
    points << -xWidth << " " << yWidth << " " << zWidth << endl;
    points << -xWidth << " " << -yWidth << " " << zWidth;

    phis[ipos] = TMath::ATan2(y,x);
    if (phis[ipos] < 0) phis[ipos] += TMath::TwoPi();
    ladder4 = new Mpdshape(f, "sts01ladder4", "sts01", "BOX", "air", "", "", "");
    lads[ipos++] = ladder4;

    ladder4->SetPosition(x,y,0.);
    ladder4->SetRotation(alpha+(gamma+2.*beta*i),0.,180.);
    ladder4->SetPoints(points.str());
    //ladder4->DumpWithIncrement();
  }

  Radius = radiusIn[3]-0.5*ladderThick;
  for (Int_t i = 0; i < Nladders[3]/2; i++) {

    x = Radius * TMath::Cos(gamma_rad+beta_rad+2.*beta_rad*i);
    y = Radius * TMath::Sin(gamma_rad+beta_rad+2.*beta_rad*i);

    points.str(""); position.str(""); rotation.str("");
    points << xWidth << " " << -yWidth << " " << -zWidth << endl;
    points << xWidth << " " << yWidth << " " << -zWidth << endl;
    points << -xWidth << " " << yWidth << " " << -zWidth << endl;
    points << -xWidth << " " << -yWidth << " " << -zWidth << endl;
    points << xWidth << " " << -yWidth << " " << zWidth << endl;
    points << xWidth << " " << yWidth << " " << zWidth << endl;
    points << -xWidth << " " << yWidth << " " << zWidth << endl;
    points << -xWidth << " " << -yWidth << " " << zWidth;

    phis[ipos] = TMath::ATan2(y,x);
    if (phis[ipos] < 0) phis[ipos] += TMath::TwoPi();
    ladder4 = new Mpdshape(f, "sts01ladder4", "sts01", "BOX", "air", "", "", "");
    lads[ipos++] = ladder4;

    ladder4->SetPosition(x,y,0.);
    ladder4->SetRotation(alpha+(gamma+beta+2.*beta*i),0.,180.);
    ladder4->SetPoints(points.str());
    //ladder4->DumpWithIncrement();
  }
  // Sort ladders in Phi
  TMath::Sort(Nladders[3],phis,inds,kFALSE);
  for (Int_t i = 0; i < Nladders[3]; ++i) {
    lads[inds[i]]->SetSegment(i+1);
    lads[inds[i]]->DumpToFile();
  }

  // one sector 14 of ladder4 (sector 62*62)
  xWidth = 0.5*sensor_h; 
  yWidth = 0.5*sensorThick; 
  zWidth = 0.5*sensor_l1;
  
  points.str(""); position.str(""); rotation.str("");
  points << xWidth << " " << -yWidth << " " << -zWidth << endl;
  points << xWidth << " " << yWidth << " " << -zWidth << endl;
  points << -xWidth << " " << yWidth << " " << -zWidth << endl;
  points << -xWidth << " " << -yWidth << " " << -zWidth << endl;  
  points << xWidth << " " << -yWidth << " " << zWidth << endl;
  points << xWidth << " " << yWidth << " " << zWidth << endl;
  points << -xWidth << " " << yWidth << " " << zWidth << endl;
  points << -xWidth << " " << -yWidth << " " << zWidth;
  
  // sector 14 definition
  Mpdshape* sector14 = new Mpdshape(f, "sts01sector14", "sts01ladder4", 
				    "BOX", "silicon", points.str(), position.str());
  sector14->SetSegment(1);
  sector14->SetMotherSegment(1);
  ipos = 0;
  
  // sectors 14 positioning into 4-th layer  

  for (Int_t j = 0; j < nSec1[3]/2; j++) {    	      
    
     y = 4.7-0.8*j; 
     z = (-1.+0.5*sensor_l1) + j*(sensor_l1-delta);
	 
	sry[j] = y-0.5*ladderThick;
	crz[j] = z+zWidth;

    points.str(""); position.str(""); rotation.str("");
    points << xWidth << " " << -yWidth << " " << -zWidth << endl;
    points << xWidth << " " << yWidth << " " << -zWidth << endl;
    points << -xWidth << " " << yWidth << " " << -zWidth << endl;
    points << -xWidth << " " << -yWidth << " " << -zWidth << endl;	
    points << xWidth << " " << -yWidth << " " << zWidth << endl;
    points << xWidth << " " << yWidth << " " << zWidth << endl;
    points << -xWidth << " " << yWidth << " " << zWidth << endl;
    points << -xWidth << " " << -yWidth << " " << zWidth;
    
    zpos[ipos] = z;
    sector14 = new Mpdshape(f, "sts01sector14", "sts01ladder4", "BOX", "silicon", "", "");
    sector14->SetMotherSegment(1);
    sens[ipos++] = sector14;

    sector14->SetPosition(0.,y-0.5*ladderThick,z);
    sector14->SetPoints(points.str());
    //sector14->DumpWithIncrement();        	 
  }  

  for (Int_t j = 0; j < nSec1[3]/2; j++) {    	      
    
     y = 3.9-0.8*j; 
     z = (1.-0.5*sensor_l1) - j*(sensor_l1-delta);
	   
      	    sly[j] = y-0.5*ladderThick;
            clz[j] = z-zWidth;

    points.str(""); position.str(""); rotation.str("");
    points << xWidth << " " << -yWidth << " " << -zWidth << endl;
    points << xWidth << " " << yWidth << " " << -zWidth << endl;
    points << -xWidth << " " << yWidth << " " << -zWidth << endl;
    points << -xWidth << " " << -yWidth << " " << -zWidth << endl;	
    points << xWidth << " " << -yWidth << " " << zWidth << endl;
    points << xWidth << " " << yWidth << " " << zWidth << endl;
    points << -xWidth << " " << yWidth << " " << zWidth << endl;
    points << -xWidth << " " << -yWidth << " " << zWidth;
    
    zpos[ipos] = z;
    sector14 = new Mpdshape(f, "sts01sector14", "sts01ladder4", "BOX", "silicon", "", "");
    sector14->SetMotherSegment(1);
    sens[ipos++] = sector14;

    sector14->SetPosition(0.,y-0.5*ladderThick,z);
    sector14->SetPoints(points.str());
    //sector14->DumpWithIncrement();        	 
  }  

  // one sector 24 of ladder4 (sector 62*124)
  xWidth = 0.5*sensor_h; 
  yWidth = 0.5*sensorThick; 
  zWidth = 0.5*sensor_l2;
  
  points.str(""); position.str(""); rotation.str("");
  points << xWidth << " " << -yWidth << " " << -zWidth << endl;
  points << xWidth << " " << yWidth << " " << -zWidth << endl;
  points << -xWidth << " " << yWidth << " " << -zWidth << endl;
  points << -xWidth << " " << -yWidth << " " << -zWidth << endl;  
  points << xWidth << " " << -yWidth << " " << zWidth << endl;
  points << xWidth << " " << yWidth << " " << zWidth << endl;
  points << -xWidth << " " << yWidth << " " << zWidth << endl;
  points << -xWidth << " " << -yWidth << " " << zWidth;
  
  // sector 24 definition
  Mpdshape* sector24 = new Mpdshape(f, "sts01sector24", "sts01ladder4", 
				    "BOX", "silicon", points.str(), position.str());
  sector24->SetSegment(1);
  sector24->SetMotherSegment(1);

  // sectors 24 positioning into 4-th layer  

  for (Int_t j = 0; j < nSec2[3]/2; j++) {    	      
    
     y = 4.7-0.8*(j+nSec1[3]/2); 
     z = (-1.+0.5*sensor_l2) + j*(sensor_l2-delta) + nSec1[3]/2*(sensor_l1-delta);

	    sry[j+nSec1[3]/2] = y-0.5*ladderThick;
            crz[j+nSec1[3]/2] = z+zWidth;

    points.str(""); position.str(""); rotation.str("");
    points << xWidth << " " << -yWidth << " " << -zWidth << endl;
    points << xWidth << " " << yWidth << " " << -zWidth << endl;
    points << -xWidth << " " << yWidth << " " << -zWidth << endl;
    points << -xWidth << " " << -yWidth << " " << -zWidth << endl;	
    points << xWidth << " " << -yWidth << " " << zWidth << endl;
    points << xWidth << " " << yWidth << " " << zWidth << endl;
    points << -xWidth << " " << yWidth << " " << zWidth << endl;
    points << -xWidth << " " << -yWidth << " " << zWidth;
    
    zpos[ipos] = z;
    sector24 = new Mpdshape(f, "sts01sector24", "sts01ladder4", "BOX", "silicon", "", "");
    sector24->SetMotherSegment(1);
    sens[ipos++] = sector24;

    sector24->SetPosition(0.,y-0.5*ladderThick,z);
    sector24->SetPoints(points.str());
    //sector24->DumpWithIncrement();        	 
  }  

  for (Int_t j = 0; j < nSec2[3]/2; j++) {    	      
    
     y = 3.9-0.8*(j+nSec1[3]/2); 
     z = (1.-0.5*sensor_l2) - j*(sensor_l2-delta) - nSec1[3]/2*(sensor_l1-delta);

	    sly[j+nSec1[3]/2] = y-0.5*ladderThick;
            clz[j+nSec1[3]/2] = z-zWidth;
	  
    points.str(""); position.str(""); rotation.str("");
    points << xWidth << " " << -yWidth << " " << -zWidth << endl;
    points << xWidth << " " << yWidth << " " << -zWidth << endl;
    points << -xWidth << " " << yWidth << " " << -zWidth << endl;
    points << -xWidth << " " << -yWidth << " " << -zWidth << endl;	
    points << xWidth << " " << -yWidth << " " << zWidth << endl;
    points << xWidth << " " << yWidth << " " << zWidth << endl;
    points << -xWidth << " " << yWidth << " " << zWidth << endl;
    points << -xWidth << " " << -yWidth << " " << zWidth;
    
    zpos[ipos] = z;
    sector24 = new Mpdshape(f, "sts01sector24", "sts01ladder4", "BOX", "silicon", "", "");
    sector24->SetMotherSegment(1);
    sens[ipos++] = sector24;

    sector24->SetPosition(0.,y-0.5*ladderThick,z);
    sector24->SetPoints(points.str());
    //sector24->DumpWithIncrement();        	 
  }  

  // one sector 34 of ladder4 (sector 62*186)

  xWidth = 0.5*sensor_h; 
  yWidth = 0.5*sensorThick; 
  zWidth = 0.5*sensor_l3;
  
  points.str(""); position.str(""); rotation.str("");
  points << xWidth << " " << -yWidth << " " << -zWidth << endl;
  points << xWidth << " " << yWidth << " " << -zWidth << endl;
  points << -xWidth << " " << yWidth << " " << -zWidth << endl;
  points << -xWidth << " " << -yWidth << " " << -zWidth << endl;  
  points << xWidth << " " << -yWidth << " " << zWidth << endl;
  points << xWidth << " " << yWidth << " " << zWidth << endl;
  points << -xWidth << " " << yWidth << " " << zWidth << endl;
  points << -xWidth << " " << -yWidth << " " << zWidth;
  
  // sector 34 definition
  Mpdshape* sector34 = new Mpdshape(f, "sts01sector34", "sts01ladder4", 
				    "BOX", "silicon", points.str(), position.str());
  sector34->SetSegment(1);
  sector34->SetMotherSegment(1);
 
  // sectors 34 positioning into 4-th layer  

  for (Int_t j = 0; j < nSec3[3]/2; j++) {    	      
    
     y = 4.7-0.8*(j+nSec1[3]/2+nSec2[3]/2); 
     z = (-1.+0.5*sensor_l3) + j*(sensor_l3-delta) + nSec1[3]/2*(sensor_l1-delta) +nSec2[3]/2*(sensor_l2-delta);

	    sry[j+nSec1[3]/2+nSec2[3]/2] = y-0.5*ladderThick;
            crz[j+nSec1[3]/2+nSec2[3]/2] = z+zWidth;
	 
    points.str(""); position.str(""); rotation.str("");
    points << xWidth << " " << -yWidth << " " << -zWidth << endl;
    points << xWidth << " " << yWidth << " " << -zWidth << endl;
    points << -xWidth << " " << yWidth << " " << -zWidth << endl;
    points << -xWidth << " " << -yWidth << " " << -zWidth << endl;	
    points << xWidth << " " << -yWidth << " " << zWidth << endl;
    points << xWidth << " " << yWidth << " " << zWidth << endl;
    points << -xWidth << " " << yWidth << " " << zWidth << endl;
    points << -xWidth << " " << -yWidth << " " << zWidth;
        
    zpos[ipos] = z;
    sector34 = new Mpdshape(f, "sts01sector34", "sts01ladder4", "BOX", "silicon", "", "");
    sector34->SetMotherSegment(1);
    sens[ipos++] = sector34;

    sector34->SetPosition(0.,y-0.5*ladderThick,z);
    sector34->SetPoints(points.str());
    //sector34->DumpWithIncrement();        	 
  }  
 
  for (Int_t j = 0; j < nSec3[3]/2; j++) {    	      
    
     y = 3.9-0.8*(j+nSec1[3]/2+nSec2[3]/2); 
     z = (1.-0.5*sensor_l3) - j*(sensor_l3-delta) - nSec1[3]/2*(sensor_l1-delta) - nSec2[3]/2*(sensor_l2-delta);

	    sly[j+nSec1[3]/2+nSec2[3]/2] = y-0.5*ladderThick;
            clz[j+nSec1[3]/2+nSec2[3]/2] = z-zWidth;
	
    points.str(""); position.str(""); rotation.str("");
    points << xWidth << " " << -yWidth << " " << -zWidth << endl;
    points << xWidth << " " << yWidth << " " << -zWidth << endl;
    points << -xWidth << " " << yWidth << " " << -zWidth << endl;
    points << -xWidth << " " << -yWidth << " " << -zWidth << endl;	
    points << xWidth << " " << -yWidth << " " << zWidth << endl;
    points << xWidth << " " << yWidth << " " << zWidth << endl;
    points << -xWidth << " " << yWidth << " " << zWidth << endl;
    points << -xWidth << " " << -yWidth << " " << zWidth;
        
    zpos[ipos] = z;
    sector34 = new Mpdshape(f, "sts01sector34", "sts01ladder4", "BOX", "silicon", "", "");
    sector34->SetMotherSegment(1);
    sens[ipos++] = sector34;

    sector34->SetPosition(0.,y-0.5*ladderThick,z);
    sector34->SetPoints(points.str());
    //sector34->DumpWithIncrement();        	 
  } 

  // Sort sectors in Z
  segmNo[0] = segmNo[1] = segmNo[2] = 0;
  TMath::Sort(ipos,zpos,inds1,kFALSE);
  for (Int_t i = 0; i < ipos; ++i) {
    Mpdshape *shape = sens[inds1[i]];
    TString vol(shape->GetVolumeName());
    if (vol.Contains("14")) indx = 0;
    else if (vol.Contains("24")) indx = 1;
    else if (vol.Contains("34")) indx = 2;
    ++segmNo[indx];
    shape->SetSegment(segmNo[indx]);
    shape->DumpToFile();
  }
  
   /*
// cables ccccccccccccccccccccccccccccccccccccccccccccccccccccccccc
 for (Int_t j = 0; j < Nsensor - 1; j++) {   // 4 
  
  Double_t xWidth = 0.5*sensor_h; // always 31mm
  Double_t yWidth = 0.5*cableThick; // always 0.058 mm
 
// Start with "right" side
  Double_t zWidth = (crz[4]-crz[j])/2.;
  
  points.str(""); position.str(""); rotation.str("");
  points << xWidth << " " << -yWidth << " " << -zWidth << endl;
  points << xWidth << " " << yWidth << " " << -zWidth << endl;
  points << -xWidth << " " << yWidth << " " << -zWidth << endl;
  points << -xWidth << " " << -yWidth << " " << -zWidth << endl;  
  points << xWidth << " " << -yWidth << " " << zWidth << endl;
  points << xWidth << " " << yWidth << " " << zWidth << endl;
  points << -xWidth << " " << yWidth << " " << zWidth << endl;
  points << -xWidth << " " << -yWidth << " " << zWidth;
 
  cablename.str("");	
  cablename << "sts01ladder04cable0" << j+1;
	cout <<cablename.str() << endl;
	cout << crz[j] << endl;
    Mpdshape* cable = new Mpdshape(f, cablename.str(), "sts01ladder4", 
				     "BOX", "silicon_dead", points.str(), position.str());
  cable->SetSegment(1);
  cable->SetMotherSegment(1);
  
  cable->SetPosition(0.,sry[j]+cable_yshift,crz[j]+zWidth);
  cable->SetPoints(points.str());
  cable->DumpWithIncrement();        	
  
  cable->SetPosition(0.,sry[j]-cable_yshift,crz[j]+zWidth);
  cable->SetPoints(points.str());
  cable->DumpWithIncrement(); 	
  
// Left side
  Double_t zWidth = (clz[j]-clz[4])/2.;
  
  points.str(""); position.str(""); rotation.str("");
  points << xWidth << " " << -yWidth << " " << -zWidth << endl;
  points << xWidth << " " << yWidth << " " << -zWidth << endl;
  points << -xWidth << " " << yWidth << " " << -zWidth << endl;
  points << -xWidth << " " << -yWidth << " " << -zWidth << endl;  
  points << xWidth << " " << -yWidth << " " << zWidth << endl;
  points << xWidth << " " << yWidth << " " << zWidth << endl;
  points << -xWidth << " " << yWidth << " " << zWidth << endl;
  points << -xWidth << " " << -yWidth << " " << zWidth;

  cablename.str("");	
  cablename << "sts01ladder04cable0" << j+5;
	cout <<cablename.str() << endl;
	cout << clz[j] << endl;
    Mpdshape* cable = new Mpdshape(f, cablename.str(), "sts01ladder4", 
				     "BOX", "silicon_dead", points.str(), position.str());
  cable->SetSegment(1);
  cable->SetMotherSegment(1);
  
  cable->SetPosition(0.,sly[j]+cable_yshift,clz[j]-zWidth);
  cable->SetPoints(points.str());
  cable->DumpWithIncrement();        	
  
  cable->SetPosition(0.,sly[j]-cable_yshift,clz[j]-zWidth);
  cable->SetPoints(points.str());
  cable->DumpWithIncrement(); 	
} 
   */
 
   f->close(); 
}

  

