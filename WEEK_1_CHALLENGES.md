# 🔥 WEEK 1 MASTERY CHALLENGES

**Goal:** Test the DEPTH of your Week 1 knowledge  
**Difficulty:** Medium → Hard → Very Hard  
**Time:** 2-4 hours (if you attempt all)  
**Rules:** Try on your own first, then check solutions!

---

## 📊 CHALLENGE CATEGORIES:

1. **Bit Manipulation Challenges** (3 problems)
2. **Pointer Challenges** (3 problems)
3. **Hardware Challenges** (3 problems)
4. **Memory & Keywords** (3 problems)
5. **Integration Challenge** (1 BOSS challenge)

**Total: 13 Challenges**

---

# 🎯 PART 1: BIT MANIPULATION CHALLENGES

---

## ⭐ CHALLENGE 1.1: Reverse Bits (MEDIUM)

**Problem:**  
Write a function that reverses the bits in a byte.

**Example:**
```
Input:  0b10110100 (0xB4)
Output: 0b00101101 (0x2D)
```

**Function Signature:**
```c
uint8_t reverseBits(uint8_t byte) {
    // Your code here
}
```

**Hint:** Loop through bits, build result from right to left.

**Test Cases:**
```c
reverseBits(0b10110100) == 0b00101101  // 0xB4 → 0x2D
reverseBits(0b11110000) == 0b00001111  // 0xF0 → 0x0F
reverseBits(0b10101010) == 0b01010101  // 0xAA → 0x55
```

---

## ⭐⭐ CHALLENGE 1.2: Count Consecutive 1s (HARD)

**Problem:**  
Find the length of the longest consecutive sequence of 1s in a 32-bit number.

**Example:**
```
Input:  0b00011110001111100000  (has sequences of 4 and 5 ones)
Output: 5 (longest sequence)
```

**Function Signature:**
```c
uint8_t longestOnesSequence(uint32_t num) {
    // Your code here
}
```

**Hint:** Track current streak and max streak while scanning bits.

**Test Cases:**
```c
longestOnesSequence(0b00011110001111100000) == 5
longestOnesSequence(0b11111111) == 8
longestOnesSequence(0b10101010) == 1
longestOnesSequence(0b00000000) == 0
```

---

## ⭐⭐⭐ CHALLENGE 1.3: Swap Nibbles Without Temp (VERY HARD)

**Problem:**  
Swap the upper and lower nibbles of a byte **using only bit operations** (no temp variable, no array).

**Example:**
```
Input:  0xA3 (1010 0011)
Output: 0x3A (0011 1010)
        Upper nibble (A) and lower nibble (3) swapped
```

**Function Signature:**
```c
uint8_t swapNibbles(uint8_t byte) {
    // Your code here - ONE line solution exists!
}
```

**Constraint:** Must be done in **one or two operations** (no loops, no temp variables).

**Hint:** Think about bit shifting and OR operations.

**Test Cases:**
```c
swapNibbles(0xA3) == 0x3A
swapNibbles(0xF0) == 0x0F
swapNibbles(0x12) == 0x21
```

---

# 🧠 PART 2: POINTER CHALLENGES

---

## ⭐ CHALLENGE 2.1: Array Sum via Pointer (MEDIUM)

**Problem:**  
Calculate the sum of an array using **only pointer arithmetic** (no array indexing `arr[i]` allowed!).

**Function Signature:**
```c
int arraySum(int *arr, int size) {
    // Your code here
    // RULE: Cannot use arr[i], must use *(arr + i) or *arr++
}
```

**Test Cases:**
```c
int arr1[] = {1, 2, 3, 4, 5};
arraySum(arr1, 5) == 15

int arr2[] = {10, -5, 3};
arraySum(arr2, 3) == 8
```

---

## ⭐⭐ CHALLENGE 2.2: String Reverse In-Place (HARD)

**Problem:**  
Reverse a string **in-place** using two pointers (start and end).

**Function Signature:**
```c
void reverseString(char *str) {
    // Your code here
    // Must modify original string, no extra memory
}
```

**Hint:** Two pointers: one at start, one at end. Swap and move toward middle.

**Test Cases:**
```c
char str1[] = "Hello";
reverseString(str1);
// str1 is now "olleH"

char str2[] = "STM32";
reverseString(str2);
// str2 is now "23MTS"
```

