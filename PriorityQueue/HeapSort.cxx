#include<PQ.h>

using namespace std;


bool compare(vector<int>* a, int i, int j){

     if(a->at(i)>a->at(j)) return 1;
     return 0;
}

typedef PQ<int, compare> priority_q;


void hsort(vector<int> &a_in){



   priority_q pq=priority_q();
   int size = a_in.size();

   
   while(a_in.size()>0){
     cout<<a_in[a_in.size()-1]<<" "<<endl;
     pq.Insert(a_in[a_in.size()-1]);
     a_in.pop_back();
   }
   cout<<endl;

   while(a_in.size()!=size){
     a_in.push_back(pq.delRoot());
   }
   
}

void run_hsort(){

     vector<int> a={1,9,15,8,3,2,7,21,6};

     hsort(a);
     
     int i=0;
     while(i!=a.size()){

         cout<<a[i]<<" ";
         i++;
     }
     cout<<endl;

}
