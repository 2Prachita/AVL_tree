#include<stdio.h> 
#include<stdlib.h>
#include<string.h>
#include "AVL.h"

// KEY IS SUBJECT CODE AS WELL AS ROLL NO
//PRIOROTY IS GIVEN TO SUBJECT CODE THEN THE ROLL NO

AVL* insertion( AVL *root, AVL *node )
{
	AVL *ret_ptr=root;
	if(root==NULL)
	{
		ret_ptr=node;
		root=ret_ptr;
		printf("                                               -----  INSERTED SUCCESFULLY  ----- \n");
	}
	else
	{
		if(strcmp(node->sc,root->sc)<0)	
		{
			root->left=insertion(root->left,node);
	//		printf("l");
		}
		else if(strcmp(node->sc,root->sc)>0)
		{
			root->right=insertion(root->right,node);
	//		printf("r");
		}
		else if(strcmp(node->sc,root->sc)==0)
		{
			if(node->roll<root->roll)
			{
				root->left=insertion(root->left,node);
	//		printf("l");				
			}
			else if(node->roll>root->roll)
			{
				root->right=insertion(root->right,node);
	//		printf("r");
			}
			else if(node->roll=root->roll)
			{
				strcpy(root->name,node->name);
				strcpy(root->dp,node->dp);
				root->sem=node->sem;
				root->marks=node->marks;
				printf("                                                -----  UPDATED DATABASE  -----\n");	
			}
		}
	}
	root->ht=height(root);
	ret_ptr=balance(root);
	return(ret_ptr);
}

AVL* balance( AVL *root )
{
	int b,c_b;
	b=height(root->left)-height(root->right);
	if(b==2)
	{
		c_b=height(root->left->left)-height(root->left->right);
		if(c_b==-1)
		{
			root->left=RL(root->left);
			printf("rotate left\n");
		}
		root=RR(root);
		printf("rotate right\n");
	}
	else if(b==-2)
	{
		c_b=height(root->right->left)-height(root->right->right);
		if(c_b==1)
		{
			root->right=RR(root->right);
			printf("rotate right\n");
		}
		root=RL(root);
		printf("rotate left\n");

	}
	return(root);
}

AVL* RR( AVL *root)
{
	AVL *temp;
	if(root==NULL)
	{
		printf("ERROR\n");	
	}	
	else if(root->left==NULL)
	{
		printf("cannot rotate\n");
	}
	else
	{
		temp=root->left;
		root->left=temp->right;
		temp->right=root;
	}
	return(temp);
}

AVL* RL( AVL *root)
{
	AVL *temp;
	if(root==NULL)
	{
		printf("ERROR\n");	
	}	
	else if(root->right==NULL)
	{
		printf("cannot rotate\n");
	}
	else
	{
		temp=root->right;
		root->right=temp->left;
		temp->left=root;
	}
	return(temp);
}



int search( AVL *root, AVL *element )
{
	int ret_val=0;
	if(root==NULL)
	{
		printf("\n THE DATABASE DOES NOT HAVE %s WITH %d ROLL NO.",element->sc,element->roll);
	}
	else if(root!=NULL)
	{
		if(strcmp(element->sc,root->sc)<0)
		{
			ret_val=search(root->left,element);
		}
		else if(strcmp(element->sc,root->sc)>0)
		{
			ret_val=search(root->right,element);
		}
		else if(strcmp(element->sc,root->sc)==0)
		{
			 if(element->roll<root->roll)
			{
				ret_val=search(root->left,element);
			}
			else if(element->roll>root->roll)
			{
				ret_val=search(root->right,element);
			}
			else if(element->roll==root->roll)
			{
				ret_val=1;
				print_record(root);
				return(ret_val);
			}
		}
	}
	return(ret_val);
}

int height ( AVL *root)
{
	int ret=0,l,r;
	if(root==NULL)
	{
		l=-1;
		r=-1;	
	}
	else if(root!=NULL)
	{
		if(root->left==NULL&&root->right==NULL)
		{
			l=0;
			r=0;
		}
		else //if(root->left!=NULL&&root->right!=NULL)
		{
			l=height(root->left);
			r=height(root->right);
		}
	}
	if(l>r)
	{
		ret=1+l;
	}
	else
	{
		ret=1+r;
	}
	return(ret);
}

void range_search( AVL *root , int key1 ,int key2)
{
	int k1,k2;
	k1=key1;
	k2=key2;
	if(root!=NULL)
	{
		range_search(root->left,k1,k2);
		if((root->roll)>=k1&&root->roll<=k2)
		{
			print_record(root);
		}
		range_search(root->right,k1,k2);
	}
}

int num_nodes( AVL *root )
{
	int ret_val;
	if(root==NULL)
	{
		ret_val=0;
	}
	else if(root!=NULL)
	{
		ret_val=1+num_nodes(root->left)+num_nodes(root->right);
	}
	return(ret_val);
}

