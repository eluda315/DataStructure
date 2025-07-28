#include "ArrayStack.h"

// 스택 생성
void AS_CreateStack(ArrayStack** Stack, int Capacity)
{
	*Stack = (ArrayStack*)malloc(sizeof(ArrayStack));

	(*Stack)->Nodes = (Node*)malloc(sizeof(Node) * Capacity);

	(*Stack)->Capacity = Capacity;
	(*Stack)->Top = -1;
}


// 스택 소멸
void AS_DestroyStack(ArrayStack* Stack)
{
	free(Stack->Nodes);
	free(Stack);
}

// 노드 삽입 연산
void AS_Push(ArrayStack* Stack, ElementType Data)
{
	Stack->Top++;
	Stack->Nodes[Stack->Top].Data = Data;
}

// 노드 제거 연산
ElementType AS_Pop(ArrayStack* Stack)
{
	ElementType popped = Stack->Nodes[Stack->Top].Data;
	Stack->Top--;  // 최상위 노드 위치 조정
	return popped;
}

// 최상위 노드 반환
ElementType AS_Top(ArrayStack* Stack)
{
	return Stack->Nodes[Stack->Top].Data;
}

// 데이터가 들어있는 노드 개수 반환
int AS_GetSize(ArrayStack* Stack)
{
	return Stack->Top + 1;
}

// 빈 스택인지 검사
int AS_IsEmpty(ArrayStack* Stack)
{
	return (Stack->Top < 0);
}