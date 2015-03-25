#include "util-openssl.h"
#include <openssl/sha.h>
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