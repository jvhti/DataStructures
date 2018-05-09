#include "Heap.h"

int main(void){
	heap *h = createHeap(1);

	for(size_t i = 0; i < 100000; ++i)
		pushHeap(h, rand() % 255);
	printHeap(h);

	TYPE t = popHeap(h), tt;
	while(!isEmptyHeap(h)){
		//printHeap(h);
		tt = popHeap(h);
		if(t < tt){
			printf("Invalid output %i (last pop) < %i (cur pop)\n", t, tt);
			exit(1);
		}
		t = tt;
	}
	printHeap(h);
	return 0;
}

heap *createHeap(size_t size){
	heap *h = (heap*)malloc(sizeof(heap));

	if(!h){
		printf("Error: Can't malloc heap\n");
		exit(1);
		return NULL;
	}

	h->alloc = size;
	h->size = 0;

	h->data = (TYPE*)malloc(sizeof(TYPE) * h->alloc);

	if(!h->data){
		printf("Error: Can't alloc %i bytes for the heap\n", sizeof(TYPE) * h->alloc);
		exit(1);
		return NULL;
	}

	return h;
}

void pushHeap(heap *h, TYPE data){
	if(h->size + 1 > h->alloc) resizeHeap(h, h->alloc << 1);

	h->data[h->size++] = data;

	_reHeapUp(h, h->size - 1);
}

TYPE popHeap(heap *h){
	if(h->size == 0) return TYPE_DEFAULT;

	TYPE ret = h->data[0];

	--h->size;

	if(h->size == 0) return ret;

	h->data[0] = h->data[h->size];

	_reHeapDown(h, 0);

	if(h->alloc > h->size * 2) resizeHeap(h, _smallestPowerOf2(h->size));

	return ret;
}

void printHeap(heap *h){
	for(int i = 0; i < h->size; ++i)
		printf(TYPE_PRINTF", ", h->data[i]);

	printf("\n=====================\n");
}

void resizeHeap(heap *h, size_t size){
	//printf("Realloc from %lu to  %lu\n", h->alloc, size);
	h->alloc = size;
	TYPE *tdata = (TYPE*)realloc(h->data, sizeof(TYPE) * h->alloc);
	if(!tdata){
		printf("Error: Can't resize the heap data array to %i bytes\n", sizeof(TYPE) * h->alloc);
		exit(1);
	}
}

void _reHeapUp(heap *h, size_t index){
	if(index == 0 || h->data[FATHER(index)] > h->data[index]) return;

	TYPE t = h->data[FATHER(index)];
	h->data[FATHER(index)] = h->data[index];
	h->data[index] = t;

	_reHeapUp(h, FATHER(index));
}

void _reHeapDown(heap *h, size_t index){
	size_t lc = LCHILD(index), rc = RCHILD(index);
	TYPE t;

	if(lc < h->size && rc < h->size){
		if(h->data[lc] >= h->data[rc] && h->data[lc] > h->data[index]){
			SWAP(h->data[index], h->data[lc], t);
			_reHeapDown(h, lc);
		}else if(h->data[rc] > h->data[index]){
			SWAP(h->data[index], h->data[rc], t);
			_reHeapDown(h, rc);
		}

	}else{
		if(lc < h->size && h->data[lc] > h->data[index]){
			SWAP(h->data[index], h->data[lc], t);
			_reHeapDown(h, lc);
		}
	}
}

bool isEmptyHeap(heap *h){
	return h->size == 0;
}

size_t _smallestPowerOf2(size_t n){
	size_t count = 0;

	if (n && !(n&(n-1))) return n;
	while( n != 0){
		n  >>= 1;
		++count;
	}

	return 1 << count;
}
