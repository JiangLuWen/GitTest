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
 *
 ***********************************************/
#include <iostream>
#include <vector>
#include <cmath>
#include <string>

#include "TF1.h" //for TF1 class
#include "TH1F.h" //for TH1F class
#include "TMath.h" //for TMath::Landau()
#include "TCanvas.h" //for TCanvas class
#include "TImage.h"
#include "TMultiGraph.h"
#include "TGraph.h"

using namespace std;
typedef vector<TH1*> HistV;
double landauf(double *x, double *par);
int main(){
  //define landau formula
  TF1* myf = new TF1("mylandau",landauf,-3,10,3);
  myf->SetParameters(1.0,2,1);

  //create a vector for holding hist
  HistV histv;
  
  //get ready to initial hist
  const int num = 3;
  string histvName[num] = {"ld_1e2","ld_1e3","ld_1e4"};
  string histvTitle[num] = {"Landau 100 entris","Landau 1000 entris","Landau 10000 entris"};
  int histEntries[num] = {100,1000,10000};

  //new hist and fill them
  //at the same time fit them
  TF1* fitf[3];
  TCanvas* canvas = new TCanvas("myc","HW1",800,600);
  string fitfName[num] = {"Fit func for hist1","Fit func for hist2","Fit func for hist3"};
  TMultiGraph* mg = new TMultiGraph();
  for(int i = 0;i<num;i++){
    histv.push_back(new TH1F(histvName[i].c_str(),histvTitle[i].c_str(),100,-3,10));
    histv[i]->FillRandom("mylandau",histEntries[i]);
    fitf[i] = new TF1(fitfName[i].c_str(),landauf,-3,10,3);
    fitf[i]->SetParameters(1.0,2,1);
    histv[i]->Fit(fitfName[i].c_str(),"q");
    mg->Add((new TGraph())->SetHistogram(histv[i]));
  }
  mg->Draw("AP");

  TImage *img = TImage::Create();
  img->FromPad(canvas);
  img->WriteImage("hw1.png");
  delete img;

  //delete all pointers
  for (HistV::size_type ix = 0; ix != histv.size(); ++ix)
    delete histv[ix];
  delete myf;

  //return
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
