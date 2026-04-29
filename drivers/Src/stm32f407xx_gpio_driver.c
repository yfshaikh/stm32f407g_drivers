
#include "stm32f407xx_gpio_driver.h"


// init and deinit

/** @param[in] pGPIOHandle : pointer to a GPIO_Handle_t structure that contains the configuration settings for the GPIO pin to be initialized 
    @brief : This function initializes the GPIO pin based on the configuration settings provided in the GPIO_Handle_t structure. It configures the mode, speed, pull-up/pull-down, output type and alternate function settings for the specified GPIO pin. It also enables the clock for the corresponding GPIO peripheral before configuring the pin settings.
    @return : None
*/
void GPIO_Init(GPIO_Handle_t *pGPIOHandle) {
    uint32_t temp = 0; // temporary register

    /* 1. configure the mode of the GPIO pin */
    if (pGPIOHandle->GPIO_PinConfig.GPIO_PinMode <= GPIO_MODE_ANALOG) { // non-interrupt mode (0-3)
        // @TEXTBOOK = [RM407][pg_number][8.4.1][GPIO port mode register (GPIOx_MODER)]
        // each pin has 2 bits in the MODER register, so we need to shift the mode value by 2 times the pin number to set the correct bits for the specified pin
        temp = (pGPIOHandle->GPIO_PinConfig.GPIO_PinMode << (2 * pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber));

        pGPIOHandle->pGPIOx->MODER &= ~(0x3 << (2 * pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber)); // clear the 2 bits corresponding to the pin number in the MODER register (using bitwise AND and NOT operator to clear the bits without affecting the other bits)
        pGPIOHandle->pGPIOx->MODER |= temp; // write the mode value to the MODER register (using bitwise OR operator to set the bits without affecting the other bits)
    } else {
        // interrupt mode

        if (pGPIOHandle->GPIO_PinConfig.GPIO_PinMode == GPIO_MODE_IT_FT) { // check if the interrupt mode is falling edge trigger

            /* FTSR: Stands for Falling Trigger Selection Register. It's a 32-bit register in the EXTI peripheral that controls which GPIO pins 
            (0-15, since there are 16 pins per port) will trigger an interrupt on a falling edge (when the voltage goes from high to low, e.g., 3.3V to 0V).*/


            // configure the falling trigger selection register (FTSR)
            EXTI->FTSR |= (1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber); // set the bit corresponding to the pin number in the FTSR register to enable falling edge trigger for the specified pin
            EXTI->RTSR &= ~(1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber); // clear the bit corresponding to the pin number in the RTSR register to disable rising edge trigger for the specified pin
        } else if (pGPIOHandle->GPIO_PinConfig.GPIO_PinMode == GPIO_MODE_IT_RT) {
            // configure the rising trigger selection register (RTSR)
            EXTI->RTSR |= (1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber); // set the bit corresponding to the pin number in the RTSR register to enable rising edge trigger for the specified pin
            EXTI->FTSR &= ~(1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber); // clear the bit corresponding to the pin number in the FTSR register to disable falling edge trigger for the specified pin
        } else if (pGPIOHandle->GPIO_PinConfig.GPIO_PinMode == GPIO_MODE_IT_RFT) {
            // configure both rising and falling trigger selection registers (RTSR and FTSR)
            EXTI->RTSR |= (1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber); // set the bit corresponding to the pin number in the RTSR register to enable rising edge trigger for the specified pin
            EXTI->FTSR |= (1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber); // set the bit corresponding to the pin number in the FTSR register to enable falling edge trigger for the specified pin
        }

        // configure the GPIO port selection in SYSCFG_EXTICR

        // enable the EXTI interrupt delivery using the interrupt mask register (IMR)
        EXTI->IMR |= (1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber); // set the bit corresponding to the pin number in the IMR register to enable interrupt delivery for the specified pin
        
}
temp = 0;


    /* 2. configure the speed of the GPIO pin */

    // each pin has 2 bits in the OSPEEDR register, so we need to shift the speed value by 2 times the pin number to set the correct bits for the specified pin
    temp = (pGPIOHandle->GPIO_PinConfig.GPIO_PinSpeed << (2 * pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber)); 
    pGPIOHandle->pGPIOx->OSPEEDR &= ~(0x3 << (2 * pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber)); // clear the 2 bits corresponding to the pin number in the OSPEEDR register (using bitwise AND and NOT operator to clear the bits without affecting the other bits)
    pGPIOHandle->pGPIOx->OSPEEDR |= temp; // write the speed value to the OSPEEDR register

    temp = 0;

    /* 3. configure the pull-up/pull-down settings of the GPIO pin */

    // each pin has 2 bits in the PUPDR register, so we need to shift the pull-up/pull-down value by 2 times the pin number to set the correct bits for the specified pin
    temp = (pGPIOHandle->GPIO_PinConfig.GPIO_PinPuPdControl << (2 * pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber)); 
    pGPIOHandle->pGPIOx->PUPDR &= ~(0x3 << (2 * pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber)); // clear the 2 bits corresponding to the pin number in the PUPDR register (using bitwise AND and NOT operator to clear the bits without affecting the other bits)
    pGPIOHandle->pGPIOx->PUPDR |= temp; // write the pull-up/pull-down value to the PUPDR register

    temp = 0;

    /* 4. configure the output type of the GPIO pin */

    // each pin has 1 bit in the OTYPER register, so we need to shift the output type value by the pin number to set the correct bit for the specified pin
    temp = (pGPIOHandle->GPIO_PinConfig.GPIO_PinOPType << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber); 
    pGPIOHandle->pGPIOx->OTYPER &= ~(0x1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber); // clear the bit corresponding to the pin number in the OTYPER register (using bitwise AND and NOT operator to clear the bit without affecting the other bits)
    pGPIOHandle->pGPIOx->OTYPER |= temp; // write the output type value to the OTYPER register

    temp = 0;

    /* 5. configure the alternate function mode of the GPIO pin */
    if (pGPIOHandle->GPIO_PinConfig.GPIO_PinMode == GPIO_MODE_ALTFN) {
        // each pin has 4 bits in the AFR register, so we need to shift the alternate function mode value by 4 times the pin number to set the correct bits for the specified pin
        uint8_t AFRIndex = pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber / 8; // determine which AFR register to use (AFR[0] for pins 0-7, AFR[1] for pins 8-15)
        uint8_t AFRPinNumber = pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber % 8; // determine the pin number within the AFR register (0-7)
        temp = (pGPIOHandle->GPIO_PinConfig.GPIO_PinAltFunMode << (4 * AFRPinNumber)); 
        pGPIOHandle->pGPIOx->AFR[AFRIndex] &= ~(0xF << (4 * AFRPinNumber)); // clear the 4 bits corresponding to the pin number in the AFR register
        pGPIOHandle->pGPIOx->AFR[AFRIndex] |= temp; // write the alternate function mode value to the appropriate AFR register
    }

}

