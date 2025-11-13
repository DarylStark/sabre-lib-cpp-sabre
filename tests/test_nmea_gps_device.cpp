#include <gtest/gtest.h>

#include "sabre_testing/uart/uart.hpp"
#include <sabre/devices/serial_nmea_gps_device.hpp>

TEST(SerialNmeaGpsDeviceTest, DefaultConstructor)
{
    sabre::devices::SerialNmeaGpsDevice device;
    EXPECT_FALSE(device.is_valid_position());
    EXPECT_FALSE(device.read());
}

TEST(SerialNmeaGpsDeviceTest, ReceiveDataFromUART)
{
    // Set up UART
    sabre::UARTUniquePtr uart = std::make_unique<sabre::testing::TestUART>();
    for (char c : "$GNRMC,120000.000,A,3409.3251,N,11849.1290,W,0.00,0.00,"
                  "061125,,,A*64\r\n")
        uart->write_byte(c);

    // Read the data
    sabre::devices::SerialNmeaGpsDevice device(uart.get());
    while (device.read())
        ;

    ASSERT_TRUE(device.is_valid_position());
    ASSERT_NEAR(device.get_last_position().get_latitude().get_dd(), 34.1554183,
                1e-7);
    ASSERT_NEAR(device.get_last_position().get_longitude().get_dd(),
                -118.8188167, 1e-7);
}

TEST(SerialNmeaGpsDeviceTest, ReceiveDataFromUART_MultipleScentences)
{
    // Set up UART
    sabre::UARTUniquePtr uart = std::make_unique<sabre::testing::TestUART>();
    for (char c :
         "$GNRMC,120000.000,A,3409.3251,N,11849.1290,W,0.00,0.00,"
         "061125,,,A\r\n$GNRMC,120000.000,A,3509.3251,N,11949.1290,W,0.00,0.00,"
         "061125,,,A*64\r\n")
        uart->write_byte(c);

    // Read the data
    sabre::devices::SerialNmeaGpsDevice device(uart.get());
    while (device.read())
        ;

    ASSERT_TRUE(device.is_valid_position());
    ASSERT_NEAR(device.get_last_position().get_latitude().get_dd(), 35.1554183,
                1e-7);
    ASSERT_NEAR(device.get_last_position().get_longitude().get_dd(),
                -119.8188167, 1e-7);
}

TEST(SerialNmeaGpsDeviceTest, ReceiveDataFromUART_MidSentence)
{
    // Set up UART
    sabre::UARTUniquePtr uart = std::make_unique<sabre::testing::TestUART>();
    for (char c :
         ".9999,N,11249.1290,W,0.00,0.00,"
         "061125,,,A\r\n$GNRMC,120000.000,A,3409.3251,N,11849.1290,W,0.00,0.00,"
         "061125,,,A*64\r\n")
        uart->write_byte(c);

    // Read the data
    sabre::devices::SerialNmeaGpsDevice device(uart.get());
    while (device.read())
        ;

    ASSERT_TRUE(device.is_valid_position());
    ASSERT_NEAR(device.get_last_position().get_latitude().get_dd(), 34.1554183,
                1e-7);
    ASSERT_NEAR(device.get_last_position().get_longitude().get_dd(),
                -118.8188167, 1e-7);
}

TEST(SerialNmeaGpsDeviceTest, ReceiveDataFromUART_MidSentenceStop)
{
    // Set up UART
    sabre::UARTUniquePtr uart = std::make_unique<sabre::testing::TestUART>();
    for (char c :
         ".9999,N,11249.1290,W,0.00,0.00,"
         "061125,,,A\r\n$GNRMC,120000.000,A,3409.3251,N,11849.1290,W,0.00,0.00,"
         "061125,,,A*64\r\n$GNRMC,120000.000,A,3509.3251,N,11949.1290,W,")
        uart->write_byte(c);

    // Read the data
    sabre::devices::SerialNmeaGpsDevice device(uart.get());
    while (device.read())
        ;
    ASSERT_TRUE(device.is_valid_position());
    ASSERT_NEAR(device.get_last_position().get_latitude().get_dd(), 34.1554183,
                1e-7);
    ASSERT_NEAR(device.get_last_position().get_longitude().get_dd(),
                -118.8188167, 1e-7);
}

