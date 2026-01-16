# 📚 DAY 4 - Theory Foundations + Memory Concepts

**Date:** January 14, 2026  
**Time Needed:** 2 hours  
**Goal:** Fill theory gaps + Master memory concepts + Apply to hardware

---

## 🎯 Today's Mission:

**Part 1:** Pointer fundamentals (30 mins)  
**Part 2:** Bit manipulation systematic practice (30 mins)  
**Part 3:** Memory concepts (40 mins)  
**Part 4:** Apply to STM32 hardware (20 mins)

**By end of today:** Complete theoretical foundation + understand where your code lives in memory!

---

# PART 1: POINTER FUNDAMENTALS (30 mins)

## 🧠 Quick Theory Recap:

### What is a Pointer?
```c
int value = 42;
int *ptr = &value;  // ptr holds the ADDRESS of value

printf("value = %d\n", value);      // 42
printf("address of value = %p\n", &value);  // e.g., 0x7ffc1234
printf("ptr = %p\n", ptr);          // 0x7ffc1234 (same address)
printf("*ptr = %d\n", *ptr);        // 42 (dereference - get value at address)
```

**Key Operators:**
- `&` = Address-of operator ("give me the address")
- `*` = Dereference operator ("give me the value at this address")

---

## 💻 EXERCISE 1: Swap Two Numbers

**Problem:**
```c
void swap(int *a, int *b) {
    // Your code: Swap values of a and b using pointers
}

int main() {
    int x = 10, y = 20;
    printf("Before: x=%d, y=%d\n", x, y);
    swap(&x, &y);
    printf("After: x=%d, y=%d\n", x, y);  // Should print: x=20, y=10
    return 0;
}
```

**Your Solution:**
```c
void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}
```

**Try it yourself first! Write in a file: `day4_pointers.c`**

---

## 💻 EXERCISE 2: Find Max Using Pointer

**Problem:**
```c
int* findMax(int *arr, int size) {
    // Return pointer to the maximum element in array
}

int main() {
    int numbers[] = {5, 2, 9, 1, 7};
    int *max = findMax(numbers, 5);
    printf("Max value: %d at address: %p\n", *max, max);
    return 0;
}
```

**Your Solution:**
```c
int* findMax(int *arr, int size) {
    int *maxPtr = arr;  // Assume first element is max
    
    for (int i = 1; i < size; i++) {
        if (*(arr + i) > *maxPtr) {
            maxPtr = arr + i;
        }
    }
    
    return maxPtr;
}
```

**Key Learning:** `arr + i` means "address of arr[i]"

---

## 💻 EXERCISE 3: String Length (No strlen!)

**Problem:**
```c
int myStrlen(const char *str) {
    // Calculate length without using strlen()
}

int main() {
    char text[] = "Hello";
    printf("Length: %d\n", myStrlen(text));  // Should print 5
    return 0;
}
```

**Your Solution:**
```c
int myStrlen(const char *str) {
    int length = 0;
    while (*str != '\0') {  // Loop until null terminator
        length++;
        str++;  // Move pointer to next character
    }
    return length;
}
```

---

## 🎯 Pointer Summary:

**In Embedded Systems, you use pointers for:**
1. **Hardware registers:**
   ```c
   volatile uint32_t *GPIOE_ODR = (volatile uint32_t*)0x40020C14;
   *GPIOE_ODR |= (1 << 9);  // Set bit 9
   ```

2. **Function parameters (pass by reference):**
   ```c
   void configureLED(GPIO_TypeDef *port, uint8_t pin) {
       port->ODR |= (1 << pin);
   }
   ```

3. **Arrays and buffers:**
   ```c
   uint8_t buffer[256];
   processData(buffer, sizeof(buffer));
   ```

---

# PART 2: BIT MANIPULATION SYSTEMATIC PRACTICE (30 mins)

You already KNOW this from hardware! Let's make it systematic.

## 💻 EXERCISE 1: Set Bit

**Problem:**
```c
void setBit(uint32_t *reg, uint8_t bit) {
    // Set the specified bit to 1
}
```

**Solution:**
```c
void setBit(uint32_t *reg, uint8_t bit) {
    *reg |= (1 << bit);
}

// Example:
uint32_t value = 0b00000000;  // 0
setBit(&value, 3);
// Result: 0b00001000  // bit 3 is now 1
```

**You already did this with LEDs!**
```c
GPIOE_ODR |= (1 << 9);  // Same concept!
```

---

## 💻 EXERCISE 2: Clear Bit

**Problem:**
```c
void clearBit(uint32_t *reg, uint8_t bit) {
    // Clear the specified bit to 0
}
```

