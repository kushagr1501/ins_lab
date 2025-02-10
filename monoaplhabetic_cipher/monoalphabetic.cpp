#include<bits/stdc++.h>
using namespace std;

int main()
{
    map<char,char>encrypt;
    map<char,char>decrypt;

    encrypt['A']='Z';
    encrypt['B']='Y';
    encrypt['C']='X';
    encrypt['D']='W';
    encrypt['E']='V';
    encrypt['F']='U';
    encrypt['G']='T';
    encrypt['H']='S';
    encrypt['I']='R';
    encrypt['J']='Q';
    encrypt['K']='P';
    encrypt['L']='O';
    encrypt['M']='N';
    encrypt['N']='M';
    encrypt['O']='L';
    encrypt['P']='K';
    encrypt['Q']='J';
    encrypt['R']='I';
    encrypt['S']='H';
    encrypt['T']='G';
    encrypt['U']='F';
    encrypt['V']='E';
    encrypt['W']='D';
    encrypt['X']='C';
    encrypt['Y']='B';
    encrypt['Z']='A';

    for(auto pair :encrypt){
        decrypt[pair.second]=pair.first;
    }
    string plainText;

    cout<<"enter the message:"<<endl;
    getline(cin,plainText);


 string cipaer;
    for(char c:plainText){
        if(encrypt.count(c)!=0){
            cipaer+=encrypt[c];
        }else{
            cipaer+=c;
        }
    }

  cout<<"encrypted text is :"<<cipaer<<endl;


 string decryptText;
    for(char c:cipaer){
        if(decrypt.count(c)!=0){
            decryptText+=decrypt[c];
        }else{
            decryptText+=c;
        }
    }


    cout<<"decrypted text is :"<<decryptText;


    return 0;

}
