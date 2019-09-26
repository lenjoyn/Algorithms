#include<PQ.h>
#include<stdlib.h>
#include<Shuffle.h>
using namespace std;

class Board{
public:
      Board(std::vector<int> &in_content):  //constructor
      ham(0),man(0),zero(-1){
           content = &in_content;
           edge = sqrt(in_content.size());
           hamming();     
           manhattan();   
      } 

      Board(std::vector<int> &in_content, int empty):  //constructor
      ham(0),man(0),zero(empty){
           content = &in_content;
           edge = sqrt(in_content.size());
           hamming();
           manhattan();
      }

      ~Board(){                             //destructor
            Delete();
      }

      void Delete(){                        //delete this object
            //delete content;
            content=NULL;
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


      void PrintBoard(){
           for(int i=0;i<content->size();i++){
              cout<<content->at(i);
              if((i+1)%edge==0) cout<<endl;
           }
           cout<<endl;
      }
 
      /*Board MakeNewBoard(int nz){
         
         vector<int> nv= *content;
         swap(nv[nz],nv[zero]);
         Board nb =Board(nv, nz);
         return nb; 
      }*/
      int ham;
      int man;
      int zero;
      std::vector<int>* content;
private:
      int edge;

      void hamming(){
          int size=sqrt(content->size());

          for(int i=0; i<content->size(); i++){

             int x1=(content->at(i)-1)%size+1;
             int y1=(content->at(i)-1)/size+1;

             int x2=i%size+1;
             int y2=i/size+1;

             //printf("(%d,%d) (%d,%d) (%d,%d)\n",content->at(i),i+1,x1,y1,x2,y2);
             ham += fabs(x1-x2)+fabs(y1-y2);
          }
      }
 
      void manhattan(){
           for(int i=0; i<content->size(); i++)   if(content->at(i)-1!=i) man++;
      }
};

bool compare(vector<Board>* b, int i, int j){

     if(b->at(i).ham < b->at(j).ham) return 1;
     else if(b->at(i).ham > b->at(j).ham) return 0;
     else if(b->at(i).man < b->at(j).man) return 1;
     else if(b->at(i).man > b->at(j).man) return 0;
     return 0;
}

typedef PQ<Board, compare> priority_q;

int main(){

      vector<int> test={1,2,3,4,5,6,7,8,0};
      shuffle<int>(test);
      Board b = Board(test);
      b.PrintBoard();
      int last = -1;

      priority_q bq=priority_q();
      bq.Insert(b);
        vector<int> n =b.FindNeighbour();
        for(int i=0;i<n.size(); i++){
           if(n.at(i)==last) continue;
           vector<int> nv(*b.content);
           swap(nv[n[i]],nv[b.zero]);

           Board nb=Board(nv,n[i]);
       //    nb.PrintBoard();
           bq.Insert(nb);
       //    nb.PrintBoard();

        }
       bq.a->at(0).PrintBoard();
       cout<<endl;
       Board t = bq.delRoot();
       t.PrintBoard(); 
       return 0;
}
