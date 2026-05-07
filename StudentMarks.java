// Write a Java program for to Read the marks obtained by second year students. Find out
// maximum and minimum marks using heap data structure.
import java.util.Scanner;
import java.util.Collections;
import java.util.PriorityQueue;

public class StudentMarks {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);

        // Min-Heap to find the minimum value
        PriorityQueue<Integer> minHeap = new PriorityQueue<>();
        
        // Max-Heap to find the maximum value
        PriorityQueue<Integer> maxHeap = new PriorityQueue<>(Collections.reverseOrder());

        System.out.print("Enter the number of students: ");
        int n = sc.nextInt();

        if (n <= 0) {
            System.out.println("Invalid number of students.");
            return;
        }

        System.out.println("Enter the marks for " + n + " students:");
        for (int i = 0; i < n; i++) {
            int marks = sc.nextInt();
            minHeap.add(marks);
            maxHeap.add(marks);
        }

        // The root of the heaps will have our required values
        System.out.println("\n--- Analysis Result ---");
        System.out.println("Maximum Marks Obtained: " + maxHeap.peek());
        System.out.println("Minimum Marks Obtained: " + minHeap.peek());

        sc.close();
    }
}