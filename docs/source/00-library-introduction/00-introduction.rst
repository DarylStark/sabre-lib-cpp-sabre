Sabre introduction
==================

Sabre is a C++ library designed to provide a consistent way of building applications for IoT devices on Microchip controllers. Sabre exposes a few abstract classes that platform specific interfaces can implement to expose the platform dependent API as Sabre classes. By doing this, applications can be depend on the abstract interfaces and rely on the interfaces run the application on specific hardware.

This documentation is divided in two parts:

-   Documentation for people who want to implement their favourite MCU API as Sabre
-   Documentation for people who want to create application for Sabre