#include <TFile.h>
#include <TTree.h>
#include <TH1D.h>
#include <TH2D.h>
#include <Riostream.h>

//____________________________________________________________________________
void Effic(Int_t nRead = 0)
{
  // Compute track finding efficiency

  Int_t iqMC, iqKF;
  Int_t nhitsMC, lastLay, idMC, nhitsKF, idKF, nWrong, event, lastLayKF;
  Double_t thetaMC, ptMC, thetaKF, ptKF, dTheta, dPt, chi2, z;

  TFile f("test.raw.root");
  TTree *sim = (TTree*) f.Get("MCtracks");
  TTree *rec = (TTree*) f.Get("KFtracks");

  sim->SetBranchAddress("theta",&thetaMC);
  sim->SetBranchAddress("pt",&ptMC);
  sim->SetBranchAddress("nhits",&nhitsMC);
  sim->SetBranchAddress("lastLay",&lastLay);
  sim->SetBranchAddress("id",&idMC);
  sim->SetBranchAddress("q",&iqMC);
  sim->SetBranchAddress("event",&event);

  rec->SetBranchAddress("theta",&thetaKF);
  rec->SetBranchAddress("pt",&ptKF);
  rec->SetBranchAddress("dTheta",&dTheta);
  rec->SetBranchAddress("dPt",&dPt);
  rec->SetBranchAddress("chi2",&chi2);
  rec->SetBranchAddress("z",&z);
  rec->SetBranchAddress("nhits",&nhitsKF);
  rec->SetBranchAddress("id",&idKF);
  rec->SetBranchAddress("q",&iqKF);
  rec->SetBranchAddress("nWrongs",&nWrong);
  rec->SetBranchAddress("lastLay",&lastLayKF);
  rec->SetBranchAddress("event",&event);

  Int_t nEntries = sim->GetEntriesFast();
  sim->GetEntry(nEntries-1);
  Int_t events = event;
  if (nRead != 0) events = TMath::Min (events, nRead);
  cout << " Number of events = " << events << endl;
  Int_t *evPtrSim = new Int_t [events+1]; // event pointers
  Int_t *evPtrRec = new Int_t [events+1]; // event pointers

  TH1D *hPtMC = new TH1D("hPtMC","Pt of primary tracks",100,0,2);
  TH1D *hPtMC1 = new TH1D("hPtMC1","Pt of all tracks",100,0,2);
  TH1D *hPtKF = new TH1D("hPtKF","Pt of primary tracks",100,0,2);
  TH1D *hPtKF1 = new TH1D("hPtKF1","Pt of all tracks",100,0,2);
  TH1D *hPtExtra = new TH1D("hPtExtra","Pt of extra tracks",100,0,2);
  //TH1D *hEff = new TH1D("hEff","Efficiency for primary tracks",200,0,2);
  //TH1D *hEff1 = new TH1D("hEff1","Efficiency for all tracks",200,0,2);
  TH1D *hDpp = new TH1D("hDpp","dPt/Pt of primary tracks",100,-0.2,0.2);
  TH1D *hDpp1 = new TH1D("hDpp1","dPt/Pt of all tracks",100,-0.2,0.2);
  TH2D *hDppVsPt = new TH2D("hDppVsPt","dPt/Pt vs Pt of prim. tracks",100,0,2,100,-0.2,0.2);
  TH2D *hDppVsPt1 = new TH2D("hDppVsPt1","dPt/Pt vs Pt of all tracks",100,0,2,100,-0.2,0.2);

  evPtrSim[0] = evPtrRec[0] = 0;
  Char_t chsel[256];
  for (Int_t i = 1; i <= events; ++i) {
    Int_t evNo = i;
    sprintf(chsel,"event==%d",evNo);
    evPtrSim[i] = evPtrSim[i-1] + sim->GetEntries(chsel);
    evPtrRec[i] = evPtrRec[i-1] + rec->GetEntries(chsel);
  }
     
  for (Int_t i = 0; i < events; ++i) {
    //Int_t nMC = evPtrSim[i+1] - evPtrSim[i];

    // Find max track ID
    Int_t idMax = -1;
    for (Int_t j = evPtrSim[i]; j < evPtrSim[i+1]; ++j) {
      sim->GetEntry(j);
      idMax = TMath::Max (idMax, TMath::Abs(idMC));
    }

    Int_t *trackID = new Int_t [idMax+1];

    // Fill MC track ID's for selected tracks
    for (Int_t j = evPtrSim[i]; j < evPtrSim[i+1]; ++j) {
      sim->GetEntry(j);
      //if (lastLay >= 49 && iqMC != 0) {
      //if (lastLay >= 44 && iqMC != 0) {
      if (lastLay >= 30 && iqMC != 0) {
	//trackID[TMath::Abs(idMC)] = TMath::Sign(1,idMC);
	if (iqMC == 0) trackID[TMath::Abs(idMC)] = 0; //99; // strange case
	//if (iqMC == 0) continue;
	else trackID[TMath::Abs(idMC)] = TMath::Sign(1,iqMC); // charge
	hPtMC1->Fill(ptMC);
	if (idMC <= 0) hPtMC->Fill(ptMC);
	if (idMC <= 0 && ptMC < 0.1) cout << i << " " << idMC << " " << ptMC << endl;
      }
      else trackID[TMath::Abs(idMC)] = 0;
    }

    // Reco tracks
    for (Int_t j = evPtrRec[i]; j < evPtrRec[i+1]; ++j) {
      rec->GetEntry(j);
      if (trackID[TMath::Abs(idKF)] == 0) continue; 
      if (trackID[TMath::Abs(idKF)] != 99 && 
	  trackID[TMath::Abs(idKF)] != -iqKF) { // different sign - 
	// can happen for curling tracks (returning branch)
	hPtExtra->Fill(ptKF);
	continue; 
      }
      //
      if (lastLayKF < -49) continue;
      //
      trackID[TMath::Abs(idKF)] = 0; // protection against returning branches
 
      hPtKF1->Fill(ptKF-dPt);
      hDpp1->Fill(dPt/(ptKF-dPt));
      hDppVsPt1->Fill(ptKF-dPt,dPt/(ptKF-dPt));
      if (idKF <= 0) {
	hPtKF->Fill(ptKF-dPt);
	hDpp->Fill(dPt/(ptKF-dPt));
	hDppVsPt->Fill(ptKF-dPt,dPt/(ptKF-dPt));
      }
    }

    delete [] trackID;
  } // for (Int_t i = 0; i < events;

  TH1D *hEff = (TH1D*) hPtKF->Clone("hEff");
  TH1D *hEff1 = (TH1D*) hPtKF1->Clone("hEff1");
  hEff->SetTitle("Efficiency for primary tracks");
  hEff1->SetTitle("Efficiency for all tracks");
  hEff->Sumw2();
  hEff1->Sumw2();
  hPtMC->Sumw2();
  hPtMC1->Sumw2();
  hEff->Divide(hPtMC);
  hEff1->Divide(hPtMC1);
  hEff->SetMaximum(1.5);
  hEff->SetMinimum(0);
  hEff1->SetMaximum(1.5);
  hEff1->SetMinimum(0);

  TFile out("efficiency.root","recreate");
  hPtKF->Write();
  hPtKF1->Write();
  hPtMC->Write();
  hPtMC1->Write();
  hEff->Write();
  hEff1->Write();
  hDpp->Write();
  hDpp1->Write();
  hDppVsPt->Write();
  hDppVsPt1->Write();
  hPtExtra->Write();
  out.Write();
  out.Close();
}
