#include "LinkedList.h"

/* ��� ���� */
Node* SLL_CreateNode(ElementType NewData)
{
	Node* NewNode = (Node*)malloc(sizeof(Node));

	NewNode->Data = NewData;
	NewNode->NextNode = NULL;

	return NewNode;
}


/* ��� �Ҹ� */
void SLL_DestroyNode(Node* Node)
{
	free(Node);
}


/* ��� �߰� */
void SLL_AppendNode(Node** Head, Node* NewNode)
{
	if ((*Head) == NULL) // �� ����Ʈ���
	{
		(*Head) = NewNode;
	}
	else
	{
		Node* Tail = *Head;  // Tail�� ã�� ���� ����: �ϴ� Head���� ����
		while (Tail->NextNode != NULL)
		{
			Tail = Tail->NextNode;
		}
		// Tail�� ã������
		Tail->NextNode = NewNode;
	}
}


/* ��忡 ��� �߰� */
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


/* ��� Ž�� */
Node* SLL_GetNodeAt(Node* List, int index)
{
	Node* Node = List;
	while (Node != NULL && (--index) >= 0)
	{
		Node = Node->NextNode;
	}

	return Node;
}


/* ��� ���� */
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


/* ��� ���� */
void SLL_InsertAfter(Node* Current, Node* NewNode)
{
	// �̸� ������ ��ġ �ٷ� �� ��带 Ž�� ������ ���� ���ؼ� ���ڷ� ����
	NewNode->NextNode = Current->NextNode;
	Current->NextNode = NewNode;
}

void SLL_InsertBefore(Node** Head, Node* TargetNode, Node* NewNode)
{
	// Case 1: TargetNode�� Head�� ���
	if (*Head == TargetNode)
	{
		NewNode->NextNode = *Head;
		*Head = NewNode;
		return;
	}

	// Case 2: TargetNode �� ��� Ž��
	Node* Current = *Head;
	while (Current != NULL && Current->NextNode != TargetNode)
	{
		Current = Current->NextNode;
	}

	// TargetNode ���� ã������ ����
	if (Current != NULL)
	{
		NewNode->NextNode = TargetNode;
		Current->NextNode = NewNode;
	}
}



/* ��� ���� ���� */
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