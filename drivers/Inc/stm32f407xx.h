#ifndef INC_STM32F407XX_H_
#define INC_STM32F407XX_H_

#include <stdint.h>
#define __vo volatile

// base addresses of flash and sram memories
#define FLASH_BASEADDR            0x08000000UL // unsigned long
#define SRAM1_BASEADDR             0x20000000UL
#define SRAM SRAM1_BASEADDR
#define ROM_BASEADDR              0x1FFF0000UL
#define SRAM2_BASEADDR             0x2001C000UL

// base addresses of peripheral buses
#define PERIPH_BASEADDR           0x40000000UL
#define APB1PERIPH_BASEADDR       PERIPH_BASEADDR // APB1 peripherals base address is same as peripheral base address
#define APB2PERIPH_BASEADDR       0x40010000UL
#define AHB1PERIPH_BASEADDR       0x40020000UL
#define AHB2PERIPH_BASEADDR       0x50000000UL

// bases addresses of peripherals which are hanging on AHB1 bus
#define GPIOA_BASEADDR            (AHB1PERIPH_BASEADDR + 0x0000UL) // gpioa is the first peripheral on ahb1 bus so its base address is same as ahb1 peripheral base address
#define GPIOB_BASEADDR            (AHB1PERIPH_BASEADDR + 0x0400UL)
#define GPIOC_BASEADDR            (AHB1PERIPH_BASEADDR + 0x0800UL)
#define GPIOD_BASEADDR            (AHB1PERIPH_BASEADDR + 0x0C00UL)
#define GPIOE_BASEADDR            (AHB1PERIPH_BASEADDR + 0x1000UL)
#define GPIOF_BASEADDR            (AHB1PERIPH_BASEADDR + 0x1400UL)
#define GPIOG_BASEADDR            (AHB1PERIPH_BASEADDR + 0x1800UL)
#define GPIOH_BASEADDR            (AHB1PERIPH_BASEADDR + 0x1C00UL)
#define GPIOI_BASEADDR            (AHB1PERIPH_BASEADDR + 0x2000UL)
#define RCC_BASEADDR             (AHB1PERIPH_BASEADDR + 0x3800UL)


// base addresses of peripherals which are hanging on APB1 bus
#define I2C1_BASEADDR             (APB1PERIPH_BASEADDR + 0x5400UL)
#define I2C2_BASEADDR             (APB1PERIPH_BASEADDR + 0x5800UL)
#define I2C3_BASEADDR             (APB1PERIPH_BASEADDR + 0x5C00UL)
#define SPI2_BASEADDR             (APB1PERIPH_BASEADDR + 0x3800UL)
#define SPI3_BASEADDR             (APB1PERIPH_BASEADDR + 0x3C00UL)
#define USART2_BASEADDR           (APB1PERIPH_BASEADDR + 0x4400UL)
#define USART3_BASEADDR           (APB1PERIPH_BASEADDR + 0x4800UL)
#define UART4_BASEADDR            (APB1PERIPH_BASEADDR + 0x4C00UL)
#define UART5_BASEADDR            (APB1PERIPH_BASEADDR + 0x5000UL)

// base addresses of peripherals which are hanging on APB2 bus
#define EXTI_BASEADDR             (APB2PERIPH_BASEADDR + 0x3C00UL)
#define SYSCFG_BASEADDR           (APB2PERIPH_BASEADDR + 0x3800UL)
#define SPI1_BASEADDR             (APB2PERIPH_BASEADDR + 0x3000UL)
#define USART1_BASEADDR           (APB2PERIPH_BASEADDR + 0x1000UL)
#define USART6_BASEADDR           (APB2PERIPH_BASEADDR + 0x1400UL)

/***************** peripheral register definition structures *****************/

// note: registers of a peripheral are specific to the microcontroller, 

