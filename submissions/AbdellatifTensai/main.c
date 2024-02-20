#include <stdio.h>
#include <assert.h>

#define INPUT_COUNT 1024
static char input[INPUT_COUNT];

void slurp_file(){
	FILE *file = fopen("input.txt", "rb");
	assert(file);
	fread(input, sizeof(*input), INPUT_COUNT, file);
	fclose(file);
}

int main(){
	slurp_file();
	printf("%s", input);
	return 0;
}
