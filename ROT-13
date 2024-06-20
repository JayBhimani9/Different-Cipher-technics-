 //ROT-13 using C++

#include<bits/stdc++.h>
using namespace std;

int main() {

    string myText;


    ifstream inFile;
    inFile.open("FileName.txt");
    stringstream strStream;
    strStream << inFile.rdbuf();
    myText = strStream.str();

    cout << "Input text is : " << myText;

    int ceaserKey=13;
    
    cout << endl;
    //cout << "The ceaser Key between 0 and 25 : ";
    //cin >> ceaserKey;

    string ecypherTxt;
    
    int n = myText.length();
    for(int i = 0; i < n; i++) {
        if((myText[i]>='a' && myText[i]<='z')){
            int val;
            val = ((myText[i]-'a'+ceaserKey)%26 + 'a');
            ecypherTxt.push_back((char)val);
        }
        else if((myText[i]>='A' && myText[i]<='Z')){
            int val;
            val = ((myText[i]-'A'+ceaserKey)%26 + 'A');
            ecypherTxt.push_back((char)val);
        }
        else ecypherTxt.push_back(myText[i]);
    }

    cout << "The encrpyted text is : " << ecypherTxt << endl;

    string decypherTxt;
    

    for(int i = 0; i < n; i++) {
        if((ecypherTxt[i]>='a' && ecypherTxt[i]<='z')){
            int val;
            val = ((ecypherTxt[i]-'a'-ceaserKey+26)%26 + 'a');
            decypherTxt.push_back((char)val);
        }
        else if((ecypherTxt[i]>='A' && ecypherTxt[i]<='Z')){
            int val;
            val = ((ecypherTxt[i]-'A'-ceaserKey+26)%26 + 'A');
            decypherTxt.push_back((char)val);
        }
        else decypherTxt.push_back(ecypherTxt[i]);
    }

    cout << "The decrpyted text is : " << decypherTxt << endl;
    
}
