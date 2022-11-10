#include <stdio.h>
#include <time.h>
#define NN 10000  // big enough for buffer in mergesort and data0.
int C1, C2;  // number of comparisons and writings

void selectionsort(int arr[],int n) {
    int i, j, min, temp, indexOfMin;

    for (i = 0; i < n - 1; i++)
    {
        min = arr[i];
        indexOfMin = i;
        for (j = i + 1; j < n; j++)
        {
            if (min > arr[j]){
                min = arr[j];
                indexOfMin = j;
            }
            C1++;
        }
        temp = arr[i];
        C2++;
        arr[i] = arr[indexOfMin];
        C2++;
        arr[indexOfMin] = temp;
    }
    
}

void insertionsort(int arr[],int n){
    int i, j, key;
    for (i = 1; i < n; i++){
        key = arr[i];

        for (j = i - 1; j >= 0 && arr[j] > key; j--){
            arr[j + 1] = arr[j];
            C1++;
            C2++;
        }
        arr[j + 1] = key;
        C2++;
    }
}

void merge(int arr[], int l, int m, int r) // l<m<r
{
  int b[NN+1];  // buffer to store two sublists. 
  int i,j,k;

  // copy sublists to buffer
  for (i=l; i<=r; i++)
    {b[i]=arr[i];  C2++;}
  
  i=l; j=m+1; k=l; // reset indices.
  
  // merge sublists in buffer into arr[]
  while (i<=m && j<=r) {
    if (b[i]<=b[j]) 
      {arr[k++]=b[i++]; C2++;}
    else
      {arr[k++]=b[j++]; C2++;}
    C1++;
  }
  if (i>m)
    while (j<=r)
      {arr[k++]=b[j++]; C2++;}
  else
    while (i<=m)
      {arr[k++]=b[i++]; C2++;}
}

void mergesort(int arr[], int l, int r)
{
  int m;

  if (l < r) {
    m = (l+r)/2;
    mergesort(arr, l, m);
    mergesort(arr, m+1, r);
    merge(arr, l, m, r);
  }
  
}

void swap(int *x, int *y) {
    int temp = *x;
    *x = *y;
    *y = temp;
}

int partition(int arr[], int l, int r){
    int x = arr[l];
    int i = l + 1;
    int j = r;

    while(1){

      while (arr[i] <= x && i <= r)
      {
        i++;
        C1++;
      }
      
      while (arr[j] > x && j >= l + 1)
      {
        j--;
        C1++;
      }
      
      if (i < j)
      {
        swap(&arr[i], &arr[j]);
        C2+=2;
      }
      else
      {
        break;
      }
    }
    swap(&arr[l], &arr[j]);
    C2+=2;
    return j;
}

void quicksort(int arr[], int l, int r){
    int p;
    if (l < r){
        p = partition(arr, l, r);
        quicksort(arr, l, p - 1);
        quicksort(arr, p + 1, r);
    }
}

    int main()
{
  int i, j;
  int data0[NN];
  int data[10] = {5,3,8,2,1,6,9,7,0,4};
  int N[10];
  N[1]= 100;
  N[2]= 200;
  N[3]= 300;
  N[4]= 400;
  N[5]= 500;
  N[6]= 600;
  N[7]= 700;
  N[8]= 800;
  N[9]= 900;
  
  printf("\n** Selection Sort **\n");
  for (i=1; i<10; i++) {  
    // read N[i] data
    for (j=0; j<N[i]; j++) {
      scanf("%d", &data0[j]); // read the input 
    }
    C1 = C2 = 0;
    selectionsort(data0,N[i]);
    printf("n = %d; C1 = %d; C2 = %d.\n", N[i], C1, C2);
  }

  printf("\n** Insertion Sort **\n");
  for (i=1; i<10; i++) {  
    // read N[i] data
    for (j=0; j<N[i]; j++) {
      scanf("%d", &data0[j]); // read the input 
    }
    C1 = C2 = 0;
    insertionsort(data0,N[i]);
    printf("n = %d; C1 = %d; C2 = %d.\n", N[i], C1, C2);
  }

  printf("\n** Merge Sort **\n");
  for (i=1; i<10; i++) {  
    // read N[i] data
    for (j=0; j<N[i]; j++) {
      scanf("%d", &data0[j]); // read the input 
    }
    C1=C2=0;
    mergesort(data0,0,N[i]-1);
    printf("n = %d; C1 = %d; C2 = %d.\n", N[i], C1, C2);
  }
  // quicksort(data, 0, 10);
  printf("\n** Quick Sort **\n");
  for (i=1; i<10; i++) {
    // read N[i] data
    for (j=0; j<N[i]; j++) {
      scanf("%d", &data0[j]); // read the input
    }
    C1=C2=0;
    quicksort(data0,0,N[i]-1);
    printf("n = %d; C1 = %d; C2 = %d.\n", N[i], C1, C2);
  }

}