// this structure will be used to access the registers of GPIO peripheral
// structs automatically add 4 bytes of padding after each member, so we can directly use uint32_t for each register without worrying about the padding
// MODER register is at offset 0x00, OTYPER is at offset 0x04, OSPEEDR is at offset 0x08 and so on, so we can directly use uint32_t for each register and the compiler will take care of the rest
// the registers are volatile because they can change at any time (for example, the input data register can change when the state of the pin changes), so we need to tell the compiler not to optimize access to these registers
typedef struct {
    __vo uint32_t MODER; // GPIO port mode register
    __vo uint32_t OTYPER; // GPIO port output type register
    __vo uint32_t OSPEEDR; // GPIO port output speed register
    __vo uint32_t PUPDR; // GPIO port pull-up/pull-down register
    __vo uint32_t IDR; // GPIO port input data register
    __vo uint32_t ODR; // GPIO port output data register
    __vo uint32_t BSRR; // GPIO port bit set/reset register
    __vo uint32_t LCKR; // GPIO port configuration lock register
    __vo uint32_t AFR[2]; // GPIO alternate function registers (AFR[0] for pins 0-7, AFR[1] for pins 8-15)

} GPIO_RegDef_t;

typedef struct {
    __vo uint32_t CR; // RCC clock control register
    __vo uint32_t PLLCFGR; // RCC PLL configuration register
    __vo uint32_t CFGR; // RCC clock configuration register
    __vo uint32_t CIR; // RCC clock interrupt register
    __vo uint32_t AHB1RSTR; // RCC AHB1 peripheral reset register
    __vo uint32_t AHB2RSTR; // RCC AHB2 peripheral reset register
    __vo uint32_t AHB3RSTR; // RCC AHB3 peripheral reset register
    uint32_t RESERVED0; // reserved space to maintain the memory map, this will be ignored by the compiler
    __vo uint32_t APB1RSTR; // RCC APB1 peripheral reset register
    __vo uint32_t APB2RSTR; // RCC APB2 peripheral reset register
    uint32_t RESERVED1[2]; // reserved space to maintain the memory map, this will be ignored by the compiler
    __vo uint32_t AHB1ENR; // RCC AHB1 peripheral clock enable register
    __vo uint32_t AHB2ENR; // RCC AHB2 peripheral clock enable register
    __vo uint32_t AHB3ENR; // RCC AHB3 peripheral clock enable register
    uint32_t RESERVED2; // reserved space to maintain the memory map, this will be ignored by the compiler
    __vo uint32_t APB1ENR; // RCC APB1 peripheral clock enable register
    __vo uint32_t APB2ENR; // RCC APB2 peripheral clock enable register
    uint32_t RESERVED3[2]; // reserved space to maintain the memory map, this will be ignored by the compiler
    __vo uint32_t AHB1LPENR; // RCC AHB1 peripheral clock enable in low power mode register
    __vo uint32_t AHB2LPENR; // RCC AHB2 peripheral clock enable in low power mode register
    __vo uint32_t AHB3LPENR; // RCC AHB3 peripheral clock enable in low power mode register
    uint32_t RESERVED4; // reserved space to maintain the memory map, this will be ignored by the compiler
    __vo uint32_t APB1LPENR; // RCC APB1 peripheral clock enable in low power mode register
    __vo uint32_t APB2LPENR; // RCC APB2 peripheral clock enable in low power mode register
    uint32_t RESERVED5[2]; // reserved space to maintain the memory map, this will be ignored by the compiler
    __vo uint32_t BDCR; // RCC Backup domain control register
    __vo uint32_t CSR; // RCC clock control & status register
    uint32_t RESERVED6[2]; // reserved space to maintain the memory map, this will be ignored by the compiler
    __vo uint32_t SSCGR; // RCC spread spectrum clock generation register
    __vo uint32_t PLLI2SCFGR; // RCC PLLI2S configuration register
    __vo uint32_t PLLSAICFGR; // RCC PLLSAI configuration register
    __vo uint32_t DCKCFGR; // RCC Dedicated Clocks Configuration Register
    __vo uint32_t CKGATENR; // RCC Clocks Gated ENable Register
    __vo uint32_t DCKCFGR2; // RCC Dedicated Clocks Configuration Register

} RCC_RegDef_t;

// structure for EXTI peripheral
typedef struct {
    __vo uint32_t IMR; // EXTI Interrupt mask register
    __vo uint32_t EMR; // EXTI Event mask register
    __vo uint32_t RTSR; // EXTI Rising trigger selection register
    __vo uint32_t FTSR; // EXTI Falling trigger selection register
    __vo uint32_t SWIER; // EXTI Software interrupt event register
    __vo uint32_t PR; // EXTI Pending register 
} EXTI_RegDef_t;

