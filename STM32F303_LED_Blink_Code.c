/**
 ******************************************************************************
 * @file           : main.c
 * @brief          : LED Blink on STM32F303 Discovery - PE9 (North LED)
 * @author         : Aabel Jeevan Jose
 * @date           : January 14, 2026
 ******************************************************************************
 * LED: LD3 (North/Red) connected to PE9
 * This code demonstrates:
 * - GPIO clock enable
 * - GPIO pin configuration as output
 * - Toggling GPIO pin to blink LED
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
#define LED_PIN             9          // PE9 = North LED (LD3)

// ============================================================================
// Simple Delay Function
// ============================================================================
void delay(volatile uint32_t count) {
    while(count--) {
        // Just burn CPU cycles
        __asm("NOP");  // No operation - prevents compiler optimization
    }
}

// ============================================================================
// Main Function
// ============================================================================
int main(void)
{
    // STEP 1: Enable clock for GPIO Port E
    // Without clock, the peripheral won't work!
    RCC_AHBENR |= RCC_AHBENR_GPIOEEN;

    // STEP 2: Configure PE9 as OUTPUT
    // MODER register: 2 bits per pin
    // 00 = Input, 01 = Output, 10 = Alternate Function, 11 = Analog
    // For PE9: bits [19:18] need to be 01

    GPIOE_MODER &= ~(3 << (LED_PIN * 2));  // Clear bits [19:18]
    GPIOE_MODER |=  (1 << (LED_PIN * 2));  // Set to 01 (Output mode)

    // STEP 3: Infinite loop - Blink LED!
    while(1) {
        // Turn LED ON
        GPIOE_ODR |= (1 << LED_PIN);   // Set PE9 high
        delay(500000);                  // Wait ~500ms

        // Turn LED OFF
        GPIOE_ODR &= ~(1 << LED_PIN);  // Set PE9 low
        delay(500000);                  // Wait ~500ms
    }
}

