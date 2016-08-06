
{
#include "mpdshape.class.C"


const char* filename = "etof_simple_wall.geo";
Double_t initDist = 2500.0; // Distance from interacting point, mm

Double_t innerRadius = 250.0; // Layer inner radius, mm
Double_t outerRadius = 1210.0; // Layer outer radius, mm
Double_t xWidth = 10.0; // x - half-dimension of block
Double_t yWidth = 10.0; // y - half-dimension of block
Double_t zWidth = 5.0; // z - half-dimension of block

// output file for straw endcap geometry
ofstream* f = new ofstream(filename, ios::out | ios::trunc);                                                                            

// helper streams
std::ostringstream points, position, rotation;
points.setf(ios::showpoint); points.setf(ios::fixed); points << setprecision(6);
position.setf(ios::showpoint); position.setf(ios::fixed); rotation << setprecision(6);
rotation.setf(ios::showpoint); rotation.setf(ios::fixed); rotation << setprecision(6);

// stof layer helpers 
points << xWidth << " " << -yWidth << " " << -zWidth << endl;
points << xWidth << " " << yWidth << " " << -zWidth << endl;
points << -xWidth << " " << yWidth << " " << -zWidth << endl;
points << -xWidth << " " << -yWidth << " " << -zWidth << endl;

points << xWidth << " " << -yWidth << " " << zWidth << endl;
points << xWidth << " " << yWidth << " " << zWidth << endl;
points << -xWidth << " " << yWidth << " " << zWidth << endl;
points << -xWidth << " " << -yWidth << " " << zWidth;

position << 0.0 << " " << 0.0 << " " << 0.0;

// straw layer definition
Mpdshape* stofbox = new Mpdshape(f, "etof01", "cave", "BOX", "polystyrene",                                                                        
    points.str(),                                     
    position.str());                       
stofbox->SetSegment(1);

const Double_t hHeight = int(outerRadius/(xWidth*2));
cout << "height: " << hHeight << "\n";
const Double_t hHeight_inner = int(innerRadius/(xWidth*2));

for (Double_t k = -hHeight; k <= hHeight; k ++) {
    for (Double_t m = -hHeight; m <= hHeight; m++) {
	Double_t rad = TMath::Sqrt(k*xWidth*2*k*xWidth*2 + m*yWidth*2*m*yWidth*2);
	if (rad >= innerRadius && rad <= outerRadius) {
	    Double_t kx = k*xWidth*2.0;
	    Double_t my = m*yWidth*2.0;
	    Double_t kz = initDist + zWidth;
	    stofbox->SetPosition(kx, my, kz);
	    stofbox->DumpWithIncrement();
	}
    }
}  
                            
// close geometry file                                                                                                                                                                        
f->close(); 

}