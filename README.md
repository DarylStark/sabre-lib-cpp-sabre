# Sabre

Sabre is a platform-independent framework for programming microcontrollers in a consistent way. The framework itself contains a few abstract classes that should be overridden by platform-dependent frameworks to implement specific APIs. By using consistent code, software designers can write software for different devices without changing too much.

## Building and testing

To build the framework, you have to use `cmake`. There are three CMake presets defined:

-   Debug - with tests
-   Release - with tests
-   Release - without tests

To build the project, use the following commands (replace the preset name if your configuration differs):

> **Note:** The example below uses the `ninja-release-with-tests` preset, which requires [Ninja](https://ninja-build.org/) to be installed. If you do not have Ninja or wish to use a different generator, use the appropriate preset for your setup.
```bash
cmake --preset ninja-release-with-tests
cmake --build build/release-with-tests
```

After that, you can run the tests:

```bash
cd build/release-with-tests
ctest
```

> Note: This only tests the implementation in this repository. It does not test any platform-specific implementations. Platform-specific frameworks should provide and test their own code.