// peripheral register definition structure for SYSCFG peripheral
typedef struct {
    __vo uint32_t MEMRMP; // SYSCFG memory remap register
    __vo uint32_t PMC; // SYSCFG peripheral mode configuration register
    __vo uint32_t EXTICR[4]; // SYSCFG external interrupt configuration registers (EXTICR[0] for EXTI0-3, EXTICR[1] for EXTI4-7, EXTICR[2] for EXTI8-11, EXTICR[3] for EXTI12-15)
    uint32_t RESERVED1[2]; // reserved space to maintain the memory map, this will be ignored by the compiler
    __vo uint32_t CMPCR; // SYSCFG Compensation cell control register
} SYSCFG_RegDef_t;



// peripheral definitions
#define GPIOA ((GPIO_RegDef_t *) GPIOA_BASEADDR) // typecasting the base address to a pointer of type GPIO_RegDef_t, so that we can access the registers of GPIOA peripheral using this pointer
#define GPIOB ((GPIO_RegDef_t *) GPIOB_BASEADDR)
#define GPIOC ((GPIO_RegDef_t *) GPIOC_BASEADDR)
#define GPIOD ((GPIO_RegDef_t *) GPIOD_BASEADDR)
#define GPIOE ((GPIO_RegDef_t *) GPIOE_BASEADDR)
#define GPIOF ((GPIO_RegDef_t *) GPIOF_BASEADDR)
#define GPIOG ((GPIO_RegDef_t *) GPIOG_BASEADDR)
#define GPIOH ((GPIO_RegDef_t *) GPIOH_BASEADDR)
#define GPIOI ((GPIO_RegDef_t *) GPIOI_BASEADDR)

#define RCC ((RCC_RegDef_t *) RCC_BASEADDR)

#define EXTI ((EXTI_RegDef_t *) EXTI_BASEADDR)

#define SYSCFG ((SYSCFG_RegDef_t *) SYSCFG_BASEADDR)

// clock enable macros for GPIO peripherals
/*
 * RCC->AHB1ENR is the register that controls the clock for the peripherals hanging on AHB1 bus, so we need to set the specific bit in this register to enable the clock for a specific peripheral
 * 
 * 1 << 0 : start with 0000 0001 => shift left by 0 positions => 0000 0001 => |= with AHB1ENR register will set the 0th bit of AHB1ENR register to 1 (but not affect the other bits), which will enable the clock for GPIOA peripheral
 * 1 << 1 : start with 0000 0001 => shift left by 1 position => 0000 0010 => |= with AHB1ENR register will set the 1st bit of AHB1ENR register to 1 (but not affect the other bits), which will enable the clock for GPIOB peripheral
 * 
 * use bitwise OR operator (|=) to set the specific bit in the AHB1ENR register without affecting the other bits
 * use bitwise shift operator (<<) to create a bitmask for the specific bit that we want to set in the AHB1ENR register
 * use bitwise AND and NOT operator (&= ~) to clear the specific bit in the AHB1ENR register without affecting the other bits
*/
#define GPIOA_PCLK_EN() (RCC->AHB1ENR |= (1 << 0)) // enable the clock for GPIOA peripheral by setting the 0th bit of AHB1ENR register
#define GPIOB_PCLK_EN() (RCC->AHB1ENR |= (1 << 1)) // enable the clock for GPIOB peripheral by setting the 1st bit of AHB1ENR register
#define GPIOC_PCLK_EN() (RCC->AHB1ENR |= (1 << 2)) // enable the clock for GPIOC peripheral by setting the 2nd bit of AHB1ENR register
#define GPIOD_PCLK_EN() (RCC->AHB1ENR |= (1 << 3)) // enable the clock for GPIOD peripheral by setting the 3rd bit of AHB1ENR register
#define GPIOE_PCLK_EN() (RCC->AHB1ENR |= (1 << 4)) // enable the clock for GPIOE peripheral by setting the 4th bit of AHB1ENR register
#define GPIOF_PCLK_EN() (RCC->AHB1ENR |= (1 << 5)) // enable the clock for GPIOF peripheral by setting the 5th bit of AHB1ENR register
#define GPIOG_PCLK_EN() (RCC->AHB1ENR |= (1 << 6)) // enable the clock for GPIOG peripheral by setting the 6th bit of AHB1ENR register
#define GPIOH_PCLK_EN() (RCC->AHB1ENR |= (1 << 7)) // enable the clock for GPIOH peripheral by setting the 7th bit of AHB1ENR register
#define GPIOI_PCLK_EN() (RCC->AHB1ENR |= (1 << 8)) // enable the clock for GPIOI peripheral by setting the 8th bit of AHB1ENR register  

