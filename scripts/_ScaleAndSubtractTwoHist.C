void _ScaleAndSubtractTwoHist(string expFN, string expHN, string simFN, string simHN, string nFN, string nHN, float windowLow, float windowHigh){
  //open the two files and get the histograms 
  //set range user of both histograms to the windowLow and windowHigh
  //for each histogram scale it by the maximum in the desired range
  //open a tcanvas in which you draw both histograms onto it.
  //now create a file
  //create a new canvas
  //create a new histogram which contains the difference between the two histograms divided by the GetBinError of the first histogram
  //Draw this histgram onto the canvas
  //write the newest histogram to the file
  //close all files

   TFile *expFile = new TFile(expFN.c_str());
   TH1F *expHist = (TH1F*)expFile->Get(expHN.c_str());
    TFile *simFile = new TFile(simFN.c_str());
    TH1F *simHist = (TH1F*)simFile->Get(simHN.c_str());

    expHist->GetXaxis()->SetRangeUser(windowLow, windowHigh);
    simHist->GetXaxis()->SetRangeUser(windowLow, windowHigh);
    simHist->SetLineColor(kRed);
    expHist->Scale(1/expHist->GetMaximum());
    simHist->Scale(1/simHist->GetMaximum());
    //create two clones of the histograms
    TH1F *expHistClone = (TH1F*)expHist->Clone();
    TH1F *simHistClone = (TH1F*)simHist->Clone();
    new TCanvas();
    expHistClone->Draw();
    simHistClone->Draw("same");
    //set the directory of the histograms to 0
    expHistClone->SetDirectory(0);
    simHistClone->SetDirectory(0);


    //create a new file
    //TFile *newFile = new TFile(nFN.c_str(), "RECREATE");
    //create a new histogram with the same number of Bins as the expHist and same range
    //TH1F *newHist = new TH1F(nHN.c_str(), nHN.c_str(), expHist->GetNbinsX(), expHist->GetXaxis()->GetXmin(), expHist->GetXaxis()->GetXmax());
    //print the range of the expHist
    cout << expHist->GetXaxis()->GetXmin() << " " << expHist->GetXaxis()->GetXmax() << endl;


    //create a new file
    TFile *newFile = new TFile(nFN.c_str(), "RECREATE");
    TH1F *newHist = new TH1F(nHN.c_str(), "residuals", expHist->GetNbinsX(), expHist->GetXaxis()->GetXmin(), expHist->GetXaxis()->GetXmax());
    //subtract the two cloned histograms, divide by the error of the first histogram then put these bin values into newHist
    for(int i = 0; i < expHist->GetNbinsX(); i++){
      //print only if between windowLow and windowHigh
      if(expHist->GetBinCenter(i) > windowLow && expHist->GetBinCenter(i) < windowHigh){
        cout << expHist->GetBinCenter(i) << " " << expHist->GetBinContent(i) << " " << simHist->GetBinContent(i) << " " << expHist->GetBinError(i) << endl;
      }
      newHist->SetBinContent(i, (expHist->GetBinContent(i) - simHist->GetBinContent(i))/expHist->GetBinError(i));
    }

    newHist->GetXaxis()->SetRangeUser(windowLow, windowHigh);
    //clone the new histogram
    TH1F *newHistClone = (TH1F*)newHist->Clone();
    //set the directory of the new histogram to 0
    newHistClone->SetDirectory(0);
    new TCanvas();
    //draw the newHist
    newHistClone->Draw();

    //write the newhist to the new file
    newFile->Write();
    //close all files
    expFile->Close();
    expFile->Close();
    simFile->Close();
};
