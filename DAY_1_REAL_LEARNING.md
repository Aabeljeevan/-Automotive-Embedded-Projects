# 🚀 DAY 1 - Your First Embedded C Code!

**Date:** January 13, 2026  
**Time Needed:** 90 minutes  
**Goal:** Understand embedded C fundamentals and write your first program!

---

## 🎯 Today's Mission:

1. Understand what makes embedded C different from regular C
2. Master bit manipulation (the heart of embedded programming)
3. Write and understand your first embedded program
4. Learn about registers and hardware control

**By the end of today, you'll know more embedded C than 90% of software engineers!**

---

## Part 1: What Makes Embedded C Special? (15 mins)

### Regular C vs Embedded C

**Regular C (PC):**
```c
#include <stdio.h>
int main() {
    printf("Hello World\n");  // OS handles everything!
    return 0;
}
```

**Embedded C (Microcontroller):**
```c
// NO operating system! You control hardware DIRECTLY!

#define LED_PORT *((volatile uint32_t*)0x40020C14)  // Direct memory address!

void delay(int count) {
    for(int i = 0; i < count; i++);  // No sleep() function!
}

int main() {
    LED_PORT = 0x01;  // Turn ON LED by writing to hardware register
    while(1) {        // Loop forever (no OS to return to!)
        delay(100000);
    }
}
```

**KEY DIFFERENCES:**
- ❌ No `printf()` - no screen connected!
- ❌ No OS - you ARE the operating system!
- ✅ Direct hardware access via memory addresses
- ✅ Infinite loops are normal (`while(1)`)
- ✅ You control EVERY bit of hardware

---

## Part 2: Bit Manipulation Mastery (30 mins)

**THIS IS THE #1 SKILL FOR EMBEDDED!**

### Why Bits Matter in Embedded:

In embedded systems, EVERYTHING is controlled by bits:
- Want to turn on LED? **Set bit 3 to 1**
- Want to check if button pressed? **Read bit 5**
- Want to configure UART? **Set bits 2-4 to 101**

### The 4 Essential Bit Operations:

#### 1️⃣ **SET a Bit (Turn ON)**

```c
// Set bit 3 to 1 (all other bits unchanged)
uint8_t status = 0b00000000;  // Binary: all bits OFF
status = status | (1 << 3);   // Set bit 3
// Result: 0b00001000 (bit 3 is now ON)

// Real example: Turn ON LED connected to pin 3
LED_PORT = LED_PORT | (1 << 3);
// Shortcut:
LED_PORT |= (1 << 3);
```

**What's happening?**
- `1 << 3` means shift 1 left by 3 positions: `0b00001000`
- `|` is OR operation: keeps existing bits, sets new bit to 1

#### 2️⃣ **CLEAR a Bit (Turn OFF)**

```c
// Clear bit 3 to 0 (all other bits unchanged)
uint8_t status = 0b00001111;  // Binary: bits 0-3 ON
status = status & ~(1 << 3);  // Clear bit 3
// Result: 0b00000111 (bit 3 is now OFF)

// Real example: Turn OFF LED connected to pin 3
LED_PORT &= ~(1 << 3);
```

**What's happening?**
- `1 << 3` = `0b00001000`
- `~(1 << 3)` = `0b11110111` (inverts: all 1s except bit 3)
- `&` is AND operation: clears the target bit

#### 3️⃣ **TOGGLE a Bit (Flip ON/OFF)**

```c
// Toggle bit 3 (if 1 make 0, if 0 make 1)
status = status ^ (1 << 3);

// Real example: Blink LED
LED_PORT ^= (1 << 3);  // LED was ON? Now OFF. Was OFF? Now ON.
```

**What's happening?**
- `^` is XOR operation: flips the bit

#### 4️⃣ **CHECK a Bit (Read status)**

```c
// Check if bit 3 is set (is it 1 or 0?)
uint8_t status = 0b00001100;

if (status & (1 << 3)) {
    // Bit 3 is ON (1)
} else {
    // Bit 3 is OFF (0)
}

// Real example: Check if button pressed
if (BUTTON_PORT & (1 << 5)) {
    // Button is pressed!
}
```

---

### 🧠 PRACTICE EXERCISES - DO THESE NOW!

Open a text file and work through these BY HAND:

**Exercise 1:**
```c
uint8_t value = 0b00110010;  // Starting value

// 1. Set bit 0 (result = ?)
// 2. Clear bit 5 (result = ?)
// 3. Toggle bit 1 (result = ?)
// 4. Check if bit 4 is set (Yes/No?)
```

<details>
<summary>Click for answers after you try!</summary>

```c
uint8_t value = 0b00110010;  // = 50 decimal

// 1. Set bit 0
value |= (1 << 0);
// Result: 0b00110011 = 51

// 2. Clear bit 5
value &= ~(1 << 5);
// Result: 0b00010011 = 19

// 3. Toggle bit 1
value ^= (1 << 1);
// Result: 0b00010001 = 17

// 4. Check if bit 4 is set
if (value & (1 << 4)) {
    // YES! Bit 4 is 1
}
```
</details>

---

## Part 3: Your First Real Embedded Program (30 mins)

