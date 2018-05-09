#ifndef AVL_H
#define AVL_H
#define SIZE 20

// KEY IS SUBJECT CODE AS WELL AS ROLL NO
//PRIOROTY IS GIVEN TO SUBJECT CODE THEN THE ROLL NO

typedef struct AVL_tag
{
	char name[SIZE];
	char sc[SIZE];
	char dp[SIZE];
	int roll;
	int sem;
	int marks;
	int ht;
	struct AVL_tag *left;
	struct AVL_tag *right;
}AVL;

void visit( AVL *root );
void preorder( AVL *root );
void inorder( AVL *root );
void print_record( AVL *root );
AVL* insertion( AVL *root,AVL *node );
AVL* create_node();
AVL* RR( AVL *root );
AVL* RL( AVL *root );
AVL* balance( AVL *root );
AVL* deletion( AVL *root, AVL *del );
AVL* min( AVL *root);
//AVL* balancing( AVL *root );
int height ( AVL *root);
int search( AVL *root, AVL *search );
int num_nodes( AVL *root );
void range_search( AVL *root ,int key1,int key2);
AVL* get_max( AVL *root, AVL *sub_code);
void failure ( AVL *root,AVL *key);
AVL* kth_Highest( AVL *root, int k );
AVL* get_Highest( AVL *root, AVL *lo, AVL *high);
AVL* topInsert( AVL *root, AVL *node );
AVL* newtree( AVL *root );
AVL* topper( );

#endif
