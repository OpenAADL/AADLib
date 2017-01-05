#ifndef STM32_HARDWARE_H_
#define STM32_HARDWARE_H_

void SystemClock_Config(void);
void MX_GPIO_Init(void);
void MX_I2C1_Init(void);
void MX_SPI1_Init(void);
void MX_USART2_UART_Init(void);

void init_hardware(void);

#endif /* STM32_HARDWARE_H_ */
