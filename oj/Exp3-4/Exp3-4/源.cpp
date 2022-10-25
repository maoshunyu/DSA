#include <stdio.h>
#pragma warning(disable:4996)
using namespace std;
typedef struct node {
	int data;
	int prev;
	node* lchild, * rchild;
}node;
node* root;
void insert(node*& head, int d) {
	if (head == NULL) {
		node* n = new node();
		n->data = d;
		n->lchild = NULL;
		n->rchild = NULL;
		head = n;
		return;
	}

	if (head->data < d) {
		insert(head->rchild, d);
	}
	else {
		insert(head->lchild, d);
	}
}
void create(node*& head) {
	int len;
	scanf("%d", &len);
	while (len-- > 0) {
		int d;
		scanf("%d", &d);
		insert(head, d);
	}
}


node* inorderSuc(node* root, node* p) {
	if (p == NULL || root == NULL) {
		return NULL;
	}
	node* cur = root;
	node* res = NULL;
	while (cur != NULL) {
		if (cur->data <= p->data) {
			cur = cur->rchild;
		}
		else {
			if (res == NULL || res->data > cur->data) {
				res = cur;
			}
			cur = cur->lchild;
		}
	}
	return res;
}
int getmax(node* p) {
	if (p == NULL)return -1;
	if (p->lchild == NULL && p->rchild == NULL)return p->data;
	int max = p->data;
	int maxl = getmax(p->lchild);
	int maxr = getmax(p->rchild);
	if (maxl >= max) max = maxl;
	if (maxr > max) max = maxr;
	return max;
}


int inorder(node* head) {
	if (head == NULL)return 0;
	if (head->lchild != NULL) {
		head->prev = getmax(head->lchild);
	}
	else if (head->rchild) {
		head->prev = -1;
	}
	else {
		if (inorderSuc(root, head) != NULL) {
			delete head;
			head = NULL;
			return -1;
		}
		else {
			head->prev = -1;
		}
	}
	if (inorder(head->lchild) == -1)head->lchild = NULL;
	if (inorder(head->rchild) == -1)head->rchild = NULL;
	return 0;
	
}
void preorder(node*& head) {
	if (head == NULL) return;
	printf("%d ", head->data);

	if (head->prev == -1) {
		printf("- ");
	}
	else printf("%d ", head->prev);
	preorder(head->lchild);
	preorder(head->rchild);
}
int main() {
	create(root);
	inorder(root);
	preorder(root);

}