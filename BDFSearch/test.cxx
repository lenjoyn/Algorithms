#include "Digraph.h"

int main(){
 
	Digraph g;
        vector<int> v={1};
	g.Add(1,v);
	v={10};
	g.Add(4,v);
	g.Add(5,v);
	v={13};
	g.Add(10,v);
	g.Add(11,v);
	v={14};
	g.Add(13,v);
	g.Add(15,v);
	v={11,16,17};
	g.Add(9,v);
	v={15};
	g.Add(16,v);
	g.Add(13,v);
	v={17};
	g.Add(18,v);
	v={16};
	g.Add(17,v);
	int i=4;
	int j=16;
	cout<<g.Ancestor(i,j)<<" "<<g.Length(i,j)<<endl;
	return 0;
}
