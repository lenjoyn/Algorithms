#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <math.h>
/* run this program using the console pauser or add your own getch, system("pause") or input loop */
//construct the matrix
using namespace std;
vector<int> roots;
vector<int> trees;
vector<int> grids;

void construction(int size, int valid){
	
	// build up the matrix
	int n_grids=size*size+2;
	
	grids.assign(n_grids,0);
	grids[0]=1;
	grids[n_grids-1]=1;
	
	int vacancies = 0;
	// make the vacant sites
        while(vacancies<valid){
    	    int clean= rand()%(n_grids+1);
    	    if(clean==0) continue;
    	
	    if(grids[clean]!=1){
			grids[clean]=1;
			vacancies++;
	    }
	}
}

void printV(vector<int> v){

     int border = sqrt(v.size()-2);
     //cout<<v[0]<<endl;
     for(int i=0; i<v.size();i++){

        printf("%3d ",v[i]);
        if(i%border==0) printf("\n");
     }
     //cout<<endl;
}


void unit(int i, int j){

        //cout<<i<<"("<<roots[i]<<") "<<j<<"("<<roots[j]<<") ";
	//merging the two trees;
	if(trees[roots[i]]>=trees[roots[j]]){
		int n_items=trees[roots[j]];
                trees[roots[j]]=0;
		//path compression
	        roots[roots[j]]=roots[i];	
		while(roots[j]!=j){
                     roots[j] = roots[roots[j]];
                     j=roots[j];
                }
                trees[roots[i]]=n_items+ trees[roots[i]];

         	
	}
 	else{
                int n_items=trees[roots[i]];		
                trees[roots[j]]=0;
		//path compression
                roots[roots[i]]=roots[j];
                while(roots[i]!=i){
                     roots[i] = roots[roots[i]];
                     i=roots[i];
                }
                trees[roots[j]]=n_items+trees[roots[j]];
	}
       
}




void link(vector<int> grid){
	int n_sites = grid.size();
	int border = sqrt(n_sites-2);
    
	roots.push_back(0);
	trees.push_back(1);
        int last_size=0;
	//initialization
	for(int isite=1; isite<=n_sites-2; isite++){
		if(isite<=border && grid[isite]==1){
                        trees[0]++;
			roots.push_back(0);
			trees.push_back(0);
		}
		else if((n_sites-isite-2)<border && grid[isite]==1){
			roots.push_back(n_sites-1);
			trees.push_back(0);
                        last_size++;
		}
		else{
			roots.push_back(isite);
			trees.push_back(1);
		}
	}
        roots.push_back(grids.size()-1);
        trees.push_back(last_size);   

 //       printV(trees);
	
	//run the links
	for(int isite=border+1; isite<n_sites;isite++){
		if(grids[isite]!=1) continue;


  		if(grids[isite-border]==1) unit(isite-border,isite);
		if((isite)%border==1) continue;
		if(grids[isite-1]==1) unit(isite-1, isite);
                
		
	}
    //    printV(roots);	
}

int root(int i){


    while(roots[i]!=i){
      roots[i]=roots[roots[i]];
      i=roots[i];
    }
    return(roots[i]);
}

int percolation(/*int argc, char** argv*/) {
	
    for(int j=1; j<390; j++){
       float count=0;
       for(int i=0; i<1000; i++){
          construction(20,j);
	  link(grids);
          bool tong = (root(0)==root(grids.size()-1));
          if(tong) count++;
          grids.clear();
          roots.clear();
          trees.clear();
        }
        cout<<j<<" "<<count/1000<<endl;
    }
    return 0;
}


