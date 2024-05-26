#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main() {
    char* sampleString;
    printf("Enter numbers: ");
    scanf(" %[^\n]s", sampleString);
    printf("Core dump?\n");
  char str[] = "10 20 30 40 50 60";
  char *pch;
//   printf ("Splitting string \"%s\" into tokens:\n", sampleString);
    int sum = 0;
  pch = strtok(sampleString, " ,.-");
  while (pch != NULL) {
    sum += atoi(pch);
    printf ("%s\n",pch);
    pch = strtok(NULL, " ,.-");
  }
  printf("Sum: %d.\n", sum);
  return 0;
}

