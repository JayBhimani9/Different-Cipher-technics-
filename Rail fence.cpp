#include<bits/stdc++.h>

using namespace std;


int main()
{
    string myText, temp;
    ifstream MyReadFile("rf2.txt");
    while (getline (MyReadFile, temp)) {
        //cout << "Input text is : " << temp<<endl;
        myText+=temp;
    }

    cout<<myText<<endl;

    int s=myText.length();

    string ntext;

    //Spaces(myText,s);
    for(int i=0;i<s;i++)
    {
        if(myText[i]!=' ')
        {
            ntext+=myText[i];
        }
    }
    cout<<ntext<<endl;


    string newkey;
    cout<<"The Key word:";
    ifstream MyRead("message.txt");
    while (getline (MyRead, temp)) {
        //cout << "Input text is : " << temp<<endl;
        newkey+=temp;
    }
    int m=0;
    
    //cin>>newkey;
    int n=newkey.length();
    string sorted=newkey;

    sort(sorted.begin(),sorted.end());

    if(ntext.length()%n==0)
        m=ntext.length()/n;
    else
        m=1+ntext.length()/n;
    cout<<sorted<<endl;
    cout<<n<<m<<"\n";
    int k=0;
    char a[m][n];
    for(int i=0;i<m;i++)
    {
        for(int j=0;j<n;j++)
        {
            if(k!=ntext.length())
            {
                a[j][i]=ntext[k];
                k++;
            }
            else
            {
                a[j][i]='_';
                
            }
        }
    }

    for(int i=0;i<m;i++)
    {
        for(int j=0;j<n;j++)
        {
            cout<<a[j][i];
        }
        cout<<"\n";
    }
    string b;

    
}
