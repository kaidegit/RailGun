//
// Created by yekai on 2021/5/18.
//

#include "LCD.h"
#include "usart.h"
#include "stdio.h"
#include "string.h"
#include "fsmc.h"

uint16_t POINT_COLOR = 0x0000;
uint16_t BACK_COLOR = 0xFFFF;

lcd_dev lcddev;

void LCD_WR_REG(__IO uint16_t regval) {
    LCD->LCD_REG = regval;
}

void LCD_WR_DATA(__IO uint16_t data) {
    LCD->LCD_RAM = data;
}

uint16_t LCD_RD_DATA(void) {
    __IO uint16_t ram;
    ram = LCD->LCD_RAM;
    return ram;
}

void LCD_WriteReg(uint16_t LCD_Reg, uint16_t LCD_RegValue) {
    LCD->LCD_REG = LCD_Reg;
    LCD->LCD_RAM = LCD_RegValue;
}

uint16_t LCD_ReadReg(uint16_t LCD_Reg) {
    LCD_WR_REG(LCD_Reg);
    return LCD_RD_DATA();
}

void LCD_WriteRAM_Prepare(void) {
    LCD->LCD_REG = lcddev.wramcmd;
}

void LCD_WriteRAM(uint16_t RGB_Code) {
    LCD->LCD_RAM = RGB_Code;
}

uint16_t LCD_BGR2RGB(uint16_t c) {
    uint16_t r, g, b, rgb;
    b = (c >> 0) & 0x1f;
    g = (c >> 5) & 0x3f;
    r = (c >> 11) & 0x1f;
    rgb = (b << 11) + (g << 5) + (r << 0);
    return (rgb);
}

void LCD_Display_Dir(uint8_t dir) {
    if (dir == 0) {
        lcddev.dir = 0;
        lcddev.height = 320;
        lcddev.width = 240;
        if (lcddev.id == 0X9341) {
            lcddev.wramcmd = 0X2C;
            lcddev.setxcmd = 0X2A;
            lcddev.setycmd = 0X2B;
            if (lcddev.id == 0X6804 || lcddev.id == 0X5310) {
                lcddev.width = 320;
                lcddev.height = 480;
            }
        }
    } else {
        lcddev.dir = 1;
        lcddev.width = 320;
        lcddev.height = 240;
        if (lcddev.id == 0X9341) {
            lcddev.wramcmd = 0X2C;
            lcddev.setxcmd = 0X2A;
            lcddev.setycmd = 0X2B;
        }
    }
    LCD_Scan_Dir(DFT_SCAN_DIR);
}

void LCD_Scan_Dir(enum SCAN_DIR dir) {
    uint16_t regval = 0;
    uint16_t dirreg = 0;
    uint16_t temp;
    if ((lcddev.dir == 1 && lcddev.id != 0X6804 && lcddev.id != 0X1963) ||
        (lcddev.dir == 0 && lcddev.id == 0X1963))//ºáÆÁÊ±£¬¶Ô6804ºÍ1963²»¸Ä±äÉ¨Ãè·½Ïò£¡ÊúÆÁÊ±1963¸Ä±ä·½Ïò
    {
        switch (dir) {
            case 0:
                dir = 6;
                break;
            case 1:
                dir = 7;
                break;
            case 2:
                dir = 4;
                break;
            case 3:
                dir = 5;
                break;
            case 4:
                dir = 1;
                break;
            case 5:
                dir = 0;
                break;
            case 6:
                dir = 3;
                break;
            case 7:
                dir = 2;
                break;
            default:
                break;
        }
    }
    if (lcddev.id == 0x9341) {
        switch (dir) {
            case L2R_U2D:
                regval |= (0 << 7) | (0 << 6) | (0 << 5);
                break;
            case L2R_D2U:
                regval |= (1 << 7) | (0 << 6) | (0 << 5);
                break;
            case R2L_U2D:
                regval |= (0 << 7) | (1 << 6) | (0 << 5);
                break;
            case R2L_D2U:
                regval |= (1 << 7) | (1 << 6) | (0 << 5);
                break;
            case U2D_L2R:
                regval |= (0 << 7) | (0 << 6) | (1 << 5);
                break;
            case U2D_R2L:
                regval |= (0 << 7) | (1 << 6) | (1 << 5);
                break;
            case D2U_L2R:
                regval |= (1 << 7) | (0 << 6) | (1 << 5);
                break;
            case D2U_R2L:
                regval |= (1 << 7) | (1 << 6) | (1 << 5);
                break;
            default:
                break;
        }
        dirreg = 0X36;
        regval |= 0X08;
        LCD_WriteReg(dirreg, regval);

        if (regval & 0X20) {
            if (lcddev.width < lcddev.height)//½»»»X,Y
            {
                temp = lcddev.width;
                lcddev.width = lcddev.height;
                lcddev.height = temp;
            }
        } else {
            if (lcddev.width > lcddev.height)//½»»»X,Y
            {
                temp = lcddev.width;
                lcddev.width = lcddev.height;
                lcddev.height = temp;
            }
        }

        LCD_WR_REG(lcddev.setxcmd);
        LCD_WR_DATA(0);
        LCD_WR_DATA(0);
        LCD_WR_DATA((lcddev.width - 1) >> 8);
        LCD_WR_DATA((lcddev.width - 1) & 0XFF);
        LCD_WR_REG(lcddev.setycmd);
        LCD_WR_DATA(0);
        LCD_WR_DATA(0);
        LCD_WR_DATA((lcddev.height - 1) >> 8);
        LCD_WR_DATA((lcddev.height - 1) & 0XFF);

        dirreg = 0X03;
        regval |= 1 << 12;
        LCD_WriteReg(dirreg, regval);
    }
}

