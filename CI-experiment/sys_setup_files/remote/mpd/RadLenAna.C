/* Macro draws histograms of radiation length scan of the MPD TPC
 Output result values are "effective radiation lengths" which are calculated as radiation length (cm) divided by distance (cm).
 14/07/2012 A. Basalaev*/

#include <TVector3.h>
#include <TChain.h>
#include <TClonesArray.h>
#include <TH2F.h>
#include "TROOT.h"
#include "TMath.h"

using namespace TMath;

void RadLenAna(TString infile1 = "RadLenSim.root") {

    TH2F *hXY = new TH2F("hXY", "Material budget in the MPD", 3000, -320., 320., 3000, -320., 320.);
    TH2F *hZR = new TH2F("hZR", "Material budget in the MPD", 3000, 0., 500., 1500, 0., 350.);
    TH2F *hZX_narrow = new TH2F("hZX_narrow", "Material budget in the MPD, |y| < 10.0 cm", 3000, -500., 500., 3000, -350., 350.);
    TH2F *hZX = new TH2F("hZX", "Material budget in the MPD", 3000, -500., 500., 3000, -350., 350.);
    TH2F *hEtaDist = new TH2F("hEtaDist", "Material budget in the MPD", 3000, -5.5, 5.5, 1500, 0., 600.);

    /* Load basic libraries */
    gROOT->LoadMacro("$VMCWORKDIR/macro/mpd/mpdloadlibs.C");
    mpdloadlibs(kTRUE, kTRUE); // all libs


    TChain *tree = new TChain("cbmsim");
    tree->Add(infile1);

    // Activate branches
    TClonesArray *fRadLenPs;
    tree->SetBranchAddress("RadLen", &fRadLenPs);

    Int_t events = tree->GetEntries();
    std::cout << " Processing RadLenSimZR..." << std::endl;
    std::cout << " Number of events in file = " << events << std::endl;

    TVector3 PosIn, PosOut, DistVec;

    for (Int_t iEv = 0; iEv < events; iEv++) {
        tree->GetEntry(iEv);

        Int_t fNpoints = fRadLenPs->GetEntriesFast();

        for (Int_t pointIndex = 0; pointIndex < fNpoints; pointIndex++) {
            FairRadLenPoint* RadLenP = (FairRadLenPoint*) fRadLenPs->At(pointIndex);
            Float_t Len = RadLenP->GetRadLength();
            PosIn = RadLenP->GetPosition();
            PosOut = RadLenP->GetPositionOut();
            DistVec = PosIn - PosOut;
            Float_t Dist = DistVec.Mag();
            Float_t LenEff = Dist / Len;

            Float_t X = PosIn.X();
            Float_t Y = PosIn.Y();
            Float_t Z = PosIn.Z();
            Float_t r = Sqrt(X * X + Y * Y);
            Float_t Theta = PosIn.Theta();
            Float_t Eta = -Log(Tan(Theta / 2));

            if(Abs(Y) < 10.0) hZX_narrow->Fill(Z, X, LenEff);
            hZX->Fill(Z, X, LenEff);
            hXY->Fill(X, Y, LenEff);
            hZR->Fill(Z, r, LenEff);
            hEtaDist->Fill(Eta, PosIn.Mag(), LenEff);

            if (pointIndex % 10000 == 0) cout << pointIndex * 100.0 / fNpoints << "% processed" << endl;
        }
        cout << iEv + 1 << " out of " << events << " events processed" << endl;
    }

    gStyle->SetOptStat(0);

    TCanvas *c1 = new TCanvas(hXY->GetName(), hXY->GetName(), 1000, 1000);
    DrawHisto(hXY, "X, cm", "Y, cm", c1);
    TCanvas *c2 = new TCanvas(hZR->GetName(), hZR->GetName(), 1000, 1000);
    DrawHisto(hZR, "Z, cm", "R, cm", c2);
    TCanvas *c3 = new TCanvas(hEtaDist->GetName(), hEtaDist->GetName(), 1000, 500);
    DrawHisto(hEtaDist, "#eta", "Distance from IP, cm", c3);
    TCanvas *c4 = new TCanvas(hZX_narrow->GetName(), hZX_narrow->GetName(), 1000, 700);
    DrawHisto(hZX_narrow, "Z, cm", "X, cm", c4);
    TCanvas *c5 = new TCanvas(hZX->GetName(), hZX->GetName(), 1000, 700);
    DrawHisto(hZX, "Z, cm", "X, cm", c5);

}

void DrawHisto(TH2F* h, TString xName, TString yName, TCanvas *c) {
    h->GetXaxis()->SetTitle(xName);
    h->GetXaxis()->CenterTitle();
    h->GetYaxis()->SetTitle(yName);
    h->GetYaxis()->CenterTitle();
    h->GetZaxis()->SetTitle("Radiation length, X/X0");
    h->SetMaximum(10.);
    h->Draw("colz");
}