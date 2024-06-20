#include<bits/stdc++.h>
using namespace std;

long long binpow(long long a, long long b, long long m) {
    a %= m;
    long long res = 1;
    while (b > 0) {
        if (b & 1)
            res = res * a % m;
        a = a * a % m;
        b >>= 1;
    }
    return res;
}



int main() {

    string myText;

    ifstream inFile;
    inFile.open("rsa.txt");
    stringstream strStream;
    strStream << inFile.rdbuf();
    myText = strStream.str();


    int p,q,e,n,fn,d;
    strStream >> p >> q >> e ;
    string s;
    
    strStream >> s;
    cout<<"Plain Text : "<<s<<endl;
    // cout<<p <<" "<<q<<" "<<e<<" "<<m<<endl;
    
    n=p*q;
    fn=(p-1)*(q-1);
    if(__gcd(fn,e)!=1)
        cout<<"e is not Co-Prime "<<endl;
    else
    {
        cout<<"e is Co-Prime"<<endl;
        int Q,A,B,R,T1,T2,T;
        d=0;
        A=fn;
        B=e;
        T1=0;
        T2=1;
        while(B!=0)
            {
                Q=A/B;
                R=A%B;
                T=T1-(T2*Q);

                A=B;
                B=R;
                T1=T2;
                T2=T;

            }

            if(T1<0)
                d=(fn-T1);
            else
                d=T1;

            //Encryption
            //cout<<endl<<"key : "<<d<<endl;
            int le=0;
            le=s.length();
            int c[le],plain[le];
        for(int i=0;i<s.length();i++)
        {
            int m=0;
            m=s[i]-64;
            //cout<<endl<<"Enter the message : ";
            //cin>>m;
            cout<<m<<endl;
            long long int power=0;
            

            c[i]=binpow(m,e,n);

            

            // power=pow(c[i],d);

            plain[i]=binpow(c[i],d,n);

            //cout<<c[i]<<"  "<<plain[i]<<endl<<endl;
            
        }
        cout<<"encrypted message : ";
        for (int i = 0; i < le; i++)
        {
                cout<<char(c[i]+64);
                
        }
        cout<<endl<<"decrypted message : ";
        for (int i = 0; i < le; i++)
        {
                cout<<char(plain[i]+64);
                
        }
        

    }
    

    return 0;
}