---

## ⭐⭐⭐ CHALLENGE 2.3: Pointer to Function Array (VERY HARD)

**Problem:**  
Create an array of **function pointers** to your LED patterns, then call them via pointer indexing.

**Function Signature:**
```c
// Define function pointer type
typedef void (*PatternFunc)(void);

// Create array of function pointers
PatternFunc patterns[7] = {
    pattern_clockwise_step,
    pattern_counter_clockwise_step,
    // ... etc
};

// Call pattern via pointer
void runPattern(uint8_t index) {
    // Your code here - call the pattern using function pointer
}
```

**Goal:** Understand function pointers (used heavily in automotive embedded systems!).

**Test:**
```c
runPattern(0);  // Calls pattern_clockwise_step()
runPattern(4);  // Calls pattern_knight_rider()
```

**Bonus:** Modify your Day 3 code to use this approach!

---

# 🔧 PART 3: HARDWARE CHALLENGES

---

## ⭐ CHALLENGE 3.1: Toggle Multiple LEDs Atomically (MEDIUM)

**Problem:**  
Toggle **3 specific LEDs** in a **single register write** (not 3 separate writes).

**Requirement:**  
Toggle LEDs on pins 9, 11, and 15 using **one line** of code.

**Your Code:**
```c
// ❌ BAD - 3 register writes
GPIOE_ODR ^= (1 << 9);
GPIOE_ODR ^= (1 << 11);
GPIOE_ODR ^= (1 << 15);

// ✅ GOOD - 1 register write
GPIOE_ODR ^= ???;  // Fill this in
```

**Why it matters:** Atomic operations are critical in embedded systems to avoid race conditions.

---

## ⭐⭐ CHALLENGE 3.2: Button Double-Press Detection (HARD)

**Problem:**  
Detect when the button is pressed **twice within 500ms** (double-click detection).

**Requirements:**
- Single press → Do nothing
- Double press (within 500ms) → Trigger action
- If second press is > 500ms after first → Count as new single press

**Pseudo-code to implement:**
```c
uint8_t detectDoublePress(void) {
    // Your state machine here
    // Return 1 if double press detected, 0 otherwise
}
```

**Hint:** Track first press time, detect second press within window.

**Test:** Press button twice quickly → Should detect double press.

---

## ⭐⭐⭐ CHALLENGE 3.3: LED PWM via Software (VERY HARD)

**Problem:**  
Create **software PWM** to dim an LED without using hardware timers.

**Requirements:**
- Brightness levels: 0% (off), 25%, 50%, 75%, 100% (full)
- Use a counter in your main loop
- Achieve smooth dimming effect

**Algorithm:**
```c
void softwarePWM(uint8_t brightness) {
    // brightness: 0-100 (percentage)
    // Your code here
    // Hint: Use a counter from 0-99, turn LED on/off based on brightness
}
```

**Example:**
- 50% brightness: LED on for 50 counts, off for 50 counts (per 100-count cycle)
- 75% brightness: LED on for 75 counts, off for 25 counts

**Test:** Create a smooth breathing effect (fade in/out).

---

# 🧩 PART 4: MEMORY & KEYWORDS CHALLENGES

---

## ⭐ CHALLENGE 4.1: Predict Memory Layout (MEDIUM)

**Problem:**  
Given this code, predict where each variable is stored:

```c
const char VERSION[] = "v2.0.0";        // Where?
uint32_t bootCount = 5;                 // Where?
static uint8_t internalBuffer[512];     // Where?

void processData(void) {
    static uint32_t callCount = 0;      // Where?
    uint8_t tempBuffer[64];             // Where?
    const uint16_t TIMEOUT = 1000;      // Where?
    
    uint8_t *dynamicBuffer = malloc(128); // Where?
    
    callCount++;
    // ...
    free(dynamicBuffer);
}
```

**Your Answer:**
```
VERSION:           _______
bootCount:         _______
internalBuffer:    _______
callCount:         _______
tempBuffer:        _______
TIMEOUT:           _______
dynamicBuffer:     _______ (the pointer itself)
*dynamicBuffer:    _______ (the allocated memory)
```

