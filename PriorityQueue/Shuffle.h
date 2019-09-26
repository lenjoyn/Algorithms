#ifndef SHUFFLE_H
#define SHUFFLE_H

#include<random>

template <typename T>
void shuffle(std::vector<T> &a){


  std::random_device rd;
  std::mt19937 mt(rd());
  std::uniform_int_distribution<> dis(1,a.size());

  int j;
  for(int i=0;i<a.size();i++){
 
     j=dis(mt)%(a.size()-i);
     j=j+i;

     swap(a[i],a[j]);
  }
}
#endif 
