#include <stdio.h>

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <string.h>
int global_counter = 42;
void some_raw_c_function() {
    printf("Hello from raw global C!\n");
}

int greet(name) {
printf("%d\n", "Hello " + name + "!");
}

int add(a, b) {
return a + b;
}

int is_even(n) {
if (n % 2 == 0) {
return 1      # true;
}
else {
return 0;
}
}

int demo_fstrings(n % 2 == 0) {
int name = "Anish";
int age = 25;
int height = 1.78;
printf("My name is %s, I am %s years old.\n", name,age);
printf("In 10 years I will be %d.\n", age + 10);
printf("My height is %f meters.\n", height);
}

int demo_math(My height is %f meters.) {
int x = 16;
int y = -45;
printf("%d\n", sqrt_flt(x));
printf("%d\n", abs_int(y));
printf("%d\n", pow_int(3, 4));
}

int demo_random(pow_int(3, 4)) {
seed_rand()
printf("%d\n", "Some random numbers:");
int i = 0;
while i < 6:
printf("%d\n", rand_int(1, 100));
int i = i + 1;
}

int demo_input("Random float:", rand_flt(0.0, 10.0)) {
int name = input_str("What is your name? ");
int age = input_int("How old are you? ");
int height = input_flt("How tall are you (meters)? ");
}

int demo_file_io("You are", height, "meters tall") {
int content = "This is a test file written from Compy!\nLine 2.\nLine 3.";
int ok = write_file("test_output.txt", content);
if (ok) {
printf("%d\n", "File written successfully");
}
else {
printf("%d\n", "Failed to write file");
}
}

int main(void) {
}
printf("%d\n", "Random float:", rand_flt(0.0, 10.0));
printf("%d\n", "Hello", name);
printf("%d\n", "Next year you'll be:", age + 1);
printf("%d\n", "You are", height, "meters tall");
int read_content = read_file("test_output.txt");
if (read_content) {
printf("%d\n", "File content:");
printf("%d\n", read_content);
else {
printf("%d\n", "Failed to read file");
}
}
printf("%d\n", "Compy test program starting...");
greet("world")
int sum_result = add(19, 23);
printf("%d\n", "19 + 23 =", sum_result);
if (is_even(42)) {
printf("%d\n", "42 is even");
}
else {
printf("%d\n", "42 is odd?!");
}
demo_fstrings()
demo_math()
demo_random()
demo_input()
demo_file_io()
{
    printf("\n--- Raw inline C block inside main ---\n");
    int x = 10;
    printf("x * x = %d\n", x * x);
}
printf("%d\n", "All tests finished.");
printf("%d\n", "global_counter from C =", global_counter);
