#include <stdio.h>
#include <stdlib.h>

int getArrayLength(int* a) {
    int length = 0;

    for(int i = 0; a[i]!='\0'; i++){
        length += 1;
    }
    return length;
}

void printArray(int* a, int length) {

    for(int i = 0; i<length; i++) {
        printf("%d ", a[i]);
    }

    printf("\n");
}

void writeFile(int a[], int length) {
    FILE* fileHandle = fopen("output.txt", "w");
    for (int i = 0; i<length; i++) {
        fprintf(fileHandle, "%d\n", a[i]);
    }
    fclose(fileHandle);
}

void loadFile(int* array, int* length) {
    FILE* fp = fopen("input.txt", "r");

    if(fp==NULL) {
        printf("No such file exists. creating a new one.\n");
        fp = fopen("input.txt", "w");
        fclose(fp);
        return;
    }

    fscanf(fp, "%d\n", length);
    printf("!!!\n");
    printf("length %d\n", (*length));

    array = (int *)malloc((sizeof(int))*(*length));
    for(int i = 0; i<(*length); i++) {
        fscanf(fp, "%d", &array[i]);
        printf("%d ", array[i]);
    }
    fclose(fp);
}

void merge(int a[], int lower, int mid, int upper) {
    int *temp, i, j, k;

    temp = (int *)malloc((upper-lower+1)*sizeof(int));

    for(i=0, j=lower, k=(mid+1); j<=mid || k<=upper; i++) {
        
        // printf("BEFORE a[%d]:%d, a[%d]:%d\n",j, a[j],k, a[k]);
        temp[i] = (a[j]<a[k] || k>upper)?a[j++]:a[k++];
        // printf("AFTER a[%d]:%d, a[%d]:%d\n",j, a[j],k, a[k]);

        // printArray(temp);
    }

    for(i=0, j=lower; j<=upper; i++,j++) {
        a[j] = temp[i];
    }
    free(temp);

}

void merge_sort(int a[], int lower, int upper) {

    int mid=(lower+upper)/2;


    if ((upper-lower)>0) {


        merge_sort(a, lower, mid);
        merge_sort(a, mid+1, upper);
        merge(a, lower, mid, upper);
    }
}

int main() {
    // int a[] = {7, 1, 6, 4, 8, 2, 5, 3};
    // int b[] = {7,1,6,4,9,8,2,5,3};
    int* array, length;
    loadFile(array, &length);
    // printf("Initial array: ");
    merge_sort(array, 0, length);
    printArray(array, length);
    // merge_sort(b,0,8);
    // printArray(b);
    return 0;
}