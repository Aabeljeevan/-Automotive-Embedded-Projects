# 🎯 DAY 6 - Project Documentation for Portfolio

**Date:** January 19, 2026  
**Goal:** Document your hardware projects professionally for GitHub/Resume

---

## 📁 YOUR COMPLETED PROJECTS:

### ✅ **Project 1: Multi-LED Counter Pattern**
- **File:** `Day2_LED_Spinning_Final.c`
- **Board:** STM32F303 Discovery
- **Skills:** GPIO, Register-level programming, Delay loops

### ✅ **Project 2: Button-Controlled Interactive LED System**
- **File:** `Day3_Final_7_Patterns.c`
- **Board:** STM32F303 Discovery
- **Skills:** GPIO input, Button debouncing, State machines, 7 LED patterns

### ✅ **Project 3: Custom LED Patterns (Your Creativity!)**
- **Patterns:** Knight Rider, Binary Counter, Random Chaos
- **Skills:** Pattern design, PRNG, Bit manipulation

---

# 🚀 PROJECT 1: Multi-LED Counter Pattern

## 📝 Project Description:

**Title:** 8-LED Counter-Clockwise Spinning Pattern on STM32F303 Discovery Board

**Summary:**  
Implemented a bare-metal LED control system using register-level GPIO programming on the STM32F303 Discovery board. The project controls 8 LEDs (PE8-PE15) to create a counter-clockwise spinning pattern without using any HAL libraries.

---

## 🎯 Technical Skills Demonstrated:

✅ **Hardware:**
- STM32F303VCT6 microcontroller
- GPIO Port E configuration
- LED control via register manipulation

✅ **Programming:**
- Register-level programming (no HAL)
- RCC clock configuration
- GPIO mode configuration
- Bit manipulation for LED control
- Software delay implementation

✅ **Concepts:**
- Memory-mapped I/O
- Hardware register access
- Embedded C with volatile pointers

---

## 🔧 Key Technical Details:

### Hardware Registers Used:
```c
RCC_AHBENR    (0x40021014)  // Clock enable for GPIO
GPIOE_MODER   (0x48001000)  // GPIO mode configuration
GPIOE_ODR     (0x48001014)  // GPIO output data register
```

### LED Mapping:
| LED Color | Pin | Register Bit |
|-----------|-----|--------------|
| Red N     | PE9 | Bit 9        |
| Blue NE   | PE10| Bit 10       |
| Orange E  | PE11| Bit 11       |
| Blue SE   | PE12| Bit 12       |
| Red S     | PE13| Bit 13       |
| Orange SW | PE14| Bit 14       |
| Green W   | PE15| Bit 15       |
| Green NW  | PE8 | Bit 8        |

### Pattern Sequence:
Counter-clockwise rotation: N → NE → E → SE → S → SW → W → NW → repeat

---

## 💻 Code Highlights:

```c
// Clock enable for GPIO Port E
RCC_AHBENR |= RCC_AHBENR_GPIOEEN;

// Configure all 8 LEDs as output
for (int pin = 8; pin <= 15; pin++) {
    GPIOE_MODER &= ~(3 << (pin * 2));  // Clear mode bits
    GPIOE_MODER |=  (1 << (pin * 2));  // Set as output
}

// Control individual LED
GPIOE_ODR |= (1 << led_pins[i]);   // LED ON
GPIOE_ODR &= ~(1 << led_pins[i]);  // LED OFF
```

---

## 🎓 Learning Outcomes:

1. ✅ Understanding of STM32 GPIO architecture
2. ✅ Register-level programming without HAL abstraction
3. ✅ Bit manipulation for hardware control
4. ✅ Software delay implementation
5. ✅ Reading and understanding datasheets

---

## 📸 Demo:

