#ifndef DIGRAPH_H
#define DIGRAPH_H

#include<queue>
#include<vector>
#include<unordered_map>
#include<iostream>
using namespace std;

class Digraph{

	class node{
	      public:
	      vector<int> from;
	      vector<int> to;
	};

        std::unordered_map<int, node> nmap;

	int Ancestor(int& v, int& w, unordered_map<int, bool>& checked, int& length){

		vector<vector<int>> tos;  // structure:  distance from v --> same distance in the same vector
		vector<vector<vector<int>>> froms;  // structure: distance from v --> from the same ancestor --> same distance same ancestor
                froms.resize(1);
		if(v==w) return  v; 
		else {
		     tos.push_back(nmap[v].to);
                     froms.at(0).push_back(nmap[v].from);
		} 

		unordered_map<int, int> amap;
		amap[0]=v;

                int mom_size=1;
                
		int ans=-999;
                bool conti = true;
                while(conti){
		     vector<int> tmp_to;
		     vector<vector<int>> tmp_from;
                     conti=false;
                     int mom=0;
		     for(vector<int> is:froms.at(length)){
			vector<int> tmp;
			for(int i:is){
			   if(i==w){
		             ans = amap[mom];
			     break;
		           }
			   if(checked[i]) continue;
			   checked[i] = true;
			   if(nmap[i].from.size()!=0) conti=true;
			   tmp.insert(tmp.end(),nmap[i].from.begin(), nmap[i].from.end());
		        }
			if(ans>0) break;
			tmp_from.push_back(tmp);
			++mom;
		     }
		     if(ans>0) break;

                     for(int i:tos.at(length)){                
		        if(i==w) {    
			   ans=i;
			   break;
			}
			if(checked[i]) continue;        
			checked[i]=true;       
			if(nmap[i].to.size()!=0 || nmap[i].from.size()!=0 ) conti=true;
			tmp_to.insert(tmp_to.end(), nmap[i].to.begin(), nmap[i].to.end());
			tmp_from.push_back(nmap[i].from);
			
			amap[mom_size]=i;
			++mom_size;
		     }
		     tos.push_back(tmp_to); 
	             froms.push_back(tmp_from);
		     if(ans>0) break;
		     length++;
		}
		return ans;
        }
	int Length(int& v, int& w, unordered_map<int, bool>& checked, int length){
            return 1;
        }
	public:
	void Add(int index, vector<int> tos){
	     if(nmap.find(index)!=nmap.end()){
	       for(int i:tos) nmap[index].to.push_back(i);
	     }
	     else{
	       node n;
	       n.to=tos;
	       nmap[index] = n;
	     }

	     for(auto i:tos){
                if(nmap.find(i)!=nmap.end()) nmap[i].from.push_back(index);
		else{
	          node n;
		  n.from.push_back(index);
                  nmap[i] = n; 
	        }
	     }
	}
	int Length(int v, int w){
            unordered_map<int, bool> checked;
	    int length=0;
	    int ans = Ancestor(v, w, checked, length);
            return length+1;
	};
	int Ancestor(int& v, int& w){
            unordered_map<int, bool> checked;
	    int length=0; 
            return Ancestor(v, w, checked,length); 
	}
};



#endif
