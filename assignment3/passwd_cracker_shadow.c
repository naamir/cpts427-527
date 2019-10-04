#include <crypt.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

#define SHDW_LINE_LEN 256
#define WORD_LEN 80

int uid_i = 0;
int salt_i = 0;
int hash_i = 0;
char *salt_arr[20];
char salt_ch_arr[512];
char *hash_arr[20];
char hash_ch_arr[2048];
char *uid_arr[20];
char uid_ch_arr[512];

char *hash;

int tokenize(char *arr, char *type)
{
    int i = 0;
    char *s;

    //strcpy(temp, arr);
    s = strtok(arr, "$");
    while (s != NULL)
	{
        if (strcmp(type, "salt") == 0) salt_arr[i] = s;
		if (strcmp(type, "hash") == 0) hash_arr[i] = s;
		if (strcmp(type, "uid") == 0) uid_arr[i] = s;
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
			strcat(uid_ch_arr, token);
			strcat(uid_ch_arr, "$");
			printf("  uid: %s\n", token);
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

	salt_i = tokenize(salt_ch_arr, "salt");
	hash_i = tokenize(hash_ch_arr, "hash");
	uid_i = tokenize(uid_ch_arr, "uid");
	for (int i=0; i < uid_i; i++)
	{
		printf("uid %i %s ", i, uid_arr[i]);
		printf("salt %s ", salt_arr[i]);
		printf("hash %s\n", hash_arr[i]);
	}

	char word[WORD_LEN];
	char salt[WORD_LEN];
	char full_hash[2048];

	strcpy(salt, "$6$");
	while(fgets(word, WORD_LEN, dict)!=NULL){
		word[strlen(word)-1] = '\0';
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
		for (int n=0; n < num_accounts; n++)
		{
			strcat(salt, salt_arr[n]);
			hash = crypt(word, salt);
			strcpy(full_hash, salt);
			strcat(full_hash, "$");
			strcat(full_hash, hash_arr[n]);

			
			
			if (strcmp(hash, full_hash) == 0)
			{
				printf("match found! For uid %s\n", uid_arr[n]);
				printf("word: %s hash   : %s\n ourhash: %s\n", word, hash, full_hash);
				//getchar();
			}
			strcpy(salt, "$6$"); // clear
		}
		
	}
}
