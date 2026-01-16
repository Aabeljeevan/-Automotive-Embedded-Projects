//============================================
// DAY 1 EVENING CHALLENGE - Your First Embedded C Code!
// Topic: Bit Manipulation Basics
// Date: January 13, 2026
// Author: Aabel Jeevan Jose
//============================================

#include <stdio.h>
#include <stdint.h>

//============================================
// CHALLENGE 1: Turn ON a specific bit
//============================================
void turnOnBit(uint32_t *reg, uint8_t bitPosition) {
    // TODO: Write code to turn ON the bit at 'bitPosition'
    // HINT: Use OR operation and left shift
    // Example: To turn ON bit 5: *reg = *reg | (1 << 5);
    // Or shorter: *reg |= (1 << 5);

    // YOUR CODE HERE:

}

//============================================
// CHALLENGE 2: Turn OFF a specific bit
//============================================
void turnOffBit(uint32_t *reg, uint8_t bitPosition) {
    // TODO: Write code to turn OFF the bit at 'bitPosition'
    // HINT: Use AND operation with inverted mask
    // Example: To turn OFF bit 5: *reg = *reg & ~(1 << 5);
    // Or shorter: *reg &= ~(1 << 5);

    // YOUR CODE HERE:

}

//============================================
// CHALLENGE 3: Check if a bit is ON or OFF
//============================================
uint8_t isBitOn(uint32_t reg, uint8_t bitPosition) {
    // TODO: Return 1 if bit is ON, 0 if OFF
    // HINT: Use AND operation and check if result is non-zero
    // Example: To check bit 5: (reg & (1 << 5)) != 0

    // YOUR CODE HERE:
    return 0;  // Replace this
}

//============================================
// CHALLENGE 4: Toggle (flip) a specific bit
//============================================
void toggleBit(uint32_t *reg, uint8_t bitPosition) {
    // TODO: If bit is ON, turn it OFF. If OFF, turn it ON.
    // HINT: Use XOR operation
    // Example: To toggle bit 5: *reg ^= (1 << 5);

    // YOUR CODE HERE:

}

//============================================
// Helper function to print register in binary
//============================================
void printRegister(uint32_t reg, const char* label) {
    printf("%s: 0x%08X = ", label, reg);

    // Print in binary (32 bits)
    for (int i = 31; i >= 0; i--) {
        printf("%d", (reg >> i) & 1);
        if (i % 8 == 0) printf(" ");  // Space every 8 bits
    }
    printf("\n");
}

