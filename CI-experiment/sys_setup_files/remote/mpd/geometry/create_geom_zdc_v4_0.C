#include "mpdshape.class.C"

void create_geom_zdc_v4_0 (const char* filename = "")
{

  Double_t initDist = 3705.0; // Distance between ZDC and interacting point (along the beam), mm

  Double_t innerRadius = 50.;  // the hole XY rectangle: "2*innerRadius x 2*innerRadius", mm
  Double_t outerRadius = 600.0 ; // 250.0; //  mm

  Double_t xyWidth = innerRadius ; // 50.0;       // x and y - half-dimension of single module, mm
  Double_t zWidth = 800.0;        // z - FULL-dimension of single module, mm

  Double_t xyWidthAS =  innerRadius ; //50.0; // x and y - half-dimension of absorber and  scintillator layer, mm
  Double_t zWidthA = 16.0;         // z - FULL-dimension of absorber layer, mm
  Double_t zWidthS = 4.0;          // z - FULL-dimension of scintillator layer, mm

  Int_t
    ix,iy,imodule, ilayer,
      nrad = 5; // number of modules along radius

  Int_t
    nlayers =  TMath::Nint(zWidth/(zWidthA+zWidthS));        // number of Absorber-Scintillator layers 

     
  // output file
  ofstream* f;
  if (!strlen(filename)) {
    char filename1[200];
    int tmp = 24*4;     // for 10x10 cm^2
    sprintf(filename1,"zdc_10x10_modules%d_layers%d_%g_%g\.geo",tmp, nlayers,zWidthA,zWidthS);   
    f = new ofstream(filename1, ios::out | ios::trunc);
    cout << "filename: " << filename1 << endl;
  }
  else {
    f = new ofstream(filename, ios::out | ios::trunc);
    cout << "filename: " << filename << endl;
  }

                                           

  // helper streams
  std::ostringstream points, position, rotation;
  points.setf(ios::showpoint); //points.setf(ios::fixed); points << setprecision(6);
  position.setf(ios::showpoint); position.setf(ios::fixed); rotation << setprecision(6);
  rotation.setf(ios::showpoint); rotation.setf(ios::fixed); rotation << setprecision(6);

  // zdc as whole (one end-cup):

  points << "0.0 0.0 " << (-zWidth/2-10) << endl;
  points << innerRadius << " " << (outerRadius+10) << endl;
  points << "0.0 0.0 " << (zWidth/2+10) << endl;

  //  Mpdshape* zdcmother = new Mpdshape(f, "zdc01", "cave", "TUBS", "air",    points.str(),position.str());  
  Mpdshape* zdcmother = new Mpdshape(f, "zdc01", "cave", "TUBE", "air",    points.str(),position.str());                       
  zdcmother->SetSegment(1);
  //  zdcmother->SetPositionRotation("0. 0. 0."," 1. 0. 0. 0. 1. 0. 0. 0.  1.");  
  zdcmother->SetPosition(0., 0., initDist+zWidth/2);  
  zdcmother->SetRotation(" 1. 0. 0. 0. 1. 0. 0. 0.  1.");  
  zdcmother->DumpWithIncrement();

  // one module:

  points.str(""); position.str(""); rotation.str("");  points << setprecision(4);

  points << xyWidth << " " << -xyWidth << " " << "0." << endl;
  points << xyWidth << " " << xyWidth << " " << "0." << endl;
  points << -xyWidth << " " << xyWidth << " " << "0." << endl;
  points << -xyWidth << " " << -xyWidth << " " << "0." << endl;
  points << xyWidth << " " << -xyWidth << " " << zWidth << endl;
  points << xyWidth << " " << xyWidth << " " << zWidth << endl;
  points << -xyWidth << " " << xyWidth << " " << zWidth << endl;
  points << -xyWidth << " " << -xyWidth << " " << zWidth;

  Mpdshape* zdcmodule = new Mpdshape(f, "zdc01m", "zdc01#1", "BOX", "air",    points.str(),position.str());
  zdcmodule->SetSegment(1);  

  imodule=1;

  Mpdshape *zdclayer_abs=0, *zdclayer_sci=0;
  Double_t xm,ym;
  Int_t signx, signy;

  for (ix=(-nrad);ix<=nrad;ix++) {
        signx=(ix>=0)? 1 : -1;
    for (iy=(-nrad);iy<=nrad;iy++) {
      if ((ix)||(iy)) ) {
        signy=(iy>=0)? 1 : -1;
	xm=xyWidth*2*ix+xyWidth*signx;
	ym=xyWidth*2*iy+xyWidth*signy;
	if (TMath::Sqrt(xm*xm+ym*ym)<=(outerRadius+5))  {
	    zdcmodule->SetPosition(xyWidth*2*ix,xyWidth*2*iy,-zWidth/2);
	    zdcmodule->SetRotation(" 1. 0. 0. 0. 1. 0. 0. 0. 1.");
	    zdcmodule->DumpWithIncrement();
	    if (imodule==1) {
	      for (ilayer=0;ilayer<nlayers;ilayer++) {
		if (!ilayer) {
		  points.str(""); position.str("");
		  points << xyWidthAS << " " << -xyWidthAS << " " << "0." << endl;
		  points << xyWidthAS << " " << xyWidthAS << " " << "0." << endl;
		  points << -xyWidthAS << " " << xyWidthAS << " " << "0." << endl;
		  points << -xyWidthAS << " " << -xyWidthAS << " " << "0." << endl;
		  points << xyWidthAS << " " << -xyWidthAS << " " << zWidthA << endl;
		  points << xyWidthAS << " " << xyWidthAS << " " << zWidthA << endl;
		  points << -xyWidthAS << " " << xyWidthAS << " " << zWidthA << endl;
		  points << -xyWidthAS << " " << -xyWidthAS << " " << zWidthA;
		  zdclayer_abs = new Mpdshape(f, "zdc01a", "zdc01m#1", "BOX", "lead",    points.str(),position.str());
		  zdclayer_abs->SetSegment(1);  

		  points.str(""); position.str("");
		  points << xyWidthAS << " " << -xyWidthAS << " " << "0." << endl;
		  points << xyWidthAS << " " << xyWidthAS << " " << "0." << endl;
		  points << -xyWidthAS << " " << xyWidthAS << " " << "0." << endl;
		  points << -xyWidthAS << " " << -xyWidthAS << " " << "0." << endl;
		  points << xyWidthAS << " " << -xyWidthAS << " " << zWidthS << endl;
		  points << xyWidthAS << " " << xyWidthAS << " " << zWidthS << endl;
		  points << -xyWidthAS << " " << xyWidthAS << " " << zWidthS << endl;
		  points << -xyWidthAS << " " << -xyWidthAS << " " << zWidthS;
		  zdclayer_sci = new Mpdshape(f, "zdc01s", "zdc01m#1", "BOX", "FscScint",    points.str(),position.str());
	      zdclayer_sci->SetSegment(1);  
	    }
	    zdclayer_abs->SetPosition(0.,0.,(zWidthA+zWidthS)*ilayer);
	    zdclayer_abs->SetRotation(" 1. 0. 0. 0. 1. 0. 0. 0. 1.");
	    zdclayer_abs->DumpWithIncrement();
	    zdclayer_sci->SetPosition(0.,0.,(zWidthA+zWidthS)*ilayer+zWidthA);
	    zdclayer_sci->SetRotation(" 1. 0. 0. 0. 1. 0. 0. 0. 1.");
	    zdclayer_sci->DumpWithIncrement();
	  }
	  cout << " layers: " << nlayers << endl;
	}
	imodule++;
	}}
    }}
  cout << " modules: " << (imodule-1) << endl;

  // zdc as whole (second end-cup):
  zdcmother->SetPosition(0., 0., -initDist-zWidth/2);  
  zdcmother->SetRotation(" 1. 0. 0. 0. 1. 0. 0. 0. -1.");  
  zdcmother->DumpToFile();
                  
  // close geometry file                                                                                                                                                                        
  f->close(); 

}
