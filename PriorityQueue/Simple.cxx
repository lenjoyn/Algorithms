#include<PQ.h>
#include<stdlib.h>
#include<Shuffle.h>
using namespace std;

class Board{
public:
      
      Board(std::vector<int> &in_content,int empty):  //constructor
      zero(empty),id(1),ham(0){
           content = &in_content;
           edge = sqrt(in_content.size());
           hamming();
      }



      ~Board(){                             //destructor
            Delete();
      }

      void Delete(){                        //delete this object
            //delete content;
            content=NULL;
      }


      void PrintBoard(){
           cout<<"Zero is "<<zero<<", ham is "<<ham<<" size is "<<content->size()<<endl;
           for(int i=0;i<content->size();i++){
              cout<<content->at(i);
              if((i+1)%edge==0) cout<<endl;
           }
      }

      vector<int> FindNeighbour(){

             vector<int> neighbours;
             if(zero==-1){
               for(zero=0; ;zero++) if(content->at(zero)==0) break;
             }

             //move up
             if(zero-edge>0) neighbours.push_back(zero-edge);
             if(zero+edge<content->size()) neighbours.push_back(zero+edge);
             if((zero+1)%edge!=0) neighbours.push_back(zero+1);
             if((zero+1)%edge!=1) neighbours.push_back(zero-1);
             return neighbours;
      }


      vector<int>* content;  
      int id,ham,zero;
private:
      int edge;

      void hamming(){
          int size=sqrt(content->size());

          for(int i=0; i<content->size(); i++){

             int x1=(content->at(i)-1)%size+1;
             int y1=(content->at(i)-1)/size+1;

             int x2=i%size+1;
             int y2=i/size+1;

             ham += fabs(x1-x2)+fabs(y1-y2);
          }
      }

};


bool compare(vector<Board>* b, int i, int j){
     return  b->at(i).ham<b->at(j).ham;
}

typedef PQ<Board, compare> priority_q;


int main(){
      vector<int> test={1,2,3,4,5,6,7,8,0};
      shuffle<int>(test);
      Board b=Board(test,-1);
      b.PrintBoard(); 
      
      priority_q bq=priority_q();
      //bq.Insert(b);
   
      vector<int> n=b.FindNeighbour();
      /*for(int i=1; i<3;i++){
         shuffle<int>(test);
         Board c = Board(test,i);
         c.PrintBoard();
         bq.Insert(c);
      }*/
      int last =-1;
      for(auto i: n){
        vector<int> nv(*b.content);
      //  cout<<"testtest::"<<i<<" "<<b.zero<<endl;
        last = b.zero;
        std::swap(nv[1],nv[last]); 
        Board nb=Board(nv,1);
        cout<<"====none======"<<endl;
        nb.PrintBoard();
        cout<<"=============="<<endl;
        bq.Insert(nb);
      cout<<"====Inside bq====="<<endl;
      bq.a->at(0).PrintBoard();
      cout<<"======================="<<endl;

      }
      cout<<"====before delRoot====="<<endl;
      bq.a->at(0).PrintBoard();    
      cout<<"======================="<<endl;  
      Board t= bq.delRoot();
      cout<<"final::"<<endl;
      t.PrintBoard();
      return 0;
 
}
