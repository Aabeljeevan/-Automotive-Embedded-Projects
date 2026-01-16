/**
 * Day 4 - Memory Concepts Practice
 * Study where each variable is stored
 */

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

// ============================================
// GLOBAL VARIABLES - Where are these stored?
// ============================================

// Question 1: Where is this stored?
const char FIRMWARE_VERSION[] = "v1.0.0";  // Answer: ___________

// Question 2: Where is this stored?
int globalInitialized = 100;                // Answer: ___________

// Question 3: Where is this stored?
int globalUninitialized;                    // Answer: ___________

// Question 4: Where is this stored?
static int fileStaticInit = 50;             // Answer: ___________

// Question 5: Where is this stored?
static int fileStaticUninit;                // Answer: ___________

// ============================================
// FUNCTION WITH VARIOUS STORAGE TYPES
// ============================================
void demonstrateStorage() {
    // Question 6: Where is this stored?
    int localVar = 10;                      // Answer: ___________
    
    // Question 7: Where is this stored?
    static int functionStatic = 0;          // Answer: ___________
    
    // Question 8: Where is this pointer stored? Where does it point?
    int *heapPtr = (int*)malloc(sizeof(int));  // Pointer: _____  Data: _____
    
    // Question 9: Where is this array stored?
    char localArray[256];                   // Answer: ___________
    
    // Question 10: Where is this string stored?
    const char *strPtr = "Hello";           // String: _____  Pointer: _____
    
    functionStatic++;
    printf("Function called %d times\n", functionStatic);
    
    if (heapPtr != NULL) {
        *heapPtr = 42;
        free(heapPtr);  // Don't forget to free!
    }
}

// ============================================
// MEMORY SECTIONS DEMO
// ============================================
void demonstrateMemorySections() {
    printf("=== MEMORY ADDRESSES DEMO ===\n\n");
    
    // Print addresses of different storage types
    printf(".text section (Flash - Code & Constants):\n");
    printf("  FIRMWARE_VERSION: %p = %s\n", 
           (void*)FIRMWARE_VERSION, FIRMWARE_VERSION);
    printf("  Function address: %p\n\n", (void*)demonstrateMemorySections);
    
    printf(".data section (RAM - Initialized Globals):\n");
    printf("  globalInitialized: %p = %d\n", 
           (void*)&globalInitialized, globalInitialized);
    printf("  fileStaticInit:    %p = %d\n\n", 
           (void*)&fileStaticInit, fileStaticInit);
    
    printf(".bss section (RAM - Uninitialized Globals, auto-zeroed):\n");
    printf("  globalUninitialized: %p = %d\n", 
           (void*)&globalUninitialized, globalUninitialized);
    printf("  fileStaticUninit:    %p = %d\n\n", 
           (void*)&fileStaticUninit, fileStaticUninit);
    
    printf("Stack (RAM - Local Variables):\n");
    int stackVar = 99;
    printf("  stackVar: %p = %d\n\n", (void*)&stackVar, stackVar);
    
    printf("Heap (RAM - Dynamic Allocation):\n");
    int *heapVar = (int*)malloc(sizeof(int));
    if (heapVar != NULL) {
        *heapVar = 77;
        printf("  heapVar:  %p = %d\n\n", (void*)heapVar, *heapVar);
        free(heapVar);
    }
}

// ============================================
// STM32-STYLE MEMORY USAGE
// ============================================

// Simulating STM32 register access
#define GPIOE_BASE  0x48001000
#define GPIOE_ODR   (*((volatile uint32_t*)(GPIOE_BASE + 0x14)))

// Pattern state (like your LED code)
uint8_t currentPattern = 0;     // Question: Where? ___________

void pattern_example() {
    // Pattern step counter
    static uint8_t step = 0;    // Question: Where? ___________
    
    // Temporary calculation
    uint32_t ledMask = (1 << step);  // Question: Where? ___________
    
    // Access hardware register (STM32-style)
    // GPIOE_ODR |= ledMask;  // Question: GPIOE_ODR where? ___________
    
    step++;
}

