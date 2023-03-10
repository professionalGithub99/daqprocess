void _WriteResponseTxt(TString ofN = "proton_matrix.txt")
{
  //create a text file called ofN
  ofstream myfile;
  myfile.open (ofN);
  //Loop through a directory of files with the name ./resolutionDir/simulatedResponses/_en_#.#000.root
  //where #.# is the energy of the file
  //if the number is less than 1, then there is no leading 0. just .#000
  //there will be files from .1 to 30 MeV
  int nBins;
  int lIn;
  for(int i = 1; i<=300;i++)
  {
    stringstream ss;
    ss << "./resolutionDir/simulatedResponses/_en_"; 
    if(i<10)
    {
      ss << ".";
      ss<<i;
      ss<<"000.root";
    }
    else{
      float x = i/10.;
      if(std::fmod(x,1)==0.0)
      {
        ss<<x;
        ss<<".0000.root";
      }
      else
      {
        ss<<x;
        ss<<"000.root";
      }
    }
    cout<<ss.str()<<endl;
    TFile *f = new TFile(ss.str().c_str());
    TH1F *h = (TH1F*)f->Get("Det0_neu_smear;1");
    //rebin 4 bins to 1
    //print the number of bins and the x range of the histogram
    cout<<h->GetNbinsX()<<endl;
    cout<<h->GetXaxis()->GetXmin()<<endl;
    cout<<h->GetXaxis()->GetXmax()<<endl;
    //get the energy increment
    float enInc = (h->GetXaxis()->GetXmax()-h->GetXaxis()->GetXmin())/h->GetNbinsX();
    cout<<enInc<<endl;
    h->Rebin(16);
    if(i==1)
    {
      nBins = h->GetNbinsX();
      lIn = h->GetXaxis()->GetBinWidth(1);
      //get low edge if 5th bin
      //get high edge of 5th bin
      cout<<"low edge: "<<h->GetXaxis()->GetBinLowEdge(5)<<endl;
      cout<<"high edge: "<<h->GetXaxis()->GetBinUpEdge(5)<<endl;
      cout << "nBins: " << nBins << endl << "lIn: " << lIn<<"bin XMax "<<h->GetXaxis()->GetXmax()<<endl;
      myfile << nBins << " " << 300 << " " << 1 << " " << lIn << endl;
    }
    cout<<h->GetXaxis()->GetNbins()<<" i "<<i<<endl;
    for(int j=0; j<nBins; j++)
    {
      myfile << h->GetBinContent(j+1) << " ";
    }
    myfile << endl;
  }
}
