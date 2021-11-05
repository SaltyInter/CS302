//CS 302 Assignment 8 By Jorge Fonseca
//Build as: g++ ast08.cpp -g -std=c++17
//Execute as: ./a.out shipnames.txt
//Debug as: 'gdb a.out' and then type 'r shipnames.txt'
//Check for memory leaks with valgrind ./a.out shipnames.txt
/*
 * Name: Matthew Shiroma, NSHE ID: 2001814396, assignment #8
 * Description:  
 * Inputs: 
 * Outputs: 
 */
#include <iostream> //cout
#include <fstream>  //ifstream
#include <cstdlib>  //rand()
#include <string>   //stringz
#include <vector>   //vector

//assn8 write up counters
//should be commented out by default
//#define COUNTERS
#ifdef COUNTERS
static int comparisonCounter = 0;
static int rotationCounter = 0;
#endif

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

//Changes for ast05
//compare function courtesy of Professor :)
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
    for(int i = 0; i < (fleet_size - 1); i++){         //Go through the list
        for(int j = 0; j < (fleet_size - 1); j++){
            a = arr[j]->getName();      //get strings and place into a and b
            b = arr[j+1]->getName();
                if(compareShipNames(a,b) > 0){
                    Xyston_class_StarDestroyer *temp = arr[j];  //put arr[j] into temp
                    arr[j] = arr[j+1];  //Swap the higher index to lower
                    arr[j+1] = temp;    //put temp back into arr[j+1] which was arr[j]
            }   
        }
    }
}

void insertNodeSort(Node** headRef, Node* insertNode){
    Node* curr = *headRef;

    //Case 1: List is empty
    if(*headRef == NULL){
        *headRef = insertNode;
    }
    //Case 2: Insert at the start
    else if(compareShipNames((*headRef)->data.getName(), (insertNode->data.getName())) >= 0){
        //move head to 2nd spot and place insertNode at the beginning
        insertNode->next = *headRef;
        insertNode->next->prev = insertNode;
        *headRef = insertNode;
    }
    //Case 3: Insert somewhere after start
    else{       
        while(curr->next != NULL && compareShipNames(curr->next->data.getName(),insertNode->data.getName()) < 0)
            curr = curr->next;  //Keep traversing till gets to a node that

        //Start preping for swap
        insertNode->next = curr->next; 
        //Swap
        curr->next = insertNode;
        insertNode->prev = curr;
    }
}

