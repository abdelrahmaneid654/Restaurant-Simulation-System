#include <iostream>
#include <string>
using namespace std;

class Node
{
private:
	int data;
	Node* left;
	Node* right;
public:
	Node(int val);
	Node();
	void setdata(int d);
	int getdata();
	void setright(Node* p);
	Node*& getright();

	void setleft(Node* p);
	Node*& getleft();



};

Node::Node(int val)
{
	data = val;
	left = right = nullptr;
}
Node::Node()
{
	data = -111;
	left = right = nullptr;
}


void Node::setdata(int d)
{
	data = d;
}
int Node::getdata()
{
	return data;
}
void Node::setleft(Node* p)
{
	left = p;
}
Node*& Node::getleft()
{
	return left;
}
void Node::setright(Node* p)
{
	right = p;
}
Node*& Node::getright()
{
	return right;
}





class BSTree
{
private:
	Node* root;

	// Utility Functions - Recursive Functions --------------------------

	// Given functions
	static void rec_insertBST(Node*& subRoot, int key);
	static void rec_inorder_traverse(Node* subRoot);
	static void rec_preorder_traverse(Node* subRoot);
	static void rec_postorder_traverse(Node* subRoot);
	static void rec_destroy_tree(Node*& subRoot);

	//Functions to be implemented by student
	static Node* rec_find_max(Node* subRoot);
	static Node* rec_find_min(Node* subRoot);
	static int rec_max_depth(Node* subRoot);
	static void addTrees(Node*& subRoot1, Node* subroot2);
	void rec_printBT(const std::string& prefix, Node* node, bool isLeft);

public:
	void printBT();


	BSTree(void);
	~BSTree(void);
	BSTree(const BSTree& T);
	Node* copyconc(Node* subroot);
	void addTrees(BSTree& T1);

	void insertBST(int key); // not const
	void inorder_traverse() const;
	void preorder_traverse() const;
	void postorder_traverse() const;
	void destroy_tree(); // not const


	Node* find_max() const;
	Node* find_min() const;
	int max_depth() const;


	static void count(Node*& subroot)
	{



		if (!subroot)return;
		if (!subroot->getleft() && !subroot->getright())
		{
			delete subroot;
			subroot = nullptr;
			return;
		}



		count(subroot->getleft());
		count(subroot->getright());
	}

	void countN()
	{
		count(root);

	}
};



void BSTree::addTrees(Node*& subroot1, Node* subroot2)
{
	if (!subroot1 && subroot2)
	{
		subroot1 = new Node(subroot2->getdata());
	}
	else if (!subroot2 && subroot1)
	{
		return;
	}
	else if (!subroot1 && !subroot2)
	{
		return;
	}
	else {
		subroot1->setdata(subroot2->getdata() + subroot1->getdata());
	}
	addTrees(subroot1->getright(), subroot2->getright());
	addTrees(subroot1->getleft(), subroot2->getleft());



}







void BSTree::rec_insertBST(Node*& subRoot, int key)
{
	if (subRoot == nullptr)
		subRoot = new Node(key); // this line is why we pass subRoot by reference (subRoot = something)
	else if (subRoot->getdata() < key)
	{

		//recursively call insert for the right subtree
		rec_insertBST(subRoot->getright(), key);

	}
	else
	{
		// recursive call on left
		rec_insertBST(subRoot->getleft(), key);
	}
}

void BSTree::rec_inorder_traverse(Node* subRoot)
{
	if (subRoot == nullptr) return;
	rec_inorder_traverse(subRoot->getleft());
	cout << subRoot->getdata() << " ";
	rec_inorder_traverse(subRoot->getright());
}

void BSTree::rec_preorder_traverse(Node* subRoot)
{
	if (subRoot == nullptr) return;
	cout << subRoot->getdata() << "  ";
	rec_preorder_traverse(subRoot->getleft());
	rec_preorder_traverse(subRoot->getright());
}

void BSTree::rec_postorder_traverse(Node* subRoot)
{
	if (subRoot == nullptr) return;
	rec_postorder_traverse(subRoot->getleft());
	rec_postorder_traverse(subRoot->getright());
	cout << subRoot->getdata() << "  ";
}

void BSTree::rec_destroy_tree(Node*& subRoot)
{
	if (subRoot != nullptr)
	{
		// recursive call on left
		rec_destroy_tree(subRoot->getleft());

		// recursive call on right
		rec_destroy_tree(subRoot->getright());

		delete subRoot;
		subRoot = nullptr; // this line is why we pass subRoot by reference (subRoot = something)
	}
}

Node* BSTree::rec_find_max(Node* subRoot)
{
	//TO DO
	return nullptr; // should be changed
}
Node* BSTree::rec_find_min(Node* subRoot)
{
	//TO DO
	return nullptr; // should be changed
}
int BSTree::rec_max_depth(Node* subRoot)
{
	//TO DO
	return 0; // should be changed
}

void BSTree::rec_printBT(const std::string& prefix, Node* node, bool isLeft)
{
	if (node != nullptr)
	{
		cout << prefix;

		cout << (isLeft ? "L─" : "─R─");

		// print the value of the node
		cout << "(" << node->getdata() << ") " << std::endl;
		//string 
		// enter the next tree level - left and right branch
		rec_printBT(prefix + (isLeft ? "│   " : "    "), node->getleft(), true);
		rec_printBT(prefix + (isLeft ? "│   " : "    "), node->getright(), false);
	}
}


Node* BSTree::copyconc(Node* subroot)
{
	if (subroot == NULL)
	{
		return nullptr;
	}
	Node* N = new Node(subroot->getdata());
	copyconc(subroot->getleft());
	copyconc(subroot->getright());
	return N;


}
BSTree::BSTree()
{
	root = nullptr;
}
BSTree::BSTree(const BSTree& T)
{
	this->root = copyconc(T.root);


}

BSTree::~BSTree()
{
	destroy_tree();
}

// Public Functions ---------------------------------

// Given functions
void BSTree::insertBST(int key) // not const
{
	// not const because rec_insertBST takes the root by reference, so may change it
	rec_insertBST(root, key);
}
void BSTree::inorder_traverse() const
{
	rec_inorder_traverse(root);
}
void BSTree::preorder_traverse() const
{
	rec_preorder_traverse(root);
}
void BSTree::postorder_traverse() const
{
	rec_postorder_traverse(root);
}
void BSTree::destroy_tree() // not const
{
	rec_destroy_tree(root);
}

void BSTree::printBT()
{
	cout << "\nPrinting BT, L means Left Child, R means Right Child (or Root)\n";
	rec_printBT("", root, false);
	cout << endl;
}


Node* BSTree::find_max() const // return a pointer to the node that hold the maximum value in binary search tree.
{
	//TO DO
	return nullptr; // should be changed
}
Node* BSTree::find_min() const // return a pointer to the node that hold the minimum value in binary search tree.
{
	//TO DO
	return nullptr; // should be changed
}
int BSTree::max_depth() const
{
	//TO DO
	return 0; // should be changed
}


void BSTree::addTrees(BSTree& T1)
{
	addTrees(root, T1.root);

}






int main()
{
	int x, n = 0;
	BSTree tree1, tree2;
	cin >> n;
	for (int i = 0; i < n; i++)
	{
		cin >> x;
		tree1.insertBST(x);
	}
	//cin >> n;
	/*for (int i = 0; i < n; i++)
	{
		cin >> x;
		tree2.insertBST(x);
	}
	tree1.addTrees(tree2);
*/
	tree1.countN();
	tree1.preorder_traverse();

	tree1.destroy_tree();
	//tree2.destroy_tree();
	return 0;
}