/* 
   Sarthak Kukreja.
   Sort a List of 0s , 1s and 2s.
   3 different Implementations - Sort1 , Sort2 and Sort3.
   Sort1 - Retains order of Nodes and does not rewrite Node Values.
   Sort2 - Rewrites Node values.
   Sort3 - Dutch National flag Algorithm.
*/

#include "myLL.h"
using namespace std;

Node *non_empty( Node *head1 , Node *head2 , Node *head3 )
{
	if(head1) return head1;

	if(head2) return head2;

	if(head3) return head3;
}

Node *merge(Node *head1 , Node *head2 , Node *head3 , Node *tail1 , Node *tail2 , Node *tail3)
{
	if( head1 == NULL && head2 == NULL && head3 == NULL) // No 0s,1s and 2s in list.
	{
		return NULL;
	}

	if( head1 == NULL && head2 != NULL && head3 != NULL) // No 0s in list.
	{
		tail2 -> next = head3;
		return head2;
	}

	if( head1 != NULL && head2 == NULL && head3 != NULL) // No 1s in the list.
	{
		tail1 -> next = head3;
		return head1;
	}

	if( head1 != NULL && head2 != NULL && head3 == NULL) // No 2s in the list.
	{
		tail1 -> next = head2;
		return head1;
	}

	if( !head1 || !head2 || !head3 ) return non_empty(head1 , head2 , head3); // Checks if lists contains only zeroes,ones or twos.

	// If execution has reached this point,neither of the zeroes,ones or twos list is empty.

	tail1 -> next = head2;
	tail2 -> next = head3;

	return head1; 
}

void sort1( Node * &head )
{
	Node *zeroes,*ones,*twos;

	zeroes = new Node(-1); // Header Nodes to generalise while loop.
	ones = new Node(-1); 
	twos = new Node(-1);

	Node *zeroesHead = zeroes;
	Node *onesHead = ones;
	Node *twosHead = twos;

	while( head != NULL )
	{
		switch( head -> data)
		{
			case 0 : zeroes -> next = head;
			     	 zeroes = zeroes -> next;
			     	 break;

	     	case 1 : ones -> next = head;
			     	 ones = ones -> next;
			     	 break;

	     	case 2 : twos -> next = head;
			     	 twos = twos -> next;
			     	 break;

		}

		head = head -> next;
	}

	zeroes -> next = NULL; // Ending the Lists.
	ones -> next = NULL;
	twos -> next = NULL;

	head = merge( zeroesHead -> next , onesHead -> next , twosHead -> next , zeroes , ones , twos );

	delete zeroesHead; // Deleting previously assigned header Nodes. 
	delete onesHead;
	delete twosHead;
}

Node *sort2( Node *head )
{
	int size[3] = {}; // Initializes Array to Zero.

	Node *knight = head; // Variable to Parse List.

	while( knight != NULL )
	{
		size[ knight -> data ]++;
		knight = knight -> next;
	}

	Node *bishop = head; // Variable to Parse List.

	for( int i = 0 ; i < 3 ; i++ )
	{
		for( int j = 0 ; j < size[i] ; j++ )
		{
			bishop -> data = i;
			bishop = bishop -> next;
		}
	}

	return head;
}

Node *moveBeg( Node *king , Node *pawn ) // Reminder : Optimize code by already passing the prev element.
{
	if( king == pawn ) return king;

	Node *knight = king;

	while( knight -> next != pawn )
	{
		knight = knight -> next;
	}

	knight -> next = pawn -> next;
	pawn -> next = king;

	king = pawn; // Deep.

	return king;
}

Node *moveEnd( Node *king , Node *pawn )
{
	//if( pawn -> next == NULL || pawn -> next -> next == NULL ) return king;

	Node *knight = king;
	Node *bishop = pawn;

	while( knight -> next != pawn )
	{
		knight = knight -> next;
	}

	while( bishop -> next != NULL )
	{
		bishop = bishop -> next;
	}

	knight -> next = pawn -> next;

	bishop -> next = pawn;

	pawn -> next = NULL;

	return king;
}

Node *sort3( Node *head )
{
	Node *knight = head;
	Node *end = head;

	while(end -> next != NULL)
	{
		end = end -> next;
	}

	while( knight != NULL )
	{
		if( knight -> data == 0) // Shift any zero encountered to front of the list.
		{
			Node *pawn = knight;
			knight = knight -> next;
			head = moveBeg( head , pawn);
		}
		else if( knight -> data == 1) // Do nothing to ones.
		{
			knight = knight -> next;
		}
		else // Shift any two encountered to end of the list.
		{
			if( knight == end ) // To prevent infinte loop caused by checking of previously sorted 'twos' nodes.
			{
				return head;
			}

			Node *pawn = knight;
			knight = knight -> next;
			head = moveEnd(head , pawn);
		}
	}

	return head;
}

int main()
{
	Node *main = takeInput();

	Node *head1 = copyList(main);
	Node *head2 = copyList(main);
	Node *head3 = copyList(main);

	cout << "\n";

	sort1(head1); // Head of Linked List passed by reference. 
	cout << "Implementation 1 : ";
	print(head1);

	head2 = sort2(head2);
	cout << "\nImplementation 2 : ";
	print(head2);

	head3 = sort3(head3);
	cout << "\nImplementation 3 : ";
	print(head3);

	return 0;
}
