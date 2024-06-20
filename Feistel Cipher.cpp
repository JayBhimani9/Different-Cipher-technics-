#include<bits/stdc++.h>

using  namespace std;

void printBinary(char c) {
    for (int i = 7; i >= 0; --i) {
        cout << ((c & (1 << i))? '1' : '0');
    }
}

int main()
{
    string message;

    ifstream MyRead("message.txt");
    stringstream stream;
    stream << MyRead.rdbuf();
    message = stream.str();

    cout<<"The message :"<<message<<endl;

    string mykey, temp;
    ifstream MyReadFile("fc.txt");
    while (getline (MyReadFile, temp)) {
        //cout << "Input text is : " << temp<<endl;
        mykey+=temp;
    }

    char k1,k2;
    k1=mykey[0];
    k2=mykey[1];
    char l1,r1,l2,r2,l3,r3;

    char fun1,fun2;
    string enc;

    cout<<"Binary of Plain Text :  ";
    for (int i = 0; i < message.length(); i+=2)
    {
        l1=message[i];
        r1=message[i+1];

        for (int i = 0; i < message.length(); i += 2) {
        printBinary(l1);
        cout<< " - ";
        printBinary(r1);
        cout<< " - ";
        }

        fun1=r1^k1;

        r2=l1^fun1;
        l2=r1;

        fun2=r2^k2;

        r3=l2^fun2;
        l3=r2;

        enc+=l3;
        enc+=r3;


    }
    cout<<"\n"<<"\n";
    cout<<"The encryted text is :"<<enc<<endl;

    string dec;

    for (int i = 0; i < enc.length(); i+=2)
    {
        l1=enc[i];
        r1=enc[i+1];

        fun1=l1^k2;

        l2=r1^fun1;
        r2=l1;

        fun2=l2^k1;

        l3=r2^fun2;
        r3=l2;

        dec+=l3;
        dec+=r3;


    }
    cout<<"The decryted text is :"<<dec<<endl;

}
