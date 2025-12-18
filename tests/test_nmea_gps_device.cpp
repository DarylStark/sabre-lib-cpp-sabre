#include "sabre_testing/hal.hpp"
#include <gtest/gtest.h>
#include <sabre/devices/serial_nmea_gps_device.hpp>

TEST(SerialNmeaGpsDeviceTest, DefaultConstructor)
{
    sabre::devices::SerialNmeaGpsDevice device;
    EXPECT_FALSE(device.isValidPosition());
    EXPECT_FALSE(device.readData());
}

TEST(SerialNmeaGpsDeviceTest, ReceiveDataFromUART)
{
    // Set up UART
    sabre::hal::Uart::UniquePtr uart =
        std::make_unique<sabre::impl::sabre_testing::TestUART>();
    for (char c : "$GNRMC,120000.000,A,3409.3251,N,11849.1290,W,0.00,0.00,"
                  "061125,,,A*64\r\n")
        uart->writeByte(c);

    // Read the data
    sabre::devices::SerialNmeaGpsDevice device(uart.get());
    while (device.readData())
        ;

    ASSERT_TRUE(device.isValidPosition());
    ASSERT_NEAR(device.getLastPosition().get_latitude().get_dd(), 34.1554183,
                1e-7);
    ASSERT_NEAR(device.getLastPosition().get_longitude().get_dd(), -118.8188167,
                1e-7);
}

TEST(SerialNmeaGpsDeviceTest, ReceiveDataFromUART_MultipleScentences)
{
    // Set up UART
    sabre::hal::Uart::UniquePtr uart =
        std::make_unique<sabre::impl::sabre_testing::TestUART>();
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
    ASSERT_NEAR(device.getLastPosition().get_latitude().get_dd(), 35.1554183,
                1e-7);
    ASSERT_NEAR(device.getLastPosition().get_longitude().get_dd(), -119.8188167,
                1e-7);
}

TEST(SerialNmeaGpsDeviceTest, ReceiveDataFromUART_MidSentence)
{
    // Set up UART
    sabre::hal::Uart::UniquePtr uart =
        std::make_unique<sabre::impl::sabre_testing::TestUART>();
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
    ASSERT_NEAR(device.getLastPosition().get_latitude().get_dd(), 34.1554183,
                1e-7);
    ASSERT_NEAR(device.getLastPosition().get_longitude().get_dd(), -118.8188167,
                1e-7);
}

TEST(SerialNmeaGpsDeviceTest, ReceiveDataFromUART_MidSentenceStop)
{
    // Set up UART
    sabre::hal::Uart::UniquePtr uart =
        std::make_unique<sabre::impl::sabre_testing::TestUART>();
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
    ASSERT_NEAR(device.getLastPosition().get_latitude().get_dd(), 34.1554183,
                1e-7);
    ASSERT_NEAR(device.getLastPosition().get_longitude().get_dd(), -118.8188167,
                1e-7);
}

TEST(SerialNmeaGpsDeviceTest, ReceiveDataFromUART_InvalidData)
{
    // Set up UART
    sabre::hal::Uart::UniquePtr uart =
        std::make_unique<sabre::impl::sabre_testing::TestUART>();
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
    sabre::hal::Uart::UniquePtr uart =
        std::make_unique<sabre::impl::sabre_testing::TestUART>();
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
    ASSERT_NEAR(device.getLastPosition().get_latitude().get_dd(), 34.1554183,
                1e-7);
    ASSERT_NEAR(device.getLastPosition().get_longitude().get_dd(), -118.8188167,
                1e-7);
}

TEST(SerialNmeaGpsDeviceTest, SwitchUARTPtr)
{
    // Set up UART-1
    sabre::hal::Uart::UniquePtr uart =
        std::make_unique<sabre::impl::sabre_testing::TestUART>();
    for (char c : "$GNRMC,120000.000,A,3409.3251,N,11849.1290,W,0.00,0.00,"
                  "061125,,,A*64\r\n")
        uart->writeByte(c);

    // Read the data from UART-1
    sabre::devices::SerialNmeaGpsDevice device(uart.get());
    while (device.readData())
        ;

    ASSERT_TRUE(device.isValidPosition());
    ASSERT_NEAR(device.getLastPosition().get_latitude().get_dd(), 34.1554183,
                1e-7);
    ASSERT_NEAR(device.getLastPosition().get_longitude().get_dd(), -118.8188167,
                1e-7);

    // Set up UART-2
    sabre::hal::Uart::UniquePtr uart2 =
        std::make_unique<sabre::impl::sabre_testing::TestUART>();
    for (char c : "$GNRMC,120000.000,A,3609.3251,N,12049.1290,W,0.00,0.00,"
                  "061125,,,A*6D\r\n")
        uart2->writeByte(c);

    // Switch to UART-2 and read data
    device.setUartPtr(uart2.get());
    while (device.readData())
        ;

    ASSERT_TRUE(device.isValidPosition());
    ASSERT_NEAR(device.getLastPosition().get_latitude().get_dd(), 36.1554183,
                1e-7);
    ASSERT_NEAR(device.getLastPosition().get_longitude().get_dd(), -120.8188167,
                1e-7);
}

TEST(SerialNmeaGpsDeviceTest, WriteToUart)
{
    std::string gnrmc =
        "$GNRMC,120000.000,A,3409.3251,N,11849.1290,W,0.00,0.00,"
        "061125,,,A*64\r\n";
    sabre::hal::Uart::UniquePtr uart =
        std::make_unique<sabre::impl::sabre_testing::TestUART>();
    for (char c : gnrmc)
        uart->writeByte(c);

    sabre::hal::Uart::UniquePtr out_uart =
        std::make_unique<sabre::impl::sabre_testing::TestUART>();
    sabre::devices::SerialNmeaGpsDevice device(uart.get());
    device.setOutputUartPtr(out_uart.get());
    while (device.readData())
        ;
    ASSERT_EQ(out_uart->readBytes(gnrmc.length(), 100), gnrmc);
}