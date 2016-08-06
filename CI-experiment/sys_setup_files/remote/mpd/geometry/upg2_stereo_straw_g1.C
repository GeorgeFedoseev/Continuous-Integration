#include "mpdshape.class.C"

//*************** global parameters ****************************************************************

const Double_t numLayers = 60; // Number of layers
const Double_t innerRadius = 250.0; // Layer inner radius, mm
const Double_t outerRadius = 1210.0; // Layer outer radius, mm
const Double_t initDist = 1550.0; // Distance from interacting point, mm

//**************** radial parameters ***************************************************************

const Double_t angleLayers = 0.596; // Angle between layers, degrees
const Double_t distLayers = 10; // Distance between layers, mm
const Double_t tubeRadius = 2.1; // Radius of the straw tube, mm
const Double_t gasRadius = 2.0; // Radius of the straw gas chamber, mm
const Double_t wireRadius = 0.01; // Radius of the straw wire, mm
const Double_t layerThickness = 10; // Thickness of the straw layer, mm
const Double_t distBetweenStraw = 1.0; // Distance between straws at inner radius, mm
const Int_t numStrawsPerLayer = floor(2*TMath::Pi()*innerRadius/(tubeRadius*2+distBetweenStraw));
const Double_t angleStraws = 360.0 / numStrawsPerLayer; // Angle between straws in layer, degrees

//***************** stereo parameters **************************************************************

const Double_t angleStereo = 7; // degrees
//const Double_t stereoLength = LineLength(angleStereo, TVector3(0,0,0), outerRadius, TVector3(0,innerRadius,0));
//const TVector3 stereoPositionR = StereoPosition(angleStereo, TVector3(0,0,0), outerRadius, TVector3(0,innerRadius,0));;
//const TVector3 stereoPositionL(-stereoPositionR.X(), stereoPositionR.Y(),0); 
//const TVector3 stereoEndR = StereoEnd(angleStereo, TVector3(0,0,0), outerRadius, TVector3(0,innerRadius,0));

// helper streams
std::ostringstream points, position, rotation;
points.setf(ios::showpoint); points.setf(ios::fixed); points << setprecision(6);
position.setf(ios::showpoint); position.setf(ios::fixed); rotation << setprecision(6);
rotation.setf(ios::showpoint); rotation.setf(ios::fixed); rotation << setprecision(6);

void upg2_stereo_straw_g1() {

ostringstream fname; 
fname << "upg2_stereo_straw_" << numLayers << "_layers_" << Int_t(floor(innerRadius)) << "_x_" << Int_t(floor(outerRadius)) << ".01.geo";
const char* filename = (fname.str()).c_str();

// output file for straw endcap geometry
ofstream* f = new ofstream(filename, ios::out | ios::trunc);                                                                            

//************************* Main procedure START *****************************

Mpdshape* layerL = initDrawLayer(f, TVector3(angleLayers, 0.0, 0.0), TVector3(0, 0, initDist + layerThickness/2.0), -angleStereo);
Mpdshape* layer =  initDrawLayer(f, TVector3(angleLayers, 0.0, 0.0), TVector3(0, 0, initDist + layerThickness*1 + layerThickness/2.0), 0);
Mpdshape* layerR = initDrawLayer(f, TVector3(angleLayers, 0.0, 0.0), TVector3(0, 0, initDist + layerThickness*2 + layerThickness/2.0), angleStereo);


for (Int_t i = 3; i < numLayers; i+=3) {                                                                                                          
    drawLayer(layerL, TVector3((i/3.+1)*angleLayers,0,0), TVector3(0,0, initDist + layerThickness/2.0 + (i)*layerThickness));
    drawLayer(layer, TVector3((i/3.+1)*angleLayers,0,0), TVector3(0,0, initDist + layerThickness/2.0 + (i+1)*layerThickness));
    drawLayer(layerR, TVector3((i/3.+1)*angleLayers,0,0), TVector3(0,0, initDist + layerThickness/2.0 + (i+2)*layerThickness));
} 


//*********************** Main procedure END *********************************

delete layerL;
delete layer;
delete layerR;

f->close();
return;

}

