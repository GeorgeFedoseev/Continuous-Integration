{
#include "mpdshape.class.C"

const char* filename = "tgem.geo";

const Double_t initDist = 1740.0;
const Double_t driftGap = 3; //mm
const Double_t induceGap = 1; //mm
//=const Double_t electrodeWidth = 1; // mm

//Gem: cuprum-tekstolit-cuprum-tekstolit-cuprim
const Double_t cuprumWidth = 0.018; //mm
const Double_t textolitWidth = 0.5; // mm
const Double_t tgemElectrode =  3*cuprumWidth+2*textolitWidth; // mm
const Double_t layerThickness = driftGap+induceGap+5*cuprumWidth+4*textolitWidth ; // Thickness of Tgem, ~6.09mm 
const Double_t layersDist = 90; //mm

// const Double_t innerRadius = 250.0; // Layer inner radius, mm
const Double_t innerRadius = 100.0; // Layer inner radius, mm
const Double_t outerRadius = 1210.0; // Layer outer radius, mm
const Double_t DRing = 0.4; // hole diameter, mm
const Double_t distRing = 0.8; // distanse between ring, mm
const Double_t outerActiveRadius = outerRadius-2.0; //mm
const Double_t innerActiveRadius = innerRadius+2.0; //mm
const Double_t height=1.0; //mm
Double_t height2;
Double_t numLayers = 10; // Number of layers
Double_t distinblock = 10;

// output file for straw endcap geometry
ofstream* f = new ofstream(filename, ios::out | ios::trunc);                                                                            

// helper streams
std::ostringstream points, position, rotation;
points.setf(ios::showpoint); points.setf(ios::fixed); points << setprecision(6);
position.setf(ios::showpoint); position.setf(ios::fixed); rotation << setprecision(6);
rotation.setf(ios::showpoint); rotation.setf(ios::fixed); rotation << setprecision(6);

// tgem layer helpers 
points << 0.0 << " " << 0.0 << " " << -layerThickness/2.0 << endl;
points << innerRadius << " " << outerRadius << endl;
points << 0.0 << " " << 0.0 << " " << layerThickness/2.0;
position << 0.0 << " " << 0.0 << " " << initDist;

// tgem layer definition. 
Mpdshape* layer = new Mpdshape(f, "tgem01", "cave", "TUBE", "vacuum", points.str(), position.str());
layer->SetSegment(1);

// electrode 1 helpers, cuprum
points.str(""); position.str(""); rotation.str("");
points << 0.0 << " " << 0.0 << " " << -layerThickness/2.0 << endl;
points << innerRadius << " " << outerRadius << endl;
points << 0.0 << " " << 0.0 << " " << -layerThickness/2.0+cuprumWidth;
//= position << 0.0 << " " << 0.0 << " " << -layerThickness/2.0+electrodeWidth;

// electrode 1 definition, cuprum 
Mpdshape* elec1c = new Mpdshape(f, "tgem01electrode1c", "tgem01", "TUBE", "copper", points.str());                                     
//=    position.str());
elec1c->SetSegment(1);
elec1c->SetMotherSegment(1);

// electrode 1 helpers, textolite
points.str(""); position.str(""); rotation.str("");
points << 0.0 << " " << 0.0 << " " << -layerThickness/2.0 +cuprumWidth<< endl;
points << innerRadius << " " << outerRadius << endl;
points << 0.0 << " " << 0.0 << " " << -layerThickness/2.0+cuprumWidth+textolitWidth;
//= position << 0.0 << " " << 0.0 << " " << -layerThickness/2.0+electrodeWidth;

// electrode 1 definition, textolite 
Mpdshape* elec1t = new Mpdshape(f, "tgem01electrode1t", "tgem01", "TUBE", "G10", points.str());                                     
//=    position.str());
elec1t->SetSegment(1);
elec1t->SetMotherSegment(1);

// tgas01 1 helpers, arco27030 Ar+CO2 30%
points.str(""); position.str(""); rotation.str("");
points << 0.0 << " " << 0.0 << " " << -layerThickness/2.0 +cuprumWidth+textolitWidth << endl;
points << innerRadius << " " << outerRadius << endl;
points << 0.0 << " " << 0.0 << " " << -layerThickness/2.0+cuprumWidth+textolitWidth+driftGap;
//= position << 0.0 << " " << 0.0 << " " << -layerThickness/2.0+electrodeWidth;

// tgas01 1 definition, textolite 
Mpdshape* tgas1 = new Mpdshape(f, "tgem01tgas01", "tgem01", "TUBE", "arco27030", points.str());                                     
//=    position.str());
tgas1->SetSegment(1);
tgas1->SetMotherSegment(1);

// Tgem electrode helpers
points.str(""); position.str(""); rotation.str("");
points << 0.0 << " " << 0.0 << " " << -layerThickness/2.0+textolitWidth+cuprumWidth+driftGap << endl;
points << innerRadius << " " << outerRadius << endl;
points << 0.0 << " " << 0.0 << " " << -layerThickness/2.0+textolitWidth+cuprumWidth+driftGap+tgemElectrode;
//= position << 0.0 << " " << 0.0 << " " << 0.0;
Double_t elPos = -layerThickness/2.0 + textolitWidth + cuprumWidth + driftGap; //AZ

// Tgem electrode definition (textolite)
Mpdshape* tgem01elec = new Mpdshape(f, "tgem01electrode", "tgem01", "TUBE", "G10", points.str());                                     
//=    position.str());
tgem01elec->SetSegment(1);
tgem01elec->SetMotherSegment(1);

// Tgem cuprum electrode 1 helpers
points.str(""); position.str(""); rotation.str("");
//AZ points << 0.0 << " " << 0.0 << " " << -tgemElectrode/2.0 << endl;
points << 0.0 << " " << 0.0 << " " << -cuprumWidth/2.0 << endl;
points << innerRadius << " " << outerRadius << endl;
//AZ points << 0.0 << " " << 0.0 << " " << -tgemElectrode/2.0+cuprumWidth;
points << 0.0 << " " << 0.0 << " " << cuprumWidth/2.0;
position << 0.0 << " " << 0.0 << " " << elPos+cuprumWidth/2.0; //AZ

//=================COPPER=========================
// Tgem cuprum electrode 1 definition 
 Mpdshape* cupr01 = new Mpdshape(f, "tgem01cuprum01layer", "tgem01electrode", "TUBE", "copper", points.str(), position.str());
cupr01->SetSegment(1);
cupr01->SetMotherSegment(1);

// Tgem cuprum electrode 2 helpers
points.str(""); position.str(""); rotation.str("");
points << 0.0 << " " << 0.0 << " " << -cuprumWidth/2.0 << endl;
points << innerRadius << " " << outerRadius << endl;
points << 0.0 << " " << 0.0 << " " << cuprumWidth/2.0;
position << 0.0 << " " << 0.0 << " " << elPos + tgemElectrode/2.0; //AZ

// Tgem cuprum electrode 2 definition 
 Mpdshape* cupr02 = new Mpdshape(f, "tgem01cuprum02layer", "tgem01electrode", "TUBE", "copper", points.str(), position.str());
cupr02->SetSegment(1);
cupr02->SetMotherSegment(1);

// Tgem cuprum electrode 3 helpers
points.str(""); position.str(""); rotation.str("");
//AZ points << 0.0 << " " << 0.0 << " " << tgemElectrode/2.0-cuprumWidth << endl;
points << 0.0 << " " << 0.0 << " " << -cuprumWidth/2.0 << endl;
points << innerRadius << " " << outerRadius << endl;
//AZ points << 0.0 << " " << 0.0 << " " << tgemElectrode/2.0;
points << 0.0 << " " << 0.0 << " " << cuprumWidth/2.0;
position << 0.0 << " " << 0.0 << " " << elPos + tgemElectrode - cuprumWidth/2.0; //AZ

// Tgem cuprum electrode 3 definition 
 Mpdshape* cupr03 = new Mpdshape(f, "tgem01cuprum03layer", "tgem01electrode", "TUBE", "copper", points.str(), position.str());
cupr03->SetSegment(1);
cupr03->SetMotherSegment(1);

//==for holes==

//==

// tgas02 1 helpers, arco27030 Ar+CO2 30%
points.str(""); position.str(""); rotation.str("");
points << 0.0 << " " << 0.0 << " " << -layerThickness/2.0+textolitWidth+cuprumWidth+driftGap+tgemElectrode << endl;
points << innerRadius << " " << outerRadius << endl;
points << 0.0 << " " << 0.0 << " " << layerThickness/2.0-cuprumWidth-textolitWidth;
//= position << 0.0 << " " << 0.0 << " " << ...

// tgas2 1 definition, textolite 
Mpdshape* tgas2 = new Mpdshape(f, "tgem01tgas02", "tgem01", "TUBE", "arco27030", points.str());                                     
//=    position.str());
tgas2->SetSegment(1);
tgas2->SetMotherSegment(1);

// electrode 2 helpers, textolit
points.str(""); position.str(""); rotation.str("");
points << 0.0 << " " << 0.0 << " " << layerThickness/2.0-textolitWidth-cuprumWidth << endl;
points << innerRadius << " " << outerRadius << endl;
points << 0.0 << " " << 0.0 << " " << layerThickness/2.0-cuprumWidth;
//= position << 0.0 << " " << 0.0 << " " << -layerThickness/2.0+electrodeWidth;

// electrode 2 definition, textolit 
Mpdshape* elec2t = new Mpdshape(f, "tgem01electrode2t", "tgem01", "TUBE", "G10", points.str());                                     
//=    position.str());
elec2t->SetSegment(1);
elec2t->SetMotherSegment(1);

// electrode 2 helpers, cuprum
points.str(""); position.str(""); rotation.str("");
points << 0.0 << " " << 0.0 << " " << layerThickness/2.0-cuprumWidth << endl;
points << innerRadius << " " << outerRadius << endl;
points << 0.0 << " " << 0.0 << " " << layerThickness/2.0;
//= position << 0.0 << " " << 0.0 << " " << -layerThickness/2.0+electrodeWidth;

// electrode 2 definition, cuprum 
Mpdshape* elec2c = new Mpdshape(f, "tgem01electrode2c", "tgem01", "TUBE", "copper", points.str());                                     
//=    position.str());
elec2c->SetSegment(1);
elec2c->SetMotherSegment(1);

// output first layer definition, moved to initial position and rotated(!)
layer->SetPosition(0, 0, initDist + layerThickness/2.0);
layer->DumpWithIncrement();
elec1c->DumpWithIncrement();
elec1t->DumpWithIncrement();
tgas1->DumpWithIncrement();
tgem01elec->DumpWithIncrement();
cupr01->DumpWithIncrement();
cupr02->DumpWithIncrement();
cupr03->DumpWithIncrement();
tgas2->DumpWithIncrement();
elec2t->DumpWithIncrement();
elec2c->DumpWithIncrement();

//==for holes==
//Not implemented
//==
    layer->SetPosition(0,0, initDist + layerThickness/2.0 + distinblock);
    layer->DumpWithIncrement();
    layer->SetPosition(0,0, initDist + layerThickness/2.0 + 2*distinblock);
    layer->DumpWithIncrement();

// output layers, starting from layer 1 to numLayers, move each layer
for (Int_t i = 1; i < numLayers; i++) {                                                                                                          
    layer->SetPosition(0,0, initDist + layerThickness/2.0 + i*layersDist);
    layer->DumpWithIncrement();
    layer->SetPosition(0,0, initDist + layerThickness/2.0 + i*layersDist+distinblock);
    layer->DumpWithIncrement();
    layer->SetPosition(0,0, initDist + layerThickness/2.0 + i*layersDist+2*distinblock);
    layer->DumpWithIncrement();
} 
for (Int_t i = 0; i < numLayers; i++) {                                                                                                          
    layer->SetPosition(0,0, -initDist + layerThickness/2.0 - i*layersDist);
    layer->SetRotation(0.0, 180., 0.0);
    layer->DumpWithIncrement();
    layer->SetPosition(0,0, -initDist + layerThickness/2.0 - i*layersDist-distinblock);
    layer->SetRotation(0.0, 180., 0.0);
    layer->DumpWithIncrement();
    layer->SetPosition(0,0, -initDist + layerThickness/2.0 - i*layersDist-2*distinblock);
    layer->SetRotation(0.0, 180., 0.0);
    layer->DumpWithIncrement();
}                            
// close geometry file                                                                                                                                                                        
f->close(); 
}
