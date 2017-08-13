#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Automat.h"

int number_of_products = 0;
int credit_inserted = 0;
int flag_request = 0;
typedef struct bills_stock{
		int stock_for_1;
		int stock_for_5;
		int stock_for_10;
		int stock_for_50;
	}stock_bills;
	stock_bills bills_available;
	
product_info p;	
	
void set_number_of_products(int count){
	number_of_products = count;
}

int get_number_of_products(){
	return number_of_products;
}

void set_available_bills(bill_type bill, int count){
	if(bill == _1_DOLLAR){
		bills_available.stock_for_1 = count;
	}
	else{
		if(bill == _5_DOLLARS){
			bills_available.stock_for_5 = count;
		}
		else{
			if(bill == _10_DOLLARS){
				bills_available.stock_for_10 = count;
			}
			else{
				bills_available.stock_for_50 = count;
			}
		}
	}
}

int get_available_bills(bill_type bill){
	if(bill == 1){
		if(bills_available.stock_for_1 == 0){
			return -1;
		}
		else{
			return bills_available.stock_for_1;
		}
	}
	else{
		if(bill == 5){
			if(bills_available.stock_for_5 == 0){
				return -1;
			}
			else{
				return bills_available.stock_for_5;
			}
		}
		else{
			if(bill == 10){
				if(bills_available.stock_for_10 == 0){
					return -1;
				}
				else{
					return bills_available.stock_for_10;
				}
			}
			else{
				if(bills_available.stock_for_50 == 0){
					return -1;
				}
				else{
					return bills_available.stock_for_50;
				}
			}
		}
	}
}

void set_product_cost(int code, int cost){
	p.product_price = cost;
}

int get_product_cost(int code){
	return p.product_price;
}

void set_product_quantity(int code, int quantity){
	p.product_quantity = quantity;
}

int get_product_quantity(int code){
	return p.product_quantity;
}

int insert_bill(bill_type bill){
	switch(bill){
		case _1_DOLLAR:
			bills_available.stock_for_1 += 1;
			return 1;
		case _5_DOLLARS:
			bills_available.stock_for_5 += 1;
			return 5;
		case _10_DOLLARS:
			bills_available.stock_for_10 += 1;
			return 10;
		case _50_DOLLARS:
			bills_available.stock_for_50 += 1;
			return 50;
		case 0:
			return -1;
	}
}

void send_to_cache(product_info ordered_product){
	p=ordered_product;
}

int check_for_change(int credit){
	int rest = credit - p.product_price;
	if(rest == 0){
		return 1;
	}
	else{
		while(1){
			if(rest >= _50_DOLLARS && bills_available.stock_for_50 != 0){
				if(rest / _50_DOLLARS >= bills_available.stock_for_50){
					rest = rest - (bills_available.stock_for_50 * _50_DOLLARS);
				}
				else{
					rest = rest - ((rest/_50_DOLLARS)*_50_DOLLARS);
				}
				if(rest == 0){
					return 1;
				}
			}
			else{
				if(rest >= _10_DOLLARS && bills_available.stock_for_10 != 0){
					if(rest / _10_DOLLARS >= bills_available.stock_for_10){
						rest = rest - (bills_available.stock_for_10 * _10_DOLLARS);
					}
					else{
						rest = rest - ((rest/_10_DOLLARS)*_10_DOLLARS);
					}
					if(rest == 0){
						return 1;
					}
				}
				else{
					if(rest >= _5_DOLLARS && bills_available.stock_for_5 != 0){
						if(rest / _5_DOLLARS >= bills_available.stock_for_5){
							rest = rest - (bills_available.stock_for_5 * _5_DOLLARS);
						}
						else{
							rest = rest - ((rest/_5_DOLLARS)*_5_DOLLARS);
						}
						if(rest == 0){
							return 1;
						}
					}
					else{
						if(rest >= _1_DOLLAR && bills_available.stock_for_1 != 0){
							if(rest / _1_DOLLAR >= bills_available.stock_for_1){
								rest = rest - (bills_available.stock_for_1 * _1_DOLLAR);
							}
							else{
								rest = rest - ((rest/_1_DOLLAR)*_1_DOLLAR);
							}
							if(rest == 0){
								return 1;
							}
							else{
								return 0;
							}
						}
						else{
							return 0;
						}
					}
				}
			}
		}
	}
}

