//Created by SniperJF
//Dedicated to all the competitive gamers out there.
//Compile as: g++ ast12.cpp -lncurses

/*
 * Name: Matthew Shiroma, NSHE ID: 2001814396, assignment #12
 * Description: CS:GO
 */

//#include<iostream>    //cin/cout NOT USED. DO NOT ENABLE!
#include<fstream>       //File Streams
#include<ncurses.h>     //N Curses Library
#include<stdlib.h>      //srand
#include<time.h>        //time
#include<string>
#include<vector>

//using namespace std;

void initCurses();
void endCurses();

class CharMap {
  public:
    CharMap(char *arg);
    CharMap(char** c, std::string m, int w, int h) : 
        map(c), mapName(m), width(w), height(h){}
    ~CharMap();
    void print();
    char ** map;
    std::string mapName;
    int width;
    int height;
};

//Your Code Here

int main(int argc, char **argv){
//	srand(time(NULL)); //Comment out to always have the same RNG for debugging
    CharMap *map = (argc == 2) ? new CharMap(argv[1]) : NULL; //Read in input file
    if(map == NULL){printf("Invalid Map File\n"); return 1;}  //close if no file given
    initCurses(); // Curses Initialisations
    map->print();

    //Your Code Here

    delete map; map = NULL;
    printw("\ngg ez\n");
    endCurses(); //END CURSES
    return 0;
}

void initCurses(){
    // Curses Initialisations
	initscr();
	raw();
	keypad(stdscr, TRUE);
	noecho();
	printw("Welcome - Press Q to Exit\n");
}
void endCurses(){
	refresh();
	getch(); //Make user press any key to close
	endwin();
}


//CharMap Functions
CharMap::CharMap(char *arg){
    char temp;
    std::ifstream fin(arg);
    fin >> mapName;
    fin >> height;
    fin >> temp;
    fin >> width;
    map = new char*[height]; //Allocate our 2D array
    for(int i=0; i<height; i++){
        map[i] = new char[width];
        for(int j=0; j<width; j++) //Read into our array while we're at it!
            fin >> (map[i][j]) >> std::noskipws; //dont skip whitespace
        fin >> std::skipws; //skip it again just so we skip linefeed
    }
    //for(int i=0; i<height; i++){ //Uncomment if you have issues reading
    //    for(int j=0; j<width; j++) printf("%c", map[i][j]); printf("\n");};
}

CharMap::~CharMap(){
    if(map == NULL) return;
    for(int i=0; i<height; i++)
        delete [] map[i];
    delete [] map;
}

void CharMap::print(){ //call only after curses is initialized!
    printw("Read Map: '%s' with dimensions %dx%d!\n", 
            mapName.c_str(), height, width);
    //Note the c_str is required for C++ Strings to print with printw
    for(int i=0; i<height; i++){
        for(int j=0; j<width; j++)
            printw("%c", map[i][j]);
        printw("\n");
    }   
}
