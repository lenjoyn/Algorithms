#ifndef TRIES_H
#define TRIES_H
#include<vector>
#include<memory>
#include<string>
#include<unordered_map>

using namespace std;

class Tries{

     class Node{

          char key;
          unordered_map<char, shared_ptr<Node>> next;
          bool exist;

        public:
          Node(char k):key(k),exist(0){};

          void touch(){
             exist = 1;
          }

          bool char_exist(char c){
             if(next.find(c) == next.end()) return false;
             else return true;
          }

          void add_next(char c){
              shared_ptr<Node> n = make_shared<Node>(c);
              next[c] = n;
          }

          shared_ptr<Node> go_next(char c) {
               return next[c];
          }
     };

    shared_ptr<Node> root = make_shared<Node>('0');

    void put(shared_ptr<Node> node, string& word, int order){
    
       ++order;
       if(order==word.length()){
         node->touch();
         return;
       }

       if(node->char_exist(word[order]))  node->add_next(word[order]);
       shared_ptr<Node> n = node->go_next(word[order]);       
       put(n, word, order);
    }

  public:
     Tries(){};

     void put(string& word){
          put(root, word, -1);
     }   

};
#endif
