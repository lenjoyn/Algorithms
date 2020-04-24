#include<iostream>
#include"BoggleBoard/BoggleBoard.h"
#include"Tries/Tries.h"

void LoadDict(char* dict, Tries& tri ){
    
     ifstream inFile;
     inFile.open(dict);
     string line;

     while(getline(inFile, line)){
           tri.put(line);
     }  
}

int score(unordered_map<string, bool> words){

    int count = 0;

    for(unordered_map<string, bool>::iterator it=words.begin(); it!=words.end();it++){

        int leng = (it->first).length();
    
        if(leng<3) continue;
        if(leng==3 || leng ==4) ++count;
        if(leng==5) count+=2;
        if(leng==6) count+=3;
        if(leng==7) count+=5;
        if(leng>7)  count+=11;
    }
    return count;
}

int main(int argc, char* argv[]){


   Tries tri;
   LoadDict(argv[1], tri);

  // create the board
  // generate boards     
   if(argc==2){
     int i=0;
     while(i<100){

         BoggleBoard b=BoggleBoard();
         b.setDict(tri);
         unordered_map<string, bool> words = b.validWords();
         int sc=score(words);
         b.Print();
         
         cout<<"total score of this board is "<<sc<<"\n\n";
         ++i;
     }
   }
  //Load an existing board
   else if(argc>2){

     string boardFile = argv[2];
     BoggleBoard b = BoggleBoard(boardFile);
     b.setDict(tri);
     unordered_map<string, bool> words = b.validWords();
     int sc=score(words);
     b.Print();

     cout<<"total score of this board is "<<sc<<"\n\n";

   }
    
  


   return 0;
}
