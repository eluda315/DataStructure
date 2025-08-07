#include "CircularQueue.h"

void CQ_CreateQueue(CircularQueue** Queue, int Capacity)
{
	*Queue = (CircularQueue*)malloc(sizeof(CircularQueue));

	(*Queue)->Capacity = Capacity;
	(*Queue)->Front = 0;
	(*Queue)->Rear = 0;

	(*Queue)->Nodes = (Node*)malloc(sizeof(Node) * (Capacity + 1));
}


void CQ_DestroyQueue(CircularQueue* Queue)
{
	free(Queue->Nodes);
	free(Queue);
}


void CQ_Enqueue(CircularQueue* Queue, ElementType Data)
{
	if (CQ_IsFull(Queue)) // ²Ë Ã¡À¸¸é
	{
		printf("! Queue is Full !\n");
	}
	else // °ø°£ ÀÖÀ¸¸é
	{
		Queue->Nodes[Queue->Rear].Data = Data;
		if (Queue->Rear == Queue->Capacity) Queue->Rear = 0;
		else Queue->Rear++;
	}
}


ElementType CQ_Dequeue(CircularQueue* Queue)
{
	int position = 0;

	if (CQ_IsEmpty(Queue)) printf("! Queue is empty !\n");
	else
	{
		position = Queue->Front;
		if (Queue->Front == Queue->Capacity) Queue->Front = 0;
		else Queue->Front++;
	}

	return Queue->Nodes[position].Data;
}


int CQ_GetSize(CircularQueue* Queue)
{
	int size = 0;
	if (Queue->Front <= Queue->Rear) size = Queue->Rear - Queue->Front;
	else size = Queue->Capacity + Queue->Rear - Queue->Front + 1;

	return size;
}


int CQ_IsEmpty(CircularQueue* Queue)
{
	return (Queue->Front == Queue->Rear);
}


int CQ_IsFull(CircularQueue* Queue)
{
	if (Queue->Front < Queue->Rear) return (Queue->Rear - Queue->Front) == Queue->Capacity;
	else return (Queue->Front == (Queue->Rear + 1));
}