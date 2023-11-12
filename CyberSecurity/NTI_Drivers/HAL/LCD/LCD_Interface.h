

#ifndef LCD_INTERFACE_H_
#define LCD_INTERFACE_H_

void LCD_Init();
void LCD_CLR();
void LCD_GoTo(u8 line, u8 cell);

void LCD_WriteChar(u8 ch);
void LCD_WriteString(u8* str);

void LCD_WriteNumber(u32 num);
void LCD_WriteBinary(u8 num);
void LCD_WriteHex(s32 num);
void LCD_WriteHexU32(u32 num);
void LCD_Clear_Position(u8 line, u8 cell, u8 noCells);
void LCD_CustomChar(u8 address,u8* customchar);

#endif /* LCD_INTERFACE_H_ */