**Options:** Flash (.text), .data, .bss, Stack, Heap

---

## ⭐⭐ CHALLENGE 4.2: Fix the Volatile Bug (HARD)

**Problem:**  
This code has a bug. Find it and fix it!

```c
// Hardware status register
uint32_t *STATUS_REG = (uint32_t*)0x40021000;

void waitForReady(void) {
    // Wait until bit 0 is set
    while (!(*STATUS_REG & 0x01)) {
        // Waiting...
    }
    printf("Ready!\n");
}
```

**Issue:** This might create an **infinite loop** with optimization enabled!

**Your Task:**
1. Identify the bug
2. Fix it using the correct keyword
3. Explain WHY it's needed

---

## ⭐⭐⭐ CHALLENGE 4.3: Const Pointer Quiz (VERY HARD)

**Problem:**  
For each declaration, state what CAN and CANNOT be modified:

```c
// 1.
const int *ptr1 = &value;

// 2.
int * const ptr2 = &value;

// 3.
const int * const ptr3 = &value;

// 4.
volatile uint32_t * const ptr4 = (volatile uint32_t*)0x40020C14;

// 5.
const volatile uint32_t * const ptr5 = (const volatile uint32_t*)0x40020C10;
```

**Your Answer:**
```
1. Can change: _______   Cannot change: _______
2. Can change: _______   Cannot change: _______
3. Can change: _______   Cannot change: _______
4. Can change: _______   Cannot change: _______
5. Can change: _______   Cannot change: _______
```

**Hint:** Read from RIGHT to LEFT!

---

# 🏆 PART 5: BOSS CHALLENGE - INTEGRATION

---

## ⭐⭐⭐⭐ BOSS CHALLENGE: Morse Code SOS Beacon (ULTRA HARD)

**Problem:**  
Implement a **Morse Code SOS beacon** on your STM32 board.

**Requirements:**

1. **Morse Code Timing:**
   - Dot (·) = 200ms ON
   - Dash (─) = 600ms ON
   - Gap between symbols = 200ms OFF
   - Gap between letters = 600ms OFF
   - Gap between words = 1400ms OFF

2. **SOS Pattern:**
   ```
   S = · · ·    (3 dots)
   O = ─ ─ ─    (3 dashes)
   S = · · ·    (3 dots)
   ```

3. **Features to Implement:**
   - LED blinks SOS pattern continuously
   - Button press toggles beacon ON/OFF
   - Use state machine for timing
   - Use proper `static` variables for state persistence

4. **Advanced (BONUS):**
   - Add a second LED that blinks opposite to main LED
   - Add button long-press (> 2 seconds) to change speed (slow/fast)
   - Use software PWM for "breathing" effect during dashes

**Code Structure:**
```c
typedef enum {
    MORSE_DOT,
    MORSE_DASH,
    MORSE_GAP_SYMBOL,
    MORSE_GAP_LETTER,
    MORSE_GAP_WORD
} MorseState;

void morseSOS(void) {
    static MorseState state = MORSE_DOT;
    static uint8_t symbol_count = 0;
    static uint8_t letter_count = 0;
    
    // Your implementation here
}
```

**Success Criteria:**
- ✅ Correct SOS timing
- ✅ Clean state machine implementation
- ✅ Button control works
- ✅ Code is readable and commented

**This challenge combines:**
- GPIO (LEDs + Button)
- Timing and delays
- State machines
- Bit manipulation
- Static variables
- Button debouncing
- Pattern generation

**Good luck!** 🚀

---

# 📝 ANSWER KEY & SOLUTIONS

## 🔒 SEALED UNTIL YOU TRY!

Solutions are provided below, but **TRY FIRST** before looking!

---

<details>
<summary><b>💡 SOLUTION 1.1: Reverse Bits</b></summary>

```c
uint8_t reverseBits(uint8_t byte) {
    uint8_t result = 0;
    
    for (int i = 0; i < 8; i++) {
        // Extract bit from byte
        uint8_t bit = (byte >> i) & 1;
        
        // Place bit in reversed position
        result |= (bit << (7 - i));
    }
    
    return result;
}
```

**Explanation:**
- Loop through each bit (0-7)
- Extract bit at position `i`
- Place it at position `7-i` in result
- Time: O(8) = O(1)

