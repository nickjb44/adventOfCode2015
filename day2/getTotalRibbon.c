#include <stdio.h>

int calculatePaperFromDimensions(int l, int w, int h) {
    return 2*l*w + 2*w*h + 2*h*l;
}

int calculatePerimeter(int a, int b){
    return 2*a + 2*b;
}

int calculateRibbonForBow(int l, int w, int h) {
    return l*w*h;
}

int calculateRibbonToWrap(int l, int w, int h) {
    int perimeterA = calculatePerimeter(l, w);
    int perimeterB = calculatePerimeter(w, h);
    int perimeterC = calculatePerimeter(h, l);

    int perimeters[3] = {perimeterA, perimeterB, perimeterC};
    int smallestPerimeter = perimeters[0];
    for (int i = 1; i < 3; i++) {
        if (perimeters[i] < smallestPerimeter) {
            smallestPerimeter = perimeters[i];
        }
    }

    return smallestPerimeter;
}

int main(){
    // declare variable
    int length;
    int width;
    int height;
    int totalRibbon = 0;
    int ribbonToWrap;
    int ribbonForBow;

    // read input
    FILE *file = fopen("input1.txt", "r");
    while(fscanf(file, "%dx%dx%d\n", &length, &width, &height) == 3) {
        ribbonToWrap = calculateRibbonToWrap(length, width, height);
        ribbonForBow = calculateRibbonForBow(length, width, height);
        totalRibbon += ribbonToWrap + ribbonForBow;
    }
    fclose(file);
    printf("Total ribbon: %d\n", totalRibbon);
    return 0;
}