/** @param[in] pGPIOx : base address of the GPIO peripheral to which the pin belongs */
void GPIO_DeInit(GPIO_RegDef_t *pGPIOx) {
    if (pGPIOx == GPIOA) {
        GPIOA_REG_RESET();
    } else if (pGPIOx == GPIOB) {
        GPIOB_REG_RESET();
    } else if (pGPIOx == GPIOC) {
        GPIOC_REG_RESET();
    } else if (pGPIOx == GPIOD) {
        GPIOD_REG_RESET();
    } else if (pGPIOx == GPIOE) {
        GPIOE_REG_RESET();
    } else if (pGPIOx == GPIOF) {
        GPIOF_REG_RESET();
    } else if (pGPIOx == GPIOG) {
        GPIOG_REG_RESET();
    } else if (pGPIOx == GPIOH) {
        GPIOH_REG_RESET();
    } else if (pGPIOx == GPIOI) {
        GPIOI_REG_RESET();
    }
}

// peripheral clock setup

/** @param[in] pGPIOx : base address of the GPIO peripheral to enable or disable the clock for */
/** @param[in] Enable : ENABLE or DISABLE macros to enable or disable the clock for the given GPIO peripheral */
void GPIO_PeriClockControl(GPIO_RegDef_t *pGPIOx, uint8_t Enable) {
    if (Enable == ENABLE) {
        if (pGPIOx == GPIOA) {
            GPIOA_PCLK_EN();
        } else if (pGPIOx == GPIOB) {
            GPIOB_PCLK_EN();
        } else if (pGPIOx == GPIOC) {
            GPIOC_PCLK_EN();
        } else if (pGPIOx == GPIOD) {
            GPIOD_PCLK_EN();
        } else if (pGPIOx == GPIOE) {
            GPIOE_PCLK_EN();
        } else if (pGPIOx == GPIOF) {
            GPIOF_PCLK_EN();
        } else if (pGPIOx == GPIOG) {
            GPIOG_PCLK_EN();
        } else if (pGPIOx == GPIOH) {
            GPIOH_PCLK_EN();
        } else if (pGPIOx == GPIOI) {
            GPIOI_PCLK_EN();
        }
    } else {
        if (pGPIOx == GPIOA) {
            GPIOA_PCLK_DI();
        } else if (pGPIOx == GPIOB) {
            GPIOB_PCLK_DI();
        } else if (pGPIOx == GPIOC) {
            GPIOC_PCLK_DI();
        } else if (pGPIOx == GPIOD) {
            GPIOD_PCLK_DI();
        } else if (pGPIOx == GPIOE) {
            GPIOE_PCLK_DI();
        } else if (pGPIOx == GPIOF) {
            GPIOF_PCLK_DI();
        } else if (pGPIOx == GPIOG) {
            GPIOG_PCLK_DI();
        } else if (pGPIOx == GPIOH) {
            GPIOH_PCLK_DI();
        } else if (pGPIOx == GPIOI) {
            GPIOI_PCLK_DI();
        }
    }
}