TEST(SerialNmeaGpsDeviceTest, ReceiveDataFromUART_InvalidData)
{
    // Set up UART
    sabre::UARTUniquePtr uart = std::make_unique<sabre::testing::TestUART>();
    for (char c : "$GNRMC,112939.000,V,,,,,,,031125,,,N,V*2C\r\n")
        uart->write_byte(c);

    // Read the data
    sabre::devices::SerialNmeaGpsDevice device(uart.get());
    while (device.read())
        ;
    ASSERT_FALSE(device.is_valid_position());
}

TEST(SerialNmeaGpsDeviceTest, ReceiveDataFromUART_UARTError)
{
    // Set up UART
    sabre::UARTUniquePtr uart = std::make_unique<sabre::testing::TestUART>();
    for (char c : "$GNRMC,120000.000,A,3609.3251,N,11949.1290,W,0.00,0.00,"
                  "061125,,,A\r\n$GNRMC,120000.000,A,3409.$GNRMC,120000.000,A,"
                  "3409.3251,N,11849.1290,W,0.00,0.00,"
                  "061125,,,A*64\r\n")
        uart->write_byte(c);

    // Read the data
    sabre::devices::SerialNmeaGpsDevice device(uart.get());
    while (device.read())
        ;
    ASSERT_TRUE(device.is_valid_position());
    ASSERT_NEAR(device.get_last_position().get_latitude().get_dd(), 34.1554183,
                1e-7);
    ASSERT_NEAR(device.get_last_position().get_longitude().get_dd(),
                -118.8188167, 1e-7);
}

TEST(SerialNmeaGpsDeviceTest, SwitchUARTPtr)
{
    // Set up UART-1
    sabre::UARTUniquePtr uart = std::make_unique<sabre::testing::TestUART>();
    for (char c : "$GNRMC,120000.000,A,3409.3251,N,11849.1290,W,0.00,0.00,"
                  "061125,,,A*64\r\n")
        uart->write_byte(c);

    // Read the data from UART-1
    sabre::devices::SerialNmeaGpsDevice device(uart.get());
    while (device.read())
        ;

    ASSERT_TRUE(device.is_valid_position());
    ASSERT_NEAR(device.get_last_position().get_latitude().get_dd(), 34.1554183,
                1e-7);
    ASSERT_NEAR(device.get_last_position().get_longitude().get_dd(),
                -118.8188167, 1e-7);

    // Set up UART-2
    sabre::UARTUniquePtr uart2 = std::make_unique<sabre::testing::TestUART>();
    for (char c : "$GNRMC,120000.000,A,3609.3251,N,12049.1290,W,0.00,0.00,"
                  "061125,,,A*6D\r\n")
        uart2->write_byte(c);

    // Switch to UART-2 and read data
    device.set_uart_ptr(uart2.get());
    while (device.read())
        ;

    ASSERT_TRUE(device.is_valid_position());
    ASSERT_NEAR(device.get_last_position().get_latitude().get_dd(), 36.1554183,
                1e-7);
    ASSERT_NEAR(device.get_last_position().get_longitude().get_dd(),
                -120.8188167, 1e-7);
}

TEST(SerialNmeaGpsDeviceTest, WriteToUart)
{
    std::string gnrmc =
        "$GNRMC,120000.000,A,3409.3251,N,11849.1290,W,0.00,0.00,"
        "061125,,,A*64\r\n";
    sabre::UARTUniquePtr uart = std::make_unique<sabre::testing::TestUART>();
    for (char c : gnrmc)
        uart->write_byte(c);

    sabre::UARTUniquePtr out_uart =
        std::make_unique<sabre::testing::TestUART>();
    sabre::devices::SerialNmeaGpsDevice device(uart.get());
    device.set_output_uart_ptr(out_uart.get());
    while (device.read())
        ;
    ASSERT_EQ(out_uart->read_bytes(gnrmc.length(), 100), gnrmc);
}