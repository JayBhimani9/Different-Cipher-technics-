#include <bits/stdc++.h>

using namespace std;

int main(){

    string mykey, temp;
    ifstream MyReadFile("otp.txt");
    while (getline (MyReadFile, temp)) {
        cout << "key text is : " << temp<<endl;
        mykey+=temp;
    }
    cout<<"\n";

    string message;

    ifstream MyRead("1.txt");
    stringstream stream;
    stream << MyRead.rdbuf();
    message = stream.str();

    cout<<"The message is : "<<message<<"\n";

    if(message.length()>mykey.length())
    cout<<"Message is bigger the key";
    else{
    for (int i = 0; i < message.length(); i++)
    {
        message[i] = message[i] ^ mykey[i];
    }

    cout<<"Encrypted message: "<<message<<"\n";

    for (int i = 0; i < message.length(); i++)
    {
        message[i] = message[i] ^ mykey[i];
    }

    cout<<"Decrypted message: "<<message;
    }

    return 0;
}
