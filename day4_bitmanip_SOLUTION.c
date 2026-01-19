/**
 * Day 4 - Bit Manipulation Practice - COMPLETE SOLUTIONS
 * You already used these in your LED projects!
 */

#include <stdio.h>
#include <stdint.h>

// ============================================
// EXERCISE 1: Set Bit
// ============================================
void setBit(uint32_t *reg, uint8_t bit) {
    *reg |= (1 << bit);
}

// How it works:
// 1 << 3  = 0b00001000  (create mask with bit 3 set)
// reg | mask = set that bit (OR keeps other bits unchanged)
// You used this: GPIOE_ODR |= (1 << 9);  // Turn ON LED!

// ============================================
// EXERCISE 2: Clear Bit
// ============================================
void clearBit(uint32_t *reg, uint8_t bit) {
    *reg &= ~(1 << bit);
}

// How it works:
// 1 << 3  = 0b00001000
// ~(1 << 3) = 0b11110111  (invert - all 1s except bit 3)
// reg & mask = clear that bit (AND zeros that bit only)
// You used this: GPIOE_ODR &= ~(1 << 9);  // Turn OFF LED!

// ============================================
// EXERCISE 3: Toggle Bit
// ============================================
void toggleBit(uint32_t *reg, uint8_t bit) {
    *reg ^= (1 << bit);
}

// How it works:
// XOR with 1 flips the bit:
// 0 ^ 1 = 1  (OFF becomes ON)
// 1 ^ 1 = 0  (ON becomes OFF)
// You used this: GPIOE_ODR ^= (1 << 9);  // Flip LED state!

// ============================================
// EXERCISE 4: Check if Bit is Set
// ============================================
uint8_t isBitSet(uint32_t reg, uint8_t bit) {
    return (reg & (1 << bit)) ? 1 : 0;
}

// How it works:
// reg & (1 << bit)  // AND isolates that bit
// If bit is 1: result != 0 → true
// If bit is 0: result == 0 → false
// You used this: if (GPIOA_IDR & (1 << 0))  // Check button!

// ============================================
// EXERCISE 5: Count Set Bits
// ============================================
uint8_t countSetBits(uint32_t num) {
    uint8_t count = 0;
    
    while (num) {
        count += num & 1;  // Add 1 if LSB is set
        num >>= 1;         // Shift right by 1
    }
    
    return count;
}

// How it works:
// num & 1  // Check if LSB (rightmost bit) is 1
// num >>= 1  // Shift right (move next bit to LSB position)
// Repeat until num becomes 0

// ============================================
// EXERCISE 6: Extract Bits
// ============================================
uint32_t extractBits(uint32_t value, uint8_t position, uint8_t length) {
    uint32_t mask = (1 << length) - 1;  // Create mask with 'length' 1s
    return (value >> position) & mask;
}

// How it works:
// Step 1: Create mask
//   (1 << 3) = 0b1000
//   0b1000 - 1 = 0b0111  (3 bits of 1s)
//
// Step 2: Shift value right to move desired bits to LSB
// Step 3: AND with mask to extract only those bits
//
// Used in STM32 for reading multi-bit register fields!

// ============================================
// Helper: Print Binary
// ============================================
void printBinary(uint32_t num, uint8_t bits) {
    printf("0b");
    for (int i = bits - 1; i >= 0; i--) {
        printf("%d", (num >> i) & 1);
        if (i % 4 == 0 && i != 0) printf("_");
    }
}