Mpdshape* initDrawLayer(ofstream* f, TVector3 rot, TVector3 pos, Double_t alpha) {
    
    points.str(""); position.str(""); rotation.str("");
    // straw layer helpers 
    points << 0.0 << " " << 0.0 << " " << -layerThickness/2.0 << endl;
    points << innerRadius << " " << outerRadius << endl;
    points << 0.0 << " " << 0.0 << " " << layerThickness/2.0;
    position << 0.0 << " " << 0.0 << " " << (initDist+layerThickness/2.0);

    // straw layer definition
    std::ostringstream layername;
    layername << "stt01layer";
    if (alpha > 0) {
	layername << "right";
    } else if (alpha < 0) {
	layername << "left";
    } else {
	layername << "radial";
    }

    Mpdshape* layerR = new Mpdshape(f, (layername.str()).c_str(), "cave", "TUBE", "air",                                                                        
	points.str(),                                     
	position.str());                                                                                                                                 
    layerR->SetSegment(1);

    // straw tube helpers
    points.str(""); position.str(""); rotation.str("");
    points << 0.0 << " " << 0.0 << " " << 0 << endl;
    points << 0.0 << " " << tubeRadius << endl;
    points << 0.0 << " " << 0.0 << " " << (outerRadius-innerRadius);


    std::ostringstream tubename;
    tubename << "stt01tube";
    if (alpha > 0) {
	tubename << "right";
    } else if (alpha < 0) {
	tubename << "left";
    } else {
	tubename << "radial";
    }
    // straw tube definition
    Mpdshape* tube = new Mpdshape(f, (tubename.str()).c_str(), (layername.str()).c_str(), "TUBE", "kapton", points.str());
    tube->SetSegment(1);
    tube->SetMotherSegment(1);

    // straw gas helpers
    points.str(""); position.str(""); rotation.str("");
    points << 0.0 << " " << 0.0 << " " << 0 << endl;
    points << 0.0 << " " << gasRadius << endl;
    points << 0.0 << " " << 0.0 << " " << (outerRadius-innerRadius);

    std::ostringstream gasname;
    gasname << "stt01gas";
    if (alpha > 0) {
	gasname << "right";
    } else if (alpha < 0) {
	gasname << "left";
    } else {
	gasname << "radial";
    }
    // straw gas definition
    Mpdshape* gas = new Mpdshape(f, (gasname.str()).c_str(), (tubename.str()).c_str(), "TUBE", "DCHmixture",
    points.str());
    gas->SetSegment(1);
    gas->SetMotherSegment(1);

    // straw wire helpers
    points.str(""); position.str(""); rotation.str("");
    points << 0.0 << " " << 0.0 << " " << 0 << endl;
    points << 0.0 << " " << wireRadius << endl;
    points << 0.0 << " " << 0.0 << " " << (outerRadius-innerRadius);

    std::ostringstream wirename;
    wirename << "stt01wire";
    if (alpha > 0) {
	wirename << "right";
    } else if (alpha < 0) {
	wirename << "left";
    } else {
	wirename << "radial";
    }
    // straw wire definition
    Mpdshape* wire = new Mpdshape(f, (wirename.str()).c_str(), (gasname.str()).c_str(), "TUBE", "copper",
    points.str());
    wire->SetSegment(1);
    wire->SetMotherSegment(1);

    // output first layer definition, moved to initial position and rotated(!)
    layerR->SetRotation(rot.X(), rot.Y(), rot.Z());
    layerR->SetPosition(pos.X(), pos.Y(), pos.Z());
    layerR->DumpWithIncrement();
    
    // output first tube definition
    // first tube should be rotated too !!
    tube->SetRotation(alpha+angleStraws, 90, 0); 
    TVector3 pos = getPosition(angleStraws);
    tube->SetPosition(pos.X(), pos.Y(), pos.Z());
    tube->DumpWithIncrement();

    // output first gas chamber definition
    gas->DumpWithIncrement();

    // output first wire definition
    wire->DumpWithIncrement();


    // output tubes for first layer, starting from 2 to numStrawsPerLayer, rotate each tube
    for (Int_t i = 2; i <= numStrawsPerLayer; i++) {
	tube->SetRotation(alpha+i*angleStraws, 90, 0);
	TVector3 pos = getPosition(i*angleStraws);
	tube->SetPosition(pos.X(), pos.Y(), pos.Z());
	tube->DumpWithIncrement();
    }

    return layerR;
}

void drawLayer(Mpdshape* layer, TVector3 rot, TVector3 pos) {
    layer->SetRotation(rot.X(), rot.Y(), rot.Z());
    layer->SetPosition(pos.X(), pos.Y(), pos.Z());
    layer->DumpWithIncrement();
}

TVector3 getPosition(Double_t angle) {
    Double_t r = innerRadius;
    Double_t x = r*TMath::Cos(angle*TMath::DegToRad());
    Double_t y = r*TMath::Sin(angle*TMath::DegToRad());
    return TVector3(x, y, 0);
}
