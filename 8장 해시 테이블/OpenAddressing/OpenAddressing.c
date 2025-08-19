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

// �� ���
//void OAHT_Set(HashTable** HT, KeyType Key, ValueType Value)
//{
//	// �뷮 50% ������ ���ؽ�
//	double Usage = (double)(*HT)->OccupiedCount / (*HT)->TableSize;
//	if (Usage > 0.5) OAHT_Rehash(HT);
//	
//	int addr1 = OAHT_Hash(Key, strlen(Key), (*HT)->TableSize);
//	int addr2 = OAHT_Hash2(Key, strlen(Key), (*HT)->TableSize);
//	int addr = addr1;
//
//	/*�ؽ� ���̺��� Set �Լ��� ���ο� Ű�� �����ϴ� ��ɻӸ� �ƴ϶�, 
//	�̹� �����ϴ� Ű�� ���� ���ο� ������ �����ϴ� ��ɵ� �����ؾ� �մϴ�.
//	���� �����Ϳ��� �� �񱳵� �ʿ��ϴٴ� ��.*/
//	if ((*HT)->Table[addr1].Status == EMPTY)
//	{
//		// �ƹ��͵� �� �ص� ��.
//	}
//	else
//	{
//		while (1)
//		{
//			/*�� �ڵ�� addr + addr2�� TableSize�� 2�� �̻� Ŀ���� ��� �迭�� ������ ����� ���׸� ����ų �� �ֽ��ϴ�
//			���� �����ϰ� ǥ������ ����� **������ ������(%)**�� ����ϴ� ���Դϴ�.*/
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

// ������
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

	// �� �ؽ� ���̺��� �����
	HashTable* NewHT = OAHT_CreateHashTable((*HT)->TableSize * 2);

	printf("\nRehashed. New table size is : %d\n\n", NewHT->TableSize);

	// ������ �ؽ� ���̺� �ִ� �����͸� �� �ؽ� ���̺�� �ű��
	for (int i = 0; i < (*HT)->TableSize; i++)
	{
		if (OldTable[i].Status == OCCUPIED)
		{
			OAHT_Set(&NewHT, OldTable[i].Key, OldTable[i].Value);
		}
	}

	// ���� �ؽ� ���̺� �Ҹ�
	OAHT_DestroyHashTable((*HT));

	// HT �����Ϳ��� ���� �ؽ� ���̺��� �ּҸ� ����
	(*HT) = NewHT;
}