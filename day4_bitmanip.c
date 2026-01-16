/**
 * Day 4 - Bit Manipulation Practice
 * Complete the functions below
 */

#include <stdio.h>
#include <stdint.h>

// ============================================
// EXERCISE 1: Set Bit
// ============================================
void setBit(uint32_t *reg, uint8_t bit) {
    // TODO: Your code here
    // Hint: Use OR with left shift
}

// ============================================
// EXERCISE 2: Clear Bit
// ============================================
void clearBit(uint32_t *reg, uint8_t bit) {
    // TODO: Your code here
    // Hint: Use AND with NOT of left shift
}

// ============================================
// EXERCISE 3: Toggle Bit
// ============================================
void toggleBit(uint32_t *reg, uint8_t bit) {
    // TODO: Your code here
    // Hint: Use XOR with left shift
}

// ============================================
// EXERCISE 4: Check if Bit is Set
// ============================================
uint8_t isBitSet(uint32_t reg, uint8_t bit) {
    // TODO: Your code here
    // Hint: Use AND with left shift, check if result != 0
    return 0;  // Replace this
}

// ============================================
// EXERCISE 5: Count Set Bits
// ============================================
uint8_t countSetBits(uint32_t num) {
    // TODO: Your code here
    // Hint: Loop, check LSB, shift right
    return 0;  // Replace this
}

// ============================================
// EXERCISE 6: Extract Bits
// ============================================
uint32_t extractBits(uint32_t value, uint8_t position, uint8_t length) {
    // TODO: Your code here
    // Hint: Create mask, shift, then AND
    return 0;  // Replace this
}

// ============================================
// Helper: Print Binary
// ============================================
void printBinary(uint32_t num, uint8_t bits) {
    printf("0b");
    for (int i = bits - 1; i >= 0; i--) {
        printf("%d", (num >> i) & 1);
        if (i % 4 == 0 && i != 0) printf("_");  // Separator every 4 bits
    }
}

// ============================================
// TEST MAIN
// ============================================
int main() {
    printf("=== DAY 4 BIT MANIPULATION PRACTICE ===\n\n");
    
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
    printf("Expected: 0b00001000 (0x08)\n\n");
    
    // Test clearBit
    printf("Test 2: Clear Bit\n");
    reg = 0xFF;  // All bits set
    printf("Before: ");
    printBinary(reg, 8);
    printf(" (0x%02X)\n", reg);
    
    clearBit(&reg, 5);
    printf("After clear bit 5: ");
    printBinary(reg, 8);
    printf(" (0x%02X)\n", reg);
    printf("Expected: 0b11011111 (0xDF)\n\n");
    
    // Test toggleBit
    printf("Test 3: Toggle Bit\n");
    reg = 0b00001000;
    printf("Before: ");
    printBinary(reg, 8);
    printf("\n");
    
    toggleBit(&reg, 3);
    printf("After toggle bit 3: ");
    printBinary(reg, 8);
    printf("\n");
    
    toggleBit(&reg, 3);
    printf("After toggle again: ");
    printBinary(reg, 8);
    printf("\nExpected: back to 0b00001000\n\n");
    
    // Test isBitSet
    printf("Test 4: Check if Bit is Set\n");
    reg = 0b10101010;
    printf("Value: ");
    printBinary(reg, 8);
    printf("\n");
    printf("Bit 1 set? %s (Expected: YES)\n", isBitSet(reg, 1) ? "YES" : "NO");
    printf("Bit 2 set? %s (Expected: NO)\n", isBitSet(reg, 2) ? "YES" : "NO");
    printf("Bit 7 set? %s (Expected: YES)\n\n", isBitSet(reg, 7) ? "YES" : "NO");
    
    // Test countSetBits
    printf("Test 5: Count Set Bits\n");
    uint32_t values[] = {0b00000000, 0b11111111, 0b10101010, 0b00001111};
    uint8_t expected[] = {0, 8, 4, 4};
    
    for (int i = 0; i < 4; i++) {
        uint8_t count = countSetBits(values[i]);
        printBinary(values[i], 8);
        printf(" has %d set bits (Expected: %d)\n", count, expected[i]);
    }
    printf("\n");
    
    // Test extractBits
    printf("Test 6: Extract Bits\n");
    reg = 0b11010110;
    printf("Value: ");
    printBinary(reg, 8);
    printf("\n");
    
    uint32_t extracted = extractBits(reg, 2, 3);  // Extract 3 bits from position 2
    printf("Extract 3 bits from position 2: ");
    printBinary(extracted, 8);
    printf("\nExpected: 0b00000101 (bits [4:2] = 101)\n");
    
    return 0;
}