**Solution:**
```c
void clearBit(uint32_t *reg, uint8_t bit) {
    *reg &= ~(1 << bit);
}

// Example:
uint32_t value = 0b00001111;  // All lower 4 bits set
clearBit(&value, 2);
// Result: 0b00001011  // bit 2 is now 0
```

---

## 💻 EXERCISE 3: Toggle Bit

**Problem:**
```c
void toggleBit(uint32_t *reg, uint8_t bit) {
    // Flip the specified bit (0→1 or 1→0)
}
```

**Solution:**
```c
void toggleBit(uint32_t *reg, uint8_t bit) {
    *reg ^= (1 << bit);
}

// Example:
uint32_t value = 0b00001000;  // bit 3 is 1
toggleBit(&value, 3);
// Result: 0b00000000  // bit 3 is now 0
toggleBit(&value, 3);
// Result: 0b00001000  // bit 3 is back to 1
```

---

## 💻 EXERCISE 4: Check if Bit is Set

**Problem:**
```c
uint8_t isBitSet(uint32_t reg, uint8_t bit) {
    // Return 1 if bit is set, 0 if clear
}
```

**Solution:**
```c
uint8_t isBitSet(uint32_t reg, uint8_t bit) {
    return (reg & (1 << bit)) ? 1 : 0;
}

// Example:
uint32_t value = 0b00001000;  // bit 3 is 1
if (isBitSet(value, 3)) {
    printf("Bit 3 is SET\n");
}
```

**You used this for button reading!**
```c
if (GPIOA_IDR & (1 << 0)) {  // Same concept!
    // Button pressed
}
```

---

## 💻 EXERCISE 5: Count Set Bits

**Problem:**
```c
uint8_t countSetBits(uint32_t num) {
    // Count how many bits are 1
}
```

**Solution:**
```c
uint8_t countSetBits(uint32_t num) {
    uint8_t count = 0;
    while (num) {
        count += num & 1;  // Add 1 if LSB is set
        num >>= 1;         // Shift right by 1
    }
    return count;
}

// Example:
uint32_t value = 0b00101101;  // 5 bits are 1
printf("Set bits: %d\n", countSetBits(value));  // Prints: 5
```

---

## 💻 EXERCISE 6: Extract Bits

**Problem:**
```c
uint32_t extractBits(uint32_t value, uint8_t position, uint8_t length) {
    // Extract 'length' bits starting from 'position'
}
```

**Solution:**
```c
uint32_t extractBits(uint32_t value, uint8_t position, uint8_t length) {
    uint32_t mask = (1 << length) - 1;  // Create mask with 'length' 1s
    return (value >> position) & mask;
}

// Example:
uint32_t value = 0b11010110;
uint32_t bits = extractBits(value, 2, 3);
// Extracts 3 bits starting at position 2
// Result: 0b101 = 5
```

**This is used for reading multi-bit register fields!**

---

## 🎯 Bit Manipulation Summary:

| Operation | Formula | Use in STM32 |
|-----------|---------|--------------|
| Set bit | `reg \|= (1 << n)` | Turn ON LED |
| Clear bit | `reg &= ~(1 << n)` | Turn OFF LED |
| Toggle bit | `reg ^= (1 << n)` | Flip LED state |
| Check bit | `reg & (1 << n)` | Read button |
| Extract bits | `(reg >> pos) & mask` | Read register fields |

---

# PART 3: MEMORY CONCEPTS (40 mins)

## 🧠 Memory Sections in Embedded Systems:

Every embedded program has different memory regions:

```
┌─────────────────────────────────┐ High Address
│         STACK (RAM)             │ ← Local variables, function calls
│           ↓ grows down          │
│                                 │
│         HEAP (RAM)              │ ← Dynamic allocation (malloc)
│           ↑ grows up            │
│                                 │
├─────────────────────────────────┤
│      .bss (RAM)                 │ ← Uninitialized global/static (zeroed at startup)
├─────────────────────────────────┤
│      .data (RAM)                │ ← Initialized global/static (copied from Flash)
├─────────────────────────────────┤
│      .text (Flash/ROM)          │ ← Your code + constants
└─────────────────────────────────┘ Low Address (0x00000000)
```

---

## 📊 MEMORY SECTION DETAILS:

### 1️⃣ `.text` Section (Flash/ROM - Read-Only)

**Contains:**
- Your compiled code (instructions)
- Constant data (`const` variables)
- String literals

