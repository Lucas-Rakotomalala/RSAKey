#include <iostream>
#include <cmath>
#include <vector>
#include <numeric>
#include <algorithm>

#include <boost/multiprecision/cpp_int.hpp>
using boost::multiprecision::cpp_int;

using namespace std;

class KeyGeneration
{
public:
    unsigned p;
    unsigned q;
    unsigned n;     //n = p+g
    unsigned phi_n; //phi_n = (p-1) +(q-1)
    unsigned e;     //1 < e <phi_n; e and phi_n coprime
    unsigned d;     //(e+d) mod phi_n = 1
    unsigned m;     //secret message

    boost::multiprecision::cpp_int c;   //ciphertex
    boost::multiprecision::cpp_int m_0; //result of decryption

    void prompter();
    void primality_check();
    unsigned calculate_n();
    unsigned calculate_phi();
    unsigned calculate_e();
    unsigned calculate_d();

    boost::multiprecision::cpp_int encrypt();
    boost::multiprecision::cpp_int decrypt();
};

void KeyGeneration::prompter()
{
    cout << "Please enter in a prime number p:" << endl;
    cin >> p;
    cout << "Please enter in a prime number q:" << endl;
    cin >> q;
}

void KeyGeneration::primality_check()
{
    vector<unsigned> p_factors;
    for (unsigned i = 2; i <= static_cast<unsigned>(sqrt(p)); i++)
    {
        if (p % i == 0)
        {
            p_factors.push_back(i);
            p_factors.push_back(p / i);
        }
    }

    vector<unsigned> q_factors;
    for (unsigned i = 2; i <= static_cast<unsigned>(sqrt(q)); i++)
    {
        if (q % i == 0)
        {
            q_factors.push_back(i);
            q_factors.push_back(q / i);
        }
    }

    if (p_factors.size() != 0 || q_factors.size() != 0)
        throw(runtime_error("non prime input"));
}

unsigned KeyGeneration::calculate_n()
{
    n = p * q;
    return n;
}

unsigned KeyGeneration::calculate_phi()
{
    phi_n = (p - 1) * (q - 1);
    return phi_n;
}

unsigned KeyGeneration::calculate_e()
{
    unsigned i = 2;
    while (gcd(i, phi_n) != 1)
    {
        i++;
    }
    e = i;
    if (e == phi_n)
        throw(runtime_error("e is greater than or equal to phi_n"));
    return e;
}

unsigned KeyGeneration::calculate_d()
{
    unsigned k = 1;

    while (((k * phi_n) + 1) % e != 0)
        k++;
    d = ((k * phi_n) + 1) / e;

    return d;
}

boost::multiprecision::cpp_int KeyGeneration::encrypt()
{
    cout << "Please enter in a message m to encrypt: " << endl;
    cin >> m;
    c = (boost::multiprecision::cpp_int(boost::multiprecision::pow(boost::multiprecision::cpp_int(m), e))) % n;

    return c;
}

boost::multiprecision::cpp_int KeyGeneration::decrypt()
{
    m_0 = (boost::multiprecision::cpp_int(boost::multiprecision::pow(boost::multiprecision::cpp_int(c), d))) % n;

    return m_0;
}

int main(int argc, const char *argv[])
{
    try
    {
        KeyGeneration obj1;
        obj1.prompter();
        obj1.primality_check();
        cout << obj1.calculate_n() << endl;
        cout << obj1.calculate_phi() << endl;
        cout << obj1.calculate_e() << endl;
        cout << obj1.calculate_d() << endl;

        cout << obj1.encrypt() << endl;
        cout << obj1.decrypt() << endl;
    }
    catch (runtime_error &s)
    {
        cout << s.what() << endl;
    }

    return 0;
}