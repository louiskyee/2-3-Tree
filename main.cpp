#include <iostream>
#include <string>
using namespace std;
int keyReset = -999999;

class twothreeNode {
private:
public:
	int height = 0;
	int k1 = keyReset, k2 = keyReset, k3 = keyReset;	//key1=small number, key2=large number
	int N = 0;	//n key has value
	twothreeNode* left = NULL;
	twothreeNode* mid = NULL;
	twothreeNode* right = NULL;
	twothreeNode* temp = NULL;
	twothreeNode* parent = NULL;
};
struct qNode {
	twothreeNode* data = NULL;
	qNode* next = NULL;
};
class queue {
private:
	qNode* _front = NULL;
	qNode* rear = NULL;
public:
	twothreeNode* front() {
		return _front->data;
	}
	void push(twothreeNode* _data) {
		qNode* ptr = new qNode;
		ptr->data = _data;
		if (_front == NULL) {
			_front = ptr;
			rear = ptr;
			_front->next = NULL;
			rear->next = NULL;
		}
		else {
			rear->next = ptr;
			rear = ptr;
			rear->next = NULL;
		}
	}
	void pop() {
		if (_front) {
			qNode* temp = _front;
			_front = _front->next;
			delete[] temp;
			temp = NULL;
		}
	}
	bool empty() {
		if (_front == NULL) return true;
		return false;
	}
};
class twothreeTree {
private:
	twothreeNode* root = NULL;
	void swap(int& a, int& b) {
		int temp;
		temp = a;
		a = b;
		b = temp;
	}
	void sort(int N, int& a, int& b, int& c) {	////a < b < c
		if (N == 2) {
			if (a > b) {	// a > b
				swap(a, b);
			}
		}
		else if (N == 3) {
			if (b < a && a < c) {	//b < a < c
				swap(a, b);
			}
			else if (b < c && c < a) {	//b < c < a
				swap(a, b);
				swap(b, c);
			}
			else if (a < c && c < b) {	//a < c < b
				swap(b, c);
			}
			else if (c < a && a < b) {	//c < a < b
				swap(a, c);
				swap(c, b);
			}
			else if(c < b && b < a){	//c < b < a
				swap(a, c);
			}
		}
	}
	void spilt(twothreeNode* node) {
		if (node->parent == NULL) {
			twothreeNode* father = new twothreeNode;
			twothreeNode* New = new twothreeNode;
			father->k1 = node->k2; father->N++;			
			father->parent = NULL;
			father->left = node;
			father->mid = New;
			New->k1 = node->k3; New->N++;
			node->parent = father;
			New->parent = father;
			New->left = node->right;
			if (New->left != NULL) New->left->parent = New;
			New->mid = node->temp;
			if (New->mid != NULL) New->mid->parent = New;
			root = father;
			node->N -= 2;
			node->right = NULL;
			node->temp = NULL;
		}
		else {
			twothreeNode* father = node->parent;
			twothreeNode* New = new twothreeNode;
			New->k1 = node->k3; New->N++;
			New->parent = father;
			New->left = node->right;
			if (New->left != NULL) New->left->parent = New;
			New->mid = node->temp;
			if (New->mid != NULL)New->mid->parent = New;

			if (father->N == 1) {
				if (node->k2 > father->k1) {
					father->k2 = node->k2;
					father->right = New;
				}
				else {
					father->k2 = father->k1;
					father->k1 = node->k2;
					father->right = father->mid;
					father->mid = New;
				}				
			}
			else if (father->N == 2) {
				if (node->k2 > father->k2) {
					father->k3 = node->k2;
					father->temp = New;
				}
				else if (node->k2 > father->k1) {
					father->k3 = father->k2;
					father->k2 = node->k2;
					father->temp = father->right;
					father->right = New;
				}
				else {
					father->k3 = father->k2;
					father->k2 = father->k1;
					father->k1 = node->k2;
					father->temp = father->right;
					father->right = father->mid;
					father->mid = New;
				}
			}
			father->N++;
			node->N -= 2;
			node->right = NULL;
			node->temp = NULL;
			if(father->N >=3) spilt(father);
		}
	}
	void _insert(twothreeNode* node, int data) {
		if (node->left == NULL) {
			if (node->N == 0) {
				node->k1 = data;
			}
			else if (node->N == 1) {
				node->k2 = data;
			}
			else if (node->N == 2) {
				node->k3 = data;
			}
			node->N++;
			sort(node->N, node->k1, node->k2, node->k3);
			if (node->N >= 3)spilt(node);
		}
		else {
			if (data < node->k1) {		//left child
				_insert(node->left, data);
			}
			else {
				if (node->N < 2) {
					_insert(node->mid, data);
				}
				else {
					if (data < node->k2) {
						_insert(node->mid, data);
					}
					else {
						_insert(node->right, data);
					}
				}
			}
		}
	}
	void _print(twothreeNode* node) {
		//queue<twothreeNode*> qu;
		queue qu;
		int pre = 1;
		if (node == root && node) {
			if (root->N == 2) {
				printf("%d %d", node->k1, node->k2);
				if (node->left) qu.push(node->left);
				if (node->mid) qu.push(node->mid);
				if (node->right) qu.push(node->right);
			}
			else {
				printf("%d", node->k1);
				if (node->left) qu.push(node->left);
				if (node->mid) qu.push(node->mid);
			}
		}
		while (!qu.empty()) {
			if (qu.front()->height != pre) {
				printf("\n");
				pre = qu.front()->height;
			}
			else {
				printf(" / ");
			}
			if (qu.front()->N == 2) {
				printf("%d %d", qu.front()->k1, qu.front()->k2);
				if (qu.front()->left) qu.push(qu.front()->left);
				if (qu.front()->mid) qu.push(qu.front()->mid);
				if (qu.front()->right) qu.push(qu.front()->right);
			}
			else {
				printf("%d", qu.front()->k1);
				if (qu.front()->left) qu.push(qu.front()->left);
				if (qu.front()->mid) qu.push(qu.front()->mid);
			}
			qu.pop();
		}
	}
	void _get_height(twothreeNode* _node, int height) {
		_node->height = height;
		if (_node->left) {
			_get_height(_node->left, height + 1);
		}
		if (_node->mid) {
			_get_height(_node->mid, height + 1);
		}
		if (_node->right) {
			_get_height(_node->right, height + 1);
		}
	}
public:
	void insert(int _data) {
		if (root != NULL) {
			_insert(root, _data);
		}
		else {
			root = new twothreeNode;
			root->k1 = _data;
			root->N++;
			root->left = NULL;
			root->mid = NULL;
			root->right = NULL;
			root->temp = NULL;
			root->parent = NULL;
		}
	}
	void get_height() {
		_get_height(root, 1);
	}
	void print() {
		_print(root);
	}
};
int main(void) {
	twothreeTree tree;
	string str;
	getline(cin, str);
	int num = 0;
	for (int i = 0; str[i] != '\0'; ++i) {
		if (str[i] == ' ') {
			tree.insert(num);
			num = 0;
		}
		else {
			num *= 10;
			num += str[i] - '0';
		}
	}
	tree.insert(num);
	tree.get_height();
	tree.print();
}

