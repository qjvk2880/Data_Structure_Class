#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define HASH_PRIME 11117
#define NUMBER_OF_WORDS 5757

char words[5757][5]; 
// 2-D array for store words
int numberOfNodesInChain[HASH_PRIME] = {0,}; 

int hash(char key[5]) {
  int i;
  long long x;
  x = 0;
  
  for (i = 0; i < 4; i++) {
    x = x + key[i];
    x = x << 8;
  }
  
  x = x + key[4];
  return x % HASH_PRIME;
}

int makeHashTable(){
  int hashValue;
  int numberOfCollisions = 0;
  
  for(int i =0; i < NUMBER_OF_WORDS; i++){
    
    hashValue = hash(words[i]);
    
    numberOfNodesInChain[hashValue]++;
    
  }
}

void putWordsInArray() {
  FILE *fp = fopen("words.dat", "r");
  char line[100];
  
  for(int i=0; i<4;i++){
    fgets(line, sizeof(line), fp); // ignore first 4 lines.
  }
  
  for(int i=0; i<NUMBER_OF_WORDS;i++){
    fgets(line, sizeof(line), fp);
    strncpy(words[i],line,5); // put first 5 characters in words array
  }
}

int countKeyComparisons(){
  int totalKeyComparisons = 0;
  
  for(int i = 0; i < HASH_PRIME; i++){
    int keyComparisonsInChain = 0;
    
    int n = numberOfNodesInChain[i];
    keyComparisonsInChain += (n*(n+1))/2;
    
    totalKeyComparisons += keyComparisonsInChain;
  }
  return totalKeyComparisons;
}

int main(void) {
  putWordsInArray();
  makeHashTable();
  printf("%d",countKeyComparisons());
  return 0;
}