	//nearest gram
	//2310P12P23P**
	//2 array entries 
		//3rd canister 10 grams
		//PAUSE
		//1st canister 2 grams 
		//PAUSE
		//2nd canister 3 grams
	//** end sequence  

#include <stdio.h>

struct ctrl_word{
	int arr_size;					//ingredients to print out 
	char canister[1];			//canister
	char ref_weight[1];		//reference weight
};
// char decode(char word) []{
// 	// printf("%c",word);
// 	return 0;
// };
char * decode(char *word){
	// printf("%s hi\n\n",word);
	return word;

};
int main(){

// struct ctrl_word ctrl_array[10];	//queue up to 10 items
// struct ctrl_word ctrl1;
char * ctrl1;
char ctrl_word [] = "2310P12P23P**";


	// assemble();
	// decode();
	printf("Hello, %s \n\n",ctrl_word);
	ctrl1 = decode(ctrl_word);
	printf("%s feedback", ctrl1);

	return 0;
};

int assemble(){
	return 0;
};

// ctrl_word decode(char word){
// char decode(char word){
// 	return word;
// };
// void decode(char *word){
// 	printf("%s",word);
// 	return;
// };