</details>

---

<details>
<summary><b>💡 SOLUTION 1.2: Count Consecutive 1s</b></summary>

```c
uint8_t longestOnesSequence(uint32_t num) {
    uint8_t max_count = 0;
    uint8_t current_count = 0;
    
    while (num) {
        if (num & 1) {
            // Current bit is 1
            current_count++;
            if (current_count > max_count) {
                max_count = current_count;
            }
        } else {
            // Current bit is 0, reset streak
            current_count = 0;
        }
        
        num >>= 1;  // Move to next bit
    }
    
    return max_count;
}
```

**Explanation:**
- Track current streak and max streak
- When we hit a 1, increment current streak
- When we hit a 0, reset current streak
- Keep track of maximum

</details>

---

<details>
<summary><b>💡 SOLUTION 1.3: Swap Nibbles</b></summary>

```c
uint8_t swapNibbles(uint8_t byte) {
    return ((byte & 0x0F) << 4) | ((byte & 0xF0) >> 4);
}
```

**Explanation:**
- `(byte & 0x0F) << 4` - Extract lower nibble, shift to upper
- `(byte & 0xF0) >> 4` - Extract upper nibble, shift to lower
- OR them together

**Example:**
```
Input: 0xA3 = 1010 0011

Lower nibble: 0xA3 & 0x0F = 0000 0011 = 0x03
Shift left:   0x03 << 4   = 0011 0000 = 0x30

Upper nibble: 0xA3 & 0xF0 = 1010 0000 = 0xA0
Shift right:  0xA0 >> 4   = 0000 1010 = 0x0A

Combine:      0x30 | 0x0A = 0011 1010 = 0x3A ✅
```

</details>

---

<details>
<summary><b>💡 SOLUTION 2.1: Array Sum via Pointer</b></summary>

```c
int arraySum(int *arr, int size) {
    int sum = 0;
    int *end = arr + size;  // Pointer to one past end
    
    while (arr < end) {
        sum += *arr;  // Add current element
        arr++;        // Move pointer forward
    }
    
    return sum;
}

// Alternative using pointer arithmetic:
int arraySum(int *arr, int size) {
    int sum = 0;
    
    for (int i = 0; i < size; i++) {
        sum += *(arr + i);  // Pointer arithmetic instead of arr[i]
    }
    
    return sum;
}
```

</details>

---

<details>
<summary><b>💡 SOLUTION 2.2: String Reverse In-Place</b></summary>

```c
void reverseString(char *str) {
    if (!str) return;  // Null check
    
    char *start = str;
    char *end = str;
    
    // Find end of string
    while (*end != '\0') {
        end++;
    }
    end--;  // Move back to last character (not null terminator)
    
    // Swap from both ends toward middle
    while (start < end) {
        // Swap characters
        char temp = *start;
        *start = *end;
        *end = temp;
        
        start++;  // Move toward middle
        end--;    // Move toward middle
    }
}
```

**Explanation:**
- Two pointers: start and end
- Swap characters and move toward middle
- Stop when pointers meet
- Time: O(n/2) = O(n)
- Space: O(1) - in-place!

</details>

---

<details>
<summary><b>💡 SOLUTION 2.3: Function Pointer Array</b></summary>

```c
// Define function pointer type
typedef void (*PatternFunc)(void);

// Create array of function pointers
PatternFunc patterns[7] = {
    pattern_clockwise_step,
    pattern_counter_clockwise_step,
    pattern_ping_pong,
    pattern_all_blink,
    pattern_knight_rider,
    pattern_binary_counter,
    pattern_random_chaos
};

// Call pattern via pointer
void runPattern(uint8_t index) {
    if (index < 7) {
        patterns[index]();  // Call function through pointer
    }
}

// Your main loop can now be:
int main(void) {
    // ... setup ...
    
    while (1) {
        if (button_pressed) {
            current_pattern = (current_pattern + 1) % 7;
        }
        
        runPattern(current_pattern);  // Clean!
        delay_ms(PATTERN_SPEED);
    }
}
```

**Why this is better:**
- Cleaner code (no giant switch statement)
- Easy to add new patterns (just add to array)
- Used in real embedded systems (callback tables, interrupt vectors)

</details>

---

