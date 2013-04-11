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

#include "TFile.h"
#include "TTree.h"
#include "TH1F.h" 
#include "TCanvas.h"
#include "TImage.h"

using namespace std;
int main(){
  //get tree from input root file
  TFile inputroot("jpsi_rec.root");
  TTree* t_mc = (TTree*)inputroot.Get("t_mc");
  TTree* t_data = (TTree*)inputroot.Get("t_data");

  //calculate mass distribution and store in TH1
  t_mc->Draw("(child_p1[3]+child_p2[3])**2-(child_p1[2]+child_p2[2])**2-(child_p1[1]+child_p2[1])**2-(child_p1[0]+child_p2[0])**2>>m_mc");
  t_data->Draw("(child_p1[3]+child_p2[3])**2-(child_p1[2]+child_p2[2])**2-(child_p1[1]+child_p2[1])**2-(child_p1[0]+child_p2[0])**2>>m_data");

  //get hist
  TH1F* hm_mc = (TH1F*)gDirectory->Get("m_mc");
  TH1F* hm_data = (TH1F*)gDirectory->Get("m_data");

  inputroot.Close();

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
  delete img;
  return 0;
}
