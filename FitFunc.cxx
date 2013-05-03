#include <vector>
#include <iostream>
#include <string>
#include <math.h>
#include "TGraph.h"

#define p pow

using namespace std;

vector<double>* TrueFunc(vector<double>* Argm)
{
	vector<double>* TmpTF = new vector<double>;//Attention! TmpTF is an empty pointer, maybe I need new.
	TmpTF->clear();
	for(int i=0; i<Argm->size(); i++)
	{
		TmpTF->push_back(1/(1+25*(*(Argm->begin()+i))*(*(Argm->begin()+i))));
	}
	return TmpTF;
}

vector<double>* LagraIntpo(vector<double>* Argm, vector<double>* TFunc, vector<double>* ArgmL)
{
	vector<double>* TmpLI = new vector<double>;
	TmpLI->clear();
	for(int j=0; j<ArgmL->size(); j++)
	{
		vector<double> phi;
		phi.push_back(0.);
		for(int i=0; i<Argm->size(); i++)//for phi(xj), the one LagraIntpo value
		{
			vector<double> l;
			l.push_back(1.);
			for(int k=0; k<Argm->size(); k++)//for li(xj), one Lagrange Interpolation basis
			{
				if(k==i){
					continue;
				}else{
					l[0]=l[0]*((*(ArgmL->begin()+j))-(*(Argm->begin()+k)))/((*(Argm->begin()+i))-(*(Argm->begin()+k)));//Introduction to Computing Method (2.20)
				} 
			}
			phi[0]=phi[0]+*(TFunc->begin()+i)*l[0];//Introduction to Computing Method (2.21)
		}	
		TmpLI->push_back(phi[0]);
	}
	return TmpLI;
}

vector<double>* ThreHerm(vector<double>* Argm, vector<double>* TFunc, vector<double>* ArgmH)
{
	vector<double> Fdrv;
	vector<double>* TmpTH = new vector<double>;
	Fdrv.clear();
	TmpTH->clear();
	for(int i=0; i<Argm->size(); i++)//compute first order derivative
	{
		Fdrv.push_back(((-50)*(*(Argm->begin()+i)))/p((1+25*pow(*(Argm->begin()+i),2)),2));
	}
	for(int j=0; j<ArgmH->size(); j++)//take one of xh
	{
		vector<double> CapH, H, h;//CapH[0]+Cap[1] is temporary for TmpTH, H and h are the two kinds of Interpolation basis in Three Hermite Method
		for(int i=0; i<Argm->size(); i++)//judge which range xh is in
		{
			vector<double> x, xi, xi1;
			x.clear();
			xi.clear();
			xi1.clear();
			x.push_back(*(ArgmH->begin()+j));//x
			xi.push_back(*(Argm->begin()+i));//x(i)
			xi1.push_back(*(Argm->begin()+i+1));//x(i+1)
//			cout<<"x="<<x[0]<<endl;
//			cout<<"xi="<<xi[0]<<endl;
//			cout<<"xi1="<<xi1[0]<<endl;
			if(xi<=x && x<=xi1){//two "=" means: if x=xi or x=xi1, them it will be calculated twice in two cycles
				h.push_back((1+2*(x[0]-xi[0])/(xi1[0]-xi[0]))*pow(((x[0]-xi1[0])/(xi[0]-xi1[0])),2));
				h.push_back((1+2*(x[0]-xi1[0])/(xi[0]-xi1[0]))*pow(((x[0]-xi[0])/(xi1[0]-xi[0])),2));

				H.push_back((x[0]-xi[0])*pow(((x[0]-xi1[0])/(xi[0]-xi1[0])),2));
				H.push_back((x[0]-xi1[0])*pow(((x[0]-xi[0])/(xi1[0]-xi[0])),2));

				CapH.push_back((*(TFunc->begin()+i)*h[0]+Fdrv[i]*H[0]));//the value of y*h[0]+y'*H[0]	
				CapH.push_back((*(TFunc->begin()+i+1)*h[1]+Fdrv[i+1]*H[1]));
			}else{
				continue;
			}
		}
		TmpTH->push_back((CapH[0]+CapH[1]));
	}
	return TmpTH;
}

int main()
{
	vector<double>* x = new vector<double>;
	vector<double> *xl = new vector<double>;
	vector<double> *xh = new vector<double>;
	vector<double> *TF, *LI, *TH;
	cout<<"The value of True Fucntion:"<<endl;
	
	for(int i=0; i<=10; i++)//i=0,1,2,...,10
	{
		x->push_back(-1+0.2*i);//known argument
	}
	
	TF=TrueFunc(x);//known func value
	
	TGraph *tgTF= new TGraph(11, &((*x)[0]), &((*TF)[0]));
	tgTF->Draw("*al");

	for(int i=0; i<(TF->size()); i++)
	{
		cout<<(*(TF->begin()+i))<<";"<<endl;		
	}

	cout<<"The value of Lagrange Interpolation method:"<<endl;
	for(int i=0; i<=40; i++)//i=0,1,2,...,40
	{
		xl->push_back(-1+0.05*i);
	}
	
	LI=LagraIntpo(x, TF, xl);//Lagrange Interpolation method
	
	TGraph *tgLI= new TGraph(41, &((*xl)[0]), &((*LI)[0]));
	tgLI->Draw("*alsame");
	
	for(int i=0; i<LI->size(); i++)
	{
		double OPutLI;
		OPutLI=*(LI->begin()+i);
		cout<<OPutLI<<";"<<endl;
	}

	cout<<"The value of Three Hermite method:"<<endl;
	for(int i=0; i<=40; i++)//i=0,1,2,...,40
	{
		xh->push_back(-1+0.05*i);
	}
	
	TH=ThreHerm(x, TF, xh);//Three Hermite method

//	TGraph *tgTH= new TGraph(41, &((*xh)[0]), &((*TH)[0]));
//	tgTH->Draw("*al");

	for(int i=0; i<TH->size(); i++)
	{
		cout<<"LI["<<*(xl->begin()+i)<<"]="<<(*(LI->begin()+i))<<";   "<<"TH["<<*(xl->begin()+i)<<"]="<<(*(TH->begin()+i))<<";"<<endl;
	}
	
}
