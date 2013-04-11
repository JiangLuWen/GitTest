void draw()
{
TFile *_file0=TFile::Open("OmegaKK_data.root");
TH1F *h1=new TH1F("freedom", "Mphi", 100, -5, 5);
t1=(TTree*)_file0->Get("ana");
t1->Project("freedom","m4xyz[3]");
//t->Project("freedom", "momega", "0.9>momega&momega>0.65&chi2<90");
h1->Draw();
//h1->Draw("e");
//f2=TFile::Open("Phitest4_data.root");
//t2=(TTree*)f2->Get("ana");
//TH1F *h2=new TH1F("error", "Mphi", 100, 0.95, 1.15);
//t2->Project("error", "mphi_4c");
//h2->Draw("esame");
//h2->Draw("same");
}
