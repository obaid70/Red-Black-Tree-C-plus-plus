#include<iostream>
using namespace std;
#include<fstream>

template <typename T>
class stack {
private:
	T * array;
	int top;
	int size;
public:
	stack(int size)
	{
		if (this->array == nullptr)
		{
			this->array = new T[size];
			this->size = size;
			this->top = -1;
		}
		else
		{
			delete[]this->array;
			this->array = nullptr;
			this->array = new T[size];
			this->size = size;
			this->top = -1;
		}
	}
	~stack()
	{
		if (this->array != nullptr)
		{
			delete[] this->array;
			this->array = nullptr;
		}
		this->size = 0;
		this->top = 0;
	}
	void push(T val)
	{
		if (!this->isFull())
		{
			this->array[++this->top] = val;
		}
	}
	T pop()
	{
		T temp = this->peek();
		if (!this->isEmpty())
		{
			this->top--;
		}
		return temp;
	}
	T peek()
	{
		if (!this->isEmpty())
		{
			return this->array[top];
		}
		return {};
	}
	bool isEmpty()
	{
		if (this->top == -1)
		{
			return true;
		}
		return false;
	}
	void display()
	{
		if (this->array != nullptr)
		{
			if (!this->isEmpty())
			{
				cout << "\nStack[" << this->top + 1 << "] = ";
				for (int i = 0; i < this->top + 1; i++)
				{
					cout << this->array[i] << " ";
				}
				cout << endl << endl;
			}
			else
			{
				cout << "\nStack is Empty!\n\n";
			}
		}
		return;
	}
	bool isFull()
	{
		if (this->top == this->size - 1)
		{
			return true;
		}
		return false;
	}
};

struct Node
{
	int data;
	Node*leftChild;
	Node*rightChild;
	char colour;
	Node()
	{
		this->data = 0;
		this->leftChild = nullptr;
		this->rightChild = nullptr;
		this->colour = '\0';
	}
	Node(int D, Node* L, Node* R, char C)
	{
		this->data = D;
		this->leftChild = L;
		this->rightChild = R;
		this->colour = C;
	}
};

