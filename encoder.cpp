#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include<time.h>
#include <vector>
#include <map>

using namespace std;

//Class node with data and frequency column and left right pointers
class MinNode {
	
	string data;
	int freq;
	
	MinNode *left,*right;
	
	public :
		MinNode(string data, int freq);
		MinNode* getChild(int child);
        int isLeaf();
        int getFreq();
        void set_l_r(MinNode *l, MinNode* r);
        bool isChild(int child);
        string getData();
	
	
		
};
//constructor to initialize the node class object
MinNode::MinNode(string data, int freq){
    this->data = data;
    this->freq = freq;
    this->left = this->right = NULL;
}

//function which returns the frequency of the class object
int MinNode::getFreq(){
    return this->freq;
}

//function which puts the value in left and right pointer
void MinNode::set_l_r(MinNode *l, MinNode* r){
    this->left = l;
    this->right = r;
}

// function which check whether a node is child or not
bool MinNode::isChild(int child){
    if(child == 0 and this->left){
        return true;
    }
    else if(child == 1 and this->right){
        return true;
    }
    return false;
}
// function which returns the child node
MinNode* MinNode::getChild(int child){
    if(child == 0){
        return this->left;
    }
    else{
        return this->right;
    }
}

//function to get the data part of the node
string MinNode::getData(){
    return this->data;
}

//function which check the node is leaf or not
int MinNode::isLeaf(){
    return !(this->left) && !(this->right);
}

//4way heap class 
class DHeap{
    public:
        int d;
        int currentSize;
        int size;
        MinNode **array;
    
    //constructor to initialize the 4way heap
        DHeap(int capacity)
        {
            currentSize = 3;
            d = 4;
            size = capacity + 3;
            array = new MinNode*[capacity + 3];
            for (int i = 0 ; i < capacity + 3; i++)
                array[i] = NULL;
        }
        
        // function which returns the  bool value if 4way heap is empty
         bool isEmpty()
        {
            return currentSize < 4;
        }
 
 //function which returns true if 4way heap is full
        bool isFull()
        {
            return currentSize == size;
        }
 
 //function which makes the 4way heap
        void makeEmpty()
        {
            currentSize = 3;
        }
        
        //function which return the parent of the node
         int parent(int i)
        {
            return i/d+2;
        }
 
       //function which returns the specified child in 4way heap 
        int kthChild(int i, int k)
        {
            return d * (i-2) +(k-1);
        }
        
        //function which insert the node in the 4way heap
         void insert(MinNode* temp){
            if (isFull())
            {
                cout<<"Array Out of Bounds Sorry Bro"<<endl;
                return;
            }
            int hole = currentSize;
            currentSize++;
            array[hole] = temp;
            pUp(hole);
                                   }
             
			 //function which return the min node                       
           MinNode* findMin()
        {
            if (isEmpty())
            {
                cout<<"Array Underflow Sorry Bro"<<endl;
                return 0;
            }
            return array[3];
        }
        //function which delete the root node in 4way heap
    MinNode* deleteMin(){
            if (isEmpty()){
                cout<<"Array Underflow Sorry Bro"<<endl;
                return 0;
            }
            MinNode* keyItem = array[3];
            array[3] = array[currentSize - 1];
            currentSize--;
            pDown(3);
            return keyItem;
        }
        
        //function to build the 4way heap
    void buildHeap(){
            for (int i = currentSize - 1 ; i >= 3; i--)
                pDown(i);
        }
        
        //function which is used satisfy the 4way heap property
     void pDown(int hole){
            int child;
            MinNode* tmp = array[hole];
            for ( ; kthChild(hole, 1) < currentSize; hole = child){
                child = smallestChild(hole);
                if (array[child]->getFreq() < tmp->getFreq())
                    array[hole] = array[child];
                else
                    break;
            }
            array[hole] = tmp;
        }
        
        //function which place the smallest child in 4way heap
        int smallestChild(int hole){
            int bestChildYet = kthChild(hole, 1);
            int k = 2;
            int candidateChild = kthChild(hole, k);
            while ((k <= d) && (candidateChild < currentSize))
            {
                if (array[candidateChild]->getFreq() < array[bestChildYet]->getFreq())
                    bestChildYet = candidateChild;
                k++;
                candidateChild = kthChild(hole, k);
            }
            return bestChildYet;
        }
        
        //function to move the up the 4way heap 
         void pUp(int hole){
            MinNode* tmp = array[hole];
            for (; hole > 3 && tmp->getFreq() < array[parent(hole)]->getFreq(); hole = parent(hole))
                array[hole] = array[parent(hole)];
            array[hole] = tmp;
        }
        //function to print the heap
         void printHeap(){
            for(int i=3;i<currentSize;i++)
             cout<<array[i]->getData()<<": " << cout<<array[i]->getFreq();
            cout<<endl;
        }

//funtion to set the array with data
        void set_array(int i, string data, int freq){
            this->array[i] = new MinNode(data, freq);
        }
//function to set the array size
        void set_size(int size){
            this->currentSize = size;
        }

