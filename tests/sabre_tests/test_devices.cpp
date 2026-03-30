#include "sabre_test_mocks/devices.hpp"
#include "sabre_test_mocks/hal.hpp"
#include <gtest/gtest.h>
#include <sabre/core/exceptions.hpp>
#include <sabre/devices/serial_nmea_gps_device.hpp>

using sabre::impl::sabre_test_mocks::StRgbPixelStrip;

TEST(SerialNmeaGpsDeviceTest, DefaultConstructor)
{
    sabre::devices::SerialNmeaGpsDevice device;
    EXPECT_FALSE(device.isValidPosition());
    EXPECT_FALSE(device.readData());
}

TEST(SerialNmeaGpsDeviceTest, ReceiveDataFromUART)
{
    // Set up UART
    sabre::hal::Serial::UniquePtr uart =
        std::make_unique<sabre::impl::sabre_test_mocks::TestUART>();
    for (char c : "$GNRMC,120000.000,A,3409.3251,N,11849.1290,W,0.00,0.00,"
                  "061125,,,A*64\r\n")
        uart->writeByte(c);

    // Read the data
    sabre::devices::SerialNmeaGpsDevice device(uart.get());
    while (device.readData())
        ;

    ASSERT_TRUE(device.isValidPosition());
    ASSERT_NEAR(device.getLastPosition().getLatitude().getDD(), 34.1554183,
                1e-7);
    ASSERT_NEAR(device.getLastPosition().getLongitude().getDD(), -118.8188167,
                1e-7);
}

TEST(SerialNmeaGpsDeviceTest, ReceiveDataFromUART_MultipleScentences)
{
    // Set up UART
    sabre::hal::Serial::UniquePtr uart =
        std::make_unique<sabre::impl::sabre_test_mocks::TestUART>();
    for (char c :
         "$GNRMC,120000.000,A,3409.3251,N,11849.1290,W,0.00,0.00,"
         "061125,,,A\r\n$GNRMC,120000.000,A,3509.3251,N,11949.1290,W,0.00,0.00,"
         "061125,,,A*64\r\n")
        uart->writeByte(c);

    // Read the data
    sabre::devices::SerialNmeaGpsDevice device(uart.get());
    while (device.readData())
        ;

    ASSERT_TRUE(device.isValidPosition());
    ASSERT_NEAR(device.getLastPosition().getLatitude().getDD(), 35.1554183,
                1e-7);
    ASSERT_NEAR(device.getLastPosition().getLongitude().getDD(), -119.8188167,
                1e-7);
}

TEST(SerialNmeaGpsDeviceTest, ReceiveDataFromUART_MidSentence)
{
    // Set up UART
    sabre::hal::Serial::UniquePtr uart =
        std::make_unique<sabre::impl::sabre_test_mocks::TestUART>();
    for (char c :
         ".9999,N,11249.1290,W,0.00,0.00,"
         "061125,,,A\r\n$GNRMC,120000.000,A,3409.3251,N,11849.1290,W,0.00,0.00,"
         "061125,,,A*64\r\n")
        uart->writeByte(c);

    // Read the data
    sabre::devices::SerialNmeaGpsDevice device(uart.get());
    while (device.readData())
        ;

    ASSERT_TRUE(device.isValidPosition());
    ASSERT_NEAR(device.getLastPosition().getLatitude().getDD(), 34.1554183,
                1e-7);
    ASSERT_NEAR(device.getLastPosition().getLongitude().getDD(), -118.8188167,
                1e-7);
}

TEST(SerialNmeaGpsDeviceTest, ReceiveDataFromUART_MidSentenceStop)
{
    // Set up UART
    sabre::hal::Serial::UniquePtr uart =
        std::make_unique<sabre::impl::sabre_test_mocks::TestUART>();
    for (char c :
         ".9999,N,11249.1290,W,0.00,0.00,"
         "061125,,,A\r\n$GNRMC,120000.000,A,3409.3251,N,11849.1290,W,0.00,0.00,"
         "061125,,,A*64\r\n$GNRMC,120000.000,A,3509.3251,N,11949.1290,W,")
        uart->writeByte(c);

    // Read the data
    sabre::devices::SerialNmeaGpsDevice device(uart.get());
    while (device.readData())
        ;
    ASSERT_TRUE(device.isValidPosition());
    ASSERT_NEAR(device.getLastPosition().getLatitude().getDD(), 34.1554183,
                1e-7);
    ASSERT_NEAR(device.getLastPosition().getLongitude().getDD(), -118.8188167,
                1e-7);
}

TEST(SerialNmeaGpsDeviceTest, ReceiveDataFromUART_InvalidData)
{
    // Set up UART
    sabre::hal::Serial::UniquePtr uart =
        std::make_unique<sabre::impl::sabre_test_mocks::TestUART>();
    for (char c : "$GNRMC,112939.000,V,,,,,,,031125,,,N,V*2C\r\n")
        uart->writeByte(c);

    // Read the data
    sabre::devices::SerialNmeaGpsDevice device(uart.get());
    while (device.readData())
        ;
    ASSERT_FALSE(device.isValidPosition());
}

