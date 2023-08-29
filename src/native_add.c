#include "native_add.h"
#include "gost89.c"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// A very short-lived native function.
//
// For very short-lived functions, it is fine to call them on the main isolate.
// They will block the Dart execution while running the native function, so
// only do this for native functions which are guaranteed to be short-lived.
FFI_PLUGIN_EXPORT intptr_t sum(intptr_t a, intptr_t b) {
  printf("Hello World!");
  return 2003;
}
FFI_PLUGIN_EXPORT int get_age(int a, int b) { return -1; }


FFI_PLUGIN_EXPORT char* get_name(int a, int b) {
     return "Temur Xoldarov";
}

char* caesarEncrypt(const char *input, int key) {
    int len = strlen(input);
    char *encrypted = (char*)malloc(len + 1);  // +1 for the null terminator

    for (int i = 0; i < len; i++) {
        if (input[i] >= 'a' && input[i] <= 'z') {
            encrypted[i] = 'a' + (input[i] - 'a' + key) % 26;
        } else if (input[i] >= 'A' && input[i] <= 'Z') {
            encrypted[i] = 'A' + (input[i] - 'A' + key) % 26;
        } else {
            encrypted[i] = input[i];  // Keep non-alphabetic characters unchanged
        }
    }

    encrypted[len] = '\0';  // Null-terminate the encrypted string
    return encrypted;
}


char* concatStrings(const char *str1, const char *str2) {
    size_t len1 = strlen(str1);
    size_t len2 = strlen(str2);

    char *result = (char*)malloc(len1 + len2 + 1); // +1 for null terminator

    if (result) {
        strcpy(result, str1);
        strcat(result, str2);
    }

    return result;
}

FFI_PLUGIN_EXPORT char* encrypt_string(char* string) {
   const char *input = "Hello, C!";
   int key = 3;
   gost_file();
   return concatStrings(caesarEncrypt(input, key),string);
}

// A longer-lived native function, which occupies the thread calling it.
//
// Do not call these kind of native functions in the main isolate. They will
// block Dart execution. This will cause dropped frames in Flutter applications.
// Instead, call these native functions on a separate isolate.
FFI_PLUGIN_EXPORT intptr_t sum_long_running(intptr_t a, intptr_t b) {
  // Simulate work.
#if _WIN32
  Sleep(5000);
#else
  usleep(5000 * 1000);
#endif
  return a + b;
}
