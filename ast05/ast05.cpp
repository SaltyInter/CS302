//CS 302 Assignment 1 By Jorge Fonseca
//Build as: g++ ast01.cpp -g -std=c++17
//Execute as: ./a.out shipnames.txt
//Debug as: 'gdb a.out' and then type 'r shipnames.txt'
//Check for memory leaks with valgrind ./a.out shipnames.txt
/*
 * Name: Matthew Shiroma, NSHE ID: 2001814396, assignment #5
 * Description: Program that takes input from a file to name ships. Those ships will point at a "Nav tower" then will point to another ship.
 *              Will be able to use 3 different data types in this version: dynamic arrays, vectors, and linked list.
 *              Will be able to sort the list using various sorting algorithms 
 * Inputs: the filename that the program takes and uses the names from
 * Outputs: Outputs what the ships are pointing to
 */
#include <iostream> //cout
#include <fstream>  //ifstream
#include <cstdlib>  //rand()
#include <string>   //stringz
#include <vector>   //vector

using namespace std;

class RNGnamer{
public:
    RNGnamer(string filename = "shipnames.txt", int inputDataType = 1) : size(0){
        //Your Code Here:
        //Using filestream open the file with shipnames.
        //Read the file once the end of it to count the number of ships.
        //Keep that value in size class variable.
        //Close file.
        //Use new to dynamically allocate an array of strings called names. 
        //For the size use the number you just read into the size class variable.
        //Open file again.
        //Read in all ship names into the names array you just made.
        //Note that the first 3 lines will always be a header so you want to skip 
        //them when reading into the array.
        //close file.

        //Variables
        ifstream file;
        string dummyStr = "";           //Temp String for holding the line from file 
        size = 0;
        dataType  = inputDataType;       //1 = dynamic array, 2 = vector, 3 = linked list

        file.open(filename);
        for(int i = 0; i < 3; i++)        //For skipping the header
            getline(file,dummyStr);   
        while(getline(file,dummyStr)){       //Inputing names from file to names
            //This is for the extra linefeed at the end. If its blank it will skip this if and not input and cause seg fault
            if(dummyStr != ""){
                names.push_back(dummyStr);
            } 
        }
            file.close();

            size = names.size();   //Sets size var used in other parts from vector size
    }
    ~RNGnamer(){
        //Your Code Here:
        //use delete to de-allocate your name array. 
        //No memory leaks allowed or you will lose points.
        //No need to delete as ast03 made this a vec no dynamic array
    }
    void printAllPossibleNames(){
        cout << "All Possible Ship Names:" << endl;
        for(int i=0; i < size; i++)
                cout << i << ": " << names.at(i) << endl;  //Prins all names from vec
        cout << endl;
    }
    string generateName(){
        return names.at(rand() % size); //picks random name from vec
        return "ERROR";
    }
private:
    int dataType;
    int size;
    vector<string> names;
};

class entity_t {
public:
    entity_t() : id(ent_cnt++){}
    //Your Code Here: Virtual Function whatamI() that returns a string
    virtual string whatamI() = 0; 
    //Your Code Here: function getName that returns a string with the name
    string getName()
    {
        return name;
    }
protected:
    //Your Code Here: static integer variable called ent_cnt that keeps track of how many entities there are
    static int ent_cnt;
    int id; //individual entity id
    string name;
};
int entity_t::ent_cnt = 0;

class navigation_tower : public entity_t{
public:
    navigation_tower(){
        name = "Exegol Navigation Tower #" + to_string(id);
    }
    string whatamI(){
        return "Navigation_Tower";
    }
};

//Your Code Here for the Xyston_class_StarDestroyer class that inherits from entity_t
class Xyston_class_StarDestroyer : public entity_t{
public:
    entity_t *point = NULL;
    Xyston_class_StarDestroyer(RNGnamer &inNameList) 
    {
        this->name = inNameList.generateName() + " #" + to_string(id);
    }
    Xyston_class_StarDestroyer(){};
    void setNavSource(entity_t* inPtr)
    {
        point = inPtr;
    }
    void printNavSource()
    {
        if(point != NULL) //Only works if pointer is not pointing to null
        {
            //Says what the pointer is point to
             cout << "Current Navigation Source is a " << point->whatamI() << ": " << point->getName() << endl << endl; 
        }
        else
        {
            //Couts a statement if pointer is pointing to null
            cout << "No Navigator Source is set. Cannot escape Exogol without one!" << endl;
        }
    }
    string whatamI(){
        return "Xyston_class_StarDestroyer";
    }
};