class RedBlackTree
{
private:
	Node* root;
	void Fix(Node* child)
	{
		if (this->root == child)
		{
			return;
		}
		else
		{
			Node* parent = this->GetParent(child->data);
			Node* grandparent = this->GetParent(parent->data);
			Node* uncle = nullptr;
			while (child != this->root && child->colour != 'B' && parent->colour == 'R')
			{
				parent = this->GetParent(child->data);
				grandparent = this->GetParent(this->GetParent(child->data)->data);
				if (parent == grandparent->leftChild)
				{
					uncle = grandparent->rightChild;
					if (uncle != nullptr && uncle->colour == 'R')
					{
						grandparent->colour = 'R';
						parent->colour = 'B';
						uncle->colour = 'B';
						child = grandparent;
						parent = this->GetParent(child->data);
					}
					else
					{
						if (child == parent->rightChild)
						{
							this->rotateLeft(parent);
							child = parent;
							parent = this->GetParent(child->data);
						}
						this->rotateRight(grandparent);
						char color = parent->colour;
						parent->colour = grandparent->colour;
						grandparent->colour = color;
						child = parent;
						parent = this->GetParent(child->data);
					}
				}
				else
				{
					uncle = grandparent->leftChild;
					if (uncle != nullptr && uncle->colour == 'R')
					{
						grandparent->colour = 'R';
						parent->colour = 'B';
						uncle->colour = 'B';
						child = grandparent;
						parent = this->GetParent(child->data);
					}
					else
					{
						if (child == parent->leftChild)
						{
							this->rotateRight(parent);
							child = parent;
							parent = this->GetParent(child->data);
						}
						this->rotateLeft(grandparent);
						char color = parent->colour;
						parent->colour = grandparent->colour;
						grandparent->colour = color;
						child = parent;
						parent = this->GetParent(child->data);
					}
				}
			}
		}
		this->root->colour = 'B';
	}
	void rotateRight(Node * current)
	{
		Node * Currentparent = this->GetParent(current->data);
		Node * temp = current->leftChild;
		current->leftChild = temp->rightChild;
		if (Currentparent == nullptr)
		{
			this->root = temp;
		}
		else if (current == Currentparent->leftChild)
		{
			Currentparent->leftChild = temp;
		}
		else
		{
			Currentparent->rightChild = temp;
		}
		temp->rightChild = current;
		return;
	}
	void rotateLeft(Node * current)
	{
		Node * Currentparent = this->GetParent(current->data);
		Node * temp = current->rightChild;
		current->rightChild = temp->leftChild;
		if (Currentparent == nullptr)
		{
			this->root = temp;
		}
		else if (current == Currentparent->leftChild)
		{
			Currentparent->leftChild = temp;
		}
		else
		{
			Currentparent->rightChild = temp;
		}
		temp->leftChild = current;
		return;
	}
public:
	RedBlackTree()
	{
		this->root = nullptr;
	}
	void insert(int value)
	{
		if (this->root == nullptr)
		{
			Node * newNode = new Node(value, nullptr, nullptr,'B');
			this->root = newNode;
		}
		else
		{
			Node * child = this->root;
			Node * parent = this->root;
			while (child != nullptr)
			{
				parent = child;
				if (value < child->data)
				{
					child = child->leftChild;
				}
				else if (value > child->data)
				{
					child = child->rightChild;
				}
				else
				{
					parent->data = value;
					cout << "\n\nCannot Insert Duplicate Values!\n\n";
					return;
				}
			}
			Node * newNode = new Node(value, nullptr, nullptr,'R');
			if (value < parent->data)
			{
				parent->leftChild = newNode;
				child = parent->leftChild;
			}
			else
			{
				parent->rightChild = newNode;
				child = parent->rightChild;
			}
			if (parent->colour == 'B')
			{
				return;
			}
			else
			{
				this->Fix(child);
			}
		}
		return;
	}
	Node * GetParent(int value)
	{
		if (this->root == nullptr || this->root->data == value || this->search(value) == nullptr)
		{
			return nullptr;
		}
		else
		{
			Node * current = this->root;
			Node * parent = this->root;
			Node * child = this->root;
			while (current != nullptr)
			{
				parent = child;
				child = current;
				if (value < current->data)
				{
					current = current->leftChild;
				}
				else if (value > current->data)
				{
					current = current->rightChild;
				}
				else
				{
					return parent;
				}
			}
			return nullptr;
		}
	}
	Node * search(int value)
	{
		
		if (this->root == nullptr)
		{
			return nullptr;
		}
		else
		{
			Node * current = this->root;
			while (current != nullptr)
			{
				if (value < current->data)
				{
					current = current->leftChild;
				}
				else if (value > current->data)
				{
					current = current->rightChild;
				}
				else
				{
					return current;
				}
			}
			return nullptr;
		}
	}
	void preorderNLR() const
	{
		if (this->root == nullptr)
		{
			cout << "\n\n Red Black Tree is Empty!\n\n";
			return;
		}
		cout << endl;
		stack<Node*> S(20000);
		Node * current = this->root;
		S.push(current);
		while (S.isEmpty() == false)
		{
			current = S.pop();
			cout << current->data << " (" << current->colour << ") , ";
			if (current->rightChild != nullptr)
			{
				S.push(current->rightChild);
			}
			if (current->leftChild != nullptr)
			{
				S.push(current->leftChild);
			}
		}
		cout << "\n\nRoot Node : " << this->root->data;
		cout << endl << endl;
		return;
	}
	void  inorderLNR() const
	{
		stack<Node *> S(20000);
		Node* temp = this->root;
		if (temp == nullptr)
		{
			cout << "\n\nRed Black Tree is Empty!\n\n";
			return;
		}
		cout << endl << endl;
		while (temp != nullptr || S.isEmpty() == false)
		{
			while (temp != nullptr)
			{
				S.push(temp);
				temp = temp->leftChild;
			}
			temp = S.pop();
			cout << temp->data << " (" << temp->colour << ") , ";
			temp = temp->rightChild;
		}
		cout << "\n\nRoot Node : " << this->root->data;
		cout << endl << endl;
		return;
	}
	void postorderLRN() const
	{
		if (this->root == nullptr)
		{
			cout << "\n\n Red Black Tree is Empty!\n\n";
			return;
		}
		cout << endl;
		stack<Node*> S(20000);
		stack<Node*> temp(20000);
		Node * current = this->root;
		S.push(current);
		while (S.isEmpty() == false)
		{
			current = S.pop();
			temp.push(current);
			if (current->leftChild != nullptr)
			{
				S.push(current->leftChild);
			}
			if (current->rightChild != nullptr)
			{
				S.push(current->rightChild);
			}
		}
		while (temp.isEmpty() == false)
		{
			current = temp.pop();
			cout << current->data << " (" << current->colour << ") , ";
		}
		cout << "\n\nRoot Node : " << this->root->data;
		cout << endl << endl;
		return;
	}
	void preorderNRL() const
	{
		if (this->root == nullptr)
		{
			cout << "\n\n Red Black Tree is Empty!\n\n";
			return;
		}
		cout << endl;
		stack<Node*> S(20000);
		Node * current = this->root;
		S.push(current);
		while (S.isEmpty() == false)
		{
			current = S.pop();
			cout << current->data << " (" << current->colour << ") , ";
			if (current->leftChild != nullptr)
			{
				S.push(current->leftChild);
			}
			if (current->rightChild != nullptr)
			{
				S.push(current->rightChild);
			}
		}
		cout << "\n\nRoot Node : " << this->root->data;
		cout << endl << endl;
		return;
	}
	void inorderRNL() const
	{
		stack<Node *> S(20000);
		Node* temp = this->root;
		if (temp == nullptr)
		{
			cout << "\n\nRed Black Tree is Empty!\n\n";
			return;
		}
		cout << endl;
		while (temp != nullptr || S.isEmpty() == false)
		{
			while (temp != nullptr)
			{
				S.push(temp);
				temp = temp->rightChild;
			}
			temp = S.pop();
			cout << temp->data << " (" << temp->colour << ") , ";
			temp = temp->leftChild;
		}
		cout << "\n\nRoot Node : " << this->root->data;
		cout << endl << endl;
		return;
	}
	void postorderRLN() const
	{
		if (this->root == nullptr)
		{
			cout << "\n\n Red Black Tree is Empty!\n\n";
			return;
		}
		cout << endl;
		stack<Node*> S(20000);
		stack<Node*> temp(20000);
		Node * current = this->root;
		S.push(current);
		while (S.isEmpty() == false)
		{
			current = S.pop();
			temp.push(current);
			if (current->rightChild != nullptr)
			{
				S.push(current->rightChild);
			}
			if (current->leftChild != nullptr)
			{
				S.push(current->leftChild);
			}
		}
		while (temp.isEmpty() == false)
		{
			current = temp.pop();
			cout << current->data << " (" << current->colour << ") , ";
		}
		cout << "\n\nRoot Node : " << this->root->data;
		cout << endl << endl;
		return;
	}
	void destroy()
	{
		if (this->root == nullptr)
		{
			cout << "\n\n Red Black Tree is Already Empty!\n\n";
			return;
		}
		stack<Node*> S(20000);
		stack<Node*> temp(20000);
		Node * current = this->root;
		S.push(current);
		while (S.isEmpty() == false)
		{
			current = S.pop();
			temp.push(current);
			if (current->leftChild != nullptr)
			{
				S.push(current->leftChild);
			}
			if (current->rightChild != nullptr)
			{
				S.push(current->rightChild);
			}
		}
		while (temp.isEmpty() == false)
		{
			current = temp.pop();
			delete current;
			current = nullptr;
		}
		this->root = nullptr;
		cout << "\n\nRed Black Tree Destroyed Successfully!\n\n";
		return;
	}
};

