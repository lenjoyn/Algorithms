#inclde "Digraph.h"

int Digraph::Ancestor(int& v, int& w){

    std::dequeue<int> wl;
    int ans=-999;
    for(auto i:nmap[v].to){
        if(!Trace(i,w, xxv)) continue; 
	ans =i;
    }
    return ans;
}

bool Digraph::Trace(int& v, int &w, int &from){

	if(v==w) return true;
	if(v==from) return false;
 
	bool p=false;
	for(auto i:nmap[v].from){
	   p=Trace(i, w, v);
	   if(p) break;
	}
	return p;
}
