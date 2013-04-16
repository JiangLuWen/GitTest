#include <vector>
#include <iostream>
#include <string>
#include <math.h>

using namespace std;

vector<double>* TrueFunc(vector<double>* Argm)
{
  vector<double>* TmpTF;//Attention! TmpTF is an empty pointer, maybe I need new.
  TmpTF = new vector<double>;
  //TmpTF->clear();
  cout<<"222"<<endl;
  for(unsigned int i=0; i<Argm->size(); i++)
  {
    cout<<i<<i<<i<<endl;
    TmpTF->push_back(1/(1+25*(*(Argm->begin()+i))*(*(Argm->begin()+i))));
  }
  return TmpTF;
}

vector<double>* LagraIntpo(vector<double>* Argm, vector<double>* TFunc, vector<double>* ArgmL)
{
  vector<double>* TmpLI;
  TmpLI = new vector<double>; 
  //TmpLI->clear();
  for(unsigned int j=0; j<ArgmL->size(); j++)
  {
    vector<double> phi;
    phi.push_back(0.);
    for(unsigned int i=0; i<Argm->size(); i++)//for phi(xj), the one LagraIntpo value
    {
      vector<double> l;
      l.push_back(1.);
      for(unsigned int k=0; k<Argm->size(); k++)//for li(xj), one Lagrange Interpolation basis
      {
        if(k==i){
          continue;
        }else{
          l[0]=l[0]*((*(ArgmL->begin()+j))-(*(Argm->begin()+k)))/((*(Argm->begin()+i))-(*(Argm->begin()+k)));//Introduction to Computing Method (2.20)
        } 
      }
      phi[0]=phi[0]+l[0];//Introduction to Computing Method (2.21)
    }  
    TmpLI->push_back(phi[0]);
  }
  return TmpLI;
}

vector<double>* ThreHerm(vector<double>* Argm, vector<double>* TFunc, vector<double>* ArgmH)
{
  vector<double> Fdrv;
  vector<double>* TmpTH;
  Fdrv.clear();
  TmpTH = new vector<double>; //By DingXuefeng: Inialization a pointer means allocate mem for it.
  //TmpTH->clear(); You don't need it.
  for(unsigned int i=0; i<Argm->size(); i++)//compute first order derivative
  {
    Fdrv.push_back(((-50)*(*(Argm->begin()+i)))/pow((1+25*pow(*(Argm->begin()+i),2)),2));
  }
  for(unsigned int j=0; j<ArgmH->size(); j++)
  {
    vector<double> CapH, H, h;
    CapH.push_back(0.);
    H.push_back(0.); 
    h.push_back(0.);//CapH is temporary for TmpTH, H and h are the two kinds of Interpolation basis in Three Hermite Method
    for(unsigned int i=0; i<Argm->size(); i++)
    {
      vector<double> x, xi, xi1;
      x.push_back(*(ArgmH->begin()+j));//x
      xi.push_back(*(Argm->begin()+i));//x(i)
      xi1.push_back(*(Argm->begin()+i+1));//x(i+1)
      
      h[0]=(1+2*(x[0]-xi[0])/(xi1[0]-xi[0]))*pow(((x[0]-xi1[0])/(xi[0]-xi1[0])),2);
      H[0]=(x[0]-xi[0])*pow(((x[0]-xi1[0])/(xi[0]-xi1[0])),2);
      CapH[0]=((*(TFunc->begin()+i))*h[0]+Fdrv[i]*H[0]);  
    }
    TmpTH->push_back(CapH[0]);
  }
  return TmpTH;
}

int main()
{
  vector<double>* x, *xl, *xh, *TF, *LI, *TH;
  cout<<"The value of True Fucntion:"<<endl;
  cout<<"amazing"<<endl;
  x = new vector<double>; //allocate mem for it.
  for(unsigned int i=0; i<=10; i++)//i=0,1,2,...,10
  {
    cout<<i<<i<<i<<endl;
    x->push_back(-1+0.2*i);//known argument
  }
  cout<<"111"<<endl;
    TF=TrueFunc(x);//known func value
  cout<<"000"<<endl;
  for(unsigned int i=0; i<(TF->size()); i++)
  {
    cout<<(*(TF->begin()+i))<<";"<<endl;    
  }

  cout<<"The value of Lagrange Interpolation method:"<<endl;
  xl = new vector<double>; //allocate mem for it.
  for(unsigned int i=0; i<=40; i++)//i=0,1,2,...,40
  {
    xl->push_back(-1+0.05*i);
  }
    LI=LagraIntpo(x, TF, xl);

  for(unsigned int i=0; i<LI->size(); i++)
  {
    double OPutLI;
    OPutLI=*(LI->begin()+i);
    cout<<OPutLI<<";"<<endl;
  }

  xh = new vector<double>;
  cout<<"The value of Three Hermite method:"<<endl;
  for(unsigned int i=0; i<=40; i++)//i=0,1,2,...,40
  {
    xh->push_back(-1+0.05*i);
  }
    TH=ThreHerm(x, TF, xh);
  for(unsigned int i=0; i<TH->size(); i++)
  {
    cout<<(*(TH->begin()+i))<<";"<<endl;
  }

  delete x;
  delete xl;
  delete xh;
  delete TF;
  delete LI;
  delete TH; //free them, or your mem will be used up soon

  return 0; // You should return in c++, which is different from c.
}
