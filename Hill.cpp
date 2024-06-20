#include<bits/stdc++.h>


using namespace std;

ofstream fout("outputHC.txt");
float e[3][1], d[3][1], a[3][3], b[3][3], ms[3][1], m[3][3];

void displayMMes(float matrix[3][1], const string & name) {
    cout << name << " Matrix:\n";
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 1; j++) {
            cout << matrix[i][j] << " ";
        };
        cout << "\n";
    }
}

void displayMA(float matrix[3][3], const string & name) {
    cout << name << " Matrix:\n";
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            cout << matrix[i][j] << " ";
        }
        cout << "\n";
    }
}

void KeyM(const string & filename) {
    ifstream file(filename);

    if (file.is_open()) {
        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 3; j++) {
                file >> a[i][j];
                m[i][j] = a[i][j];
            }

        file.close();
    } else {
        cerr << "Unable to open file: " << filename << endl;
        exit(EXIT_FAILURE);
    }

    displayMA(a, "Key");
}

void KeyMessage() {
    string keyFilename;
    cout << "Enter the filename containing the key matrix: ";
    cin >> keyFilename;

    KeyM(keyFilename);

    char me[3];
    cout << "\nEnter a string of 3 letter(use A through Z): ";
	cin >> me;
	for (int i = 0; i < 3; i++)
		ms[i][0] = me[i] - 65;
    displayMMes(ms, "Message");
}
void encryp()
{
	int i, j, k;
	for (i = 0; i < 3; i++)
		for (j = 0; j < 1; j++)
			for (k = 0; k < 3; k++)
				e[i][j] +=  a[i][k] * ms[k][j];
	cout << "\nEncrypted string is: ";
	for (i = 0; i < 3; i++){
		cout << (char)(fmod(e[i][0], 26) + 65);
		fout<<(char)(fmod(e[i][0], 26) + 65);}
	fout<<"\n";
}
void inverse()
{
	int i, j, k;
	float p, q;
	for (i = 0; i < 3; i++)
		for (j = 0; j < 3; j++)
		{
			if (i == j)
				b[i][j] = 1;
			else
				b[i][j] = 0;
		}
	for (k = 0; k < 3; k++)
	{
		for (i = 0; i < 3; i++)
		{
			p = m[i][k];
			q = m[k][k];
			for (j = 0; j < 3; j++)
			{
				if (i != k)
				{
					m[i][j] = m[i][j] * q - p * m[k][j];
					b[i][j] = b[i][j] * q - p * b[k][j];
				}
			}
		}
	}
	for (i = 0; i < 3; i++)
		for (j = 0; j < 3; j++)
			b[i][j] = b[i][j] / m[i][i];
	cout << "\n\nInverse Matrix is:\n";
	for (i = 0; i < 3; i++)
	{
		for (j = 0; j < 3; j++)
			cout << b[i][j] << " ";
		cout << "\n";
	}
}
void decryp()
{
	int i, j, k;
	inverse();
	for (i = 0; i < 3; i++)
		for (j = 0; j < 1; j++)
			for (k = 0; k < 3; k++)
				d[i][j] += b[i][k] * e[k][j];
	cout << "\nDecrypted string is: ";
	for (i = 0; i < 3; i++){
		cout << (char)(fmod(d[i][0], 26) + 65);
		fout<<(char)(fmod(d[i][0], 26) + 65);}
	cout << "\n";
	fout<<"\n";
}
int main()
{
	KeyMessage();
	encryp();
	decryp();
	fout.close();
}
