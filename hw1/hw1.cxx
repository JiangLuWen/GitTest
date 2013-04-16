/************************************************
 * Home work of Ding Xuefeng for 312017Z
 *         <Toolkit in the experiment simulation 
 *                    and data analysis>
 * Homework 1
 * it should be put here:
 * /user/comphys13S/HomeWork02/${username}/
 * 
 * Description:
 *   Compare histogram with 1e2, 1e3 and 1e4
 * entries, while pdf are non-linear shape.
 * 1) Err bars should be plotted, and show the
 * difference between different cases.
 * 2) Print mean, RMS, skewness on the plot and
 * screen
 * 3) Fit them
 * 4) Keep pretty
 *
 * Author
 *  Name: Ding Xuefeng
 *  email: dingxf@ihep.ac.cn
 *
 * History
 *  2013.04.11 ver 0.0
 *   Plot two hist, run in cint
 *  2013.04.17 ver 1.0
 *   Remove vector, use fixed name
 ***********************************************/
#include <iostream>
#include <sstream>
#include <vector>
#include <cmath>
#include <string>
#include <iomanip>

#include "TF1.h" //for TF1 class
#include "TROOT.h" //for gROOT
#include "TStyle.h"
#include "TH1F.h" //for TH1F class
#include "TMath.h" //for TMath::Landau()
#include "TCanvas.h" //for TCanvas class
#include "TImage.h"
#include "TMultiGraph.h"
#include "TGraph.h"
#include "TPaveStats.h"
#include "TList.h"
#include "TLegend.h"

using namespace std;
typedef vector<TH1*> HistV;
double landauf(double *x, double *par);
int main(){
#include "dayabayStyle.C"
  gROOT->SetStyle("dybStyle");
  //define landau formula
  TF1* myf = new TF1("mylandau",landauf,-3,10,3);
  myf->SetParameters(1.0,2,1);

  TCanvas* canvas = new TCanvas("myc","HW1",800,600);

  TH1F* h1 = new TH1F("h1","Landau 100 entries",15,-3,10);
  TH1F* h2 = new TH1F("h2","Landau 1000 entries",60,-3,10);
  TH1F* h3 = new TH1F("h3","Landau 10000 entries",200,-3,10);
  h1->FillRandom("mylandau",100);
  h2->FillRandom("mylandau",1000);
  h3->FillRandom("mylandau",10000);
  h3->GetXaxis()->SetTitle("x");
  h3->GetXaxis()->CenterTitle(true);
  h3->GetYaxis()->SetTitle("Entries");
  h3->GetYaxis()->CenterTitle(true);
  h3->SetStats(kFALSE);

  TF1* fit3 = new TF1("fit3",landauf,-3,10,3);
  fit3->SetParameters(1.0,2,1);
  h3->SetMarkerColor(kRed);
  h3->SetLineColor(kRed);
  fit3->SetLineColor(kRed+2);
  h3->Fit("fit3","q","e");

  TF1* fit2 = new TF1("fit2",landauf,-3,10,3);
  fit2->SetParameters(1.0,2,1);
  h2->SetMarkerColor(kBlue);
  h2->SetLineColor(kBlue);
  fit2->SetLineColor(kBlue+2);
  h2->Fit("fit2","q","esame");

  TF1* fit1 = new TF1("fit1",landauf,-3,10,3);
  fit1->SetParameters(1.0,2,1);
  h1->SetMarkerColor(kGreen);
  h1->SetLineColor(kGreen);
  fit1->SetLineColor(kGreen+2);
  h1->Fit("fit1","q","esame");

  double h1M = h1->GetMean();
  double h1R = h1->GetRMS();
  double h1S = h1->GetSkewness();
  double h2M = h2->GetMean();
  double h2R = h2->GetRMS();
  double h2S = h2->GetSkewness();
  double h3M = h3->GetMean();
  double h3R = h3->GetRMS();
  double h3S = h3->GetSkewness();

  cout<<setprecision(4);
  cout<<"+----+--------+--------+--------+"<<endl;
  cout<<"|hist|  Mean  |  RMS   |skewness|"<<endl;
  cout<<"+----+--------+--------+--------+"<<endl;
  cout<<"+  1 |"<<setw(8)<<h1M<<"|"<<setw(8)<<h1R<<"|"<<setw(8)<<h1S<<"|"<<endl;
  cout<<"+----+--------+--------+--------+"<<endl;
  cout<<"+  2 |"<<setw(8)<<h2M<<"|"<<setw(8)<<h2R<<"|"<<setw(8)<<h2S<<"|"<<endl;
  cout<<"+----+--------+--------+--------+"<<endl;
  cout<<"+  3 |"<<setw(8)<<h3M<<"|"<<setw(8)<<h3R<<"|"<<setw(8)<<h3S<<"|"<<endl;
  cout<<"+----+--------+--------+--------+"<<endl;

  TPaveStats *ptstats = new TPaveStats(0.5747126,0.6334746,0.9353448,0.934322,"brNDC");
  ptstats->SetName("stats");
  ptstats->SetBorderSize(1);
  ptstats->SetFillColor(0);
  ptstats->SetLineWidth(2);
  ptstats->SetTextAlign(12);
  ptstats->SetTextFont(132);
  ptstats->AddText(" hist   Mean     RMS    skewness ");
  ostringstream os;
  cout<<setprecision(4);
  os<<"   1  "<<setw(8)<<h1M<<" "<<setw(8)<<h1R<<" "<<setw(8)<<h1S<<" ";
  ptstats->AddText(os.str().c_str());
  os.str(string());
  os<<"   2  "<<setw(8)<<h2M<<" "<<setw(8)<<h2R<<" "<<setw(8)<<h2S<<" ";
  ptstats->AddText(os.str().c_str());
  os.str(string());
  os<<"   3  "<<setw(8)<<h3M<<" "<<setw(8)<<h3R<<" "<<setw(8)<<h3S<<" ";
  ptstats->AddText(os.str().c_str());
  ptstats->SetOptStat(0);
  ptstats->SetOptFit(111);
  ptstats->Draw();
  h1->GetListOfFunctions()->Add(ptstats);
  ptstats->SetParent(h1);

  TLegend *leg = new TLegend(0.1582915,0.7237762,0.3580402,0.9230769,NULL,"brNDC");
  leg->AddEntry(h1,"100 entries","pe");
  leg->AddEntry(h2,"1000 entries","pe");
  leg->AddEntry(h3,"10000 entries","pe");
  leg->SetFillColor(0);
  leg->Draw();

  //export png
  TImage *img = TImage::Create();
  img->FromPad(canvas);
  img->WriteImage("hw1.png");
  //delete img;
  delete img;

  return 0;
}

double landauf(double *_x, double *_par){
  double x = _x[0];
  double A = _par[0];
  double mu = _par[1];
  double c = _par[2];
  double y = A*TMath::Landau(x,mu,c,true);
  return y;
} 
