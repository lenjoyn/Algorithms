#ifndef PQ_H
#define PQ_H
//This is not just a practice of priority queue but also a practice to use template and follow rule of three of C++
//https://stackoverflow.com/questions/4172722/what-is-the-rule-of-three

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

         if(a->size()<1) return 0;
         T out=  a->at(0);
         a->at(0) = a->at(a->size()-1);
         a->pop_back();

         int k=0;
         sink(k);
         return out;
    }


    void Insert(T in){
         a->push_back(in);
         int k= a->size()-1;
         if(k<1) return;
         swim(k);
    }



private:
    void swim(int k){
         while(comp(a,k,(k+1)/2-1)){
            std::swap(a->at(k),a->at((k+1)/2-1));
            k=(k+1)/2-1;
            if(k==0) break;
         }

    }
    void sink(int k){
         while(2*k+1<a->size()){
            int p=2*k+1;
            if(p+2>a->size()){
              if(comp(a,k,p)) break;
              swap(a->at(k), a->at(p));
              k=p;
            }
            else if(!comp(a,k,p)||!comp(a,k,p+1)){
              p = comp(a,p,p+1)?p : p+1;
              swap(a->at(k), a->at(p));
              k=p;
            }
            else break;
         }
    }
    vector<T>* a;    
};
#endif
