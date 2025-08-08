#include "LinkedQueue.h"

void LQ_CreateQueue(LinkedQueue** Queue)
{
	(*Queue) = (LinkedQueue*)malloc(sizeof(LinkedQueue));

	(*Queue)->Front = NULL;
	(*Queue)->Rear = NULL;
	(*Queue)->size = 0;
}

void LQ_DestroyQueue(LinkedQueue* Queue)
{
	while (!LQ_IsEmpty(Queue))
	{
		Node* Popped = LQ_Dequeue(Queue);
		LQ_DestroyNode(Popped);
	}

	free(Queue);
}

Node* LQ_CreateNode(char* Data)
{
	Node* NewNode = (Node*)malloc(sizeof(Node));

	NewNode->Data = (char*)malloc(strlen(Data) + 1);
	strcpy(NewNode->Data, Data);
	NewNode->NextNode = NULL;

	return NewNode;
}

void LQ_DestroyNode(Node* _Node)
{
	free(_Node->Data);  // 문자열 데이터도 해제
	free(_Node);
}

void LQ_Enqueue(LinkedQueue* Queue, Node* NewNode)
{
	if (Queue->Front == NULL) // 빈 큐이면
	{
		Queue->Front = NewNode;
		Queue->Rear = NewNode;
	}
	else // 노드 존재하면
	{
		Queue->Rear->NextNode = NewNode;
		Queue->Rear = NewNode; // 후단 갱신
	}
	Queue->size++;
}

Node* LQ_Dequeue(LinkedQueue* Queue)
{
	Node* Popped = Queue->Front; // 전단 미리 저장
	
	if (Queue->size == 0) // 빈 큐면
	{
		printf("! Queue is empty !\n");
		return NULL;  // 명시적으로 NULL 반환
	}
	else if (Queue->size == 1) // 단일 노드면
	{
		Queue->Front = NULL;
		Queue->Rear = NULL;
		Queue->size--;
	}
	else // 여러 노드 존재
	{
		Queue->Front = Queue->Front->NextNode; // 전단 갱신
		Queue->size--;
	}

	return Popped;
}

int LQ_IsEmpty(LinkedQueue* Queue)
{
	return (Queue->Front == NULL);
}