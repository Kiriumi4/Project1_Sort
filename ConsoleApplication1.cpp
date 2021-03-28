
#include <iostream>
#include <chrono>  

using namespace std;
using namespace std::chrono; 

void generate_back(int* tab, int n);
void generate_rand(int* tab, int n);
void generate_percent(int tab[], float n, float x);
void merge(int tab[], int l, int m, int r);
void merge_sort(int* tab, int l, int r);
int partition(int* tab, int l, int r);
void quick_sort(int tab[], int l, int r);
void heapify(int tab[], int n, int i);
void heap_sort(int tab[], int n);

int main()
{
   
    int n=10000; //array size
    int* tab2 = new int[n];
    int* tab_quick = new int[n];
    int* tab_heap = new int[n];
    int* tab_merge = new int[n];
// floats for saving sorting duration:
    float  duration1[100];
    float  duration2[100];
    float  duration3[100];
    float  time1 = 0;
    float  time2 = 0;
    float  time3 = 0;



   for (int i = 0; i < 100; i++)
    {
       //generate_rand(tab2, n);     
       //generate_back(tab2, n);
       generate_percent(tab2, n,25);
        tab_quick = tab2;
        tab_heap = tab2;
        tab_merge = tab2;
      

        high_resolution_clock::time_point t1 = high_resolution_clock::now();
        quick_sort(tab_quick, 0, n - 1);
        high_resolution_clock::time_point t2 = high_resolution_clock::now();

        high_resolution_clock::time_point t3 = high_resolution_clock::now();
        heap_sort(tab_heap, n);
        high_resolution_clock::time_point t4 = high_resolution_clock::now();

        high_resolution_clock::time_point t5 = high_resolution_clock::now();
        merge_sort(tab_merge, 0, n - 1);
        high_resolution_clock::time_point t6 = high_resolution_clock::now();
 
       duration1[i] = duration_cast<microseconds>(t2 - t1).count();    //messuring time of quick sort
       duration2[i] = duration_cast<microseconds>(t4 - t3).count();    //messuring time of heap sort
       duration3[i] = duration_cast<microseconds>(t6 - t5).count();    //messuring time of merge sort

       //adding time from every cycle
        time1 += duration1[i];
        time2 += duration2[i];
        time3 += duration3[i];
        if(i%10==0) cout << i << endl;   //every 10 sorted array show progress
        
     }
   cout << "Successfully Sorted!" << endl << endl;

   cout << "Quick sorting time:" << endl;
   cout << time1 <<" micro s" << endl;
   cout << "Heap sorting time:" << endl;
   cout << time2 << " micro s" << endl;
   cout << "Merge sorting time:" << endl;
   cout << time3 << " micro s" << endl;
   
  
    cin.ignore();
    cin.get();
    return 0;
}


void generate_back(int* tab, int n) //generates tables sorted backwards for test
{
    int i = 0;
    while (1)
    {
        tab[i] = (n - i) % 500;
        i++;
        if (i == n) break;
    }
}

void generate_rand(int* tab, int n) //generates random element tables for test
{
    int i = 0;
    while (1)
    {
        tab[i] = rand() % 500;
        i++;
        if (i == n) break;
    }
}

void generate_percent(int tab[], float n, float x) //generates sorted to cartain percentage tables for test
{
    int i = 0;
    float j = x / 100 * n;
    while (1)
    {
        if (i < j)
        {
            tab[i] = i % 500;
        }
        else tab[i] = rand() % 500;
        i++;
        if (i == n) break;
    }

}


void merge(int tab[], int l, int m, int r)
{
    int a = m - l + 1;
    int b = r - m;
    int* A = new int[a];
    int* B = new int[b];

    // dividing tab into two arrays A and B
    for (int i = 0; i < a; i++)
    {
        A[i] = tab[l + i];
    }
    for (int j = 0; j < b; j++)
    {
        B[j] = tab[m + 1 + j];
    }




    int i = 0, j = 0, k = l;



    while (i < a && j < b)
    {
        if (A[i] <= B[j])
        {
            tab[k] = A[i];  // adding from first array
            i++;
        }
        else
        {
            tab[k] = B[j];  // adding from second array
            j++;
        } k++;

    }

    // adding left elements from array A and B
    while (i < a)
    {
        tab[k] = A[i];
        i++;
        k++;
    }
    while (j < b)
    {
        tab[k] = B[j];
        j++;
        k++;
    }
    delete A;
    delete B;
}

void merge_sort(int* tab, int l, int r)
{
    int m = l + (r - l) / 2;
    if (l < r)
    {
        merge_sort(tab, l, m);
        merge_sort(tab, m + 1, r);
        merge(tab, l, m, r);
    }
    else return;
}

int partition(int* tab, int l, int r)  //finds partition from table for pivot in quicksort
{
    int x = tab[l];
    int i = l, j = r;
    while (1)
    {
        while (tab[j] > x)   j--;
        while (tab[i] < x)   i++;

        if (i < j)
        {
            swap(tab[i], tab[j]);
            i++;
            j--;
        }
        else
            return j;
    }
}

void quick_sort(int tab[], int l, int r)
{
    int pivot;
    if (l < r)
    {
        pivot = partition(tab, l, r);
        quick_sort(tab, l, pivot);
        quick_sort(tab, pivot + 1, r);
    }
    else return;
}

void heapify(int tab[], int n, int i)
{
    int max = i;
    int l = 2 * i + 1, r = 2 * i + 2;

    if (l < n && tab[l] > tab[max])
        max = l;

    if (r < n && tab[r] > tab[max])
        max = r;

    if (max != i)
    {
        swap(tab[i], tab[max]);
        heapify(tab, n, max);
    }
}

void heap_sort(int tab[], int n)
{
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(tab, n, i);

    for (int i = n - 1; i > 0; i--) {
        swap(tab[0], tab[i]);
        heapify(tab, i, 0);
    }
}


