#ifndef _UTILLITY_H_
#define _UTILLITY_H_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <malloc.h>
#include <crtdbg.h>


/**
 * 위치값을 표현해 내기 위한 구조체.
 * Vector와 어울리지 않는 표현인 unsigned char를 사용하였다.
 * POSITION이라고 네이밍을 하는게 좋겠지만
 * 편의상 일반적으로 많이 쓰이는 Vector2로 하였다.
 */
struct Vector2
{
	unsigned char x, y;
};

/**
 * Linked Stack을 활용하기 위해
 * Node구조체에 자기참조구조체 변수를 넣어 만들었다.
 * 이로써 Node간의 연결 표현이 가능해져 Linked 방식의 노드로써 활용이 가능해졌다.
 * 현재에는 범용성이 없는 데이터(pos변수는 Vector2로 되어있다.)로 되어있어
 * 노드를 활용하는 자료구조 또한 범용성이 떨어진다.
 * 추후 이를 개선하여 void* 를 활용할 예정이다.
 */
struct Node
{
	// 위치 값을 갖는 변수.
	struct Vector2 pos;
	// 자기 참조 구조체. 이를 활용하여 노드간의 연결이 가능하다.
	struct Node* pNext;
};

// const를 이용해 Global에서 안전하게 상수값으로 활용. #define 사용 지양
extern const unsigned char const FALSE;
extern const unsigned char const TRUE;

#endif