        //function to set the minimum size
        int isSizeOne(){
            return (this->currentSize == 4);
        }
};


std::string to_string(int i)
{
    std::stringstream ss;
    ss << i;
    return ss.str();
}


//function to print the array
string arrayprint(int arr[], int n)
{
    int i;
    string temp = "";
    for (i = 3; i < n; ++i)
        temp = temp + to_string(arr[i]);
    return temp;
}

//min heap create command 
DHeap* CreateBuildFourWayHeap(map<string, int> m){
    DHeap* minHeap = new DHeap(m.size());
    int i = 3;
    for (map<string,int>::iterator it=m.begin(); it!=m.end(); ++it){
        minHeap->set_array(i, it->first, it->second);
        i++;
    }

    minHeap->set_size(m.size()+3);
    minHeap->buildHeap();
    return minHeap;
}

//Function to build the huffman tree 
MinNode* buildHuffmanTreeVasu(map<string, int> m)
{
    MinNode *left, *right, *top;

    
    DHeap* minHeap = CreateBuildFourWayHeap(m);
 
    
    while(!minHeap->isSizeOne()){
      
        left = minHeap->deleteMin();
        right = minHeap->deleteMin();
 
       
        top = new MinNode("$", left->getFreq() + right->getFreq());
        top->set_l_r(left, right);
        minHeap->insert(top);

    }
 
   
    return minHeap->deleteMin();
}

//Map to store the code_table
map<string, string> code_table;
//function to print the code table
void printingCode(MinNode* root, int arr[], int top)
{
    
    if (root->isChild(0))
    {
        arr[top] = 0;
        printingCode(root->getChild(0), arr, top + 1);
    }
 
    
    if (root->isChild(1))
    {
        arr[top] = 1;
        printingCode(root->getChild(1), arr, top + 1);
    }
 
    
    if (root->isLeaf())
    {
        code_table[root->getData()] = arrayprint(arr, top);
    }
}


//function to genrate the code table
void GenerateCodeTable(){
    ofstream out("code_table.txt");
    if (out.is_open()){
        for(map<string,string>::iterator it=code_table.begin(); it!=code_table.end(); ++it){
            out << it->first << " " << it->second << endl;
        }
        out.close();
    }
    else cout << "Unable to open file Sorry Bro" << endl;
}

//function to genrate the encoded data
void GenerateEncodedData(vector<string> v){
    FILE *myfile;
    int bit;
    int currentbit = 0;
    unsigned char bitbuffer;
    string result = "";
    for(int i=0; i<v.size(); i++)
        result += code_table[v[i]];
    myfile = fopen ("encoded.bin", "wb");
    for(int j=0; j<result.size(); j++){
        bit = result[j] - '0';
        if(bit)
            bitbuffer |= (1<<currentbit);
        currentbit++;
        if (currentbit == 8){
            fwrite(&bitbuffer, 1, 1, myfile);
            currentbit = 0;
            bitbuffer = 0;
        }
    }
    cout << result.size();
    fclose(myfile);
}

//function to print make the huffman tree
void HuffmanCodesVasu(map<string, int> m){  
  
   MinNode* root = buildHuffmanTreeVasu(m);
  
   int *arr = new int[m.size()+3];
   int top = 3;
   printingCode(root, arr, top);
   GenerateCodeTable();
}

 struct datafrequency{
    map<string, int> m;
    vector<string> v;
};


//function to read the frequency
struct datafrequency read_file(char *file){
    ifstream thefile(file);
    map<string, int> mi;
    vector<string> vi;
    struct datafrequency tmp;
    if (!thefile.is_open())
        cout<<"Could not open file Sorry Bro\n";
    else{
        string line;
        while (getline(thefile, line)){
            
            if(line!=""){
                vi.push_back(line);
                if (mi.find(line) != mi.end()){
                    mi[line]++;
                }
                else{
                    mi[line]=1;
                }
            }
        }
    }
    tmp.m = mi;
    tmp.v = vi;
    return tmp;
}

int main(int argc, char *argv[]){   
    clock_t start_time;
    if (argc != 2) 
       
        cout<<"usage: "<< argv[0] <<" <filename>\n";
    else{ 
        struct datafrequency input = read_file(argv[1]);
        start_time = clock();
       
        HuffmanCodesVasu(input.m);
       
        GenerateEncodedData(input.v);
    }
}


