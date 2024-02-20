#include <stdio.h>
#include <assert.h>
#include <string.h>

#define MAX_INPUT_COUNT 1024
static char input[MAX_INPUT_COUNT];
static int inputCount;

void slurp_file(){
	FILE *file = fopen("test.txt", "rb");
	assert(file);
	fread(input, sizeof(*input), MAX_INPUT_COUNT, file);
	inputCount = ftell(file);
	fclose(file);
}

void cheapest_products(){
	char *currentChar = input;

	while((currentChar - input) < inputCount){
		while(*currentChar++ != ',');

		char *currentProduct = currentChar;
		while(*currentChar++ != ',');
		int currentProductLength = currentChar - currentProduct - 1;

		char *currentPrice = currentChar;
		while(*currentChar++ != '\n');
		int currentPriceLength = currentChar - currentPrice - 1;

		write(1, currentProduct, currentProductLength);
		write(1, " : ", 3);
		write(1, currentPrice, currentPriceLength);
		write(1, "\n", 1);
	}
	fflush(stdout);
}

int main(){
	slurp_file();
	cheapest_products();
	printf("\n%s", input);

	return 0;
}
