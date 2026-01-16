# 🎮 DAY 3 - Button Input & Interactive Control

**Date:** January 14, 2026  
**Time Needed:** 1.5-2 hours  
**Goal:** Make your LEDs respond to button presses!

---

## 🎯 Today's Mission:

By the end of Day 3, you'll:
1. ✅ Understand GPIO INPUT mode
2. ✅ Read button states from hardware
3. ✅ Implement button debouncing
4. ✅ Create 3 different LED patterns controlled by button
5. ✅ Build your first INTERACTIVE embedded system!

**From output-only to INTERACTIVE control!** 🎮

---

## Part 1: Understanding GPIO Input (15 mins)

### Day 2 vs Day 3:

**Day 2 - GPIO OUTPUT:**
```
Microcontroller → Controls LED
    (sends signal OUT)
```

**Day 3 - GPIO INPUT:**
```
Button → Microcontroller reads signal
    (receives signal IN)
```

---

### Your STM32F303 Discovery Board Has:

**USER Button:**
- Connected to **PA0** (Port A, Pin 0)
- **Active HIGH** - reads 1 when pressed, 0 when released
- Built-in hardware on your board!

**RESET Button:**
- Restarts the microcontroller
- We won't use this for input

---

### GPIO Input Configuration:

Remember from Day 2, MODER register:
- `00` = **INPUT** ← We'll use this today!
- `01` = OUTPUT (what we used yesterday)
- `10` = Alternate Function
- `11` = Analog

**To configure PA0 as INPUT:**
```c
GPIOA_MODER &= ~(3 << (0 * 2));  // Clear bits [1:0] → sets to 00 (INPUT)
```

---

### Reading Button State:

**New Register: IDR (Input Data Register)**

```c
GPIOA_IDR = (*((volatile uint32_t*)(GPIOA_BASE + 0x10)))
```

**To check if button is pressed:**
```c
if (GPIOA_IDR & (1 << 0)) {
    // Button is PRESSED (bit 0 is HIGH)
} else {
    // Button is RELEASED (bit 0 is LOW)
}
```

---

## Part 2: Pull-Up and Pull-Down Resistors (15 mins)

### The Problem: Floating Pins

**Without pull resistors:**
```
Button Released → Pin is "floating" (undefined state)
Could read 0, could read 1, could randomly fluctuate!
❌ UNRELIABLE!
```

### The Solution: Pull Resistors

**Pull-DOWN:**
```
Button Released → Resistor pulls pin to GND (0)
Button Pressed  → Pin goes to 3.3V (1)
✅ Always defined!
```

**Pull-UP:**
```
Button Released → Resistor pulls pin to 3.3V (1)
Button Pressed  → Pin goes to GND (0)
✅ Always defined! (inverted logic)
```

---

### STM32F303 Discovery USER Button:

**Good News!** The USER button has **built-in hardware pull-down**!
- Released = 0 (LOW)
- Pressed = 1 (HIGH)

**No software configuration needed!** But here's how you'd configure it if needed:

**PUPDR Register (Pull-Up/Pull-Down Register):**
```c
GPIOA_PUPDR &= ~(3 << (0 * 2));  // Clear bits [1:0]
GPIOA_PUPDR |=  (2 << (0 * 2));  // Set to 10 = Pull-down

// Options:
// 00 = No pull-up, no pull-down
// 01 = Pull-up
// 10 = Pull-down
// 11 = Reserved
```

---

## Part 3: Button Debouncing (20 mins)

### The Problem: Mechanical Bounce

**When you press a button:**
```
Physical button press:
         _______________
________|               (You think it's one press)

What microcontroller sees:
    _  _  ______________
___|_||_||              (Multiple rapid presses!)
   ↑ ↑ ↑
   Bouncing contacts!
```

**This happens in ~5-50 milliseconds!**

---

### Solution 1: Software Debouncing (Simple Delay)

