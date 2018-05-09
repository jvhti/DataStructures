#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_HEAP

#define TYPE char
#define TYPE_PRINTF "%i"
#define TYPE_DEFAULT 0

#define FATHER(i) ((i-1)/2)
#define LCHILD(i) ((2*i)+1)
#define RCHILD(i) ((2*i)+2)

#define SWAP(a,b,t) ((t = a, a = b, b = t))

typedef struct _heap heap;

struct _heap{
	size_t alloc, size;
	TYPE *data;
};

heap *createHeap(size_t size);
void deleteHeap(heap *h);
void resizeHeap(heap *h, size_t size);

bool isEmptyHeap(heap *h);

void pushHeap(heap *h, TYPE data);
TYPE popHeap(heap *h);

void _reHeapDown(heap *h, size_t index);
void _reHeapUp(heap *h, size_t index);

size_t _smallestPowerOf2(size_t n);

void printHeap(heap *h);

int main(void);
