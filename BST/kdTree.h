#ifndef KDTREE_H
#define KDTREE_H
#include<vector>
#include<iostream>
#include<memory>
#include<climits>
#include<math.h>
//kd-Tree building
using namespace std;


template <typename Key, typename Value, int (*p)(Key key1, Key key2)>
class kdTree{


     
     int compare(vector<Key> keys1, vector<Key> keys2, int level){
          if(keys1.size()!= keys2.size()) return false;

	  int out = 0;

	  for(int k=0; k<keys1.size(); ++k){
	     if(p(keys1[k], keys2[k])==0) continue;
	     out = 1; 
	     break;
          }
	  if(!out) return out;

	  if(p(keys1[level],keys2[level]>0)) return 1;
	  else return -1;
     }

     int compare_in(vector<Key> keys1, vector<Key> keys2){

	  int n=-999;
	  for(int k=0; k<keys1.size(); ++k){
             int comp=p(keys1[k], keys2[k]);
	     if(n!=-999 && n!=comp) break;
	     else n = comp;
	  }
	  return n;
     }
     class Node{

	  public:
             Node(vector<Key> in_keys, Value in_val){
                 keys = in_keys;
		 val = in_val;
		 red=1;
	     }
             shared_ptr<Node> right;
	     shared_ptr<Node> left;
	     vector<Key> keys;
	     Value val;
	     bool red;
     };

     
     shared_ptr<Node> root;
     int kd=-99999;
     //private methods
     shared_ptr<Node> Put(vector<Key>& keys, Value &val, shared_ptr<Node> node, int level, float& dist){

	  if(node==NULL) return make_shared<Node>(keys, val);   
	  int comp = compare(keys, node->keys, level%kd);

	  if(comp == 0) node->Val = val;
	  else if(comp  <0) node->left= Put(keys, val, node->left, ++level);
	  else node->right = Put(keys, val, node->right, ++level);

          return node; 
     }

     void Range(vector<Key> lo, vector<Key> hi, shared_ptr<Node> node, vector<vector<Key>> &keysets, int level){
	  if(node==NULL) return;

          int comp_lo = compare_in(lo,node->keys);
	  int comp_hi = compare_in(hi,node->keys);

	  if(comp_lo<=0 && comp_hi>=0) keysets.push_back(node->keys);  //points on edge are also counted

	  if(compare(lo, node->left->key)<0)  Range(lo, hi, node->left, keysets, ++level);
	  if(compare(lo, node->right->key)<0) Range(lo, hi, node->right,keysets, ++level);
     }

     float Distance(vector<Key> keys1, vector<Key> keys2){ 

	   int dist=0;

	   for(int k=0; k<keys1.size();++k)   dist += (keys1[k]-keys2[k])*(keys1[k]-keys2[k]);

	   return sqrt(dist);
     }
     void Closest(vector<Key> req, shared_ptr<Node> node, vector<Key>& closest, float& dist, int level){ 
          if(node==NULL) return;

	  int dis = Distance(node->keys, req);
	  if(dis<dist){
		  dist = dist;
		  closest = node;
          }
 
	  int lev = level%kd;
	  int comp = (req, node->keys, level);
	  if(comp==0) {
		  closest = node->keys;
		  return;
          }
	  else if(comp>0){
		  Closest(req, node->right, closest, dist, ++level);
                  if(fabs(node->keys[lev]-req[lev])<dist) Closest(req, node->left, closest, dist, ++level);
          }
	  else{
		  Closest(req, node->left, closest, dist, ++level);
		  if(fabs(node->keys[lev]-req[lev]<dist)) Closest(req, node->right, closest, dist, ++level);
          }

     }
  public:
     void Put(vector<Key> keys, Value val){
	   if(root==NULL) {
		   root = make_shared<Node>(keys, val);
		   kd = keys.size();
		   return;
	   }
	   if(keys.size()!=kd){
		   cout<<"the input keys are not compatible, please check the input\n";
           }
	   Put(keys, val, root, 0);
     }
 
     void  Delete(vector<Key> keys){ Delete(keys, root); }  
//     vector<Value> Keys(vector<Key>, vector<Key>);
     vector<Key> Closest(vector<Key> req){
	     vector<Key> closest;
	     int dist=INT_MAX;
	     Closest(req, root, closest, dist, 0);
             return closest;
     }
     vector<vector<Key>> Range(vector<Key> lo, vector<Key> hi){
	     vector<vector<Key>> keysets;
             Range(lo, hi, root, keysets,0);
	     return keysets;
     }
};

#endif
