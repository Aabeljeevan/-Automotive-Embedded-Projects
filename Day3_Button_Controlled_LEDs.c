/**
 ******************************************************************************
 * @file           : main.c
 * @brief          : Button-Controlled LED Patterns - STM32F303 Discovery
 * @author         : Aabel Jeevan Jose
 * @date           : January 14, 2026
 ******************************************************************************
 * Button: USER button on PA0
 * LEDs: All 8 LEDs (PE8-PE15)
 * 
 * Features:
 * - Press button to cycle through 3 patterns
 * - Pattern 1: Clockwise spin
 * - Pattern 2: Counter-clockwise spin
 * - Pattern 3: All LEDs blink together
 * 
 * This demonstrates:
 * - GPIO Input configuration
 * - Button debouncing
 * - Button press event detection
 * - Multiple pattern control
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
uint8_t current_pattern = 0;           // Current pattern (0, 1, or 2)
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
// Returns 1 if button just pressed (rising edge), 0 otherwise
// ============================================================================
uint8_t button_pressed(void) {
    // Read current button state
    uint8_t button_current = (GPIOA_IDR & (1 << BUTTON_PIN)) ? 1 : 0;
    
    // Detect RISING EDGE (button just pressed)
    if (button_current == 1 && button_prev == 0) {
        button_prev = button_current;
        delay(50000);  // Debounce delay (50ms)
        return 1;      // Button press event detected!
    }
    
    button_prev = button_current;
    return 0;  // No button press event
}

// ============================================================================
// Pattern 1: Clockwise Spin
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
// Pattern 2: Counter-Clockwise Spin
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
// Pattern 3: All Blink Together
// ============================================================================
void pattern_all_blink_step(void) {
    static uint8_t on = 0;
    
    if (on) {
        all_leds_on();
    } else {
        all_leds_off();
    }
    
    on = !on;  // Toggle state
}

// ============================================================================
// Main Function
// ============================================================================
int main(void)
{
    // ========================================================================
    // STEP 1: Enable Clocks
    // ========================================================================
    RCC_AHBENR |= RCC_AHBENR_GPIOAEN;  // Enable clock for GPIOA (button)
    RCC_AHBENR |= RCC_AHBENR_GPIOEEN;  // Enable clock for GPIOE (LEDs)
    
    // ========================================================================
    // STEP 2: Configure Button (PA0) as INPUT
    // ========================================================================
    // Default after reset is INPUT (00), but let's be explicit
    GPIOA_MODER &= ~(3 << (BUTTON_PIN * 2));  // Clear bits [1:0] → INPUT mode
    
    // Note: STM32F303 Discovery USER button has hardware pull-down
    // No need to configure PUPDR register
    
    // ========================================================================
    // STEP 3: Configure All LED Pins (PE8-PE15) as OUTPUT
    // ========================================================================
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
    
    // ========================================================================
    // STEP 4: Main Loop - Pattern Control
    // ========================================================================
    while(1) {
        // Check for button press
        if (button_pressed()) {
            current_pattern++;
            if (current_pattern > 2) {
                current_pattern = 0;  // Cycle back to pattern 0
            }
            all_leds_off();  // Clear LEDs when switching patterns
            delay(100000);   // Small delay after pattern change
        }
        
        // Execute current pattern
        switch(current_pattern) {
            case 0:
                pattern_clockwise_step();
                delay(150000);  // Speed of pattern
                break;
                
            case 1:
                pattern_counter_clockwise_step();
                delay(150000);
                break;
                
            case 2:
                pattern_all_blink_step();
                delay(300000);  // Slower blink
                break;
        }
    }
}

