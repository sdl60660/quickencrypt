#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;

string Encrypt(string, string);
string Decrypt(string, string);
int KeySum(string);

int main(int argc, char* argv[]) {

    //cout << endl;

    if (argc != 5) {
        cout << "Usage: <function> <Encrypt/Decrypt> <infile name> <outfile name> <encryption key>" << endl;
    } else {
        string IFile = argv[2];
        string OFile = argv[3];
        string eKey = argv[4];

        ifstream inFile;
        ofstream outFile;

        string output;

        inFile.open(IFile);
        outFile.open(OFile);

        stringstream buffer;
        buffer << inFile.rdbuf();

        if (strncmp(argv[1], "Encrypt", 7) == 0) {
           // cout << "Encrypting File..." << endl;
            //output = Encrypt(buffer.str(), eKey);
            output = Encrypt(Encrypt(Encrypt(buffer.str(), eKey), eKey), eKey);
            outFile << output;
           // cout << "Done! File encrypted." << endl;
            
        } else if (strncmp(argv[1], "Decrypt", 7) == 0) {
           // cout << "Deciphering File..." << endl;
            //output = Decrypt(buffer.str(),eKey);
            output = Decrypt(Decrypt(Decrypt(buffer.str(), eKey), eKey), eKey);
            outFile << output;
           // cout << "Done! File deciphered." << endl;
        }

        inFile.close();
        outFile.close();
        //cout << endl;

    } 

    return 0;
}





string Decrypt (string out, string key) {
    string undo;
    char tempoutput[out.length()];
    int i;

    int keySum = KeySum(key);
    
    for (i = 0; i < out.length(); i++) {
        
        char tempchar;
        
        if (out[i] == 0)
            tempchar = 0;
        else if (out[i] == 14 || out[i] == 15 || out[i] == 16) {
     
            tempchar = (out[i] - 5);
                        
        } else {
            if (((out[i] - 32) - key[(i + keySum + key.length()) % key.length()]) >= 0)
                tempchar = (((out[i] - 32) - key[(i + keySum + key.length()) % key.length()]) + 32);
            else if (((out[i] - 32) - key[(i + keySum + key.length()) % key.length()]) >= (-95))
                tempchar = (((out[i] - 32) - key[(i + keySum + key.length()) % key.length()]) + 32 + (95 * 1));
            else
                tempchar = (((out[i] - 32) - key[(i + keySum + key.length()) % key.length()]) + 32 + (95 * 2));
        }
        
        tempoutput[i] = tempchar;
    }
    
    undo = tempoutput;
    return undo;
};

string Encrypt(string in, string key) {
    string output;
    char tempinput[(in.length())];
    int i;
    
    int keySum = KeySum(key);
    
    for (i = 0; i < in.length(); i++) {
        char tempchar;
        if (in[i] == \xe2\x80\x94)
        	cout << mdash << endl;
        if(in[i] == 0) {
            tempchar = 0;
            tempinput[i] = tempchar;
        } else if (in[i] == 9 || in[i] == 10 || in[i] == 11) {
            tempchar = (in[i] + 5);
            tempinput[i] = tempchar;
            
        } else {
            tempchar = ((((in[i] - 32) + key[(i + keySum + key.length()) % key.length()]) % 95) + 32);
            tempinput[i] = tempchar;
        }
    }
    output = tempinput;
    return output;
};

int KeySum(string key) {
    int keySum = 0;
    int k;
    
    for (k = 0; k < key.length(); k++)
    {
        keySum = keySum + key[k];
    }
    
    return keySum;
}