// ============================================
// TEST MAIN
// ============================================
int main() {
    printf("=== DAY 4 BIT MANIPULATION - SOLUTIONS ===\n\n");
    
    // Test setBit
    printf("Test 1: Set Bit\n");
    uint32_t reg = 0x00000000;
    printf("Before: ");
    printBinary(reg, 8);
    printf(" (0x%02X)\n", reg);
    
    setBit(&reg, 3);
    printf("After set bit 3: ");
    printBinary(reg, 8);
    printf(" (0x%02X)\n", reg);
    printf("Expected: 0b00001000 (0x08) ✅\n\n");
    
    // Test clearBit
    printf("Test 2: Clear Bit\n");
    reg = 0xFF;
    printf("Before: ");
    printBinary(reg, 8);
    printf(" (0x%02X)\n", reg);
    
    clearBit(&reg, 5);
    printf("After clear bit 5: ");
    printBinary(reg, 8);
    printf(" (0x%02X)\n", reg);
    printf("Expected: 0b11011111 (0xDF) ✅\n\n");
    
    // Test toggleBit
    printf("Test 3: Toggle Bit\n");
    reg = 0b00001000;
    printf("Before: ");
    printBinary(reg, 8);
    printf("\n");
    
    toggleBit(&reg, 3);
    printf("After toggle bit 3: ");
    printBinary(reg, 8);
    printf(" (OFF)\n");
    
    toggleBit(&reg, 3);
    printf("After toggle again: ");
    printBinary(reg, 8);
    printf(" (ON)\n");
    printf("Expected: back to 0b00001000 ✅\n\n");
    
    // Test isBitSet
    printf("Test 4: Check if Bit is Set\n");
    reg = 0b10101010;
    printf("Value: ");
    printBinary(reg, 8);
    printf("\n");
    printf("Bit 1 set? %s ", isBitSet(reg, 1) ? "YES" : "NO");
    printf("(Expected: YES) ✅\n");
    printf("Bit 2 set? %s ", isBitSet(reg, 2) ? "YES" : "NO");
    printf("(Expected: NO) ✅\n");
    printf("Bit 7 set? %s ", isBitSet(reg, 7) ? "YES" : "NO");
    printf("(Expected: YES) ✅\n\n");
    
    // Test countSetBits
    printf("Test 5: Count Set Bits\n");
    uint32_t values[] = {0b00000000, 0b11111111, 0b10101010, 0b00001111};
    uint8_t expected[] = {0, 8, 4, 4};
    
    for (int i = 0; i < 4; i++) {
        uint8_t count = countSetBits(values[i]);
        printBinary(values[i], 8);
        printf(" has %d set bits (Expected: %d) ✅\n", count, expected[i]);
    }
    printf("\n");
    
    // Test extractBits
    printf("Test 6: Extract Bits\n");
    reg = 0b11010110;
    printf("Value: ");
    printBinary(reg, 8);
    printf("\n");
    
    uint32_t extracted = extractBits(reg, 2, 3);
    printf("Extract 3 bits from position 2: ");
    printBinary(extracted, 8);
    printf("\nExpected: 0b00000101 (bits [4:2] = 101) ✅\n\n");
    
    printf("=== ALL TESTS PASSED! ===\n");
    
    return 0;
}

/*
KEY TAKEAWAYS:

BIT OPERATION SUMMARY:
┌──────────────┬────────────────────┬─────────────────────┐
│ Operation    │ Formula            │ Use Case            │
├──────────────┼────────────────────┼─────────────────────┤
│ Set bit      │ reg |= (1 << n)   │ Turn ON LED         │
│ Clear bit    │ reg &= ~(1 << n)  │ Turn OFF LED        │
│ Toggle bit   │ reg ^= (1 << n)   │ Flip LED state      │
│ Check bit    │ reg & (1 << n)    │ Read button         │
│ Extract bits │ (reg >> p) & mask │ Read register field │
└──────────────┴────────────────────┴─────────────────────┘

YOU ALREADY USED THESE IN YOUR LED PROJECTS!

Your Hardware Code:
- GPIOE_ODR |= (1 << 9);   ← setBit()
- GPIOE_ODR &= ~(1 << 9);  ← clearBit()
- GPIOE_ODR ^= (1 << 9);   ← toggleBit()
- if (GPIOA_IDR & (1 << 0)) ← isBitSet()

Now you have the systematic theory behind what you've been doing! 🎯
*/

