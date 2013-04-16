#include <vector>
#include <iostream>
#include <string>
#include <math.h>
//#include <>

using namespace std;

vector<double>* TrueFunc(vector<double>* Argm)
{
	vector<double>* TmpTF;//Attention! TmpTF is an empty pointer, maybe I need new.
	TmpTF->clear();
	cout<<"222"<<endl;
	for(int i=0; i<Argm->size(); i++)
	{
		cout<<i<<i<<i<<endl;
		TmpTF->push_back(1/(1+25*(*(Argm->begin()+i))*(*(Argm->begin()+i))));
	}
	return TmpTF;
}

vector<double>* LagraIntpo(vector<double>* Argm, vector<double>* TFunc, vector<double>* ArgmL)
{
	vector<double>* TmpLI;
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
	TmpTH->clear();
	for(int i=0; i<Argm->size(); i++)//compute first order derivative
	{
		Fdrv.push_back(((-50)*(*(Argm->begin()+i)))/pow((1+25*pow(*(Argm->begin()+i),2)),2));
	}
	for(int j=0; j<ArgmH->size(); j++)
	{
		vector<double> CapH, H, h;
		CapH.push_back(0.);
		H.push_back(0.); 
		h.push_back(0.);//CapH is temporary for TmpTH, H and h are the two kinds of Interpolation basis in Three Hermite Method
		for(int i=0; i<Argm->size(); i++)
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
	for(int i=0; i<=10; i++)//i=0,1,2,...,10
	{
		cout<<i<<i<<i<<endl;
		x->push_back(-1+0.2*i);//known argument
	}
	cout<<"111"<<endl;
		TF=TrueFunc(x);//known func value
	cout<<"000"<<endl;
	for(int i=0; i<(TF->size()); i++)
	{
		cout<<(*(TF->begin()+i))<<";"<<endl;		
	}

	cout<<"The value of Lagrange Interpolation method:"<<endl;
	for(int i=0; i<=40; i++)//i=0,1,2,...,40
	{
		xl->push_back(-1+0.05*i);
	}
		LI=LagraIntpo(x, TF, xl);

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
		TH=ThreHerm(x, TF, xh);
	for(int i=0; i<TH->size(); i++)
	{
		cout<<(*(TH->begin()+i))<<";"<<endl;
	}
}
