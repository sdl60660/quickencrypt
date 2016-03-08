//
//  main.cpp
//  Quick Encrypt
//
//  Created by Sam Learner on 8/1/15.
//  Copyright © 2015 Sam Learner. All rights reserved.
//

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;

string Encrypt(string, string);
string Decrypt(string, string);
int KeySum(string);

int main(int argc, char* argv[]) {
    
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
            cout << "Encrypting File..." << endl;
            //output = Encrypt(buffer.str(), eKey);
            output = Encrypt(Encrypt(Encrypt(buffer.str(), eKey), eKey), eKey);
            outFile << output;
            cout << "Done! File encrypted." << endl;
            
        } else if (strncmp(argv[1], "Decrypt", 7) == 0) {
            cout << "Deciphering File..." << endl;
            //output = Decrypt(buffer.str(),eKey);
            output = Decrypt(Decrypt(Decrypt(buffer.str(), eKey), eKey), eKey);
            outFile << output;
            cout << "Done! File deciphered." << endl;
        }
        
        inFile.close();
        outFile.close();
        
    } 
    
    
    return 0;
}





string Decrypt (string out, string key) {
    
    char tempoutput[out.length()];
    int i;
    string undo;
    
    int keySum = KeySum(key);
    
    for (i = 0; i < out.length(); i++) {
        
        char tempchar;
        
        if (out[i] == 0)
            tempchar = 0;
        else if (out[i] == 9 || out[i] == 10 || out[i] == 11) {
            tempchar = (out[i] - 9);
            int mod = key[(i + keySum + key.length()) % key.length()] % 3;
            tempchar -= mod;
            if (tempchar < 0) {
                tempchar += 12;
            } else {
                tempchar += 9;
            }
            
        } else {
            if (((out[i] - 32) - key[(i + keySum + key.length()) % key.length()]) >= 0)
                tempchar = (((out[i] - 32) - key[(i + keySum + key.length()) % key.length()]) + 32);
            else if (((out[i] - 32) - key[(i + keySum + key.length()) % key.length()]) < 0) {
                if (((out[i] - 32) - key[(i + keySum + key.length()) % key.length()]) >= (-95))
                    tempchar = (((out[i] - 32) - key[(i + keySum + key.length()) % key.length()]) + 32 + (95 * 1));
                else
                    tempchar = (((out[i] - 32) - key[(i + keySum + key.length()) % key.length()]) + 32 + (95 * 2));
            }
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
        
        if(in[i] == 0) {
            tempchar = 0;
            tempinput[i] = tempchar;
        } else if (in[i] == 9 || in[i] == 10 || in[i] == 11) {
            tempchar = (in[i] - 9);
            int mod = key[(i + keySum + key.length()) % key.length()] % 3;
            tempchar += mod;
            tempchar = tempchar % 3;
            tempchar += 9;
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