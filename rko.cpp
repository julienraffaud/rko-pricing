#include <cstdlib>
#include <cmath>
#include <ctime>
#include <iostream>
using namespace std;

double uniformRandom()
{
    return (double) (rand())/(double) (RAND_MAX);
}

double normalRand()
{
    double u1 = uniformRandom();
    double u2 = uniformRandom();
    return cos(8.*atan(1.)*u2)*sqrt(-.2*log(u1));
}

double European_RKO_payoff(double s, double b, double k)
{
    double payoff(0);
    if (s<=b and s>=k)
    {
        payoff = s - k;
    }
    return payoff;
}

double MC_European_RKO_price(int n, double b, double k, double r)
{
    double total_payoff(0);
    double payoff_sim;
    for (int i(0); i<n; i++)
    {
        double u = normalRand();
        payoff_sim = European_RKO_payoff(u,b,k);
        total_payoff+=payoff_sim;
    }
    return exp(-r)*total_payoff/n;
}

int main()
{
    cout << MC_European_RKO_price(10000,.2,.15,.005)<<endl;
}