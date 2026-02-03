#include <stdio.h>
#include <string.h>

#define LEN 0x100

__attribute__((constructor)) static void init(void)
{
	setvbuf(stdin, NULL, _IONBF, 0);
	setvbuf(stdout, NULL, _IONBF, 0);
	setvbuf(stderr, NULL, _IONBF, 0);
}

#define ALPHABETS_LEN 26

/*
 * Modifies pt itself
 */
void vigenere_cipher(char *pt, char *key)
{
	int len_pt, len_key;
	int base_pt, base_key;
	char c;

	len_pt = strlen(pt);
	len_key = strlen(key);
	for (int i = 0 ; i < len_pt ; i++) {
		c = pt[i];
		if ('a' <= c && c <= 'z')
			base_pt = 'a';
		else if ('A' <= c && c <= 'Z')
			base_pt = 'A';
		else
			continue;

		c = key[i % len_key];
		if ('a' <= c && c <= 'z')
			base_key = 'a';
		else if ('A' <= c && c <= 'Z')
			base_key = 'A';
		else
			continue;

		pt[i] = base_pt + ((pt[i] - base_pt) + (key[i % len_key] - base_key)) % ALPHABETS_LEN;
	}
}

void vigenere(void)
{
	char pt[LEN];
	char key[LEN];

	puts("[[ VIGENERE CIPHER ]]");
	printf("plaintext: ");
	fgets(pt, sizeof(pt), stdin);
	pt[strcspn(pt, "\n")] = '\0';
	pt[strcspn(pt, " ")] = '\0';
	printf("key: ");
	fgets(key, sizeof(key), stdin);
	key[strcspn(key, "\n")] = '\0';
	key[strcspn(key, " ")] = '\0';
	vigenere_cipher(pt, key);
	printf("ciphertext: \"%s\"\n", pt);
}

/*
 * Modifies pt itself
 */
void caesar_cipher(char *pt, int key)
{
	int len, base;
	char c;

	len = strlen(pt);
	for (int i = 0 ; i < len ; i++) {
		c = pt[i];
		if ('a' <= c && c <= 'z')
			base = 'a';
		else if ('A' <= c && c <= 'Z')
			base = 'A';
		else
			continue;
		pt[i] = base + ((c - base + key) % ALPHABETS_LEN);
	}
}

void caesar(void)
{
	char pt[LEN];
	int key;

	puts("[[ CAESAR CIPHER ]]");
	printf("plaintext: ");
	fgets(pt, sizeof(pt), stdin);
	pt[strcspn(pt, "\n")] = '\0';
	pt[strcspn(pt, " ")] = '\0';
	printf("key/shift: ");
	scanf("%d", &key);
	caesar_cipher(pt, key);
	printf("ciphertext: \"%s\"\n", pt);
}
