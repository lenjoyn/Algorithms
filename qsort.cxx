#include<iostream>
using namespace std;

int partition(vector<int>& a, int low, int high){

  int ref=a[low];
  low++;

  while(low<=high){

    if(a[low]<ref) low++;

    else if(a[high]<ref){
         swap(a[low],a[high]);
         high--;
    }
    else high --;
  }    

  return high;
}

int partition3way(vector<int> &a, int low, int high, int &lt, int &gt){

    lt=low;
    gt=low;
    low++;

    while(low<=high){

      if(a[low]<a[lt]){
        swap(a[low],a[lt]);
        low++;
        lt++;
        gt++;
      }

      else if(a[low]==a[lt]) {
        low++;
        gt++;
      }
     
      else if(a[low]>a[lt]){

        if(a[high]>a[lt]) high--;

        else if(a[high]==a[lt]){
          swap(a[low],a[high]);
          gt++;
          low++;
        }

        else if(a[high]<a[lt]){
          swap(a[low],a[high]);
          high--;
        }
      }
    }
   
    return high;

}

vector<int> qsort3way (vector<int> a, int low, int high) {

  if(low>high) return a;
  int lt;
  int gt;
  int j=partition3way(a, low, high,lt, gt);


  if(lt-low>1)   a=qsort3way(a, low,lt-1);
  if(high-gt>1)  a=qsort3way(a, gt+1,high);
  return a;
}


vector<int> qsort (vector<int> a, int low, int high) {

  if(low>high) return a;

  int j=partition(a, low, high);
  swap(a[j],a[low]);

  if(j-low>1)  a=qsort(a, low,j-1);
  if(high-j>1) a=qsort(a, j+1,high);
  
  return a;
}

void run(vector<int> a){

     for(auto p:a){
        std::cout<<p<<" ";
     }
     std::cout<<std::endl;
     a=qsort3way(a,0,a.size()-1);
     for(auto p:a){
        std::cout<<p<<" ";
     }
     std::cout<<std::endl;
    
}

