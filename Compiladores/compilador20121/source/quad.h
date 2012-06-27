typedef enum {
	plus, minus, un_minus, times, div,
} Op;

typedef struct {
	Op op;
	int arg1;
	int arg2;
	int result;
} Quad;
