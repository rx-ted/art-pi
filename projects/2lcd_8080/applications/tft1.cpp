#include <tft1.h>
#include <pins.h>
#include <sys.h>

uint8_t cmd_B0[] = {0xB0, 1, 0x00};
uint8_t cmd_B3[] = {0xB3, 4, 0x02, 0x00, 0x00, 0x00};
uint8_t cmd_C0[] = {0xC0, 8, 0x13, 0x3B, 0x00, 0x02, 0x00, 0x01, 0x00, 0x43};
uint8_t cmd_C1[] = {0xC1, 4, 0x08, 0x16, 0x08, 0x08};
uint8_t cmd_C4[] = {0xC4, 4, 0x11, 0x07, 0x03, 0x03};
uint8_t cmd_C6[] = {0xC6, 1, 0x00};
uint8_t cmd_C8[] = {0xC8, 20, 0x03, 0x03, 0x13, 0x5C, 0x03, 0x07, 0x14, 0x08, 0x00, 0x21, 0x08, 0x14, 0x07, 0x53, 0x0C, 0x13, 0x03, 0x03, 0x21, 0x00};
uint8_t cmd_0C[] = {0x0C, 1, 0x55};
uint8_t cmd_38[] = {0x38, 0};
uint8_t cmd_3A[] = {0x3A, 1, 0x55};
uint8_t cmd_D0[] = {0xD0, 4, 0x07, 0x07, 0x1D, 0x03};
uint8_t cmd_D1[] = {0xD1, 3, 0x03, 0x30, 0x10};
uint8_t cmd_D2[] = {0xD2, 3, 0x03, 0x14, 0x04};
uint8_t cmd_11[] = {0x11, 0};
uint8_t cmd_2A[] = {0x2A, 4, 0x00, 0x00, ((SCREEN_XSIZE - 1) >> 8) & 0XFF, (SCREEN_XSIZE - 1) & 0XFF};
uint8_t cmd_2B[] = {0x2B, 4, 0x00, 0x00, ((SCREEN_YSIZE - 1) >> 8) & 0XFF, (SCREEN_YSIZE - 1) & 0XFF};
uint8_t cmd_29[] = {0x29, 0};
uint8_t cmd_2C[] = {0x2C, 0};


TFT1::TFT1(/* args */)
{
    delay(1000);
    _rd = A0;
    _wr = A1;
    _dc = A2;
    _cs = A3;
    _rst = A4;
    _p8[0] = D0;
    _p8[1] = D1;
    _p8[2] = D2;
    _p8[3] = D3;
    _p8[4] = D4;
    _p8[5] = D5;
    _p8[6] = D6;
    _p8[7] = D7;
    CONTROL_8080(OUTPUT);
    SET_8P_MODE(OUTPUT);
    CONTROL_8080_INITIALIZE;
    DATA_P8_WRITE(0XFF);

    writeReg(cmd_B0);
    writeReg(cmd_B3);
    // writeReg(cmd_B4);
    writeReg(cmd_C0);
    writeReg(cmd_C1);
    writeReg(cmd_C4);
    writeReg(cmd_C6);
    writeReg(cmd_C8); // Gamma
    // writeReg(cmd_36);
    writeReg(cmd_0C);
    writeReg(cmd_3A);
    writeReg(cmd_38);
    writeReg(cmd_D0);
    writeReg(cmd_D1);
    writeReg(cmd_D2);
    // writeReg(0x21, NULL, 0); // Invert mode
    writeReg(cmd_11);
    delay(150);
    writeReg(cmd_2A);
    writeReg(cmd_2B);
    delay(10);
    writeReg(cmd_29);
    delay(100);
    writeReg(cmd_2C);
    delay(5);
}

void TFT1::write(uint8_t d)
{
    SET_8P_MODE(OUTPUT);
    DATA_P8_WRITE(d);
    WR_STROBE;
}
void TFT1::writeCommand(uint8_t c)
{
    CS_ACTIVE;
    DC_CMD;
    write(c);
    DC_DAT;
    CS_IDLE;
}
void TFT1::writeData(uint8_t d)
{
    CS_ACTIVE;
    DC_DAT;
    write(d);
    CS_IDLE;
}
void TFT1::writeReg(uint8_t *reg)
{
    writeCommand(reg[0]);
    // rt_kprintf("%2x-> ", reg[0]);
    uint8_t i = 2, size = reg[1];
    while (i < size + 2)
    {
        writeData(reg[i]);
        // rt_kprintf("%d:%02x ", i-2, reg[i]);
        i++;
    }
    // rt_kprintf("\t reg size is %d\n", i - 2);
    // rt_kprintf("\n");
}

uint8_t TFT1::read8()
{
    SET_8P_MODE(INPUT);
    CS_ACTIVE;
    RD_ACTIVE;
    // TODO(Ben)

    uint8_t result =
        (digitalRead(_p8[0]) & 0x01) << 0 |
        (digitalRead(_p8[1]) & 0x01) << 1 |
        (digitalRead(_p8[2]) & 0x01) << 2 |
        (digitalRead(_p8[3]) & 0x01) << 3 |
        (digitalRead(_p8[4]) & 0x01) << 4 |
        (digitalRead(_p8[5]) & 0x01) << 5 |
        (digitalRead(_p8[6]) & 0x01) << 6 |
        (digitalRead(_p8[7]) & 0x01) << 7;
    RD_IDLE;
    CS_IDLE;
    return result;
}

uint8_t TFT1::getCurrentPinStatus()
{
    return read8();
}
uint16_t TFT1::getDriverId()
{
    writeCommand(0X0A);
    return read8() << 8 | read8();
}

uint8_t TFT1::getRstPinStatus(uint8_t d)
{
    writeData(d);
    return read8();
}

void TFT1::fillScreen(uint16_t c)
{
    writeCommand(0X2C);
    for (size_t i = 0; i < SCREEN_XSIZE * SCREEN_YSIZE; i++)
    {
        writeData(c >> 8);
        writeData(c);
    }
}

TFT1::~TFT1()
{
}
