#ifndef HFF_ALG_H
#define HFF_ALG_H
#include<iostream>
#include<sstream>
#include<unordered_map>
#include<deque>
#include<queue>
#include<bitset>
#include<math.h>
class Hff_alg{

     class Node{

        shared_ptr<Node> left;
        shared_ptr<Node> right;
        int val;
       
        public:
        int count;
        Node(int i, int n):val(i),left(NULL), right(NULL),count(n){}
       
        bool setNode(shared_ptr<Node> n) { 

             if(left==NULL) left = n;
             else if(right==NULL) right= n;
             else return false;

             count+= n->count;
             return true;
        }
        void set(int v){val=v;}
        int get(){return val;}
        shared_ptr<Node> goLeft(){return left;}
        shared_ptr<Node> goRight(){return right;}
     };

     shared_ptr<Node> encoder_root;
     unordered_map<int, vector<bool>> encoder; 

     shared_ptr<Node> decoder_root = make_shared<Node>(-1, 0);
     

     void encoder_build(stringstream& data){

          unordered_map<int, int> count;

          int i;
          //count occurance of each letter
          while(data>>i){
             if(count.find(i)==count.end()) {
               count[i] = 1;
             } 
             else count[i]+=1;
          }
          //construct the priority queue
          auto comparator =  [&](shared_ptr<Node> n1, shared_ptr<Node> n2)->bool{return n1->count > n2->count;};
          priority_queue<shared_ptr<Node>, vector<shared_ptr<Node>>,decltype(comparator) > pq(comparator);

          for(unordered_map<int, int>::iterator it=count.begin(); it!=count.end(); ++it){
             shared_ptr<Node> n = make_shared<Node>(it->first, it->second);
             pq.push(n);         
          }

          //construct the trie
          shared_ptr<Node> n = make_shared<Node>(-1,0);
          while(pq.size()>0){

               shared_ptr<Node> next = pq.top();
               if(n->setNode(next))  pq.pop();
               else{
                 pq.push(n);
                 n = make_shared<Node>(-1,0); 
               }
          }
          encoder_root = n;
          vector<bool> bin;


          //build the hash from the trie
          encoder_keys(encoder_root, bin);
     }

     //Note: if there is only one character in the file, the tree would be messed up 
     void encoder_keys(shared_ptr<Node> node, vector<bool> bin){
          if(node == NULL) return;
          int val = node->get();
          if(val>=0){
            encoder[val] = bin;
            return;
          }

          vector<bool> bin1 = bin;
          bin1.push_back(false);
          encoder_keys(node->goLeft(),  bin1);
          
          vector<bool> bin2 = bin;
          bin2.push_back(true);
          encoder_keys(node->goRight(), bin2);
     }

     deque<bool> to8Bits(int i){

          deque<bool> out;
  
          int count=0;
          while(count<8){

              out.push_front(i%2);
              i=i/2;
              ++count;
          }
          return out;
     }

     void encoder_output(shared_ptr<Node> now, vector<bool>& trie){

          if(now==NULL) return;

          if(now->get()<0){
            trie.push_back(0);
            encoder_output(now->goLeft(), trie);
            encoder_output(now->goRight(), trie);
          }
          else{
            trie.push_back(1);
            deque<bool> bin = to8Bits(now->get());
            trie.insert(trie.end(), bin.begin(), bin.end()); 
            return;
          }

     }


     int bitsToInt(vector<bool>::iterator it){
         
         int out = 0;
         for(int order=7; order>=0; --order){
           
            it++;
            if(*it) out+=pow(2,order);
         }
         return out; 
     }

     vector<bool>::iterator decoder_build(shared_ptr<Node> node, vector<bool>::iterator it){
          if(*it){
            int value = bitsToInt(it);
            node->set(value);
            advance( it, 8 );
            return it;
          }
          else{
            shared_ptr<Node> l = make_shared<Node>(-1,0);
            node->setNode(l);
            it++;
            it = decoder_build(l, it);
            shared_ptr<Node> r = make_shared<Node>(-1,0);
            node->setNode(r);
            it++;
            it = decoder_build(r, it);
          }

          return it;
     }

     vector<bool>::iterator decoder(vector<bool>::iterator it, shared_ptr<Node> n, int& out){
         if(n->get()!=-1) {
           out = n->get();
           return it;
         }

         shared_ptr<Node> next;
         if(*it) next = n->goRight();
         else next = n->goLeft();
         
         ++it;
         return decoder(it, next, out);

     }

     public:
     Hff_alg(){}
     vector<bool> encode(stringstream& data){

          stringstream::pos_type pos = data.tellg();
          encoder_build(data);
          vector<bool> trie;
          encoder_output(encoder_root, trie);

          data.clear();
          data.seekg(data.beg);   //rewind data stream to the start
          int val;
          while(data>>val){
            trie.insert(trie.end(), encoder[val].begin(), encoder[val].end());
          }
          return trie;
     }

     void decode(stringstream& decoded, vector<bool> bin){
          vector<bool>::iterator it=decoder_build(decoder_root, bin.begin());
          ++it;

          while(distance(bin.begin(), it)<bin.size()){
             int out;
             it=decoder(it, decoder_root, out);
             decoded<<to_string(out)<<" ";
          }       

     }

};

#endif
