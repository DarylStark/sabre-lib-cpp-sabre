#include "test_core.hpp"
#include "sabre/core/exceptions.hpp"
#include <gtest/gtest.h>
#include <sabre/log/logging.hpp>
#include <sabre_test_mocks/hal.hpp>
#include <sabre_test_mocks/log.hpp>

TEST(SabreExceptionTest, CustomMessage)
{
    sabre::core::SabreException ex("Custom error message");
    ASSERT_STREQ(ex.what(), "Custom error message");
}

TEST(SabreExceptionTest, APIErrorDefaultMessage)
{
    sabre::core::ApiError apiError;
    ASSERT_STREQ(apiError.what(), "Unknown API error");
}

TEST(SabreExceptionTest, APIErrorCustomMessage)
{
    class DerivedAPIError : public sabre::core::ApiError
    {
    public:
        DerivedAPIError(const std::string &msg) : sabre::core::ApiError(msg) {}
    };
    DerivedAPIError apiError("Specific API error occurred");
    ASSERT_STREQ(apiError.what(), "Specific API error occurred");
}

TEST_F(ResourceManagerTest, RetrieveGpioResourceManager)
{
    auto &gpio_rm1 = _manager.gpio();
    auto &gpio_rm2 = _manager.gpio();
    ASSERT_EQ(&gpio_rm1, &gpio_rm2);
}

TEST_F(ResourceManagerTest, RetrieveSerialResourceManager)
{
    auto &serial_rm1 = _manager.serial();
    auto &serial_rm2 = _manager.serial();
    ASSERT_EQ(&serial_rm1, &serial_rm2);
}

TEST_F(ResourceManagerTest, RetrieveLogManager)
{
    auto &log_manager1 = _manager.getLogManager();
    auto &log_manager2 = _manager.getLogManager();
    ASSERT_EQ(&log_manager1, &log_manager2);
}

TEST_F(ResourceManagerTest, RetrieveFactory)
{
    auto &factory1 = _manager.getFactory();
    auto &factory2 = _manager.getFactory();
    ASSERT_EQ(&factory1, &factory2);
}

TEST_F(ResourceManagerTest, RetrieveTimeResourceManager)
{
    auto &time_rm1 = _manager.time();
    auto &time_rm2 = _manager.time();
    ASSERT_EQ(&time_rm1, &time_rm2);
}

TEST_F(ResourceManagerTest, RetrieveNetworkResourceManager)
{
    auto &network_rm1 = _manager.network();
    auto &network_rm2 = _manager.network();
    ASSERT_EQ(&network_rm1, &network_rm2);
}

TEST_F(ResourceManagerTest, RetrievePlatform)
{
    auto &platform1 = _manager.getPlatform();
    auto &platform2 = _manager.getPlatform();
    ASSERT_EQ(&platform1, &platform2);
}

TEST_F(GpioResourceManagerTest, CreateDifferentInputGpios)
{
    const auto &gpio1 = _gpio_rm.getInputGpio(26);
    const auto &gpio2 = _gpio_rm.getInputGpio(25);
    ASSERT_NE(&gpio1, &gpio2);
}

TEST_F(GpioResourceManagerTest, CreateInputGpioTwice)
{
    const auto &gpio1 = _gpio_rm.getInputGpio(26);
    const auto &gpio2 = _gpio_rm.getInputGpio(26);
    ASSERT_EQ(&gpio1, &gpio2);
}

TEST_F(GpioResourceManagerTest, CreateDifferentOutputGpios)
{
    const auto &gpio1 = _gpio_rm.getOutputGpio(26);
    const auto &gpio2 = _gpio_rm.getOutputGpio(25);
    ASSERT_NE(&gpio1, &gpio2);
}

TEST_F(GpioResourceManagerTest, CreateOutputGpioTwice)
{
    const auto &gpio1 = _gpio_rm.getOutputGpio(26);
    const auto &gpio2 = _gpio_rm.getOutputGpio(26);
    ASSERT_EQ(&gpio1, &gpio2);
}

TEST_F(GpioResourceManagerTest, CreateOutputAfterInput)
{
    const auto &gpio1 = _gpio_rm.getInputGpio(26);
    ASSERT_THROW(_gpio_rm.getOutputGpio(26), sabre::core::GpioInUseException);
}

