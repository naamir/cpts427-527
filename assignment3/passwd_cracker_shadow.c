#include <crypt.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

#define SHDW_LINE_LEN 256
#define WORD_LEN 80

int salt_i = 0;
char *salt_arr[50];
char *hash_array[50];

int main(){

	FILE *shadow;
	FILE *dict;
	

	shadow = fopen("shadow", "r");
	if(shadow == NULL){
		fprintf(stderr, "Cannot open shadow file \n");
		exit(1);
	}

	dict   = fopen("words.txt", "r");
	if(dict == NULL){
		fprintf(stderr, "Cannot open dict file\n");
		exit(1);
	}

	char shdw_line[SHDW_LINE_LEN];
	int num_accounts = 0;
	while(fgets(shdw_line, SHDW_LINE_LEN, shadow)!=NULL){
		char *token = strtok(shdw_line, ":");
		printf("ID: %s\n", token);
		char *shdw_hash = strtok(NULL, ":");
		if(strcmp(shdw_hash, "*")!=0 && strcmp(shdw_hash, "!")!=0){
			token = strtok(shdw_hash, "$");
			token = strtok(NULL, "$");
			salt_arr[salt_i] = token;
			printf("  salt %i: %s\n", salt_i, salt_arr[salt_i]);
			salt_i++;
			token = strtok(NULL, "$");
			printf("  hash: %s\n", token);
			num_accounts++;
			//////////////////////
			// Part A: 
			//  These values need to 
			//  be stored in an array
			//////////////////////
		}
	}
	for (int i = 0; i < salt_i; i++)
		printf("  salt: %s\n", salt_arr[salt_i]);

	char word[WORD_LEN];
	while(fgets(word, WORD_LEN, dict)!=NULL){
		for(int i=0; i<num_accounts; i++){
			//////////////////////
			// Part B: 
			//  For each account, compute
			//  the hash for that dictionary
			//  word and the users known salt
			//  as shown below:
			//     hash = crypt("password", "$6$_____");
			//  then check if the password is 
			//  the same as that users entry 
			//  from  /etc/shadow, if so
			//  you've successfully cracked it,
			//  print the password and userid
			//////////////////////
		}
	}
}
