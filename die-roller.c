#include <stdlib.h>
#include <stdio.h>
#include <time.h>

int main(int argc, char* argv[]) {
    // Initialize random number generator
    srand((unsigned)time(NULL));
    
    // Generate random number between 1 and 6
    int rand_num = (rand() % 6) + 1;
    
    // Print number to screen
    printf("%d\n", rand_num);
    
    return 0;
}