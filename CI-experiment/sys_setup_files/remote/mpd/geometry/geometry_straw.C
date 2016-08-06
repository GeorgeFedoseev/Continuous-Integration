{

#include "mpdshape.class.C"

const char* filename = "straw_28_layers.geo";
const Double_t initDist = 1550.0; // Distance from interacting point, mm
const Double_t angleStraws = 1.1920529801325; // Angle between straws in layer, degrees
const Double_t angleLayers = 0.23841059602649; // Angle between layers, degrees
const Double_t distLayers = 10; // Distance between layers, mm
const Double_t innerRadius = 250.0; // Layer inner radius, mm
const Double_t outerRadius = 1210.0; // Layer outer radius, mm
const Double_t tubeRadius = 2.1; // Radius of the straw tube, mm
const Double_t gasRadius = 2.0; // Radius of the straw gas chamber, mm
const Double_t wireRadius = 0.01; // Radius of the straw wire, mm
const Double_t layerThickness = 10; // Thickness of the straw layer, mm
const Double_t numStrawsPerLayer = 302; // Number of straws per layer
const Double_t numLayers = 28; // Number of layers

// output file for straw endcap geometry
ofstream* f = new ofstream(filename, ios::out | ios::trunc);                                                                            

// helper streams
std::ostringstream points, position, rotation;
points.setf(ios::showpoint); points.setf(ios::fixed); points << setprecision(6);
position.setf(ios::showpoint); position.setf(ios::fixed); rotation << setprecision(6);
rotation.setf(ios::showpoint); rotation.setf(ios::fixed); rotation << setprecision(6);

// straw layer helpers 
points << 0.0 << " " << 0.0 << " " << -layerThickness/2.0 << endl;
points << innerRadius << " " << outerRadius << endl;
points << 0.0 << " " << 0.0 << " " << layerThickness/2.0;
position << 0.0 << " " << 0.0 << " " << initDist;

// straw layer definition
Mpdshape* layer = new Mpdshape(f, "stt01layer", "cave", "TUBE", "vacuum",                                                                        
    points.str(),                                     
    position.str());                                                                                                                                 
layer->SetSegment(1);

// straw tube helpers
points.str(""); position.str(""); rotation.str("");
points << 0.0 << " " << 0.0 << " " << innerRadius << endl;
points << 0.0 << " " << tubeRadius << endl;
points << 0.0 << " " << 0.0 << " " << outerRadius;
 
// std::cout << points.str() << endl;
 
// straw tube definition
Mpdshape* tube = new Mpdshape(f, "stt01tube", "stt01layer", "TUBE", "kapton", points.str());
tube->SetSegment(1);
tube->SetMotherSegment(1);


// straw gas helpers
points.str(""); position.str(""); rotation.str("");
points << 0.0 << " " << 0.0 << " " << innerRadius << endl;
points << 0.0 << " " << gasRadius << endl;
points << 0.0 << " " << 0.0 << " " << outerRadius;

// straw gas definition
Mpdshape* gas = new Mpdshape(f, "stt01gas", "stt01tube", "TUBE", "DCHmixture",
    points.str());
gas->SetSegment(1);
gas->SetMotherSegment(1);

// straw wire helpers
points.str(""); position.str(""); rotation.str("");
points << 0.0 << " " << 0.0 << " " << innerRadius << endl;
points << 0.0 << " " << wireRadius << endl;
points << 0.0 << " " << 0.0 << " " << outerRadius; 

// straw wire definition
Mpdshape* wire = new Mpdshape(f, "stt01wire", "stt01gas", "TUBE", "copper",
    points.str());
wire->SetSegment(1);
wire->SetMotherSegment(1);

// output first layer definition, moved to initial position and rotated(!)
layer->SetRotation(angleLayers, 0.0, 0.0);
layer->SetPosition(0, 0, 1550 + layerThickness/2.0);
layer->DumpWithIncrement();

// output first tube definition
// first tube should be rotated too !!
tube->SetRotation(angleStraws, 90, 0); 
tube->DumpWithIncrement();

// output first gas chamber definition
gas->DumpWithIncrement();

// output first wire definition
wire->DumpWithIncrement();

// output tubes for first layer, starting from 2 to numStrawsPerLayer, rotate each tube
for (Int_t i = 2; i <= numStrawsPerLayer; i++) {
    tube->SetRotation(i*angleStraws, 90, 0);
    tube->DumpWithIncrement();
}

// output layers, starting from layer 2 to numLayers, move and rotate each layer
for (Int_t i = 2; i <= numLayers; i++) {                                                                                                          
    layer->SetRotation(i*angleLayers,0,0);
    layer->SetPosition(0,0, 1550 + i*layerThickness);
    layer->DumpWithIncrement();
} 
                            
// close geometry file                                                                                                                                                                        
f->close(); 

}