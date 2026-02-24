#include <assert.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/evp.h>
#include <openssl/err.h>
#include <openssl/provider.h>

void handle_errors()
{
	ERR_print_errors_fp(stderr);
	abort();
}

int encrypt(unsigned char *pt, int pt_len, unsigned char *key, unsigned char *iv, unsigned char *ct)
{
	EVP_CIPHER_CTX *ctx;
	int len;
	int ct_len;

	if (!(ctx = EVP_CIPHER_CTX_new()))
		handle_errors();

	if (1 != EVP_EncryptInit_ex(ctx, EVP_des_cbc(), NULL, key, iv))
		handle_errors();

	if (1 != EVP_EncryptUpdate(ctx, ct, &len, pt, pt_len))
		handle_errors();

	ct_len = len;

	if (1 != EVP_EncryptFinal_ex(ctx, ct + len, &len))
		handle_errors();

	ct_len += len;
	
	EVP_CIPHER_CTX_free(ctx);

	return ct_len;
}

int decrypt(unsigned char *ct, int ct_len, unsigned char *key, unsigned char *iv, unsigned char *pt)
{
	EVP_CIPHER_CTX *ctx;
	int len;
	int pt_len;

	if (!(ctx = EVP_CIPHER_CTX_new()))
		handle_errors();

	if (1 != EVP_DecryptInit_ex(ctx, EVP_des_cbc(), NULL, key, iv))
		handle_errors();

	if (1 != EVP_DecryptUpdate(ctx, pt, &len, ct, ct_len))
		handle_errors();

	pt_len = len;

	if (1 != EVP_DecryptFinal_ex(ctx, pt + len, &len))
		handle_errors();

	pt_len += len;
	
	EVP_CIPHER_CTX_free(ctx);

	return pt_len;
}

void read_random(void *addr, size_t size)
{
	FILE *fp;

	fp = fopen("/dev/urandom", "r");
	if (!fp)
		exit(EXIT_FAILURE);

	fread(addr, 1, size, fp);
}

int main(int argc, char *argv[])
{
	unsigned char key[8];
	unsigned char iv[8];
	unsigned char pt[128];
	unsigned char ct[128];
	unsigned char decrypted[128];
	int ct_len, dec_len;
	OSSL_PROVIDER *legacy_provider;
	OSSL_PROVIDER *default_provider;

	if (!(legacy_provider = OSSL_PROVIDER_load(NULL, "legacy")))
		exit(EXIT_FAILURE);
	if (!(default_provider = OSSL_PROVIDER_load(NULL, "default")))
		exit(EXIT_FAILURE);

	read_random(key, sizeof(key));
	read_random(iv, sizeof(iv));
	printf("[PLAINTEXT] ");
	fflush(stdout);
	scanf("%127s", pt);

	ct_len = encrypt(pt, strlen((char *)pt), key, iv, ct);

	printf("[CIPHERTEXT] ");
	for (int i = 0 ; i < ct_len ; i++) {
		printf("%02x", ct[i]);
	}
	printf("\n");

	dec_len = decrypt(ct, ct_len, key, iv, decrypted);

	printf("[DECRYPTED] \"%s\"\n", decrypted);

	assert(memcmp(pt, decrypted, dec_len) == 0);
	puts("[+] SUCCESS");

	OSSL_PROVIDER_unload(legacy_provider);
	OSSL_PROVIDER_unload(default_provider);

	return EXIT_SUCCESS;
}
