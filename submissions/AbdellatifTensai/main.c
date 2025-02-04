#include <stdio.h>
#include <stdint.h>
#include <assert.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <float.h>

#define PRODUCTS_HASH_MAX 139
#define CITIES_HASH_MAX 306

//removed duplicated names: Cantaloupe, Cranberry, Coconut, Honeydew, Pomegranate, Artichoke.
char *products[94] = {
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
const int productsCount = 94;

char *cities[101] = {
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
const int citiesCount = 101;

static char *input;
static int inputCount;
static uint16_t hashmap[CITIES_HASH_MAX*PRODUCTS_HASH_MAX];
static uint64_t citiesTotalPrices[CITIES_HASH_MAX];

void slurp_file(){
	FILE *file = fopen("input.txt", "rb");
	assert(file && "failed to open input.txt");
	fseek(file, 0, SEEK_END);
	size_t inputSize = ftell(file);
	rewind(file);

	input = (char *)malloc(inputSize);
	inputCount = inputSize;
	fread(input, sizeof(*input), inputSize, file);
	fclose(file);
}

uint16_t to_fixed_point(char digits[4]) {
	return (digits[0] - '0')*1000 + (digits[1] - '0')*100 + (digits[2] - '0')*10 + (digits[3] - '0');
}

//generated by gperf
uint32_t products_perf_hash(char *str, size_t len){
	static unsigned char asso_values[] = {
		140, 140, 140, 140, 140, 140, 140, 140, 140, 140, 140, 140, 140, 140, 140, 140, 140, 140, 140, 140, 140, 140, 140, 140, 140, 140, 140, 140, 140, 140, 140, 140, 140, 140, 140, 140, 140, 140, 140, 140, 140, 140, 140, 140, 140, 140, 140, 140, 140, 140, 140, 140, 140, 140, 140, 140, 140, 140, 140, 140, 140, 140, 140, 140, 140,  40,  40,   0,  75,   0,   0,  15,  20, 140,  55,  50,  20,  30,  35,  95,   0, 140,  10,  25,  65, 140, 140,  20, 140,   5,   5, 140, 140, 140, 140, 140, 140,   0,   0,  65, 60,   0, 140,  65,  40,   5,  10,   0,  30,  50,   5,   0,  30, 140,   5,  20,   0,   0, 140,  55, 140,  20, 140, 140, 140, 140, 140, 140, 140, 140, 140, 140, 140, 140, 140, 140, 140, 140, 140, 140, 140, 140, 140, 140, 140, 140, 140, 140, 140, 140, 140, 140, 140, 140, 140, 140, 140, 140, 140, 140, 140, 140, 140, 140, 140, 140, 140, 140, 140, 140, 140, 140, 140, 140, 140, 140, 140, 140, 140, 140, 140, 140, 140, 140, 140, 140, 140, 140, 140, 140, 140, 140, 140, 140, 140, 140, 140, 140, 140, 140, 140, 140, 140, 140, 140, 140, 140, 140, 140, 140, 140, 140, 140, 140, 140, 140, 140, 140, 140, 140, 140, 140, 140, 140, 140, 140, 140, 140, 140, 140, 140, 140, 140, 140, 140, 140, 140, 140, 140, 140, 140, 140, 140, 140, 140, 140, 140, 140, 140, 140, 140, 140, 140, 140, 140, 140
	};     
	return len + asso_values[(unsigned char)str[2]] + asso_values[(unsigned char)str[0]] + asso_values[(unsigned char)str[len - 1]];
}


uint32_t cities_perf_hash(char *str, size_t len){
  static unsigned short asso_values[] = {
    307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 105,  50, 307,  25, 307, 307, 307,  65, 307,  35,   5,   0,   5, 307, 307, 307, 307,  25, 307,  25, 307, 307, 307, 307, 307, 307, 307, 307, 307,  65,   0,   0,  40,  95,  30,   5,  25, 120,   0,   5,  55,  70,  60,  30, 10,  15,   5,  10,   0,  20,  30,   0,  60, 307, 307,  10,  20,   0, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307,   0, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307,  15, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307, 307
  };

  uint32_t hval = len;
  switch (hval){
      default: hval += asso_values[(unsigned char)str[5]];
      case 5: hval += asso_values[(unsigned char)str[4]+1];
      case 4:
      case 3: hval += asso_values[(unsigned char)str[2]];
      case 2: hval += asso_values[(unsigned char)str[1]]; break;
  }
  return hval;
}

//

void parse_fill_hashmap(){
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
		
		uint16_t currentPrice = to_fixed_point(digits);
		uint16_t cityHash = cities_perf_hash(currentCity, currentCityLength);
		uint16_t productHash = products_perf_hash(currentProduct, currentProductLength);
		uint16_t currentLowestPrice = hashmap[cityHash*PRODUCTS_HASH_MAX + productHash];

		citiesTotalPrices[cityHash] += currentPrice; 
		if(currentLowestPrice == 0 || currentPrice < currentLowestPrice)
			hashmap[cityHash*PRODUCTS_HASH_MAX + productHash] = currentPrice;
	}
}

uint64_t cheapest_city(char **out){
	char *lowestCity;
	uint64_t min = -1;
	for(int x=0;x<citiesCount;x++){
		char *city = cities[x];
		uint16_t cityHash = cities_perf_hash(city, strlen(city));
		uint64_t total = citiesTotalPrices[cityHash];
		//printf("%s : %f %f\n", city, sum, min);
		if(total && total < min){
			min = total;
			lowestCity = city;
		}
	}
	*out = lowestCity;
	return min;
}

void selection_sort_products(uint32_t cityHash){
	int minIndex; 
	for(int x=0; x<productsCount-1; x++){ 
		minIndex = x; 
		for(int y=x+1; y<productsCount; y++){
			char *product = products[y];
			char *currentMinProduct = products[minIndex];
			uint16_t price = hashmap[cityHash*PRODUCTS_HASH_MAX + products_perf_hash(product, strlen(product))];
			uint16_t currentMinPrice = hashmap[cityHash*PRODUCTS_HASH_MAX + products_perf_hash(currentMinProduct, strlen(currentMinProduct))];

			if(price < currentMinPrice) minIndex = y; 
		}
  
		char *tmp = products[minIndex];
		products[minIndex] = products[x]; 
		products[x] = tmp;
	}
}

int main(){
	struct timespec t0, t1;
	size_t elapsed[3];

	slurp_file();

	clock_gettime(CLOCK_REALTIME, &t0);
	parse_fill_hashmap();
	clock_gettime(CLOCK_REALTIME, &t1);
	elapsed[0] = ((size_t)t1.tv_sec - (size_t)t0.tv_sec) + ((size_t)t1.tv_nsec - (size_t)t0.tv_nsec);

	clock_gettime(CLOCK_REALTIME, &t0);
	char *cheapestCity;
	uint64_t cheapestCityTotal = cheapest_city(&cheapestCity);
	clock_gettime(CLOCK_REALTIME, &t1);
	elapsed[1] = ((size_t)t1.tv_sec - (size_t)t0.tv_sec) + ((size_t)t1.tv_nsec - (size_t)t0.tv_nsec);

	clock_gettime(CLOCK_REALTIME, &t0);
	uint16_t cheapestCityHash = cities_perf_hash(cheapestCity, strlen(cheapestCity));
	selection_sort_products(cheapestCityHash);
	clock_gettime(CLOCK_REALTIME, &t1);
	elapsed[2] = ((size_t)t1.tv_sec - (size_t)t0.tv_sec) + ((size_t)t1.tv_nsec - (size_t)t0.tv_nsec);
	
	printf("%s %lu.%.2lu\n", cheapestCity, cheapestCityTotal/100, cheapestCityTotal%100);
	for(int y=0, k=0; (k<5) && (y<productsCount); y++){
		char *product = products[y];
		uint16_t productHash = products_perf_hash(product, strlen(product));
		uint32_t price = hashmap[cheapestCityHash*PRODUCTS_HASH_MAX + productHash];
		if(price){
			printf("%s %lu.%.2lu\n", product, price/100, price%100);
			k++;
		}
	}

	printf("parsing csv: %luns = %fms\n", elapsed[0], (double)elapsed[0]*1e-6);
	printf("find cheapest city: %luns = %fms\n", elapsed[1], (double)elapsed[1]*1e-6);
	printf("sort products: %luns = %fms\n", elapsed[2], (double)elapsed[2]*1e-6);
	printf("total: %luns = %fms\n", elapsed[0] + elapsed[1] + elapsed[2], (double)(elapsed[0] + elapsed[1] + elapsed[2])*1e-6);
	
	return 0;
}
