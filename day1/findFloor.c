#include <stdio.h>
#include <string.h>

int main() {
    // read input from text file
    // for each input increment floor according to ( or )
    // print floor
    int floor = 0;
    FILE *file = fopen("input.txt", "r");
    if (file == NULL){ 
        printf("Error Reading File\n"); 
        return 1; 
    }
    char buffer[256];
    while (fgets(buffer, 256, file) != NULL) {
        for (size_t i = 0; i< strlen(buffer); i++) {
            if (buffer[i] == '(') {
                floor++;
            } else if (buffer[i] == ')') {
                floor--;
            }
        }
    }
    fclose(file);
    printf("Floor: %d\n", floor);
    return 0;
}
