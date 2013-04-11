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
#include<iostream>

#include "Rtypes.h"//for kFALSE
#include "TROOT.h" //for gROOT
#include "TStyle.h"
#include "TFile.h"
#include "TTree.h"
#include "TH1F.h" 
#include "TCanvas.h"
#include "TImage.h"
#include "TMath.h"

//g
const double g[4] = {1,1,1,-1};
double fillmass(TTree* tree,int entry,TH1* hist,double* p1,double* p2);

using namespace std;
int main(){
#include "dayabayStyle.C"
  gROOT->SetStyle("dybStyle");
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
  double min(20),max(0);
  for(int i = 0;i<t_mc->GetEntries();i++){
    double mass = fillmass(t_mc,i,hm_mc,p1,p2);
    min = (mass<min)?mass:min;
    max = (mass>max)?mass:max;
  }
  cout<<min<<endl;
  cout<<max<<endl;
  for(int i = 0;i<t_data->GetEntries();i++){
    double mass = fillmass(t_data,i,hm_data,p1,p2);
    min = (mass<min)?mass:min;
    max = (mass>max)?mass:max;
  }
  cout<<min<<endl;
  cout<<max<<endl;

  //get the signal
  TH1F* hm_signal = new TH1F("h_signal","signal",binN,binStart,binEnd);
  for(int i = 0;i<binN+1;i++){
    /*
    Convention for numbering bins

    For all histogram types: nbins, xlow, xup
      bin = 0;       underflow bin
      bin = 1;       first bin with low-edge xlow INCLUDED
      bin = nbins;   last bin with upper-edge xup EXCLUDED
      bin = nbins+1; overflow bin
    From root site
    */
    hm_signal->SetBinContent(i,hm_data->GetBinContent(i)-hm_mc->GetBinContent(i));
    hm_signal->SetBinError(i,hm_data->GetBinError(i)-hm_mc->GetBinError(i));
  }

  //ready to draw
  TCanvas* canvas = new TCanvas("cv","HW4",700,500);

  //draw the data hist
  hm_data->Draw("e");
  hm_data->SetStats(kFALSE);
  
  //draw the mc hist
  hm_mc->SetFillColor(45);
  hm_mc->Draw("same");
  hm_mc->SetStats(kFALSE);

  //draw the signal
  hm_signal->Draw("same");

  //export png
  TImage *img = TImage::Create();
  img->FromPad(canvas);
  img->WriteImage("hw4.png");
  inputroot.Close();
  delete img;
  return 0;
}
double fillmass(TTree* tree,int entry,TH1* hist,double* p1,double* p2){
    tree->GetEntry(entry);
    double mass2 = 0;
    for(int d = 0;d<4;d++){
      mass2 += TMath::Power(p1[d]+p2[d],2)*g[d];
    }
    double mass = TMath::Sqrt(-mass2);
    hist->Fill(mass);
    return mass;
}
