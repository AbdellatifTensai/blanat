#include <stdio.h>
#include <stdint.h>
#include <assert.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <float.h>

#define  ARRAY_COUNT(arr) (sizeof(arr)/sizeof(arr[0]))
#define PRODUCTS_HASHES 20000
#define CITIES_HASHES 20000

//removed duplicated names: Cantaloupe, Cranberry, Coconut, Honeydew, Pomegranate, Artichoke.
char *products[] = {
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
const int productsCount = ARRAY_COUNT(products);

char *cities[] = {
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
const int citiesCount = ARRAY_COUNT(cities);

typedef struct{ char digit[4]; } real_num;

static char *input;
static int inputCount;
uint16_t citiesHashesMin = 0;
uint16_t productsHashesMin = 0;
uint16_t productsHashesMax = 0;
float *hashmap;

void slurp_file(){
	FILE *file = fopen("input.txt", "rb");
	assert(file);
	fseek(file, 0, SEEK_END);
	size_t inputSize = ftell(file);
	rewind(file);

	input = (char *)malloc(inputSize);
	inputCount = inputSize;
	fread(input, sizeof(*input), inputSize, file);
	fclose(file);
}

float to_float(char digits[4]){
	float f = 0.0f;
	f += (digits[0] - '0')*10.0f;
	f += (digits[1] - '0')*1.0f;
	f += (digits[2] - '0')*0.1f;
	f += (digits[3] - '0')*0.01f;
	return f;
}

uint32_t products_perf_hash(char *cstr, size_t length){
	//trial and error
	return cstr[0]*length + cstr[1]*22 + cstr[length/3-1]*21 + cstr[length-1]*13 - productsHashesMin;
}

uint32_t cities_perf_hash(char *cstr, size_t length){
	//trial and error
	//return cstr[0]*length + cstr[length-2]*length + cstr[length/4-1]*19 + cstr[length*3/4-1]*23 + cstr[length-1]*9 - citiesHashesMin;
	//return cstr[0]*length + cstr[1]*length + cstr[2]*19 + cstr[length-1]*6 + cstr[length-2]*5 - citiesHashesMin;
	return ((cstr[0]<<24) + (cstr[1]<<16) + (cstr[length*3/4-1]<<8) + (cstr[length-1])) % 12345;
}

typedef struct{ char *city; float total; uint32_t hash; } city_record; 
city_record cheapest_products_city(){
	char *currentChar = input;

	while((currentChar - input + 1) < inputCount){
		char *currentCity = currentChar;
		while(*currentChar++ != ',');
		int currentCityLength = currentChar - currentCity - 1;

		char *currentProduct = currentChar;
		while(*currentChar++ != ',');
		int currentProductLength = currentChar - currentProduct - 1;

		char digits[4];
		digits[0] = *currentChar++;
		if(*currentChar == '.'){
			digits[1] = digits[0];
			digits[0] = '0';
		}
		else
			digits[1] = *currentChar++;

		digits[2] = *++currentChar;
		digits[3] = *++currentChar == '\n'? '0': *currentChar++;
		currentChar++;
		
		float currentPrice = to_float(digits);
		uint32_t cityHash = cities_perf_hash(currentCity, currentCityLength);
		uint32_t productHash = products_perf_hash(currentProduct, currentProductLength);
		uint32_t priceIndex = cityHash*productsHashesMax + productHash;
		float currentLowestPrice = hashmap[priceIndex];

		if(currentPrice < currentLowestPrice)
			hashmap[priceIndex] = currentPrice;
	}

	char *lowestCity;
	uint32_t lowestCityHash;
	float min = FLT_MAX;
	for(int x=0;x<citiesCount;x++){
		float sum = 0;
		char *city = cities[x];
		uint32_t cityHash = cities_perf_hash(city, strlen(city));
		for(int y=0;y<productsCount;y++){
			char *product = products[y];
			uint32_t productHash = products_perf_hash(product, strlen(product));
			float price = hashmap[cityHash*productsHashesMax + productHash];
			if(price != FLT_MAX)
				sum += price;
		}

		printf("%s : %f %f\n", city, sum, min);
		if(sum != 0.0f && sum < min){
			min = sum;
			lowestCity = city;
			lowestCityHash = cityHash;
		}
	}
	return (city_record){ lowestCity, min, lowestCityHash};
}

void init_hashmap(){
	size_t hashmapSize = CITIES_HASHES*PRODUCTS_HASHES*sizeof(float);
	hashmap = (float *) malloc(hashmapSize);
	for(int x=0;x<hashmapSize/sizeof(float);x++)
		hashmap[x] = FLT_MAX;

	uint16_t min = -1, max = 0;
	for(int x=0; x<citiesCount; x++){
		char *c = cities[x];
		uint32_t hash = cities_perf_hash(c, strlen(c));
		if(hash < min) min = hash;
	}
	citiesHashesMin = min;

	min = -1;
	for(int x=0; x<productsCount; x++){
		char *c = products[x];
		uint32_t hash = products_perf_hash(c, strlen(c));
		if(hash < min) min = hash;
		else if(hash > max) max = hash;
	}
	productsHashesMax = max;
	productsHashesMin = min;
}

void selection_sort_products(uint32_t cityHash){
	int minIndex; 
	for(int x=0; x<productsCount-1; x++){ 
		minIndex = x; 
		for(int y=x+1; y<productsCount; y++){
			char *product = products[y];
			char *currentMinProduct = products[minIndex];
			float price = hashmap[cityHash*productsHashesMax + products_perf_hash(product, strlen(product))];
			float currentMinPrice = hashmap[cityHash*productsHashesMax + products_perf_hash(currentMinProduct, strlen(currentMinProduct))];

			if(price < currentMinPrice) minIndex = y; 
		}
  
		char *tmp = products[minIndex];
		products[minIndex] = products[x]; 
		products[x] = tmp;
	}
}

void test(){
	for(int x=0;x<citiesCount;x++){
		char *city = cities[x];
		uint32_t cityHash = cities_perf_hash(city, strlen(city));
		for(int y=x+1;y<citiesCount;y++){
			char *city2 = cities[y];
			uint32_t cityHash2 = cities_perf_hash(city2, strlen(city2));
			if(cityHash == cityHash2)
				printf("clash: %s %d %s %d\n", city, cityHash, city2, cityHash2);
		}
	}
	for(int x=0; x<citiesCount; x++){
		char *city = cities[x];
		uint32_t cityHash = cities_perf_hash(city, strlen(city));
		printf("%s : \n", city);
		for(int y=0; y<productsCount; y++){
			char *product = products[y];
			uint32_t productHash = products_perf_hash(product, strlen(product));
			size_t priceIndex = cityHash*productsHashesMax + productHash;
			float price = hashmap[priceIndex];
			printf("\t%s : %.2f\n", product, price == FLT_MAX? 0.0f: price);
		}
		printf("\n");
	}
}

int main(){

	slurp_file();
	init_hashmap();

	struct timespec init, final;
	clock_gettime(CLOCK_REALTIME, &init);
	city_record lowestCity = cheapest_products_city();
	clock_gettime(CLOCK_REALTIME, &final);

	size_t elapsed = ((size_t)final.tv_sec - (size_t)init.tv_sec) + ((size_t)final.tv_nsec - (size_t)init.tv_nsec);
	printf("time took: %luns = %fms\n", elapsed, (double)elapsed*1e-6);

	selection_sort_products(lowestCity.hash);
	
	printf("%s %.2f\n", lowestCity.city, lowestCity.total);
	for(int y=0; y<5; y++){
		char *product = products[y];
		uint32_t productHash = products_perf_hash(product, strlen(product));
		size_t priceIndex = lowestCity.hash*productsHashesMax + productHash;
		float price = hashmap[priceIndex];
		if(price != FLT_MAX)
			printf("%s %.2f\n", product, price);
	}
	
	return 0;
}