class Resurgent_class_StarDestroyer : public entity_t{
public:
    Resurgent_class_StarDestroyer(string name = "Capital Ship Steadfast") {
        this->name = name;
    }
    string whatamI(){
        return "Resurgent_StarDestroyer";
    }
};

//Linked list for assn3
class Node{
    public:
        Node(){next = NULL;prev = NULL;}
        Xyston_class_StarDestroyer data;    //Holds the classes
        Node* next;
        Node* prev;
};

void pushNode(Node** headRef, Node** tailRef, Xyston_class_StarDestroyer d){
    Node* newNode = new Node();         //New node inputed by function
    Node *temp = *headRef;              //for traversing the node

    newNode->data = d;                  //Inputs data from param
    newNode->next = NULL;

    if(*headRef == NULL)                //If the list is empty
    {
        newNode->prev = NULL;           //It is head node before is NULL
        *headRef = newNode;             //Makes newNode the head node
        *tailRef = newNode;
        return;
    }

    while(temp->next != NULL){          //Traverse node until it is the last node
        temp = temp->next;              //Makes temp node the last node
    }
    
    temp->next = newNode;               //Makes the temp node, that became the last node, to point to the new last node that was created
    *tailRef = newNode;
    newNode->prev = temp;               //temp becomes the new prev node
    return;
}

//return 0 for equal, -1 for a being less and 1 for b being less.
int compareShipNames(string a, string b){
	if( a == b) return 0;
	int min = a.length() <= b.length() ? a.length() : b.length(); //min function
	int i;
	for(i=0; i < min; i++){
		if(isdigit(a[i]) || isdigit(b[i])) break;
		if(tolower(a[i]) < tolower(b[i])) return -1;
		if(tolower(a[i]) > tolower(b[i])) return 1;
		if(tolower(a[i]) == tolower(b[i])) continue;
		cout << "wat" << endl;
	}
	if(isdigit(a[i]) && !isdigit(b[i])) return -1;
	if(!isdigit(a[i]) && isdigit(b[i])) return 1;
	if(!isdigit(a[i]) && !isdigit(b[i])) cout << "We dun gufd"<< endl;
	
	//Copy numbers to their own strings:
	string anum = "";
	string bnum = "";
	for(int j=i; j < a.length(); j++){
		anum += a[j];
	}
	for(int j=i; j < b.length(); j++){
		bnum += b[j];		
	}
	//convert em to ints
	int numa = stoi(anum); 
	int numb = stoi(bnum);

	if(numa < numb) return -1;
	if(numa > numb) return 1;
	if(numa == numb) return 0;
	
	return 42; // we dun guffd
}

//Bubble sort
void bubbleSort(Xyston_class_StarDestroyer* arr[],int fleet_size){
    string a, b;    //Place holder strings for the names
    int temp = 0;   //temp for swaping
    for(int i = 0; i < (fleet_size - 1); i++){         //Go through the list
        for(int j = 0; j < (fleet_size - 1); j++){
            a = arr[j]->getName();      //get strings and place into a and b
            b = arr[j+1]->getName();
            temp = compareShipNames(a,b);        //compare to see which is greater
                if(temp > 0){
                    Xyston_class_StarDestroyer *temp = arr[j];  //put arr[j] into temp
                    arr[j] = arr[j+1];  //Swap the higher index to lower
                    arr[j+1] = temp;    //put temp back into arr[j+1] which was arr[j]
            }   
        }
    }
}

void insertNodeSort(Node** headRef, Node* insertNode){
    Node* curr;

    //Case 1: List is empty
    if(*headRef == NULL){
        *headRef = insertNode;
    }
    //Case 2: Insert at the start
    
    else if(compareShipNames((*headRef)->data.getName(), (insertNode->data.getName())) >= 0){
        insertNode->next = *headRef;
        insertNode->next->prev = insertNode;
        *headRef = insertNode;
    }
    //Case 3: Insert somewhere after start
    else{
        curr = *headRef;        
        while(curr->next != NULL && compareShipNames(curr->next->data.getName(),insertNode->data.getName()) < 0)
            curr = curr->next;  //Keep traversing till gets to a node that
        
        //Swap the nodes
        insertNode->next = curr->next; 

        //If its at the end of the linked list
        if(curr->next != NULL)
            insertNode->next->prev = insertNode;

        curr->next = insertNode;
        insertNode->prev = curr;
    }
}

//Insertion Sort
void insertionSort(Node** headRef, Node** tailRef, int fleet_size){
    Node* sortedList = NULL;    //Sorted list that will be sent back
    Node* curr = *tailRef;      //Get the list starting at the back
    while(curr != NULL){
        Node* tempPrev = curr->prev;    //Save the node behind before its changed
        insertNodeSort(&sortedList, curr);
        curr = tempPrev;        //traverse the list backwards
    }
    *headRef = sortedList;      //set the sorted list to the head
}

