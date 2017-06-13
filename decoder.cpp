#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
using namespace std;

//Class minNode for 4way heap 
class MinNode{
	public:
	    string data;  
	    MinNode *left, *right; 
		MinNode(string data){
			this->data = data;
			left = NULL;
			right = NULL;
		}
};
//funtion which reads the file 
vector<int> FileReadDecode(string filename){
	ifstream f(filename.c_str(), ios::binary | ios::in);
	vector<int> v;
	char c;
	int bit;
	while (f.get(c)){
	    for(int i = 0; i <8; i++){
	    	bit = (c >> i) & 1;
	        v.push_back(bit);
	    }
	}
	return v;
}

//function to build the huffman tree
MinNode *buildHuffmanVasu(string filename){
	map<string, string> m;
	MinNode* root = new MinNode("$");
	MinNode* head = root;
	MinNode *temp = root;

	ifstream the_file(filename.c_str());
    if (!the_file.is_open())
        cout<<"File Could not open Sorry Bro\n";
    else{
        string key, value;
        while (the_file >> key >> value){
        	m[key] = value;
	    }

	}

	
	for (map<string,string>::iterator it=m.begin(); it!=m.end(); ++it){
		root = temp;
    	for (int i=0; i < it->second.size(); i++){
	        if(it->second[i]=='0'){
	        	if(!root->left)
	        		root->left = new MinNode("$");
	        	root = root->left;
	        }
	        else{
	        	if(!root->right)
	        		root->right = new MinNode("$");
	        	root = root->right;
	        }
    	}
    	root->data = it->first;
    }
    return head;
}


//function to decode the tree
void DecodeVasu(MinNode* root, vector<int> v){
	MinNode* head = root;
	ofstream myfile("decoded.txt");
    int i;
    if (!myfile.is_open())
        cout<<"file could not open Sorry Bro\n";
    else{
	    for(i = 0; i<v.size(); i++){
	    	if(v[i])
	            root = root->right;
	        else
	            root = root->left;

	        if(!root->left && !root->right){
	            myfile << root->data << endl;
	            root = head;
	        }
	    }
	}
	myfile.close();
}

/*int main()
{
	vector<int> v = FileReadDecode("encoded_fw.bin");
		MinNode* head = buildHuffmanVasu("code_table_fw.txt");
		DecodeVasu(head,v);
		return 0;
} */

int main(int argc, char *argv[]){
	if(argc != 3)
    	cout<<"usage: "<< argv[0] <<" <filename> " << "<filename> " << endl;
  	else{
		vector<int> v = FileReadDecode(argv[1]);
		MinNode* head = buildHuffmanVasu(argv[2]);
		//generates a decoded file named decoded.txt
		DecodeVasu(head, v);
	}
	return 0;
}

