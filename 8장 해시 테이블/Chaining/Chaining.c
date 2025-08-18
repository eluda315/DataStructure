#include "Chaining.h"

HashTable* CHT_CreateHashTable(int TableSize)
{
	HashTable* HT = (HashTable*)malloc(sizeof(HashTable));

	HT->TableSize = TableSize;
	HT->Table = (Node*)malloc(sizeof(Node) * TableSize);
	memset(HT->Table, 0, sizeof(List) * TableSize);

	return HT;
}

void CHT_DestroyHashTable(HashTable* HT)
{
	// 1. 각 링크드 리스트를 자유 저장소에서 제거하기
	for (int i = 0; i < HT->TableSize; i++)
	{
		CHT_DestroyList(HT->Table[i]);
	}

	// 2. 해시 테이블을 자유 저장소에서 제거하기
	free(HT->Table);
	free(HT);
}

Node* CHT_CreateNode(KeyType Key, ValueType Value)
{
	Node* NewNode = (Node*)malloc(sizeof(Node));

	NewNode->Key = (char*)malloc(sizeof(char) * (strlen(Key) + 1));
	strcpy(NewNode->Key, Key);

	NewNode->Value = (char*)malloc(sizeof(char) * (strlen(Value) + 1));
	strcpy(NewNode->Value, Value);

	NewNode->Next = NULL;

	return NewNode;
}

void CHT_DestroyNode(Node* TheNode)
{
	free(TheNode->Key);
	free(TheNode->Value);
	free(TheNode);
}

void CHT_Set(HashTable* HT, KeyType Key, ValueType Value)
{
	int addr = CHT_Hash(Key, strlen(Key), HT->TableSize);
	Node* NewNode = CHT_CreateNode(Key, Value);

	if (HT->Table[addr] == NULL) // 해당 주소가 비어 있는 경우
	{
		HT->Table[addr] = NewNode;
	}
	else  // 다른 노드가 존재하는 경우: 맨 앞에 삽입
	{
		List L = HT->Table[addr];
		NewNode->Next = L;
		HT->Table[addr] = NewNode;

		printf("Collision occured : Key(%s), Address(%d)\n", Key, addr);
	}
}

ValueType CHT_Get(HashTable* HT, KeyType Key)
{
	int addr = CHT_Hash(Key, strlen(Key), HT->TableSize);
	List TheList = HT->Table[addr];
	List Target = NULL;

	if (TheList == NULL) return NULL;

	while (1)
	{
		if (strcmp(TheList->Key, Key) == 0)
		{
			Target = TheList;
			break;
		}
		if (TheList->Next == NULL) break;
		else TheList = TheList->Next;
	}

	return Target->Value;
}

int CHT_Hash(char* Key, int KeyLength, int TableSize)
{
	int i = 0;
	int HashValue = 0;
	for (i = 0; i < KeyLength; i++)
		HashValue = (HashValue << 3) + Key[i];

	return HashValue % TableSize;
}

void CHT_DestroyList(List L)
{
	if (L == NULL) return;
	if (L->Next != NULL) CHT_DestroyList(L->Next);

	CHT_DestroyNode(L);
}