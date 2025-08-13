#include "LinkedList.h"

Node* SLL_SequentialSeach(Node* Head, int Target)
{
	Node* Current = Head;
	Node* Match = NULL;

	while (Current != NULL)
	{
		if (Current->Data == Target)
		{
			Match = Current;
			break;
		}
		else Current = Current->NextNode;
	}

	return Match;
}

int main(void)
{

}