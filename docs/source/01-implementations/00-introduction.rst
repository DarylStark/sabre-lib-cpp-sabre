Implementations
===============

It is possible to create a implementation for the MCU you want to use. To do this, you have to override a few Sabre classes with the correct code for the API for the MCU you want to use. As a convention, all implemented classes go inside the ``sabre::impl::<implementation-name>`` namespace. For instance, if you are creating a implementation for Raspberry Pi Pico, you should place all implementations inside the namespace ``sabre::impl::pico``.

In the following pages you can find which classes should be overridden and which methods specifically should be overridden.

.. toctree::
   :maxdepth: 1
   :caption: Contents:

   ./01-classes-to-override