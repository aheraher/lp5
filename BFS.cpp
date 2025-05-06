#include<iostream>
#include<cstdio>
#include<queue>
#include<omp.h>
using namespace std;

class node
{
	public:
		node *left, *right;
		int data;
};

class breadthfs
{
	public:
		node *insert(node*, int);
		void bfs(node*);
};


node *insert(node *root, int data){
	if(!root)
	{
		root=new node;
		root->left=NULL;
		root->right=NULL;
		root->data=data;
		return root;
	}
	
	queue<node*>q;
	q.push(root);
	
	while(!q.empty())
	{
		node *temp=q.front();
		q.pop();
		
		if(temp->left==NULL)
		{
			temp->left=new node;
			temp->left->left=NULL;
			temp->left->right=NULL;
			temp->left->data=data;
			return root;
		}
		else
		{
			q.push(temp->left);
		}
		
		
		if(temp->right==NULL)
		{
			temp->right=new node;
			temp->right->left=NULL;
			temp->right->right=NULL;
			temp->right->data=data;
			return root;
		}
		else
		{
			q.push(temp->right);
		}
	}
}


//void bfs(node *head){
//	queue<node*>q;
//	q.push(head);
//
//	int qsize;
//
//
//	while(!q.empty())
//	{
//		#pragma omp parallel for
//
//		for(int i=0;i<qsize;i++)
//		{
//			node* currNode;
//			#pragma omp critical
//			{
//				currNode=q.front();
//				q.pop();
//				cout<<"\t"<<currNode->data;
//			}
//
//			#pragma omp critical
//			{
//				if(currNode->left)
//					q.push(currNode->left);
//				if(currNode->right)
//					q.push(currNode->right);
//			}
//		}
//	}
//
//}



void bfs(node *head) {
    if (!head) return;

    queue<node*> q;
    q.push(head);

    while (!q.empty()) {
        int qsize = q.size();  // Fix: Properly initialize

        #pragma omp parallel for
        for (int i = 0; i < qsize; i++) {
            node* currNode;

            #pragma omp critical
            {
                currNode = q.front();
                q.pop();
                cout << "\t" << currNode->data;
            }

            #pragma omp critical
            {
                if (currNode->left)
                    q.push(currNode->left);
                if (currNode->right)
                    q.push(currNode->right);
            }
        }
    }
}




	int main()
	{
		node *root=NULL;
		int data;
		char ans;
		
		do
		{
			cout<<"\n Enter data: ";
			cin>>data;
			
			root=insert(root,data);
			
			cout<<"Do you want to insert one more number?";
			cin>>ans;
			
		}while(ans=='y'||ans=='Y');
		
		bfs(root);
		
		return 0;
	}



