#ifndef _STACK_H_
#define _STACK_H_
#include "global.h"

/**
 * Stack의 기본적인 기능들에 대해 구현해놓았다.
 * Array방식으로는 메모리 공간에 대한 제약때문에(할당량 만큼만 써야한다든가 혹은 재할당하고 copy structure한다든가 등)
 * 그런이유로 연결갯수에 제약에서 많이 자유로운 Linked 방식을 활용한 Stack을 구현하였다.
 */
struct Stack
{
	// 현재 스택의 최상단 메모리 블럭을 가리키는 포인터.
	struct Node* _top;
	// 현재 스택에 대한 크기.(할당된 메모리 블럭의 갯수)
	unsigned int _size;

	/* initialize()
	 *
	 * initialize에서는 구조체 변수들을 초기화 하고 각각의 함수포인터에 맞는 함수를 연결해준다.
	 *
	 * Parameters:
	 *     struct Stack* : 만들어 둔 스택구조체 변수를 인자로 가져온다.(더 좋은 방식을찾지 못한 한계)
	 * Returns : unsigned char
	 *     initialize가 실패하면 FALSE(0)을 리턴하고 성공하면 TRUE(1)을 리턴한다.
	 */
	unsigned char(*initialize)(struct Stack* stack);
	
	/* push()
	 *
	 * push에서는 인자로 전달된 struct Vector2의 값을 담은 새 노드를 만들어서 스택에 연결해준다.
	 *
	 * Parameters:
	 *     struct Stack*  : intialize의 인자 struct Stack*와 동일. 해당 부분 참조.
	 *     struct Vector2 : 위치값을 나타내는 구조체 변수.
	 * Returns : void
	 */
	void(*push)(struct Stack* stack, struct Vector2 data);

	/* top()
	 *
	 * top에서는 현재 스택이 가리키고 있는 최상단 메모리블럭의 값을 리턴해준다.
	 *
	 * Parameters:
	 *     struct Stack*  : intialize의 인자 struct Stack*와 동일. 해당 부분 참조.
	 * Returns : struct Vector2
	 *     위치값을 나타낸 구조체 변수 하나를 리턴한다.
	 */
	struct Vector2(*top)(struct Stack* stack);

	/* pop()
	 *
	 * 현재 스택이 가리키고 있는 최상단 메모리 블럭과의 연결을 끊고 그 메모리 블럭을 삭제한다.
	 *
	 * Parameters:
	 *     struct Stack*  : intialize의 인자 struct Stack*와 동일. 해당 부분 참조.
	 * Returns : void
	 */
	void(*pop)(struct Stack* stack);

	/* empty()
	*
	* 현재 스택이 비어있는지 확인하는 기능.
	*
	* Parameters:
	*     struct Stack*  : intialize의 인자 struct Stack*와 동일. 해당 부분 참조.
	* Returns : unsigned char
	*     initialize가 실패하면 FALSE(0)을 리턴하고 성공하면 TRUE(1)을 리턴한다.
	*/
	unsigned char(*empty)(struct Stack* stack);

	/* size()
	*
	* 현재 스택에 연결된 메모리 블럭의 갯수를 리턴해주는 기능.
	*
	* Parameters:
	*     struct Stack*  : intialize의 인자 struct Stack*와 동일. 해당 부분 참조.
	* Returns : unsigned int
	*     스택과 연결된 메모리 블럭갯수를 리턴.
	*/
	unsigned int (*size)(struct Stack* stack);

	/* release()
	*
	* 스택과 연결된 최상단 메모리부터 차례로 스택과의 연결을 끊으면서 메모리블럭을 삭제한다.
	*
	* Parameters:
	*     struct Stack*  : intialize의 인자 struct Stack*와 동일. 해당 부분 참조.
	* Returns : void
	*/
	void(*release)(struct Stack* stack);
};

/*
 * 아래 region으로 묶인 StackFunctions는
 * 위에 선언한 스택의 함수포인터 변수들과 연결될 목적의 함수들이다.
 * 주석들을 위에 Stack구조체의 함수포인터에 쓴 이유는
 * 외부인터페이스로서의 역할을 하는 것은 위에 선언한 Stack 구조체이므로
 * 실질적으로 외부에서 사용 할 때 해당 함수의 주석 참조(마우스 on을 해서든 직접 헤더참조를 하던)는
 * 위에 선언한 Stack구조체에 하기 때문이다.
 * 현재 프로젝트에서는 의미가 덜하지만 모듈별로 나누면??
 * 외부인터페이스에 주석다는 것이 의미가 크다 생각했다.
 */
#pragma region StackFunctions
unsigned char initializeLS(struct Stack* stack);
void pushLS(struct Stack* stack, struct Vector2 pos);
struct Vector2 topLS(struct Stack* stack);
void popLS(struct Stack* stack);
unsigned char emptyLS(struct Stack* stack);
unsigned int sizeLS(struct Stack* stack);
void releaseLS(struct Stack* stack);
unsigned char createStack(struct Stack * stack);
#pragma endregion
#endif