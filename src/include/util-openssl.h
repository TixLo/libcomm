#ifndef __UTIL_OPENSSL_H__
#define __UTIL_OPENSSL_H__

#include <iostream>

class UtilOpenssl{
public:
    static char* Base64Encode(char *input, int input_len);

    static void Base64Decode(char *input, char **decoded_bytes, int *decoded_len);

    static bool AesEncrypt(unsigned char *key, 
                           unsigned char *plaintext,
                           int plaintext_len, 
                           unsigned char **ciphertext, 
                           int *ciphertext_len);

    static bool AesDecrypt(unsigned char *key, 
                           unsigned char *ciphertext,
                           int ciphertext_len, 
                           unsigned char **plaintext, 
                           int *plaintext_len);
    
    static char* Hash(void* input, unsigned long length);
};

#endif//__UTIL_OPENSSL_H__