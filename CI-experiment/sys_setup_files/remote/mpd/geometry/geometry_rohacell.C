{

#include "mpdshape.class.C"

//const char* filename = "rohacell_1_layers.geo";

const Int_t numlayers = 10; // Number of layers
const Double_t initDist = 1550.0; // Distance from interacting point, mm
const Int_t zdir = -1; // Direction in z axis
const Double_t innerRadius = 250.0; // Layer inner radius, mm
const Double_t outerRadius = 1700.0; // Layer outer radius, mm
const Double_t angleStrips = 5.0; // Radial strip angle, degrees
const Double_t widthStrip = 3.0; // width of horizontal strips, mm
const Double_t widthRadStrip = 3.0; // inner width of radial strips, mm
const Double_t widthRohacell = 25.0; // width of the rohacell layer, mm
const Double_t widthGas = 3.0; // total width of the ar+co2 gas layer, mm
const Double_t wireRadius = 0.015; // radius of the wire (diameter = 30 mkm)
const Double_t distWires = 2.0; // distance between wires, mm
const Double_t distLayers = 3.0; // distance between rohacell layers, mm
const Double_t widthFiberglass = 0.3; // width of the fiberglass layer, mm (300 mkm)
const Double_t widthCopper = 0.005; // width of the copper layer, mm (5 mkm)

const Double_t inpos = initDist*zdir; // initial position


// helper streams
std::ostringstream points, position, rotation;
points.setf(ios::showpoint); points.setf(ios::fixed); points << setprecision(6);
position.setf(ios::showpoint); position.setf(ios::fixed); rotation << setprecision(6);
rotation.setf(ios::showpoint); rotation.setf(ios::fixed); rotation << setprecision(6);

// helper stream
std::ostringstream name;
name.str("");

name << "rohacell_" << numlayers << "_layers.geo";
const char* filename = (name.str()).c_str();

// output file for straw endcap geometry
ofstream* f = new ofstream(filename, ios::out | ios::trunc);                                                                            


// ******************** DEFINITION *************************************************************
// ELEMENTS: solid copper -> fiberglass -> rohacell -> fiberglass -> copper -> gas container -> copper -> fiberglass -> rohacell [...]

//********************************************************************************************* 
// Copper layer defininition
// copper layer helpers
points.str(""); position.str(""); rotation.str(""); 
points << 0.0 << " " << 0.0 << " " << -widthCopper/2.0 << endl;
points << innerRadius << " " << outerRadius << endl;
points << 0.0 << " " << 0.0 << " " << widthCopper/2.0;
position << 0.0 << " " << 0.0 << " " << 0.0;

// copper layer definition
Mpdshape* copper = new Mpdshape(f, "rhe01copper", "cave", "TUBE", "copper",                                                                        
    points.str(),                                     
    position.str());                                                                                                                                 
copper->SetSegment(1);
copper->SetPosition(0, 0, inpos); // copper goes first
copper->DumpWithIncrement();

//********************************************************************************************* 
// fiberglass layer helpers
points.str(""); position.str(""); rotation.str(""); 
points << 0.0 << " " << 0.0 << " " << -widthFiberglass/2.0 << endl;
points << innerRadius << " " << outerRadius << endl;
points << 0.0 << " " << 0.0 << " " << widthFiberglass/2.0;
position << 0.0 << " " << 0.0 << " " << 0.0;

// fiberglass layer definition
Mpdshape* fiberglass = new Mpdshape(f, "rhe01fglass", "cave", "TUBE", "fiberglass",                                                                        
    points.str(),                                     
    position.str());                                                                                                                                 
fiberglass->SetSegment(1);
fiberglass->SetPosition(0, 0, inpos + 0.5*widthCopper*zdir + 0.5*widthFiberglass*zdir); // fiberglass goes second
fiberglass->DumpWithIncrement();

//********************************************************************************************* 
// rohacell layer helpers
points.str(""); position.str(""); rotation.str(""); 
points << 0.0 << " " << 0.0 << " " << -widthRohacell/2.0 << endl;
points << innerRadius << " " << outerRadius << endl;
points << 0.0 << " " << 0.0 << " " << widthRohacell/2.0;
position << 0.0 << " " << 0.0 << " " << 0.0;

// rohacell layer definition
Mpdshape* rohacell = new Mpdshape(f, "rhe01rohacell", "cave", "TUBE", "rohacellhf71",                                                                        
    points.str(),                                     
    position.str());                                                                                                                                 
rohacell->SetSegment(1);
rohacell->SetPosition(0, 0, inpos + 0.5*widthCopper*zdir + widthFiberglass*zdir + 0.5*widthRohacell*zdir); // rohacell is third 
rohacell->DumpWithIncrement();


//********************************************************************************************* 

// need to position "-> fiberglass -> copper->" layers here

fiberglass->SetPosition(0, 0, inpos + 0.5*widthCopper*zdir + widthFiberglass*zdir + widthRohacell*zdir 
+ 0.5*widthFiberglass*zdir); 
fiberglass->DumpWithIncrement();

copper->SetPosition(0, 0, inpos + 0.5*widthCopper*zdir + widthFiberglass*zdir + widthRohacell*zdir 
+ widthFiberglass*zdir + 0.5*widthCopper*zdir); 
copper->DumpWithIncrement();

//********************************************************************************************* 
// Gas container layer defininition
// gas container layer helpers
points.str(""); position.str(""); rotation.str(""); 
points << 0.0 << " " << 0.0 << " " << (-widthGas/2.0 - 0.1) << endl; // 100 mikron protection
points << (innerRadius - 0.1) << " " << (outerRadius + 0.1) << endl; // 100 mikron protection
points << 0.0 << " " << 0.0 << " " << (widthGas/2.0 + 0.1); // 100 mikron protection
position << 0.0 << " " << 0.0 << " " << 0.0; 

// gas container layer definition
Mpdshape* gascontainer = new Mpdshape(f, "rhe01gcont", "cave", "TUBE", "vacuum",                                                                        
    points.str(),                                     
    position.str());                                                                                                                                 
gascontainer->SetSegment(1);
gascontainer->SetPosition(0, 0, inpos + 0.5*widthCopper*zdir + widthFiberglass*zdir + widthRohacell*zdir 
+ widthFiberglass*zdir + widthCopper*zdir + 0.5*(widthGas+0.2)*zdir); 
gascontainer->DumpWithIncrement();

//********************************************************************************************* 
const Float_t numrad = 2*TMath::Pi()*innerRadius/(widthStrip+0.2); // zazor 200 mikron
const Float_t radangle = 360.0/(numrad); // angle of strip + zazor
const Float_t radangle2 = 360.0/(2*TMath::Pi()*innerRadius/widthStrip); // angle of strip only
// ar+co2 gas RADIAL strip layer helpers
points.str(""); position.str(""); rotation.str(""); 

points << 0.0 << " " << 0.0 << " " << -widthGas/2.0 << endl;
points << innerRadius << " " << outerRadius << endl;
points << 0.0 << " " << 0.0 << " " << -0.1 << endl;
points << 0.0 << " " << radangle2;
position << 0.0 << " " << 0.0 << " " << 0.0;

// ar+co2 gas layer definition
Mpdshape* gaslayer_R = new Mpdshape(f, "rhe01gasr", "rhe01gcont#1", "TUBS", "arco27030",                                                                        
    points.str(),                                     
    position.str());                                                                                                                                 
gaslayer_R->SetSegment(1);


for (Int_t i = 0; i < numrad; i++) { 
    gaslayer_R->SetRotation(i*radangle, 0, 0);
    gaslayer_R->DumpWithIncrement();
}

//********************************************************************************************* 

const Int_t numcircles = (outerRadius - innerRadius)/(widthStrip+0.2); // kolichestvo kolec, s zazorom
//cout << "total number of circular layers: " << numcircles << endl;

for (Int_t i = 0; i < numcircles; i++) {

// ar+co2 gas LEFT half-CIRCLE strip layer helpers
points.str(""); position.str(""); rotation.str(""); 
points << 0.0 << " " << 0.0 << " " << 0.1 << endl;
points << (innerRadius + i*(widthStrip+0.2)) << " " << (innerRadius + i*(widthStrip+0.2) + widthStrip) << endl;
points << 0.0 << " " << 0.0 << " " << widthGas/2.0 << endl; 
points << 0.1 << " " << 179.9;
position << 0.0 << " " << 0.0 << " " << 0.0;


name.str("");
name << "rhe01gascl" << i;
// ar+co2 gas layer definition
Mpdshape* gaslayer_CL = new Mpdshape(f, (name.str()).c_str(), "rhe01gcont#1", "TUBS", "arco27030",                                                                        
    points.str(),                                     
    position.str());                                                                                                                                 
gaslayer_CL->SetSegment(1);
gaslayer_CL->DumpWithIncrement();
}


//********************************************************************************************* 

for (Int_t i = 0; i < numcircles; i++) {
// ar+co2 gas RIGHT half-CIRCLE strip layer helpers
points.str(""); position.str(""); rotation.str(""); 
points << 0.0 << " " << 0.0 << " " << 0.1 << endl;
points << (innerRadius + i*(widthStrip+0.2)) << " " << (innerRadius + i*(widthStrip+0.2) + widthStrip) << endl;
points << 0.0 << " " << 0.0 << " " << widthGas/2.0 << endl;
points << -179.9 << " " << -0.1;
position << 0.0 << " " << 0.0 << " " << 0.0;

name.str("");
name << "rhe01gascr" << i;
// ar+co2 gas layer definition
Mpdshape* gaslayer_CR = new Mpdshape(f, (name.str()).c_str(), "rhe01gcont#1", "TUBS", "arco27030",                                                                        
    points.str(),                                     
    position.str());                                                                                                                                 
    gaslayer_CR->SetSegment(1);
    gaslayer_CR->DumpWithIncrement();
}

// EXAMPLE: layer->SetRotation(angleLayers, 0.0, 0.0);

//********************************************************************************************* 

cout << "Defined all volumes, now process to positioning \n";

Double_t tmp = inpos + 0.5*widthCopper*zdir + widthFiberglass*zdir + widthRohacell*zdir 
+ widthFiberglass*zdir + widthCopper*zdir + (widthGas+0.2)*zdir;

// copper -> fiberglass -> rhcell ; this completes first layer
copper->SetPosition(0, 0, tmp + 0.5*widthCopper*zdir); 
copper->DumpWithIncrement();

fiberglass->SetPosition(0, 0, tmp + widthCopper*zdir + 0.5*widthFiberglass*zdir); 
fiberglass->DumpWithIncrement();

rohacell->SetPosition(0, 0, tmp + widthCopper*zdir + widthFiberglass*zdir + 0.5*widthRohacell*zdir); 
rohacell->DumpWithIncrement();

// -> fiberglass -> copper -> gascontainer -> copper -> fiberglass -> rohacell
tmp = tmp + widthCopper*zdir + widthFiberglass*zdir + widthRohacell*zdir;
for (Int_t i = 1; i < numlayers; i++) {
    
    fiberglass->SetPosition(0, 0, tmp + 0.5*widthFiberglass*zdir); 
    fiberglass->DumpWithIncrement();
    
    copper->SetPosition(0, 0, tmp + widthFiberglass*zdir + 0.5*widthCopper*zdir); 
    copper->DumpWithIncrement();

    gascontainer->SetPosition(0, 0, tmp + widthFiberglass*zdir + widthCopper*zdir + 0.5*(widthGas+0.2)*zdir ); 
    gascontainer->DumpWithIncrement();

    copper->SetPosition(0, 0, tmp + widthFiberglass*zdir + widthCopper*zdir + (widthGas+0.2)*zdir + 0.5*widthCopper*zdir); 
    copper->DumpWithIncrement();
    
    fiberglass->SetPosition(0, 0, tmp + widthFiberglass*zdir + widthCopper*zdir + (widthGas+0.2)*zdir + widthCopper*zdir 
    + 0.5*widthFiberglass*zdir); 
    fiberglass->DumpWithIncrement();
    
    rohacell->SetPosition(0, 0, tmp + widthFiberglass*zdir + widthCopper*zdir + (widthGas+0.2)*zdir + widthCopper*zdir 
    + widthFiberglass*zdir + 0.5*widthRohacell*zdir);  
    rohacell->DumpWithIncrement();
    
    tmp += widthFiberglass*zdir + widthCopper*zdir + (widthGas+0.2)*zdir + widthCopper*zdir 
    + widthFiberglass*zdir + widthRohacell*zdir;
}



//**************** END ************************************************************************
                            
// close geometry file                                                                                                                                                                        
f->close(); 

}
