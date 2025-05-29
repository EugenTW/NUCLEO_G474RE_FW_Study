#include "stm32g474xx.h"

constexpr uint32_t GPIOAEN = (1U << 0);
constexpr uint32_t PIN5 = (1U << 5);
constexpr uint32_t LED_PIN = PIN5;
constexpr uint32_t LED_PIN_SHIFTED = (1U << (5 + 16));  // 用於 BSRR reset

class GPIOController {
public:
    static void enableGPIOAClock() {
        RCC->AHB2ENR |= GPIOAEN;
    }

    static void configurePA5AsOutput() {
        GPIOA->MODER &= ~(3U << (5 * 2));  // Clear MODER11:10
        GPIOA->MODER |=  (1U << (5 * 2));  // Set MODER10 = 1 (output)
    }

    static void setPA5High() {
        GPIOA->BSRR = LED_PIN;  // Set bit 5
    }

    static void setPA5Low() {
        GPIOA->BSRR = LED_PIN_SHIFTED;  // Reset bit 5 (bit 21 = 5+16)
    }

    static void delay(volatile int count) {
        while (count--) {
            __asm__ volatile("nop");
        }
    }
};

int main() {
    GPIOController::enableGPIOAClock();
    GPIOController::configurePA5AsOutput();

    while (true) {
        GPIOController::setPA5High();
        GPIOController::delay(100000);
        GPIOController::setPA5Low();
        GPIOController::delay(100000);
    }
}