TEST_F(GpioResourceManagerTest, CreateInputAfterOuput)
{
    const auto &gpio1 = _gpio_rm.getOutputGpio(26);
    ASSERT_THROW(_gpio_rm.getInputGpio(26), sabre::core::GpioInUseException);
}

TEST_F(GpioResourceManagerTest, CreateInputGpioToHigh)
{
    ASSERT_THROW(const auto &gpio1 = _gpio_rm.getInputGpio(30),
                 sabre::core::GpioUnavailableException);
}

TEST_F(GpioResourceManagerTest, CreateOutputGpioToHigh)
{
    ASSERT_THROW(const auto &gpio1 = _gpio_rm.getOutputGpio(30),
                 sabre::core::GpioUnavailableException);
}

TEST_F(GpioResourceManagerTest, CreateInputGpioToLow)
{
    ASSERT_THROW(const auto &gpio1 = _gpio_rm.getInputGpio(-1),
                 sabre::core::GpioUnavailableException);
}

TEST_F(GpioResourceManagerTest, CreateOutputGpioToLow)
{
    ASSERT_THROW(const auto &gpio1 = _gpio_rm.getOutputGpio(-1),
                 sabre::core::GpioUnavailableException);
}

TEST_F(GpioResourceManagerTest, CreateInputGpioZero)
{
    ASSERT_NO_THROW(const auto &gpio1 = _gpio_rm.getInputGpio(0));
}

TEST_F(GpioResourceManagerTest, CreateOutputGpioZero)
{
    ASSERT_NO_THROW(const auto &gpio1 = _gpio_rm.getOutputGpio(0));
}

TEST_F(GpioResourceManagerTest, CreateInputGpioExactlyUpperBound)
{
    ASSERT_NO_THROW(const auto &gpio1 = _gpio_rm.getInputGpio(26));
}

TEST_F(GpioResourceManagerTest, CreateOutputGpioExactlyUpperBound)
{
    ASSERT_NO_THROW(const auto &gpio1 = _gpio_rm.getOutputGpio(26));
}

TEST_F(GpioResourceManagerTest, CreateGpioTwice)
{
    const auto &gpio1 = _gpio_rm.getGpio(26);
    const auto &gpio2 = _gpio_rm.getGpio(26);
    ASSERT_EQ(&gpio1, &gpio2);
}

TEST_F(GpioResourceManagerTest, CreateDifferentGpios)
{
    const auto &gpio1 = _gpio_rm.getGpio(26);
    const auto &gpio2 = _gpio_rm.getGpio(25);
    ASSERT_NE(&gpio1, &gpio2);
}

TEST_F(GpioResourceManagerTest, CreateGpioAfterOuput)
{
    const auto &gpio1 = _gpio_rm.getOutputGpio(26);
    ASSERT_THROW(_gpio_rm.getGpio(26), sabre::core::GpioInUseException);
}

TEST_F(GpioResourceManagerTest, CreateGpioToHigh)
{
    ASSERT_THROW(const auto &gpio1 = _gpio_rm.getGpio(30),
                 sabre::core::GpioUnavailableException);
}

TEST_F(GpioResourceManagerTest, CreateGpioToLow)
{
    ASSERT_THROW(const auto &gpio1 = _gpio_rm.getGpio(-1),
                 sabre::core::GpioUnavailableException);
}

TEST_F(GpioResourceManagerTest, CreateGpioZero)
{
    ASSERT_NO_THROW(const auto &gpio1 = _gpio_rm.getGpio(0));
}

TEST_F(GpioResourceManagerTest, LoggerAttachedToGpio)
{
    using namespace sabre::log;
    using sabre::impl::sabre_test_mocks::TestHandler;

    auto &gpio1 = _gpio_rm.getGpio(26);

    LoggingLevel lastLevel;
    std::string lastLoggerName;
    std::string lastMessage;

    _logManager.addHandler(
        "testLogger",
        std::make_unique<TestHandler>(lastLevel, lastLoggerName, lastMessage));
    gpio1.getLogHelper().log(LoggingLevel::ERROR, "TestMessage");

    ASSERT_EQ(lastLevel, LoggingLevel::ERROR);
    ASSERT_EQ(lastLoggerName, "Gpio_26");
    ASSERT_EQ(lastMessage, "TestMessage");
}

