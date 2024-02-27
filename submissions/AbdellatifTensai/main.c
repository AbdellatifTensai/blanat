#include <stdio.h>
#include <stdint.h>
#include <assert.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>

#define  ARRAY_COUNT(arr) (sizeof(arr)/sizeof(arr[0]))

static char *input;
static int inputCount;
//removed duplicated names: Cantaloupe, Cranberry, Coconut, Honeydew, Pomegranate, Artichoke.
const char *products[] = {
    "Apple", "Banana", "Orange", "Strawberry", "Grapes",
    "Watermelon", "Pineapple", "Mango", "Kiwi", "Peach",
    "Plum", "Cherry", "Pear", "Blueberry", "Raspberry",
    "Blackberry", "Cantaloupe", "Coconut",
    "Lemon", "Lime", "Grapefruit", "Avocado", "Papaya",
    "Guava", "Fig", "Passion_Fruit", "Apricot", "Nectarine",
    "Cucumber", "Carrot", "Broccoli", "Spinach", "Kale",
    "Lettuce", "Tomato", "Bell_Pepper", "Zucchini", "Eggplant",
    "Cabbage", "Cauliflower", "Brussels_Sprouts", "Radish", "Beet",
    "Asparagus", "Green_Beans", "Peas", "Celery",
    "Onion", "Garlic", "Potato", "Sweet_Potato", "Yam",
    "Butternut_Squash", "Acorn_Squash", "Pumpkin", "Cranberry", "Goji_Berry",
    "Currant", "Date", "Clementine", "Rhubarb",
    "Chard", "Collard_Greens", "Parsley", "Cilantro", "Mint",
    "Basil", "Thyme", "Rosemary", "Sage", "Dill",
    "Oregano", "Honeydew", "Pomegranate",
    "Jackfruit", "Starfruit", "Persimmon", "Ginger", "Turnip",
    "Jicama", "Kohlrabi", "Watercress", "Okra", "Artichoke",
    "Plantain", "Cactus_Pear", "Kiwano", "Squash_Blossom", "Dragon_Fruit",
    "Parsnip", "Rutabaga", "Salsify", "Bok_Choy", "Endive"
};
const size_t productsCount = ARRAY_COUNT(products);

const char *cities[] = {
    "Casablanca", "Rabat", "Marrakech", "Fes", "Tangier",
    "Agadir", "Meknes", "Oujda", "Kenitra", "Tetouan",
    "Safi", "El_Jadida", "Beni_Mellal", "Errachidia",
    "Taza", "Essaouira", "Khouribga", "Guelmim",
    "Jorf_El_Melha", "Laayoune", "Ksar_El_Kebir", "Sale", "Bir_Lehlou",
    "Arfoud", "Temara", "Mohammedia", "Settat",
    "Béni_Mellal", "Nador", "Kalaat_MGouna",
    "Chichaoua", "Chefchaouen", "Al_Hoceima", "Taourirt",
    "Taroudant", "Guelta_Zemmur", "Dakhla", "Laâyoune",
    "Tiznit","Tinghir", "Ifrane", "Azrou", "Bab_Taza",
    "Berrechid", "Sidi_Slimane", "Souk_Larbaa", "Tiflet", "Sidi_Bennour",
    "Larache", "Tan-Tan", "Sidi_Ifni", "Goulmima",
    "Midelt", "Figuig", "Azilal", "Jerada", "Youssoufia",
    "Ksar_es_Seghir", "Tichka", "Ait_Melloul",
    "Layoune", "Ben_guerir", "Ouarzazate", "Inezgane",
    "Oujda_Angad", "Sefrou", "Aourir",
    "Oulad_Teima", "Tichla", "Bni_Hadifa",
    "Fquih_Ben_Salah", "Guercif", "Bouarfa", "Demnate",
    "Ahfir", "Berkane", "Akhfenir", "Boulemane",
    "Khenifra", "Bir_Anzerane", "Assa", "Smara", "Boujdour",
    "Tarfaya", "Ouazzane", "Zagora", "had_soualem",
    "Saidia", "Bab_Berred", "Midar", "Moulay_Bousselham",
    "Khemisset", "Guerguerat", "Asilah", "Sidi_Bouzid", "Tafraout",
    "Imzouren", "Zemamra", "Sidi_Kacem", "Drarga", "Skhirate"
    };

const size_t citiesCount = ARRAY_COUNT(cities);

typedef struct{ char digit[4]; } real_num;