int main()
{
	RedBlackTree tree;
	int choice = 0, num = 0, value = 0;
	while (choice != 14)
	{
		cout << "\n\n					Red Black Binary Search Tree Project : \n\n";
		cout << "\n1.Press 1 to insert values one by one in the tree.\n";
		cout << "\n2.Press 2 to delete a value from the tree .\n";
		cout << "\n3.Press 3 to search a value from the tree.\n";
		cout << "\n4.Press 4 to pre-order traversal NLR.\n";
		cout << "\n5.Press 5 to in-order traversal LNR.\n";
		cout << "\n6.Press 6 to post-order traversal LRN.\n";
		cout << "\n7.Press 7 to pre-order traversal 2 NRL.\n";
		cout << "\n8.Press 8 to in-order traversal 2 RNL.\n";
		cout << "\n9.Press 9 to post-order traversal 2 RLN.\n";
		cout << "\n10.Press 10 to destroy the tree.\n";
		cout << "\n11.Press 11 to delete all values in the tree greater than X.\n";
		cout << "\n12.Press 12 to for displaying parent of a node present in Tree.\n";
		cout << "\n13.Press 13 to to read integer values from the file \"input.txt\" to create a red black tree.\n";
		cout << "\n14.Press 14 to EXIT from program.\n";
		cout << "\n\nPlease select a choice (1-14) : ";
		cin >> choice;
		cin.ignore();
		while (choice < 1 || choice >14)
		{
			cout << "\n\nPlease select a valid choice (1-14) : ";
			cin >> choice;
			cin.ignore();
		}
		system("CLS");
		if (choice == 1)
		{
			cout << "\nPlease enter value to Insert : ";
			cin >> value;
			cin.ignore();
			if (tree.search(value) == nullptr)
			{
				tree.insert(value);
				cout << "\n\nNode Inserted Successfully!\n\n";
			}
			else
			{
				cout << "\n\nNode with Given Value Already Exists!\n\n";
			}
			system("pause");
		}
		else if (choice == 2)
		{
			cout << "\n\nDeletion of Red Black Tree Not Attempted! ( As it is Bonus/Optional )\n\n";
			system("pause");
		}
		else if (choice == 3)
		{
			cout << "\nPlease enter value to Search : ";
			cin >> num;
			cin.ignore();
			Node * temp = tree.search(num);
			if (temp == nullptr)
			{
				cout << "\n\nNode with Given Value Not Found!\n\n";
			}
			else
			{
				cout << "\n\nNode with Given Value Found!\n\n";
				cout << "\nValue : " << temp->data;
				if (temp->colour == 'R')
				{
					cout << "\n\n\nColour : Red\n\n";
				}
				else
				{
					cout << "\n\n\nColour : Black\n\n";
				}
			}
			system("pause");
		}
		else if (choice == 4)
		{
			cout << "\n\nPre-Order Traversal NLR : \n";
			tree.preorderNLR();
			system("pause");
		}
		else if (choice == 5)
		{
			cout << "\n\nIn-Order Traversal LNR : \n";
			tree.inorderLNR();
			system("pause");
		}
		else if (choice == 6)
		{
			cout << "\n\nPost-Order Traversal LRN : \n";
			tree.postorderLRN();
			system("pause");
		}
		else if (choice == 7)
		{
			cout << "\n\nPre-Order Traversal NRL : \n";
			tree.preorderNRL();
			system("pause");
		}
		else if (choice == 8)
		{
			cout << "\n\nIn-Order Traversal RNL : \n";
			tree.inorderRNL();
			system("pause");
		}
		else if (choice == 9)
		{
			cout << "\n\nPost-Order Traversal RLN : \n";
			tree.postorderRLN();
			system("pause");
		}
		else if (choice == 10)
		{
			tree.destroy();
			system("pause");
		}
		else if (choice == 11)
		{
			cout << "\n\nDeletion of Red Black Tree Not Attempted! ( As it is Bonus/Optional )\n\n";
			system("pause");
		}
		else if (choice == 12)
		{
			cout << "\nPlease enter value to Display Parent of a Node : ";
			cin >> value;
			cin.ignore();
			if (tree.search(value) != nullptr)
			{
				Node * parent = tree.GetParent(value);
				if (parent != nullptr)
				{
					cout << "\n\nParent Node Details :-";
					cout << "\n\nValue : " << parent->data;
					if (parent->colour == 'B')
					{
						cout << "\n\nColour : Black\n\n";
					}
					else
					{
						cout << "\n\nColour : Red\n\n";
					}
				}
				else
				{
					cout << "\n\nParent of Given Node Does not Exist!\n\n";
				}
			}
			else
			{
				cout << "\n\nNode with Given Value Does Not Exist in the Tree!\n\n";
			}
			system("pause");
		}
		else if (choice == 13)
		{
			tree.destroy();
			system("CLS");
			ifstream fin("input.txt");
			int num = 0;
			if (fin.is_open() == true)
			{
				while (fin >> num)
				{
					tree.insert(num);
				}
				cout << "\n\nTree Created from \"input.txt\" file Successfully!\n\n";
				fin.close();
			}
			else
			{
				cout << "\n\n\"input.txt\" File not Opening for Reading Data.\n\n";
			}
			system("pause");
		}
		else if (choice == 14)
		{
			cout << "\n\nThank You for using the program!\n\n";
			break;
		}
		system("CLS");
	}
	return 0;
}