AVL* get_max( AVL *root, AVL *sub_code)
{
	AVL *ret_ptr;//chk the return if marks 0 then no one has opted for course or this sub is not peresent in database
	ret_ptr=sub_code;
	if(root!=NULL)
	{
		if(strcmp(sub_code->sc,root->sc)==0)
		{
			if(sub_code->marks<root->marks)
			{
				ret_ptr=root;
				ret_ptr=get_max(root->right,root);
			}
		}
		else if(strcmp(sub_code->sc,root->sc)<0)
		{
			ret_ptr=get_max(root->left,sub_code);
		}
		else if(strcmp(sub_code->sc,root->sc)>0)
		{
			ret_ptr=get_max(root->right,sub_code);
		}
	}
	return(ret_ptr);
}

void failure ( AVL *root,AVL *key )//key contain subject code and the passing marks
{	
	if(root!=NULL)
	{
		failure(root->left,key);
		if((strcmp(root->sc,key->sc)==0)&&(root->marks<key->marks))
		{
			print_record(root);			
		}
		failure(root->right,key);
	}
}

AVL* deletion( AVL *root,AVL *del )
{
	AVL* ret_ptr=root,*ptr;
	if(root==NULL)
	{
		printf("\n RECORD NOT PRESENT IN DATABASE \n");
		
	}
	else if(root!=NULL)
	{
	//	printf("knknkn\n");
		if(strcmp(del->sc,root->sc)<0)
		{
			root->left=deletion(root->left,del);
	//		printf("l");
		}
		else if(strcmp(del->sc,root->sc)>0)
		{
			root->right=deletion(root->right,del);
	//		printf("r");
		}
		else if(strcmp(del->sc,root->sc)==0)
		{
			if((del->roll)<(root->roll))
			{
				root->left=deletion(root->left,del);
	//			printf("l");
			}
			else if((del->roll)>(root->roll))
			{
				root->right=deletion(root->right,del);
	//			printf("r");
			}
			else if((del->roll)==(root->roll))
			{
				if(root->left==NULL && root->right==NULL)  //leaf node
				{
					ptr=root;
					root=NULL;
					free(ptr);
					ret_ptr=root;
				}
				else if(root->left!=NULL && root->right==NULL)  //single child (left)
				{
					ret_ptr=root->left;
					root->left=NULL;
					root->right=NULL;
					ptr=root;
					free(ptr);
					root=ret_ptr;	
				}
				else if(root->left==NULL && root->right!=NULL)  //single child (right)
				{
					ret_ptr=root->right;
					root->right=NULL;
					root->left=NULL;
					ptr=root;
					free(ptr);
					root=ret_ptr;	
				}
				else if(root->left!=NULL && root->right!=NULL)
				{
	//				printf("boo\n");
					ret_ptr=root->right;
					if(ret_ptr->left==NULL&&ret_ptr->right==NULL)
					{
	//					printf("boo1\n");
						ret_ptr->left=root->left;
					//	ret_ptr->right=NULL;
						//ret_ptr->right=balance(ret_ptr->right);
					//	ptr=root;
					}
					else if(ret_ptr->left==NULL&&ret_ptr->right!=NULL)
					{
	//					printf("boo2\n");
						ret_ptr->left=root->left;
					//	ptr=root;
					}
					else if(ret_ptr->left!=NULL&&ret_ptr->right==NULL)
					{
	//					printf("boo3\n");
						ret_ptr=min(root->right);
						ret_ptr->left=root->left;
						ret_ptr->right=root->right;
						//ret_ptr->right=balance(ret_ptr->right);
					//	ptr=root;
					}
					else if(ret_ptr->left!=NULL&&ret_ptr->right!=NULL)
					{
	//					printf("boo4\n");
						ret_ptr=min(root->right);
						ret_ptr->left=root->left;
						ret_ptr->right=root->right;
						ret_ptr->right=balance(ret_ptr->right);
					//	ptr=root;
					}
					root->left=NULL;
					root->right=NULL;
					ptr=root;
					free(root);
					root=ret_ptr;
	//				printf("jjjjj\n");		
				}
			}
		}
	}
	if(root==NULL)
	{
		return(root);
	}
	else
	{
		root->ht=height(root);
	//	root->right=balance(root->right);
		ret_ptr=balance(root);
	}
	return(ret_ptr);
}

AVL* min( AVL *root)
{
	AVL *prv=root,*current=root;
	//printf("min1\n");
	while(current->left!=NULL)
	{
	//	printf("min3\n");
		prv=current;
		current=current->left;	
	}
	//printf("min6\n");
	prv->left=NULL;
	return(current);
}

