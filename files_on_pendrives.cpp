#include <iostream>
#include <string.h>

#define NUM_OF_PENDRIVES 2

using namespace std;  

struct File
{
    int id; // File ID
    int r;  // File size

    // Default constructor
    File()
    : id(0), r(0)
    {}

    // Parameterized constructor
    File(int id, int r)
    : id(id), r(r)
    {}
    
    // Copy constructor
    File(const File& f)
    : id(f.id), r(f.r)
    {}

    // Move constructor
    File(File&& f)
    {
        id = f.id;
        r = f.r;
        f = File();
    }

    // Copy assignment operator
    File& operator=(const File& f)
    {
        File tmp = f;
        swap(id, tmp.id);
        swap(r, tmp.r);
        return *this;
    }

    // Move assignment operator
    File& operator=(File&& f)
    {
        swap(id, f.id);
        swap(r, f.r);
        return *this;
    }

    // Assignment operator with an integer
    File& operator=(const int& i)
    {
        this->id = i;
        this->r = i;
        return *this;
    }
};

void quicksort(File *arr, const char *str, int low, int high);
void reverse_arr(File *arr, int n);

struct Pendrive
{
    int n;     // Number of files in the pendrive
    int max_n; // Maximum capacity of the pendrive
    int r;     // Remaining space in the pendrive
    File *arr; // Array of files stored in the pendrive

    // Default constructor
    Pendrive() 
    : n(0), max_n(0), r(0), arr(nullptr)
    {}

    // Constructor with maximum capacity
    Pendrive(int max_n) 
    : n(0), max_n(max_n), r(0), arr(new File [max_n])
    {}

    // Constructor with maximum capacity and initial remaining space
    Pendrive(int max_n, int p)
    : n(0), max_n(max_n), r(p), arr(new File [max_n])
    {}

    // Destructor
    ~Pendrive() { if (n > 0) delete[] arr; }

    // Add a file to the pendrive with provided values
    void add_file(int id, int r)
    {
        arr[n] = File(id, r);
        n++;
    }

    // Add a file to the pendrive from an external source
    void add_file(File &file)
    {
        if (file.r > 0 && r - file.r >= 0)
        {
            arr[n] = file;
            n++;
            r -= file.r;
            file = 0;
        }
    }

    // Sort files in the pendrive based on the given criteria
    // Files are sorted in descending order when sorted by ID
    // and in ascending order when sorted by file size
    void sort_files_by(const char *str)
    {
        quicksort(arr, str, 0, n - 1);
        if (!strcmp(str, "id")) reverse_arr(arr, n);
    }
};

// Function to partition the array of files for quicksort
int partition(File *arr, const char *str, int low, int high)
{
    int x, i, j;
    File buffer;
    if (!strcmp(str, "r"))
        x = arr[low].r;
    else if (!strcmp(str, "id"))
        x = arr[low].id;
    else
        x = arr[low].r;
    i = low;
    j = high;
    while (true)
    {
        while ((!strcmp(str, "r") && arr[j].r > x) ||
               (!strcmp(str, "id") && arr[j].id > x))
            j--;
        while ((!strcmp(str, "r") && arr[i].r < x) ||
               (!strcmp(str, "id") && arr[i].id < x))
            i++;
        if (i < j)
        {
            buffer = arr[i];
            arr[i] = arr[j];
            arr[j] = buffer;
            i++;
            j--;
        }
        else
            return j;
    }
}

// Function to perform quicksort on the array of files
void quicksort(File *arr, const char *str, int low, int high)
{
    int pivot;
    if (low < high)
    {  
        pivot = partition(arr, str, low, high);
        quicksort(arr, str, low, pivot);
        quicksort(arr, str, pivot + 1, high);
    }
}

// Function to reverse the elements of the array of files
void reverse_arr(File *arr, int n)
{
    File buffer;
    int low = 0, high = n - 1;
    while (low < high)
    {
        buffer = arr[low];
        arr[low] = arr[high];
        arr[high] = buffer;
        low++;
        high--;
    }
}

int main()
{
    int n; // Number of files
    int p; // Size of the pendrives
    Pendrive pendrives[NUM_OF_PENDRIVES];
    Pendrive buffer; 

    // Read input values for number of files and size of pendrives
    scanf("%d %d", &n, &p);

    // Create a buffer pendrive with the given size
    buffer = Pendrive(n);

    // Create multiple pendrives with the given capacity 
    // and initial remaining space
    for (int i = 0; i < NUM_OF_PENDRIVES; i++)
        pendrives[i] = Pendrive(n, p);
        
    int id; // File ID
    int r;  // File size
    // Read file information and add it to the buffer pendrive
    for (int i = 0; i < n; i++)
    {
        scanf("%d %d", &id, &r);
        buffer.add_file(id, r);
    }

    // Sort the files in the buffer pendrive based on 
    // the size of files (ascending order)
    buffer.sort_files_by("r");

    // Distribute the files from the buffer pendrive
    // to individual pendrives
    for (int i = 0; i < NUM_OF_PENDRIVES; i++)
        for (int j = 0; j < n; j++)
            pendrives[i].add_file(buffer.arr[j]);

    int sum = 0;
    // Calculate the total number of files across all pendrives
    for (int i = 0; i < NUM_OF_PENDRIVES; i++)
        sum += pendrives[i].n;

    // Print the total number of files
    printf("%d\n", sum);

    // Print the file IDs in each pendrive,
    // sorted by ID (descending order)
    for (int i = 0; i < NUM_OF_PENDRIVES; i++)
    {
        pendrives[i].sort_files_by("id");
        int num = i + 1;
        printf("%d: ", num);
        for (int j = 0; j < pendrives[i].n; j++)
            printf("%d ", pendrives[i].arr[j].id);
        printf("\n");
    }

    return 0;
}