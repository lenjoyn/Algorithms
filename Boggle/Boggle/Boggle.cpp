#include<iostream>
#include"BoggleBoard/BoggleBoard.h"
//#include"Tries/Tries.h"

int main(int argc, char* argv[]){
     
   if(argc==1){
     int i=0;
     while(i<10){

         BoggleBoard b=BoggleBoard();
         b.Print();
         cout<<"\n\n";
         ++i;
     }
   }
 
   else{

     string boardFile = argv[1];
     BoggleBoard b = BoggleBoard(boardFile);
     b.Print();
   }
    
   return 0;
}
