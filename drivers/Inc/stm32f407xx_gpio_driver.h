
#ifndef INC_STM32F407XX_GPIO_DRIVER_H_
#define INC_STM32F407XX_GPIO_DRIVER_H_


#include "stm32f407xx.h"





typedef struct {
    uint8_t GPIO_PinNumber; // possible values from 0 to 15
    uint8_t GPIO_PinMode; // possible values from @GPIO_PIN_MODES
    uint8_t GPIO_PinSpeed; // possible values from @GPIO_PIN_SPEED
    uint8_t GPIO_PinPuPdControl; // possible values from @GPIO_PIN_PUPD
    uint8_t GPIO_PinOPType; // possible values from @GPIO_PIN_OP_TYPE
    uint8_t GPIO_PinAltFunMode; // possible values from @GPIO_PIN_ALT_FUN_MODE
} GPIO_PinConfig_t;

// this handle structure will be used to hold the information about the GPIO pin that we want to configure, 
// such as the pin number, mode, speed, pull-up/pull-down configuration, output type and alternate function mode
typedef struct {
    GPIO_RegDef_t *pGPIOx; // this holds the base address of the GPIO port to which the pin belongs
    GPIO_PinConfig_t GPIO_PinConfig; // this holds the GPIO pin configuration settings

} GPIO_Handle_t;


/*
* @GPIO_PIN_NUMBERS
* GPIO pin numbers
*/
#define GPIO_PIN_NO_0 0
#define GPIO_PIN_NO_1 1
#define GPIO_PIN_NO_2 2
#define GPIO_PIN_NO_3 3
#define GPIO_PIN_NO_4 4
#define GPIO_PIN_NO_5 5
#define GPIO_PIN_NO_6 6
#define GPIO_PIN_NO_7 7
#define GPIO_PIN_NO_8 8
#define GPIO_PIN_NO_9 9
#define GPIO_PIN_NO_10 10
#define GPIO_PIN_NO_11 11
#define GPIO_PIN_NO_12 12
#define GPIO_PIN_NO_13 13
#define GPIO_PIN_NO_14 14
#define GPIO_PIN_NO_15 15


/* 
* @GPIO_PIN_MODES
* GPIO possible pin modes
*/
#define GPIO_MODE_IN 0
#define GPIO_MODE_OUT 1
#define GPIO_MODE_ALTFN 2
#define GPIO_MODE_ANALOG 3
#define GPIO_MODE_IT_FT 4 // interrupt mode for falling edge trigger
#define GPIO_MODE_IT_RT 5 // interrupt mode for rising edge trigger
#define GPIO_MODE_IT_RFT 6 // interrupt mode for both rising and falling edge trigger

/* 
* @GPIO_PIN_OP_TYPES
* GPIO possible output types
*/
#define GPIO_OP_TYPE_PP 0 // push-pull output
#define GPIO_OP_TYPE_OD 1 // open-drain output


/* 
* @GPIO_PIN_SPEED
* GPIO possible output speeds
*/
#define GPIO_SPEED_LOW 0
#define GPIO_SPEED_MEDIUM 1
#define GPIO_SPEED_FAST 2
#define GPIO_SPEED_HIGH 3

/* 
* @GPIO_PIN_PUPD
* GPIO possible pull-up/pull-down configurations
*/
#define GPIO_NO_PUPD 0
#define GPIO_PIN_PU 1
#define GPIO_PIN_PD 2

/***************** APIs supported by this driver *****************/

// init and deinit

/** @param[in] pGPIOHandle : pointer to a GPIO_Handle_t structure that contains the configuration settings for the GPIO pin to be initialized */
void GPIO_Init(GPIO_Handle_t *pGPIOHandle);

/** @param[in] pGPIOx : base address of the GPIO peripheral to which the pin belongs */
void GPIO_DeInit(GPIO_RegDef_t *pGPIOx);

// peripheral clock setup

/** @param[in] pGPIOx : base address of the GPIO peripheral to enable or disable the clock for */
/** @param[in] Enable : ENABLE or DISABLE macros to enable or disable the clock for the given GPIO peripheral */
void GPIO_PeriClockControl(GPIO_RegDef_t *pGPIOx, uint8_t Enable);

// data read and write

/** @param[in] pGPIOx : base address of the GPIO peripheral to which the pin belongs */
/** @param[in] PinNumber : pin number (0 to 15) of the GPIO pin to which the value needs to be written */
/** @param[in] Value : value to be written to the GPIO pin (0 or 1) */
void GPIO_WriteToOutputPin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber, uint8_t Value);

/** @param[in] pGPIOx : base address of the GPIO peripheral to which the pin belongs */
/** @param[in] Value : value to be written to the GPIO port (16-bit value) */
void GPIO_WriteToOutputPort(GPIO_RegDef_t *pGPIOx, uint16_t Value);

/** @param[in] pGPIOx : base address of the GPIO peripheral to which the pin belongs */
/** @param[in] PinNumber : pin number (0 to 15) of the GPIO pin to which the value needs to be read */
/** @return : value read from the GPIO pin (0 or 1) */
uint8_t GPIO_ReadFromInputPin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber);

/** @param[in] pGPIOx : base address of the GPIO peripheral to which the pin belongs */
/** @return : value read from the GPIO port (16-bit value) */
uint16_t GPIO_ReadFromInputPort(GPIO_RegDef_t *pGPIOx);

// other peripheral control APIs

/** @param[in] pGPIOx : base address of the GPIO peripheral to which the pin belongs */
/** @param[in] PinNumber : pin number (0 to 15) of the GPIO pin to be toggled */
void GPIO_ToggleOutputPin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber);

/** @param[in] IRQNumber : IRQ number of the GPIO pin for which the interrupt needs to be configured */
/** @param[in] IRQPriority : priority of the IRQ (0 to 15, where 0 is the highest priority) */
/** @param[in] Enable : ENABLE or DISABLE macros to enable or disable the interrupt for the given GPIO pin */
void GPIO_IRQConfig(uint8_t IRQNumber, uint8_t IRQPriority, uint8_t Enable);

/** @param[in] PinNumber : pin number (0 to 15) of the GPIO pin for which the interrupt needs to be handled */
void GPIO_IRQHandling(uint8_t PinNumber);


#endif // INC_STM32F407XX_GPIO_DRIVER_H_