### Understanding LED Blink (The "Hello World" of Embedded)

This is the FIRST program you'll run on your STM32 board when it arrives!

```c
/* 
 * LED Blink - STM32F407 Discovery Board
 * Green LED connected to PD12 (Port D, Pin 12)
 */

#include "stm32f4xx.h"  // STM32F407 register definitions

// Register addresses (you'll learn these in detail later)
#define RCC_AHB1ENR   *((volatile uint32_t*)0x40023830)
#define GPIOD_MODER   *((volatile uint32_t*)0x40020C00)
#define GPIOD_ODR     *((volatile uint32_t*)0x40020C14)

void delay(int count) {
    // Simple delay loop
    for(volatile int i = 0; i < count; i++);
}

int main(void) {
    // Step 1: Enable clock for GPIO Port D
    RCC_AHB1ENR |= (1 << 3);  // Set bit 3 to enable GPIOD clock
    
    // Step 2: Configure PD12 as OUTPUT
    GPIOD_MODER |= (1 << 24);   // Set bit 24
    GPIOD_MODER &= ~(1 << 25);  // Clear bit 25
    // Result: bits [25:24] = 01 = Output mode
    
    // Step 3: Infinite loop - blink LED
    while(1) {
        GPIOD_ODR ^= (1 << 12);  // Toggle LED on PD12
        delay(1000000);          // Wait ~500ms
    }
}
```

---

### 🔍 Line-by-Line Breakdown:

#### **Line 1: Enable Clock**
```c
RCC_AHB1ENR |= (1 << 3);
```
- Every peripheral needs POWER (clock)
- RCC = Reset and Clock Control
- Bit 3 controls GPIOD clock
- **Think:** Like plugging in a device before using it!

#### **Line 2-3: Configure Pin as Output**
```c
GPIOD_MODER |= (1 << 24);   // Set bit 24
GPIOD_MODER &= ~(1 << 25);  // Clear bit 25
```
- Each pin can be INPUT or OUTPUT
- MODER register controls this
- 2 bits per pin: `01` = Output, `00` = Input
- Pin 12 uses bits [25:24]

#### **Line 4: Toggle LED**
```c
GPIOD_ODR ^= (1 << 12);
```
- ODR = Output Data Register
- Each bit controls one pin
- XOR toggles the bit (ON→OFF, OFF→ON)

---

## Part 4: Understanding `volatile` (15 mins)

**CRITICAL EMBEDDED CONCEPT!**

### What is `volatile`?

```c
volatile uint32_t *led_register = (uint32_t*)0x40020C14;
```

**`volatile` tells the compiler:**
> "This variable can change OUTSIDE of my C code - DON'T optimize it!"

### Why It Matters:

**WITHOUT volatile:**
```c
uint32_t *reg = (uint32_t*)0x40020C14;
*reg = 1;  // Turn ON LED
*reg = 1;  // Turn ON LED again
*reg = 1;  // Turn ON LED again

// Compiler thinks: "Why write 1 three times? I'll optimize to just once!"
// Result: LED might not blink correctly!
```

**WITH volatile:**
```c
volatile uint32_t *reg = (uint32_t*)0x40020C14;
*reg = 1;
*reg = 1;
*reg = 1;

// Compiler thinks: "It's volatile! Hardware might need all 3 writes!"
// Result: All 3 writes happen as expected
```

**RULE:** 
- Always use `volatile` for hardware registers!
- Always use `volatile` for variables shared with interrupts!

---

## 🎯 DAY 1 HOMEWORK (do this before Day 2!):

1. **Practice Bit Manipulation (15 mins):**
   - Do Exercise 1 above by hand
   - Write down the answers
   - Verify with a calculator

2. **Read the LED Blink Code (10 mins):**
   - Go through the code line by line
   - Understand WHAT each line does (not HOW yet!)
   - Write down any questions

3. **Research (10 mins):**
   - Google: "What is a register in embedded systems?"
   - Google: "STM32F407 GPIO pins"
   - Just READ, don't try to memorize!

---

## 📝 Quick Quiz - Test Yourself!

**Answer these (no cheating!):**

1. What makes embedded C different from regular C?
2. How do you set bit 7 in a variable `x`?
3. How do you clear bit 3 in a variable `x`?
4. What does `volatile` keyword do?
5. In the LED blink code, what does `(1 << 12)` mean?

<details>
<summary>Answers</summary>

1. Direct hardware access, no OS, no standard libraries, infinite loops
2. `x |= (1 << 7);`
3. `x &= ~(1 << 3);`
4. Prevents compiler optimization for hardware registers or interrupt-shared variables
5. Shift 1 left by 12 positions = 0x1000 = controls pin 12
</details>

---

## 🎉 CONGRATULATIONS!

You just learned:
- ✅ Embedded C fundamentals
- ✅ Bit manipulation (THE core skill!)
- ✅ How to read embedded code
- ✅ Why `volatile` matters
- ✅ Your first embedded program structure

**Tomorrow:** We'll dive deeper into GPIO and write more complex code!

---

**Total Time Today:** ~90 minutes  
**Knowledge Gained:** MASSIVE! 🚀

---

*Keep this file open while studying. Come back to it anytime!*

