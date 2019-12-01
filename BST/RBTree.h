#ifndef RBTREE_H
#define RBTREE_H
#include"kdTree.h"
#include<vector>
#include<iostream>
#include<memory>
//Red-Black tree for a general use
using namespace std;


template <typename Key, typename Value, int (*compare)(Key key1, Key key2)>
class RBTree{

     class Node{
	  public:
             Node(Key in_key, Value in_val){
                 key = in_key;
		 val = in_val;
		 red=1;
	     }
	     int value() {return val;}
	     bool isRed() {return red;}
             shared_ptr<Node> right;
	     shared_ptr<Node> left;
	     Key key;
	     Value val;
	     bool red;
     };
     
     shared_ptr<Node> root;
     vector<Key> keys;

     //private methods
     shared_ptr<Node> Put(Key key, Value val, shared_ptr<Node> node, int level){

	  if(node==NULL) return make_shared<Node>(key, val);   
	  int comp = compare(key, node->key);

	  if(comp == 0) node->Val = val;
	  else if(comp  <0) node->left= Put(key, val, node->left, level++);
	  else node->right = Put(key, val, node->right, level++);

	  if(node->left!=NULL && node->right!=NULL){
	    if(node->left->isRed() && node->right->isRed()) node = colourSwap(node);
          }
	  if(node->right!=NULL){
	    if(node->right->isRed()) node = leftRotate(node);
	  }
	  if(node->left!=NULL){
            if(node->left->left!=NULL){
	      if(node->left->isRed() && node->left->left->isRed()) node=rightRotate(node);
            }
          }
          return node; 
     }

     //   Red-Black tree process to balance the tree structure
     shared_ptr<Node> colourSwap(Node* node){
	   node->red = true;
	   node->left->red=false;
	   node->right->red=false;
	   return node;
     }

     shared_ptr<Node> leftRotate(shared_ptr<Node> node){
	  shared_ptr<Node> tmp = node;
          node = node->right;
	  node->red = tmp->red;
	  tmp->right = node->left;
	  node->left = tmp;
          node->left->red = true;
	  return node;
     }

     shared_ptr<Node> rightRotata(shared_ptr<Node> node){
	  shared_ptr<Node> tmp = node;
          node = node->left;
	  node->red = tmp->red;
	  tmp->left = node->right;
	  node->right = tmp;
          node->right->red = true;
	  return node;
     }

     int count(shared_ptr<Node> node){
          
         if(node==NULL) return 0;
	  
         return 1+count(node->left)+count(node->right);
     }

     shared_ptr<Node> Search(Key key, shared_ptr<Node> node){

	      while(node!=NULL && compare(key, node->key)!=0){

		   int comp = compare(key, node->key);
		   if(comp>0) node=node->right;
		   if(comp<0) node=node->left;
	      }
	      return node;
     }

     shared_ptr<Node> Delete(Key key, shared_ptr<Node> node){

	     if(node==NULL) return NULL;

	     int comp = compare(key, node->key);

	     if(comp>0){
		 node->right = Delete(key, node->right);
             }
	     else if(comp<0){
		 node->left = Delete(key, node->left);
             }
	     else if(comp==0){

		 shared_ptr<Node> tmp = NULL;
		 shared_ptr<Node> tmp2= NULL;

		 if(node->left!=NULL){
		   if(node->left->right==NULL)   return node->left;
	           else{
		     for(tmp = node->left; ; tmp=tmp->right){
			if(tmp->right->right==NULL) break;
		     }
		     tmp2 = tmp->right;
		     tmp->right = tmp->right->left;
	           }  
	         }

		 else if(node->right!=NULL){
	           if(node->right->left==NULL) return node->right;
		   else{
		     for(tmp =node->right;;tmp=tmp->left){
			if(tmp->left->left==NULL) break;
		     }
		     tmp2=tmp->lelft;
		     tmp->left = tmp->left->right;
		   } 
	         }
		 else return NULL;

                 tmp2->left = node->left;
		 tmp2->right= node->right;
		 node=NULL;
		 node=tmp2;
		 return node;
	     }
     }

     shared_ptr<Node> Floor(Key key, shared_ptr<Node> node){
	     shared_ptr<Node> min=NULL;

	     while(node!=NULL){
                  int comp=compare(key, node->key);
		  
		  if(comp<1){
	            if(min==NULL) min =node;
		    else if(compared(min->key, node->key)>1)  max = node;
		    node=node->right;
	          }
		  else if(comp<1) node=node->left;
		  else{
			  min=node->release();
	          }
             }
	     return min;
     }
     
     shared_ptr<Node> Ceiling(Key key, shared_ptr<Node> node){
	     shared_ptr<Node> max=NULL;

	     while(node!=NULL){
                  int comp=compare(key, node->key);
		  
		  if(comp>1){
	            if(max==NULL) max=node;
		    else if(compared(max->key, node->key)>1)  max = node;
		    node=node->right;
	          }
		  else if(comp<1) node=node->left;
		  else{
			  max=node->release();
	          }
             }
	     return max;
     }

     void  Inverse(shared_ptr<Node> node){
           if(node==NULL) return;
	   Inverse(node->left);
	   keys.push_back(node->key);
	   Inverse(node->right);
     }

     
  public:
     // add a new node or modeify a node
     void Put(Key key, Value val){
	   if(root==NULL) {
		   root = make_shared<Node>(key, val);
		   return;
	   }
	   Put(key, val, root, 1);
     }
     //remove a node if existing in the binary tree
     void  Delete(Key keys){ 
	   Delete(keys, root); 
     }  
     //find the value for a given key
     Value Search(Key key){
	  return Search(key, root)->Val;
     }
     //find keys within a given key range
     vector<Key> Range(Key lo, Key hi){
	     vector<Key> keys;
	     Range(lo, hi, root, keys);
	     return keys;
     }
     //find the value with key at or above (closest) the given key value
     Value Floor(Key key){
	     shared_ptr<Node> node= Floor(key, root);
	     if(node==NULL) return 0;
	     else return node->val;
     }
     //find the value with key at or below (closest) the given key value
     Value Ceiling(Key key){
	    shared_ptr<Node> node = Ceiling(key,root);
	    if(node==NULL) return 0;
	    else return node->val;
     }
     //order the keys from small to big
     vector<Key> Inverse(){
            if(keys.size()!=0) return keys;
	    Inverse(root);
	    return keys; 
     }
     //find the number of keys below the given key
     int Rank(Key key){
	    shared_ptr<Node> node=Ceiling(key, root);
	    if(compare(key,node->key)==0) return count(node);
	    else return count(node->left);
     }
     //return the number of nodes in this binary tree
     int Size(){
	     return count(root);
     }
};

#endif
