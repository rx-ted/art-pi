#include <tft_test.h>
#include <sys.h>
#include <unity.h>

void TFT_MATCH_DRIVER_NAME_ID_PINOUT()
{
    char *name = (char *)"ili9341";
    tft_8_parallel_t p8 = {
        D0, D1, D2, D3, D4, D5, D6, D7};

    tft_mcu_t mcu = {
        name, 240, 320, A0, A1, A2, A3, A4, p8};

    TFT tft = TFT(mcu);
    tft.begin();
    TEST_ASSERT_EQUAL_HEX(tft.findDriverId(), 0x01);
    TEST_ASSERT_EQUAL_UINT16(mcu.width, 240);
    TEST_ASSERT_EQUAL_UINT16(mcu.height, 320);
    TEST_ASSERT_EQUAL_HEX(mcu.cs, A3);
    TEST_ASSERT_EQUAL_HEX(mcu.p8.p0, D0);
    tft.setRotation(0);
    TEST_ASSERT_EQUAL(240, tft.getWidth());
    tft.setRotation(1);
    TEST_ASSERT_EQUAL(320, tft.getWidth());
    tft.RST_ACTIVE();
    TEST_ASSERT_EQUAL(LOW, digitalRead(A4));
    tft.RST_IDLE();
    TEST_ASSERT_EQUAL(HIGH, digitalRead(A4));
}

void test_tft()
{
    UnityBegin("tft_test");
    TFT_MATCH_DRIVER_NAME_ID_PINOUT();
    UnityEnd();
}