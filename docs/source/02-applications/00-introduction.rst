Applications
============

Applications are instances of a class that inherits from `sabre::runtime::App<ReturnType>`. The only method that should be overriden in this subclass, is a method called `run` with the following signature:

.. code-block:: cpp

   #include <sabre/runtime/app.hpp>

   class MyPersonalApp: public sabre::runtime::App<int>
   {
   public:
       int run() override
       {
           auto& button = getResourceManager().gpio.getInputGpio(10);
           auto& led = getResourceManager().gpio.getOutputGpio(2);

           while(true)
           {
               led.setLevel(button.getLevel());
           }
       }
   };
