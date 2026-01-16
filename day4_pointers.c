/**
 * Day 4 - Pointer Practice
 * Complete the functions below
 */

#include <stdio.h>
#include <stdint.h>

// ============================================
// EXERCISE 1: Swap Two Numbers
// ============================================
void swap(int *a, int *b) {
    // TODO: Your code here
    // Hint: Use a temporary variable
}

// ============================================
// EXERCISE 2: Find Max Using Pointer
// ============================================
int* findMax(int *arr, int size) {
    // TODO: Your code here
    // Hint: Keep track of pointer to max element
    // Return pointer, not value!
    return NULL;  // Replace this
}

// ============================================
// EXERCISE 3: String Length (No strlen!)
// ============================================
int myStrlen(const char *str) {
    // TODO: Your code here
    // Hint: Loop until '\0'
    return 0;  // Replace this
}

// ============================================
// BONUS: Reverse Array Using Pointers
// ============================================
void reverseArray(int *arr, int size) {
    // TODO: Your code here
    // Hint: Use two pointers, one at start, one at end
}

// ============================================
// TEST MAIN
// ============================================
int main() {
    printf("=== DAY 4 POINTER PRACTICE ===\n\n");
    
    // Test swap
    printf("Test 1: Swap\n");
    int x = 10, y = 20;
    printf("Before: x=%d, y=%d\n", x, y);
    swap(&x, &y);
    printf("After: x=%d, y=%d\n", x, y);
    printf("Expected: x=20, y=10\n\n");
    
    // Test findMax
    printf("Test 2: Find Max\n");
    int numbers[] = {5, 2, 9, 1, 7};
    int *max = findMax(numbers, 5);
    if (max != NULL) {
        printf("Max value: %d at address: %p\n", *max, (void*)max);
        printf("Expected: 9\n\n");
    }
    
    // Test myStrlen
    printf("Test 3: String Length\n");
    char text[] = "Hello";
    printf("Length of '%s': %d\n", text, myStrlen(text));
    printf("Expected: 5\n\n");
    
    // Test reverseArray
    printf("Test 4: Reverse Array\n");
    int arr[] = {1, 2, 3, 4, 5};
    printf("Before: ");
    for (int i = 0; i < 5; i++) printf("%d ", arr[i]);
    reverseArray(arr, 5);
    printf("\nAfter: ");
    for (int i = 0; i < 5; i++) printf("%d ", arr[i]);
    printf("\nExpected: 5 4 3 2 1\n");
    
    return 0;
}