void LCD_SetCursor(uint16_t Xpos, uint16_t Ypos) {
    if (lcddev.id == 0X9341) {
        LCD_WR_REG(lcddev.setxcmd);
        LCD_WR_DATA(Xpos >> 8);
        LCD_WR_DATA(Xpos & 0XFF);
        LCD_WR_REG(lcddev.setycmd);
        LCD_WR_DATA(Ypos >> 8);
        LCD_WR_DATA(Ypos & 0XFF);
    }
}

void LCD_Clear(enum COLOR color) {
    uint32_t index = 0;
    uint32_t totalpoint = lcddev.width;
    totalpoint *= lcddev.height;
    LCD_SetCursor(0x00, 0x0000);
    LCD_WriteRAM_Prepare();
    for (index = 0; index < totalpoint; index++) {
        LCD->LCD_RAM = color;
    }
}

void LCD_DrawPic(uint16_t start_x, uint16_t end_x,
                 uint16_t start_y, uint16_t end_y,
                 const unsigned char *color) {
    uint16_t height, width;
    uint16_t i, j;
    width = end_x - start_x + 1;            //得到填充的宽度
    height = end_y - start_y + 1;            //高度
    for (i = 0; i < height; i++) {
        LCD_SetCursor(start_x, start_y + i);    //设置光标位置
        LCD_WriteRAM_Prepare();     //开始写入GRAM
        for (j = 0; j < width; j++)
            LCD->LCD_RAM = color[(i * width + j) * 2] * 0x100 + color[(i * width + j) * 2 + 1];//写入数据
    }
}

void LCD_Fast_DrawPoint(uint16_t x, uint16_t y, uint16_t color) {
    if (lcddev.id == 0X9341) {
        LCD_WR_REG(lcddev.setxcmd);
        LCD_WR_DATA(x >> 8);
        LCD_WR_DATA(x & 0XFF);
        LCD_WR_REG(lcddev.setycmd);
        LCD_WR_DATA(y >> 8);
        LCD_WR_DATA(y & 0XFF);
    }
    LCD->LCD_REG = lcddev.wramcmd;
    LCD->LCD_RAM = color;
}

void LCD_DrawPoint(uint16_t x, uint16_t y) {
    LCD_SetCursor(x, y);        //设置光标位置
    LCD_WriteRAM_Prepare();    //开始写入GRAM
    LCD->LCD_RAM = POINT_COLOR;
}

void LCD_Draw_Circle(uint16_t x0, uint16_t y0, uint8_t r) {
    int a, b;
    int di;
    a = 0;
    b = r;
    di = 3 - (r << 1);             //判断下个点位置的标志
    while (a <= b) {
        LCD_DrawPoint(x0 + a, y0 - b);             //5
        LCD_DrawPoint(x0 + b, y0 - a);             //0
        LCD_DrawPoint(x0 + b, y0 + a);             //4
        LCD_DrawPoint(x0 + a, y0 + b);             //6
        LCD_DrawPoint(x0 - a, y0 + b);             //1
        LCD_DrawPoint(x0 - b, y0 + a);
        LCD_DrawPoint(x0 - a, y0 - b);             //2
        LCD_DrawPoint(x0 - b, y0 - a);             //7
        a++;
        //使用Bresenham算法画圆
        if (di < 0)di += 4 * a + 6;
        else {
            di += 10 + 4 * (a - b);
            b--;
        }
    }
}