//Selection sort
void selectionSort(vector<Xyston_class_StarDestroyer> &arr, int fleet_size){
    int minIndex = 0;   //used to hold the index of smallest value in unsorted part of list
    for(int i = 0; i < fleet_size-1; i++){
        minIndex = i; //assume first index is the smallest
        for(int j = i+1; j < fleet_size; j++){
            //compare to see if first value is lower than min
            
            if(compareShipNames(arr.at(j).getName(), arr.at(minIndex).getName()) < 0)
                minIndex = j; //min index is the smallest
        }
        if(minIndex != i){  //there is a different minValue not at I
            swap(arr.at(i),arr.at(minIndex));   //swap the two
        }
    }
}

//Merge sort

//function to split the list into two
void mergeSplit(Node* head, Node** left, Node** right){
    //used to advance the list till the middle
    Node* fast;     //will grow 2x as fast as slow so when it hits end slow should be mid
    Node* slow;

    slow = head;
    fast = head->next;

    //figure out the middle of the list
    while(fast != NULL){    //check if at end of list
        fast = fast->next;
        if(fast != NULL){   //check if at end of list
            fast = fast->next;  //goes down the list 2 times
            slow = slow->next;  //goes down the list 1 time 
        }
    }//finished traversing the list

    *left = head;   //start at the start
    *right = slow->next;
    slow->next = NULL;
}

//Sorts between the two list and merges them back into one
Node* merge(Node* left, Node* right){
    Node* temp = NULL;

    //Base cases
    if(left == NULL)
        return(right);
    else if(right == NULL)
        return(left);
    else{
        //sort the list by comparing the values and call merge again till done
        string leftStr = left->data.getName();
        string rightStr = right->data.getName();
        if(compareShipNames(leftStr, rightStr) <= 0){  //if left is less than or equal to right
            temp = left;
            temp->next = merge(left->next, right);  //recur till list is done
        }
        else{
            temp = right;
            temp->next = merge(left,right->next);
        }
        return temp;    //temp will have the sorted list of the two left and right
    }
}

