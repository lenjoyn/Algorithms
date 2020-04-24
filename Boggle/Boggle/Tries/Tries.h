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

          void remove(){
             exist = 0;
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
          bool end(){
               return exist;
          }
 
     };

    shared_ptr<Node> root = make_shared<Node>('0');

    void put(shared_ptr<Node> node, string& word, int order){
    
       ++order;
       if(order==word.length()){
         node->touch();
         return;
       }

       if(!node->char_exist(word[order]))  node->add_next(word[order]);

       shared_ptr<Node> n = node->go_next(word[order]);       
       put(n, word, order);
    }
  
    void remove(shared_ptr<Node> node, string& word, int order){
       ++order;
       if(order==word.length()){
          node->remove();
          return;
       }

       if(!node->char_exist(word[order]))  return;

       shared_ptr<Node> n = node->go_next(word[order]);
       remove(n, word, order);
    }

    int get(shared_ptr<Node> node, string& word, int order){
       ++order;
       if(order==word.length() ) return node->end();
       if(!node->char_exist(word[order]))  return -1;

       shared_ptr<Node> n = node->go_next(word[order]);
       return get(n, word, order);
    }

  public:
    Tries(){};

    void put(string word){
         put(root, word, -1);
    }

    void remove(string word){
         remove(root, word,-1);
    }   
 
    int get(string word){
        return get(root, word, -1);
    }
};
#endif
