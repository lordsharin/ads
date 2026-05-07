// Implement the Heap/Shell sort algorithm implemented in Java demonstrating heap/shell
// data structure with modularity of programming language
import java.util.Scanner;

public class HeapSort {

    // Main function to perform sort
    public void sort(int arr[]) {
        int n = arr.length;

        // 1. Build heap (rearrange array)
        // We start from the last non-leaf node and move up
        for (int i = n / 2 - 1; i >= 0; i--) {
            heapify(arr, n, i);
        }

        // 2. One by one extract elements from heap
        for (int i = n - 1; i > 0; i--) {
            // Move current root to end (swap)
            int temp = arr[0];
            arr[0] = arr[i];
            arr[i] = temp;

            // call max heapify on the reduced heap
            heapify(arr, i, 0);
        }
    }

    // To heapify a subtree rooted with node i which is an index in arr[]
    void heapify(int arr[], int n, int i) {
        int largest = i; // Initialize largest as root
        int left = 2 * i + 1; // left child
        int right = 2 * i + 2; // right child

        // If left child is larger than root
        if (left < n && arr[left] > arr[largest])
            largest = left;

        // If right child is larger than largest so far
        if (right < n && arr[right] > arr[largest])
            largest = right;

        // If largest is not root, swap and continue heapifying
        if (largest != i) {
            int swap = arr[i];
            arr[i] = arr[largest];
            arr[largest] = swap;

            // Recursively heapify the affected sub-tree
            heapify(arr, n, largest);
        }
    }

    // Helper method to print the array
    static void printArray(int arr[]) {
        for (int i : arr) {
            System.out.print(i + " ");
        }
        System.out.println();
    }

    public static void main(String args[]) {
        Scanner sc = new Scanner(System.in);
        
        System.out.println("Enter number of elements:");
        int n = sc.nextInt();
        int arr[] = new int[n];

        System.out.println("Enter the elements:");
        for(int i = 0; i < n; i++) {
            arr[i] = sc.nextInt();
        }

        HeapSort ob = new HeapSort();
        ob.sort(arr);

        System.out.println("Sorted array is:");
        printArray(arr);
        
        sc.close();
    }
}