TEST_F(GpioResourceManagerTest, LoggerAttachedToInputGpio)
{
    using namespace sabre::log;
    using sabre::impl::sabre_test_mocks::TestHandler;

    auto &gpio1 = _gpio_rm.getInputGpio(26);

    LoggingLevel lastLevel;
    std::string lastLoggerName;
    std::string lastMessage;

    _logManager.addHandler(
        "testLogger",
        std::make_unique<TestHandler>(lastLevel, lastLoggerName, lastMessage));
    gpio1.getLogHelper().log(LoggingLevel::ERROR, "TestMessage");

    ASSERT_EQ(lastLevel, LoggingLevel::ERROR);
    ASSERT_EQ(lastLoggerName, "InputGpio_26");
    ASSERT_EQ(lastMessage, "TestMessage");
}

TEST_F(GpioResourceManagerTest, LoggerAttachedToOutputGpio)
{
    using namespace sabre::log;
    using sabre::impl::sabre_test_mocks::TestHandler;

    auto &gpio1 = _gpio_rm.getOutputGpio(26);

    LoggingLevel lastLevel;
    std::string lastLoggerName;
    std::string lastMessage;

    _logManager.addHandler(
        "testLogger",
        std::make_unique<TestHandler>(lastLevel, lastLoggerName, lastMessage));
    gpio1.getLogHelper().log(LoggingLevel::ERROR, "TestMessage");

    ASSERT_EQ(lastLevel, LoggingLevel::ERROR);
    ASSERT_EQ(lastLoggerName, "OutputGpio_26");
    ASSERT_EQ(lastMessage, "TestMessage");
}

TEST_F(SerialResourceManagerTest, RetrieveTheSameUart)
{
    _serial_rm.configureUart(0, 9600, sabre::impl::sabre_test_mocks::StGpio(24),
                             sabre::impl::sabre_test_mocks::StGpio(25), 128);
    const auto &uart1 = _serial_rm.getUart(0);
    const auto &uart2 = _serial_rm.getUart(0);
    ASSERT_EQ(&uart1, &uart2);
}

TEST_F(SerialResourceManagerTest, RetrieveTheDifferentUart)
{
    _serial_rm.configureUart(0, 9600, sabre::impl::sabre_test_mocks::StGpio(24),
                             sabre::impl::sabre_test_mocks::StGpio(25), 128);
    _serial_rm.configureUart(1, 9600, sabre::impl::sabre_test_mocks::StGpio(20),
                             sabre::impl::sabre_test_mocks::StGpio(21), 128);
    const auto &uart1 = _serial_rm.getUart(0);
    const auto &uart2 = _serial_rm.getUart(1);
    ASSERT_NE(&uart1, &uart2);
}

TEST_F(SerialResourceManagerTest, RetrieveUartWithoutConfiguration)
{
    ASSERT_THROW(_serial_rm.getUart(0), std::runtime_error);
}

TEST_F(SerialResourceManagerTest, ConfigureUartTwice)
{
    _serial_rm.configureUart(0, 9600, sabre::impl::sabre_test_mocks::StGpio(24),
                             sabre::impl::sabre_test_mocks::StGpio(25), 128);
    ASSERT_THROW(_serial_rm.configureUart(
                     0, 9600, sabre::impl::sabre_test_mocks::StGpio(20),
                     sabre::impl::sabre_test_mocks::StGpio(21), 128),
                 std::runtime_error);
}

TEST_F(SerialResourceManagerTest, ConfigureUartOutsideBounds)
{
    ASSERT_THROW(_serial_rm.configureUart(
                     4, 9600, sabre::impl::sabre_test_mocks::StGpio(20),
                     sabre::impl::sabre_test_mocks::StGpio(21), 128),
                 std::out_of_range);
}

TEST_F(SerialResourceManagerTest, RetrieveTheSameUsbCdc)
{
    _serial_rm.configureUsbCdc(0, 128);
    const auto &usbcdc1 = _serial_rm.getUsbCdc(0);
    const auto &usbcdc2 = _serial_rm.getUsbCdc(0);
    ASSERT_EQ(&usbcdc1, &usbcdc2);
}

TEST_F(SerialResourceManagerTest, RetrieveTheDifferentUsbCdc)
{
    _serial_rm.configureUsbCdc(0, 128);
    _serial_rm.configureUsbCdc(1, 128);
    const auto &usbcdc1 = _serial_rm.getUsbCdc(0);
    const auto &usbcdc2 = _serial_rm.getUsbCdc(1);
    ASSERT_NE(&usbcdc1, &usbcdc2);
}

