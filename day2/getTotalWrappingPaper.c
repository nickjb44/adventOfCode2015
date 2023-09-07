#include <stdio.h>

int calculatePaperFromDimensions(int l, int w, int h) {
    return 2*l*w + 2*w*h + 2*h*l;
}

int calculateSlackAmount(int l, int w, int h) {
    int smallestSide = l*w;
    if (w*h < smallestSide) {
        smallestSide = w*h;
    }
    if (h*l < smallestSide) {
        smallestSide = h*l;
    }
    return smallestSide;
}

int main(){
    // declare variable
    int length;
    int width;
    int height;
    int totalPaper = 0;
    int slack;

    // read input
    FILE *file = fopen("input1.txt", "r");
    while(fscanf(file, "%dx%dx%d\n", &length, &width, &height) == 3) {
        totalPaper += calculatePaperFromDimensions(length, width, height);
        slack = calculateSlackAmount(length, width, height);
        totalPaper += slack;
    }
    fclose(file);
    printf("Total paper: %d\n", totalPaper);
    return 0;
}