//Insertion Sort
void insertionSort(Node** headRef, Node** tailRef, int fleet_size){
    Node* sortedList = NULL;    //Sorted list that will be sent back
    Node* curr = *tailRef;      //Get the list starting at the back
    while(curr != NULL){
        //Dequeue from the list into the sorted list
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
    Node* slow = head;     
    Node* fast = head->next;    //will grow 2x faster than slow so when it hits end slow should be mid

    //figure out the middle of the list
    while(fast != NULL){    //check if at end of list
        fast = fast->next;
        if(fast != NULL){   //check if at end of list
            fast = fast->next;  //goes down the list 2 times
            slow = slow->next;  //goes down the list 1 time 
        }
    }//finished traversing the list

    *left = head;   //start at the start
    *right = slow->next;    //start at the middle + 1
    slow->next = NULL;  //clear out the rest of slow
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

//changes for ast08
template < class T>
class node {
  public:
    //Your Code Here: Default Constructor
    node(){left = nullptr; right = nullptr; data = new T; height = 1;};
    node(const T &var) : left(NULL), right(NULL), height(1) {
        //Your Code Here
        data = new T;
        *data = var;
    }
    //Your Code Here for Destructor
    ~node(){
        delete data;
    }
    //Your Code Here to Overlaod Copy Constructor so you can make a node(node)
    node& operator=(const node& otherNode){
        node* temp = new node();
        temp->data = otherNode.data;
        temp->left = otherNode.left;
        temp->right = otherNode.right;
        temp->height = otherNode.height;
        return temp;
    }
    //Your Code Here for Assignment Operator Overload to assign node to a node  (Part of Rule of 3)
    void operator=(const T &var){  //Assignment Operator Overload to take literals
        *data = var;
    }
    void setData(T var) {
        *data = var;
    }
    T getData() const {
        //Your Code Here
        return *data;
    }
    friend std::ostream& operator<<(std::ostream& out, const node& n){
        out << *n.data;
    }
    //Your Code Here for >> operator overloading to read into n.data of a node&n. Make it inline
    friend istream& operator>>(istream& in, const node& n){in >> *n.data; return in;};
  protected:
    T    *data;
    node *left;
    node *right;
    int height;
    template <class U> friend class BinaryTree; //<--Don't you dare to @#$%$ touch this.
};

template <class T>
class BinaryTree{
  public:
    BinaryTree() : root(NULL), size(0){}
    virtual ~BinaryTree(){                //Destructor                    (Part of Rule of 3)
        DeleteTree(&root);
        root = NULL;
    }
    BinaryTree(const BinaryTree &b2){     //Copy Constructor Overload     (Part of Rule of 3)
        //Your Code Here (Should call copyTree)
        copyTree(b2.root, &(this->root));
    }
    int copyTree(node<T>* currOG, node<T>** currNEW){
        //Your Code Here
        *currNEW = currOG;
    }

    //overload | operator to act as mirror :D
    BinaryTree operator|(const BinaryTree& OG){
        if(OG.root == NULL) return OG;
        DeleteTree(&root);
        this->root = NULL;
        this->size = mirrorTree(OG.root, &(this->root));
        return OG;
    }
    int mirrorTree(node<T>* currOG, node<T>** currNEW){
        //Your Code Here
        static int counter;
        node<T>* temp = new node<T>; 
        if(currOG != NULL){
            // cout << "TESTING " << counter << ": ";
            // inOrderTraversal(*currNEW);
            // cout << " ";
            // inOrderTraversal(currOG);
            // cout << endl;

            counter++;
            temp->data = currOG->data;
            *currNEW = temp;
            //cout << "TEMP DATA: " << temp->data << ", CURR DATA " << currOG->data << endl; //TESTING
            if(currOG->left != NULL)
                mirrorTree(currOG->right, &temp->left);
            if(currOG->right != NULL)
                mirrorTree(currOG->left, &temp->right);
        }
        return counter;
    }
    void operator=(const BinaryTree &b2){ //Assignment Operator Overload  (Part of Rule of 3)
        DeleteTree(&root);
        this->root = NULL;
        this->size = copyTree(b2.root, &(this->root));
    }
    void readnGenerate(const T a[], int arr_size){
        if(arr_size <= 0) return; //empty
        #ifdef DEBUG
        cout << "Generating From: '" << a << "'\nOG Length: 00" << arr_size << endl;
        #endif
        DeleteTree(&root);
        this->size = recInsert(a, arr_size, &root, 1);
        #ifdef DEBUG
        cout << "Total Inserted: "  << this->size << endl;
        #endif

    }
    //ast 08 code
    void insertShipBinarySearch(node<T>* insertItem){
        this->root = insertShipBinarySearchHelper(this->root, insertItem);
    }

    node<T>* insertShipBinarySearchHelper(node<T>* root, node<T>* insertItem){
        
        if(root == NULL){   //Spot is empty
            return insertItem;
        }
        else{
            #ifdef COUNTERS
                comparisonCounter++;
            #endif
            //get the names of the ships for comparing
            string currStr = root->data->getName();
            string insertStr = insertItem->data->getName();

            //go left if the new item is less than or equal to the curr one
            if(compareShipNames(currStr, insertStr) >= 0){   //call compareShipNames to see whos greater
                root->left = insertShipBinarySearchHelper(root->left, insertItem);
            }
            //go right if the new item is greater than the curr one
            else if(compareShipNames(currStr, insertStr) < 0){
                root->right = insertShipBinarySearchHelper(root->right, insertItem);
            }
        }
        return root;
    }

    void insertShipAVL(node<T>* insertItem){
        //TESTING STUFF
        // cout << "\n\nINSERT " << insertItem->data->getName() << endl;
        // if(root != NULL)
        //     cout << "!!!ROOT DATA " << root->data->getName() << endl;
        this->root = insertShipAVLHelper(this->root, insertItem);
    }

    node<T>* insertShipAVLHelper(node<T>* root, node<T>* insertItem){
        if(root == NULL){       //new node
            return insertItem;
        }
        
        #ifdef COUNTERS
                comparisonCounter++;
        #endif

        //Insert the node into the tree
        //get the names of the ships for comparing
        string currStr = root->data->getName();
        string insertStr = insertItem->data->getName();
        //cout << "TESTING " << currStr << " " <<insertStr << endl;   //TESTING

        //get the return value of comparing the two strings
        // >= 0 is left < 0 right
        int compareValue = (compareShipNames(currStr, insertStr)); 
        
         //go left if the new item is less than or equal to the curr one
        if(compareValue >= 0){   //call compareShipNames to see whos greater
            root->left = insertShipAVLHelper(root->left, insertItem);
        }
        //go right if the new item is greater than the curr one
        else if(compareValue < 0){
            root->right = insertShipAVLHelper(root->right, insertItem);
        }

        //check for inbalance in the tree
        int treeBalance = getTreeBalance(root);

        //Only run this if there is an imbalance in the tree
        if(treeBalance > 1 || treeBalance < -1){
            #ifdef COUNTERS
                rotationCounter++;
            #endif
            //used for comapring nodes to left strings
            string currLeftStr = " ";
            string currRightStr = " ";

            if(root->left != NULL)
                currLeftStr = root->left->data->getName();
            if(root->right != NULL)
                currRightStr = root->right->data->getName();

            //Get int values from comparing left/right of the root to the new insert
            //returns 0 if equal -1 if curr(left/right) is less and 1 for insert being less
            int compareValueLeft = (compareShipNames(currLeftStr, insertStr)); 
            int compareValueRight = (compareShipNames(currRightStr, insertStr)); 

            //left left case
            if(treeBalance > 1 && compareValueLeft > 0){
                return rightRotate(root);
            }
            //right right case
            else if(treeBalance < -1 && compareValueRight <= 0){
                return leftRotate(root);
            }

            //left right case
            if(treeBalance > 1 && compareValueLeft <= 0){
                root->left = leftRotate(root->left);
                return rightRotate(root);
            }

            //right left case
            if(treeBalance < -1 && compareValueRight > 0){
                root->right = rightRotate(root->right);
                return leftRotate(root);
            }
        }

        //return the root of the node
        return root;
    }

    //Left Left imbalance
    node<T>* rightRotate(node<T>* root){
        //Store the node into temps
        node<T>* rootLeft = root->left;        //grab the node left and store in as x
        node<T>* temp = rootLeft->right;     //create a temp node with node 2 right tree
        //preform rotations:
        rootLeft->right = root;
        root->left = temp;      //set it to root right
        return rootLeft;        //return the root->left as the new root
    }

    //Right Right imbalance
   node<T>* leftRotate(node<T>* root){
       //Store the node into temps
        node<T>* rootRight = root->right;        //grab the node left and store in as x
        node<T>* temp = rootRight->left;        //create a temp node with y's left
        //preform rotations:
        rootRight->left = root;
        root->right = temp;      //set it to root right

        return rootRight;   //return the root->right as the new root
    }

    //Func that returns the height of a tree
    int height(node<T>* root){
        if(root == NULL){
            return -1;  //at the bottom
        }
        else{
            int leftHeight = height(root->left);
            int rightHeight = height(root->right);

            //return the height of the one that is higher
            if(leftHeight > rightHeight){
                return (leftHeight + 1);
            }
            else{
                return (rightHeight + 1);
            }
        }
    }

    //returns the values of the tree left and right
    int getTreeBalance(node<T>* node){
        if(node == NULL){
            return -1;      //tree has nothing in it
        }
        else{
            return (height(node->left) - height(node->right));
        }
    }
    
    //return the root
    node<T>* getRoot(){
        return this->root;
    }
    //end of ast08 changes

    //ast 07 code
    void genFromINandPRE(const T preOrder[],const  T inOrder[]){
        this->root = genFromINandPREHelper(0, 0, (string(inOrder).length())-1, preOrder, inOrder);
    }

    node<T>* genFromINandPREHelper(int preStart, int inStart, int inEnd, const T *preOrder, const T *inOrder){
        //base case nothing to do here anymore
        if(inStart > inEnd || preStart > string(preOrder).length()-1){      
            return NULL;
        }
        node<T>* temp = new node<T>;        //temp node to return later to set to root
        //cout << "TEST: " << preOrder[preStart] << endl; //TESTING
        temp->setData(preOrder[preStart]);    //set it to the next thing in the preOrder list

        int index = 0;      //used to hold the index of where the preStart is held inOrder
        for(int i = inStart; i <= inEnd; i++){
            if(temp->getData() == inOrder[i]){
                //cout << "TEMP: " << temp->getData() << ", inOrder: " << inOrder[i] << endl; //TESTING
                index = i;      //found the index and set it to I
            }
        }
        //set up temp's left and right 

        //set up varaibles to pass for next recursive call
        int leftPreStart = preStart + 1;
        int rightPreStart = preStart + index - inStart + 1;
        temp->left = genFromINandPREHelper(leftPreStart, inStart, index-1, preOrder, inOrder);
        temp->right = genFromINandPREHelper(rightPreStart, index + 1, inEnd, preOrder, inOrder);

        //return the node
        return temp;
    }

    void genFromINandPost(const T postOrder[],const  T inOrder[]){
        this->root = genFromINandPostHelper(string(postOrder).length()-1, 0, (string(inOrder).length())-1 , postOrder, inOrder);
    }

    node<T>* genFromINandPostHelper(int postStart, int inStart, int inEnd, const T *postOrder, const T *inOrder){
        //base case nothing to do here anymore
        if(inStart > inEnd){      
            return NULL;
        }
        node<T>* temp = new node<T>;        //temp node to return later to set to root
        //cout << "TEST: " << postOrder[postStart] << endl; //TESTING
        temp->setData(postOrder[postStart]);    //set it to the next thing in the preOrder list

        int index = 0;      //used to hold the index of where the preStart is held inOrder
        for(int i = inStart; i <= inEnd; i++){
            if(temp->getData() == inOrder[i]){
                //cout << "TEMP: " << temp->getData() << ", inOrder: " << inOrder[i] << endl; //TESTING
                index = i;      //found the index and set it to I
            }
        }
        //set up temp's left and right 

        //set up varaibles to pass for next recursive call
        int rightPostStart = postStart - 1;
        int leftPostStart = postStart - (inEnd - index) - 1;
        temp->right = genFromINandPostHelper(rightPostStart,index+1, inEnd, postOrder, inOrder);
        temp->left = genFromINandPostHelper(leftPostStart, inStart, index-1, postOrder, inOrder);

        //return the node
        return temp;
    }

    //end of ast 07 code

    int recInsert(const T *a, int arrSize, node<T>**curr, int currIndex){
        static int counter;
        if(currIndex <= arrSize){
            counter++;
            node<T>* temp = new node<T>; 
            if(a[currIndex-1] != '%'){
                temp->setData(a[currIndex-1]);   //set it equal to the head
            }


            int leftIndex = currIndex*2-1;
            if(leftIndex < arrSize){
                char leftChar = a[leftIndex];
                node<T>* left = new node<T>;   

                if(leftChar != '%' && arrSize >= currIndex){
                    //cout << "Left char " << leftChar << endl; //TESTING
                    left->setData(leftChar);
                    temp->left = left;
                }
                else{
                    counter--;
                    temp->left = NULL;
                }
                delete left;
            }

            int rightIndex = currIndex*2;
            if(rightIndex < arrSize){
                char rightChar = a[rightIndex];
                node<T>* right = new node<T>;

                if(rightChar != '%' && arrSize >= currIndex){
                    //cout << "Right char " << rightChar << endl; //TESTING
                    right->setData(rightChar);
                    temp->right = right;
                }
                else{
                    counter--;
                    temp->right = NULL;
                }
                delete right;
            }
            *curr = temp;
            recInsert(a, arrSize, &temp->left, currIndex*2);
            recInsert(a, arrSize, &temp->right, currIndex*2+1);
            //delete temp;
        }
        return counter;
    }

    void inOrderTraversal(node<T>* curr){       //LPR
        //Your Code Here
        static bool firstPass; 
        if(curr == NULL){   //base case that its null
            if(firstPass == false){     //first pass it is null so get root and resend it back
                firstPass = true;       //to indicate that its past the first pass
                inOrderTraversal(root);
                firstPass = false;      //reset value for next function calls but no recursion calls
            }
            else{
                return;
            }   
        }
        else{   //recur through the tree and print
            inOrderTraversal(curr->left);
            Xyston_class_StarDestroyer tempShip = *curr->data;
            cout << tempShip.getName() << endl << flush;
            inOrderTraversal(curr->right);
        }
    }

    void inOrderTraversalNavSource(node<T>* curr){       //LPR
        //Your Code Here
        static bool firstPass; 
        if(curr == NULL){   //base case that its null
            if(firstPass == false){     //first pass it is null so get root and resend it back
                firstPass = true;       //to indicate that its past the first pass
                inOrderTraversalNavSource(root);
                firstPass = false;      //reset value for next function calls but no recursion calls
            }
            else{
                return;
            }   
        }
        else{   //recur through the tree and print
            inOrderTraversalNavSource(curr->left);
            Xyston_class_StarDestroyer tempShip = *curr->data;
            //cout << tempShip.getName() << endl << flush;
            tempShip.printNavSource();
            inOrderTraversalNavSource(curr->right);
        }
    }

    void inOrderTraversalNavSource2(node<T>* curr){
        //Your Code Here
        static bool firstPass; 
        if(curr == NULL){   //base case that its null
            if(firstPass == false){     //first pass it is null so get root and resend it back
                firstPass = true;       //to indicate that its past the first pass
                inOrderTraversalNavSource2(root);
                firstPass = false;      //reset value for next function calls but no recursion calls
            }
            else{
                return;
            }   
        }
        else{   //recur through the tree and print
            inOrderTraversalNavSource2(curr->left);
            Xyston_class_StarDestroyer tempShip = *curr->data;
            cout << tempShip.getName() << ": ";
            tempShip.printNavSource();
            inOrderTraversalNavSource2(curr->right);
        }
    }

    //Set the nav source using in order traversal
    void setNavInOrder(node<T>* curr, entity_t* navSource){
        static bool firstPass; 
        if(curr == NULL){   //base case that its null
            if(firstPass == false){     //first pass it is null so get root and resend it back
                firstPass = true;       //to indicate that its past the first pass
                setNavInOrder(root, navSource);
                firstPass = false;      //reset value for next function calls but no recursion calls
            }
            else{
                return;
            }   
        }
        else{   //recur through the tree and print
            setNavInOrder(curr->left, navSource);
            curr->data->setNavSource(&*navSource);
            setNavInOrder(curr->right, navSource);
        }
    }

    void preOrderTraversal(node<T>* curr){      //PLR
        //Your Code Here
        static bool firstPass; 
        if(curr == NULL){   //base case that its null
            if(firstPass == false){     //first pass it is null so get root and resend it back
                firstPass = true;       //to indicate that its past the first pass
                preOrderTraversal(root);
                firstPass = false;      //reset value for next function calls but no recursion calls
            }
            else{
                return;
            }   
        }
        else{   //recur through the tree and print
            cout << *curr->data << flush;
            preOrderTraversal(curr->left);
            preOrderTraversal(curr->right);
        }
    }
    void postOrderTraversal(node<T>* curr){     //LRP
        //Your Code Here
        static bool firstPass; 
        if(curr == NULL){   //base case that its null
            if(firstPass == false){     //first pass it is null so get root and resend it back
                firstPass = true;       //to indicate that its past the first pass
                postOrderTraversal(root);
                firstPass = false;      //reset value for next function calls but no recursion calls
            }
            else{
                return;
            }   
        }
        else{   //recur through the tree and print
            postOrderTraversal(curr->left);
            postOrderTraversal(curr->right);
            cout << *curr->data << flush;
        }
    }
    int getHeight(node<T> *curr){
        //Compute Height of both subtrees and keep the larger one
        if(curr == NULL) return -1; //base case
        else{
            int lheight = getHeight(curr->left); 
            int rheight = getHeight(curr->right);
            if  (lheight > rheight) return lheight+1;
            else return rheight+1;
        }
    }
    void printSpecificLevel(node<T> *root, int level){
        if(root == NULL) return;
        if(level == 1) cout << *root;
        else if(level > 1){
            printSpecificLevel(root->left, level-1);
            printSpecificLevel(root->right, level-1);
        }
    }
    void printLevelOrderTraversal(){
        for(int i=0; i <= getHeight(root); i++){
            //Your Code Here. Should be one line of code, 
            //a fucntion call to printSpecificLevel with root and i as parameters
            printSpecificLevel(root, i);
        }
    }
  protected:
    node<T> *root;
    int size;
  private:
    void DeleteTree(node<T>** curr){
        //Your Code Here
        DeleteTreeFunc(*curr);
        *curr = NULL;
    }
    void DeleteTreeFunc(node<T>* curr){
        if(curr == NULL){
            cout << "NULL\n";
            return;
        }
        else{
            if(curr->left != NULL){
                //cout << "LEFT TEMP DATA: " << *curr->left->data <<  endl; //TESTING
                DeleteTreeFunc(curr->left);
            }
            if(curr->right != NULL){
                //cout << "RIGHT TEMP DATA: " << *curr->right->data <<  endl; //TESTING
                DeleteTreeFunc(curr->right);
            }
            //cout << "TEMP DATA: " << *curr->data <<  endl; //TESTING
            delete curr;
        }

    }
};

//end of changes for ast08

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

    //Lowercase the input for if statements
    for(int i = 0; i < inputDataTypeStr.length(); i++){
         inputDataTypeStr[i] = tolower(inputDataTypeStr[i]);
    }
    if(inputDataTypeStr == "vector"){        //Runs vector version
        dataType = 2;
    }
    else if(inputDataTypeStr == "linked"){   //Runs linked list version
        dataType = 3;
    }//changes for assn 8
    else if(inputDataTypeStr == "binarytree"){
        dataType = 4;
    } //end of changes
    else{                           //Runs normal array version
        dataType = 1;
    }
    //end of changes
    //Changes to main for assn5
    string inputSortingType = "";
    int sortingType = -1;
    if(argc >= 4){  //Testing if there is some sorting request
        inputSortingType = argv[3];
        //Lowercase the input for if statements
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
    //ast08 changes
    else if(inputSortingType == "standard"){
        sortingType = 6;    //Standard Binary Search Tree
    }
    else if(inputSortingType == "avl"){
        sortingType = 7;    //AVL tree
    } //end of assn 8 changes
    //end of assn 5 changes
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

    //changes for ast08
    BinaryTree<Xyston_class_StarDestroyer> *tree = new BinaryTree<Xyston_class_StarDestroyer>;
    //end of ast08 changes

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
        else if(dataType == 4){     //changes for ast08
            //node to insert into the trees
            node<Xyston_class_StarDestroyer> *insertItem 
                = new node(Xyston_class_StarDestroyer(nameList));
            if(sortingType == 6)    //standard BST 
                tree->insertShipBinarySearch(insertItem);
            else if(sortingType ==7)    //AVL tree
                tree->insertShipAVL(insertItem);
        }//end of changes
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
    
    //change for ast08
    if(dataType == 4)
        tree->setNavInOrder(NULL, &Exogol_Tower);

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
    //ast08 change
    if(dataType ==4)
        tree->inOrderTraversalNavSource(NULL);
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
    if(dataType == 4)
        tree->setNavInOrder(NULL, &Steadfast_flagship);
    if(dataType == 4)
        tree->inOrderTraversalNavSource2(NULL);
    //end of changes
    
     //changes for ast08
    //print the entire tree in non descending order
    cout << "\nTREE IN ORDER TRAVERSAL:\n"
         << "-----------------------\n";
    tree->inOrderTraversal(NULL);
    cout << "\nEND OF TRAVERSAL\n\n\n";

    #ifdef COUNTERS
    cout << "Counters:"
         << "\nComparison counter: " << comparisonCounter
         << "\nRotation counter: " << rotationCounter 
         << "\nHeight of tree: " << tree->getHeight(tree->getRoot()) << "\n\n";
     #endif

    //end of ast08 changes

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
    //ast08 change
    delete tree;    //delete tree at the end of function

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