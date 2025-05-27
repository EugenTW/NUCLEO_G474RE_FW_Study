#include <cstdint>

// Register access encapsulated in structs
struct GPIOA_Registers {
    static volatile uint32_t& MODER()   { return *(volatile uint32_t*)0x48000000UL; }
    static volatile uint32_t& OTYPER()  { return *(volatile uint32_t*)0x48000004UL; }
    static volatile uint32_t& ODR()     { return *(volatile uint32_t*)0x48000014UL; }
};

struct RCC_Registers {
    static volatile uint32_t& AHB2ENR() { return *(volatile uint32_t*)0x4002104CUL; }
};

constexpr uint32_t PIN5 = (1U << 5);

inline void simple_delay(volatile uint32_t t) {
    while (t--);
}

int main() {
    RCC_Registers::AHB2ENR() |= (1U << 0);
    (void)RCC_Registers::AHB2ENR();

    GPIOA_Registers::MODER() &= ~(3U << (5 * 2));
    GPIOA_Registers::MODER() |=  (1U << (5 * 2));
    GPIOA_Registers::OTYPER() &= ~(1U << 5);

    while (1) {
        GPIOA_Registers::ODR() &= ~PIN5;
        simple_delay(2000000);
        GPIOA_Registers::ODR() |= PIN5;
        simple_delay(2000000);
    }
}
