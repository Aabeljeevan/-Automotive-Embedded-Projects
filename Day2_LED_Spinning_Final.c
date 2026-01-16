/**
 ******************************************************************************
 * @file           : main.c
 * @brief          : All 8 LED Sequential Blink - STM32F303 Discovery
 * @author         : Aabel Jeevan Jose
 * @date           : January 14, 2026
 ******************************************************************************
 * All 8 LEDs blink one by one in clockwise pattern:
 * North → NE → East → SE → South → SW → West → NW → Repeat!
 *
 * LED Mapping:
 * LD3 (PE9)  - North (Red)
 * LD4 (PE8)  - North-East (Blue)
 * LD5 (PE10) - East (Orange)
 * LD6 (PE15) - South-East (Green)
 * LD7 (PE11) - South (Green)
 * LD8 (PE14) - South-West (Orange)
 * LD9 (PE12) - West (Blue)
 * LD10(PE13) - North-West (Red)
 ******************************************************************************
 */

#include <stdint.h>

// ============================================================================
// Register Definitions for STM32F303
// ============================================================================

// RCC (Reset and Clock Control) Base Address
#define RCC_BASE            0x40021000
#define RCC_AHBENR          (*((volatile uint32_t*)(RCC_BASE + 0x14)))

// GPIOE Base Address
#define GPIOE_BASE          0x48001000
#define GPIOE_MODER         (*((volatile uint32_t*)(GPIOE_BASE + 0x00)))
#define GPIOE_ODR           (*((volatile uint32_t*)(GPIOE_BASE + 0x14)))

// Bit positions
#define RCC_AHBENR_GPIOEEN  (1 << 21)  // Enable clock for GPIOE (bit 21)

// LED Pin Definitions (All 8 LEDs in clockwise order)
#define LED_NORTH           9          // PE9  = LD3 (North - Red)
#define LED_NE              8          // PE8  = LD4 (North-East - Blue)
#define LED_EAST            10         // PE10 = LD5 (East - Orange)
#define LED_SE              15         // PE15 = LD6 (South-East - Green)
#define LED_SOUTH           11         // PE11 = LD7 (South - Green)
#define LED_SW              14         // PE14 = LD8 (South-West - Orange)
#define LED_WEST            12         // PE12 = LD9 (West - Blue)
#define LED_NW              13         // PE13 = LD10 (North-West - Red)

// ============================================================================
// Simple Delay Function
// ============================================================================
void delay(volatile uint32_t count) {
    while(count--) {
        __asm("NOP");  // No operation - prevents compiler optimization
    }
}

// ============================================================================
// Function to Turn OFF All LEDs
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
// Main Function
// ============================================================================
int main(void)
{
    // STEP 1: Enable clock for GPIO Port E
    RCC_AHBENR |= RCC_AHBENR_GPIOEEN;

    // STEP 2: Configure ALL 8 LED pins as OUTPUT
    // Each pin needs 2 bits in MODER register set to 01 (Output mode)

    GPIOE_MODER &= ~(3 << (LED_NORTH * 2));  // Clear bits for PE9
    GPIOE_MODER |=  (1 << (LED_NORTH * 2));  // Set as Output

    GPIOE_MODER &= ~(3 << (LED_NE * 2));     // Clear bits for PE8
    GPIOE_MODER |=  (1 << (LED_NE * 2));     // Set as Output

    GPIOE_MODER &= ~(3 << (LED_EAST * 2));   // Clear bits for PE10
    GPIOE_MODER |=  (1 << (LED_EAST * 2));   // Set as Output

    GPIOE_MODER &= ~(3 << (LED_SE * 2));     // Clear bits for PE15
    GPIOE_MODER |=  (1 << (LED_SE * 2));     // Set as Output

    GPIOE_MODER &= ~(3 << (LED_SOUTH * 2));  // Clear bits for PE11
    GPIOE_MODER |=  (1 << (LED_SOUTH * 2));  // Set as Output

    GPIOE_MODER &= ~(3 << (LED_SW * 2));     // Clear bits for PE14
    GPIOE_MODER |=  (1 << (LED_SW * 2));     // Set as Output

    GPIOE_MODER &= ~(3 << (LED_WEST * 2));   // Clear bits for PE12
    GPIOE_MODER |=  (1 << (LED_WEST * 2));   // Set as Output

    GPIOE_MODER &= ~(3 << (LED_NW * 2));     // Clear bits for PE13
    GPIOE_MODER |=  (1 << (LED_NW * 2));     // Set as Output

    // STEP 3: Sequential LED Pattern - Counter-Clockwise!
    while(1) {
        // 1. North LED (Red)
        all_leds_off();
        GPIOE_ODR |= (1 << LED_NORTH);
        delay(200000);

        // 2. North-West LED (Red)
        all_leds_off();
        GPIOE_ODR |= (1 << LED_NW);
        delay(200000);

        // 3. West LED (Blue)
        all_leds_off();
        GPIOE_ODR |= (1 << LED_WEST);
        delay(200000);

        // 4. South-West LED (Orange)
        all_leds_off();
        GPIOE_ODR |= (1 << LED_SW);
        delay(200000);

        // 5. South LED (Green)
        all_leds_off();
        GPIOE_ODR |= (1 << LED_SOUTH);
        delay(200000);

        // 6. South-East LED (Green)
        all_leds_off();
        GPIOE_ODR |= (1 << LED_SE);
        delay(200000);

        // 7. East LED (Orange)
        all_leds_off();
        GPIOE_ODR |= (1 << LED_EAST);
        delay(200000);

        // 8. North-East LED (Blue)
        all_leds_off();
        GPIOE_ODR |= (1 << LED_NE);
        delay(200000);
    }
}