AVL* get_Highest( AVL *root, AVL *lo, AVL *high)
{
	AVL *ret=lo;
	if(root!=NULL)
	{
		if(lo->marks>=high->marks)
		{
			ret=NULL;
			return(ret);
		}
		else
		{
			ret=get_Highest(root->left,lo,high);
			lo=ret;
			if( strcmp(root->sc,high->sc)==0 && (root->marks>lo->marks) && (root->marks<high->marks) )
			{
				ret=root;
				lo=root;
			}
			ret=get_Highest(root->right,lo,high);
		}
	}
	return(ret);
}

AVL* kth_Highest( AVL *root, int k )
{
	AVL *lo,*h,*ret_ptr=NULL;
	int i;
	lo=(AVL*)malloc(sizeof(AVL));
	h=(AVL*)malloc(sizeof(AVL));
	printf("\n ENTER THE SUBJECT CODE \n");
	scanf("%s",lo->sc);
	strcpy(h->sc,lo->sc);
	h->marks=101;
	lo->marks=0;
	if(root!=NULL)
	{
		for(i=0;i<k;i++)
		{
			ret_ptr=get_Highest(root,lo,h);
			if(ret_ptr==NULL)
			{
				return(ret_ptr);
			}
			else
			{
				h=ret_ptr;
			}
		}
	}
	if(ret_ptr->marks==0 && strcmp(ret_ptr->sc,lo->sc))
	{
		ret_ptr=NULL;
	}
	return(ret_ptr);
}

AVL* topInsert( AVL *root, AVL *node )
{
	AVL *ret=root;
	if(root==NULL)
	{
		ret=node;
		root=ret;
	}
	else
	{
		if(node->roll<root->roll)
		{
			root->left=topInsert(root->left,node);
		}
		else if(node->roll>root->roll)
		{
			root->right=topInsert(root->right,node);
		}
		else if(node->roll==root->roll)
		{
			root->marks=root->marks+node->marks;
		}
	}
	root->ht=height(root);
	ret=balance(root);
	inorder( root );
	return(root);
}

AVL* newtree( AVL *root )
{
	AVL *neew=NULL,*node;
	if(root!=NULL)
	{
		neew=newtree(root->left);
		node=(AVL*)malloc(sizeof(AVL));
		node->marks=root->marks;
		node->sem=root->sem;
		node->roll=root->roll;
		node->left=NULL;
		node->right=NULL;
		strcpy(node->name,root->name);
		strcpy(node->dp,root->dp);
		strcpy(node->sc,"Total");
		neew=topInsert(neew,node);
		neew=newtree(root->right);
	}
	return(neew);
}

AVL* topper( )
{
	AVL *h=NULL,*ret,*temp;
	h=newtree(h);
	temp=(AVL*)malloc(sizeof(AVL));
	temp->marks=0;
	strcmp(temp->sc,"Total");
	ret=get_max(h,temp);
	return(ret);
}

/*AVL* balancing( AVL *root )
{
	AVL* ret=root;
	if(root!=NULL)
	{
		root->left=balancing(root->left);
	//	ret=balance()
		root->right=balancing(root->right);
	}
	return(ret);
}*/

void visit( AVL *root )
{
	printf("\nNAME OF STUDENT : %s",root->name);
	printf("\nSUBJECT CODE    : %s",root->sc);
	printf("\nDEPARTMENT      : %s",root->dp);
	printf("\nROLL NO         : %d",root->roll);
	printf("\nSEMESTER        : %d",root->sem);
	printf("\nMARKS           : %d\n",root->marks);
}

void preorder( AVL *root)
{
	if(root!=NULL)
	{
		visit(root);
		preorder( root->left );
		preorder( root->right );
	}
}

void inorder( AVL *root )
{
	if(root!=NULL)
	{	
		inorder( root->left );
		visit(root);
		inorder( root->right );
	}
}

void print_record( AVL *root )
{
	printf("\nNAME OF STUDENT : %s",root->name);
	printf("\nSUBJECT CODE    : %s",root->sc);
	printf("\nDEPARTMENT      : %s",root->dp);
	printf("\nROLL NO         : %d",root->roll);
	printf("\nSEMESTER        : %d",root->sem);
	printf("\nMARKS           : %d\n\n",root->marks);
}

AVL* create_node()
{
	AVL *temp;
	temp=(AVL*)malloc(sizeof(AVL));
	printf("\n ENTER THE NAME OF STUDENT \n");
	scanf("%s",temp->name);
	printf("\n ENTER THE SUBJECT CODE \n");
	scanf("%s",temp->sc);
	printf("\n ENTER THE DEPARTMENT \n");
	scanf("%s",temp->dp);
	printf("\n ENTER THE ROLL NO \n");
	scanf("%d",&temp->roll);
	printf("\n ENTER THE SEMESTER \n");
	scanf("%d",&temp->sem);
	printf("\n ENTER THE MARKS \n");
	scanf("%d",&temp->marks);
	temp->left=NULL;
	temp->right=NULL;
	temp->ht=-1;
	return(temp);
}
