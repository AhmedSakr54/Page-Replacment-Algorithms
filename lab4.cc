#include <iostream>
#include <bits/stdc++.h>
#include <unistd.h>
#include <string.h>

using namespace std;

int search(int * buffer, int numberOfElements, int searchedFor) {
    for (int i = 0; i < numberOfElements; i++) {
        if (buffer[i] == searchedFor) {
            return i;
        }
    }
    return -1;
}
void printBuffer(int * buffer, int numberOfElements) {
    for (int i = 0; i < numberOfElements; i++) {
        printf("%02d ", buffer[i]);
    }
    printf("\n");
}

void printHeader(char * method) {
    printf("Replacement Policy = %s", method);
    printf("-------------------------------------\n");
    printf("Page   Content of Frames\n");
    printf("----   -----------------\n");
}
void printFooter(int faultCount) {
    printf("-------------------------------------\n");
    printf("Number of page faults = %d\n", faultCount);
}
int longestNextRef(int * buffer, char buf[][50], int start, int n) {
    int numberOfRef = 0;
    int max = -12344;
    int maxIndex = -1;
    for (int i = 0; i < n; i++) {
        while (atoi(buf[start]) != -1) {
            
            if (buffer[i] == atoi(buf[start++])) {
                break;
            }
            numberOfRef++;
        }
        if (max < numberOfRef) {
            max = numberOfRef;
            maxIndex = i;
        }
        numberOfRef = 0;
    }
    return maxIndex;
}
void OPTIMAL(char buf[][50], int size) {
    int n = atoi(buf[0]);
    int buffer[n];
    printHeader(buf[1]);
    int i = 2;
    int faultCount = 0;
    int numberOfElements = 0;
    while (atoi(buf[i]) != -1) {
        int bufVal = atoi(buf[i]);
        printf("%02d", bufVal);
        int isHit = search(buffer, numberOfElements, bufVal);
        if (isHit == -1) {
            if (numberOfElements < n) {
                buffer[numberOfElements++] = bufVal;
                printf("     ");
            }
            else {
                int replaced = longestNextRef(buffer, buf, i, n);
                buffer[replaced] = bufVal;
                printf(" F   ");
                faultCount++;                
            }
        }
        else {
            printf("     ");
        }
        printBuffer(buffer, numberOfElements);
        i++;
    }
    printFooter(faultCount);
}

void CLOCK(char buf[][50]) {
    int n = atoi(buf[0]);
    int buffer[n];
    int secondChance[n];
    printHeader(buf[1]);
    int i = 2;
    int faultCount = 0;
    int numberOfElements = 0;
    int clockArm = 0;
    while (atoi(buf[i]) != -1) {
        int bufVal = atoi(buf[i]);
        printf("%02d", bufVal);
        int isHit = search(buffer, numberOfElements, bufVal);
        if (isHit == -1) {
            if (numberOfElements < n) {
                secondChance[numberOfElements] = 1;
                buffer[numberOfElements++] = bufVal;
                printf("     ");
            }
            else {
                if (secondChance[clockArm]) {
                    secondChance[clockArm] = 0;
                    clockArm = (clockArm+1) % n;
                    while (secondChance[clockArm]) {
                        secondChance[clockArm] = 0;
                        clockArm = (clockArm + 1) % n;
                    }
                }
                buffer[clockArm] = bufVal;
                secondChance[clockArm] = 1;
                printf(" F   ");
                faultCount++;
            }
            clockArm = (clockArm+1) % n;
        }
        else {
            secondChance[isHit] = 1;
            printf("     ");
        }
        printBuffer(buffer, numberOfElements);
        i++;
    }
    printFooter(faultCount);
}
void LRU(char buf[][50]) {
    int n = atoi(buf[0]);
    int buffer[n];
    queue<int> q;
    printHeader(buf[1]);
    int numberOfElements = 0;
    int i = 2;
    int faultCount = 0;
    while (atoi(buf[i]) != -1) {
        int bufVal = atoi(buf[i]);
        printf("%02d", bufVal);
        int isHit = search(buffer, numberOfElements, bufVal);
        if (isHit == -1) {
            if (numberOfElements < n) {
                q.push(numberOfElements);
                buffer[numberOfElements++] = bufVal;
                printf("     ");
            }
            else {
                int index = q.front();
                buffer[index] = bufVal;
                q.pop();
                q.push(index);
                printf(" F   ");
                faultCount++;
            }
        }
        else {
            q.pop();
            q.push(isHit);
            printf("     ");
        }
        printBuffer(buffer, numberOfElements);
        i++;
    }
    printFooter(faultCount);
}

void FIFO(char buf[][50]) {
    int n = atoi(buf[0]);
    int buffer[n];
    printHeader(buf[1]);
    int numberOfELements = 0;
    int queue = 0;
    int faultCount = 0;
    int i = 2;
    while (atoi(buf[i]) != -1) {
        printf("%02d", atoi(buf[i]));
        int isHit = search(buffer, numberOfELements, atoi(buf[i]));
        if (isHit == -1) {
            if (numberOfELements < n) {
                buffer[numberOfELements++] = atoi(buf[i]);
                printf("     ");
            }
            else {
                buffer[queue++] = atoi(buf[i]);
                printf(" F   ");
                faultCount++;
                if (queue >= numberOfELements) {
                    queue = 0;
                }
            }
        }
        else {
            printf("     ");
        }
        printBuffer(buffer, numberOfELements);
        i++;
    }
    printFooter(faultCount);
}

int main() {
    char buf[20][50];
    int size=0;
    while (fgets(buf[size++], 50, stdin));

    if (strcmp(buf[1], "FIFO\n") == 0) {
        FIFO(buf);
    }
    else if (strcmp(buf[1], "LRU\n") == 0) {
        LRU(buf);
    }
    else if (strcmp(buf[1], "CLOCK\n") == 0) {
        CLOCK(buf);
    }
    else if (strcmp(buf[1], "OPTIMAL\n") == 0) {
        size -= 2;
        OPTIMAL(buf, size);
        // printf("hey");
    }
    return 0;
}