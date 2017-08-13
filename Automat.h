#ifndef Automat
#define Automat

 /*
Homework: Drinks and Snacks Vending Machine
Author: Costin Mircea
*/

/**
*Maximum number of products
*/
#define MAX_NUMBER_OF_PRODUCTS 100 

/**
* Available bill types.
*/
typedef enum { _1_DOLLAR = 1, _5_DOLLARS = 5, _10_DOLLARS = 10, _50_DOLLARS = 50 } bill_type;
typedef struct products{
		int product_code;
		int product_price;
		int product_quantity;
	}product_info;

/**
* Sets the number of available bills of given bill type.
* param - bill type, number of bills to be set
*/
void set_available_bills(bill_type bill, int count);

/**
* Returns the number of availabe bills of certain given type.
* (-1, if given bill type stock is 0).
* param - bill type
*/
int get_available_bills(bill_type bill);

/**
* Sets the number of available products.Initially, this number
* must be 0.
*/
void set_number_of_products(int count);

/**
* Returns total number of available products,
* we're talking about different product types not their stocks.
*/
int get_number_of_products();

/**
* The client must insert bills to reach enough credit to buy the product/s he wants
* or he may change his mind abd withdraw the sum he just inserted.
*/
void insert_credit();

/**
* Returns the price for a certain product, identified by its unique code.
* param - the code of the product. Every product must have an unique code.
*/
int get_product_cost(int code);

/**
* Sets the price for a product.
* param - product unique code, price to be set
*/
void set_product_cost(int code, int cost);

/**
* Sets the stock for a certain product.
* param - product unique code, quantity to be set
*/
void set_product_quantity(int code, int quantity);

/**
* Returns the stock for a certain product.
* param - product unique code
*/
int get_product_quantity(int code);

/**
* Request for a product.
*
* Returns specific error codes regarding following situations:
* 	-1 -- the request regards a products that doesn't exist(wrong product code);
* 	-2 -- the requested product is not available (stock = 0);
* 	-3 -- clients credit is not enough to buy the product;
* 	-4 -- the rest of the money can not be paid with available bills.
*  If none of the above situations is present, this method will
* return the amount representing the rest of the money that will be
* paid to the client if he decide to ask for his change(request_change method is called).
* Internally, the stocks for available bills will not be modified untill 
* request_change method is called.
* param - product code
*/
int request_product(int code);

/**
* Request for change after a purchase.
* 
* Note: this vending machine is special, because a client may choose not to request
* a withdraw for his change, he may use it for further purchasing, he may donate it or
* he may simply forget about it.
* If this method is called after the call of request_product method, the client will receive
* the rest of its money if he explicitly choosed so.
* If credit was inserted and request_product method was not called,
* this method will return the same amount that was inserted, in any
* available bills.
*
* If force_request_product method is called, it means the client does not want back his change, 
* and this method should not be called.
*/
int request_change();

/**
* Interogates the client if he wants his change to be withdraw
*/
void question_request_change();

/**
* Modifies the stock of product after a purchase
* param - new quantity to be set
*/
void shrink_quantity(int new_quantity);

/**
* Request for a product, even if change isn't available.
*/
int force_request_product();

/**
* Inserts a bill.
* (-1, if the bill could not be recognized, wrong bill type).
* param - bill type
*/
int insert_bill(bill_type bill);

/**
* Sends the ordered product specifications(code, stock, price)
* to be temporary stored in memory, so these infos may be procesed by other related functions(e.g - get_quantity).
* param - ordered product informations
*/
void send_to_cache(product_info ordered_product);

/**
* Sets the credit after bill insertion.
* param - current credit
*/
void set_credit(int credit);

/**
* Returns available credit.
*/
int get_credit();

/**
* Signals that client requests his change to be withdraw after an order.
*/
void flag_request_change();

/**
* Make an order.
*/
void order();

/**
* Checks if there are enough suited bills in stock so the rest to be paid
* param - credit
*/
int check_for_change(int credit);

/**
* Resets the vending machine, its entire state, number of products, codes, stocks, prices, etc.
* In order to do that, user will be requested to insert a PIN code(1234).
*/
void reset();

#endif