TEST_F(SerialResourceManagerTest, RetrieveUsbCdcWithoutConfiguration)
{
    ASSERT_THROW(_serial_rm.getUsbCdc(0), std::runtime_error);
}

TEST_F(SerialResourceManagerTest, ConfigureUsbCdcTwice)
{
    _serial_rm.configureUsbCdc(0, 128);
    ASSERT_THROW(_serial_rm.configureUsbCdc(0, 128), std::runtime_error);
}

TEST_F(SerialResourceManagerTest, LoggerAttachedToUart)
{
    using namespace sabre::log;
    using sabre::impl::sabre_test_mocks::TestHandler;

    _serial_rm.configureUart(1, 9600, sabre::impl::sabre_test_mocks::StGpio(20),
                             sabre::impl::sabre_test_mocks::StGpio(21), 512);
    auto &uart1 = _serial_rm.getUart(1);

    LoggingLevel lastLevel;
    std::string lastLoggerName;
    std::string lastMessage;

    _logManager.addHandler(
        "testLogger",
        std::make_unique<TestHandler>(lastLevel, lastLoggerName, lastMessage));
    uart1.getLogHelper().log(LoggingLevel::ERROR, "TestMessage");

    ASSERT_EQ(lastLevel, LoggingLevel::ERROR);
    ASSERT_EQ(lastLoggerName, "Uart_1");
    ASSERT_EQ(lastMessage, "TestMessage");
}

TEST_F(SerialResourceManagerTest, LoggerAttachedToUsbCdc)
{
    using namespace sabre::log;
    using sabre::impl::sabre_test_mocks::TestHandler;

    _serial_rm.configureUsbCdc(1, 128);
    auto &usbcdc1 = _serial_rm.getUsbCdc(1);

    LoggingLevel lastLevel;
    std::string lastLoggerName;
    std::string lastMessage;

    _logManager.addHandler(
        "testLogger",
        std::make_unique<TestHandler>(lastLevel, lastLoggerName, lastMessage));
    usbcdc1.getLogHelper().log(LoggingLevel::ERROR, "TestMessage");

    ASSERT_EQ(lastLevel, LoggingLevel::ERROR);
    ASSERT_EQ(lastLoggerName, "UsbCdc_1");
    ASSERT_EQ(lastMessage, "TestMessage");
}

TEST_F(SerialResourceManagerTest, RetrieveTheSameSerialBufferUsbCdc)
{
    _serial_rm.configureUsbCdc(0, 128);
    const auto &streambuf1 = _serial_rm.getSerialStreamBufForUsbCdc(0);
    const auto &streambuf2 = _serial_rm.getSerialStreamBufForUsbCdc(0);
    ASSERT_EQ(&streambuf1, &streambuf2);
}

TEST_F(SerialResourceManagerTest, RetrieveTheDifferentSerialBufferUsbCdc)
{
    _serial_rm.configureUsbCdc(0, 128);
    _serial_rm.configureUsbCdc(1, 128);
    const auto &streambuf1 = _serial_rm.getSerialStreamBufForUsbCdc(0);
    const auto &streambuf2 = _serial_rm.getSerialStreamBufForUsbCdc(1);
    ASSERT_NE(&streambuf1, &streambuf2);
}

TEST_F(SerialResourceManagerTest,
       RetrieveSerialBufferUsbCdcWithoutConfiguration)
{
    ASSERT_THROW(_serial_rm.getSerialStreamBufForUsbCdc(0), std::runtime_error);
}

/****************** */

TEST_F(SerialResourceManagerTest, RetrieveTheSameSerialBufferUart)
{
    _serial_rm.configureUart(0, 9600, sabre::impl::sabre_test_mocks::StGpio(24),
                             sabre::impl::sabre_test_mocks::StGpio(25), 128);
    const auto &streambuf1 = _serial_rm.getSerialStreamBufForUart(0);
    const auto &streambuf2 = _serial_rm.getSerialStreamBufForUart(0);
    ASSERT_EQ(&streambuf1, &streambuf2);
}

