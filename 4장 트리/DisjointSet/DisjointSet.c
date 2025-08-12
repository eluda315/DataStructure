#include "DisjointSet.h"

void DS_UnionSet(DisjointSet* Set1, DisjointSet* Set2)
{
	Set2 = DS_FindSet(Set2);

	Set2->Parent = DS_FindSet(Set1);
}

DisjointSet* DS_FindSet(DisjointSet* Set)
{
	while (Set->Parent != NULL)
	{
		Set = Set->Parent;
	}

	return Set;
}

DisjointSet* DS_MakeSet(void* NewData)
{
	DisjointSet* Set = (DisjointSet*)malloc(sizeof(DisjointSet));

	Set->Data = NewData;
	Set->Parent = NULL;

	return Set;
}

void DS_DestroySet(DisjointSet* Set)
{
	free(Set);
}