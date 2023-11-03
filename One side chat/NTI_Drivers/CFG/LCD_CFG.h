// Choose between 4-bit and 8-bit configurations using a preprocessor directive
#define USE_4_BIT  1// Comment this line to use 8-bit configuration

#if defined(USE_4_BIT)
// 4-bit configuration
#define LCD_RS      PINA3
#define LCD_EN      PINA2	//Default PA2, for ADC project PA4
#define LCD_D4      PINB0	//Default PB0, for Seb7a project PB3
#define LCD_D5      PINB1
#define LCD_D6      PINB2	//Default PB2, for ADC project PB3
#define LCD_D7      PINB4	//Default PB4, PB3 for 2MCUs + LM35 (SPI)
//#define LCD_PORT    PA
/*
#else
// 8-bit configuration
#define LCD_RS      PINB0
#define LCD_EN      PINB1
#define LCD_D0      PINA0
#define LCD_D1      PINA1
#define LCD_D2      PINA2
#define LCD_D3      PINA3
#define LCD_D4      PINA4
#define LCD_D5      PINA5
#define LCD_D6      PINA6
#define LCD_D7      PINA7
#define LCD_PORT    PA
*/
#endif