void flag_request_change(){
	flag_request = 1;
}

int request_product(int code){
	if(p.product_code != code){
		return -1;
	}
	else{
		if(p.product_quantity == 0){
			return -2;
		}
		else{
			if(credit_inserted < p.product_price){
				return -3;
			}
			else{
				if(check_for_change(credit_inserted) == 0){
					return -4;
				}
				else{
					return credit_inserted-p.product_price;
				}
			}
		}
	}
}

int request_change(){
	int rest;
	if(flag_request == 1){
		rest = credit_inserted - p.product_price;
	}
	else{
		rest = credit_inserted;
	}
	
	if(check_for_change(credit_inserted) == 0){
		printf("Nu se poate returna rest cu bancnotele disponibile.\n");
		return 0;
	}
	int shrink;
	while(1){
		if(rest >= _50_DOLLARS && bills_available.stock_for_50 != 0){
			if(rest / _50_DOLLARS >= bills_available.stock_for_50){
				rest = rest - (bills_available.stock_for_50 * _50_DOLLARS);
				bills_available.stock_for_50 = 0;
			}
			else{
				shrink = rest/_50_DOLLARS;
				rest = rest - (shrink*_50_DOLLARS);
				bills_available.stock_for_50 -= shrink;
			}
			if(rest == 0){
				return 1;
			}
		}
		else{
			if(rest >= _10_DOLLARS && bills_available.stock_for_10 != 0){
				if(rest / _10_DOLLARS >= bills_available.stock_for_10){
					rest = rest - (bills_available.stock_for_10 * _10_DOLLARS);
					bills_available.stock_for_10 = 0;
				}
				else{
					shrink = rest/_10_DOLLARS;
					rest = rest - (shrink*_10_DOLLARS);
					bills_available.stock_for_10 -= shrink;
				}
				if(rest == 0){
					return 1;
				}
			}
			else{
				if(rest >= _5_DOLLARS && bills_available.stock_for_5 != 0){
					if(rest / _5_DOLLARS >= bills_available.stock_for_5){
						rest = rest - (bills_available.stock_for_5 * _5_DOLLARS);
						bills_available.stock_for_5 = 0;
					}
					else{
						shrink = rest/_5_DOLLARS;
						rest = rest - (shrink*_5_DOLLARS);
						bills_available.stock_for_5 -= shrink;
					}
					if(rest == 0){
						return 1;
					}
				}
				else{
					if(rest >= _1_DOLLAR && bills_available.stock_for_1 != 0){
						if(rest / _1_DOLLAR >= bills_available.stock_for_1){
							rest = rest - (bills_available.stock_for_1 * _1_DOLLAR);
							bills_available.stock_for_1 = 0;
						}
						else{
							shrink = rest/_1_DOLLAR;
							rest = rest - (shrink*_1_DOLLAR);
							bills_available.stock_for_1 -= shrink;
						}
						if(rest == 0){
							return 1;
						}
						else{
							return 0;
						}
					}
					else{
						return 0;
					}
				}
			}
		}
	}	
	flag_request = 0;
	credit_inserted = 0;
}

void set_credit(int credit){
	credit_inserted = credit;
}

int get_credit(){
	return credit_inserted;
}

void shrink_quantity(int new_quantity){
	p.product_quantity = new_quantity;
}

int force_request_product(){
	char ch;
	scanf(" %ch", &ch);
	if(ch == 'y' || ch == 'Y'){	
		credit_inserted -= p.product_price;
		p.product_quantity--; 	
		return 1;					
	}
	else{
		if(ch == 'n' || ch == 'N'){
			request_change();
			return 0;
		}
		else{
			printf("Ati introdus gresit! Doriti sa comandati produsul fara returnarea restului ? y/n\n");
			force_request_product();
		}
	}
}

void reset(){ 
	printf("Enter PIN code:\n");
	int pin;
	scanf("%d", &pin);
	if(pin == 1234){
		main();
	}
	else{
		printf("Wrong PIN code !\n");
	}
}
