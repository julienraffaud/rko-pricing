#include <algorithm>
#include <cmath>
#include <iostream>
using namespace std;

double normal_rand()
{
    double x = 0.0;
    double y = 0.0;
    double euc_sq = 0.0;
    
    do
    {
        x = 2.0*rand()/(RAND_MAX)-1;
        y = 2.0*rand()/(RAND_MAX)-1;
        euc_sq = x*x+y*y;
    }while (euc_sq>=1.0);
    return x*sqrt(-2*log(euc_sq)/euc_sq);
}

double ERKO_payoff(bool iscall,
                   double S,
                   double K,
                   double B)
{
    double payoff(0.0);
    
    if (iscall)
    {
        if (B>K)
        {
            if (S>=K and S<=B)
            {
                payoff = S - K;
            }
        }
        else
        {
            cout << "Error: Barrier < Strike"<<endl;
            return 0;
        }

    }
    else
    {
        if (B<K)
        {
            if (S>=B and S<=K)
            {
                payoff = K - S;
            }
        }
        else
        {
            cout << "Error: Barrier > Strike"<<endl;
            return 0;
        }
    }

    return payoff;
}

double monte_carlo_RKO_price(int num_sims,
                             bool isCall,
                             double S,
                             double K,
                             double B,
                             double r,
                             double v,
                             double T)
{
    double S_adjust = S*exp(T*(r-.5*v*v));
    double S_cur = .0;
    double sum_payoff = .0;
    
    for (int i(0); i<num_sims;i++)
    {
        double rnd = normal_rand();
        S_cur = S_adjust*exp(sqrt(v*v*T)*rnd);
        sum_payoff+=ERKO_payoff(isCall,S_cur,K,B);
    }
    return exp(-r*T)*sum_payoff/static_cast<double>(num_sims);
}

int main()
{
    int number_of_simulations = 10;
    bool Call = false;
    double S = 100.0;
    double K = 100.0;
    double B = 90.0;
    double r = 0.05;
    double v = 0.2;
    double T = 1.0;
    
    double price = monte_carlo_RKO_price(number_of_simulations,Call,
                                         S, K, B, r, v,T);
    
    cout <<"Price: "<<price <<endl;
    return 0;
}