void LCD_Init() {
    HAL_Delay(50);
    LCD_WriteReg(0x0000, 0x0001);
    HAL_Delay(50);

    lcddev.id = LCD_ReadReg(0x0000);
    LCD_WR_REG(0XD3);
    lcddev.id = LCD_RD_DATA();
    lcddev.id = LCD_RD_DATA();
    lcddev.id = LCD_RD_DATA();
    lcddev.id <<= 8;
    lcddev.id |= LCD_RD_DATA();

    if (lcddev.id == 0x9341) {
        MX_FSMC_Init_Fast();
        LCD_WR_REG(0xCF);
        LCD_WR_DATA(0x00);
        LCD_WR_DATA(0xC1);
        LCD_WR_DATA(0X30);
        LCD_WR_REG(0xED);
        LCD_WR_DATA(0x64);
        LCD_WR_DATA(0x03);
        LCD_WR_DATA(0X12);
        LCD_WR_DATA(0X81);
        LCD_WR_REG(0xE8);
        LCD_WR_DATA(0x85);
        LCD_WR_DATA(0x10);
        LCD_WR_DATA(0x7A);
        LCD_WR_REG(0xCB);
        LCD_WR_DATA(0x39);
        LCD_WR_DATA(0x2C);
        LCD_WR_DATA(0x00);
        LCD_WR_DATA(0x34);
        LCD_WR_DATA(0x02);
        LCD_WR_REG(0xF7);
        LCD_WR_DATA(0x20);
        LCD_WR_REG(0xEA);
        LCD_WR_DATA(0x00);
        LCD_WR_DATA(0x00);
        LCD_WR_REG(0xC0);    //Power control
        LCD_WR_DATA(0x1B);   //VRH[5:0]
        LCD_WR_REG(0xC1);    //Power control
        LCD_WR_DATA(0x01);   //SAP[2:0];BT[3:0]
        LCD_WR_REG(0xC5);    //VCM control
        LCD_WR_DATA(0x30);     //3F
        LCD_WR_DATA(0x30);     //3C
        LCD_WR_REG(0xC7);    //VCM control2
        LCD_WR_DATA(0XB7);
        LCD_WR_REG(0x36);    // Memory Access Control
        LCD_WR_DATA(0x48);
        LCD_WR_REG(0x3A);
        LCD_WR_DATA(0x55);
        LCD_WR_REG(0xB1);
        LCD_WR_DATA(0x00);
        LCD_WR_DATA(0x1A);
        LCD_WR_REG(0xB6);    // Display Function Control
        LCD_WR_DATA(0x0A);
        LCD_WR_DATA(0xA2);
        LCD_WR_REG(0xF2);    // 3Gamma Function Disable
        LCD_WR_DATA(0x00);
        LCD_WR_REG(0x26);    //Gamma curve selected
        LCD_WR_DATA(0x01);
        LCD_WR_REG(0xE0);    //Set Gamma
        LCD_WR_DATA(0x0F);
        LCD_WR_DATA(0x2A);
        LCD_WR_DATA(0x28);
        LCD_WR_DATA(0x08);
        LCD_WR_DATA(0x0E);
        LCD_WR_DATA(0x08);
        LCD_WR_DATA(0x54);
        LCD_WR_DATA(0XA9);
        LCD_WR_DATA(0x43);
        LCD_WR_DATA(0x0A);
        LCD_WR_DATA(0x0F);
        LCD_WR_DATA(0x00);
        LCD_WR_DATA(0x00);
        LCD_WR_DATA(0x00);
        LCD_WR_DATA(0x00);
        LCD_WR_REG(0XE1);    //Set Gamma
        LCD_WR_DATA(0x00);
        LCD_WR_DATA(0x15);
        LCD_WR_DATA(0x17);
        LCD_WR_DATA(0x07);
        LCD_WR_DATA(0x11);
        LCD_WR_DATA(0x06);
        LCD_WR_DATA(0x2B);
        LCD_WR_DATA(0x56);
        LCD_WR_DATA(0x3C);
        LCD_WR_DATA(0x05);
        LCD_WR_DATA(0x10);
        LCD_WR_DATA(0x0F);
        LCD_WR_DATA(0x3F);
        LCD_WR_DATA(0x3F);
        LCD_WR_DATA(0x0F);
        LCD_WR_REG(0x2B);
        LCD_WR_DATA(0x00);
        LCD_WR_DATA(0x00);
        LCD_WR_DATA(0x01);
        LCD_WR_DATA(0x3f);
        LCD_WR_REG(0x2A);
        LCD_WR_DATA(0x00);
        LCD_WR_DATA(0x00);
        LCD_WR_DATA(0x00);
        LCD_WR_DATA(0xef);
        LCD_WR_REG(0x11); //Exit Sleep
        HAL_Delay(120);
        LCD_WR_REG(0x29); //display on
    }
    LCD_Display_Dir(0);
    HAL_GPIO_WritePin(LCD_BL_GPIO_Port, LCD_BL_Pin, GPIO_PIN_SET);
    LCD_Clear(WHITE);
}
