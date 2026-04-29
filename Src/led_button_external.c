
#include "stm32f407xx.h"


#define LOW 0
#define HIGH 1
#define BTN_PRESSED LOW


int main (void)
{
    GPIO_Handle_t GPIOLED, GPIOButton;

    GPIOLED.pGPIOx = GPIOA;
    GPIOLED.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_8;
    GPIOLED.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUT;
    GPIOLED.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;
    GPIOLED.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;
    GPIOLED.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD; // no pull-up or pull-down resistors (the output type is already push-pull, so we don't need pull-up or pull-down resistors)

    GPIO_PeriClockControl(GPIOA, ENABLE); // enable the clock for GPIOA peripheral
    GPIO_Init(&GPIOLED); // initialize the GPIO pin with the specified configuration

    GPIOButton.pGPIOx = GPIOB;
    GPIOButton.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_12;
    GPIOButton.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_IN;
    GPIOButton.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;
    GPIOButton.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PU; 

    GPIO_PeriClockControl(GPIOB, ENABLE); 
    GPIO_Init(&GPIOButton);

    while (1) {
        if (GPIO_ReadFromInputPin(GPIOB, GPIO_PIN_NO_12) == BTN_PRESSED) { 
             for (int i = 0; i < 500000; i++); // delay loop to create a visible delay between button press and LED toggle
             GPIO_ToggleOutputPin(GPIOA, GPIO_PIN_NO_8); // toggle the state of the LED connected to pin 14 of GPIOA
        }
    }

}