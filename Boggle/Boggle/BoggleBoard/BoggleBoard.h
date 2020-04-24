#ifndef BOGGLEBOARD_H
#define BOGGLEBOARD_H
#include<vector>
#include<iostream>
#include<boost/random/mersenne_twister.hpp>
#include<boost/random/uniform_int_distribution.hpp>
#include<boost/format.hpp>
#include<iostream>
#include<fstream>
#include<sstream>
#include"../Tries/Tries.h"

using namespace std;
using boost::format;

boost::random::mt19937 gen;
boost::random::uniform_int_distribution<> dist(1, 26);

class BoggleBoard{

   
      int x_size;
      int y_size;
      vector<vector<char>> board;
      Tries dict;
      void Board(int x_range, int y_range){
          x_size=x_range;
          y_size=y_range;

          for(int y=0; y<y_size; ++y){
             vector<char> row;
             for(int x=0; x<x_size; ++x){
                int i = dist(gen);
                char tmp=static_cast<char>('A' - 1 + i);
                row.push_back(tmp);
             }
             board.push_back(row);
          }
      }
   
      void Board(string filename){

           ifstream inFile;
           inFile.open(filename);  
           istringstream iss;
           string line;

           x_size = 0;
           y_size = 0;

           while(getline(inFile, line)){
                vector<char> row;
                iss.str(line);
                string letter;
                while(!iss.eof()){
                   if(x_size==0 && y_size==0){
                        iss>>x_size;
                        y_size=x_size;
                   }
                   else{
                       iss>>letter;
                       char c = letter[0];
                       row.push_back(c);
                   }
                }
                if(row.size()>0) board.push_back(row);
                iss.clear();
           }
      }

      void validWords(int x, int y, unordered_map<string,bool>& words, vector<vector<bool>> checked,string word){

           if(x==x_size||x<0) return;
           if(y==y_size||y<0) return;
           if(checked[y][x])  return;
           checked[y][x] = true;
           word+=board[y][x];
           if(board[y][x] =='Q') word+='U';
           int exist = dict.get(word);
           if(exist<0 ) return;
           if(exist==1 && words.find(word)==words.end()) words[word] = 1;

           validWords(x+1, y+1, words, checked, word);
           validWords(x+1, y, words, checked, word);
           validWords(x+1, y-1, words, checked, word);
           validWords(x, y+1, words, checked, word);
           validWords(x, y-1, words, checked, word);
           validWords(x-1, y+1, words, checked, word);
           validWords(x-1, y, words, checked, word);
           validWords(x-1, y-1, words, checked, word);
        
     }
     
   public:
      BoggleBoard(){
         Board(4,4); 
      }
      BoggleBoard(int x, int y){
         Board(x,y);
      }
      BoggleBoard(string filename){
         Board(filename);
      }
      void setDict(Tries& tri){
         dict = tri;
      }

      void Print(){

           for(int y=0; y<y_size; ++y){
              for(int x=0; x<x_size; ++x){
                 if(board[y][x]!='Q') cout << format("%3s") % board[y][x] ;
                 else cout << format("%3s") % "Qu" ;
              }
              cout<<"\n";
           }
      }

      unordered_map<string, bool> validWords(){
            
            unordered_map<string,bool> words;
            for(int y=0; y<y_size; ++y){
               for(int x=0; x<x_size; ++x){
                  vector<vector<bool>> checked(y_size, vector<bool> (x_size, 0));
                  validWords(x, y, words, checked, "");
               }
            }
            return words;
      }

};
#endif