//============================================
// MAIN - Test your functions here
//============================================
int main() {
    printf("=================================================\n");
    printf("   DAY 1 EVENING CHALLENGE - Bit Manipulation\n");
    printf("=================================================\n\n");

    // Simulate a hardware register (like GPIO)
    uint32_t myRegister = 0x00000000;  // Start with all bits OFF

    printf("INITIAL STATE:\n");
    printRegister(myRegister, "Register");
    printf("\n");

    //----------------------------------------
    // TEST 1: Turn ON bit 5
    //----------------------------------------
    printf("TEST 1: Turn ON bit 5\n");
    turnOnBit(&myRegister, 5);
    printRegister(myRegister, "Register");

    if (myRegister == 0x00000020) {
        printf("✅ CORRECT! Bit 5 is ON (0x20 = 0b00100000)\n\n");
    } else {
        printf("❌ NOT YET! Expected 0x00000020\n\n");
    }

    //----------------------------------------
    // TEST 2: Turn ON bit 12
    //----------------------------------------
    printf("TEST 2: Turn ON bit 12\n");
    turnOnBit(&myRegister, 12);
    printRegister(myRegister, "Register");

    if (myRegister == 0x00001020) {
        printf("✅ CORRECT! Bit 5 and 12 are ON\n\n");
    } else {
        printf("❌ NOT YET! Expected 0x00001020\n\n");
    }

    //----------------------------------------
    // TEST 3: Check if bit 5 is ON
    //----------------------------------------
    printf("TEST 3: Check if bit 5 is ON\n");
    if (isBitOn(myRegister, 5)) {
        printf("✅ CORRECT! Bit 5 is ON\n\n");
    } else {
        printf("❌ NOT YET! Bit 5 should be ON\n\n");
    }

    //----------------------------------------
    // TEST 4: Turn OFF bit 5
    //----------------------------------------
    printf("TEST 4: Turn OFF bit 5\n");
    turnOffBit(&myRegister, 5);
    printRegister(myRegister, "Register");

    if (myRegister == 0x00001000) {
        printf("✅ CORRECT! Bit 5 is now OFF, bit 12 still ON\n\n");
    } else {
        printf("❌ NOT YET! Expected 0x00001000\n\n");
    }

    //----------------------------------------
    // TEST 5: Toggle bit 12 (should turn OFF)
    //----------------------------------------
    printf("TEST 5: Toggle bit 12 (should turn OFF)\n");
    toggleBit(&myRegister, 12);
    printRegister(myRegister, "Register");

    if (myRegister == 0x00000000) {
        printf("✅ CORRECT! Bit 12 toggled OFF\n\n");
    } else {
        printf("❌ NOT YET! Expected 0x00000000\n\n");
    }

    //----------------------------------------
    // TEST 6: Toggle bit 7 (should turn ON)
    //----------------------------------------
    printf("TEST 6: Toggle bit 7 (should turn ON)\n");
    toggleBit(&myRegister, 7);
    printRegister(myRegister, "Register");

    if (myRegister == 0x00000080) {
        printf("✅ CORRECT! Bit 7 toggled ON\n\n");
    } else {
        printf("❌ NOT YET! Expected 0x00000080\n\n");
    }

    //----------------------------------------
    // FINAL CHALLENGE: Real Embedded Example
    //----------------------------------------
    printf("=================================================\n");
    printf("   FINAL CHALLENGE: Real GPIO Simulation\n");
    printf("=================================================\n\n");

    printf("Imagine this register controls 8 LEDs (bits 0-7)\n");
    printf("Let's create a pattern!\n\n");

    uint32_t GPIO_ODR = 0x00000000;  // Output Data Register

    // Pattern: Turn ON LEDs 0, 2, 4, 6 (even positions)
    printf("Pattern 1: Turn ON even LEDs (0, 2, 4, 6)\n");
    turnOnBit(&GPIO_ODR, 0);
    turnOnBit(&GPIO_ODR, 2);
    turnOnBit(&GPIO_ODR, 4);
    turnOnBit(&GPIO_ODR, 6);
    printRegister(GPIO_ODR, "GPIO_ODR");
    printf("\n");

    // Pattern: Toggle all to create opposite pattern
    printf("Pattern 2: Toggle all to create opposite pattern\n");
    for (int i = 0; i < 8; i++) {
        toggleBit(&GPIO_ODR, i);
    }
    printRegister(GPIO_ODR, "GPIO_ODR");
    printf("\n");

    printf("=================================================\n");
    printf("   🎉 CHALLENGE COMPLETE!\n");
    printf("=================================================\n\n");

    printf("📝 What you just learned:\n");
    printf("   ✅ How to turn bits ON and OFF\n");
    printf("   ✅ How to check bit status\n");
    printf("   ✅ How to toggle bits\n");
    printf("   ✅ THIS IS HOW YOU CONTROL HARDWARE!\n\n");

    printf("💡 In real embedded systems:\n");
    printf("   - Each bit controls a hardware feature (LED, motor, sensor)\n");
    printf("   - Registers are at specific memory addresses\n");
    printf("   - Example: GPIOA->ODR |= (1 << 5);  // Turn ON LED on pin 5\n\n");

    printf("🚀 Next: Tomorrow you'll master pointers!\n\n");

    return 0;
}

//============================================
// HOMEWORK (Optional - if you want more!)
//============================================
/*
Try these on your own:

1. Write a function to count how many bits are ON:
   uint8_t countOnBits(uint32_t reg);

2. Write a function to turn ON multiple bits at once:
   void turnOnMultipleBits(uint32_t *reg, uint32_t mask);
   Example: turnOnMultipleBits(&reg, 0x55);  // Turn ON bits 0,2,4,6

3. Write a function to check if two registers are equal:
   uint8_t areRegistersEqual(uint32_t reg1, uint32_t reg2);

Good luck! 🎯
*/

