#include "SimpleHashTable.h"

HashTable* SHT_CreateHashTable(int TableSize)
{
	HashTable* NewHT = (HashTable*)malloc(sizeof(HashTable));

	NewHT->TableSize = TableSize;
	NewHT->Table = (Node*)malloc(sizeof(Node) * TableSize);

	return NewHT;
}

void SHT_Set(HashTable* HT, KeyType Key, ValueType Value)
{
	int addr = SHT_Hash(Key, HT->TableSize);

	HT->Table[addr].Key = Key;
	HT->Table[addr].Value = Value;
}

ValueType SHT_Get(HashTable* HT, KeyType Key)
{
	return HT->Table[SHT_Hash(Key, HT->TableSize)].Value;
}

void SHT_DestroyHashTable(HashTable* HT)
{
	free(HT->Table);
	free(HT);
}

int SHT_Hash(KeyType Key, int TableSize)
{
	return Key % TableSize;
}