#include "LinkedListStack.h"

void  LLS_CreateStack(LinkedListStack** Stack)
{
	*Stack = (LinkedListStack*)malloc(sizeof(LinkedListStack));

	(*Stack)->List = NULL;
	(*Stack)->Top = NULL;
}

// 따로 노드를 일일이 삭제하지 않음
void  LLS_DestroyStack(LinkedListStack* Stack)
{
	while (!LLS_IsEmpty(Stack))
	{
		Node* Popped = LLS_Pop(Stack);
		LLS_DestroyNode(Popped);
	}
	
	free(Stack);
}

Node* LLS_CreateNode(char* NewData)
{
	// 노드 공간 할당
	Node* NewNode = (Node*)malloc(sizeof(Node));
	// 노드의 데이터 공간 할당
	NewNode->Data = (char*)malloc(strlen(NewData) + 1);
	// 데이터 저장
	strcpy(NewNode->Data, NewData);

	NewNode->NextNode = NULL;

	return NewNode;
}

void  LLS_DestroyNode(Node* _Node)
{
	free(_Node->Data);
	free(_Node);
}

void  LLS_Push(LinkedListStack* Stack, Node* NewNode)
{
	// 빈 리스트라면
	if (Stack->List == NULL)
	{
		Stack->List = NewNode;
	}
	else // 아니면
	{
		Stack->Top->NextNode = NewNode;
	}
	Stack->Top = NewNode; // Top 갱신
}

Node* LLS_Pop(LinkedListStack* Stack)
{
	Node* Popped = Stack->Top;
	if (Popped == NULL)
		return NULL;

	if (Stack->List == Stack->Top)
	{
		Stack->List = NULL;
		Stack->Top = NULL;
	}
	else
	{
		Node* Current = Stack->List;
		while (Current->NextNode != Stack->Top)
		{
			Current = Current->NextNode;
		}

		Stack->Top = Current;
		Stack->Top->NextNode = NULL;
	}

	return Popped;
}

Node* LLS_Top(LinkedListStack* Stack)
{
	return Stack->Top;
}

int LLS_GetSize(LinkedListStack* Stack)
{
	int count = 0;
	Node* current = Stack->List;

	while (current != NULL)
	{
		count++;
		current = current->NextNode;
	}

	return count;
}

int LLS_IsEmpty(LinkedListStack* Stack)
{
	return (Stack->List == NULL);
}