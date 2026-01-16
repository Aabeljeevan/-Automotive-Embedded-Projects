/**
 ******************************************************************************
 * @file           : main.c
 * @brief          : Day 3 Complete - 8 Button-Controlled LED Patterns!
 * @author         : Aabel Jeevan Jose
 * @date           : January 14, 2026
 ******************************************************************************
 * Button: USER button on PA0
 * LEDs: All 8 LEDs (PE8-PE15)
 * 
 * 8 Patterns:
 * 0. Clockwise spin
 * 1. Counter-clockwise spin
 * 2. All blink together
 * 3. Custom sequential (by pin number)
 * 4. Knight Rider (back and forth)
 * 5. Binary counter (0-255)
 * 6. Random chaos
 * 7. Breathing effect
 * 
 * Skills demonstrated:
 * - GPIO Input/Output
 * - Button debouncing
 * - Event detection
 * - Bit manipulation
 * - Pseudo-random algorithms
 * - Pattern state machines
 ******************************************************************************
 */

#include <stdint.h>

// ============================================================================
// Register Definitions
// ============================================================================

// RCC (Reset and Clock Control)
#define RCC_BASE            0x40021000
#define RCC_AHBENR          (*((volatile uint32_t*)(RCC_BASE + 0x14)))
#define RCC_AHBENR_GPIOAEN  (1 << 17)  // Enable clock for GPIOA
#define RCC_AHBENR_GPIOEEN  (1 << 21)  // Enable clock for GPIOE

// GPIOA (for button)
#define GPIOA_BASE          0x48000000
#define GPIOA_MODER         (*((volatile uint32_t*)(GPIOA_BASE + 0x00)))
#define GPIOA_IDR           (*((volatile uint32_t*)(GPIOA_BASE + 0x10)))

// GPIOE (for LEDs)
#define GPIOE_BASE          0x48001000
#define GPIOE_MODER         (*((volatile uint32_t*)(GPIOE_BASE + 0x00)))
#define GPIOE_ODR           (*((volatile uint32_t*)(GPIOE_BASE + 0x14)))

// Pin Definitions
#define BUTTON_PIN          0          // PA0 = USER button

// LED Pins (all 8 LEDs)
#define LED_NORTH           9          // PE9  = LD3 (North - Red)
#define LED_NE              8          // PE8  = LD4 (North-East - Blue)
#define LED_EAST            10         // PE10 = LD5 (East - Orange)
#define LED_SE              15         // PE15 = LD6 (South-East - Green)
#define LED_SOUTH           11         // PE11 = LD7 (South - Green)
#define LED_SW              14         // PE14 = LD8 (South-West - Orange)
#define LED_WEST            12         // PE12 = LD9 (West - Blue)
#define LED_NW              13         // PE13 = LD10 (North-West - Red)

// Global Variables
uint8_t current_pattern = 0;           // Current pattern (0-7)
uint8_t button_prev = 0;               // Previous button state for edge detection

// ============================================================================
// Simple Delay Function
// ============================================================================
void delay(volatile uint32_t count) {
    while(count--) {
        __asm("NOP");
    }
}

// ============================================================================
// Turn OFF All LEDs
// ============================================================================
void all_leds_off(void) {
    GPIOE_ODR &= ~(1 << LED_NORTH);
    GPIOE_ODR &= ~(1 << LED_NE);
    GPIOE_ODR &= ~(1 << LED_EAST);
    GPIOE_ODR &= ~(1 << LED_SE);
    GPIOE_ODR &= ~(1 << LED_SOUTH);
    GPIOE_ODR &= ~(1 << LED_SW);
    GPIOE_ODR &= ~(1 << LED_WEST);
    GPIOE_ODR &= ~(1 << LED_NW);
}

// ============================================================================
// Turn ON All LEDs
// ============================================================================
void all_leds_on(void) {
    GPIOE_ODR |= (1 << LED_NORTH);
    GPIOE_ODR |= (1 << LED_NE);
    GPIOE_ODR |= (1 << LED_EAST);
    GPIOE_ODR |= (1 << LED_SE);
    GPIOE_ODR |= (1 << LED_SOUTH);
    GPIOE_ODR |= (1 << LED_SW);
    GPIOE_ODR |= (1 << LED_WEST);
    GPIOE_ODR |= (1 << LED_NW);
}

