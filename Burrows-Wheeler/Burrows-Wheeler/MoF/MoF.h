#ifndef MOF_H
#define MOF_H
#include<iostream>
#include<deque>
#include<sstream>
using namespace std;


class MoF{

   deque<char> char_order;

   public:
   MoF(){
      for(int i=0; i<256; ++i)   char_order.push_back(char(i));
   }

   void encode(stringstream& data){

       string s;
       getline(data,s);
       data.clear();
       deque<char> encoder(char_order.begin(), char_order.end());
       
       string output;
       int pos;
       for(auto c:s){

          deque<char>::iterator  it=find_if(encoder.begin(), encoder.end(), 
                                   [&](char& ref)->bool{return ref==c;}   );
          pos=distance(encoder.begin(), it);
          encoder.erase(it);
          output+=(to_string(pos)+" ");
          encoder.push_front(c);
       }
       data.str("");
       data<<output;
   }

   void decode(stringstream& data){
       deque<char> decoder(char_order.begin(), char_order.end());
       string output;
       int p;
       while(data>>p){
          char c = decoder[p];
          output+=c;
          deque<char>::iterator  it=decoder.begin()+p;
          decoder.erase(it);
          decoder.push_front(c);
       }
       data.clear(); 
       data.str("");
       data<<output;
   }

};
#endif
