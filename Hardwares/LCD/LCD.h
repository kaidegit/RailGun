//
// Created by yekai on 2021/5/18.
//

#ifndef __LCD_H
#define __LCD_H

#ifdef __cplusplus
extern "C" {
#endif

#include "stm32f4xx_hal.h"

typedef struct {
    uint16_t width;
    uint16_t height;
    uint16_t id;
    uint8_t dir;         // 0 横屏 1 竖屏
    uint16_t wramcmd;    // 开始写gram指令
    uint16_t setxcmd;    // 设置x坐标指令
    uint16_t setycmd;    // 设置y坐标指令
} lcd_dev;

typedef struct {
    uint16_t LCD_REG;
    uint16_t LCD_RAM;
} LCD_TypeDef;

enum SCAN_DIR {
    L2R_U2D = 0, L2R_D2U, R2L_U2D, R2L_D2U, U2D_L2R, U2D_R2L, D2U_L2R, D2U_R2L
};
enum COLOR {
    BLACK = 0x0000,
    BLUE = 0x001F,
    DARKBLUE = 0X01CF,
    GREEN = 0x07E0,
    GBLUE = 0X07FF,
    GRAYBLUE = 0X5458,
    GRAY = 0X8430,
    LIGHTBLUE = 0X7D7C,
    CYAN = 0x7FFF,
    BROWN = 0XBC40,
    RED = 0xF800,
    BRED = 0xF81F,
    BRRED = 0XFC07,
    YELLOW = 0xFFE0,
    WHITE = 0xFFFF
};


#define LCD_BASE        ((uint32_t)(0x6C000000 | 0x0000007E))
#define LCD             ((LCD_TypeDef *) LCD_BASE)
#define DFT_SCAN_DIR  L2R_U2D

void LCD_WR_REG(__IO uint16_t regval);

void LCD_WR_DATA(__IO uint16_t data);

uint16_t LCD_RD_DATA(void);

void LCD_WriteReg(uint16_t LCD_Reg, uint16_t LCD_RegValue);

uint16_t LCD_ReadReg(uint16_t LCD_Reg);

void LCD_WriteRAM_Prepare(void);

void LCD_WriteRAM(uint16_t RGB_Code);

uint16_t LCD_BGR2RGB(uint16_t c);

void LCD_Display_Dir(uint8_t dir);

void LCD_Scan_Dir(enum SCAN_DIR dir);

void LCD_SetCursor(uint16_t Xpos, uint16_t Ypos);

void LCD_Clear(enum COLOR color);

void LCD_DrawPic(uint16_t start_x, uint16_t end_x,
                 uint16_t start_y, uint16_t end_y,
                 const unsigned char *color);

void LCD_Fast_DrawPoint(uint16_t x, uint16_t y, uint16_t color);

void LCD_Draw_Circle(uint16_t x0, uint16_t y0, uint8_t r);

void LCD_DrawPoint(uint16_t x, uint16_t y);

void LCD_Init();


#ifdef __cplusplus
}
#endif

#endif //RAILGUN_LCD_H
