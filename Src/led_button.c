
// #include "stm32f407xx.h"



// int main (void)
// {
//     GPIO_Handle_t GPIOLED, GPIOButton;

//     GPIOLED.pGPIOx = GPIOD;
//     GPIOLED.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_12;
//     GPIOLED.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUT;
//     GPIOLED.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;
//     GPIOLED.GPIO_PinConfig.GPIO_PinOPType = GPIO_OP_TYPE_PP;
//     GPIOLED.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD; // no pull-up or pull-down resistors (the output type is already push-pull, so we don't need pull-up or pull-down resistors)

//     GPIO_PeriClockControl(GPIOD, ENABLE); // enable the clock for GPIOD peripheral
//     GPIO_Init(&GPIOLED); // initialize the GPIO pin with the specified configuration

//     GPIOButton.pGPIOx = GPIOA;
//     GPIOButton.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_0;
//     GPIOButton.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_IN;
//     GPIOButton.GPIO_PinConfig.GPIO_PinSpeed = GPIO_SPEED_FAST;
//     GPIOButton.GPIO_PinConfig.GPIO_PinPuPdControl = GPIO_NO_PUPD; 

//     GPIO_PeriClockControl(GPIOA, ENABLE); 
//     GPIO_Init(&GPIOButton);

//     while (1) {
//         if (GPIO_ReadFromInputPin(GPIOA, GPIO_PIN_NO_0) == GPIO_PIN_SET) { // check if the button connected to pin 0 of GPIOA is pressed (active high configuration)
//              for (int i = 0; i < 500000; i++); // delay loop to create a visible delay between button press and LED toggle
//              GPIO_ToggleOutputPin(GPIOD, GPIO_PIN_NO_12); // toggle the state of the LED connected to pin 12 of GPIOD
//         }
//     }

// }