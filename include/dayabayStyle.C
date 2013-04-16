{
TStyle* dybStyle = new  TStyle("dybStyle", "Daya Bay Style");

//set the background color to white
Int_t icol=0;
//dybStyle->SetFillColor(icol); 
dybStyle->SetFrameFillColor(icol);
dybStyle->SetCanvasColor(icol);
dybStyle->SetPadColor(icol);
dybStyle->SetStatColor(icol);
dybStyle->SetTitleFillColor(icol);
//dybStyle->SetLegendFillColor(icol); //Only available for ROOT version >= 5.30
//For ROOR version < 5.30
//TStyle has no global setting for Lengend FillColor 
//Set the FillColor for the Legend to White whenever you create it. legend->SetFillColor(0)

//dont put a colored frame around the plots
dybStyle->SetFrameBorderMode(0);
dybStyle->SetCanvasBorderMode(0);
dybStyle->SetPadBorderMode(0);
dybStyle->SetLegendBorderSize(0);

//use the primary color palette
dybStyle->SetPalette(1);

//set the default line color for a histogram to be black
dybStyle->SetHistLineColor(kBlack);

//set the default line color for a fit function to be blue
dybStyle->SetFuncColor(kBlue);

//make the axis labels black
dybStyle->SetLabelColor(kBlack,"xyz");

//set the default title color to be black
dybStyle->SetTitleColor(kBlack);
 
//set the margins, give some additional space on the Left/Bottom where axis labels go
dybStyle->SetPadTopMargin(0.05);
dybStyle->SetPadBottomMargin(0.12);
dybStyle->SetPadRightMargin(0.05); //set larger for Draw("colz")
dybStyle->SetPadLeftMargin(0.13);

//set axis label and title text sizes
Int_t font=132; //bold (4), high precision (2), root default 62
Double_t tsize=0.05; //should be set between 0.04-0.06, is in units of "% of pad"
dybStyle->SetLabelFont(font,"xyz"); 
dybStyle->SetLabelSize(tsize,"xyz");
dybStyle->SetLabelOffset(0.01,"xyz");
dybStyle->SetTitleFont(font,"xyz");
dybStyle->SetTitleSize(tsize,"xyz");
//offset the title of y and z axis a bit. The optimal tile offset relies on the number of label digits.
//The default 1.1 is proper for 3 or 4 digits.
dybStyle->SetTitleOffset(1.1,"yz"); 
dybStyle->SetTitleOffset(1.0,"x");
dybStyle->SetTitleBorderSize(0);
dybStyle->SetStatFont(font);
dybStyle->SetStatFontSize(tsize);
dybStyle->SetStatBorderSize(1);
dybStyle->SetStatX(0.98);
dybStyle->SetStatY(0.98);
dybStyle->SetTextFont(font);

//set line widths
dybStyle->SetFuncWidth(2);
dybStyle->SetHistLineWidth(2);

//turn off xy grids
dybStyle->SetPadGridX(0);
dybStyle->SetPadGridY(0);

//set the tick marks on top and right of plots 
//dybStyle->SetPadTickX(1);
//dybStyle->SetPadTickY(1);
// tick marks only on left and bottom
dybStyle->SetPadTickX(0);
dybStyle->SetPadTickY(0);

dybStyle->SetOptTitle(0); //no tile shown
//dybStyle->SetOptStat(111); //standard stat info
dybStyle->SetOptStat(0); //number of entries only
dybStyle->SetOptFit(1111);  //standard fit info
//dybStyle->SetOptFit(0);       //no fit info

//marker settings
dybStyle->SetMarkerStyle(20);
dybStyle->SetMarkerSize(0.8);
dybStyle->SetLineWidth(2); 

dybStyle->SetEndErrorSize(0); //no error caps

//done
dybStyle->cd();
gROOT->ForceStyle();
gStyle->ls();

}
