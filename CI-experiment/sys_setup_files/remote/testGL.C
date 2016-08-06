
{
#include "TColor.h"

gROOT->Reset();
Int_t row, col;
Char_t NodeName[255];
TNode* node1;
TCanvas* c1 = new TCanvas("c1","Geometry Shapes",200,10,700,700);
//     TView* View = new TView(1);
//     View->SetRange(0,0,0,150,150,150);
TBRIK* brik = new TBRIK("BRIK","BRIK","void",5,5,5);
TBRIK* MARS = new TBRIK("MARS","MARS","void",50,50,50);

TColor* MyCol = new TColor();
//MyCol->SetNumber(240);
MyCol->SetRGB(1,0,0);

TList* ColorList = gROOT->GetListOfColors();
Int_t NColors = ColorList->GetSize();
ColorList->Add(MyCol);
printf("found %i defined colors\n",  NColors );

TNode* Mother = new TNode("Mother","Mother","MARS");
Mother->cd();

for(row=0; row<5; row++){
  for(col=0; col <10; col++){
    sprintf(NodeName,"NODE%d",row*10+col);
    node1 = new TNode(NodeName,NodeName,"BRIK",col*10,row*10,0);
    node1->SetLineColor(row*10+col+1);
  }
}

for(row=4; row<10; row++){
  for(col=0; col <10; col++){
    sprintf(NodeName,"NODE%i",row*10+col);
    node1 = new TNode(NodeName,NodeName,"BRIK",col*10,row*10,0);
    node1->SetLineColor(240);
  }

}

Mother->SetVisibility(2);
Mother->Draw("same");
c1->Modified();
c1->Update();
c1->x3d("OPENGL");
}
