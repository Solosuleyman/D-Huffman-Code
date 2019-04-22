// D-Huffman Code 
// You can input the symbols and frequency. The programme gives the code of each symbol.

#include <algorithm>
#include <iostream>
#include <list>
#include <unordered_map>
#include <vector>

using namespace std;

long N_NODES = 0;
long LENGTH_CODES = 0;
long D=2;

// Structures
class Node
{
  public:
	char data = 0;
	long frequency = 0;
    vector<Node *> children;
};

long min(long a, long b){
	if (a > b)
	return b;
	else
	{
		return a;
	}
	
}

void logo()
{
    printf("Information Theory\nHuffman Code\nCAO Jinzheng, WANG Shuting\n");
}

// Tools to print

void printHuffmanTreeInBreadth(Node *N)
{
	// prints the tree in breadth
	list<Node *> queue;

	while (N != nullptr)
	{
		cout << N->frequency << endl;
        for (auto child : N->children)
        {
            if (child != nullptr)
			queue.push_back(child);
        }

		if (queue.empty())
		{
			N = nullptr;
			continue;
		}

		N = queue.front();
		queue.pop_front();
	}
}

void printHuffmanCode(const unordered_map<char, vector<int> > &map)
{
	// prints the huffman codes
	for (const auto &P : map)
	{
		cout << P.first << " => ";
		LENGTH_CODES += P.second.size();
		for (const auto &b : P.second)
			cout << int(b);
		cout << endl; //
	}
	double avg = (LENGTH_CODES + 0.0) / N_NODES;
	cout << "Average length = " << avg << endl;
}

// Tools to use in the code
Node *takeMinNodeFromList(vector<Node *> &nodes)
{
	Node *min = nodes.front();
	for (auto *N : nodes)
		if (min->frequency > N->frequency)
			min = N;

	auto it = find(nodes.begin(), nodes.end(), min);
	nodes.erase(it, it + 1);

	return min;
}

// The main functions
unordered_map<char, long> stringToFrequencyMap() //input
{
	unordered_map<char, long> map; 
	char ch;
	long fr;
	long n;
	cout << "Number of symbols = " << endl;
	cin >> n;
	N_NODES = n;
	for (long i = 1; i <= n; i++)
	{
		cout << "Symbol " + to_string(i) + ": ";
		cin >> ch;
		cin >> fr;
		map[ch] = fr;
	}

	return map;
}

vector<Node *> buildNodesFromFrequencyMap(const unordered_map<char, long> &map)
{
	vector<Node *> nodes;

	for (const pair<char, long> &P : map)
	{
		Node *N = new Node;
		N->data = P.first;
		N->frequency = P.second;
		N->children.clear();
		nodes.push_back(N);
	}
	cout << "nodes = " << nodes.size() << endl;
	return nodes;
}

Node *buildTreeFromNodeList(vector<Node *> &nodes) 
{
    long dr=(((N_NODES-2)%(D-1))+2);
		cout << "dr= " << dr << endl;
		
		Node *parent1 = new Node; 
        for (auto i=1; i<=min(dr,nodes.size()); i++)
        {
			auto min = takeMinNodeFromList(nodes);
		    parent1->frequency += (min->frequency); 
		    parent1->children.push_back(min);
        }

		nodes.push_back(parent1);

	while (nodes.size() > 1)
	{
		Node *parent = new Node; 
		auto nn=nodes.size();
        for (auto i=1; i<=min(D,nn); i++)
        {
			auto min = takeMinNodeFromList(nodes);
            parent->frequency += (min->frequency); 
		    (parent->children).push_back(min);
        }

		nodes.push_back(parent);
	}

	return nodes.front();
}

void extractCodes(Node *root, vector<int> code,
				  unordered_map<char, vector<int> > &map)
{
	int flag=0;
	if (root->children.size()>0)
	{
		flag = 1;
		for (auto i=0; i<root->children.size(); i++)
			{
			auto codeCopy = code;
			codeCopy.push_back(i);
			extractCodes(root->children[i], codeCopy, map); 
			}
		
	}

	if (flag==0)
	{
		map[root->data] = code; 
	}
}

int main(int argc, char *argv[])
{
	logo();
	cout << "D= ";
	cin >> D;
	auto map = stringToFrequencyMap();			  
	auto nodes = buildNodesFromFrequencyMap(map); 
	auto node = buildTreeFromNodeList(nodes);	 
	unordered_map<char, vector<int> > codes;	  
	extractCodes(node, vector<int>(), codes);	

	printHuffmanTreeInBreadth(node);
	cout << endl;

	printHuffmanCode(codes);
	cout << endl;

	return 0;
}

// EXAMPLE:
// D= 3
// Number of symbols = 
// 6
// Symbol 1: a 12
// Symbol 2: b 23
// Symbol 3: c 44
// Symbol 4: d 111
// Symbol 5: e 323
// Symbol 6: f 444
// nodes = 6
// dr= 2
// 957
// 190
// 323
// 444
// 35
// 44
// 111
// 12
// 23

// f => 2
// e => 1
// d => 02
// c => 01
// b => 001
// a => 000
// Average length = 2

