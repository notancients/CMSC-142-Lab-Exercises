/*
Run the following algorithms and time them:
1. Insertion sort
2. Shell sort
3. Merge sort
4. Quick sort (built-in)

Run for x, 2x, 3x, and 4x inputs (where x is your initial array size n).
Run for ascending, descending, random input
Replicate each run three (3) times. Record the average.
Graph the results.
Compare the actual running times to the supposed theoretical running times.
Do they match? Analyze your results.
*/




#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <time.h>

// Comparison function used for qsort()
int comp(const void *a, const void *b){
	int *x, *y;
	x = (int *) a;
	y = (int *) b;
	return (*x - *y);
}

// Swap function
void swap(int *a, int *b){
	int temp;
	temp = *a;
	*a = *b;
	*b = temp;
}

// Initialization of data
void init(int a[], int n){
	int i, r;
	srand(time(NULL));

	// Ascending values
	//	for(i=0; i<n; i++)
	//		a[i] = i+1;	
	
	// Descending values	
	for(i=0; i<n; i++)
		a[i] = n-i;
	
	// Random ordering of values - make sure to uncomment either ascending or descending first
	for(i=0; i<n; i++){
		r = rand()%n;
		swap(&a[i], &a[r]);
	}
}

// Merge sort
void merge (int a[], int lower, int mid, int upper){
	int *temp,i,j,k;
	temp=(int *)malloc((upper-lower+1)*sizeof(int));
	for(i=0,j=lower,k=mid+1; j<=mid || k<=upper; i++)
		temp[i]=((j <= mid) && (k > upper || a[j] <= a[k]))?a[j++]:a[k++];
	for(i=0,j=lower;j<=upper; i++, j++)
	a[j]=temp[i];
	free(temp);
}

void msort(int a[], int lower, int upper){
	int mid;
	if (upper-lower>0) {
		mid=(lower+upper)/2;
		msort(a, lower, mid);
		msort(a, mid+1, upper);
		merge(a, lower, mid, upper);
	}
}

// Insertion Sort
void isort(int a[], int n){
	int i, j;
	for(i=1;i<n;i++)
		for(j=i;j>0;j--)
			if(a[j] < a[j-1]) swap(&a[j], &a[j-1]);
			else break;
}

// Shell sort
void shellsort(int a[], int n){
	
	int hk, d, i, j;
	for(hk=n/2;hk>=1;hk/=2)
		for(i=hk;i<n;i++)
			for(j=i;j>hk-1;j-=hk)
				if(a[j-hk] > a[j])
					swap(&a[j-hk], &a[j]);
				else
					break;
}

int main(){
	int n=100000, *a;
	int i;
	double t;
	a=(int*)malloc(sizeof(int)*n);

	init(a,n);
	// time_t t1, t2;
	clock_t t1,t2;
	t1 = clock();
	// time(&t1);
	//for(i=0;i<n;i++)
	//	printf("%d\n", a[i]);

	//qsort(a, n, sizeof(int), comp);
	shellsort(a,n);
	
	//printf("------\n");
	
	//for(i=0;i<n;i++)
	//	printf("%d\n", a[i]);

	// time(&t2);			//time_t
	// t = difftime(t2,t1);

	t2 = clock();			//clock_t
	t = (double) (t2-t1)/ (double)CLOCKS_PER_SEC;
	printf("Elapsed time: %f", t);
	return 0;
}
