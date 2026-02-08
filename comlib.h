#ifndef COMPY_STDLIB_H
#define COMPY_STDLIB_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

// Simple integer power (base^exp)
int pow_int(int base, int exp) {
    int result = 1;
    for (int i = 0; i < exp; i++) {
        result *= base;
    }
    return result;
}

// Square root for float
float sqrt_flt(float x) {
    return sqrtf(x);
}

// Absolute value for int
int abs_int(int x) {
    return x < 0 ? -x : x;
}

// String length
int len_str(const char* s) {
    return strlen(s);
}

// Concatenate two strings (returns newly allocated string)
char* concat(const char* a, const char* b) {
    char* result = malloc(strlen(a) + strlen(b) + 1);
    strcpy(result, a);
    strcat(result, b);
    return result;
}

// Extract substring (returns newly allocated string)
char* substr(const char* s, int start, int len) {
    char* result = malloc(len + 1);
    strncpy(result, s + start, len);
    result[len] = '\0';
    return result;
}

// Initialize random seed using current time
void seed_rand() {
    srand((unsigned int)time(NULL));
}

// Random integer in range [min, max] inclusive
int rand_int(int min, int max) {
    return min + rand() % (max - min + 1);
}

// Random float in range [min, max]
float rand_flt(float min, float max) {
    float scale = rand() / (float)RAND_MAX;
    return min + scale * (max - min);
}

// Read string from user with optional prompt
void input_str(char* buf, int maxlen, const char* prompt) {
    if (prompt) {
        printf("%s", prompt);
    }
    fgets(buf, maxlen, stdin);
    buf[strcspn(buf, "\n")] = '\0';
}

// Read integer from user with optional prompt
int input_int(const char* prompt) {
    if (prompt) {
        printf("%s", prompt);
    }
    int value;
    scanf("%d", &value);
    while (getchar() != '\n');  // clear input buffer
    return value;
}

// Read float from user with optional prompt
float input_flt(const char* prompt) {
    if (prompt) {
        printf("%s", prompt);
    }
    float value;
    scanf("%f", &value);
    while (getchar() != '\n');  // clear input buffer
    return value;
}

// Write string content to file (returns 1 on success, 0 on failure)
int write_file(const char* path, const char* content) {
    FILE* file = fopen(path, "w");
    if (!file) {
        return 0;
    }
    fprintf(file, "%s", content);
    fclose(file);
    return 1;
}

// Read entire file into newly allocated string (returns NULL on failure)
char* read_file(const char* path) {
    FILE* file = fopen(path, "r");
    if (!file) {
        return NULL;
    }

    fseek(file, 0, SEEK_END);
    long size = ftell(file);
    fseek(file, 0, SEEK_SET);

    char* buffer = malloc(size + 1);
    fread(buffer, 1, size, file);
    buffer[size] = '\0';

    fclose(file);
    return buffer;
}

#endif