// clock enable macros for I2C peripherals
#define I2C1_PCLK_EN() (RCC->APB1ENR |= (1 << 21)) // enable the clock for I2C1 peripheral by setting the 21st bit of APB1ENR register
#define I2C2_PCLK_EN() (RCC->APB1ENR |= (1 << 22)) // enable the clock for I2C2 peripheral by setting the 22nd bit of APB1ENR register
#define I2C3_PCLK_EN() (RCC->APB1ENR |= (1 << 23)) // enable the clock for I2C3 peripheral by setting the 23rd bit of APB1ENR register  


// clock enable macros for SPI peripherals
#define SPI1_PCLK_EN() (RCC->APB2ENR |= (1 << 12)) // enable the clock for SPI1 peripheral by setting the 12th bit of APB2ENR register
#define SPI2_PCLK_EN() (RCC->APB1ENR |= (1 << 14)) // enable the clock for SPI2 peripheral by setting the 14th bit of APB1ENR register
#define SPI3_PCLK_EN() (RCC->APB1ENR |= (1 << 15)) // enable the clock for SPI3 peripheral by setting the 15th bit of APB1ENR register

// clock enable macros for USART peripherals
#define USART1_PCLK_EN() (RCC->APB2ENR |= (1 << 4)) // enable the clock for USART1 peripheral by setting the 4th bit of APB2ENR register
#define USART2_PCLK_EN() (RCC->APB1ENR |= (1 << 17)) // enable the clock for USART2 peripheral by setting the 17th bit of APB1ENR register
#define USART3_PCLK_EN() (RCC->APB1ENR |= (1 << 18)) // enable the clock for USART3 peripheral by setting the 18th bit of APB1ENR register
#define UART4_PCLK_EN() (RCC->APB1ENR |= (1 << 19)) // enable the clock for UART4 peripheral by setting the 19th bit of APB1ENR register
#define UART5_PCLK_EN() (RCC->APB1ENR |= (1 << 20)) // enable the clock for UART5 peripheral by setting the 20th bit of APB1ENR register
#define USART6_PCLK_EN() (RCC->APB2ENR |= (1 << 5)) // enable the clock for USART6 peripheral by setting the 5th bit of APB2ENR register


// clock disable macros for GPIO peripherals
#define GPIOA_PCLK_DI() (RCC->AHB1ENR &= ~(1 << 0)) // disable the clock for GPIOA peripheral by clearing the 0th bit of AHB1ENR register
#define GPIOB_PCLK_DI() (RCC->AHB1ENR &= ~(1 << 1)) // disable the clock for GPIOB peripheral by clearing the 1st bit of AHB1ENR register
#define GPIOC_PCLK_DI() (RCC->AHB1ENR &= ~(1 << 2)) // disable the clock for GPIOC peripheral by clearing the 2nd bit of AHB1ENR register
#define GPIOD_PCLK_DI() (RCC->AHB1ENR &= ~(1 << 3)) // disable the clock for GPIOD peripheral by clearing the 3rd bit of AHB1ENR register
#define GPIOE_PCLK_DI() (RCC->AHB1ENR &= ~(1 << 4)) // disable the clock for GPIOE peripheral by clearing the 4th bit of AHB1ENR register
#define GPIOF_PCLK_DI() (RCC->AHB1ENR &= ~(1 << 5)) // disable the clock for GPIOF peripheral by clearing the 5th bit of AHB1ENR register
#define GPIOG_PCLK_DI() (RCC->AHB1ENR &= ~(1 << 6)) // disable the clock for GPIOG peripheral by clearing the 6th bit of AHB1ENR register
#define GPIOH_PCLK_DI() (RCC->AHB1ENR &= ~(1 << 7)) // disable the clock for GPIOH peripheral by clearing the 7th bit of AHB1ENR register
#define GPIOI_PCLK_DI() (RCC->AHB1ENR &= ~(1 << 8)) // disable the clock for GPIOI peripheral by clearing the 8th bit of AHB1ENR register

