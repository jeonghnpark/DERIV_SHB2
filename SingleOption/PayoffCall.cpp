#include "PayoffCall.h"
#include <algorithm>  
void PayoffCall::ResetFDGrid(double* px, double* dpx, int minnode, int maxnode) const
{//In case of call, strike is located in the middle of adjacent grid
	for(int i=minnode;i<=maxnode;i++)
	{
		if(strike >=px[i] && strike <=px[i+1])
		{
			
			double tmp=std::min((strike-px[i-1])/2, (px[i+2]-strike)/2);
			px[i]=strike-tmp;
			px[i+1]=strike+tmp;
			
			dpx[i+1]=px[i+2]-px[i+1];
			dpx[i]=px[i+1]-px[i];
			dpx[i-1]=px[i]-px[i-1];
			break;
		}
	}
}

double PayoffCall::Get_strike() const
{
	return strike;
}

int PayoffCall::GetPayoffId() const
{
	return payoffId;
}

PayoffCall::PayoffCall(double strike_):strike(strike_)
{
	payoffId = 1; 
}

double PayoffCall::operator()(double spot) const
{
	return std::max(spot-strike, 0.0);
}

Payoff* PayoffCall::clone() const
{
	return new PayoffCall(*this);
}
