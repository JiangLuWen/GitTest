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
#include <iostream>
#include <vector>
#include <cmath>
#include <string>

#include "TF1.h" 
#include "TH1F.h" 
#include "TMath.h" 
#include "TCanvas.h" 
#include "TImage.h"
#include "TMultiGraph.h"
#include "TGraph.h"

using namespace std;
double landauf(double *x, double *par);
int main(){
  //read root file
  TFile inputroot("jpsi_rec.root");
  TTree* t_mc,t_data;





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
  TCanvas* canvas = new TCanvas("myc","HW1",800,600);
  TMultiGraph* mg = new TMultiGraph();
  for(int i = 0;i<num;i++){
    histv.push_back(new TH1F(histvName[i].c_str(),histvTitle[i].c_str(),100,-3,10));
    histv[i]->FillRandom("mylandau",histEntries[i]);
    histv[i]->Draw("same");
    mg->Add();
  }

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
