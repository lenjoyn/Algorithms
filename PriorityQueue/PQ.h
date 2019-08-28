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
         while(!comp(a, k,2*(k+1)-1) || !comp(a, k,2*(k+1))){

            int p = comp(a,2*(k+1)-1,2*(k+1))?2*(k+1)-1:2*(k+1);
            std::swap(a->at(p),a->at(k));
            k=p;
            if(k>a->size()-1) break; 
             
         } 
         return out;
    }


    void Insert(T in){
         a->push_back(in);
         if(a->size()<1) return; 
         int k= a->size()-1;
         if(a->size()<2) return;
         while(comp(a,k,(k+1)/2-1)){
            std::swap(a->at(k),a->at(k+1/2-1));
            k=k/2-1;
            if(k==0) break;
         }
    }

//private:
    vector<T>* a;    
};
#endif
