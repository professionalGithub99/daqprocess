void _WriteResponseToEfficiency(TString ofN = "efficiency.txt")
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
    TH1F *hTotal = (TH1F*)f->Get("Det0_src;1");
    float efficiencey = h->Integral()/hTotal->Integral();
    //write efficiency to file
    std::cout<<i<<" "<<h->Integral()<<" "<<hTotal->Integral()<<" "<<efficiencey<<std::endl;
    myfile << efficiencey << endl;
  }
}
