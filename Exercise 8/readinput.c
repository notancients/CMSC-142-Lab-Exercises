#include <stdio.h>
#include <stdlib.h>

int main() {
    int vertices;
    int edges;
    int from, to;

    printf("Enter amount of vertices:");
    scanf(" %d", &vertices);
    printf("Enter amount of edges: ");
    scanf(" %d", &edges);

    for(int i = 0; i < edges; i++) {
        scanf(" %d", &from);
        scanf(" %d", &to);

        printf("From: %d to: %d.\n", from, to);
    }
    return 0;
}