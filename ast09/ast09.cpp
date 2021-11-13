//Build as: g++ ast09.cpp -g -std=c++17
//Execute as: ./a.out shipnames.txt
/*
 * Name: Matthew Shiroma, NSHE ID: 2001814396, assignment #9
 * Description: A program that uses heaps to make a piority queue
 * Inputs: ships to be ordered
 * Outputs: the ships in queue
 */
#include<iostream>
#include<string>
#include<cstdlib>
#include<ctime>
using namespace std;

class dropship{
  public:
    dropship(string n = randname(), int p = rand() % 20 + 1){
        id = count++;
        name = new string;
        *name = n;
        priority = p;
    }
    dropship operator=(dropship const &og){
        id = og.id;
        if(name == NULL)
            name = new string;
        *name = *og.name;
        priority = og.priority;
    }
    ~dropship(){
        delete name;
        name = NULL;
    }
    friend ostream & operator<< (ostream &out, const dropship *d){
        out << "Dropship #" << d->id << ", Carries: " << *d->name << " Priority " << d->priority;
        return out;
    }
    string *name;
    int priority;    
  private:
    static string randname(){
        string name = "";
        static const char str[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
        for(int i = 0; i < 6; i++){
            name += str[rand() % 62];
        }
        return name + " squad!";
    }
    int id;
    static int count;
};

int dropship::count = 0;


//added
void heapifyArr(dropship* arr[],int arrSize, int i){
    //get the left and right index value
    int leftIndex = 2 * i + 1;
    int rightIndex = 2 * i + 2;
    
    //temp var to hold the min
    //set to the parent node by default
    int minIndex = i;

    //check left child
    if(leftIndex < arrSize && arr[leftIndex]->priority > arr[minIndex]->priority){
        //within bounds and is less than so its new min
        minIndex = leftIndex;
    }

    //check right child
    if(rightIndex < arrSize && arr[rightIndex]->priority > arr[minIndex]->priority){
        //within bounds and is less than so its new min
        minIndex = rightIndex;
    }

    //some swap needs to happen
    if(minIndex != i){
        //swap
        swap(arr[i], arr[minIndex]);

        //then bubble down the heap to check lower nodes
        heapifyArr(arr, arrSize, minIndex);
    }
}

//heapify based off at index
//bubble up the heap
void heapify(dropship* arr[], int arrSize, int index){
    //get the parent of the index
    int parent = (index-1)/2;

    //check if the parent is greater than the index
    if(arr[parent]->priority > arr[index]->priority){
        //it is greater so swap them
        swap(arr[parent], arr[index]);
        //call heapify recursivly on the new parent which was the index
        heapify(arr, arrSize, parent);
    }
}

int main(){
    srand(time(0));
    cout << "Master Sergeant Farell: It’s a new day people. Destiny calls.\n"
         << "                         The world expects only one thing from us:\n" 
         << "                         that we will win.\n" << endl;

    dropship* UDF[1002];
    for(int i=0; i<1000; i++){
        UDF[i] = new dropship;
    }
    UDF[1000] = NULL;
    UDF[1001] = NULL;

    dropship j("J SQUAD", 1);
    dropship fmb("Full Metal B***h!",1);
    cout << &j << endl;
    cout << &fmb << endl;

    //My code automatically assign a priority to each dropship randomly: 1-20
    for(int i=0; i<1000; i++){
        cout << UDF[i] << endl;
    }

    //Heapify the array.
    //Your Code Here

    //starting at the index of the last non leaf node
    int arrSize = 1000;
    int nonLeafStart = (arrSize/2) - 1;
    for(int i = nonLeafStart; i >= 0; i--){
        heapifyArr(UDF,arrSize, i);
    }

    //Insert the two VIP squads.
    UDF[1000] = &j;
    //Fix Heap after insertion of J SQUAD.
    //Your Code Here
    heapify(UDF, ++arrSize, arrSize-1);

    UDF[1001] = &fmb;
    //Fix Heap after insertion of FMB.
    //Your Code Here
    heapify(UDF, ++arrSize, arrSize-1);

    //Now launch each ship by removing it from the heap. Print to screen as each ship launches.
    //e.g:  Launching Ship: 
    //Your Code Here
    nonLeafStart = (arrSize/2) - 1;
    for(int i = nonLeafStart; i >= 0; i--){
        heapifyArr(UDF,arrSize, i);
    }
    for(int i = arrSize-1; i > 0; i--){
        //swap arr at root with the last one in the arr (of the valid section)
        swap(UDF[0], UDF[i]);

        //heapify the root and any affect parts
        heapifyArr(UDF, i, 0);
    }

    //output the ships
    for(int i=0; i< arrSize; i++){
        cout << "Launching "<< UDF[i] << endl;
    }

    cout << "Master Sergeant Farell: It’s alright to be scared.\n"
         << "There is no courage without fear." << endl;

    //De-allocate to avoid memory leaks. 
    //Your Code Here
    //causes an error but deletes all memory leaks so idk
    for(int i = 0; i < arrSize; i++){
        delete UDF[i];
    }
    return 0;
}
