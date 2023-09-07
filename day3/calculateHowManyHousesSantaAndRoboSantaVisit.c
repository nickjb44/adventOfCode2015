#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int x;
    int y;
} House;

typedef struct {
    House * data;
    size_t size;
    size_t capacity;
} Set;

int isSameHouse(House *house1, House *house2) {
    return house1->x == house2->x && house1->y == house2->y;
}

Set* set_init(size_t capacity) {
    Set* set = malloc(sizeof(Set));
    set->data = malloc(capacity * sizeof(House));
    set->size = 0;
    set->capacity = capacity;
    return set;
}

int set_contains(Set *set, House *house) {
    // NOTE: this is not a proper set in that it searches in O(N) time
    // by checking every element. This is fine for our here but a bit
    // of a lie to call it a set...
    // I'd need a hashing algorithm to make it a proper set. and I'm too lazy
    for (int i = 0; i < set->size; i++) {
        if (isSameHouse(&set->data[i], house)) {
            return 1;
        }
    }
    return 0;
}

void set_add(Set *set, House *house) {
    if (set->size == set->capacity) {
        set->capacity *= 2;
        set->data = realloc(set->data, set->capacity * sizeof(House));
    }
    // this line will add the value even if it already exists
    // so we'll need to check set_contains first
    set->data[set->size++] = *house;
}

void set_free(Set *set) {
    free(set->data);
    free(set);
}


bool hasVisitedHouse(Set *set, House *house) {
    return set_contains(set, house);
}

int main() {
    int housesVisited = 1;
    int santaX = 0;
    int santaY = 0;
    int roboX = 0;
    int roboY = 0;
    Set *houses = set_init(100);
    House *house;
    house = malloc(sizeof(House));
    bool isSantasTurn = true;


    house->x = santaX;
    house->y = santaY;
    set_add(houses, house);
    printf("starting at (%d, %d)\n", santaX, santaY);
    printf("Santa has visited %d houses\n", housesVisited);
    printf("-----");


    FILE *file = fopen("input.txt", "r");
    if (file == NULL) {
        printf("Error opening file!\n");
        return 1;
    }
    char buffer[256];
    while( fgets(buffer, sizeof(buffer), file) != NULL) {
        for (size_t i = 0; i < strlen(buffer); i++) {
            if (buffer[i] == '^') {
                if (isSantasTurn) {
                    santaY++;
                } else {
                    roboY++;
                }
            } else if (buffer[i] == 'v') {
                if (isSantasTurn) {
                    santaY--;
                } else {
                    roboY--;
                }
            } else if (buffer[i] == '>') {
                if (isSantasTurn) {
                    santaX++;
                } else {
                    roboX++;
                }
            } else if (buffer[i] == '<') {
                if (isSantasTurn) {
                    santaX--;
                } else {
                    roboX--;
                }
            }

            if (isSantasTurn) {
                house->x = santaX;
                house->y = santaY;
            } else {
                house->x = roboX;
                house->y = roboY;
            }
            isSantasTurn = !isSantasTurn;

            // do nothing if you've already visited the house
            // otherwise add it to the set and increment housesVisited
            if (!hasVisitedHouse(houses, house)) {
                set_add(houses, house);
                housesVisited++;
            }
        }
    }
    fclose(file);
    printf("Santa and robo visited %d houses\n", housesVisited);
    return 0;
}