<details>
<summary><b>💡 SOLUTION 3.1: Toggle Multiple LEDs Atomically</b></summary>

```c
// Toggle LEDs on pins 9, 11, and 15 in ONE write
GPIOE_ODR ^= ((1 << 9) | (1 << 11) | (1 << 15));
```

**Explanation:**
- Create a mask with all 3 bits set
- Single XOR operation toggles all 3 simultaneously
- **Atomic** - no risk of being interrupted mid-toggle

**Why it matters:**
In an interrupt-driven system, if you did 3 separate toggles, an interrupt could fire between them, causing inconsistent state!

</details>

---

<details>
<summary><b>💡 SOLUTION 3.2: Button Double-Press Detection</b></summary>

```c
#define DOUBLE_PRESS_WINDOW 500  // 500ms

uint8_t detectDoublePress(void) {
    static uint8_t press_count = 0;
    static uint32_t first_press_time = 0;
    static uint8_t last_button_state = 0;
    
    uint8_t current_button = read_button_debounced();
    
    // Detect rising edge (button press)
    if (current_button && !last_button_state) {
        uint32_t now = get_time_ms();
        
        if (press_count == 0) {
            // First press
            press_count = 1;
            first_press_time = now;
        } else if (press_count == 1) {
            // Second press - check timing
            if ((now - first_press_time) <= DOUBLE_PRESS_WINDOW) {
                // Double press detected!
                press_count = 0;
                last_button_state = current_button;
                return 1;  // DOUBLE PRESS!
            } else {
                // Too late, count as new first press
                press_count = 1;
                first_press_time = now;
            }
        }
    }
    
    // Timeout: reset if window passed
    if (press_count == 1) {
        uint32_t now = get_time_ms();
        if ((now - first_press_time) > DOUBLE_PRESS_WINDOW) {
            press_count = 0;  // Single press (timeout)
        }
    }
    
    last_button_state = current_button;
    return 0;  // No double press
}
```

</details>

---

<details>
<summary><b>💡 SOLUTION 3.3: LED Software PWM</b></summary>

```c
void softwarePWM(uint8_t led_pin, uint8_t brightness) {
    // brightness: 0-100 (percentage)
    static uint8_t counter = 0;
    
    // Counter cycles from 0-99 (100 steps)
    counter++;
    if (counter >= 100) {
        counter = 0;
    }
    
    // Turn LED on if counter < brightness
    if (counter < brightness) {
        GPIOE_ODR |= (1 << led_pin);   // LED ON
    } else {
        GPIOE_ODR &= ~(1 << led_pin);  // LED OFF
    }
}

// BONUS: Breathing effect
void breathingEffect(uint8_t led_pin) {
    static uint8_t brightness = 0;
    static int8_t direction = 1;  // +1 = increasing, -1 = decreasing
    
    // Fade in/out
    brightness += direction;
    
    // Reverse at limits
    if (brightness == 100) direction = -1;
    if (brightness == 0) direction = +1;
    
    softwarePWM(led_pin, brightness);
}
```

**Usage in main loop:**
```c
while (1) {
    softwarePWM(9, 50);  // 50% brightness
    delay_us(100);        // Call frequently for smooth PWM
}
```

</details>

---

<details>
<summary><b>💡 SOLUTION 4.1: Predict Memory Layout</b></summary>

```
VERSION:           Flash (.text)    - const char array
bootCount:         .data             - initialized global
internalBuffer:    .bss              - static uninitialized array
callCount:         .data (or .bss)   - static initialized to 0 (some compilers .bss)
tempBuffer:        Stack             - local array
TIMEOUT:           Stack (or optimized away) - const local
dynamicBuffer:     Stack             - the pointer variable itself
*dynamicBuffer:    Heap              - the allocated memory
```

**Key Points:**
- `const` at file scope → Flash
- Initialized globals → .data
- Uninitialized globals/static → .bss
- Local variables → Stack
- `malloc()` → Heap

</details>

---

<details>
<summary><b>💡 SOLUTION 4.2: Fix the Volatile Bug</b></summary>

**Bug:** Missing `volatile` keyword!

