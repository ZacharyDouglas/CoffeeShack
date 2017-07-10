# CoffeeShack

The purpose of this project is to demonstrate my ability to work with the Decorator Design pattern.  

In this project, a customer orders a coffee from the barista with a select number of options.  The barista calculates the cost and makes the coffee with the desired options.

Each customer/observer order is registered the barista/Subject.  This allows the barista to keep track of the orders and the cost.

The base class "Item" is inherited by multiple classes that decorate the "Item" to include the proper characteristics.

i.e - Small Coffee is $1.00.  Sprinkles are $0.50.  Caramel is $0.20.

As each item is added to the coffee, it adds the item to the barista's registry which allows for the orders to be tracked.
