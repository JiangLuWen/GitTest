/*--------------------------------------------------------------------*/
Double_t breitgausfun(Double_t *x, Double_t *par) 
/*--------------------------------------------------------------------*/
{
  // Numeric constants
  Double_t invsq2pi = 0.3989422804014; // (2 pi)^(-1/2)
  // Control constants
  int np = 1000; // number of convolution steps
  Double_t sc = 5.; // convolution extends to +-sc Gaussian sigmas
  // Variables
  Double_t xx;
  Double_t fland;
  Double_t sum = 0.0;
  Double_t xlow,xupp;
  Double_t step;

  // Range of convolution integral
  xlow = x[0] - sc * par[3];
  xupp = x[0] + sc * par[3];

  step = (xupp-xlow) / np;

  // Convolution integral of Breit and Gaussian by sum
  for(int i=0; i<np; i++) {
    xx = xlow + (i+.5) * step;
    //int_xl^xu{BW(x)*GU(x0-x)dx}
    fland = TMath::BreitWigner(xx,par[0],par[1]);
    sum += fland * TMath::Gaus(x[0],xx,par[3]);
    /*
    xx = xupp - (i-.5) * step;
    fland = TMath::BreitWigner(xx,par[0],par[1]);
    sum += fland * TMath::Gaus(x[0],xx,par[3]);
    */
  }

  return (par[2] * step * sum * invsq2pi / par[3]);
}
