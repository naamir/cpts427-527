#include <crypt.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

#define SHDW_LINE_LEN 256
#define WORD_LEN 80

int salt_i = 0;
int hash_i = 0;
char *salt_arr[20];
char salt_ch_arr[512];
char *hash_arr[20];
char hash_ch_arr[512];
char temp[512];

int tokenize_salt(char *arr)
{
    int i = 0;
    char *s;

    //strcpy(temp, arr);
    s = strtok(arr, "$");
    while (s != NULL)
	{
        salt_arr[i] = s;    // store pointer to token in *name[] array  
        s = strtok(0, "$");
        i++;
	}
    return i;
}

int tokenize_hash(char *arr)
{
    int i = 0;
    char *s;

    //strcpy(temp, arr);
    s = strtok(arr, "$");
    while (s != NULL)
	{
        hash_arr[i] = s;    // store pointer to token in *name[] array  
        s = strtok(0, "$");
        i++;
	}
    return i;
}

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
			//////////////////////
			// Part A: 
			//  These values need to 
			//  be stored in an array
			//////////////////////
			strcat(salt_ch_arr, token);
			strcat(salt_ch_arr, "$");
			printf("  salt: %s\n", token);
			token = strtok(NULL, "$");
			strcat(hash_ch_arr, token);
			strcat(hash_ch_arr, "$");
			printf("  hash: %s\n", token);
			num_accounts++;
		}
	}

	printf("all salts: %s\n", salt_ch_arr);
	printf("all hashes: %s\n", hash_ch_arr);

	salt_i = tokenize_salt(salt_ch_arr);
	for (int i=0; i < salt_i; i++)
		printf("salt token:%i %s\n", i, salt_arr[i]);
	hash_i = tokenize_hash(hash_ch_arr);
	for (int i=0; i < hash_i; i++)
		printf("hash token:%i %s\n", i, hash_arr[i]);
	

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