**Fixed Code:**
```c
// Hardware status register
volatile uint32_t *STATUS_REG = (volatile uint32_t*)0x40021000;
//       ^^^^^^^^

void waitForReady(void) {
    // Wait until bit 0 is set
    while (!(*STATUS_REG & 0x01)) {
        // Waiting...
    }
    printf("Ready!\n");
}
```

**Explanation:**

Without `volatile`, the compiler might optimize to:
```c
// Compiler thinks: "STATUS_REG never changes in this function"
uint32_t temp = *STATUS_REG;  // Read once
while (!(temp & 0x01)) {       // Check cached value forever
    // INFINITE LOOP! Never re-reads register!
}
```

With `volatile`, compiler MUST re-read every time:
```c
// Forces re-read from hardware every iteration
while (!(*STATUS_REG & 0x01)) {
    // Actually checks hardware register each time ✅
}
```

</details>

---

<details>
<summary><b>💡 SOLUTION 4.3: Const Pointer Quiz</b></summary>

**Read from RIGHT to LEFT!**

```c
// 1. const int *ptr1 = &value;
//    ptr1 is a POINTER to a CONST INT
Can change: ptr1 (the pointer itself)
Cannot change: *ptr1 (the value it points to)
Example:
  ptr1 = &other;   // ✅ OK
  *ptr1 = 10;      // ❌ ERROR

// 2. int * const ptr2 = &value;
//    ptr2 is a CONST POINTER to an INT
Can change: *ptr2 (the value it points to)
Cannot change: ptr2 (the pointer itself)
Example:
  ptr2 = &other;   // ❌ ERROR
  *ptr2 = 10;      // ✅ OK

// 3. const int * const ptr3 = &value;
//    ptr3 is a CONST POINTER to a CONST INT
Can change: NOTHING
Cannot change: ptr3 AND *ptr3
Example:
  ptr3 = &other;   // ❌ ERROR
  *ptr3 = 10;      // ❌ ERROR

// 4. volatile uint32_t * const ptr4 = (volatile uint32_t*)0x40020C14;
//    ptr4 is a CONST POINTER to a VOLATILE UINT32
//    (typical for hardware output register like GPIO_ODR)
Can change: *ptr4 (write to register)
Cannot change: ptr4 (register address)
Example:
  ptr4 = other_address;  // ❌ ERROR (can't change address)
  *ptr4 = 0xFF;          // ✅ OK (can write to register)

// 5. const volatile uint32_t * const ptr5 = (const volatile uint32_t*)0x40020C10;
//    ptr5 is a CONST POINTER to a CONST VOLATILE UINT32
//    (typical for hardware input register like GPIO_IDR)
Can change: NOTHING (read-only register)
Cannot change: ptr5 AND *ptr5
Example:
  ptr5 = other_address;  // ❌ ERROR
  *ptr5 = 0xFF;          // ❌ ERROR (read-only register!)
  uint32_t val = *ptr5;  // ✅ OK (can read)
```

**Embedded Usage:**
```c
// GPIO Output Register (read/write)
volatile uint32_t * const GPIOE_ODR = (volatile uint32_t*)0x40020C14;

// GPIO Input Register (read-only)
volatile const uint32_t * const GPIOE_IDR = (volatile const uint32_t*)0x40020C10;
```

</details>

---

<details>
<summary><b>💡 SOLUTION BOSS: Morse Code SOS (Outline)</b></summary>

