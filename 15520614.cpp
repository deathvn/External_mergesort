
// C++ program to implement external sorting using
// merge sort
#include <bits/stdc++.h>
using namespace std;


struct MinHeapNode
{
    // The element to be stored
    double element;

    // index of the array from which the element is taken
    int i;
};

// Prototype of a utility function to swap two min heap nodes
void swap(MinHeapNode* x, MinHeapNode* y);

// A class for Min Heap
class MinHeap
{
    MinHeapNode* harr; // pointer to array of elements in heap
    int heap_size;     // size of min heap

public:
    // Constructor: creates a min heap of given size
    MinHeap(MinHeapNode a[], int size);

    // to heapify a subtree with root at given index
    void MinHeapify(int);

    // to get index of left child of node at index i
    int left(int i) { return (2 * i + 1); }

    // to get index of right child of node at index i
    int right(int i) { return (2 * i + 2); }

    // to get the root
    MinHeapNode getMin() {  return harr[0]; }

    // to replace root with new node x and heapify()
    // new root
    void replaceMin(MinHeapNode x)
    {
        harr[0] = x;
        MinHeapify(0);
    }
};

// Constructor: Builds a heap from a given array a[]
// of given size
MinHeap::MinHeap(MinHeapNode a[], int size)
{
    heap_size = size;
    harr = a; // store address of array
    int i = (heap_size - 1) / 2;
    while (i >= 0)
    {
        MinHeapify(i);
        i--;
    }
}

// A recursive method to heapify a subtree with root
// at given index. This method assumes that the
// subtrees are already heapified
void MinHeap::MinHeapify(int i)
{
    int l = left(i);
    int r = right(i);
    int smallest = i;
    if (l < heap_size && harr[l].element < harr[i].element)
        smallest = l;
    if (r < heap_size && harr[r].element < harr[smallest].element)
        smallest = r;
    if (smallest != i)
    {
        swap(&harr[i], &harr[smallest]);
        MinHeapify(smallest);
    }
}

// A utility function to swap two elements
void swap(MinHeapNode* x, MinHeapNode* y)
{
    MinHeapNode temp = *x;
    *x = *y;
    *y = temp;
}

// Merges two subarrays of arr[].
// First subarray is arr[l..m]
// Second subarray is arr[m+1..r]
void merge(vector <double> arr, int l, int m, int r)
{
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;

    /* create temp arrays */
    double L[n1], R[n2];

    /* Copy data to temp arrays L[] and R[] */
    for(i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for(j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    /* Merge the temp arrays back into arr[l..r]*/
    i = 0; // Initial index of first subarray
    j = 0; // Initial index of second subarray
    k = l; // Initial index of merged subarray
    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j])
            arr[k++] = L[i++];
        else
            arr[k++] = R[j++];
    }

    /* Copy the remaining elements of L[], if there
       are any */
    while (i < n1)
        arr[k++] = L[i++];

    /* Copy the remaining elements of R[], if there
       are any */
    while(j < n2)
        arr[k++] = R[j++];
}

/* l is for left index and r is right index of the
   sub-array of arr to be sorted */
void mergeSort(vector <double> arr, int l, int r)
{
    if (l < r)
    {
        // Same as (l+r)/2, but avoids overflow for
        // large l and h
        int m = l + (r - l) / 2;

        // Sort first and second halves
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);

        merge(arr, l, m, r);
    }
}


// Merges k sorted files.  Names of files are assumed
// to be 1, 2, 3, ... k
void mergeFiles(ofstream out, int n, int k)
{

}

// Using a merge-sort algorithm, create the initial runs
// and divide them evenly among the output files
void createInitialRuns(ifstream input, int run_size, int num_ways)
{

}



// For sorting data stored on disk
void externalSort();

// Global variable
// No. of Partitions of input file.
int num_ways = 2;

int Size = 80*pow(10,3);
// The size of each partition
int run_size = Size/num_ways + 1;
ifstream input("input80K.bin");
ofstream output("output.bin");
// Global variable

// Driver program to test above
int main()
{
    //int a[10] = {2, 10, 20, 30, 40, 50, 70, 80, 90, 100};

    //for (int i=0; i<10; ++i)
    {
        num_ways = 10;
        run_size = Size/num_ways;

        cout<<"n-way: "<<num_ways<<'\n';

        clock_t start = clock();
        externalSort();
        printf("Time: %fs\n", (double)(clock() - start)/CLOCKS_PER_SEC);

        cout<<endl;
    }
    output.close();
    input.close();
    return 0;
}

void externalSort()
{
    // read the input file, create the initial runs,
    // and assign the runs to the scratch output files
    //createInitialRuns(input, run_size, num_ways);

    {
        // output scratch files
        ofstream out[num_ways];
        char fileName[2];
        for (int i = 0; i < num_ways; i++)
        {
            // convert i to string
            snprintf(fileName, sizeof(fileName), "%d", i);

            // Open output files in write mode.
            out[i].open(fileName);
        }

        // allocate a dynamic array large enough
        // to accommodate runs of size run_size
        vector <double> arr(run_size);

        bool more_input = true;
        int next_output_file = 0;

        int i;
        while (more_input)
        {
            // write run_size elements into arr from input file
            for (i = 0; i < run_size; i++)
            {
                input >> arr[i];
                if (input.eof())
                {
                    more_input = false;
                    break;
                }
            }

            // sort array using merge sort
            mergeSort(arr, 0, i - 1);

            // write the records to the appropriate scratch output file
            // can't assume that the loop runs to run_size
            // since the last run's length may be less than run_size
            for (int j = 0; j < i; j++)
                out[next_output_file]<<arr[j]<<' ';

            next_output_file++;
        }

        // close input and output files
        for (int i = 0; i < num_ways; i++)
            out[i].close();

    }

    // Merge the runs using the K-way merging
    //mergeFiles(output, run_size, num_ways);
    {
        int k = num_ways;
        int n = run_size;
        ifstream in[k];
        for (int i = 0; i < k; i++)
        {
            char fileName[2];

            // convert i to string
            snprintf(fileName, sizeof(fileName), "%d", i);

            // Open output files in read mode.
            in[i].open(fileName);
        }

        // Create a min heap with k heap nodes.  Every heap node
        // has first element of scratch output file
        MinHeapNode* harr = new MinHeapNode[k];
        int i;
        for (i = 0; i < k; i++)
        {
            // break if no output file is empty and
            // index i will be no. of input files
            in[i] >> harr[i].element;
            if (in[i].eof())
                break;

            harr[i].i = i; // Index of scratch output file
        }
        MinHeap hp(harr, i); // Create the heap

        int count = 0;

        // Now one by one get the minimum element from min
        // heap and replace it with next element.
        // run till all filled input files reach EOF
        while (count != i)
        {
            // Get the minimum element and store it in output file
            MinHeapNode root = hp.getMin();
            output<<root.element<<' ';

            // Find the next element that will replace current
            // root of heap. The next element belongs to same
            // input file as the current min element.
            in[root.i] >> root.element;
            if (in[root.i].eof() )
            {
                root.element = double(INT_MAX);
                count++;
            }

            // Replace root with next element of input file
            hp.replaceMin(root);
        }

        // close input and output files
        for (int i = 0; i < k; i++)
            in[i].close();

    }
}
