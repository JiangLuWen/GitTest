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

#include "TFile.h"
#include "TTree.h"
#include "TH1F.h" 
#include "TCanvas.h"
#include "TImage.h"
#include "TMath.h"

//g
const double g[4] = {-1,1,1,1};
void fillmass(TTree* tree,int entry,TH1* hist,double* p1,double* p2);

using namespace std;
int main(){
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
  const int binN = 20;
  const double binStart = 8.8;
  const double binEnd = 12.7;
  TH1F* hm_mc = new TH1F("h_mc","J/psi mass from MC",binN,binStart,binEnd);
  TH1F* hm_data = new TH1F("h_data","J/psi mass from DATA",binN,binStart,binEnd);

  //Fill mass of mc and data
  for(int i = 0;i<t_mc->GetEntries();i++){
    fillmass(t_mc,i,hm_mc,p1,p2);
    fillmass(t_data,i,hm_data,p1,p2);
  }

  //ready to draw
  TCanvas* canvas = new TCanvas("cv","HW4",700,500);

  //draw the mc hist
  hm_mc->SetFillColor(45);
  hm_mc->Draw();

  //draw the data hist
  hm_data->Draw("esame");
  
  //export png
  TImage *img = TImage::Create();
  img->FromPad(canvas);
  img->WriteImage("hw4.png");
  inputroot.Close();
  delete img;
  return 0;
}
void fillmass(TTree* tree,int entry,TH1* hist,double* p1,double* p2){
    tree->GetEntry(entry);
    //cout<<p1[0]<<endl;
    double mass2 = 0;
    for(int d = 0;d<4;d++)
      mass2 += TMath::Power(p1[d]+p1[d],2)*g[d];
    cout<<mass2<<endl;
    hist->Fill(mass2);
}
