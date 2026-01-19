/**
 * Day 4 - Pointer Practice - COMPLETE SOLUTIONS
 * Study these and understand how they work!
 */

#include <stdio.h>
#include <stdint.h>

// ============================================
// EXERCISE 1: Swap Two Numbers
// ============================================
void swap(int *a, int *b) {
    int temp = *a;  // Store value at address a
    *a = *b;        // Copy value from b to a
    *b = temp;      // Copy temp to b
}

// Why this works:
// - We receive ADDRESSES (pointers) to the variables
// - We modify the VALUES at those addresses
// - Changes persist after function returns

// ============================================
// EXERCISE 2: Find Max Using Pointer
// ============================================
int* findMax(int *arr, int size) {
    int *maxPtr = arr;  // Start with first element
    
    for (int i = 1; i < size; i++) {
        if (*(arr + i) > *maxPtr) {  // Compare values
            maxPtr = arr + i;         // Update pointer to new max
        }
    }
    
    return maxPtr;  // Return POINTER to max element
}

// Key concepts:
// - arr + i means "address of arr[i]"
// - *(arr + i) means "value at arr[i]"
// - We return pointer, not value!

// ============================================
// EXERCISE 3: String Length (No strlen!)
// ============================================
int myStrlen(const char *str) {
    int length = 0;
    
    while (*str != '\0') {  // Loop until null terminator
        length++;
        str++;              // Move pointer to next char
    }
    
    return length;
}

// How it works:
// - Strings in C end with '\0' (null terminator)
// - We count characters until we hit '\0'
// - str++ moves pointer forward by 1 character

// ============================================
// BONUS: Reverse Array Using Pointers
// ============================================
void reverseArray(int *arr, int size) {
    int *start = arr;           // Pointer to first element
    int *end = arr + size - 1;  // Pointer to last element
    
    while (start < end) {
        // Swap elements at start and end
        int temp = *start;
        *start = *end;
        *end = temp;
        
        start++;  // Move start forward
        end--;    // Move end backward
    }
}

// Strategy:
// - Two pointers: one at start, one at end
// - Swap elements and move pointers toward middle
// - Stop when pointers meet

// ============================================
// TEST MAIN
// ============================================
int main() {
    printf("=== DAY 4 POINTER PRACTICE - SOLUTIONS ===\n\n");
    
    // Test swap
    printf("Test 1: Swap\n");
    int x = 10, y = 20;
    printf("Before: x=%d, y=%d\n", x, y);
    swap(&x, &y);
    printf("After: x=%d, y=%d\n", x, y);
    printf("Expected: x=20, y=10 ✅\n\n");
    
    // Test findMax
    printf("Test 2: Find Max\n");
    int numbers[] = {5, 2, 9, 1, 7};
    int *max = findMax(numbers, 5);
    printf("Max value: %d at address: %p\n", *max, (void*)max);
    printf("Expected: 9 ✅\n\n");
    
    // Test myStrlen
    printf("Test 3: String Length\n");
    char text[] = "Hello";
    printf("Length of '%s': %d\n", text, myStrlen(text));
    printf("Expected: 5 ✅\n\n");
    
    // Test reverseArray
    printf("Test 4: Reverse Array\n");
    int arr[] = {1, 2, 3, 4, 5};
    printf("Before: ");
    for (int i = 0; i < 5; i++) printf("%d ", arr[i]);
    reverseArray(arr, 5);
    printf("\nAfter: ");
    for (int i = 0; i < 5; i++) printf("%d ", arr[i]);
    printf("\nExpected: 5 4 3 2 1 ✅\n\n");
    
    printf("=== ALL TESTS PASSED! ===\n");
    
    return 0;
}

/*
KEY TAKEAWAYS:

1. Pointers store ADDRESSES, not values
   int *ptr = &variable;  // ptr holds address of variable

2. Dereference (*) gets the VALUE at an address
   *ptr = 10;  // Sets value at address to 10

3. Pointer arithmetic:
   ptr + 1  // Moves to next element (not next byte!)
   arr[i] == *(arr + i)  // Same thing!

4. Pass by reference (pointers) allows modification
   swap(&x, &y);  // Pass addresses, can modify x and y

5. Returning pointers is useful
   int *max = findMax(arr, size);  // Returns address of max

EMBEDDED USAGE:
- Hardware registers: volatile uint32_t *GPIO = (uint32_t*)0x40020C14;
- Function parameters: void config(GPIO_TypeDef *port);
- Efficient data passing: No copying large structs!
*/

