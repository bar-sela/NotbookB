//
// Created by barse on 3/22/2022.
//

#include "Notebook.hpp"
#include <unordered_map>
#include <array>
#include <cstring>
#include<math.h>
using namespace std ;
using ariel ::Direction;


/////
const char minValidChar = 32 ;
const char maxValidChar = 126; 
const char COLL99_INDEX = 99;

void ariel::Notebook::write(int page, int row , int col, Direction dir, string str) {
 for(size_t i = 0 ; i < str.length(); i++){
    if ((str[i] < minValidChar) || (str[i] >maxValidChar) || (str[i] == '~')) 
            throw "iligal";
    }
    if(page < 0 || row < 0 || col < 0 || col> COLL99_INDEX || str.find('\n') != -1 )  {
         throw "iligal";
    }
    if(((size_t)col + str.length() > COLL99_INDEX+1) && (dir == Direction::Horizontal)){
        throw "iligal";     
    }
    if(floor(page)!= page|| floor(row) != row || floor(col) != col){
         throw "iligal";           
    }
    if(str.length() == 0){
        throw "iligal";
    }
    if (pages.find(page) == pages.end()) {
        unordered_map<int, char[100]> specifyPage;  /// represt a page
        pages[page] = specifyPage;
    }
    ///// crreating c ;
    char c[100];
    for (int i = 0; i < 100; i++) {
        c[i] = '_';
    }
    //// creating rows which are not exist yet ;
    if (dir == Direction::Vertical) {
        for (int i = 0; i < str.length(); i++) {
            if (pages[page].find(row + i) == pages[page].end()){ ///// cheak if the row already exist - if so , dont create it again
                strcpy(pages[page][row + i], c);
            }
        }
        /// writing
        for (int i = 0; i < str.length(); i++) {
            if (pages[page][row + i][col] == '_'){
                pages[page][row + i][col] = str[(size_t)i];
            }
            else{
                throw "not legal";
            }
        }
    }
    // creating row which are not exist
    if (dir == Direction::Horizontal) {
        if (pages[page].find(row) == pages[page].end())
            strcpy(pages[page][row], c);
        /// writing
        for (int i = 0; i < str.length(); i++) {
            if (pages[page][row][col + i] == '_')
                pages[page][row][col + i] = str[(size_t)i];
            else{
                throw "not legal";
            }
        }
    }
}

string ariel::Notebook::read(int page, int row, int col, Direction dir, int len) {
    if(page < 0 || row < 0 || col < 0 || len < 0 || col > COLL99_INDEX){
         throw "iligal";             
    }
    if((col + len > COLL99_INDEX+1) && (dir == Direction::Horizontal)){ 
        throw "iligal";   
    }
    if(floor(page)!= page|| floor(row) != row || floor(col) != col || floor(len) !=len){
               throw "iligal";   
    }
    string str = string("");
    if (pages.find(page) == pages.end()) {
        //  returning an ___ if the page is we never wrote inside the page - beacuse he is not exist.
        for (int i = 0; i < len; i++) {
            str.push_back('_');
        }
        return str;
    }
    // if the page does exist - lets read inside of it .
    if (dir == Direction::Vertical) {
        for (int i = 0; i < len; i++) {
            if (pages[page].find(row + i) != pages[page].end()) {
                char c = pages[page][row + i][col];
                str.push_back(c);
            } 
            else{
                str.push_back('_');
            }
        }
    }
    if (dir == Direction::Horizontal) {
        if (pages[page].find(row) == pages[page].end()) {
            for (int i = 0; i < len; i++) {
                str.push_back('_');
            }
            return str;
        }
        //// if the row does exist - lets read from it
        for (int i = 0; i < len; i++) {
            char c = pages[page][row][col + i];
            str.push_back(c);
        }
        return str;
    }
    return str ;
}


void ariel::Notebook::erase(int page, int row, int col, Direction dir, int len) {
    if(page < 0 || row < 0 || col < 0 || len < 0 ||col >COLL99_INDEX){
          throw "iligal";
    }
    if( (col + len > COLL99_INDEX+1) && (dir == Direction::Horizontal )){ 
         throw "iligal";;     
    }
    if(len == 0){
        return;  
    }  
    char c[100];
    for (int i = 0; i < 100; i++) {
        c[i] = '_';
    }
    if(pages.find(page) == pages.end()){ //if the page doesn't exist
        unordered_map<int, char[100]> specifyPage;
        pages[page] = specifyPage;
    }

    if (dir == Direction::Horizontal) {
        // create the row
        if(pages[page].find(row) == pages[page].end()){
            strcpy(pages[page][row], c);
        }

        // delete the right places
        for(int i=0; i<len; i++){
            pages[page][row][col+i] = '~';
        }
    }

    if (dir == Direction::Vertical) {
        // create the column
        for (int i = 0; i < len; i++) {
            if (pages[page].find(row + i) == pages[page].end())
                strcpy(pages[page][row + i], c);
        }

        // delete the right places
        for(int i=0; i<len; i++){
            pages[page][row+i][col] = '~';
        }
    }
}

void ariel::Notebook::show(int page) {
    if(page < 0 ){
       throw "ilegal";
    }
    if (pages.find(page) == pages.end()) {
        for(int i=0; i<6; i++){
            cout<<"____________________________________________________________________________________________________"<<endl;
        }
    }

    else{
        char row[100];
        for(unordered_map<int, char[100]>::iterator itr = pages[page].begin(); itr != pages[page].end(); ++itr){
            strcpy(row,itr->second);
            for(int i=0; i<100; i++){
                cout<<row[i];
            }
            cout<<endl;
        }
    }
    
}