// generic macros
#define ENABLE 1
#define DISABLE 0
#define SET ENABLE
#define RESET DISABLE
#define GPIO_PIN_SET SET
#define GPIO_PIN_RESET RESET

/* Macros to reset GPIO registers */

// note: we need to set the specific bit in the AHB1RSTR register to reset the corresponding GPIO peripheral, 
// and then clear the bit to bring the peripheral out of reset state. 
// We can use a do-while(0) loop to ensure that both operations (setting and clearing the bit) are executed together as a single statement, 
// which is important for ensuring that the peripheral is properly reset without any unintended side effects from other code that might be interleaved between these operations.
#define GPIOA_REG_RESET() do { (RCC->AHB1RSTR |= (1 << 0)); (RCC->AHB1RSTR &= ~(1 << 0)); } while(0) // reset GPIOA peripheral by setting the 0th bit of AHB1RSTR register and then clearing it
#define GPIOB_REG_RESET() do { (RCC->AHB1RSTR |= (1 << 1)); (RCC->AHB1RSTR &= ~(1 << 1)); } while(0) // reset GPIOB peripheral by setting the 1st bit of AHB1RSTR register and then clearing it
#define GPIOC_REG_RESET() do { (RCC->AHB1RSTR |= (1 << 2)); (RCC->AHB1RSTR &= ~(1 << 2)); } while(0) // reset GPIOC peripheral by setting the 2nd bit of AHB1RSTR register and then clearing it
#define GPIOD_REG_RESET() do { (RCC->AHB1RSTR |= (1 << 3)); (RCC->AHB1RSTR &= ~(1 << 3)); } while(0) // reset GPIOD peripheral by setting the 3rd bit of AHB1RSTR register and then clearing it
#define GPIOE_REG_RESET() do { (RCC->AHB1RSTR |= (1 << 4)); (RCC->AHB1RSTR &= ~(1 << 4)); } while(0) // reset GPIOE peripheral by setting the 4th bit of AHB1RSTR register and then clearing it
#define GPIOF_REG_RESET() do { (RCC->AHB1RSTR |= (1 << 5)); (RCC->AHB1RSTR &= ~(1 << 5)); } while(0) // reset GPIOF peripheral by setting the 5th bit of AHB1RSTR register and then clearing it
#define GPIOG_REG_RESET() do { (RCC->AHB1RSTR |= (1 << 6)); (RCC->AHB1RSTR &= ~(1 << 6)); } while(0) // reset GPIOG peripheral by setting the 6th bit of AHB1RSTR register and then clearing it
#define GPIOH_REG_RESET() do { (RCC->AHB1RSTR |= (1 << 7)); (RCC->AHB1RSTR &= ~(1 << 7)); } while(0) // reset GPIOH peripheral by setting the 7th bit of AHB1RSTR register and then clearing it
#define GPIOI_REG_RESET() do { (RCC->AHB1RSTR |= (1 << 8)); (RCC->AHB1RSTR &= ~(1 << 8)); } while(0) // reset GPIOI peripheral by setting the 8th bit of AHB1RSTR register and then clearing it


// return port code for given GPIO base address, this will be used in SYSCFG_EXTICR register configuration
#define GPIO_BASEADDR_TO_CODE(x) ((x == GPIOA) ? 0 : \
                                  (x == GPIOB) ? 1 : \
                                  (x == GPIOC) ? 2 : \
                                  (x == GPIOD) ? 3 : \
                                  (x == GPIOE) ? 4 : \
                                  (x == GPIOF) ? 5 : \
                                  (x == GPIOG) ? 6 : \
                                  (x == GPIOH) ? 7 : \
                                  (x == GPIOI) ? 8 : 0)



#include "stm32f407xx_gpio_driver.h"

#endif // INC_STM32F407XX_H_