TEST_F(SerialResourceManagerTest, RetrieveTheDifferentSerialBufferUart)
{
    _serial_rm.configureUart(0, 9600, sabre::impl::sabre_test_mocks::StGpio(24),
                             sabre::impl::sabre_test_mocks::StGpio(25), 128);
    _serial_rm.configureUart(1, 9600, sabre::impl::sabre_test_mocks::StGpio(20),
                             sabre::impl::sabre_test_mocks::StGpio(21), 128);
    const auto &streambuf1 = _serial_rm.getSerialStreamBufForUart(0);
    const auto &streambuf2 = _serial_rm.getSerialStreamBufForUart(1);
    ASSERT_NE(&streambuf1, &streambuf2);
}

TEST_F(SerialResourceManagerTest, RetrieveSerialBufferUartWithoutConfiguration)
{
    ASSERT_THROW(_serial_rm.getSerialStreamBufForUart(0), std::runtime_error);
}

TEST_F(SerialResourceManagerTest, RetrieveOutputStreamForUart)
{
    _serial_rm.configureUart(0, 9600, sabre::impl::sabre_test_mocks::StGpio(24),
                             sabre::impl::sabre_test_mocks::StGpio(25), 128);
    auto &uart = _serial_rm.getUart(0);
    sabre::impl::sabre_test_mocks::TestUART *uart_impl =
        dynamic_cast<sabre::impl::sabre_test_mocks::TestUART *>(&uart);

    std::ostream stream1 = _serial_rm.getOutputStreamForUart(0);
    stream1 << "TEST" << std::flush;

    ASSERT_EQ(uart_impl->_buf, "TEST");
}

TEST_F(SerialResourceManagerTest, RetrieveOutputStreamForUsbCdc)
{
    _serial_rm.configureUsbCdc(0, 128);
    auto &usb = _serial_rm.getUsbCdc(0);
    sabre::impl::sabre_test_mocks::TestUART *uart_impl =
        dynamic_cast<sabre::impl::sabre_test_mocks::TestUART *>(&usb);

    std::ostream stream1 = _serial_rm.getOutputStreamForUsbCdc(0);
    stream1 << "TEST" << std::flush;

    ASSERT_EQ(uart_impl->_buf, "TEST");
}

TEST_F(TimeResourceManagerTest, RetrieveWallClock)
{
    auto &wallclock1 = _time_rm.getWallClock();
    auto &wallclock2 = _time_rm.getWallClock();
    ASSERT_EQ(&wallclock1, &wallclock2);
}

TEST_F(TimeResourceManagerTest, LoggerAttachedToWallClock)
{
    using namespace sabre::log;
    using sabre::impl::sabre_test_mocks::TestHandler;

    auto &wallblock = _time_rm.getWallClock();

    LoggingLevel lastLevel;
    std::string lastLoggerName;
    std::string lastMessage;

    _logManager.addHandler(
        "testLogger",
        std::make_unique<TestHandler>(lastLevel, lastLoggerName, lastMessage));
    wallblock.getLogHelper().log(LoggingLevel::ERROR, "TestMessage");

    ASSERT_EQ(lastLevel, LoggingLevel::ERROR);
    ASSERT_EQ(lastLoggerName, "WallClock");
    ASSERT_EQ(lastMessage, "TestMessage");
}

TEST_F(TimeResourceManagerTest, RetrieveTheSameNtpClient)
{
    _time_rm.configureNtpClient("default", "time.ntp.org");
    const auto &ntp1 = _time_rm.getNtpClient("default");
    const auto &ntp2 = _time_rm.getNtpClient("default");
    ASSERT_EQ(&ntp1, &ntp2);
}

TEST_F(TimeResourceManagerTest, RetrieveTheDifferentNtp)
{
    _time_rm.configureNtpClient("default", "time.ntp.org");
    _time_rm.configureNtpClient("secondary", "time.ntp.com");
    const auto &ntp1 = _time_rm.getNtpClient("default");
    const auto &ntp2 = _time_rm.getNtpClient("secondary");
    ASSERT_NE(&ntp1, &ntp2);
}

TEST_F(TimeResourceManagerTest, RetrieveNtpClientWithoutConfiguration)
{
    ASSERT_THROW(_time_rm.getNtpClient("default"), std::runtime_error);
}

TEST_F(TimeResourceManagerTest, ConfigureNtpTwice)
{
    _time_rm.configureNtpClient("default", "time.ntp.org");
    ASSERT_THROW(_time_rm.configureNtpClient("default", "time.ntp.org"),
                 std::runtime_error);
}

