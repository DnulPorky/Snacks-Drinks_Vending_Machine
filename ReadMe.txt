 

+++ Snacks and Drinks Vending Machine ++ 

 

The purpose of this C project was to simulate the behavior of a snacks and drinks vending machine. 

Just like in real life, our machine sells a number of products, having different prices, some of them being available and other being sold out(or may become sold out if the user buys entire remaining stock). Also, just like any other vending machine, this one returns the rest of the money to the user if he bought something, and the credit inserted is higher than his purchase. In order to return the rest of client's money, our machine has a stock of different bill types(it accepts and use only 1 , 5 , 10 and 50 $ bills).  The user will receive the rest of its money only if he choose so, he has the option to continue shopping using that rest or adding some more credit if that's not enough for another purchase. Also, the user may donate the change if he choose so, or he may simply forget about the it :) 

Another possible scenario is when the machine does not have enough suited bills to pay the rest of client's credit for a certain purchase. If that's the situation, the client will be warned before the purchase and he may choose to renounce that purchase and withdraw his credit or he may choose to make the purchase anyway and use the rest to buy another product or simply donate the change. 

 In order to test this software, the user will have to setup the machine, inserting the number of products that will be for sale and the number of different bills used to pay customer's change. After that the software will generate codes, stocks and prices for products and it will invite you to insert credit and make a purchase. Even if the client inserted some credit he may change his mind and withdraw his money before making any purchase. 

The specifications of this projects methods and functionalities are described in Automat.h (header file for C language) and implemented in Automat.c source file. Besides these 2 files the project also contains Tema.c source file, which contains main() method that is "responsible"  for simulating the vending machine behaviour, interacting with user by input/output messages and makes use of all the methods implemented in Automat.c. 

Enjoy ! 

 