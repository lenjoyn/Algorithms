#include<unordered_map>
#include<algorithm>
#include<iostream>
#include<fstream>
#include<sstream>
#include"Maxflow/Maxflow.h"
#include<vector>
using namespace std;

int main(int argv, char* argc[] ){

    if(argv<2) return 0;
    
    ifstream inFile;
    inFile.open(argc[1]);

    int n_teams=0;
    unordered_map<int,team> Tmap;
    int team_order=0;   

    string line;   
    string dummy; 
    while(getline(inFile, line)){
         istringstream iss(line);

         if(team_order>n_teams){
           cerr<<"there should not be so many teams\n";
           return 0;
         }

         if(n_teams==0){
            iss>>n_teams;
            if(iss.fail()){
              cerr<<"The input format is wrong. No int in the first line\n";
              return 0;
            }
            iss>>dummy;
            if(!iss.eof()){
              cerr<<"The input format is wrong. The first line has more than one number\n";
              return 0; 
            }
            continue;
         }

         else{
            Tmap[team_order]=team();
            iss>>Tmap[team_order].name>>Tmap[team_order].wins>>Tmap[team_order].losses>>Tmap[team_order].remain;
            if(iss.fail()){
              cerr<<"The input format of team "<<team_order<<" is wrong\n";
              return 0;
            }

            Tmap[team_order].matches.resize(n_teams); 
            int i_team=0;
            while(i_team<n_teams){
                iss>>Tmap[team_order].matches[i_team];
                if(iss.fail()){
                  cerr<<"The input format of team "<<team_order<<" is wrong\n";
                  return 0;
                }
                ++i_team;
            }
            iss>>dummy;
            if(!iss.eof()){
              cerr<<"The input format of team "<<team_order<<" is wrong\n";
              return 0;
            }
           
         }
       //  cout<<team_order<<" "<<Tmap[team_order].name<<" "<<Tmap[team_order].matches.size()<<endl;
         ++team_order;
    }

    Maxflow max(1, Tmap);
    int flow = max.Flow("s","t"); 
    cout<<flow<<endl;   
    return 0;
}