```c
#include <stdint.h>

// Timing constants (ms)
#define DOT_DURATION      200
#define DASH_DURATION     600
#define SYMBOL_GAP        200
#define LETTER_GAP        600
#define WORD_GAP          1400

// State machine
typedef enum {
    MORSE_S1_DOT1,    // S: dot 1
    MORSE_S1_DOT2,    // S: dot 2
    MORSE_S1_DOT3,    // S: dot 3
    MORSE_S1_LETTER_GAP,
    
    MORSE_O_DASH1,    // O: dash 1
    MORSE_O_DASH2,    // O: dash 2
    MORSE_O_DASH3,    // O: dash 3
    MORSE_O_LETTER_GAP,
    
    MORSE_S2_DOT1,    // S: dot 1
    MORSE_S2_DOT2,    // S: dot 2
    MORSE_S2_DOT3,    // S: dot 3
    MORSE_S2_WORD_GAP,
    
    MORSE_IDLE
} MorseState;

void morseSOS(uint8_t led_pin) {
    static MorseState state = MORSE_S1_DOT1;
    static uint32_t state_start_time = 0;
    uint32_t now = get_time_ms();
    uint32_t elapsed = now - state_start_time;
    
    switch (state) {
        case MORSE_S1_DOT1:
        case MORSE_S1_DOT2:
        case MORSE_S1_DOT3:
        case MORSE_S2_DOT1:
        case MORSE_S2_DOT2:
        case MORSE_S2_DOT3:
            // Dot: LED ON for 200ms, then gap
            if (elapsed < DOT_DURATION) {
                GPIOE_ODR |= (1 << led_pin);  // ON
            } else if (elapsed < DOT_DURATION + SYMBOL_GAP) {
                GPIOE_ODR &= ~(1 << led_pin);  // OFF (gap)
            } else {
                // Move to next state
                state++;
                state_start_time = now;
            }
            break;
            
        case MORSE_O_DASH1:
        case MORSE_O_DASH2:
        case MORSE_O_DASH3:
            // Dash: LED ON for 600ms, then gap
            if (elapsed < DASH_DURATION) {
                GPIOE_ODR |= (1 << led_pin);  // ON
            } else if (elapsed < DASH_DURATION + SYMBOL_GAP) {
                GPIOE_ODR &= ~(1 << led_pin);  // OFF (gap)
            } else {
                // Move to next state
                state++;
                state_start_time = now;
            }
            break;
            
        case MORSE_S1_LETTER_GAP:
        case MORSE_O_LETTER_GAP:
            // Letter gap: OFF for 600ms
            GPIOE_ODR &= ~(1 << led_pin);
            if (elapsed >= LETTER_GAP) {
                state++;
                state_start_time = now;
            }
            break;
            
        case MORSE_S2_WORD_GAP:
            // Word gap: OFF for 1400ms, then restart
            GPIOE_ODR &= ~(1 << led_pin);
            if (elapsed >= WORD_GAP) {
                state = MORSE_S1_DOT1;  // Restart SOS
                state_start_time = now;
            }
            break;
            
        case MORSE_IDLE:
            // Beacon off
            GPIOE_ODR &= ~(1 << led_pin);
            break;
    }
}

// Main loop
int main(void) {
    // ... GPIO setup ...
    
    uint8_t beacon_enabled = 0;
    
    while (1) {
        // Button toggles beacon
        if (button_pressed_debounced()) {
            beacon_enabled = !beacon_enabled;
        }
        
        // Run beacon
        if (beacon_enabled) {
            morseSOS(9);  // LED on PE9
        } else {
            GPIOE_ODR &= ~(1 << 9);  // Turn off
        }
        
        delay_ms(10);  // Poll frequently
    }
}
```

**This is COMPLETE embedded system design!** 🎖️

</details>

---

# ✅ CHALLENGE CHECKLIST:

Track your progress:

**Bit Manipulation:**
- [ ] Challenge 1.1 - Reverse Bits
- [ ] Challenge 1.2 - Count Consecutive 1s
- [ ] Challenge 1.3 - Swap Nibbles

**Pointers:**
- [ ] Challenge 2.1 - Array Sum
- [ ] Challenge 2.2 - String Reverse
- [ ] Challenge 2.3 - Function Pointers

**Hardware:**
- [ ] Challenge 3.1 - Atomic Toggle
- [ ] Challenge 3.2 - Double Press
- [ ] Challenge 3.3 - Software PWM

**Memory & Keywords:**
- [ ] Challenge 4.1 - Memory Layout
- [ ] Challenge 4.2 - Volatile Bug
- [ ] Challenge 4.3 - Const Pointer Quiz

**Boss Challenge:**
- [ ] Morse Code SOS Beacon

---

# 🎯 SCORING:

- **0-5 challenges:** Good start, review concepts
- **6-9 challenges:** Solid understanding
- **10-12 challenges:** Excellent mastery
- **All 13 + Boss:** **WEEK 1 MASTER!** 🏆

---

**Good luck! Take your time, and remember:** *Struggling is learning!* 💪

**Post your progress or questions!** 🚀

---

*These challenges are designed to push you. If you complete even half, you're ready for Week 2!*