static real_num citiesHashes[10000];
uint16_t citiesHashesMin = 0;
static real_num productsHashes[10000];
uint16_t productsHashesMin = 0;

void slurp_file(){
	FILE *file = fopen("input.txt", "rb");
	assert(file);
	fseek(file, 0, SEEK_END);
	size_t inputSize = ftell(file);
	rewind(file);

	input = (char *)malloc(inputSize);
	inputCount = inputSize/sizeof(char); //being explicit
	fread(input, sizeof(*input), inputSize, file);
	fclose(file);
}

int less_than(real_num a, real_num b){
	if(a.digit[0] < b.digit[0]) return 1;
	else if(a.digit[0] > b.digit[0]) return 0;
	else if(a.digit[1] < b.digit[1]) return 1;
	else if(a.digit[1] > b.digit[1]) return 0;
	else if(a.digit[2] < b.digit[2]) return 1;
	else if(a.digit[2] > b.digit[2]) return 0;
	else if(a.digit[3] < b.digit[3]) return 1;
	else if(a.digit[3] > b.digit[3]) return 0;

	return 0;
}

uint16_t products_perf_hash(char *cstr, size_t length){
	//trial and error
	return cstr[0]*length + cstr[1]*22 + cstr[length/3-1]*21 + cstr[length-1]*13 - productsHashesMin;
}

uint16_t cities_perf_hash(char *cstr, size_t length){
	//trial and error
	return cstr[0]*length + cstr[1]*2 + cstr[length/4-1]*19 + cstr[length*3/4-1]*23 + cstr[length-2]*21 - citiesHashesMin;
}

void cheapest_products(){
	char *currentChar = input;

	while((currentChar - input + 1) < inputCount){
		char *currentCity = currentChar;
		while(*currentChar++ != ',');
		int currentCityLength = currentChar - currentCity - 1;

		char *currentProduct = currentChar;
		while(*currentChar++ != ',');
		int currentProductLength = currentChar - currentProduct - 1;

		real_num currentPrice;

		currentPrice.digit[0] = *currentChar++;
		if(*currentChar == '.'){
			currentPrice.digit[1] = currentPrice.digit[0];
			currentPrice.digit[0] = '0';
		}
		else
			currentPrice.digit[1] = *currentChar++;

		currentPrice.digit[2] = *++currentChar;

		currentPrice.digit[3] = *++currentChar == '\n'? '0': *currentChar++;
		currentChar++;

		uint16_t productHash = products_perf_hash(currentProduct, currentProductLength);
		real_num currentLowestPrice = productsHashes[productHash];
		if(less_than(currentPrice, currentLowestPrice))
			productsHashes[productHash] = currentPrice;

		//debug
		//for(int x=0; x<currentProductLength; x++) printf("%c",currentProduct[x]);
		//printf(" : %c%c.%c%c : %d\n", currentPrice.digit[0], currentPrice.digit[1], currentPrice.digit[2], currentPrice.digit[3], productHash);
	}
	fflush(stdout);
}

void init_hashes(){
	memset(productsHashes, 0x7F, sizeof(productsHashes));
	memset(citiesHashes, 0x7F, sizeof(citiesHashes));
	uint16_t min = -1;
	for(int x=0; x<citiesCount; x++){
		char *c = cities[x];
		uint16_t hash = cities_perf_hash(c, strlen(c));
		if(hash < min) min = hash;
	}
	citiesHashesMin = min;
	for(int x=0; x<productsCount; x++){
		char *c = products[x];
		uint16_t hash = products_perf_hash(c, strlen(c));
		if(hash < min) min = hash;
	}
	productsHashesMin = min;
}

int main(){
	slurp_file();
	init_hashes();

	struct timespec init, final;
	clock_gettime(CLOCK_REALTIME, &init);
	cheapest_products();
	clock_gettime(CLOCK_REALTIME, &final);

	size_t elapsed = ((size_t)final.tv_sec - (size_t)init.tv_sec) + ((size_t)final.tv_nsec - (size_t)init.tv_nsec);
	printf("time took: %luns %fms\n", elapsed, (double)elapsed*1e-6);

	for(int x=0; x<productsCount; x++){
		char *product = products[x];
		real_num price = productsHashes[products_perf_hash(product, strlen(product))];
		printf("%s : %c%c.%c%c\n", product, price.digit[0], price.digit[1], price.digit[2], price.digit[3] );
	}

	return 0;
}
