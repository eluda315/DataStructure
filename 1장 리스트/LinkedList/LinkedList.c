#include "LinkedList.h"

/* 노드 생성 */
Node* SLL_CreateNode(ElementType NewData)
{
	Node* NewNode = (Node*)malloc(sizeof(Node));

	NewNode->Data = NewData;
	NewNode->NextNode = NULL;

	return NewNode;
}


/* 노드 소멸 */
void SLL_DestroyNode(Node* Node)
{
	free(Node);
}


/* 노드 추가 */
void SLL_AppendNode(Node** Head, Node* NewNode)
{
	if ((*Head) == NULL) // 빈 리스트라면
	{
		(*Head) = NewNode;
	}
	else
	{
		Node* Tail = *Head;  // Tail을 찾기 위한 과정: 일단 Head부터 시작
		while (Tail->NextNode != NULL)
		{
			Tail = Tail->NextNode;
		}
		// Tail을 찾았으면
		Tail->NextNode = NewNode;
	}
}


/* 헤드에 노드 추가 */
void SLL_InsertNewHead(Node** Head, Node* NewNode)
{
	if ((*Head) == NULL)
	{
		*Head = NewNode;
	}
	else
	{
		NewNode->NextNode = *Head;
		*Head = NewNode;
	}
}


/* 노드 탐색 */
Node* SLL_GetNodeAt(Node* List, int index)
{
	Node* Node = List;
	while (Node != NULL && (--index) >= 0)
	{
		Node = Node->NextNode;
	}

	return Node;
}


/* 노드 삭제 */
void SLL_RemoveNode(Node** List, Node* Remove)
{
	if (Remove == (*List))
	{
		*List = Remove->NextNode;
	}
	else
	{
		Node* Prev = *List;
		while (Prev != NULL && Prev->NextNode != Remove)
		{
			Prev = Prev->NextNode;
		}
		if (Prev!=NULL)
		{
			Prev->NextNode = Remove->NextNode;
		}
	}
}


/* 노드 삽입 */
void SLL_InsertAfter(Node* Current, Node* NewNode)
{
	// 미리 삽입할 위치 바로 전 노드를 탐색 연산을 통해 구해서 인자로 전달
	NewNode->NextNode = Current->NextNode;
	Current->NextNode = NewNode;
}

void SLL_InsertBefore(Node** Head, Node* TargetNode, Node* NewNode)
{
	// Case 1: TargetNode가 Head인 경우
	if (*Head == TargetNode)
	{
		NewNode->NextNode = *Head;
		*Head = NewNode;
		return;
	}

	// Case 2: TargetNode 앞 노드 탐색
	Node* Current = *Head;
	while (Current != NULL && Current->NextNode != TargetNode)
	{
		Current = Current->NextNode;
	}

	// TargetNode 앞을 찾았으면 삽입
	if (Current != NULL)
	{
		NewNode->NextNode = TargetNode;
		Current->NextNode = NewNode;
	}
}



/* 노드 개수 세기 */
int SLL_GetNodeCount(Node* List)
{
	int cnt = 0;
	Node* Current = List;

	while (Current != NULL)
	{
		Current = Current->NextNode;
		cnt++;
	}

	return cnt;
}