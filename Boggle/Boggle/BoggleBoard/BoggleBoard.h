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


      void Print(){

           for(int y=0; y<y_size; ++y){
              for(int x=0; x<x_size; ++x){
                 if(board[y][x]!='Q') cout << format("%3s") % board[y][x] ;
                 else cout << format("%3s") % "Qu" ;
              }
              cout<<"\n";
           }
      }

};
#endif
