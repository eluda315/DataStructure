#include "LinkedList.h"

Node* SLL_SequentialSearch(Node* Head, int Target)
{
	Node* Current = Head;
	Node* Match = NULL;

	while (Current != NULL)
	{
		if (Current->Data == Target)
		{
			Match = Current;
			break;
		}
		else Current = Current->NextNode;
	}

	return Match;
}

// ���� ������ ���� �̵���(�Լ� ȣ�� + ��Ž�� ������ �������� ������ ������, ȿ���� ������)
Node* SLL_MoveToFront(Node** Head, int Target)
{
	Node* Match = SLL_SequentialSearch((*Head), Target);
	if (Match == NULL)
	{
		return NULL;
	}
	else if (Match == (*Head))
	{
		// �̹� Ž���� �׸��� Head�̹Ƿ� ���� ����
	}
	else
	{
		// Match�� �� ��带  ã�Ƽ� ��迭
		Node* Prev = (*Head);
		while (Prev != NULL)
		{
			if (Prev->NextNode == Match)
			{
				// Match�� Head�� ����, Match�� ���� �ڸ� ����
				Prev->NextNode = Match->NextNode;
				Match->NextNode = (*Head);
				(*Head) = Match;
				break;
			}
			else
			{
				Prev = Prev->NextNode;
			}
		}
	}
	return Match;
}

// ���� �̵��� ������
//Node* SLL_MoveToFront(Node** Head, int Target)
//{
//	Node* Current = (*Head);
//	Node* Previous = NULL;
//	Node* Match = NULL;
//
//	while (Current != NULL)
//	{
//		// ó�� if���� ���� �� Current�� Head�̹Ƿ� Prev�� ����(if�� ���̿��� ��ġ ��迭�� �ʿ� ���ٴ� ��)
//		if (Current->Data == Target)
//		{
//			Match = Current;
//			if (Previous != NULL)
//			{
//				//	�ڽ��� �� ���� ���� ��带 ����
//				Previous->NextNode = Current->NextNode;
//
//				//	�ڽ��� ����Ʈ�� ���� ������ �ű��
//				Current->NextNode = (*Head);
//				(*Head) = Current;
//			}
//			break;
//		}
//		else
//		{
//			// Current�� Head�� �ƴϹǷ� else�� ���� �̶� Prev�� �ʱ�ȭ �� ������ �ϸ� �Ǵ°���! ����ī
//			Previous = Current;
//			Current = Current->NextNode;
//		}
//	}
//	return Match;
//}




/*
���� ���� ����Ʈ
�� ����� Head / 2��° ��� / ������ ��带 �� ���� ���� ������ ������ ó���ϴµ�,
�������� �ϳ��� while ���� �ȿ��� ������ �̵������� ��� ��츦 ó���߾�.

��,

�� ����: �������� ������ �ڵ尡 ���, Head ��ü ������ �ߺ��� ���ɼ� ����.

������: ������ ����������, �ʺ��ڰ� �б⿣ �򰥸� �� ����.

���� ���������� ���������� �켱�ϸ� ���� �� �ڵ尡 �� ����.
�ٸ�, ���ڵ� ���� �ּ�ȭ���� ���ϸ� ������ ��Ÿ�Ϸ� �����ϴ� �� ���� ���� �־�.
*/
Node* SLL_Transpose(Node** Head, int Target)
{
	Node* Current = *Head;
	Node* Prev = NULL;
	Node* PPrev = NULL;
	Node* Match = NULL;

	while (Current != NULL) // �������� ��Ȳ�� ó��
	{
		if (Target == (*Head)->Data) // 1. Target�� Head���ٸ�
		{
			Match = (*Head);
			break; /*ã�Ҵٸ� �ߴ����ֱ�!*/
		}
		/* ���� ����� ��� ó�����ֱ� */
		else if ((*Head)->NextNode != NULL && Target == (*Head)->NextNode->Data) // 2. Target�� 2��° ��忴�ٸ�
		{
			Match = (*Head)->NextNode; // 2��° �����ͷ� ����

			// Head�� Match�� ���� �ٲٱ�
			(*Head)->NextNode = Match->NextNode;
			Match->NextNode = (*Head);
			(*Head) = Match;

			break;
		}
		else // 3. Target�� 3��° ��� �̻��̸�(�� ��)
		{
			PPrev = (*Head);
			Prev = PPrev->NextNode;
			Current = Prev->NextNode;

			while (Current != NULL && Current->Data != Target) /*������ ������ �ٲ�*/
			{
				// Target ��� ã�� ������ �� ��� ������ ���� ���� ����
				PPrev = PPrev->NextNode;
				Prev = Prev->NextNode;
				Current = Current->NextNode;
			}

			if (Current != NULL) // Target�� �� ã�� ����Ʈ ������ ���� �ʾ�����
			{
				Match = Current; // ��ȯ�� Match ����

				// ��ġ ��迭
				Prev->NextNode = Current->NextNode;
				Current->NextNode = Prev;
				PPrev->NextNode = Current;
			}

			break;
		}
	}

	return Match;
}

// ������ ������
//Node* SLL_Transpose(Node** Head, int Target)
//{
//	Node* Current = (*Head);
//	Node* PPrevious = NULL; //	���� ����� ���� ���
//	Node* Previous = NULL; //	���� ���
//	Node* Match = NULL;
//
//	while (Current != NULL)
//	{
//		if (Current->Data == Target)
//		{
//			Match = Current;
//			if (Previous != NULL)
//			{
//				if (PPrevious != NULL)
//					PPrevious->NextNode = Current;
//				else
//					(*Head) = Current;
//
//				Previous->NextNode = Current->NextNode;
//				Current->NextNode = Previous;
//			}
//			break;
//		}
//		else
//		{
//			if (Previous != NULL)
//				PPrevious = Previous;
//
//			Previous = Current;
//			Current = Current->NextNode;
//		}
//	}
//	return Match;
//}



Node* SLL_FrequencyCount()
{

}

int main(void)
{

}