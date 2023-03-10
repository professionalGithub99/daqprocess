TCutG *AmbeOnlyNeutrons(){
//========= Macro generated from object: CUTG/Graph
//========= by ROOT version6.26/10
   TCutG *cutg = new TCutG("CUTG",10);
   cutg->SetVarX("PSP vs Light Output");
   cutg->SetVarY("");
   cutg->SetTitle("Graph");
   cutg->SetFillStyle(1000);
   cutg->SetPoint(0,9.8463,0.0734426);
   cutg->SetPoint(1,4.84316,0.0546889);
   cutg->SetPoint(2,-0.505019,0.0783778);
   cutg->SetPoint(3,-0.403074,0.487011);
   cutg->SetPoint(4,-0.144291,0.5107);
   cutg->SetPoint(5,0.153701,0.512674);
   cutg->SetPoint(6,0.357591,0.263941);
   cutg->SetPoint(7,9.34442,0.118846);
   cutg->SetPoint(8,9.78356,0.0882481);
   cutg->SetPoint(9,9.8463,0.0734426);
   cutg->Draw("");
   return cutg;
}