void mergeSort(Node** headRef){
    Node* head = *headRef;
    Node* left;
    Node* right;

    //base case linked list is empty or one link
    if(head == NULL|| head->next == NULL){  
        return;     //end recursion
    }
    else{
        mergeSplit(head, &left, &right);    //Split the list into two parts left and right

        //recursion that will divide the list more and more
        mergeSort(&left);
        mergeSort(&right);

        //remerge the two list
        *headRef = merge(left, right);
    } 
}
//Quick sort
int partition(Xyston_class_StarDestroyer* arr[], int l, int r){
    string pivotStr = arr[r]->getName();    //Get pivot string and store it
    string tempStr = "";                    //used later for compare
    int i = l - 1;

    for(int j = l; j < r; j++){
        tempStr = arr[j]->getName();
        if(compareShipNames(tempStr, pivotStr) < 0){  //if high pointer is less than pivot
            i++;
            //Swap the two
            Xyston_class_StarDestroyer* temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }
    //Place pivot in correct spot among the array
    Xyston_class_StarDestroyer* temp = arr[i+1];
    arr[i+1] = arr[r];
    arr[r] = temp;
    return (i+1);   //return the pivot place
}

void quickSort(Xyston_class_StarDestroyer* arr[], int l, int r){
    //Base Case
    if(l >= r)  //Quick sort is done as there is nothing left to sort
        return;
    else{
        int pivot = partition(arr, l, r);   //place pivot in right place
        quickSort(arr, l, (pivot-1));       //Recurrsive calls for l than pivot
        quickSort(arr, (pivot+1), r);       //and for right of pivot
    }
}

//end of changes for ast05

int main(int argc, char **argv){
    if(argc < 2){
        cout << "Error: Missing shipnames.txt!" << endl;
        return 1;
    } 
    //Changes to main for assn3
    string inputDataTypeStr = "";
    int dataType = 1;            //Param temp var to figure out what data type the nameList is
    if(argc >= 3){               //Prevent crash if there is nothing in argv[2]
        inputDataTypeStr = argv[2];
    }
    if(inputDataTypeStr == "vector"){        //Runs vector version
        dataType = 2;
    }
    else if(inputDataTypeStr == "linked"){   //Runs linked list version
        dataType = 3;
    }
    else{                           //Runs normal array version
        dataType = 1;
    }
    //end of changes
    //Changes to main for assn5
    string inputSortingType = "";
    int sortingType = -1;
    if(argc >= 4){  //Testing if there is some sorting request
        inputSortingType = argv[3];
        //Lowercase the input for in statements
        for(int i = 0; i < inputSortingType.length(); i++){
            inputSortingType[i] = tolower(inputSortingType[i]);
        }
    }
    //Figure out which sorting to use
    if(inputSortingType == "bubblesort"){
        sortingType = 1;    //Bubble Sort
    }
    else if(inputSortingType == "insertionsort"){
        sortingType = 2;    //Insertion Sort
    }
    else if(inputSortingType == "selectionsort"){
        sortingType = 3;    //Selection Sort
    }
    else if(inputSortingType == "mergesort"){
        sortingType = 4;    //Merge Sort
    }
    else if(inputSortingType == "quicksort"){
        sortingType = 5;    //Quick Sort
    }
    //end of changes
    srand (time(NULL)); //Seed Rand!
    RNGnamer nameList(argv[1]);
    int fleet_size = 10000;
//#define DEBUG
#ifdef DEBUG
    fleet_size = 10; //for small tests (sample output given is with this size)
#endif
    Resurgent_class_StarDestroyer Steadfast_flagship;
    //Xyston_class_StarDestroyer Sith_Eternal_Fleet[fleet_size](nameList); //old

    //Changes to main for ast03
    Xyston_class_StarDestroyer *Sith_Eternal_Fleet[fleet_size]; //Dyanmic array
    vector<Xyston_class_StarDestroyer> Sith_Eternal_Fleet_Vec;     //Vector
    Node* head = NULL;          //Linked List
    Node* tail = NULL;
    
    //Fill the data type depending on which type it is
    for(int i=0; i < fleet_size; i++){
        if(dataType == 1){
            Sith_Eternal_Fleet[i] = new Xyston_class_StarDestroyer(nameList);
        }
        else if(dataType == 2){
            Sith_Eternal_Fleet_Vec.push_back(Xyston_class_StarDestroyer(nameList));
        }
        else if(dataType == 3){
            pushNode(&head, &tail, Xyston_class_StarDestroyer(nameList));
        }
    }
    
    //end of changes
    navigation_tower Exogol_Tower;

    cout << "\nAt last the work of generations is complete. "
         << "The great error is corrected. The day of victory is at hand. "
         << "The day of revenge. The day of the Sith.\n" << endl;

    //changes for ast03
    //Set the nav sources of the ships to the tower in respected data type
    Node* curr = head;  //Used to reset to the start of linked list
    for(int i = 0; i < fleet_size; ++i ){
        if(dataType == 1){
            Sith_Eternal_Fleet[i]->setNavSource(&Exogol_Tower);
        }
        else if(dataType == 2){
            Sith_Eternal_Fleet_Vec.at(i).setNavSource(&Exogol_Tower);
        }
        else if(dataType == 3){
            curr->data.setNavSource(&Exogol_Tower);
            curr = curr->next;    //goes to next element of linked list
        }
    }
    //end of changes

    cout << "Nav Source for fleet:" << endl;

    //changes for ast03
    //prints the navsource for the data types
    if(dataType == 1){
        for (auto ship : Sith_Eternal_Fleet)
            ship->printNavSource();
    }
    else if(dataType == 2){
        for (auto ship : Sith_Eternal_Fleet_Vec)
            ship.printNavSource();
    }
    else if(dataType == 3){
        Node* curr = head;  //used to be at start of Linked list
        for(int i = 0; i < fleet_size; i++){
            curr->data.printNavSource();
            curr = curr->next;  //go to next element of linked list
        }
    }
    //end of changes

    cout << "\nThe Resistance is targetting the Navigation Tower. "
         << "Transfer the signal to the Steadfast. "
         << "We'll guide the fleet ourselves." << endl;

    cout << "\nSwitching Nav Source to Steadfast." << endl;

    //changes for ast03
    curr = head;  //start at the head of linked list
    //change the nav source to the steadfast ships and print them out
    for(int i = 0; i < fleet_size; ++i ){
        if(dataType == 1){
            Sith_Eternal_Fleet[i]->setNavSource(&Steadfast_flagship);
            cout << Sith_Eternal_Fleet[i]->getName() << ": ";
            Sith_Eternal_Fleet[i]->printNavSource();
        }
        else if(dataType == 2){
            Sith_Eternal_Fleet_Vec.at(i).setNavSource(&Steadfast_flagship);
            cout << Sith_Eternal_Fleet_Vec.at(i).getName() << ": ";
            Sith_Eternal_Fleet_Vec.at(i).printNavSource();
        }
        else if(dataType == 3){
            curr->data.setNavSource(&Steadfast_flagship);
            cout << curr->data.getName() << ": ";
            curr->data.printNavSource();
            curr = curr->next;      //go to next element of linked list
        }
    }
    //end of changes
    
    //changes for ast05
    //Output to file
    if(argc >= 4){      //Running sorting
        //Writing unsorted ships into file
        ofstream file;
        file.open("sithfleet.txt");
        Node* curr = head;
        for(int i = 0; i < fleet_size; i++){
            if(dataType == 1){
                file << Sith_Eternal_Fleet[i]->getName() << endl;
            }
            else if(dataType == 2){
                file << Sith_Eternal_Fleet_Vec.at(i).getName() << endl;
            }
            else if(dataType == 3){
                file << curr->data.getName() << endl;
                curr = curr->next;      //traverse the linked list
            }
        }
        file << "\n\n\n\n\n\n\n\n\n\n";     //Linefeed space

        if(sortingType == 1){       //Bubble sort 
            if(dataType == 1){      //Only run if dynamic array
                bubbleSort(Sith_Eternal_Fleet,fleet_size);
            }
            else{
                file << dataType <<endl << "ERROR: WRONG DATA FORMAT TO SORT WITH!!!" << endl;
                sortingType = -1;
            }
        }
        else if(sortingType == 2){  //Insertion Sort
            if(dataType == 3){      //Only run if Linked list
                insertionSort(&head, &tail, fleet_size);
            }
            else{
                file << dataType <<endl << "ERROR: WRONG DATA FORMAT TO SORT WITH!!!" << endl;
                sortingType = -1;
            }
        }
        else if(sortingType == 3){   //Selection Sort
            if(dataType == 2){       //only runs if vector
                selectionSort(Sith_Eternal_Fleet_Vec,fleet_size);    
            }
            else{
                file << dataType <<endl << "ERROR: WRONG DATA FORMAT TO SORT WITH!!!" << endl;
                sortingType = -1;
            }
        }
        else if(sortingType == 4){   //Merge Sort
            if(dataType == 3){       //Only runs if linked list
                mergeSort(&head);
            }
            else{
                file << dataType <<endl << "ERROR: WRONG DATA FORMAT TO SORT WITH!!!" << endl;
                sortingType = -1;
            }
        }
        else if(sortingType == 5){   //Quick Sort
            if(dataType == 1){       //Only runs if dytanmic array
                quickSort(Sith_Eternal_Fleet, 0, (fleet_size-1));
            }
            else{
                file << dataType <<endl << "ERROR: WRONG DATA FORMAT TO SORT WITH!!!" << endl;
                sortingType = -1;
            }
        }
        else if(sortingType == -1){  //Didnt pick any sorting algorithm
            file << "ERROR: WRONG SORTING PARM SENT IN!!!" << endl;
        }

        //Print to file if it went through some sorting
        if(sortingType != -1){
            Node* curr = head;
            for(int i = 0; i < fleet_size; i++){
                if(dataType == 1){
                    file << Sith_Eternal_Fleet[i]->getName() << endl;
                }
                else if(dataType == 2){
                    file << Sith_Eternal_Fleet_Vec.at(i).getName() << endl;
                }
                else if(dataType == 3){
                    while(curr != NULL){
                        file << curr->data.getName() << endl;
                        curr = curr->next;      //traverse the linked list
                    }
                }
            }
        }

        file.close();
    }
    //end of changes
    if(dataType == 1){
        for(int i=0; i < fleet_size; i++){
            delete Sith_Eternal_Fleet[i];
        }
    } //Did you ever hear the tragedy of Darth Plagueis the wise?

#ifdef DEBUG
    nameList.printAllPossibleNames(); //Test if read successfully.
    cout << "RNG Test: " << nameList.generateName() << endl; //Test RNG of names (should be different each run)
    cout << "RNG Test: " << nameList.generateName() << endl; //Test RRG of names (should be different each run)

    Xyston_class_StarDestroyer ship1(nameList);
    Xyston_class_StarDestroyer ship2(nameList);

    navigation_tower test_tower;
    Resurgent_class_StarDestroyer flagship;

    ship1.printNavSource(); //No Nav Set

    //ship1.setNavSource(dynamic_cast<entity_t*>(&test_tower));
    ship1.setNavSource(&test_tower);
    ship2.setNavSource(dynamic_cast<entity_t*>(&flagship));
    //ship2.setNavSource(&flagship);

    ship1.printNavSource();
    ship2.printNavSource();

#endif
    cout << "\n\nSimulation Terminated." << endl;
    return 0;
}