// ============================================
// MEMORY OPTIMIZATION EXAMPLES
// ============================================

// BAD: Wastes Flash and RAM
void badExample() {
    int lookupTable[256] = {0, 1, 2, 3, /* ... */};  // Stack! Bad for large array!
    // Each call creates this 1KB array on stack!
}

// GOOD: Uses Flash only
const int LOOKUP_TABLE[256] = {0, 1, 2, 3, /* ... */};  // Flash, once!
void goodExample() {
    // Just use LOOKUP_TABLE directly
    int value = LOOKUP_TABLE[10];
}

// BAD: Initialized large array (wastes Flash)
uint8_t badBuffer[1024] = {0};  // .data - 1KB Flash + 1KB RAM!

// GOOD: Uninitialized large array (saves Flash)
uint8_t goodBuffer[1024];       // .bss - only 1KB RAM, auto-zeroed!

// ============================================
// QUIZ
// ============================================
void memoryQuiz() {
    printf("\n=== MEMORY QUIZ ===\n\n");
    
    printf("Questions (write your answers):\n\n");
    
    printf("1. Where is code stored in embedded systems?\n");
    printf("   Answer: ___________\n\n");
    
    printf("2. Where should you put large constant lookup tables?\n");
    printf("   Answer: ___________\n\n");
    
    printf("3. What's the difference between .data and .bss?\n");
    printf("   Answer: ___________\n\n");
    
    printf("4. Why avoid large arrays on stack?\n");
    printf("   Answer: ___________\n\n");
    
    printf("5. Why avoid malloc in embedded systems?\n");
    printf("   Answer: ___________\n\n");
    
    printf("6. Where do volatile hardware registers live?\n");
    printf("   Answer: ___________\n\n");
    
    printf("7. What happens to .bss at startup?\n");
    printf("   Answer: ___________\n\n");
    
    printf("8. Can you write to .text section at runtime?\n");
    printf("   Answer: ___________\n\n");
}

// ============================================
// ANSWERS (Check after attempting!)
// ============================================
/*
ANSWERS:

Variable Storage:
1. FIRMWARE_VERSION[]      → .text (Flash) - const string
2. globalInitialized       → .data (RAM) - initialized global
3. globalUninitialized     → .bss (RAM) - uninitialized, zeroed
4. fileStaticInit          → .data (RAM) - initialized static
5. fileStaticUninit        → .bss (RAM) - uninitialized static
6. localVar                → Stack - local variable
7. functionStatic          → .data (RAM) - initialized static
8. heapPtr (pointer)       → Stack, points to Heap data
9. localArray[256]         → Stack - local array
10. "Hello" string         → .text (Flash), strPtr → Stack

STM32 Pattern:
- currentPattern           → .data (RAM) - initialized global
- step (static)            → .data (RAM) - static local
- ledMask                  → Stack - temporary calculation
- GPIOE_ODR               → Peripheral address space (memory-mapped I/O)

Quiz Answers:
1. Flash/ROM (.text section)
2. Flash, using const keyword
3. .data has initial values (uses Flash), .bss doesn't (RAM only, zeroed)
4. Stack is limited (4-16KB), can overflow
5. Heap fragmentation, non-deterministic, memory leaks risk
6. Peripheral address space (memory-mapped, 0x40000000+)
7. Zeroed by startup code before main()
8. No - it's read-only (Flash/ROM)
*/

// ============================================
// MAIN
// ============================================
int main() {
    printf("=== DAY 4 MEMORY CONCEPTS ===\n\n");
    
    demonstrateMemorySections();
    
    printf("Calling function multiple times to see static behavior:\n");
    demonstrateStorage();
    demonstrateStorage();
    demonstrateStorage();
    
    memoryQuiz();
    
    printf("\n=== Study the code and answer the questions! ===\n");
    printf("Check your answers at the end of the file.\n\n");
    
    return 0;
}

