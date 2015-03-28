#include "util-openssl.h"
#include <openssl/sha.h>
#include <openssl/aes.h> 
#include <openssl/hmac.h>
#include <openssl/evp.h>
#include <openssl/bio.h>
#include <openssl/buffer.h>
#include <string.h>
#include <stdlib.h>

using namespace std;
///////////////////////////////////////////////////////////////
// private
///////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////
// public
///////////////////////////////////////////////////////////////
void UtilOpenssl::Base64Decode(char *input, char **decoded_bytes, int *decoded_len){
    BIO *bioMem, *b64;
    ssize_t buffer_length;

    bioMem = BIO_new_mem_buf((void *)input, -1);
    b64 = BIO_new(BIO_f_base64());
    BIO_set_flags(b64, BIO_FLAGS_BASE64_NO_NL);
    bioMem = BIO_push(b64, bioMem);

    buffer_length = BIO_get_mem_data(bioMem, NULL);
    *decoded_bytes = new char[buffer_length + 1];
    memset(*decoded_bytes, 0 , buffer_length + 1);
    *decoded_len = BIO_read(bioMem, *decoded_bytes, buffer_length);
    BIO_free_all(bioMem);
}

char* UtilOpenssl::Base64Encode(char *input, int input_len){
    int x;
    BIO *bioMem, *b64;
    BUF_MEM *bufPtr;
    char *buff;

    b64 = BIO_new(BIO_f_base64());
    BIO_set_flags(b64, BIO_FLAGS_BASE64_NO_NL);
    bioMem = BIO_new(BIO_s_mem());
    b64 = BIO_push(b64, bioMem);
    
    BIO_write(b64, input, input_len);
    x = BIO_flush(b64);
    if(x < 1) {
        BIO_free_all(b64);
        return NULL;
    }
    
    BIO_get_mem_ptr(b64, &bufPtr);

    buff = new char[bufPtr->length+1];
    memcpy(buff, bufPtr->data, bufPtr->length);
    buff[bufPtr->length] = 0;

    BIO_free_all(b64);
    return buff;
}

char* UtilOpenssl::Hash(void* input, unsigned long length){
    unsigned char md[SHA256_DIGEST_LENGTH+1] = {0};

    SHA256_CTX context;
    if(!SHA256_Init(&context))
        return NULL;

    if(!SHA256_Update(&context, (unsigned char*)input, length))
        return NULL;

    if(!SHA256_Final(md, &context))
        return NULL;

    return UtilOpenssl::Base64Encode((char*)md, SHA256_DIGEST_LENGTH);
}

bool UtilOpenssl::AesEncrypt(unsigned char *key, 
                             unsigned char *plaintext,
                             int plaintext_len, 
                             unsigned char **ciphertext, 
                             int *ciphertext_len){
    if (!key || !plaintext || !ciphertext){
        return false;
    }

    *ciphertext = NULL;
    *ciphertext_len = 0;

    AES_KEY aes;
    if(AES_set_encrypt_key((unsigned char*)key, 128, &aes) < 0){
        return false;
    }

    int enc_buf_len = ((plaintext_len / AES_BLOCK_SIZE) + 1) * AES_BLOCK_SIZE;

    unsigned char *enc_out = (unsigned char*)calloc(enc_buf_len, 1);
    if (!enc_out){
        return false;
    }

    unsigned char *in = plaintext;
    unsigned char *out = enc_out;
    int enc_len = 0;
    while(enc_len < plaintext_len){
        AES_encrypt((unsigned char*)in, (unsigned char*)out, &aes);
        in += AES_BLOCK_SIZE;
        out += AES_BLOCK_SIZE;
        enc_len += AES_BLOCK_SIZE;
    }

    *ciphertext = enc_out;
    *ciphertext_len = enc_len;
    return true;
}

bool UtilOpenssl::AesDecrypt(unsigned char *key, 
                             unsigned char *ciphertext,
                             int ciphertext_len, 
                             unsigned char **plaintext, 
                             int *plaintext_len){
    if (!key || !plaintext || !ciphertext){
        return false;
    }

    *plaintext = NULL;
    *plaintext_len = 0;

    AES_KEY aes;
    if(AES_set_decrypt_key((unsigned char*)key, 128, &aes) < 0){
        return false;
    }

    int dec_buf_len = ((ciphertext_len / AES_BLOCK_SIZE) + 1) * AES_BLOCK_SIZE;

    unsigned char *dec_out = (unsigned char*)calloc(dec_buf_len, 1);
    if (!dec_out){
        return false;
    }

    unsigned char *in = ciphertext;
    unsigned char *out = dec_out;
    int dec_len=0;
    while(dec_len < ciphertext_len){
        AES_decrypt((unsigned char*)in, (unsigned char*)out, &aes);
        in+=AES_BLOCK_SIZE;
        out+=AES_BLOCK_SIZE;
        dec_len += AES_BLOCK_SIZE;
    }

    *plaintext = dec_out;
    *plaintext_len = dec_len;
    return true;
}