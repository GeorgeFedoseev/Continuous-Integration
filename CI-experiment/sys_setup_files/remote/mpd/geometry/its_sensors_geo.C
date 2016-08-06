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

void its_sensors_geo()
{
  // 29.02.2012   Author V.Kondratiev
  // Sensor's structure of STS
  // 18-aug-2012 A.Zinchenko - change ladder and sensor numeration 
  //                           (to have neighbours with sequential numbers)

  const Int_t Nlayer = 4; // Number of layers in barrel
  Double_t radiusPipe = 0.5*80.; //mm// Radius of pipe
  Double_t outerRadius =0.5*500.; //mm// Radius of pipe
  // silicon elements of barrel
  Double_t sensor_l = 62.0; //mm// Length of sensor
  Double_t sensor_h = 62.0; //mm// Height of sensor
  Double_t sensorThick = 0.3; //mm// Thickness of sensor

  Double_t deltaSensor = 0.8; //mm// Distance between modules in ladder
  Double_t delta = 2.0; //mm// Overlaping of modules
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

  //====== end declaration =======================================

  // output file
  const char* filename = "its_sensors.geo";
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

  // Layer 111111111111111111111111111111111111111111111111111111111111111

  // Ladder of 1-st layer (ladder1)
  Double_t xWidth = 0.5*(sensor_l + stock);
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
    Double_t x = Radius * TMath::Cos(gamma_rad+2.*beta_rad*i);
    Double_t y = Radius * TMath::Sin(gamma_rad+2.*beta_rad*i);
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
    ladder1 = new Mpdshape(f, "sts01ladder1", "sts01", "BOX", "air",
			   "", "", "");
    lads[ipos++] = ladder1;

    ladder1->SetPosition(x,y,0.);
    //ladder1->SetRotation(alpha+(gamma+2.*beta*i),0.,0.);
    ladder1->SetRotation(alpha+(gamma+2.*beta*i),0.,180.);
    ladder1->SetPoints(points.str());
    //ladder1->DumpWithIncrement();
  }

  Radius = radiusIn[0]-0.5*ladderThick;
  for (Int_t i = 0; i < Nladders[0]/2; i++) {

    Double_t x = Radius * TMath::Cos(gamma_rad+beta_rad+2.*beta_rad*i);
    Double_t y = Radius * TMath::Sin(gamma_rad+beta_rad+2.*beta_rad*i);

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
    ladder1 = new Mpdshape(f, "sts01ladder1", "sts01", "BOX", "air",
			   "", "", "");
    lads[ipos++] = ladder1;

    ladder1->SetPosition(x,y,0.);
    //ladder1->SetRotation(alpha+(gamma+beta+2.*beta*i),0.,0.);
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
  
// one sensor of ladder1 (detector1)
  xWidth = 0.5*sensor_l; 
  yWidth = 0.5*sensorThick; 
  zWidth = 0.5*sensor_h;
  
  points.str(""); position.str(""); rotation.str("");
  points << xWidth << " " << -yWidth << " " << -zWidth << endl;
  points << xWidth << " " << yWidth << " " << -zWidth << endl;
  points << -xWidth << " " << yWidth << " " << -zWidth << endl;
  points << -xWidth << " " << -yWidth << " " << -zWidth << endl;  
  points << xWidth << " " << -yWidth << " " << zWidth << endl;
  points << xWidth << " " << yWidth << " " << zWidth << endl;
  points << -xWidth << " " << yWidth << " " << zWidth << endl;
  points << -xWidth << " " << -yWidth << " " << zWidth;
  
  // sensor1 definition
  //Mpdshape* sensor1 = new Mpdshape(f, "sts01sensor1", "sts01ladder1", 
  Mpdshape* sensor1 = new Mpdshape(f, "sts01sector11", "sts01ladder1", 
				   "BOX", "silicon", points.str(), position.str());
  sensor1->SetSegment(1);
  sensor1->SetMotherSegment(1);
  
  Double_t* zpos = new Double_t [Nelements[3]];
  Mpdshape** sens = new Mpdshape* [Nelements[3]];
  Int_t* inds1 = new Int_t [Nelements[3]];
  ipos = 0;

  // sensors positioning into 1-st layer  
  
  for (Int_t j = 0; j < Nelements[0]/2.; j++) {    	      
    
    Double_t y = 0.0, z = 0.0;
    if(j == 0) {y = 4.7; z = (-1.+0.5*sensor_h) + j*sensor_h-j*delta;}
    if(j == 1) {y = 3.9; z = (-1.+0.5*sensor_h) + j*sensor_h-j*delta;}
    if(j == 2) {y = 3.1; z = (-1.+0.5*sensor_h) + j*sensor_h-j*delta;}
    if(j == 3) {y = 3.1; z = (-1.+0.5*sensor_h) + j*sensor_h-(j-1)*delta;}
    if(j == 4) {y = 2.3; z = (-1.+0.5*sensor_h) + j*sensor_h-(j-1)*delta;} 
    if(j == 5) {y = 2.3; z = (-1.+0.5*sensor_h) + j*sensor_h-(j-2)*delta;}
    if(j == 6) {y = 1.5; z = (-1.+0.5*sensor_h) + j*sensor_h-(j-2)*delta;}
    if(j == 7) {y = 1.5; z = (-1.+0.5*sensor_h) + j*sensor_h-(j-3)*delta;}
    if(j == 8) {y = 1.5; z = (-1.+0.5*sensor_h) + j*sensor_h-(j-4)*delta;}
  
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
    //sensor1 = new Mpdshape(f, "sts01sensor1", "sts01ladder1", "BOX", 
    sensor1 = new Mpdshape(f, "sts01sector11", "sts01ladder1", "BOX", 
			   "silicon", "", "");
    sensor1->SetMotherSegment(1);
    sens[ipos++] = sensor1;
    
    sensor1->SetPosition(0.,y-0.5*ladderThick,z);
    sensor1->SetPoints(points.str());
    //sensor1->DumpWithIncrement();        	 
  }  
 
  for (Int_t j = 0; j < Nelements[0]/2.; j++) {    	      
    
    Double_t y = 0.0, z = 0.0;
    if(j == 0) {y = 3.9; z = (1.-0.5*sensor_h) - j*sensor_h+j*delta;}
    if(j == 1) {y = 3.1; z = (1.-0.5*sensor_h) - j*sensor_h+j*delta;}
    if(j == 2) {y = 2.3; z = (1.-0.5*sensor_h) - j*sensor_h+j*delta;}
    if(j == 3) {y = 2.3; z = (1.-0.5*sensor_h) - j*sensor_h+(j-1)*delta;}
    if(j == 4) {y = 1.5; z = (1.-0.5*sensor_h) - j*sensor_h+(j-1)*delta;} 
    if(j == 5) {y = 1.5; z = (1.-0.5*sensor_h) - j*sensor_h+(j-2)*delta;}
    if(j == 6) {y = 0.7; z = (1.-0.5*sensor_h) - j*sensor_h+(j-2)*delta;}
    if(j == 7) {y = 0.7; z = (1.-0.5*sensor_h) - j*sensor_h+(j-3)*delta;}
    if(j == 8) {y = 0.7; z = (1.-0.5*sensor_h) - j*sensor_h+(j-4)*delta;}   

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
    //sensor1 = new Mpdshape(f, "sts01sensor1", "sts01ladder1", "BOX",
    sensor1 = new Mpdshape(f, "sts01sector11", "sts01ladder1", "BOX",
                           "silicon", "", "");
    sensor1->SetMotherSegment(1);
    sens[ipos++] = sensor1;

    sensor1->SetPosition(0.,y-0.5*ladderThick,z);
    sensor1->SetPoints(points.str());
    //sensor1->DumpWithIncrement();        	 
  }
  // Sort sensors in Z
  TMath::Sort(Nelements[0],zpos,inds1,kFALSE);
  for (Int_t i = 0; i < Nelements[0]; ++i) {
    sens[inds1[i]]->SetSegment(i+1);
    sens[inds1[i]]->DumpToFile();
  }

// Layer 22222222222222222222222222222222222222222222222222222222

  // Ladder of 2-nd layer (ladder2)
  xWidth = 0.5*(sensor_l + stock);
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

  Radius = radiusOut[1]+0.5*ladderThick;

  ipos = 0;
  for (Int_t i = 0; i < Nladders[1]/2; i++) {

    Double_t x = Radius * TMath::Cos(gamma_rad+2.*beta_rad*i);
    Double_t y = Radius * TMath::Sin(gamma_rad+2.*beta_rad*i);

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
    ladder2 = new Mpdshape(f, "sts01ladder2", "sts01", "BOX", "air",
			   "", "", "");
    lads[ipos++] = ladder2;

    ladder2->SetPosition(x,y,0.);
    //ladder2->SetRotation(alpha+(gamma+2.*beta*i),0.,0.);
    ladder2->SetRotation(alpha+(gamma+2.*beta*i),0.,180.);
    ladder2->SetPoints(points.str());
    //ladder2->DumpWithIncrement();
  }

  Radius = radiusIn[1]-0.5*ladderThick;
  for (Int_t i = 0; i < Nladders[1]/2; i++) {

    Double_t x = Radius * TMath::Cos(gamma_rad+beta_rad+2.*beta_rad*i);
    Double_t y = Radius * TMath::Sin(gamma_rad+beta_rad+2.*beta_rad*i);

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
    ladder2 = new Mpdshape(f, "sts01ladder2", "sts01", "BOX", "air",
			   "", "", "");
    lads[ipos++] = ladder2;

    ladder2->SetPosition(x,y,0.);
    //ladder2->SetRotation(alpha+(gamma+beta+2.*beta*i),0.,0.);
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

// one sensor of ladder2 (detector2)
  xWidth = 0.5*sensor_l; 
  yWidth = 0.5*sensorThick; 
  zWidth = 0.5*sensor_h;
  
  points.str(""); position.str(""); rotation.str("");
  points << xWidth << " " << -yWidth << " " << -zWidth << endl;
  points << xWidth << " " << yWidth << " " << -zWidth << endl;
  points << -xWidth << " " << yWidth << " " << -zWidth << endl;
  points << -xWidth << " " << -yWidth << " " << -zWidth << endl;  
  points << xWidth << " " << -yWidth << " " << zWidth << endl;
  points << xWidth << " " << yWidth << " " << zWidth << endl;
  points << -xWidth << " " << yWidth << " " << zWidth << endl;
  points << -xWidth << " " << -yWidth << " " << zWidth;
  
  // sensor2 definition
  // Mpdshape* sensor2 = new Mpdshape(f, "sts01sensor2", "sts01ladder2",   
  Mpdshape* sensor2 = new Mpdshape(f, "sts01sector12", "sts01ladder2", 
				     "BOX", "silicon", points.str(), position.str());
  sensor2->SetSegment(1);
  sensor2->SetMotherSegment(1);

  ipos = 0;

  // sensors positioning into 2-nd layer  
 
  for (Int_t j = 0; j < Nelements[1]/2.; j++) {    	      
    
    Double_t y = 0.0, z = 0.0;
    if(j == 0) {y = 4.7; z = (-1.+0.5*sensor_h) + j*sensor_h-j*delta;}
    if(j == 1) {y = 3.9; z = (-1.+0.5*sensor_h) + j*sensor_h-j*delta;}
    if(j == 2) {y = 3.1; z = (-1.+0.5*sensor_h) + j*sensor_h-j*delta;}
    if(j == 3) {y = 3.1; z = (-1.+0.5*sensor_h) + j*sensor_h-(j-1)*delta;}
    if(j == 4) {y = 2.3; z = (-1.+0.5*sensor_h) + j*sensor_h-(j-1)*delta;} 
    if(j == 5) {y = 2.3; z = (-1.+0.5*sensor_h) + j*sensor_h-(j-2)*delta;}
    if(j == 6) {y = 2.3; z = (-1.+0.5*sensor_h) + j*sensor_h-(j-3)*delta;}
    if(j == 7) {y = 1.5; z = (-1.+0.5*sensor_h) + j*sensor_h-(j-3)*delta;}
    if(j == 8) {y = 1.5; z = (-1.+0.5*sensor_h) + j*sensor_h-(j-4)*delta;}
    if(j == 9) {y = 1.5; z = (-1.+0.5*sensor_h) + j*sensor_h-(j-5)*delta;}
  
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
    sensor2 = new Mpdshape(f, "sts01sector12", "sts01ladder2", "BOX", 
			   "silicon", "", "");
    sensor2->SetMotherSegment(1);
    sens[ipos++] = sensor2;

    sensor2->SetPosition(0.,y-0.5*ladderThick,z);
    sensor2->SetPoints(points.str());
    //sensor2->DumpWithIncrement();        	 
  }  
 
  for (Int_t j = 0; j < Nelements[1]/2.; j++) {    	      
    
    Double_t y = 0.0, z = 0.0;
    if(j == 0) {y = 3.9; z = (1.-0.5*sensor_h) - j*sensor_h+j*delta;}
    if(j == 1) {y = 3.1; z = (1.-0.5*sensor_h) - j*sensor_h+j*delta;}
    if(j == 2) {y = 2.3; z = (1.-0.5*sensor_h) - j*sensor_h+j*delta;}
    if(j == 3) {y = 2.3; z = (1.-0.5*sensor_h) - j*sensor_h+(j-1)*delta;}
    if(j == 4) {y = 1.5; z = (1.-0.5*sensor_h) - j*sensor_h+(j-1)*delta;} 
    if(j == 5) {y = 1.5; z = (1.-0.5*sensor_h) - j*sensor_h+(j-2)*delta;}
    if(j == 6) {y = 1.5; z = (1.-0.5*sensor_h) - j*sensor_h+(j-3)*delta;}
    if(j == 7) {y = 0.7; z = (1.-0.5*sensor_h) - j*sensor_h+(j-3)*delta;}
    if(j == 8) {y = 0.7; z = (1.-0.5*sensor_h) - j*sensor_h+(j-4)*delta;}
    if(j == 9) {y = 0.7; z = (1.-0.5*sensor_h) - j*sensor_h+(j-5)*delta;}   

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
    sensor2 = new Mpdshape(f, "sts01sector12", "sts01ladder2", "BOX",
                           "silicon", "", "");
    sensor2->SetMotherSegment(1);
    sens[ipos++] = sensor2;
    
    sensor2->SetPosition(0.,y-0.5*ladderThick,z);
    sensor2->SetPoints(points.str());
    //sensor2->DumpWithIncrement();        	 
  }
  // Sort sensors in Z
  TMath::Sort(Nelements[1],zpos,inds1,kFALSE);
  for (Int_t i = 0; i < Nelements[1]; ++i) {
    sens[inds1[i]]->SetSegment(i+1);
    sens[inds1[i]]->DumpToFile();
  }

 // Layer 3333333333333333333333333333333333333333333333333333333333

  //  Ladder of 3-rd layer (ladder3)

  xWidth = 0.5*(sensor_l + stock);
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

  ipos = 0;

  // ladder3 positioning
  beta = 360./Nladders[2];
  beta_rad = beta*TMath::DegToRad();
  gamma = 90.;
  gamma_rad = gamma*TMath::DegToRad();
  alpha = 90.;

  Radius = radiusOut[2]+0.5*ladderThick;
  for (Int_t i = 0; i < Nladders[2]/2; i++) {

    Double_t x = Radius * TMath::Cos(gamma_rad+2.*beta_rad*i);
    Double_t y = Radius * TMath::Sin(gamma_rad+2.*beta_rad*i);

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
    ladder3 = new Mpdshape(f, "sts01ladder3", "sts01", "BOX", "air",
			   "", "", "");
    lads[ipos++] = ladder3;

    ladder3->SetPosition(x,y,0.);
    //ladder3->SetRotation(alpha+(gamma+2.*beta*i),0.,0.);
    ladder3->SetRotation(alpha+(gamma+2.*beta*i),0.,180.);
    ladder3->SetPoints(points.str());
    //ladder3->DumpWithIncrement();
  }

  Radius = radiusIn[2]-0.5*ladderThick;
  for (Int_t i = 0; i < Nladders[2]/2; i++) {

    Double_t x = Radius * TMath::Cos(gamma_rad+beta_rad+2.*beta_rad*i);
    Double_t y = Radius * TMath::Sin(gamma_rad+beta_rad+2.*beta_rad*i);

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
    ladder3 = new Mpdshape(f, "sts01ladder3", "sts01", "BOX", "air",
			   "", "", "");
    lads[ipos++] = ladder3;

    ladder3->SetPosition(x,y,0.);
    //ladder3->SetRotation(alpha+(gamma+beta+2.*beta*i),0.,0.);
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

  // one sensor of ladder3 (detector3)
  xWidth = 0.5*sensor_l; 
  yWidth = 0.5*sensorThick; 
  zWidth = 0.5*sensor_h;
  
  points.str(""); position.str(""); rotation.str("");
  points << xWidth << " " << -yWidth << " " << -zWidth << endl;
  points << xWidth << " " << yWidth << " " << -zWidth << endl;
  points << -xWidth << " " << yWidth << " " << -zWidth << endl;
  points << -xWidth << " " << -yWidth << " " << -zWidth << endl;  
  points << xWidth << " " << -yWidth << " " << zWidth << endl;
  points << xWidth << " " << yWidth << " " << zWidth << endl;
  points << -xWidth << " " << yWidth << " " << zWidth << endl;
  points << -xWidth << " " << -yWidth << " " << zWidth;
  
  // sensor3 definition
  //Mpdshape* sensor3 = new Mpdshape(f, "sts01sensor3", "sts01ladder3",  
  Mpdshape* sensor3 = new Mpdshape(f, "sts01sector13", "sts01ladder3", 
				     "BOX", "silicon", points.str(), position.str());
  sensor3->SetSegment(1);
  sensor3->SetMotherSegment(1);
  
  ipos = 0;

  // sensors positioning into 3-rd layer  
 
  for (Int_t j = 0; j < Nelements[2]/2.; j++) {    	      
    
    Double_t y = 0.0, z = 0.0;
    if(j == 0) {y = 4.7; z = (-1.+0.5*sensor_h) + j*sensor_h-j*delta;}
    if(j == 1) {y = 3.9; z = (-1.+0.5*sensor_h) + j*sensor_h-j*delta;}
    if(j == 2) {y = 3.9; z = (-1.+0.5*sensor_h) + j*sensor_h-(j-1)*delta;}
    if(j == 3) {y = 3.1; z = (-1.+0.5*sensor_h) + j*sensor_h-(j-1)*delta;}
    if(j == 4) {y = 3.1; z = (-1.+0.5*sensor_h) + j*sensor_h-(j-2)*delta;}
    if(j == 5) {y = 2.3; z = (-1.+0.5*sensor_h) + j*sensor_h-(j-2)*delta;} 
    if(j == 6) {y = 2.3; z = (-1.+0.5*sensor_h) + j*sensor_h-(j-3)*delta;}
    if(j == 7) {y = 2.3; z = (-1.+0.5*sensor_h) + j*sensor_h-(j-4)*delta;}
    if(j == 8) {y = 1.5; z = (-1.+0.5*sensor_h) + j*sensor_h-(j-4)*delta;}
    if(j == 9) {y = 1.5; z = (-1.+0.5*sensor_h) + j*sensor_h-(j-5)*delta;}
    if(j == 10) {y = 1.5; z = (-1.+0.5*sensor_h) + j*sensor_h-(j-6)*delta;}
  
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
    sensor3 = new Mpdshape(f, "sts01sector13", "sts01ladder3", "BOX", 
			   "silicon", "", "");
    sensor3->SetMotherSegment(1);
    sens[ipos++] = sensor3;

    sensor3->SetPosition(0.,y-0.5*ladderThick,z);
    sensor3->SetPoints(points.str());
    //sensor3->DumpWithIncrement();        	 
  }  
 
  for (Int_t j = 0; j < Nelements[2]/2.; j++) {    	      
    
    Double_t y = 0.0, z = 0.0;
    if(j == 0) {y = 3.9; z = (1.-0.5*sensor_h) - j*sensor_h+j*delta;}
    if(j == 1) {y = 3.1; z = (1.-0.5*sensor_h) - j*sensor_h+j*delta;}
    if(j == 2) {y = 3.1; z = (1.-0.5*sensor_h) - j*sensor_h+(j-1)*delta;}
    if(j == 3) {y = 2.3; z = (1.-0.5*sensor_h) - j*sensor_h+(j-1)*delta;}
    if(j == 4) {y = 2.3; z = (1.-0.5*sensor_h) - j*sensor_h+(j-2)*delta;}
    if(j == 5) {y = 1.5; z = (1.-0.5*sensor_h) - j*sensor_h+(j-2)*delta;} 
    if(j == 6) {y = 1.5; z = (1.-0.5*sensor_h) - j*sensor_h+(j-3)*delta;}
    if(j == 7) {y = 1.5; z = (1.-0.5*sensor_h) - j*sensor_h+(j-4)*delta;}
    if(j == 8) {y = 0.7; z = (1.-0.5*sensor_h) - j*sensor_h+(j-4)*delta;}
    if(j == 9) {y = 0.7; z = (1.-0.5*sensor_h) - j*sensor_h+(j-5)*delta;}
    if(j == 10) {y = 0.7; z = (1.-0.5*sensor_h) - j*sensor_h+(j-6)*delta;}   

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
    sensor3 = new Mpdshape(f, "sts01sector13", "sts01ladder3", "BOX",
                           "silicon", "", "");
    sensor3->SetMotherSegment(1);
    sens[ipos++] = sensor3;

    sensor3->SetPosition(0.,y-0.5*ladderThick,z);
    sensor3->SetPoints(points.str());
    //sensor3->DumpWithIncrement();        	 
  }

  // Sort sensors in Z
  TMath::Sort(Nelements[2],zpos,inds1,kFALSE);
  for (Int_t i = 0; i < Nelements[2]; ++i) {
    sens[inds1[i]]->SetSegment(i+1);
    sens[inds1[i]]->DumpToFile();
  }

  // Layer 4444444444444444444444444444444444444444444444444444444444444444444

  //  Ladder of 4-th layer (ladder4)

  xWidth = 0.5*(sensor_l + stock);
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

  ipos = 0;

  // ladder4 positioning
  beta = 360./Nladders[3];
  beta_rad = beta*TMath::DegToRad();
  gamma = 90.;
  gamma_rad = gamma*TMath::DegToRad();
  alpha = 90.;

  Radius = radiusOut[3]+0.5*ladderThick;
  for (Int_t i = 0; i < Nladders[3]/2; i++) {

    Double_t x = Radius * TMath::Cos(gamma_rad+2.*beta_rad*i);
    Double_t y = Radius * TMath::Sin(gamma_rad+2.*beta_rad*i);

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
    ladder4 = new Mpdshape(f, "sts01ladder4", "sts01", "BOX", "air",
			   "", "", "");
    lads[ipos++] = ladder4;

    ladder4->SetPosition(x,y,0.);
    //ladder4->SetRotation(alpha+(gamma+2.*beta*i),0.,0.);
    ladder4->SetRotation(alpha+(gamma+2.*beta*i),0.,180.);
    ladder4->SetPoints(points.str());
    //ladder4->DumpWithIncrement();
  }

  Radius = radiusIn[3]-0.5*ladderThick;
  for (Int_t i = 0; i < Nladders[3]/2; i++) {

    Double_t x = Radius * TMath::Cos(gamma_rad+beta_rad+2.*beta_rad*i);
    Double_t y = Radius * TMath::Sin(gamma_rad+beta_rad+2.*beta_rad*i);

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
    ladder4 = new Mpdshape(f, "sts01ladder4", "sts01", "BOX", "air",
			   "", "", "");
    lads[ipos++] = ladder4;

    ladder4->SetPosition(x,y,0.);
    //ladder4->SetRotation(alpha+(gamma+beta+2.*beta*i),0.,0.);
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

  // one sensor of ladder4 (detector4)
  xWidth = 0.5*sensor_l; 
  yWidth = 0.5*sensorThick; 
  zWidth = 0.5*sensor_h;
  
  points.str(""); position.str(""); rotation.str("");
  points << xWidth << " " << -yWidth << " " << -zWidth << endl;
  points << xWidth << " " << yWidth << " " << -zWidth << endl;
  points << -xWidth << " " << yWidth << " " << -zWidth << endl;
  points << -xWidth << " " << -yWidth << " " << -zWidth << endl;  
  points << xWidth << " " << -yWidth << " " << zWidth << endl;
  points << xWidth << " " << yWidth << " " << zWidth << endl;
  points << -xWidth << " " << yWidth << " " << zWidth << endl;
  points << -xWidth << " " << -yWidth << " " << zWidth;
  
  // sensor4 definition
  //Mpdshape* sensor4 = new Mpdshape(f, "sts01sensor4", "sts01ladder4", 
  Mpdshape* sensor4 = new Mpdshape(f, "sts01sector14", "sts01ladder4", 
				     "BOX", "silicon", points.str(), position.str());
  sensor4->SetSegment(1);
  sensor4->SetMotherSegment(1);
  
  ipos = 0;

  // sensors positioning into 4-th layer  
 
  for (Int_t j = 0; j < Nelements[3]/2.; j++) {    	      
    
    Double_t y = 0.0, z = 0.0;
    if(j == 0) {y = 4.7; z = (-1.+0.5*sensor_h) + j*sensor_h-j*delta;}
    if(j == 1) {y = 3.9; z = (-1.+0.5*sensor_h) + j*sensor_h-j*delta;}
    if(j == 2) {y = 3.9; z = (-1.+0.5*sensor_h) + j*sensor_h-(j-1)*delta;}
    if(j == 3) {y = 3.1; z = (-1.+0.5*sensor_h) + j*sensor_h-(j-1)*delta;}
    if(j == 4) {y = 3.1; z = (-1.+0.5*sensor_h) + j*sensor_h-(j-2)*delta;}
    if(j == 5) {y = 3.1; z = (-1.+0.5*sensor_h) + j*sensor_h-(j-3)*delta;}
    if(j == 6) {y = 2.3; z = (-1.+0.5*sensor_h) + j*sensor_h-(j-3)*delta;} 
    if(j == 7) {y = 2.3; z = (-1.+0.5*sensor_h) + j*sensor_h-(j-4)*delta;}
    if(j == 8) {y = 2.3; z = (-1.+0.5*sensor_h) + j*sensor_h-(j-5)*delta;}
    if(j == 9) {y = 1.5; z = (-1.+0.5*sensor_h) + j*sensor_h-(j-5)*delta;}
    if(j == 10) {y = 1.5; z = (-1.+0.5*sensor_h) + j*sensor_h-(j-6)*delta;}
    if(j == 11) {y = 1.5; z = (-1.+0.5*sensor_h) + j*sensor_h-(j-7)*delta;}
  
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
    sensor4 = new Mpdshape(f, "sts01sector14", "sts01ladder4", "BOX", 
			   "silicon", "", "");
    sensor4->SetMotherSegment(1);
    sens[ipos++] = sensor4;
    
    sensor4->SetPosition(0.,y-0.5*ladderThick,z);
    sensor4->SetPoints(points.str());
    //sensor4->DumpWithIncrement();        	 
  }  
 
  for (Int_t j = 0; j < Nelements[3]/2.; j++) {    	      
    
    Double_t y = 0.0, z = 0.0;
    if(j == 0) {y = 3.9; z = (1.-0.5*sensor_h) - j*sensor_h+j*delta;}
    if(j == 1) {y = 3.1; z = (1.-0.5*sensor_h) - j*sensor_h+j*delta;}
    if(j == 2) {y = 3.1; z = (1.-0.5*sensor_h) - j*sensor_h+(j-1)*delta;}
    if(j == 3) {y = 2.3; z = (1.-0.5*sensor_h) - j*sensor_h+(j-1)*delta;}
    if(j == 4) {y = 2.3; z = (1.-0.5*sensor_h) - j*sensor_h+(j-2)*delta;}
    if(j == 5) {y = 2.3; z = (1.-0.5*sensor_h) - j*sensor_h+(j-3)*delta;}
    if(j == 6) {y = 1.5; z = (1.-0.5*sensor_h) - j*sensor_h+(j-3)*delta;} 
    if(j == 7) {y = 1.5; z = (1.-0.5*sensor_h) - j*sensor_h+(j-4)*delta;}
    if(j == 8) {y = 1.5; z = (1.-0.5*sensor_h) - j*sensor_h+(j-5)*delta;}
    if(j == 9) {y = 0.7; z = (1.-0.5*sensor_h) - j*sensor_h+(j-5)*delta;}
    if(j == 10) {y = 0.7; z = (1.-0.5*sensor_h) - j*sensor_h+(j-6)*delta;}
    if(j == 11) {y = 0.7; z = (1.-0.5*sensor_h) - j*sensor_h+(j-7)*delta;}   

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
    sensor4 = new Mpdshape(f, "sts01sector14", "sts01ladder4", "BOX",
                           "silicon", "", "");
    sensor4->SetMotherSegment(1);
    sens[ipos++] = sensor4;

    sensor4->SetPosition(0.,y-0.5*ladderThick,z);
    sensor4->SetPoints(points.str());
    //sensor4->DumpWithIncrement();        	 
  }

  // Sort sensors in Z
  TMath::Sort(Nelements[3],zpos,inds1,kFALSE);
  for (Int_t i = 0; i < Nelements[3]; ++i) {
    sens[inds1[i]]->SetSegment(i+1);
    sens[inds1[i]]->DumpToFile();
  }

   f->close(); 
}

  

