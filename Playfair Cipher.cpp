#include<bits/stdc++.h>

using namespace std;

#define SIZE 100

void toLowerCase(char plainT[], int ps)
{
    int i;
    for (i = 0; i < ps; i++) {
        if (plainT[i] > 64 && plainT[i] < 91)
            plainT[i] += 32;
    }
}

int Spaces(char* plainT, int ps)
{
    int i, count = 0;
    for (i = 0; i < ps; i++)
        if (plainT[i] != ' ')
            plainT[count++] = plainT[i];
    plainT[count] = '\0';
    return count;
}

void KeyTable(char key[], int ks, char keyT[5][5])
{
    int i, j, flag = 0, *dicty;

    dicty = (int*)calloc(26, sizeof(int));
    for (i = 0; i < ks; i++) {
        if (key[i] != 'j')
            dicty[key[i] - 97] = 2;
    }

    dicty['j' - 97] = 1;

    i = 0;
    j = 0;

    for (int k = 0; k < ks; k++) {
        if (dicty[key[k] - 97] == 2) {
            dicty[key[k] - 97] -= 1;
            keyT[i][j] = key[k];
            j++;
            if (j == 5) {
                i++;
                j = 0;
            }
        }
    }

    for (int k = 0; k < 26; k++) {
        if (dicty[k] == 0) {
            keyT[i][j] = (char)(k + 97);
            j++;
            if (j == 5) {
                i++;
                j = 0;
            }
        }
    }
}

void search(char keyT[5][5], char a, char b, int arr[])
{
    if (a == 'j')
        a = 'i';
    else if (b == 'j')
        b = 'i';

    for (int i = 0; i < 5; i++) {

        for (int j = 0; j < 5; j++) {

            if (keyT[i][j] == a) {
                arr[0] = i;
                arr[1] = j;
            }
            else if (keyT[i][j] == b) {
                arr[2] = i;
                arr[3] = j;
            }
        }
    }
}

int mod5(int a) { return (a % 5); }

int prepare(char str[], int ptrs)
{
    if (ptrs % 2 != 0) {
        str[ptrs++] = 'x';
        str[ptrs] = '\0';
    }
    return ptrs;
}

void encrypt(char str[], char keyT[5][5], int ps)
{
    int  a[4];

    for (int i = 0; i < ps; i += 2) {

        search(keyT, str[i], str[i + 1], a);

        if (a[0] == a[2]) {
            str[i] = keyT[a[0]][mod5(a[1] + 1)];
            str[i + 1] = keyT[a[0]][mod5(a[3] + 1)];


        }
        else if (a[1] == a[3]) {
            str[i] = keyT[mod5(a[0] + 1)][a[1]];
            str[i + 1] = keyT[mod5(a[2] + 1)][a[1]];

        }
        else {
            str[i] = keyT[a[0]][a[3]];
            str[i + 1] = keyT[a[2]][a[1]];


        }
    }
}


void decrypt(char str[], char keyT[5][5], int ps)
{
    int i, a[4];
    for (i = 0; i < ps; i += 2) {

        search(keyT, str[i], str[i + 1], a);

        if (a[0] == a[2]) {
            str[i] = keyT[a[0]][mod5(a[1] + 4)];
            str[i + 1] = keyT[a[0]][mod5(a[3] + 4)];


        }
        else if (a[1] == a[3]) {
            str[i] = keyT[mod5(a[0] + 4)][a[1]];
            str[i + 1] = keyT[mod5(a[2] + 4)][a[1]];

        }
        else {
            str[i] = keyT[a[0]][a[3]];
            str[i + 1] = keyT[a[2]][a[1]];
            
        }
    }
}

void encryption(char str[], char key[])
{
    char ps, ks, keyT[5][5];

    
    ks = strlen(key);
    ks = Spaces(key, ks);
    toLowerCase(key, ks);
    ps = strlen(str);
    toLowerCase(str, ps);
    ps = Spaces(str, ps);
    ps = prepare(str, ps);
    KeyTable(key, ks, keyT);
    encrypt(str, keyT, ps);
}


void decryption(char str[], char key[])
{
    char ps, ks, keyT[5][5];

    ks = strlen(key);
    ks = Spaces(key, ks);
    toLowerCase(key, ks);
 
    ps = strlen(str);
    ps = Spaces(str, ps);

    KeyTable(key, ks, keyT);

    decrypt(str, keyT, ps);
}



int main()
{
    char str[SIZE], key[SIZE];
    //FILE *p = NULL;
    //p = fopen("playfair.txt","r+");
    //fgets(key,9,p);
    string Key;
    cin>>Key;
    strcpy(key, Key.c_str()); 
    cout<<"Key :"<<key<<endl;

    string myText,temp;
    
    ifstream MyReadFile("playfair.txt");
    stringstream stream;
    stream << MyReadFile.rdbuf();
    myText = stream.str();

    strcpy(str, myText.c_str()); 
    // cout<<"Enter the plainT Text :";
    // cin.getline(str,100);
    

    encryption(str, key);

    cout<<"Encrypted text: "<<str<<endl;

    ofstream fout("outputPF.txt");
    fout<<str<<"\t";
    

    decryption(str, key);

    cout<<"Decrypted text: "<<str<<endl;
    fout<<str<<"\t";
    
    fout.close();

    return 0;
}
