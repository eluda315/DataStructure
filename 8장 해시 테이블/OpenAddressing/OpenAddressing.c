#include "OpenAddressing.h"

HashTable* OAHT_CreateHashTable(int TableSize)
{
	HashTable* HT = (HashTable*)malloc(sizeof(HashTable));

	HT->OccupiedCount = 0;
	HT->TableSize = TableSize;
	HT->Table = (ElementType*)malloc(sizeof(ElementType) * TableSize);
	memset(HT->Table, 0, sizeof(ElementType) * TableSize);

	return HT;
}

void OAHT_DestroyHashTable(HashTable* HT)
{
	for (int i = 0; i < HT->TableSize; i++)
	{
		OAHT_ClearElement(&(HT->Table[i]));
	}
	free(HT->Table);
	free(HT);
}

void OAHT_ClearElement(ElementType* Element)
{
	free(Element->Key);
	free(Element->Value);
	free(Element);
}

// 내 답안
//void OAHT_Set(HashTable** HT, KeyType Key, ValueType Value)
//{
//	// 용량 50% 넘으면 재해싱
//	double Usage = (double)(*HT)->OccupiedCount / (*HT)->TableSize;
//	if (Usage > 0.5) OAHT_Rehash(HT);
//	
//	int addr1 = OAHT_Hash(Key, strlen(Key), (*HT)->TableSize);
//	int addr2 = OAHT_Hash2(Key, strlen(Key), (*HT)->TableSize);
//	int addr = addr1;
//
//	/*해시 테이블의 Set 함수는 새로운 키를 삽입하는 기능뿐만 아니라, 
//	이미 존재하는 키의 값을 새로운 값으로 갱신하는 기능도 수행해야 합니다.
//	기존 데이터와의 값 비교도 필요하다는 말.*/
//	if ((*HT)->Table[addr1].Status == EMPTY)
//	{
//		// 아무것도 안 해도 됨.
//	}
//	else
//	{
//		while (1)
//		{
//			/*이 코드는 addr + addr2가 TableSize의 2배 이상 커지는 경우 배열의 범위를 벗어나는 버그를 일으킬 수 있습니다
//			가장 안전하고 표준적인 방법은 **나머지 연산자(%)**를 사용하는 것입니다.*/
//			addr += addr2;
//			if (addr2 >= (*HT)->TableSize) addr -= (*HT)->TableSize;
//			if ((*HT)->Table[addr].Status == EMPTY) break;
//		}
//	}
//
//	printf("Collision occured! : Key(%s), Address(%d), StepSize(%d)\n", Key, addr, addr2);
//
//	(*HT)->Table[addr].Key = (char*)malloc(strlen(Key) + 1);
//	(*HT)->Table[addr].Value = (char*)malloc(strlen(Value) + 1);
//	strcpy((*HT)->Table[addr].Key, Key);
//	strcpy((*HT)->Table[addr].Value, Value);
//	(*HT)->Table[addr].Status = OCCUPIED;
//
//	(*HT)->OccupiedCount++;
//
//	printf("Key(%s) entered at address(%d)\n", Key, addr);
//}

// 모범답안
void OAHT_Set(HashTable** HT, KeyType Key, ValueType Value)
{
	int    KeyLen, Address, StepSize;
	double Usage;

	Usage = (double)(*HT)->OccupiedCount / (*HT)->TableSize;

	if (Usage > 0.5)
	{
		OAHT_Rehash(HT);
	}

	KeyLen = strlen(Key);
	Address = OAHT_Hash(Key, KeyLen, (*HT)->TableSize);
	StepSize = OAHT_Hash2(Key, KeyLen, (*HT)->TableSize);

	while ((*HT)->Table[Address].Status != EMPTY &&
		strcmp((*HT)->Table[Address].Key, Key) != 0)
	{
		printf("Collision occured! : Key(%s), Address(%d), StepSize(%d)\n",
			Key, Address, StepSize);

		Address = (Address + StepSize) % (*HT)->TableSize;
	}

	(*HT)->Table[Address].Key = (char*)malloc(sizeof(char) * (KeyLen + 1));
	strcpy((*HT)->Table[Address].Key, Key);

	(*HT)->Table[Address].Value = (char*)malloc(sizeof(char) * (strlen(Value) + 1));
	strcpy((*HT)->Table[Address].Value, Value);

	(*HT)->Table[Address].Status = OCCUPIED;

	(*HT)->OccupiedCount++;

	printf("Key(%s) entered at address(%d)\n", Key, Address);
}


ValueType OAHT_Get(HashTable* HT, KeyType Key)
{
	int addr = OAHT_Hash(Key, strlen(Key), HT->TableSize);
	int StepSize = OAHT_Hash2(Key, strlen(Key), HT->TableSize);

	while (HT->Table[addr].Status != EMPTY && strcmp(HT->Table[addr].Key, Key) != 0)
	{
		addr = (addr + StepSize) % HT->TableSize;
	}

	return HT->Table[addr].Value;
}

int OAHT_Hash(KeyType Key, int KeyLength, int TableSize)
{
	int i = 0;
	int HashValue = 0;

	for (i = 0; i < KeyLength; i++)
	{
		HashValue = (HashValue << 3) + Key[i];
	}

	HashValue = HashValue % TableSize;

	return HashValue;
}

int OAHT_Hash2(KeyType Key, int KeyLength, int TableSize)
{
	int i = 0;
	int HashValue = 0;

	for (i = 0; i < KeyLength; i++)
	{
		HashValue = (HashValue << 2) + Key[i];
	}

	HashValue = HashValue % (TableSize - 3);

	return HashValue + 1;
}

void OAHT_Rehash(HashTable** HT)
{
	ElementType* OldTable = (*HT)->Table;

	// 새 해시 테이블을 만들고
	HashTable* NewHT = OAHT_CreateHashTable((*HT)->TableSize * 2);

	printf("\nRehashed. New table size is : %d\n\n", NewHT->TableSize);

	// 이전의 해시 테이블에 있던 데이터를 새 해시 테이블로 옮긴다
	for (int i = 0; i < (*HT)->TableSize; i++)
	{
		if (OldTable[i].Status == OCCUPIED)
		{
			OAHT_Set(&NewHT, OldTable[i].Key, OldTable[i].Value);
		}
	}

	// 이전 해시 테이블 소멸
	OAHT_DestroyHashTable((*HT));

	// HT 포인터에는 새로 해시 테이블의 주소를 대입
	(*HT) = NewHT;
}