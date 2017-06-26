// Sarthak Kukreja.
// Delete Alternate Nodes in a list.

#include "myLL.h"
using namespace std;

Node *recAltDelOdd( Node *king) // Recursively deletes Odd Nodes;
{
	if( king == NULL ) return NULL;

	Node *pawn = king;
	king = king -> next;
	delete pawn;
	if ( king != NULL ) king -> next = recAltDelOdd( king -> next );
	return king;
}

Node *recAltDelEven( Node *king) // Recursively deletes Even Nodes;
{
	if( king == NULL || king -> next == NULL)
	{
		return king;
	}

	Node *pawn = king -> next;
	king -> next = recAltDelEven( pawn -> next );
	delete pawn;

	return king;
}

Node *altDelEven( Node *king ) // Iteratively Deletes alternate Even nodes.
{
	Node *knight = king; 

	while( knight != NULL && knight -> next != NULL )
	{	
		Node *pawn = knight -> next;
		knight -> next = pawn -> next;
		knight = knight -> next;
		delete pawn;
	}

	return king;
}

Node *altDelOdd( Node *king ) // Iteratively Deletes alternate Odd nodes.
{
	Node *knight = king; // 'Current' Pointer to parse list.
	Node *bishop = NULL; // 'Prev' Pointer to parse list.

	while( knight != NULL )
	{
		if( knight == king )
		{
			king = knight -> next;
			bishop = king;
		}
		else
		{
			bishop -> next = knight -> next;
			bishop = bishop -> next;
		}

		Node *pawn = knight;
		knight = ( knight -> next ) ? knight -> next -> next : NULL;
		delete pawn;
	}

	return king;
}

int main()
{
	Node *oddHeadI,*oddHeadR,*evenHeadI,*evenHeadR;

	Node *main = takeInput();

	oddHeadI = altDelEven(copyList(main));
	evenHeadI = altDelOdd(copyList(main));
	oddHeadR = recAltDelEven(copyList(main));
	evenHeadR = recAltDelOdd(copyList(main));

	cout << "\n";

	cout << "Iterative Methods\n";

	cout << "Odd : ";
	 print(oddHeadI);
	cout << "Even : ";
	 print(evenHeadI);

	cout << "\nRecursive Methods\n";

	cout << "Odd : ";
	 print(oddHeadR);
	cout << "Even : ";
	 print(evenHeadR);

	return 0;
}
