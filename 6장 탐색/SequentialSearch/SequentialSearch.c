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

// 내가 구현한 전진 이동법(함수 호출 + 재탐색 구조라 가독성은 나쁘지 않지만, 효율은 떨어짐)
Node* SLL_MoveToFront(Node** Head, int Target)
{
	Node* Match = SLL_SequentialSearch((*Head), Target);
	if (Match == NULL)
	{
		return NULL;
	}
	else if (Match == (*Head))
	{
		// 이미 탐색된 항목이 Head이므로 할일 없음
	}
	else
	{
		// Match의 전 노드를  찾아서 재배열
		Node* Prev = (*Head);
		while (Prev != NULL)
		{
			if (Prev->NextNode == Match)
			{
				// Match는 Head로 갱신, Match의 공백 자리 연결
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

// 전진 이동법 모범답안
//Node* SLL_MoveToFront(Node** Head, int Target)
//{
//	Node* Current = (*Head);
//	Node* Previous = NULL;
//	Node* Match = NULL;
//
//	while (Current != NULL)
//	{
//		// 처음 if문을 만날 땐 Current가 Head이므로 Prev가 없음(if가 참이여도 위치 재배열이 필요 없다는 말)
//		if (Current->Data == Target)
//		{
//			Match = Current;
//			if (Previous != NULL)
//			{
//				//	자신의 앞 노드와 다음 노드를 연결
//				Previous->NextNode = Current->NextNode;
//
//				//	자신을 리스트의 가장 앞으로 옮기기
//				Current->NextNode = (*Head);
//				(*Head) = Current;
//			}
//			break;
//		}
//		else
//		{
//			// Current가 Head가 아니므로 else로 오고 이때 Prev를 초기화 겸 저장을 하면 되는거임! 유레카
//			Previous = Current;
//			Current = Current->NextNode;
//		}
//	}
//	return Match;
//}




/*
남은 개선 포인트
네 방식은 Head / 2번째 노드 / 나머지 노드를 세 가지 경우로 완전히 나눠서 처리하는데,
모범답안은 하나의 while 루프 안에서 포인터 이동만으로 모든 경우를 처리했어.

즉,

네 버전: 가독성은 좋지만 코드가 길고, Head 교체 로직이 중복될 가능성 있음.

모범답안: 로직은 간결하지만, 초보자가 읽기엔 헷갈릴 수 있음.

만약 “가독성과 안전성”을 우선하면 지금 네 코드가 더 좋아.
다만, “코드 길이 최소화”를 원하면 모범답안 스타일로 병합하는 게 좋을 수도 있어.
*/
Node* SLL_Transpose(Node** Head, int Target)
{
	Node* Current = *Head;
	Node* Prev = NULL;
	Node* PPrev = NULL;
	Node* Match = NULL;

	while (Current != NULL) // 정상적인 상황만 처리
	{
		if (Target == (*Head)->Data) // 1. Target이 Head였다면
		{
			Match = (*Head);
			break; /*찾았다면 중단해주기!*/
		}
		/* 단일 노드인 경우 처리해주기 */
		else if ((*Head)->NextNode != NULL && Target == (*Head)->NextNode->Data) // 2. Target이 2번째 노드였다면
		{
			Match = (*Head)->NextNode; // 2번째 데이터로 저장

			// Head랑 Match랑 순서 바꾸기
			(*Head)->NextNode = Match->NextNode;
			Match->NextNode = (*Head);
			(*Head) = Match;

			break;
		}
		else // 3. Target이 3번째 노드 이상이면(그 외)
		{
			PPrev = (*Head);
			Prev = PPrev->NextNode;
			Current = Prev->NextNode;

			while (Current != NULL && Current->Data != Target) /*조건의 순서를 바꿈*/
			{
				// Target 노드 찾을 때까지 세 노드 각자의 다음 노드로 갱신
				PPrev = PPrev->NextNode;
				Prev = Prev->NextNode;
				Current = Current->NextNode;
			}

			if (Current != NULL) // Target을 못 찾고 리스트 범위를 넘지 않았으면
			{
				Match = Current; // 반환할 Match 저장

				// 위치 재배열
				Prev->NextNode = Current->NextNode;
				Current->NextNode = Prev;
				PPrev->NextNode = Current;
			}

			break;
		}
	}

	return Match;
}

// 전위법 모범답안
//Node* SLL_Transpose(Node** Head, int Target)
//{
//	Node* Current = (*Head);
//	Node* PPrevious = NULL; //	이전 노드의 이전 노드
//	Node* Previous = NULL; //	이전 노드
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