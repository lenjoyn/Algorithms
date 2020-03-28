#ifndef MAXFLOW_H
#define MAXFLOW_H
#include<deque>
#include<vector>
#include<memory>
#include<string>
#include<unordered_map>

using namespace std;

class Node{

    string name;
    vector<shared_ptr<Node>> to;
    shared_ptr<Node> from;

    unordered_map<string, int> residual;
    unordered_map<string, int> flow;
public:
    Node(string& n){
      this->name = n;
    };

    void addNext(shared_ptr<Node> n, int cap){
       to.push_back(n);
       residual[n->name]=cap;
       flow[n->name]=0;
    }
   
    void addFlow(string n, int& f){
       residual[n]-=f;
       flow[n]+=f;
       cout<<name<<" to "<<n<<" "<<residual[n]<<endl;
    }

    string Name(){ return name; }
    vector<shared_ptr<Node>> To(){ return to; }
    int Residual(string s){ return residual[s]; }
    void From(shared_ptr<Node> n){ from = n; }
    shared_ptr<Node> From(){ return from; }

    ~Node(){};
};

class team{

public:
    string name;
    int wins;
    int losses;
    int remain;
    vector<int> matches;

    team():name(""),wins(0),losses(0){
    };
    ~team(){};

};

class Maxflow{
   
   unordered_map<string, shared_ptr<Node>> nmap;
   void BFS(string& s, string& t){

       unordered_map<string, int> length;
       length[s] = 0;
       deque<shared_ptr<Node>> q;
       q.push_front(nmap[s]);

       while(q.size()!=0){
            shared_ptr<Node> v=q.front();
            q.pop_front();
            for(auto w:v->To()){
               //check whether this edge is still available
               if(!v->Residual(w->Name())>0) continue;
               //check whether this is the shortest path to w, or skip w
               if(length.find(w->Name())!=length.end() && length[w->Name()]<= length[v->Name()]) continue;
               else length[w->Name()]=length[v->Name()]+1;

               w->From(v);
               q.push_back(w);
            }
       }
   }

   int Fill(string& s, string& t){

       shared_ptr<Node> v = nmap[t];
       int bottleneck = INT8_MAX;
       cout<<"filling"<<endl;
       while(v->Name()!=s){
            bottleneck = min( v->From()->Residual(v->Name()), bottleneck);
            v=v->From();
       }
       v = nmap[t]; 
       while(v->Name()!=s){
            v->From()->addFlow(v->Name(), bottleneck);
            v=v->From();
       }
       return bottleneck;
   }

   bool hasAug(string s, string& t){
        shared_ptr<Node> v = nmap[s];
        bool reached = false;
        for(auto w:v->To()){
           if(!v->Residual(w->Name())>0) continue;
           cout<<v->Name()<<" "<<w->Name()<<" "<<v->Residual(w->Name())<<endl;
           if(w->Name()==t){
             reached = true;
             break;
           }
           reached = hasAug(w->Name(),t);
           if(reached) break;
        }
        return reached;
   }   
public:
   Maxflow(int exclu, unordered_map<int,team> teams){

       string s="s";
       nmap["s"] = make_shared<Node>(s);
       string t="t";
       nmap["t"] = make_shared<Node>(t);

       int upper = teams[exclu].wins+teams[exclu].remain;
       //create the directed graph
       for(int iteam=0; iteam<teams.size(); ++iteam){
 
          if(iteam==exclu) continue;
          if(nmap.find(teams[iteam].name)==nmap.end())  nmap[teams[iteam].name] = make_shared<Node>(teams[iteam].name);
          nmap[teams[iteam].name]->addNext(nmap[t], upper-teams[iteam].wins);         // edge from team to t

          string nodeName;
          for(int imatch=iteam+1; imatch<teams[iteam].matches.size(); ++imatch){
             if(imatch==exclu) continue;    
 
             nodeName = teams[iteam].name+"_To_"+teams[imatch].name;
             nmap[nodeName] = make_shared<Node>(nodeName);
             nmap["s"]->addNext(nmap[nodeName], teams[iteam].matches[imatch]);        // edge from s to match
             if(nmap.find(teams[imatch].name)==nmap.end()) nmap[teams[imatch].name] = make_shared<Node>(teams[imatch].name);
             nmap[nodeName]->addNext(nmap[teams[iteam].name], INT8_MAX);              // edge from match to team 1 
             nmap[nodeName]->addNext(nmap[teams[imatch].name], INT8_MAX);             // edge from match to team 2 
          } 
       }
   }

   int Flow(string s, string t){
       int flow = 0;
       unordered_map<string, bool> checked;
       cout<<"=================="<<endl;
       while(hasAug(s, t)){
            cout<<"=====   Hello  ========="<<endl; 
            BFS(s, t);
            flow+= Fill(s, t); 
       }
       return flow;    
   }
   
   ~Maxflow(){};
};

#endif
