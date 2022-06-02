
#include <stdio.h>
#include <stdlib.h> // malloc() 및 srand(), rand() 포함 
#include <time.h> // rand(), srand() 사용 위한 라이브러리 추가

#define MAX_ARRAY_SIZE 13 
#define MAX_HASH_TABLE_SIZE MAX_ARRAY_SIZE

/* 함수 원형 선언 */
int initialize(int **a);
int freeArray(int *a);
void printArray(int *a);

// 정렬 함수
int selectionSort(int *a);
int insertionSort(int *a);
int bubbleSort(int *a);
int shellSort(int *a);
int quickSort(int *a, int n);

// 해시 함수
int hashCode(int key);
int hashing(int *a, int **ht);
int search(int *ht, int key);


int main()
{
    printf("------ [2019036068] [허원일] ------\n");

	char command;
	int *array = NULL; // 배열 포인터 선언 및 초기화
	int *hashtable = NULL; // 해시테이블 포인터 선언 및 초기화
	/* key, index 초기화 */
	int key = -1; 
	int index = -1;

	srand(time(NULL)); // 랜덤시간 seed로 난수 생성
	do{
		printf("----------------------------------------------------------------\n");
		printf("                        Sorting & Hashing                       \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize       = z           Quit             = q\n");
		printf(" Selection Sort   = s           Insertion Sort   = i\n");
		printf(" Bubble Sort      = b           Shell Sort       = l\n");
		printf(" Quick Sort       = k           Print Array      = p\n");
		printf(" Hashing          = h           Search(for Hash) = e\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'z': case 'Z':
            /* 배열 초기화 */ 
			initialize(&array);
			break;

		case 'q': case 'Q':
            /* 배열 메모리 해제 후 프로그램 종료 */
			freeArray(array);
			break;

		case 's': case 'S':
            /* 선택정렬 수행 */
			selectionSort(array);
			break;

		case 'i': case 'I':
            /* 삽입정렬 수행 */
			insertionSort(array);
			break;

		case 'b': case 'B':
            /* 버블정렬 수행 */
			bubbleSort(array);
			break;

		case 'l': case 'L':
            /* 셸정렬 수행 */
			shellSort(array);
			break;

		case 'k': case 'K':
            /* 퀵정렬 수행 */
			printf("Quick Sort: \n");
			printf("----------------------------------------------------------------\n");
			printArray(array);
			quickSort(array, MAX_ARRAY_SIZE);
			printf("----------------------------------------------------------------\n");
			printArray(array);

			break;

		case 'h': case 'H':
            /* 해싱 수행 */
			printf("Hashing: \n");
			printf("----------------------------------------------------------------\n");
			printArray(array);
			hashing(array, &hashtable);
			printArray(hashtable);
			break;

		case 'e': case 'E':
            /* 해시테이블에서 키값 검색 */
			printf("Your Key = ");
			scanf("%d", &key);
			printArray(hashtable);
			index = search(hashtable, key);
			printf("key = %d, index = %d,  hashtable[%d] = %d\n", key, index, index, hashtable[index]);
			break;

		case 'p': case 'P':
            /* 배열 출력 */
			printArray(array);
			break;

		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	} while(command != 'q' && command != 'Q');

	return 1;
}

/* 배열을 초기화하는 함수 */
int initialize(int** a)
{
	int *temp = NULL;

	/* array가 NULL인 경우 메모리 할당 */
	if(*a == NULL) {
		temp = (int*)malloc(sizeof(int) * MAX_ARRAY_SIZE);
		*a = temp;  /* 할당된 메모리의 주소를 복사 --> main에서 배열을 control 할수 있도록 함*/
	} else
		temp = *a;

	/* 랜덤값을 배열의 값으로 저장 */
	for(int i = 0; i < MAX_ARRAY_SIZE; i++)
		temp[i] = rand() % MAX_ARRAY_SIZE; 

	return 0;
}

/* 배열에 할당된 메모리 해제하는 함수 */
int freeArray(int *a)
{
	/* 배열포인터가 NULL이 아닌경우, 즉 배열 존재시 포인터 해제 */
	if(a != NULL)
		free(a);

	return 0;
}

/* 배열을 출력하는 함수 */
void printArray(int *a)
{
    /* 배열포인터가 NULL인 경우 경고문 출력 후 함수 종료 */
	if (a == NULL) {
		printf("nothing to print.\n");
		return;
	}

	for(int i = 0; i < MAX_ARRAY_SIZE; i++)
		printf("a[%02d] ", i);
	printf("\n");

	for(int i = 0; i < MAX_ARRAY_SIZE; i++)
		printf("%5d ", a[i]);
	printf("\n");
}

/* 선택정렬을 수행하는 함수 */
/* 선택정렬 : 전체 원소 중에서 기준 위치에 맞는 원소를 선택해 자리를 교환 */
int selectionSort(int *a)
{
	int min;
	int minindex;
	int i, j;

	printf("Selection Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a);

	for (i = 0; i < MAX_ARRAY_SIZE; i++)
	{
		minindex = i; // 기준위치 인덱스
		min = a[i]; // 기준위치 인덱스의 요소를 최솟값을 임시 저장
		/* 배열크기 - 1 만큼 반복하며 정렬 수행 */
		for(j = i+1; j < MAX_ARRAY_SIZE; j++)
		{
			// 임시 최솟값보다 a[j]가 작을 경우 임시 최솟값 갱신
			if (min > a[j])
			{
				min = a[j];
				minindex = j;
			}
		}
		a[minindex] = a[i]; // 기준위치 인덱스의 요소를 최솟값이 있는 배열의 위치에 덮어씀
		a[i] = min; // 기준위치 인덱스에 최솟값 저장
	}

	printf("----------------------------------------------------------------\n");
	printArray(a);
	return 0;
}

/* 삽입정렬을 수행하는 함수 */
/* 삽입정렬 : 정렬되어 있는 부분집합에 정렬할 새로운 원소의 위치를 찾아 삽입 */
int insertionSort(int *a)
{
	int i, j, t;

	printf("Insertion Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a);

	for(i = 1; i < MAX_ARRAY_SIZE; i++)
	{
        /* S : 정렬된 집합, U : 정렬되지 않은 집합 */
		t = a[i]; // 임시공간에  U의 첫번째 원소 저장
		j = i; // U의 첫번째 원소의 인덱스를 다른 변수에 복사

        // S의 가장마지막 원소가 t보다 크고 j가 0보다 클때까지 반복
		while (a[j-1] > t && j > 0)
		{
			a[j] = a[j-1]; // 현재 위치에 이전 위치의 원소를 대입
			j--; // j 왼쪽으로 이동
		}
		a[j] = t; // 최종 j 위치에 U의 첫번째 원소 대입
	}

	printf("----------------------------------------------------------------\n");
	printArray(a);

	return 0;
}

/* 버블정렬을 수행하는 함수 */
/* 버블정렬 : 인접한 두 원소를 비교하여 자리를 교환하는 방식을 반복 */
int bubbleSort(int *a)
{
	int i, j, t;

	printf("Bubble Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a);

	/* 배열 크기만큼 반복하며 정렬 수행 */
	for(i = 0; i < MAX_ARRAY_SIZE; i++)
	{
		for (j = 0; j < MAX_ARRAY_SIZE - i; j++)
		{
			/* 이전 원소가 더 클 경우 SWAP 진행 */
			if (a[j-1] > a[j] && j > 0)
			{
				t = a[j-1];
				a[j-1] = a[j];
				a[j] = t;
			}
		}
	}

	printf("----------------------------------------------------------------\n");
	printArray(a);

	return 0;
}

/* 셸 정렬을 수행하는 함수 */ 
/* 셸 정렬 : 일정한 간격으로 떨어져 있는 자료들끼리 부분집합 구성 후, 
			각 부분집합에 있는 원소에 대해 삽입정렬 수행 반복 */
int shellSort(int *a)
{
	int i, j, k, h, v;

	printf("Shell Sort: \n");
	printf("----------------------------------------------------------------\n");

	printArray(a);

	/* h: 부분집합을 만드는 기준이 되는 간격을 저장 */ 
	/* 초기 h를 배열의 절반으로 지정하고 단계가 수행될 때마다 절반씩 감소 */
	for (h = MAX_ARRAY_SIZE/2; h > 0; h /= 2) 
	{
		/* 단계별로 만들 수 있는 최대 부분집합 개수만큼 반복 */
		for (i = 0; i < h; i++)
		{
			/* 부분집합 내에서 정렬 수행 (간격이 배열 인덱스를 넘어가기 전까지 반복) */
			for(j = i + h; j < MAX_ARRAY_SIZE; j += h)
			{
				v = a[j]; // 부분집합의 뒤 원소를 따로 저장
				k = j; // 뒤 원소의 인덱스를 따로 저장
				/* 부분집합의 뒤 원소가 더 작은 경우 SWAP */
				while (k > h-1 && a[k-h] > v)
				{
					a[k] = a[k-h];
					k -= h;
				}
				a[k] = v;
			}
		}
	}
	printf("----------------------------------------------------------------\n");
	printArray(a);

	return 0;
}

/* 퀵정렬을 수행하는 함수 */
int quickSort(int *a, int n)
{
	int v, t;
	int i, j;

	if (n > 1) // 분할된 부분집합의 원소가 두개이상인 경우에만 실행
	{
		v = a[n-1]; // 정렬 범위(부분 집합)에서 마지막 원소 v를 pivot으로 선택
		i = -1; // i번째 원소 : 정렬 범위의 왼쪽 끝에서 오른쪽으로 움직이면서 피봇보다 크거나 같은 원소를 찾음
		j = n - 1; // j번째 원소 : 정렬 범위의 오른쪽 끝에서 왼쪽으로 움직이면서 피봇보다 작은 원소를 찾음

		/* i와 j와 만난 경우 무한루프 탈출 */
		while(1)
		{
			while(a[++i] < v); // 피봇보다 크거나 같은 원소를 찾을 때까지 오른쪽으로 이동
			while(a[--j] > v); // 피봇보다 작거나 같은 원소를 찾을 때까지 왼쪽으로 이동

			if (i >= j) break;
			/* i와 j가 만나기 이전에 각각 목표한 원소를 찾은 경우 SWAP a[i], a[j] */
			t = a[i];
			a[i] = a[j];
			a[j] = t;
		}

		/* i와 j가 만난경우, SWAP a[i], a[n-1](pivot) */
		t = a[i];
		a[i] = a[n-1];
		a[n-1] = t;

		quickSort(a, i); // 피봇의 확정된 위치 기준 왼쪽 부분집합에서 퀵정렬 수행
		quickSort(a+i+1, n-i-1); // 피봇의 확정된 위치 기준 오른쪽 부분집합에서 퀵정렬 수행
	}


	return 0;
}


int hashCode(int key) {
   return key % MAX_HASH_TABLE_SIZE;
}

/* 배열 a에 대해 hash table을 생성하는 함수 */
int hashing(int *a, int **ht)
{
	int *hashtable = NULL; // hash table을 가리키는 포인터 초기화

	/* hash table에 저장된 주소가 NULL인 경우, 메모리 할당 */
	if(*ht == NULL) {
		hashtable = (int*)malloc(sizeof(int) * MAX_ARRAY_SIZE);
		*ht = hashtable; // 할당된 메모리의 주소를 이중포인터 ht에 복사 -> main 내에서 배열 조작 가능
	/* NULL이 아닌 경우, hash table 재활용 */
	} else {
		hashtable = *ht; 
	}

	/* hash table의 저장된 값 초기화 */
	for(int i = 0; i < MAX_HASH_TABLE_SIZE; i++)
		hashtable[i] = -1;

	/*
	for(int i = 0; i < MAX_HASH_TABLE_SIZE; i++)
		printf("hashtable[%d] = %d\n", i, hashtable[i]);
	*/
	
	/* key, hashcode, index 초기화 */
	int key = -1;
	int hashcode = -1;
	int index = -1;

	/* 배열 크기만큼 돌며 수행 */
	for (int i = 0; i < MAX_ARRAY_SIZE; i++)
	{
		key = a[i]; // 배열의 값을 key에 저장
		hashcode = hashCode(key); // key값에 대한 hash값(hashCode로부터 얻은)을 hashcode로 지정
		/* 
		printf("key = %d, hashcode = %d, hashtable[%d]=%d\n", key, hashcode, hashcode, hashtable[hashcode]);
		*/
		/* 슬롯이 빈 경우 key값 삽입 */
		if (hashtable[hashcode] == -1)
		{
			hashtable[hashcode] = key;
		} 
		/* 슬롯이 찬 경우 빈 슬롯 재탐색 */
		else {

			index = hashcode; // hashcode값을 index에 임시 저장

			/* 빈 슬롯을 찾을때까지 index(hashcode) 변경 반복 */
			while(hashtable[index] != -1)
			{
				// index를 index+1을 hash table 크기로 나눈 나머지 값으로 변경
				index = (++index) % MAX_HASH_TABLE_SIZE;

				/*
				printf("index = %d\n", index);
				*/
			}
			hashtable[index] = key; // 빈 슬롯을 찾은 경우, 해당 key 삽입
		}
	}

	return 0;
}

/* 해시테이블에서 키를 검색하는 함수 */
int search(int *ht, int key)
{
	int index = hashCode(key); // 검색하려는 키에 해당하는 hashcode를 index에 임시저장

	/* 해당 위치에 key가 존재하면 hashcode 반환 */
	if(ht[index] == key)
		return index;
	/* key를 찾을 때까지 index를 index+1을 hash table 크기로 나눈 나머지로 초기화하는 작업 반복 */
	while(ht[++index] != key)
	{
		index = index % MAX_HASH_TABLE_SIZE;
	}

	return index; // 키값의 인덱스 리턴
}



