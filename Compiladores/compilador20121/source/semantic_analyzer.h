

typedef struct {
	int integer;
	double real;
	char *string;

	char *type; // symbol type
	int addr;   // symbol table addr;

	int intval;
	double realval;
	char charval;
} Attributes;
