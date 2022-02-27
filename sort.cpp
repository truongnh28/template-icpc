#include <bits/stdc++.h>

using namespace std;

//bubble sort
void bubbleSort(int a[], int n) {
    for(int i = 0; i < n; i++) {
        for(int j = n - 1; j > i; j--){
            if(a[j] < a[j - 1]) {
                swap(a[j], a[j - 1]);
            }
        }
    }
}
//selection sort
void selectionSort(int a[], int n) {
    for(int i = 0; i < n - 1; i++) {
        int m = i;
        for(int j = i + 1; j < n; j++) {
            if(a[j] < a[m]) {
                m = j;
            }
        }
        swap(a[m], a[i]);
    }
}
//insertion sort
void insertionSort(int a[], int n) {
    int pos, x;
    for(int i = 1; i < n; i++) {
        x = a[i];
        pos = i - 1;
        while(pos >= 0 && a[pos] > x) {
            a[pos + 1] = a[pos];
            pos--;
        }
        a[pos + 1] = x;
    }
}
//interchange sort
void interchangeSort(int a[], int n) {
    for(int i = 0; i < n - 1; i++) {
        for(int j = i + 1; j < n; j++) {
            if(a[j] < a[i]) {
                swap(a[i], a[j]);
            }
        }
    }
}
//quicksort
void sort (int a[], int l, int r){
    int i = l, j = r;
    int x = a[(l + r) / 2];
    do {
        while(a[i] < x) i++;
        while(a[j] > x) j--;
        if(i <= j){
            swap(a[i], a[j]);
            i++;
            j--;
        }
    } while(i <= j);
    if(l < j){
        sort(a, l, j);
    }
    if(i < r) {
        sort(a, i, r);
    }
}
void quickSort(int a[], int n) {
    sort(a, 0, n - 1);
}
//heapsort
void adjust(int a[], int i, int n) {
    int root = i;
    int l = root * 2 + 1;
    int r = root * 2 + 2;
    if(l < n && a[l] > a[root]) {
        root = l;
    }
    if(r < n && a[r] > a[root]) {
        root = r;
    }
    if(root != i) {
        swap(a[i], a[root]);
        adjust(a, root, n);
    }
}
void heapSort(int a[], int n) {
    for(int i = n / 2 - 1; i >= 0; i--) {
        adjust(a, i, n);
    }
    for(int i = n - 1; i >= 0; i--) {
        swap(a[0], a[i]);
        adjust(a, 0, i);
    }
}
//merge sort 
void merge (int a[], int p, int q, int r) {
    int n1 = q - p + 1;
    int n2 = r - q;
    int L[n1], M[n2];
    for(int i = 0; i < n1; i++) {
        L[i] = a[p + i];
    }
    for(int i = 0; i < n2; i++) {
        M[i] = a[q + 1 + i];
    }
    int i = 0, j = 0, k = p;
    while(i < n1 && j < n2) {
        if(L[i] <= M[j]) {
            a[k] = L[i];
            i++;
        } else {
            a[k] = M[j];
            j++;
        }
        k++;
    }
    while(i < n1) {
        a[k] = L[i];
        i++;
        k++;
    }
    while(j < n2) {
        a[k] = M[j];
        j++;
        k++;
    }
}
void mergeSort(int a[], int l, int r) {
    if(l < r) {
        int m = l + (r - l) / 2;
        mergeSort(a, l, m);
        mergeSort(a, m + 1, r);
        merge(a, l, m, r);
    }
}
int main () {
    int a[] = {34, 12, 33, 11};
    // mergeSort(a, 0, 3);
    insertionSort(a, 4);
    for(auto it:a) cout << it << ' ';
    return 0;
}