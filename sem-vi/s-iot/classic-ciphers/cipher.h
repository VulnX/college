#include <stdio.h>
#include <string.h>

#define LEN 0x100

__attribute__((constructor)) static void init(void)
{
	setvbuf(stdin, NULL, _IONBF, 0);
	setvbuf(stdout, NULL, _IONBF, 0);
	setvbuf(stderr, NULL, _IONBF, 0);
}

#define CAESAR_MOD 26

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
		pt[i] = base + ((c - base + key) % CAESAR_MOD);
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