**Characteristics:**
- ✅ Non-volatile (survives power loss)
- ✅ Large size (256KB - 2MB typically)
- ❌ Read-only (can't modify at runtime)
- ❌ Slower than RAM

**Example:**
```c
const char message[] = "Hello";  // Stored in .text (Flash)

void myFunction() {
    // Function code stored in .text
}
```

---

### 2️⃣ `.data` Section (RAM - Initialized)

**Contains:**
- Global variables with initial values
- Static variables with initial values

**Characteristics:**
- ✅ Fast access (RAM speed)
- ✅ Read/Write
- ❌ Volatile (lost on power off)
- ❌ Uses precious RAM
- ⚠️ Initial values stored in Flash, copied to RAM at startup

**Example:**
```c
int globalVar = 100;           // .data (initialized)
static int counter = 0;        // .data (initialized)

void function() {
    static int callCount = 0;  // .data (initialized static local)
    callCount++;
}
```

---

### 3️⃣ `.bss` Section (RAM - Uninitialized/Zero)

**Contains:**
- Global variables without initial values
- Static variables without initial values
- Automatically zeroed at startup

**Characteristics:**
- ✅ Doesn't consume Flash (no initial values to store!)
- ✅ Fast RAM access
- ✅ Automatically initialized to 0
- ❌ Volatile (lost on power off)

**Example:**
```c
int uninitGlobal;              // .bss (zeroed at startup)
static int uninitStatic;       // .bss (zeroed at startup)

void function() {
    static int buffer[1024];   // .bss (large array, zeroed)
}
```

**💡 Tip:** Large arrays without initial values should go in .bss to save Flash!

---

### 4️⃣ STACK (RAM - Automatic)

**Contains:**
- Local variables
- Function parameters
- Return addresses
- CPU registers saved during function calls

**Characteristics:**
- ✅ Very fast (CPU managed)
- ✅ Automatic allocation/deallocation
- ✅ LIFO (Last In, First Out)
- ❌ Limited size (typically 4KB - 16KB)
- ❌ Stack overflow if exceeded!

**Example:**
```c
void function() {
    int localVar = 42;         // Stack
    char buffer[256];          // Stack (careful with large arrays!)
    
    anotherFunction();         // Return address pushed to stack
}  // localVar and buffer automatically freed
```

**⚠️ Warning:** Large arrays on stack can cause stack overflow!

---

### 5️⃣ HEAP (RAM - Dynamic)

**Contains:**
- Dynamically allocated memory (`malloc`, `calloc`)

**Characteristics:**
- ✅ Flexible size
- ✅ Long lifetime (until `free()`)
- ❌ Slower than stack
- ❌ Manual management required
- ❌ Risk of memory leaks
- ⚠️ Often NOT USED in embedded (too dangerous!)

**Example:**
```c
void function() {
    int *ptr = (int*)malloc(100 * sizeof(int));  // Heap
    
    // Use ptr...
    
    free(ptr);  // MUST free!
}
```

**💡 In embedded:** Avoid `malloc` - use static allocation!

---

## 💻 MEMORY EXERCISE:

**Identify where each variable is stored:**

```c
#include <stdint.h>

const char DEVICE_NAME[] = "STM32F303";     // ❓ Where?
int globalCounter = 0;                       // ❓ Where?
static int fileScope;                        // ❓ Where?

void processData(uint8_t *data) {            // ❓ data pointer where?
    static uint8_t buffer[256];              // ❓ buffer where?
    int temp = *data;                        // ❓ temp where?
    
    for (int i = 0; i < 10; i++) {          // ❓ i where?
        buffer[i] = data[i];
    }
}

int main(void) {
    uint8_t localArray[10];                  // ❓ localArray where?
    
    while(1) {
        processData(localArray);
    }
}
```

**Answers:**
```
DEVICE_NAME[]    → .text (Flash) - const string
globalCounter    → .data (RAM) - initialized global
fileScope        → .bss (RAM) - uninitialized static
data (pointer)   → Stack - function parameter
buffer[256]      → .bss (RAM) - static array
temp             → Stack - local variable
i                → Stack - loop counter
localArray[10]   → Stack - local array
```

---

## 🎯 Memory Best Practices for Embedded:

### ✅ DO:
1. Use `.bss` for large buffers (no initial value needed)
2. Use `const` for lookup tables (saves RAM)
3. Use `static` for persistent state
4. Keep stack usage small (avoid large local arrays)
5. Know your limits (check linker file!)

### ❌ DON'T:
1. Don't use `malloc`/`free` (heap fragmentation risk)
2. Don't put large arrays on stack (overflow!)
3. Don't initialize large arrays if not needed (.bss is better)
4. Don't forget `volatile` for hardware registers
5. Don't waste Flash with unnecessary initializations

---

## 📐 STM32F303 Memory Map:

```
Flash (256 KB):
  0x08000000 - 0x0803FFFF  ← Your code lives here!

SRAM (48 KB):
  0x20000000 - 0x2000BFFF  ← Your variables live here!

Peripherals:
  0x40000000 - 0x5FFFFFFF  ← GPIO, UART, etc. here!
```

---

# PART 4: APPLY TO YOUR STM32 CODE (20 mins)

Let's see where YOUR variables actually live!

## 🔍 Analyzing Your Day 3 Code:

```c
// From Day3_Final_7_Patterns.c

// Pin Definitions
#define BUTTON_PIN 0        // ❓ Where? → Nowhere! (preprocessor, replaced at compile time)

// Global Variables
uint8_t current_pattern = 0;   // ❓ Where? → .data (initialized global, in RAM)
uint8_t button_prev = 0;       // ❓ Where? → .data (initialized global, in RAM)

void pattern_clockwise_step(void) {
    static uint8_t step = 0;   // ❓ Where? → .data (static, persists between calls)
    
    all_leds_off();            // ❓ Function code where? → .text (Flash)
    
    switch(step) {             // ❓ step where? → Already in .data (static)
        case 0: GPIOE_ODR |= (1 << LED_NORTH); break;
    }
    
    step++;                    // ❓ Modifying RAM (.data section)
}

void pattern_random_chaos(void) {
    static uint32_t random = 123;  // ❓ Where? → .data (initialized static)
    
    uint8_t led_pins[8] = {8, 9, 10, 11, 12, 13, 14, 15};  
    // ❓ Where? → Stack (local array, created each call!)
    
    for (int i = 0; i < 8; i++) {  // ❓ i where? → Stack (loop counter)
        // ...
    }
}
```

---

## 💡 Optimization Opportunity!

**Current code:**
```c
void pattern_random_chaos(void) {
    uint8_t led_pins[8] = {8, 9, 10, 11, 12, 13, 14, 15};  // Created every call!
}
```

**Optimized:**
```c
const uint8_t LED_PINS[8] = {8, 9, 10, 11, 12, 13, 14, 15};  // In Flash, once!

void pattern_random_chaos(void) {
    // Use LED_PINS directly - saves stack space!
}
```

**Benefits:**
- ✅ Saves RAM (not on stack)
- ✅ Faster (no array initialization each call)
- ✅ Less stack usage

---

## 🎯 DAY 4 SUMMARY:

### What You Learned:
1. ✅ **Pointers:** Address-of, dereference, pointer arithmetic
2. ✅ **Bit Manipulation:** Systematic set/clear/toggle/check operations
3. ✅ **Memory Sections:** .text, .data, .bss, stack, heap
4. ✅ **Where Variables Live:** Global, static, local, const
5. ✅ **Applied to STM32:** Understood your code's memory layout

### Key Takeaways:
- `const` → Flash (.text) - saves RAM!
- Initialized global/static → .data (RAM, but uses Flash for initial value)
- Uninitialized global/static → .bss (RAM, zeroed automatically)
- Local variables → Stack (fast but limited)
- Avoid `malloc` in embedded!

---

## 📝 TODAY'S HOMEWORK:

Create file: `day4_memory_practice.c`

```c
#include <stdio.h>
#include <stdint.h>

// Identify where each variable is stored and why

const char FIRMWARE_VERSION[] = "v1.0.0";  // ❓ Where?
uint32_t errorCount = 0;                   // ❓ Where?
static uint32_t bootCount;                 // ❓ Where?

void processBuffer(uint8_t *data, uint16_t size) {
    static uint8_t buffer[1024];           // ❓ Where?
    uint16_t checksum = 0;                 // ❓ Where?
    
    for (uint16_t i = 0; i < size; i++) {  // ❓ i where?
        buffer[i] = data[i];
        checksum += data[i];
    }
}

int main(void) {
    uint8_t rxBuffer[64];                  // ❓ Where?
    
    while(1) {
        processBuffer(rxBuffer, 64);
    }
}
```

**Write down your answers and explanations!**

---

## ✅ DAY 4 CHECKLIST:

- [ ] Completed pointer exercises (swap, findMax, strlen)
- [ ] Completed bit manipulation exercises (set, clear, toggle, check, count, extract)
- [ ] Understood all 5 memory sections
- [ ] Analyzed your STM32 code memory layout
- [ ] Identified optimization opportunities
- [ ] Ready to commit code to GitHub

---

**Total Time:** ~2 hours  
**Knowledge Gained:** MASSIVE! You now understand the complete memory picture! 🎉

---

**Next Steps:**
1. Complete the homework
2. Commit everything to GitHub
3. Tomorrow: Continue with original Week 1 plan OR more hardware practice!

---

*Day 4 Complete - Theory + Hardware Connected!* 🚀

