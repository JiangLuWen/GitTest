/************************************************
 * Home work of Ding Xuefeng for 312017Z
 *         <Toolkit in the experiment simulation 
 *                    and data analysis>
 * Homework 4
 * it should be put here:
 * /user/comphys13S/homework/05/${username}/
 * 
 * Description:
 *   There are two tree: t_mc and t_data in the
 * input root file, with two leaf:
 *  child_p1 -- double[4];
 *  child_p2 -- double[4];
 * they are e+/e-'s 4-d momentum in process
 *   J/psi -> e+e-
 * while p[3] represents E, and p[0~3] for vec p
 *
 * Draw the distribution of mass of J/psi from
 * mc and data, compare them so you find new 
 * particle.
 *
 * Author
 *  Name: Ding Xuefeng
 *  email: dingxf@ihep.ac.cn
 *
 * History
 * 2013.04.12 ver 0.0
 *    Plot the mass distribution, generate png 
 * file
 ***********************************************/
//g

{
  const double g[4] = {1,1,1,-1};

  //get tree from input root file
  TFile inputroot("jpsi_rec.root");
  TTree* t_mc = (TTree*)inputroot.Get("t_mc");
  TTree* t_data = (TTree*)inputroot.Get("t_data");

  //var for getting leaf
  double p1[4],p2[4];

  //set up the relationship
  t_mc->SetBranchAddress("child_p1",p1);
  t_mc->SetBranchAddress("child_p2",p2);
  t_data->SetBranchAddress("child_p1",p1);
  t_data->SetBranchAddress("child_p2",p2);

  //set up hist for filling
  const int binN = 100;
  const double binStart = 2.95;
  const double binEnd = 3.28;
  TH1F* hm_mc = new TH1F("h_mc","J/psi mass from MC",binN,binStart,binEnd);
  TH1F* hm_data = new TH1F("h_data","J/psi mass from DATA",binN,binStart,binEnd);

  //Fill mass of mc and data
  double min=20,max=0;
  for(int i = 0;i<t_mc->GetEntries();i++){
    t_mc->GetEntry(i);
    double mass2 = 0;
    for(int d = 0;d<4;d++){
      mass2 += TMath::Power(p1[d]+p2[d],2)*g[d];
    }
    double mass = TMath::Sqrt(-mass2);
    hm_mc->Fill(mass);
    min = (mass<min)?mass:min;
    max = (mass>max)?mass:max;
  }
  cout<<min<<endl;
  cout<<max<<endl;
  for(int i = 0;i<t_data->GetEntries();i++){
    t_data->GetEntry(i);
    double mass2 = 0;
    for(int d = 0;d<4;d++){
      mass2 += TMath::Power(p1[d]+p2[d],2)*g[d];
    }
    double mass = TMath::Sqrt(-mass2);
    hm_data->Fill(mass);
    min = (mass<min)?mass:min;
    max = (mass>max)?mass:max;
  }
  cout<<min<<endl;
  cout<<max<<endl;

  //get the signal
  TH1F* hm_signal = new TH1F("h_signal","signal",binN,binStart,binEnd);
  for(int i = 0;i<binN+1;i++){
    hm_signal->SetBinContent(i,hm_data->GetBinContent(i)-hm_mc->GetBinContent(i));
    hm_signal->SetBinError(i,hm_data->GetBinError(i)-hm_mc->GetBinError(i));
  }

  //ready to draw
  TCanvas* canvas = new TCanvas("cv","HW4",700,500);

  //draw the data hist
  hm_data->Draw("e");
  
  //draw the mc hist
  hm_mc->SetFillColor(45);
  hm_mc->Draw("same");

  .L bwg.C;

  //double x[]={1};
  //double par[]={1,2,3,4};
  //cout<<breitgausfun(x,par);
  //draw the signal
  TF1* myf = new TF1("BW",breitgausfun,2,4,4);
  //TF1 BW = TF1("BW2","[2]*TMath::BreitWigner(x,[0],[1])");
  //BW.SetParameters(3.0943,0.0101,3.96);
  myf->SetParNames("mass","gamma","N","sigma");
  myf->SetParameters(3.0942,0.0012,5.03,0.0103);
  myf->SetNpx(1000);
  myf->SetLineWidth(4);
  myf->SetLineColor(kRed);
  //hm_signal->Fit("BW2","","epsame");
  hm_signal->Fit("BW","","esame");
  
  TLegend *leg = new TLegend(0.19,0.71,0.57,0.91);

  leg->AddEntry(hm_data,"data","pe");
  leg->AddEntry(hm_mc,"MC","pe");
  leg->AddEntry(hm_signal,"signal","pe");
  leg->AddEntry(myf,"Fit","l");

  leg->SetFillColor(0);
  leg->Draw();
}
