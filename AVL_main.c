#include<stdio.h> 
#include<stdlib.h>
#include<string.h>
#include "AVL.h"

// KEY IS SUBJECT CODE AS WELL AS ROLL NO
//PRIOROTY IS GIVEN TO SUBJECT CODE THEN THE ROLL NO

int main()
{
	AVL *head,*temp,*pass;
	int a,exit=1,z,y,r1,r2;
	head=NULL;
	printf("                                                     -----  BEGIN  -----               \n");
	while(exit)
	{
		printf("\n                                                -----  ENTER YOUR CHOICE  -----\n");
		printf("\n 1.INSERTION                                        2.PRINT\n 3.SEARCH                                           4.HEIGHT\n 5.NUM OF NODES                                     6.RANGE SEARCH\n 7.GET MAX                                          8.FAILURE\n 9.KTH HIGHEST                                      10.TOPPER\n 11.DELETION                                        12.EXIT\n");
		scanf("%d",&a);
		switch(a)
		{
			case(1):
				temp=create_node();
			//	visit(temp);
				head=insertion(head,temp);
				break;
			case(2):
				if(head!=NULL)
				{
					preorder( head );
				}
				else
				{
					printf("                                                  -----   DATABASE EMPTY  ------	\n");
				}
				
				break;
			case(3):
				printf("\n ENTER THE SUBJECT CODE \n");
				scanf("%s",pass->sc);
				printf("\n ENTER THE ROLL NO \n");
				scanf("%d",&pass->roll);
				z=search(head,pass);
				if(z==1)
				{
					printf("\nSUCCESS");
				}
				else 
				{
					printf("\nFAILURE");
				}
				break;
			case(4):
				z=height(head);
				printf("                                                     HEIGHT IS : %d ",z);
				break;
			case(5):
				y=num_nodes(head);
				printf("NO OF NODES ARE : %d ",y);
				break;
			case(6):
				printf("\n ENTER THE ROLL NO (LOWER LIMIT) \n");
				scanf("%d",&r1);
				printf("\n ENTER THE ROLL NO (UPPER LIMIT) \n");
				scanf("%d",&r2);
				range_search(head,r1,r2);
				break;
			case(7):
				printf("\n ENTER THE SUBJECT CODE \n");
				scanf("%s",pass->sc);
				pass->marks=0;
				temp=get_max(head,pass);
				if(temp->marks==0)
				{
					printf("\n THE DATABASE DOES NOT HAVE %s SUBJECT\n",temp->sc);
				}
				else
				{
					print_record(temp);
				}
				break;
			case(8):
				printf("\n ENTER THE SUBJECT CODE \n");
				scanf("%s",pass->sc);
				printf("\n ENTER THE PASSING MARKS FOR THE ENTERED SUBJECT\n");
				scanf("%d",&pass->marks);
				failure(head,pass);
				break;
			case(9):
				printf("\n ENTER THE VALUE OF K \n");
				scanf("%d",&z);
				temp=kth_Highest(head,z);
				if(temp==NULL)
				{
					printf("\n %d th HIGHEST DOES NOT EXIST \n",z);
				}
				else
				{
					printf("\n %d th HIGHEST IS: \n",z);
					print_record(temp);
				}
				break;
			case(10):
				temp=topper();
				if(temp==NULL)
				{
					printf("\n TREE IS EMPTY \n");
				}
				else
				{
					printf("\nTHE TOPPER IS : \n",temp->sc);	
					print_record(temp);
				}
				break;
			case(11):
				printf("\n ENTER THE SUBJECT CODE \n");
				scanf("%s",pass->sc);
				printf("\n ENTER THE ROLL NO TO BE DELETED\n");
				scanf("%d",&pass->roll);
				head=deletion(head,pass);
			//	printf("fhhsjfg\n");
				//head=balancing(head);
				break;
			case(12):
				exit=0;
				break;
			default:
				printf("                                                  -----   WRONG INPUT  ------	\n");
				break;		
		}
	}
	printf("                                                     -----   END   -----               \n");
	return(0);				
}
