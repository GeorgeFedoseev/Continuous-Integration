void AddToPdg()
{
  // Add particles to PDG data base
  // (extract from AliPDG)

  TDatabasePDG *pdgDB = TDatabasePDG::Instance();
  // PDG nuclear states are 10-digit numbers
  // 10LZZZAAAI e.g. deuteron is
  // 1000010020
  const Int_t kion=1000000000;

  const Double_t kAu2Gev=0.9314943228;
  const Double_t khSlash = 1.0545726663e-27;
  const Double_t kErg2Gev = 1/1.6021773349e-3;
  const Double_t khShGev = khSlash*kErg2Gev;
  const Double_t kYear2Sec = 3600*24*365.25;

  // IONS
  //
  // Done by default now from Pythia6 table
  // Needed for other generators
  // So check if already defined

  Int_t ionCode = kion+10020;
  if(!pdgDB->GetParticle(ionCode)){
      pdgDB->AddParticle("Deuteron","Deuteron",2*kAu2Gev+8.071e-3,kTRUE,
                         0,1,"Ion",ionCode);
  }

  pdgDB->AddAntiParticle("Anti Deuteron", - ionCode);

  ionCode = kion+10030;
  if(!pdgDB->GetParticle(ionCode)){
    pdgDB->AddParticle("Triton","Triton",3*kAu2Gev+14.931e-3,kFALSE,
                     khShGev/(12.33*kYear2Sec),1,"Ion",ionCode);
  }

  ionCode = kion+20030;
  if(!pdgDB->GetParticle(ionCode)){
    pdgDB->AddParticle("HE3","HE3",3*kAu2Gev+14.931e-3,kFALSE,
                     0,2,"Ion",ionCode);
  }

  ionCode = kion+20040;
  if(!pdgDB->GetParticle(ionCode)){
    pdgDB->AddParticle("Alpha","Alpha",4*kAu2Gev+2.424e-3,kTRUE,
                       khShGev/(12.33*kYear2Sec),2,"Ion",ionCode);
  }

}