TEST(SerialNmeaGpsDeviceTest, ReceiveDataFromUART_UARTError)
{
    // Set up UART
    sabre::hal::Serial::UniquePtr uart =
        std::make_unique<sabre::impl::sabre_test_mocks::TestUART>();
    for (char c : "$GNRMC,120000.000,A,3609.3251,N,11949.1290,W,0.00,0.00,"
                  "061125,,,A\r\n$GNRMC,120000.000,A,3409.$GNRMC,120000.000,A,"
                  "3409.3251,N,11849.1290,W,0.00,0.00,"
                  "061125,,,A*64\r\n")
        uart->writeByte(c);

    // Read the data
    sabre::devices::SerialNmeaGpsDevice device(uart.get());
    while (device.readData())
        ;
    ASSERT_TRUE(device.isValidPosition());
    ASSERT_NEAR(device.getLastPosition().getLatitude().getDD(), 34.1554183,
                1e-7);
    ASSERT_NEAR(device.getLastPosition().getLongitude().getDD(), -118.8188167,
                1e-7);
}

TEST(SerialNmeaGpsDeviceTest, SwitchUARTPtr)
{
    // Set up UART-1
    sabre::hal::Serial::UniquePtr uart =
        std::make_unique<sabre::impl::sabre_test_mocks::TestUART>();
    for (char c : "$GNRMC,120000.000,A,3409.3251,N,11849.1290,W,0.00,0.00,"
                  "061125,,,A*64\r\n")
        uart->writeByte(c);

    // Read the data from UART-1
    sabre::devices::SerialNmeaGpsDevice device(uart.get());
    while (device.readData())
        ;

    ASSERT_TRUE(device.isValidPosition());
    ASSERT_NEAR(device.getLastPosition().getLatitude().getDD(), 34.1554183,
                1e-7);
    ASSERT_NEAR(device.getLastPosition().getLongitude().getDD(), -118.8188167,
                1e-7);

    // Set up UART-2
    sabre::hal::Serial::UniquePtr uart2 =
        std::make_unique<sabre::impl::sabre_test_mocks::TestUART>();
    for (char c : "$GNRMC,120000.000,A,3609.3251,N,12049.1290,W,0.00,0.00,"
                  "061125,,,A*6D\r\n")
        uart2->writeByte(c);

    // Switch to UART-2 and read data
    device.setUartPtr(uart2.get());
    while (device.readData())
        ;

    ASSERT_TRUE(device.isValidPosition());
    ASSERT_NEAR(device.getLastPosition().getLatitude().getDD(), 36.1554183,
                1e-7);
    ASSERT_NEAR(device.getLastPosition().getLongitude().getDD(), -120.8188167,
                1e-7);
}

TEST(SerialNmeaGpsDeviceTest, WriteToUart)
{
    std::string gnrmc =
        "$GNRMC,120000.000,A,3409.3251,N,11849.1290,W,0.00,0.00,"
        "061125,,,A*64\r\n";
    sabre::hal::Serial::UniquePtr uart =
        std::make_unique<sabre::impl::sabre_test_mocks::TestUART>();
    for (char c : gnrmc)
        uart->writeByte(c);

    sabre::hal::Serial::UniquePtr out_uart =
        std::make_unique<sabre::impl::sabre_test_mocks::TestUART>();
    sabre::devices::SerialNmeaGpsDevice device(uart.get());
    device.setOutputUartPtr(out_uart.get());
    while (device.readData())
        ;
    ASSERT_EQ(out_uart->readBytes(gnrmc.length(), 100), gnrmc);
}

TEST(RgbPixelStrip, Construction)
{
    StRgbPixelStrip rgb(10, 100);
    ASSERT_EQ(rgb.getLength(), 100);
}

TEST(RgbPixelStrip, ConstructionNullSize)
{
    using sabre::core::RgbSizeTooSmallException;
    ASSERT_THROW({ StRgbPixelStrip rgb(10, 0); }, RgbSizeTooSmallException);
}

TEST(RgbPixelStrip, SetPixel)
{
    StRgbPixelStrip rgb(10, 100);
    sabre::types::Color red(255, 0, 0);

    ASSERT_EQ(rgb.getPixel(10), sabre::types::Color(0, 0, 0));
    rgb.setPixel(10, red);
    ASSERT_EQ(rgb.getPixel(10), sabre::types::Color(255, 0, 0));
}

TEST(RgbPixelStrip, SetPixelTooHigh)
{
    using sabre::core::RgbIndexTooHighException;

    StRgbPixelStrip rgb(10, 100);
    sabre::types::Color red(255, 0, 0);

    ASSERT_THROW({ rgb.setPixel(101, red); }, RgbIndexTooHighException);
}

TEST(RgbPixelStrip, ClearPixel)
{
    StRgbPixelStrip rgb(10, 100);
    sabre::types::Color red(255, 0, 0);
    rgb.setPixel(10, red);
    rgb.clearPixel(10);

    ASSERT_EQ(rgb.getPixel(10), sabre::types::Color(0, 0, 0));
}

TEST(RgbPixelStrip, ClearPixelTooHigh)
{
    using sabre::core::RgbIndexTooHighException;

    StRgbPixelStrip rgb(10, 100);
    ASSERT_THROW({ rgb.clearPixel(101); }, RgbIndexTooHighException);
}

TEST(RgbPixelStrip, SetAll)
{
    StRgbPixelStrip rgb(10, 100);
    sabre::types::Color red(255, 0, 0);
    rgb.setAll(red);

    for (sabre::devices::PixelIndex idx = 0; idx < 100; idx++)
    {
        ASSERT_EQ(rgb.getPixel(idx), sabre::types::Color(255, 0, 0));
    }
}

TEST(RgbPixelStrip, ClearAll)
{
    StRgbPixelStrip rgb(10, 100);
    sabre::types::Color red(255, 0, 0);
    rgb.setAll(red);
    rgb.clear();

    for (sabre::devices::PixelIndex idx = 0; idx < 100; idx++)
    {
        ASSERT_EQ(rgb.getPixel(idx), sabre::types::Color(0, 0, 0));
    }
}