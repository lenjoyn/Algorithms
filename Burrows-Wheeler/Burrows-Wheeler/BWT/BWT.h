#ifndef BWT_H
#define BWT_H
#include<vector>
#include<memory>
#include<iostream>
#include<unordered_map>
#include<algorithm>
#include<sstream>
#include<boost/format.hpp>

using boost::format;
using namespace std;
class BWT{


    class CSA{
         vector<string> csarray;
         string original;
         int len;
         uint32_t one;
        
         public:
         CSA(){}
         void Initialise(string s){
              original = s;
              len = s.length();
              vector<vector<char>> tmp;
              tmp.resize(len, vector<char>(len));

              //construct the cs array
              for(int i_char=0; i_char<len; ++i_char){
                  char c=s.at(i_char);

                  for(int n_shift=0; n_shift<len; ++n_shift){
                     int k= i_char-n_shift;
                     if(k<0) k+=len;
                     tmp[n_shift][k]=c;
                  }                    
              }

              //convert arrays to string for easy manipulation
              for(auto str:tmp){
                 string s(str.begin(), str.end());
                 csarray.push_back(s);
              }
         }

         string get_shifted(int i){
               return csarray[i];
         }

         void Print(){

              for(auto array:csarray){
                 cout<<array<<endl;
              }
         }

         uint32_t Sort(){

             sort(csarray.begin(), csarray.end(), less<string>());
             for(one=0; one<len; ++one){
                if(csarray[one] == original) break;
             }
             return one;
          }

          string outLast(){

                 string out;
                 for(auto s: csarray){
                    out+=s[len-1];
                 }
                 return out;
          }
    };

    CSA csa;
    int original;
    string last_column;

    class Ref{

       vector<int> pos;
       int now;
       public:
       Ref():now(-1){}

       void add(int& i){
            pos.push_back(i);
       }
 
       int get(){
           ++now;
           return pos[now];
       }
               
    };
    public:

    BWT(){};
    void encode(stringstream& data){
         
         string target;
         data>>target;
         csa.Initialise(target);
         uint32_t original = csa.Sort();
         target = csa.outLast();
         //csa.Print();
         data.clear();
         data.str("");
         data<<format("%1% %2%") %original %target;
    }

    void decode(stringstream& data){
 
         uint32_t original;
         string target;
         data>>original>>target;
         unordered_map<char, Ref> last;

         //facility for next building
         for(int i=0; i<target.length(); ++i){
         //   cout<<target[i]<<endl;
            last[target[i]].add(i);
         }          

         vector<char> sorted(target.begin(),target.end());
         sort(sorted.begin(),sorted.end(), less<char>());
         vector<int> next;

         //build next array
         for(int i=0; i<target.length(); ++i){
            next.push_back(last[sorted[i]].get());
         }

         int p = original;
 
         //construct the original string
         string output="";
         do{
           output+=target[next[original]];
           original = next[original];
         }while(p!=original);
         data.clear();
         data.str("");
         data<<output;
    }


};
#endif
