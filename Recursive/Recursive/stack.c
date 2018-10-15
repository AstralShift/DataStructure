#include"global.h"
#include "stack.h"

unsigned char initializeLS(struct Stack* stack)
{
	// 함수 포인터에 각 기능에 맞는 함수들을 연결해준다.
	stack->push = pushLS;
	stack->top = topLS;
	stack->pop = popLS;
	stack->empty = emptyLS;
	stack->release = releaseLS;

	stack->_size = 0;
	// 현재 스택과 연결된 노드가 없으니 NULL로 초기화 해준다.
	stack->_top = NULL;

	return TRUE;
}

void pushLS(struct Stack* stack, struct Vector2 pos)
{
	// 새 노드 포인터 변수 선언.
	struct Node* newNode = NULL;

	// 새 노드 포인터에 메모리 블럭 할당.
	newNode = (struct Node*)malloc(sizeof(struct Node));

	// 포인터 유효성 체크. (메모리 할당 받았는지?)
	if (NULL == newNode)
	{
		printf("Stack - pushLS 메모리 할당 실패\n");
		return;
	}
	// 새 노드에 데이터 초기화.
	newNode->pos = pos;

	// 만약 현재 스택이 비어있는 경우.(즉 _top이 NULL인경우)
	if (NULL == stack->_top)
		newNode->pNext = NULL;
	// 만약 현재 스택이 비어있지 않은 경우.(즉 현재 스택에 데이터가 있어서 맨 위칸을 가리키는 경우)
	else
		newNode->pNext = stack->_top;

	// top포인터를 새로 만든 노드로 한다.
	stack->_top = newNode;

	// 스택에 연결된 메모리 블럭의 갯수를 늘려준다.
	stack->_size++;
}

/**
* 해당 함수는 스택이 비어있을때 강제 종료 시켰다.
* pop에서 노드를 지우고 반환하게끔 해도 되지만 애초에 구현할때
* top으로 현재 가리키는 부분에 값만 가져오게 하여 쓰는 측면에서 활용도가 더 높다.(반복적으로 스택의 top값과 비교하거나 확인하는 경우)
*/
struct Vector2 topLS(struct Stack* stack)
{
	// a만약 스택이 비어있는 경우 exception.
	if (TRUE == stack->empty(stack))
	{
		printf("비어있는 스택에 top을 호출하였습니다.");
		exit(1);
	}
	// 현재 스택의 _top이 가리키고 있는 노드의 data값을 리턴한다.
	return stack->_top->pos;
}

void popLS(struct Stack* stack)
{
	// 만약 스택이 비어있다면 바로 리턴한다.
	// 굳이 TRUE라고 명시하고 비교한 이유는 가독성 때문.
	// 이렇게 한다고 성능에 영향은 거의 미미하다.
	if (TRUE == stack->empty(stack))
		return;
	// 지울 노드에 대한 변수선언.
	struct Node* deleteNode = NULL;

	// 현재 스택이 가리키고 있는 노드를 deleteNode로 가리킨다.
	// 이 포인터의 역할은 스택에서 연결이 끊어진 다음 지우는 역할을 한다.
	deleteNode = stack->_top;

	// 현재 스택의 가리키는 노드를 지울 노드의 다음 노드로 한다.
	stack->_top = deleteNode->pNext;

	// 노드를 삭제한다.
	free(deleteNode);

	// 메모리블럭의 갯수를 줄여준다.
	stack->_size--;
}

unsigned char emptyLS(struct Stack* stack)
{
	// size가 0이 아니라면,
	// 즉, 스택이 비어있지 않으면 FALSE를 리턴.
	if (0 != stack->_size)
		return FALSE;

	return TRUE;
}

unsigned int sizeLS(struct Stack* stack)
{
	return stack->_size;
}

void releaseLS(struct Stack* stack)
{
	// 만약 스택이 비어있다면 바로 리턴한다.
	// 굳이 TRUE라고 명시하고 비교한 이유는 가독성 때문.
	// 이렇게 한다고 성능에 영향은 거의 미미하다.
	if (TRUE == stack->empty(stack))
		return;


	while (FALSE == stack->empty(stack))
		stack->pop(stack);

	stack->_top = NULL;
	stack->_size = 0;
}

unsigned char createStack(struct Stack * stack)
{
	stack->initialize = initializeLS;

	return TRUE;
}