// ============================================================================
// Check if Button is Pressed (with debouncing)
// ============================================================================
uint8_t button_pressed(void) {
    uint8_t button_current = (GPIOA_IDR & (1 << BUTTON_PIN)) ? 1 : 0;
    
    if (button_current == 1 && button_prev == 0) {
        button_prev = button_current;
        delay(50000);  // Debounce delay
        return 1;
    }
    
    button_prev = button_current;
    return 0;
}

// ============================================================================
// Pattern 0: Clockwise Spin
// ============================================================================
void pattern_clockwise_step(void) {
    static uint8_t step = 0;
    all_leds_off();
    
    switch(step) {
        case 0: GPIOE_ODR |= (1 << LED_NORTH); break;
        case 1: GPIOE_ODR |= (1 << LED_NE);    break;
        case 2: GPIOE_ODR |= (1 << LED_EAST);  break;
        case 3: GPIOE_ODR |= (1 << LED_SE);    break;
        case 4: GPIOE_ODR |= (1 << LED_SOUTH); break;
        case 5: GPIOE_ODR |= (1 << LED_SW);    break;
        case 6: GPIOE_ODR |= (1 << LED_WEST);  break;
        case 7: GPIOE_ODR |= (1 << LED_NW);    break;
    }
    
    step++;
    if (step > 7) step = 0;
}

// ============================================================================
// Pattern 1: Counter-Clockwise Spin
// ============================================================================
void pattern_counter_clockwise_step(void) {
    static uint8_t step = 0;
    all_leds_off();
    
    switch(step) {
        case 0: GPIOE_ODR |= (1 << LED_NORTH); break;
        case 1: GPIOE_ODR |= (1 << LED_NW);    break;
        case 2: GPIOE_ODR |= (1 << LED_WEST);  break;
        case 3: GPIOE_ODR |= (1 << LED_SW);    break;
        case 4: GPIOE_ODR |= (1 << LED_SOUTH); break;
        case 5: GPIOE_ODR |= (1 << LED_SE);    break;
        case 6: GPIOE_ODR |= (1 << LED_EAST);  break;
        case 7: GPIOE_ODR |= (1 << LED_NE);    break;
    }
    
    step++;
    if (step > 7) step = 0;
}

// ============================================================================
// Pattern 2: All Blink Together
// ============================================================================
void pattern_all_blink_step(void) {
    static uint8_t on = 0;
    
    if (on) {
        all_leds_on();
    } else {
        all_leds_off();
    }
    
    on = !on;
}

// ============================================================================
// Pattern 3: Custom Sequential (by pin number)
// ============================================================================
void pattern_sequential_pin_order(void) {
    static uint8_t step = 0;
    all_leds_off();
    
    switch(step) {
        case 0: GPIOE_ODR |= (1 << 8);  break;
        case 1: GPIOE_ODR |= (1 << 9);  break;
        case 2: GPIOE_ODR |= (1 << 10); break;
        case 3: GPIOE_ODR |= (1 << 11); break;
        case 4: GPIOE_ODR |= (1 << 12); break;
        case 5: GPIOE_ODR |= (1 << 13); break;
        case 6: GPIOE_ODR |= (1 << 14); break;
        case 7: GPIOE_ODR |= (1 << 15); break;
    }
    
    step++;
    if (step > 7) step = 0;
}

// ============================================================================
// Pattern 4: Knight Rider (back and forth)
// ============================================================================
void pattern_knight_rider(void) {
    static uint8_t position = 0;
    static uint8_t direction = 0;  // 0 = forward, 1 = backward
    
    all_leds_off();
    GPIOE_ODR |= (1 << (8 + position));  // Turn on LED at current position
    
    // Move position
    if (direction == 0) {
        position++;
        if (position >= 7) direction = 1;  // Reached end, go backward
    } else {
        position--;
        if (position == 0) direction = 0;  // Reached start, go forward
    }
}

