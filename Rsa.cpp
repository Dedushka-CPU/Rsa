#include <iostream>
#include <string>
#include <vector>
#include <random> 

using std::cout;
using std::cin;

int Nod(int a,int b){
    int temp;
    while(b!=0){
        temp=b;
        b=a%b;
        a=temp;
    }
    return a;
}

void generateKey(int& e,int& d,int& n){
    std::vector<long long> primes = {
        3, 5, 7, 11, 13, 17, 19, 23, 31, 37, 41, 61, 101, 109, 113, 181,
        199, 211, 257, 281, 313, 409, 421, 503, 571, 613, 631, 661, 719,
        761, 829, 911, 1013, 1051, 1201, 1301, 1361, 1429, 1531, 1601,
        1741, 1861, 1901, 1999, 2341, 2521, 2617, 2917, 3209, 3449, 3613,
        4253, 4621, 4789, 5471, 5659, 6427, 7741, 8089, 9127, 9551, 10513,
        11113, 12323, 14741, 17551, 18713, 21113, 21841, 22541, 23371
    };
    
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(0, primes.size() - 1);

    int p = primes[distrib(gen)];
    int q;
    
    do {
        q = primes[distrib(gen)];
    } while (p == q);

    n = p * q;
    int phi = (p - 1) * (q - 1);
    
    e = 3;
    while (Nod(e,phi)!=1){
        e++;
    }
    int k=1;
    while((1+k*phi)%e!=0){
        k++;
    }
    d=(1+k*phi)/e;
    
}

int PowNum(int base,int exp,int mod){
    int unsigned res=1;
    while(exp>0){
        if(exp%2==1){
            res=(res*base)%mod;
        }
        base=(base*base)%mod;
        exp /=2;
    }
    return res;
}

std::vector<int> Rsa(const std::string& mes,int e,int n){
    std::vector<int> MesASCII;
    int num;
    for(char c:mes){
        num=static_cast<int>(c);
        MesASCII.push_back(PowNum(num,e,n));
    }
    return MesASCII;
}

std::string DeRsa(const std::vector<int>& mes,int d,int n){
    std::string MesASCII;
    int num;
    for(int c:mes){
        num=PowNum(c,d,n);
        MesASCII+=static_cast<char>(num);
    }
    return MesASCII;
}

int main(){
    std::string message;
    std::getline(cin,message);
    int e,d,n;
    cout<<"Your message:"<<message<<"\n";
    generateKey(e,d,n);
    cout<<"e:"<<e<<"\n"<<"d:"<<d<<"\n"<<"n:"<<n;
    std::vector<int> mess=Rsa(message,e,n);
    cout<<"\nAfter Rsa:\n";
    for(int c:mess){
        cout<<c<<" ";
    }
    std::string DeRsaMes=DeRsa(mess,d,n);
    cout<<"\nAfter DeRsa:\n"<<DeRsaMes;
    return 0;
}