**Status:** ✅ Working on hardware  
**Video/GIF:** *(Can add later)*  
**Repository:** [Link to GitHub](https://github.com/Aabeljeevan/-Automotive-Embedded-Projects)

---

# 🎮 PROJECT 2: Button-Controlled Interactive LED System

## 📝 Project Description:

**Title:** Multi-Pattern Interactive LED System with Button Control

**Summary:**  
Developed an interactive embedded system featuring 7 distinct LED patterns controlled via button input. Implemented software debouncing, state machine logic, and multiple visual patterns including custom-designed Knight Rider, Binary Counter, and Random Chaos effects.

---

## 🎯 Technical Skills Demonstrated:

✅ **Hardware:**
- GPIO input configuration (button)
- GPIO output configuration (8 LEDs)
- Pull-up/pull-down resistor configuration
- STM32F303 Discovery Board

✅ **Programming:**
- Button debouncing algorithm
- State machine implementation
- Event detection (edge detection)
- Pattern generation algorithms
- PRNG (Pseudo-Random Number Generator)

✅ **Embedded Concepts:**
- Input polling
- Software debouncing (20ms window)
- State persistence with `static` keyword
- Hardware register manipulation

---

## 🔧 Key Technical Details:

### Button Configuration:
```c
// PA0 as input with pull-down
GPIOA_MODER &= ~(3 << (0 * 2));  // Input mode
GPIOA_PUPDR &= ~(3 << (0 * 2));
GPIOA_PUPDR |= (2 << (0 * 2));   // Pull-down

// Read button state
if (GPIOA_IDR & (1 << 0)) {
    // Button pressed
}
```

### Debouncing Algorithm:
```c
#define DEBOUNCE_DELAY 20  // 20ms

uint8_t read_button_debounced(void) {
    static uint8_t last_state = 0;
    static uint32_t last_change_time = 0;
    
    uint8_t current = (GPIOA_IDR & (1 << 0)) ? 1 : 0;
    
    if (current != last_state) {
        uint32_t now = system_time_ms;
        if ((now - last_change_time) > DEBOUNCE_DELAY) {
            last_state = current;
            last_change_time = now;
        }
    }
    return last_state;
}
```

---

## 🎨 Implemented Patterns:

### 1. **Clockwise Step** (Sequential LED rotation)
- Single LED moves clockwise around circle
- State machine with 8 states

### 2. **Counter-Clockwise Step** (Reverse rotation)
- Single LED moves counter-clockwise
- Demonstrates bi-directional control

### 3. **Ping-Pong** (Bouncing LED)
- LED bounces between ends
- Direction reversal logic

### 4. **All Blink** (Synchronized flash)
- All LEDs blink together
- Simple ON/OFF toggle

### 5. **Knight Rider** (Back-and-forth sweep) ⭐ CUSTOM
- LED sweeps left-to-right, then right-to-left
- 15-state state machine
- Inspired by KITT from Knight Rider

### 6. **Binary Counter** ⭐ CUSTOM
- LEDs display 8-bit binary count (0-255)
- Demonstrates bit-to-LED mapping
- Each LED represents a bit position

### 7. **Random Chaos** ⭐ CUSTOM
- Pseudo-random LED patterns
- Linear Congruential Generator (LCG) PRNG
- Formula: `random = (random * 1103515245 + 12345) % 256`

---

## 💻 Code Highlights:

### State Machine for Pattern Switching:
```c
switch (current_pattern) {
    case 0: pattern_clockwise_step(); break;
    case 1: pattern_counter_clockwise_step(); break;
    case 2: pattern_ping_pong(); break;
    case 3: pattern_all_blink(); break;
    case 4: pattern_knight_rider(); break;
    case 5: pattern_binary_counter(); break;
    case 6: pattern_random_chaos(); break;
}
```

### Custom Pattern - Knight Rider:
```c
void pattern_knight_rider(void) {
    static uint8_t step = 0;
    all_leds_off();
    
    // Forward: 0-7, Backward: 8-14
    if (step <= 7) {
        GPIOE_ODR |= (1 << (8 + step));
    } else {
        GPIOE_ODR |= (1 << (22 - step));
    }
    
    step = (step + 1) % 15;
}
```

### Custom Pattern - Binary Counter:
```c
void pattern_binary_counter(void) {
    static uint8_t count = 0;
    uint8_t led_pins[8] = {8, 9, 10, 11, 12, 13, 14, 15};
    
    for (int i = 0; i < 8; i++) {
        if (count & (1 << i)) {
            GPIOE_ODR |= (1 << led_pins[i]);   // Bit is 1
        } else {
            GPIOE_ODR &= ~(1 << led_pins[i]);  // Bit is 0
        }
    }
    count++;
}
```

### Custom Pattern - Random Chaos:
```c
void pattern_random_chaos(void) {
    static uint32_t random = 123;  // Seed
    
    // Linear Congruential Generator
    random = (random * 1103515245 + 12345) % 256;
    
    uint8_t led_pins[8] = {8, 9, 10, 11, 12, 13, 14, 15};
    for (int i = 0; i < 8; i++) {
        if (random & (1 << i)) {
            GPIOE_ODR |= (1 << led_pins[i]);
        } else {
            GPIOE_ODR &= ~(1 << led_pins[i]);
        }
    }
}
```

---

## 🎓 Learning Outcomes:

1. ✅ GPIO input configuration and reading
2. ✅ Software debouncing implementation
3. ✅ State machine design and implementation
4. ✅ Event detection (button press/release)
5. ✅ Multiple pattern algorithms
6. ✅ Creative problem solving (custom patterns)
7. ✅ Pseudo-random number generation
8. ✅ Bit manipulation for LED control

---

## 📸 Demo:

**Status:** ✅ Working on hardware  
**Features:** 7 interactive patterns, button-controlled switching  
**Video/GIF:** *(Can add later)*  
**Repository:** [Link to GitHub](https://github.com/Aabeljeevan/-Automotive-Embedded-Projects)

---

# 📋 HOW TO ADD TO RESUME:

## **For Your Resume "Projects" Section:**

### **Project 1:**
```
Multi-LED Pattern Controller | STM32F303 Discovery | C
• Implemented register-level GPIO control for 8 LEDs without HAL libraries
• Programmed counter-clockwise spinning pattern using memory-mapped I/O
• Configured RCC clock and GPIO mode registers for direct hardware access
```

### **Project 2:**
```
Interactive Button-Controlled LED System | STM32F303 | C
• Developed 7 LED patterns including Knight Rider, Binary Counter, and PRNG-based chaos
• Implemented software debouncing (20ms) and state machine for pattern switching
• Created custom algorithms for bi-directional sweeps and pseudo-random generation
```

---

# 📋 HOW TO ADD TO GITHUB:

## **Update README.md:**

```markdown
# Automotive Embedded Projects Portfolio

## 🚀 Week 1: GPIO and Register-Level Programming

### Project 1: Multi-LED Counter Pattern
**Skills:** GPIO, Register Programming, Bit Manipulation  
**File:** `Day2_LED_Spinning_Final.c`

Bare-metal LED control using register-level programming on STM32F303. 
Demonstrates understanding of GPIO architecture, RCC clocking, and 
memory-mapped I/O without HAL abstraction.

**Key Features:**
- ✅ Direct register manipulation
- ✅ 8-LED counter-clockwise pattern
- ✅ No HAL dependencies

---

### Project 2: Interactive Button-LED System
**Skills:** GPIO Input, Debouncing, State Machines, Pattern Design  
**File:** `Day3_Final_7_Patterns.c`

Interactive embedded system with 7 distinct LED patterns controlled 
via button input. Features custom-designed patterns including Knight 
Rider sweep, binary counter visualization, and PRNG-based randomization.

**Key Features:**
- ✅ Software debouncing (20ms)
- ✅ State machine implementation
- ✅ 7 unique patterns (4 basic + 3 custom)
- ✅ PRNG algorithm (LCG)

---

**Hardware:** STM32F303 Discovery Board  
**Tools:** STM32CubeIDE, ST-Link Debugger  
**Language:** Embedded C
```

---

# ✅ DAY 6 CHECKLIST:

- [ ] Read project descriptions ✅
- [ ] Understand technical details ✅
- [ ] Review code highlights ✅
- [ ] Know how to present on resume ✅
- [ ] Projects ready for GitHub portfolio ✅

---

**Time:** 20-30 minutes to review  
**Outcome:** Professional project documentation! ✅

---

*Day 6 Complete - Projects Documented!* 🎯

