#include <fstream>
#include <algorithm>
#include <vector>
#include <string>
#include <iostream>
#include <cstring>
#include <bits/stdc++.h>

using namespace std;

vector<char> transmission1;
vector<char> transmission2;
vector<char> mcode1;
vector<char> mcode2;
vector<char> mcode3;
vector<int> posiciones;
vector<int> longitudes;
vector<int> LPS(string a, int aL);

void KMP(string a, string b){
    int aL = a.length();
    int bL = b.length();
    vector<int> lps = LPS(a, aL);

    int i = 0;
    int j = 0;
    while (i < bL) {
        if (a[j] == b[i]) {
            j++;
            i++;
        }
        if (j == aL) {
            cout<<"True "<< i - j<<endl;
            return;
        }
        else if (i < bL && a[j] != b[i]) {
            if (j != 0)
                j = lps[j - 1];
            else
                i = i + 1;
        }
    }
    cout<<"False"<<endl;
}

vector<int> LPS(string a, int aL){
    int len = 0;
    vector<int> lps(aL);

    lps[0] = 0;
    int i = 1;
    while (i < aL) {
        if (a[i] == a[len]) {
            len++;
            lps[i] = len;
            i++;
        } else{
            if (len != 0)
                len = lps[len - 1];
            else{
                lps[i] = 0;
                i++;
            }
        }
    }
    return lps;
}

void impresionParte2(int p){
	int fin = (p*2)+1;
	int ini = fin -1;
	cout<<posiciones[ini]+1<<" "<<posiciones[fin]+1<<endl;
}

void palindromeSearch(string input, int j, int k) {
    for (; j >= 0 && k < input.length(); --j, ++k) {
        if (input[j] != input[k]) {
            break;
        }
	    longitudes.push_back(input.substr(j, k - j + 1).size());
	    posiciones.push_back(j);
	    posiciones.push_back(k-j+1);
    }
}

void palindromeSearch(string input) {
    posiciones.clear();
	longitudes.clear();
    for (int i = 0; i < input.length(); ++i) {
        palindromeSearch(input, i - 1, i + 1);
        palindromeSearch(input, i, i + 1);
    }
}

void maxPalindrome(){
	int longitudMax = 0;
	for(int i = 0; i < longitudes.size(); i++){
		if(longitudes[i] >= longitudMax){
			longitudMax = longitudes[i];
		}
	}
    cout<<endl<<"Tamaño maximo: "<<longitudMax<<endl;
	for(int i = 0; i < longitudes.size(); i++){
		if(longitudes[i] == longitudMax){
			impresionParte2(i);
		}
	}
}

void rellenaVector(char caracter, string name){
	if(isalpha(caracter) || isdigit(caracter)){
		if(name == "transmission1.txt"){
			transmission1.push_back(caracter);
		} else if(name == "transmission2.txt"){
			transmission2.push_back(caracter);
		} else if(name == "mcode1.txt"){
			mcode1.push_back(caracter);
		} else if(name == "mcode2.txt"){
			mcode2.push_back(caracter);
		} else {
			mcode3.push_back(caracter);
		}
	}
}

void lector(string name){
	ifstream archivo;
	char caracter;

	archivo = ifstream(name);
	if(! archivo.is_open()){
		cout<<"Error no se encontró el archivo."<<endl<<"Verifique el nombre de su archivo"<<endl;
	} else {
		while(!archivo.eof()){
			rellenaVector(caracter,name);
			archivo.get(caracter);
		}
	}
	archivo.close();
}

void longestCommonSubstring(string a, string b){
    int aL = a.length();
    int bL = b.length();

    vector<vector<int>> lcs(aL+1,vector<int>(bL + 1, 0));

    int startBiggest = -1;
    int endBiggest = -1;
    int lcsMax = 0;

    for (int i = 1; i <= aL; i++) {
        for(int j = 1; j <= bL; j++){
            if(a[i-1] == b[j-1]){
                lcs[i][j] = lcs[i-1][j-1]+1;

                if (lcs[i][j] > lcsMax) {
                    lcsMax = lcs[i][j];
                    endBiggest = i - 1;
                }
            } else {
                lcs[i][j] = 0;
            }
        }
    }

    if (endBiggest != -1) {
        startBiggest = endBiggest - lcsMax + 1;
    }
    cout<< startBiggest <<" "<< endBiggest;
}

int main() {
    lector("transmission1.txt");
    lector("transmission2.txt");
    lector("mcode1.txt");
    lector("mcode2.txt");
    lector("mcode3.txt");

    string transmission1String(transmission1.begin(), transmission1.end());
    string transmission2String(transmission2.begin(), transmission2.end());
    string mcode1String(mcode1.begin() + 1, mcode1.end());
    string mcode2String(mcode2.begin() + 1, mcode2.end());
    string mcode3String(mcode3.begin() + 1, mcode3.end());

    cout<<endl<<"Parte 1"<<endl;
    KMP(mcode1String,transmission1String);
    KMP(mcode2String,transmission1String);
    KMP(mcode3String,transmission1String);
    KMP(mcode1String,transmission2String);
    KMP(mcode2String,transmission2String);
    KMP(mcode3String,transmission2String);

    cout<<endl<<"Parte 2"<<endl;
    palindromeSearch(transmission1String);
	maxPalindrome();
    palindromeSearch(transmission2String);
	maxPalindrome();

    cout<<endl<<"Parte 3"<<endl;
    longestCommonSubstring(transmission1String,transmission2String);
}
