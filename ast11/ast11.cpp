//Build as: g++ ast09.cpp -g -std=c++17
//Execute as: ./a.out shipnames.txt
/*
 * Name: Matthew Shiroma, NSHE ID: 2001814396, assignment #11
 * Description: A program that uses Mininmum Spanning Trees
 * Inputs: Population number, range number of edges for each vertex, and the highest weight for each edge
 * Outputs: The MST
 */
#include<iostream>
#include <fstream>  //ifstream
#include<string>
#include<cstdlib>
#include<vector>
#include<cstdlib>

using namespace std;

//node that holds vertex information
class Node{
public:
    Node(){
        weight = 0;
        vertexType = "NONE";
    }
    Node(int weight, string vertexType){
        this->weight = weight;
        this->vertexType = vertexType;
    }
    int weight;
    string vertexType;
};

//MST STUFF

//function prints out the whole matrix
/**
 * Example:
 *   1 2 3 4 5
 *   ----------
 * 1| 1 6 2 0 0
 * 2|   1
 * 3|     1
 * 4|       1
 * 5|         1
 */
void printMatrix(Node **matrix, int matrixSize){
    //print out the header of the top of the matrix
    //aka the 1 2 3 4 5 ...
    //        --------  ...
    cout << "  ";   //print out two spaces for spacing
    for(int i = 0; i < matrixSize; i++)
        cout << i+1 << " ";
    
    cout << endl << "  ";   //go to next line for dashes and spacing
    for(int i = 0; i < matrixSize*2; i++)
        cout << "-";
    

    //prints out the contents of the matrix
    for(int i = 0; i < matrixSize; i++){     //go through each row
        cout << endl << i+1 << "|";
        for(int j = 0; j < matrixSize; j++){ //print the edge for the vertex
            //print out the weight of the edge
            if(matrix[i][j].weight == 0)
                cout << "  ";               //its 0 so dont print out
            else
                cout << matrix[i][j].weight << " ";    //not 0 so print out value
        }
    }
    cout << endl; 
}

void printVertexType(Node **matrix, int matrixSize){
    //print out alphas
    cout << "Alphas: ";
    for(int i = 0; i < matrixSize; i++){    //loop through and find alphas
        if(matrix[i][i].vertexType == "alpha")
            cout << i+1 << " ";
    }

    //print out drones
    cout << "\nDrones: ";
    for(int i = 0; i < matrixSize; i++){    //loop through and find drones
        if(matrix[i][i].vertexType == "drone")
            cout << i+1  << " ";
    }

    //print out you
    cout << "\nYou   : ";
    for(int i = 0; i < matrixSize; i++){    //loop through and find alphas
        if(matrix[i][i].vertexType == "you")
            cout << i+1  << " ";
    }

    cout << "\nOmega : ";
    for(int i = 0; i < matrixSize; i++){    //loop through and find alphas
        if(matrix[i][i].vertexType == "omega")
            cout << i+1  << " ";
    }
}

//expect "./a.out input.txt"
int main(int argc, char **argv){
    if(argc < 2){
        cout << "Error: Missing input.txt!" << endl;
        return 1;
    }
    string fileName = argv[1];      //get file name

    //get file information
    //first run figure out how many vertexs are in the file
    ifstream file;
    int vertexCount = -1;
    file.open(fileName);
    while(!file.eof()){
        string dummyStr;            //just used for getline
        getline(file, dummyStr);    //just used to count how many rows
        vertexCount++;              //inc counter
    }
    file.close();

    //create adjacency matrix
    Node **matrix;
    matrix = new Node*[vertexCount]();
    for(int i = 0; i < vertexCount; i++)
        matrix[i] = new Node[vertexCount]();

    //used to parse the information from the input file into usable information
    file.open(fileName);
    for(int i = 0; i < vertexCount; i++){   //go through the whole file
        string tempStr = "";
        getline(file, tempStr);     //place line from file into a string
        //format of line
        //<Vertex row> <vertex> <weight>
        int vertexRow = tempStr[0] - '0';       // - '0' to reduce ascii value since 1 starts at 49
        //012345678
        //1 2 3 9 1 
        //go through the rest of the string filling up the array
        for(int i = 2; i < tempStr.length()-3; i+=4){
            //after the first num being vertex
            //its a number followed by weight in pairs
            //cout << "V: " << tempStr[i] << "|" << tempStr[i+2] << endl;
            int tempVertex = tempStr[i] - '0';    //holds the vertex that has the edge with this row
            int tempWeight = tempStr[i+2] - '0';  //holds the weight of that edge
            matrix[vertexRow-1][tempVertex-1].weight = tempWeight;
        }
    }
    file.close();
    
    //fill the vertex with a weight of 1 to itself
    for(int i = 0; i < vertexCount; i++){
        matrix[i][i].weight = 1;
    }

    //set alpha count to 20 so there is one alpha at the start
    int alphaCount = 20;
    srand (time(NULL)); //Seed Rand!
    int startIndex = rand() % (vertexCount - 1);  //get a random number between 1-VertexCount

    //used
    bool omega = false;
    bool you = false;

    //used to get random Omega and You
    int randomOmega = rand() % (vertexCount - 1);
    int randomYou = rand() % (vertexCount - 1); 
    // cout << "Randon Omega: " << randomOmega << " | " << randomYou << " | " << startIndex <<endl;     //TESTING

    //set up one omega
    matrix[randomOmega][randomOmega].vertexType = "omega";
    do{
        if(matrix[randomYou][randomYou].vertexType == "NONE"){
            matrix[randomYou][randomYou].vertexType = "you";
            you = true;
        
        }
        else{   //spot is taken so re random
            randomYou = rand() % (vertexCount - 1);             //re randomize
            // cout << "Re randomYou: " << randomYou << endl;      //TESTING
        }
        //loops if the randomOmega and randomYou were the same
    }while(you == false);


    //set the vertex type of the nodes
    //the self node is [i][i] so on the diagonal
    for(int i = 0; i <= vertexCount; i++){   //go through all the vertexs and set them
        //if alphacount == 20 then we set a new alph then reset count
        if(alphaCount == 20){
            if(matrix[startIndex][startIndex].vertexType == "NONE"){
                matrix[startIndex][startIndex].vertexType = "alpha";  //set to alpha
                alphaCount = 0;                     //reset alpha count
            }
        }
        else{
            if(matrix[startIndex][startIndex].vertexType == "NONE")
                matrix[startIndex][startIndex].vertexType = "drone";
            alphaCount++;   //increase alpha count so it closer to 1 alpha to 20 drones
        }

        startIndex++;

        //check if start index at the end amount of vertexs
        if(startIndex == (vertexCount)){
            startIndex = 0;     //reset to 0
        }

    }

    //Output matrix
    cout << "Adjacency Matrix:\n\n";
    printMatrix(matrix, vertexCount);

    //MST WORK

    //Output MST
    cout << "\nMinimum Spanning Tree:\n\n";
    printMatrix(matrix, vertexCount);

    cout << endl;  
    printVertexType(matrix, vertexCount);
    cout << endl;

    //delete matrix
    for(int i = 0; i < vertexCount; i++){
        delete[] matrix[i];
    }
    delete[] matrix;
    return 0;
}