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

{
  //get tree from input root file
  TFile inputroot("jpsi_rec.root");
  TTree* t_mc = (TTree*)inputroot.Get("t_mc");
  TTree* t_data = (TTree*)inputroot.Get("t_data");

  //calculate mass distribution and store in TH1
  t_mc->Draw("sqrt((child_p1[3]+child_p2[3])**2-(child_p1[2]+child_p2[2])**2-(child_p1[1]+child_p2[1])**2-(child_p1[0]+child_p2[0])**2)>>m_mc");
  t_data->Draw("sqrt((child_p1[3]+child_p2[3])**2-(child_p1[2]+child_p2[2])**2-(child_p1[1]+child_p2[1])**2-(child_p1[0]+child_p2[0])**2)>>m_data");

  //get hist
  TH1F* hm_mc = (TH1F*)gDirectory->Get("m_mc");
  TH1F* hm_data = (TH1F*)gDirectory->Get("m_data");

  //get the signal
  const int binN = 100;
  const double binStart = 2.95;
  const double binEnd = 3.28;
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
  
  //draw the mc hist
  hm_mc->SetFillColor(45);
  hm_mc->Draw("same");

  //draw the signal
  TF1 mygaus("fgaus","gaus");
  mygaus->SetNpx(500);
  mygaus->SetLineWidth(4);
  mygaus->SetLineColor(kMagenta);
  hm_signal->Fit("fgaus","","epsame");

}