// data read and write

/** @param[in] pGPIOx : base address of the GPIO peripheral to which the pin belongs */
/** @param[in] PinNumber : pin number (0 to 15) of the GPIO pin to which the value needs to be written */
/** @param[in] Value : value to be written to the GPIO pin (0 or 1) */
void GPIO_WriteToOutputPin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber, uint8_t Value) {
    if (Value == GPIO_PIN_SET) {
        // write 1 to the output data register at the bit field corresponding to the pin number to set the pin
        // ODR register is used to write the output value to the pin, and each pin corresponds to a specific bit in the ODR register, so we need to set the bit corresponding to the pin number to 1 to set the pin
        pGPIOx->ODR |= (1 << PinNumber); // using bitwise OR operator to set the bit without affecting the other bits
    } else {
        // write 0 to the output data register at the bit field corresponding to the pin number to reset the pin
        pGPIOx->ODR &= ~(1 << PinNumber); // using bitwise AND and NOT operator to clear the bit without affecting the other bits
    }
}

/** @param[in] pGPIOx : base address of the GPIO peripheral to which the pin belongs */
/** @param[in] Value : value to be written to the GPIO port (16-bit value) */
void GPIO_WriteToOutputPort(GPIO_RegDef_t *pGPIOx, uint16_t Value) {
    pGPIOx->ODR = Value;
}

/** @param[in] pGPIOx : base address of the GPIO peripheral to which the pin belongs */
/** @param[in] PinNumber : pin number (0 to 15) of the GPIO pin to which the value needs to be read */
/** @return : value read from the GPIO pin (0 or 1) 
    @textbook = [RM407][pg_number][8.4.5][GPIO port input data register (GPIOx_IDR)]
    @brief : This function reads the value from the specified GPIO pin by right shifting the IDR register by the pin number to get the value of the specified pin, and then using bitwise
*/
uint8_t GPIO_ReadFromInputPin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber) {
    uint8_t value;
    value = (uint8_t)((pGPIOx->IDR >> PinNumber) & 0x00000001); // right shift the IDR register by the pin number to get the value of the specified pin, and then use bitwise AND operator with 0x00000001 to get only the least significant bit (which represents the value of the pin)
    return value;
}

/** @param[in] pGPIOx : base address of the GPIO peripheral to which the pin belongs */
/** @return : value read from the GPIO port (16-bit value) */
uint16_t GPIO_ReadFromInputPort(GPIO_RegDef_t *pGPIOx) {
    uint16_t value;
    value = (uint16_t)(pGPIOx->IDR); // read the entire IDR register to get the value of all the pins in the port
    return value;
}

// other peripheral control APIs

/** @param[in] pGPIOx : base address of the GPIO peripheral to which the pin belongs */
/** @param[in] PinNumber : pin number (0 to 15) of the GPIO pin to be toggled */
void GPIO_ToggleOutputPin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber) {
    pGPIOx->ODR ^= (1 << PinNumber); // using bitwise XOR operator to toggle the bit corresponding to the pin number without affecting the other bits
}

/** @param[in] IRQNumber : IRQ number of the GPIO pin for which the interrupt needs to be configured */
/** @param[in] IRQPriority : priority of the IRQ (0 to 15, where 0 is the highest priority) */
/** @param[in] Enable : ENABLE or DISABLE macros to enable or disable the interrupt for the given GPIO pin */
void GPIO_IRQConfig(uint8_t IRQNumber, uint8_t IRQPriority, uint8_t Enable);

/** @param[in] PinNumber : pin number (0 to 15) of the GPIO pin for which the interrupt needs to be handled */
void GPIO_IRQHandling(uint8_t PinNumber);

