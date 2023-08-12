# Interfacing PS2 wireless gamepad with stm32f401ccu6

SPI1, USART1 are used in current implementation. Which means following connections:
```
USART-USB Bridge TX -> A10 (Black Pill USART1 RX)
USART-USB Bridge RX -> A9 (Black Pill USART1 TX)

PS2 reciever VCC -> 3.3V
PS2 reciever COMMAND -> A7 (SPI MOSI)
PS2 reciever DATA -> A6 (SPI MISO)
PS2 reciever ATTENTION -> A4 (SPI SS)
PS2 reciever CLOCK -> A5 (SPI CLK)
```