```c
if (GPIOA_IDR & (1 << 0)) {
    delay(50000);  // Wait 50ms for bounce to settle
    
    if (GPIOA_IDR & (1 << 0)) {  // Check again
        // Button is REALLY pressed!
        // Do action here
    }
}
```

**Pros:** Simple, works well  
**Cons:** Blocks execution during delay

---

### Solution 2: State Machine Debouncing (Better!)

```c
// Track previous button state
uint8_t button_prev = 0;

while(1) {
    uint8_t button_current = (GPIOA_IDR & (1 << 0)) ? 1 : 0;
    
    // Detect RISING EDGE (button press event)
    if (button_current == 1 && button_prev == 0) {
        // Button just pressed! Do action ONCE
        change_pattern();
    }
    
    button_prev = button_current;  // Save state for next iteration
    delay(10000);  // Small delay (10ms) for debounce
}
```

**Pros:** Detects button press EVENT, not just state  
**Cons:** Slightly more complex

---

## Part 4: Your First Interactive Program! (40 mins)

### Project: Button-Controlled LED Patterns

**Features:**
1. **3 Different Patterns:**
   - Pattern 1: Clockwise spin
   - Pattern 2: Counter-clockwise spin
   - Pattern 3: All blink together

2. **Button Press:**
   - Each press switches to next pattern
   - Cycles through: 1 → 2 → 3 → 1 → ...

3. **Visual Feedback:**
   - LEDs change pattern immediately

---

### The Code Structure:

```c
// Global variables
uint8_t current_pattern = 0;  // 0, 1, or 2

// In main loop:
while(1) {
    // Check button
    if (button_pressed()) {
        current_pattern++;
        if (current_pattern > 2) current_pattern = 0;
    }
    
    // Execute current pattern
    switch(current_pattern) {
        case 0:
            pattern_clockwise();
            break;
        case 1:
            pattern_counter_clockwise();
            break;
        case 2:
            pattern_all_blink();
            break;
    }
}
```

---

## Part 5: Complete Working Code (20 mins)

### I'll provide you with complete, tested code that:
1. Configures PA0 as INPUT for button
2. Keeps PE8-PE15 as OUTPUT for LEDs
3. Implements button debouncing
4. Has 3 switchable patterns
5. Uses clean, readable functions

---

## 🧠 Key Concepts Summary:

### GPIO Input vs Output:

| Feature | OUTPUT | INPUT |
|---------|--------|-------|
| MODER bits | `01` | `00` |
| Register to use | ODR (Output Data) | IDR (Input Data) |
| Operation | Write bits | Read bits |
| Purpose | Control devices | Sense devices |
| Example | LED, Motor | Button, Sensor |

### Button Reading:
```c
// OUTPUT (Day 2)
GPIOE_ODR |= (1 << 9);   // Set bit → LED ON

// INPUT (Day 3)
if (GPIOA_IDR & (1 << 0)) {  // Read bit → Button pressed
    // Do something
}
```

---

## 📝 Day 3 Homework (Optional Enhancement):

After completing the basic project, try:

1. **Add a 4th pattern:** Your own creative LED sequence
2. **Hold detection:** Different action if button held for 2 seconds
3. **Speed control:** Short press = change pattern, long press = change speed
4. **Pattern memory:** Save last pattern used (we'll learn EEPROM later)

---

## 🎯 Learning Outcomes:

After Day 3, you will:
- ✅ Understand GPIO INPUT configuration
- ✅ Know how to read digital inputs
- ✅ Implement button debouncing
- ✅ Use switch-case statements for multiple patterns
- ✅ Create interactive embedded systems
- ✅ Understand the concept of events (button press vs button state)

---

## 🚀 Next: Let's Code!

I'll now create the complete working code for your STM32F303 Discovery board!

You'll be able to:
1. Press the USER button
2. See LED patterns change
3. Cycle through 3 different patterns
4. Have your first truly interactive embedded program!

---

**Ready? Let's write the code!** 💻

**Time to completion:** ~30-40 minutes of coding + testing

---

*Day 3 - Making Embedded Systems Interactive!* 🎮

