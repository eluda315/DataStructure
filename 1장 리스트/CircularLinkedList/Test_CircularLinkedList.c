#include "CircularLinkedList.h"

int main(void)
{
    int Count;
    Node* List = NULL;
	Node* NewNode = NULL;
	Node* Current = NULL;

	for (int i = 111; i < 116; i++)
	{
		NewNode = CDLL_CreateNode(i);
		CDLL_AppendNode(&List, NewNode);
	}

	// 리스트 출력
	CDLL_PrintNode(List);

    //  모든 노드를 메모리에서 제거     
    printf("\nDestroying List...\n");

    Count = CDLL_GetNodeCount(List);

    for (int i = 0; i < Count; i++)
    {
        Current = CDLL_GetNodeAt(List, 0);

        if (Current != NULL)
        {
            CDLL_RemoveNode(&List, Current);
            CDLL_DestroyNode(Current);
        }
    }

    return 0;

}