TEST_F(TimeResourceManagerTest, LoggerAttachedToNtp)
{
    using namespace sabre::log;
    using sabre::impl::sabre_test_mocks::TestHandler;

    _time_rm.configureNtpClient("default", "time.ntp.org");
    auto &ntp = _time_rm.getNtpClient("default");

    LoggingLevel lastLevel;
    std::string lastLoggerName;
    std::string lastMessage;

    _logManager.addHandler(
        "testLogger",
        std::make_unique<TestHandler>(lastLevel, lastLoggerName, lastMessage));
    ntp.getLogHelper().log(LoggingLevel::ERROR, "TestMessage");

    ASSERT_EQ(lastLevel, LoggingLevel::ERROR);
    ASSERT_EQ(lastLoggerName, "NtpClient_default");
    ASSERT_EQ(lastMessage, "TestMessage");
}

TEST_F(NetworkResourceManagerTest, RetrieveWifiSoftAp)
{
    auto &soft_ap1 = _net_rm.getWifiSoftAp();
    auto &soft_ap2 = _net_rm.getWifiSoftAp();
    ASSERT_EQ(&soft_ap1, &soft_ap2);
}

TEST_F(NetworkResourceManagerTest, LoggerAttachedToWifiSoftAp)
{
    using namespace sabre::log;
    using sabre::impl::sabre_test_mocks::TestHandler;

    auto &soft_ap = _net_rm.getWifiSoftAp();

    LoggingLevel lastLevel;
    std::string lastLoggerName;
    std::string lastMessage;

    _logManager.addHandler(
        "testLogger",
        std::make_unique<TestHandler>(lastLevel, lastLoggerName, lastMessage));
    soft_ap.getLogHelper().log(LoggingLevel::ERROR, "TestMessage");

    ASSERT_EQ(lastLevel, LoggingLevel::ERROR);
    ASSERT_EQ(lastLoggerName, "WifiSoftAp");
    ASSERT_EQ(lastMessage, "TestMessage");
}

TEST_F(NetworkResourceManagerTest, RetrieveWifiStation)
{
    auto &station1 = _net_rm.getWifiStation();
    auto &station2 = _net_rm.getWifiStation();
    ASSERT_EQ(&station1, &station2);
}

TEST_F(NetworkResourceManagerTest, LoggerAttachedToWifiStation)
{
    using namespace sabre::log;
    using sabre::impl::sabre_test_mocks::TestHandler;

    auto &station = _net_rm.getWifiStation();

    LoggingLevel lastLevel;
    std::string lastLoggerName;
    std::string lastMessage;

    _logManager.addHandler(
        "testLogger",
        std::make_unique<TestHandler>(lastLevel, lastLoggerName, lastMessage));
    station.getLogHelper().log(LoggingLevel::ERROR, "TestMessage");

    ASSERT_EQ(lastLevel, LoggingLevel::ERROR);
    ASSERT_EQ(lastLoggerName, "WifiStation");
    ASSERT_EQ(lastMessage, "TestMessage");
}

TEST_F(NetworkResourceManagerTest, RetrieveTheSameMqttClient)
{
    auto &mqtt1 = _net_rm.getMqttClient("default");
    auto &mqtt2 = _net_rm.getMqttClient("default");
    ASSERT_EQ(&mqtt1, &mqtt2);
}

TEST_F(NetworkResourceManagerTest, RetrieveDifferentMqttClients)
{
    auto &mqtt1 = _net_rm.getMqttClient("default");
    auto &mqtt2 = _net_rm.getMqttClient("secondary");
    ASSERT_NE(&mqtt1, &mqtt2);
}

TEST_F(NetworkResourceManagerTest, LoggerAttachedToMqttClient)
{
    using namespace sabre::log;
    using sabre::impl::sabre_test_mocks::TestHandler;

    auto &wallblock = _net_rm.getMqttClient("default");

    LoggingLevel lastLevel;
    std::string lastLoggerName;
    std::string lastMessage;

    _logManager.addHandler(
        "testLogger",
        std::make_unique<TestHandler>(lastLevel, lastLoggerName, lastMessage));
    wallblock.getLogHelper().log(LoggingLevel::ERROR, "TestMessage");

    ASSERT_EQ(lastLevel, LoggingLevel::ERROR);
    ASSERT_EQ(lastLoggerName, "MqttClient_default");
    ASSERT_EQ(lastMessage, "TestMessage");
}