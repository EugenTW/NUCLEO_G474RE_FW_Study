#include "stm32g474xx.h"  // CMSIS header, contains all register definitions

int main(void)
{
  // 1. Enable GPIOA clock (AHB2 bus)
  RCC->AHB2ENR |= RCC_AHB2ENR_GPIOAEN;

  // Small delay to ensure clock is stable
  volatile int delay = 10000;
  while (delay--) __asm__("nop");

  // 2. Set PA5 to general output mode (MODER = 01)
  GPIOA->MODER &= ~(0x3 << (5 * 2));  // Clear MODER5 bits
  GPIOA->MODER |=  (0x1 << (5 * 2));  // Set as output mode

  // 3. Disable pull-up/pull-down (PUPDR = 00)
  GPIOA->PUPDR &= ~(0x3 << (5 * 2));

  // 4. Set to push-pull output (OTYPER = 0)
  GPIOA->OTYPER &= ~(1 << 5);

  // 5. Set output speed to low (OSPEEDR = 00, optional)
  GPIOA->OSPEEDR &= ~(0x3 << (5 * 2));

  // 6. Set PA5 to high level -> turn on LED
  GPIOA->ODR |= (1 << 5);

  // 7. Enter infinite loop
  while (1) {
    // Always on
  }
}