// ============================================================================
// Pattern 5: Binary Counter (0-255)
// ============================================================================
void pattern_binary_counter(void) {
    static uint8_t count = 0;
    
    uint8_t led_pins[8] = {8, 9, 10, 11, 12, 13, 14, 15};
    
    for (int i = 0; i < 8; i++) {
        if (count & (1 << i)) {
            GPIOE_ODR |= (1 << led_pins[i]);
        } else {
            GPIOE_ODR &= ~(1 << led_pins[i]);
        }
    }
    
    count++;
}

// ============================================================================
// Pattern 6: Random Chaos
// ============================================================================
void pattern_random_chaos(void) {
    static uint32_t random = 123;
    
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

// ============================================================================
// Pattern 7: Breathing Effect
// ============================================================================
void pattern_breathing(void) {
    static uint8_t leds_on = 0;
    static uint8_t direction = 0;  // 0 = adding LEDs, 1 = removing LEDs
    
    uint8_t led_pins[8] = {8, 9, 10, 11, 12, 13, 14, 15};
    
    // Turn on LEDs up to 'leds_on' count
    for (int i = 0; i < 8; i++) {
        if (i < leds_on) {
            GPIOE_ODR |= (1 << led_pins[i]);
        } else {
            GPIOE_ODR &= ~(1 << led_pins[i]);
        }
    }
    
    // Update LED count
    if (direction == 0) {
        leds_on++;
        if (leds_on >= 8) direction = 1;  // Start removing
    } else {
        leds_on--;
        if (leds_on == 0) direction = 0;  // Start adding
    }
}

// ============================================================================
// Main Function
// ============================================================================
int main(void)
{
    // Enable clocks
    RCC_AHBENR |= RCC_AHBENR_GPIOAEN;
    RCC_AHBENR |= RCC_AHBENR_GPIOEEN;
    
    // Configure button as INPUT
    GPIOA_MODER &= ~(3 << (BUTTON_PIN * 2));
    
    // Configure all LEDs as OUTPUT
    GPIOE_MODER &= ~(3 << (LED_NORTH * 2));
    GPIOE_MODER |=  (1 << (LED_NORTH * 2));
    
    GPIOE_MODER &= ~(3 << (LED_NE * 2));
    GPIOE_MODER |=  (1 << (LED_NE * 2));
    
    GPIOE_MODER &= ~(3 << (LED_EAST * 2));
    GPIOE_MODER |=  (1 << (LED_EAST * 2));
    
    GPIOE_MODER &= ~(3 << (LED_SE * 2));
    GPIOE_MODER |=  (1 << (LED_SE * 2));
    
    GPIOE_MODER &= ~(3 << (LED_SOUTH * 2));
    GPIOE_MODER |=  (1 << (LED_SOUTH * 2));
    
    GPIOE_MODER &= ~(3 << (LED_SW * 2));
    GPIOE_MODER |=  (1 << (LED_SW * 2));
    
    GPIOE_MODER &= ~(3 << (LED_WEST * 2));
    GPIOE_MODER |=  (1 << (LED_WEST * 2));
    
    GPIOE_MODER &= ~(3 << (LED_NW * 2));
    GPIOE_MODER |=  (1 << (LED_NW * 2));
    
    // Main loop
    while(1) {
        // Check for button press
        if (button_pressed()) {
            current_pattern++;
            if (current_pattern > 7) {
                current_pattern = 0;
            }
            all_leds_off();
            delay(100000);
        }
        
        // Execute current pattern
        switch(current_pattern) {
            case 0:
                pattern_clockwise_step();
                delay(150000);
                break;
                
            case 1:
                pattern_counter_clockwise_step();
                delay(150000);
                break;
                
            case 2:
                pattern_all_blink_step();
                delay(300000);
                break;
                
            case 3:
                pattern_sequential_pin_order();
                delay(150000);
                break;
                
            case 4:
                pattern_knight_rider();
                delay(100000);  // Faster for smooth animation
                break;
                
            case 5:
                pattern_binary_counter();
                delay(200000);
                break;
                
            case 6:
                pattern_random_chaos();
                delay(150000);
                break;
                
            case 7:
                pattern_breathing();
                delay(150000);
                break;
        }
    }
}
