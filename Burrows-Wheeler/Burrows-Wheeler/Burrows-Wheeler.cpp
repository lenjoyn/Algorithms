#include<string>
#include"BWT/BWT.h"
#include"MoF/MoF.h"
#include"Hff_alg/Hff_alg.h"
#include<fstream> 
#include<iostream>
#include<sstream>
using namespace std;

void Output(vector<bool> out){

     ofstream outfile("test.bin", ios::out | ios::binary);
     copy(out.begin(), out.end(), std::ostreambuf_iterator<char>(outfile));

}


void Input(vector<bool>& in){

  ifstream infile ("test.bin", ifstream::binary);
  in.insert(in.end(), (std::istreambuf_iterator<char>(infile)),
                       std::istreambuf_iterator<char>());

}
int main(int argc, char* argv[]){


    BWT bwt;
    MoF mof;
    Hff_alg hff;
    stringstream data;
    data<<"SIFdi13#dj";
    cout<<data.str()<<endl;
    bwt.encode(data);
    cout<<data.str()<<endl;
    mof.encode(data);
    cout<<data.str()<<endl;    
    vector<bool> output = hff.encode(data);
    Output(output);


    vector<bool> input;
    Input(input);
    stringstream decoded;

    Hff_alg hff2;
    hff2.decode(decoded, input);    
    cout<<decoded.str()<<endl;
    mof.decode(decoded);
    cout<<decoded.str()<<endl;
    bwt.decode(decoded);
    cout<<decoded.str()<<endl;     
    return 0;
}
