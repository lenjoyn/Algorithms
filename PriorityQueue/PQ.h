#ifndef PQ_H
#define PQ_H
#include <algorithm>
#include <iostream>
#include <vector>
//This is not just a practice of priority queue but also a practice to use template and follow rule of three of C++
//https://stackoverflow.com/questions/4172722/what-is-the-rule-of-three
using namespace std;
template <typename T, bool (*comp)(vector<T>* ,int, int)>
class PQ{
public:

    PQ():a(){     //constructor
        a=new std::vector<T>();
    }       

    ~PQ(){    //destructor
         delete a;
         a=NULL;
    }  


    T delRoot(){

         //if(a->size()<1) return NULL;
         T out=  a->at(0);
              cout<<"==========delRoot 1============="<<endl;
              a->at(0).PrintBoard();
              cout<<"===================================="<<endl;

         swap(a->at(0),a->at(a->size()-1));
              cout<<"==========delRoot 2============="<<endl;
              a->at(0).PrintBoard();
              cout<<"===================================="<<endl;

         a->pop_back();
              cout<<"==========delRoot 3============="<<endl;
              a->at(0).PrintBoard();
              cout<<"===================================="<<endl;

         int k=0;
         sink(k);
         return out;
    }


    void Insert(T &in){
         a->push_back(in);
         int k= a->size()-1;
         if(k<1) return;
         swim(k);
    }


    void PrintSize(){
         std::cout<<a->size()<<std::endl;
    }

    vector<T>* a;
private:

    void swim(int &k){
         int p;
         while(comp(a,k,(k+1)/2-1)){
            p = (k+1)/2-1;
            swap(a->at(k),a->at(p));
            k=(k+1)/2-1;
            if(k==0) break;
         }

    }

    void sink(int &k){
         while(2*k+1<a->size()){
            int p=2*k+1;
            if(p+2>a->size()){
              if(comp(a,k,p)) break;
              cout<<"==========Inside siking 1============="<<endl;
              a->at(k).PrintBoard();
              a->at(p).PrintBoard();
              cout<<"===================================="<<endl;

	      swap(a->at(k), a->at(p));
              cout<<"==========Inside siking 2============="<<endl;
              a->at(k).PrintBoard();
              a->at(p).PrintBoard();
              cout<<"===================================="<<endl;

              k=p;
            }
            else if(!comp(a,k,p)||!comp(a,k,p+1)){
              cout<<"==========Inside siking 3============="<<endl;
              p = comp(a,p,p+1)?p : p+1;
              a->at(k).PrintBoard();
              a->at(p).PrintBoard();
              cout<<"===================================="<<endl;
              k=p;
              swap(a->at(k), a->at(p));
              cout<<"==========Inside siking 4============="<<endl;
              a->at(k).PrintBoard();
              a->at(p).PrintBoard();
              cout<<"===================================="<<endl;

            }
            else break;
         }
    }
};
#endif
