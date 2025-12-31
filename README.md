# Sabre

Sabre is a platform-independent framework for programming microcontrollers in a consistent way. The framework provides a set of abstract interfaces that MCU implementations can implement, enabling you to write application code once and deploy it across different hardware platforms with minimal changes.

## Overview

Sabre takes a modular approach to embedded development:

- **Core Library (`sabre`)**: Provides platform-independent interfaces for common MCU functionality like GPIO, UART, WiFi, MQTT, time management, and OS services
- **Auxiliary Library (`pilot`)**: A simulator that lets you test your application logic on your development machine without physical hardware
- **Factory Pattern**: MCU-specific implementations create concrete instances of Sabre interfaces through a factory, making it easy to swap platforms

By implementing Sabre's interfaces, hardware vendors and developers can create consistent APIs across different microcontroller platforms, reducing the learning curve and increasing code portability.

## Class Structure

The Sabre library is organized into several namespaces:

### Core Components
- **`sabre::core::Factory`**: Abstract factory for creating platform-specific implementations of all Sabre interfaces
- **`sabre::runtime::App`**: Base class for your applications that uses the factory to access hardware

### Hardware Abstraction Layer (HAL)
- **`sabre::hal::Uart`**: Serial communication interface
- **`sabre::hal::InputGpio`**: Input GPIO pin interface
- **`sabre::hal::OutputGpio`**: Output GPIO pin interface

### Networking
- **`sabre::net::WifiStation`**: WiFi client mode interface
- **`sabre::net::WifiSoftAp`**: WiFi access point mode interface
- **`sabre::net::MqttClient`**: MQTT client interface

### Time Management
- **`sabre::time::WallClock`**: System clock interface
- **`sabre::time::NtpClient`**: NTP time synchronization interface

### Operating System
- **`sabre::os::Service`**: Background service/task interface

### Additional Modules
- **`sabre::parsers`**: GPS and NMEA parsing utilities
- **`sabre::models`**: Data models for networking and geographic data
- **`sabre::utility`**: Helper utilities like wait-for operations

## The Pilot Library

The `pilot` library is an auxiliary tool that simulates MCU hardware on your development machine. It provides concrete implementations of all Sabre interfaces, allowing you to:

- Test your application logic without physical hardware
- Rapidly iterate on features during development
- Run automated tests in CI/CD pipelines
- Debug complex scenarios in a controlled environment

Pilot uses the same Factory pattern as real MCU implementations, so your application code remains unchanged when switching between the simulator and actual hardware.

## Development Environment

### Using the Dev Container

The easiest way to get started with Sabre development is using the provided dev container. The dev container comes pre-configured with all necessary tools and dependencies.

**Prerequisites:**
- [Docker](https://www.docker.com/) installed and running
- [Visual Studio Code](https://code.visualstudio.com/) with the [Dev Containers extension](https://marketplace.visualstudio.com/items?itemName=ms-vscode-remote.remote-containers)

**Getting Started:**

1. Open the repository in Visual Studio Code
2. When prompted, click "Reopen in Container" (or use the command palette: `Dev Containers: Reopen in Container`)
3. The container will build and start automatically, installing all required dependencies including:
   - CMake and Ninja build system
   - C++ compiler toolchain
   - GLFW development libraries
   - All necessary build tools

Once the container is running, you can build and test the project directly from within the containerized environment. All commands in this README will work seamlessly inside the dev container.

## Building the Project

Sabre uses CMake with presets for easy configuration. **CMake 3.20 or newer is required.**

### Available CMake Presets

The following presets are available:

- **`dbg-sabre-pilot-tests`**: Debug build with Sabre library, Pilot simulator, and tests enabled
- **`dbg-sabre-tests`**: Debug build with Sabre library and tests, but without Pilot
- **`dbg-sabre`**: Debug build with only the Sabre library (no tests, no Pilot)
- **`rel-sabre-tests`**: Release build with Sabre library and tests, but without Pilot

### CMake Options

Presets configure these CMake variables:

- **`SABRE_BUILD_TESTS`**: Set to `ON` to build tests, `OFF` to skip them
- **`SABRE_BUILD_PILOT`**: Set to `ON` to build the Pilot simulator, `OFF` to skip it

### Build Instructions

To build the project with a preset:

> **Note:** All presets use the [Ninja](https://ninja-build.org/) build system. Make sure Ninja is installed on your system.

```bash
# Configure with your chosen preset
cmake --preset dbg-sabre-pilot-tests

# Build the project
cmake --build build/dbg-sabre-pilot-tests
```

For a release build with tests:

```bash
cmake --preset rel-sabre-tests
cmake --build build/rel-sabre-tests
```

## Running Tests

After building with a preset that includes tests (e.g., `dbg-sabre-pilot-tests` or `rel-sabre-tests`), you can run the test suite using CTest:

```bash
# Navigate to the build directory
cd build/dbg-sabre-pilot-tests

# Run all tests
ctest

# Run tests with verbose output
ctest --verbose

# Run a specific test
ctest -R test_name
```

The test suite uses Google Test and includes unit tests for the Sabre library components.
