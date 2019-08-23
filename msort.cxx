#include<iostream>
using namespace std;

vector<int> msort (vector<int> a, int lower, int upper) {

  int sz=1;
  int size=upper-lower+1;

  while(sz<upper-lower+1){

       vector<int> temp;
       int i=lower;
       int j=i+sz;
       int mid=j;
       while(temp.size()<size){
             
            if((j==mid+sz && i<mid)||(j>=upper&&i<upper)) {
              temp.push_back(a[i]);
              i++;
              continue;
            }

            else if(i==mid && j<mid+sz){
                 temp.push_back(a[j]);
                 j++;
                 continue;
            }
            else if(j==mid+sz && i==mid){
                 i=j;
                 j=i+sz;
                 mid=j;
            }
            else if(a.at(i)<=a.at(j)){
                 temp.push_back(a[i]);
                 i++;
                 continue;
            }
            else if(a.at(j)<a.at(i)){
               temp.push_back(a[j]);
               j++;
               continue;
            }
       }
       sz = sz*2;
       a= temp;
  }


  return a;
}

void run(vector<int> a){

     vector<int> b = msort(a,3,6);
     for(auto p:a){
        std::cout<<p<<" ";
     }
     std::cout<<std::endl;

     for(auto p:b){
        std::cout<<p<<" ";
     }
     std::cout<<std::endl;
    
    
}

