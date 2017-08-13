#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Automat.h"

int credit = 0;
int length;
product_info* product;
int result_request_product;
int code_order;
int flag_no_bills_4_rest = 0;

void insert_credit(){
		while(1){
			printf("Creditul dvs e de %d $\nIntroduceti bancnota de 1, 5, 10, sau 50 $ sau apasati 9 pt a comanda:\n", credit);
			int money;
			scanf("%d", &money);
			if(money == 9){
				break;
			}
			else{
				switch(money){
					case 1:
						credit += insert_bill(_1_DOLLAR);
						break;
					case 5:
						credit += insert_bill(_5_DOLLARS);
						break;
					case 10:
						credit += insert_bill(_10_DOLLARS);
						break;
					case 50:
						credit += insert_bill(_50_DOLLARS);
						break;
					default:
						printf("Bancnota ilizibila.Introduceti alta bancnota de 1, 5, 10 sau 50 $:\n");
						insert_bill(0);
				}
			}
		}
	//	printf("Creditul dvs este de : %d $\n", credit);
		set_credit(credit);
		credit = get_credit();
	}


void question_request_change(){
	printf("Doriti sa vi se returneze restul de %d $ ? y/n \n", result_request_product);
	char ch;
	scanf(" %ch", &ch);
	if(ch == 'y' || ch == 'Y'){								
		flag_request_change();
		request_change();
		credit = 0;
		set_credit(credit);
	}
	else{
		if(ch == 'n' || ch == 'N'){
			credit = credit - get_product_cost(code_order);
			set_credit(credit);
		}
		else{
			printf("Ati introdus gresit!\n");
			question_request_change();
		}
	}
}


void order(){
	int i;
	while(1){
		credit = get_credit();
		printf("Creditul dvs este de : %d $\n", credit);
		printf("Introduceti codul produsului dorit sau apasati 9 pt returnarea creditului sau apasati 10 pt resetare aparat:\n");
		scanf("%d", &code_order);
		if(code_order == 10){
			reset();
		}
		else{	
			if(code_order == 9){
				if(flag_no_bills_4_rest == 1){
					printf("Nu se poate returna creditul cu bancnotele disponibile dar puteti comanda un alt produs.\n");
					break;
				}
				else{
					request_change();
					credit = 0;
					insert_credit();
					break;
				}
			}
			else{
				for(i=0; i<length; i++){
					if(product[i].product_code == code_order){
						send_to_cache(product[i]);
					}
				}
				result_request_product = request_product(code_order);
				//printf("%d\n", request_product(code_order));
				if(result_request_product == -1){
					printf("Cod produs incorect !\n");
				}
				else{
					if(result_request_product == -2){
						printf("Produsul comandat nu mai este pe stoc.\n");
					}
					else{
						if(result_request_product == -3){
							printf("Credit insuficient.\n");
							insert_credit();
							set_credit(credit);
							credit = get_credit();
						//	printf("creditul : %d", credit );
						}
						else{
							if(result_request_product == -4){
								printf("Imposibil de returnat rest cu bancnotele disponibile!Doriti sa comandati produsul fara returnarea restului ? y/n\n");
								if(force_request_product(code_order) == 0){
									flag_no_bills_4_rest = 0;
								}
								else{
									flag_no_bills_4_rest = 1;
								}
							}
							else{
								flag_no_bills_4_rest = 0;
								int flag_no_rest = 0;
								for(i=0; i<length; i++){
									if(product[i].product_code == code_order){
										product[i].product_quantity--;
										shrink_quantity(product[i].product_quantity);
										if((credit - product[i].product_price) == 0){
											flag_no_rest = 1;
										}
									}
								}
								if(flag_no_rest == 1){
									credit = 0;
									set_credit(credit);
								}
								else{
									question_request_change();
								}
							}
						}
					}
				}
			}
		}
	}
}

int main() {
  	int produse,i,j;
  	printf("Configurati numarul de produse disponibile in automat:\n");
  	scanf("%d", &produse);
	while(produse <= 0 || produse > MAX_NUMBER_OF_PRODUCTS){
		printf("Numarul de produse disponibile in automat trebuie sa fie mai mare ca 0 si sa nu depaseasca 100!\nVa rugam setati din nou numarul de produse disponibile in automat:\n");		
		scanf("%d", &produse);
	}
  	set_number_of_products(produse);
	printf("Sunt %d produse disponibile.\n", get_number_of_products());
	printf("Aparatul foloseste doar bancnote de 1, 5, 10 si 50 de dolari.\n");
	for(i=0; i<4; i++){
		if(i==0){
				j=1;
			}
		else{
			if(i==1){
				j=5;
			}
			else{
				if(i==2){
					j=10;
				}
				else{
					j=50;
				}
			}
		}
		printf("Setati numarul de bancnote de %d $ disponibile in aparat:\n", j);
		int k;
		scanf("%d", &k);
		while(k<0 || k>500){
			printf("Numarul de bancnote de %d nu poate fi mai mic ca 0 sau mai mare ca 500!\nVa rugam incercati din nou.\n", j);		
			scanf("%d", &k);
		}
		if(j==1){
			bill_type bill = _1_DOLLAR;
			set_available_bills(bill, k);
		}
		else{
			if(j==5){
				bill_type bill = _5_DOLLARS;
				set_available_bills(bill, k);
			}
			else{
				if(j==10){
					bill_type bill = _10_DOLLARS;
					set_available_bills(bill, k);
				}
				else{
					bill_type bill = _50_DOLLARS;
					set_available_bills(bill, k);
				}
			}
		}
	}
//	printf(" Stocul de bancnote de 1 $ pt rest : %d\n", get_available_bills(_1_DOLLAR));
//	printf(" Stocul de bancnote de 5 $ pt rest : %d\n", get_available_bills(_5_DOLLARS));
//	printf(" Stocul de bancnote de 10 $ pt rest : %d\n", get_available_bills(_10_DOLLARS));
//	printf(" Stocul de bancnote de 50 $ pt rest : %d\n", get_available_bills(_50_DOLLARS));
	
	length = get_number_of_products();
	product = (product_info*)malloc(length*sizeof(product_info)); 
	int a=101;
	for(i=0; i< length; i++){
		product[i].product_code = a++;
		//printf("Produs cod : %d\n", product[i].product_code);
	}
 	int price[length];
 	int quantity[length];
 	
 	for(i=0; i<length; i++){
 		price[i] = rand() % 20;
 		quantity[i] = rand() % 50;
 		if(price[i] == 0){
 			price[i] = 2;
		 }
 		//printf("%d ", price[i]);
	 }
	for(i=0; i<length; i++){
		set_product_cost(product[i].product_code, price[i]);
		set_product_quantity(product[i].product_code, quantity[i]);
		product[i].product_price = get_product_cost(product[i].product_code);
		product[i].product_quantity=get_product_quantity(product[i].product_code);
	}
	for(i=0; i<length; i++){
		printf("cod: %d pret: %d cantitate: %d\n", product[i].product_code, product[i].product_price, product[i].product_quantity);
	}
	
	insert_credit();
	
	while(1){
		order();
	}
	
	return 0;
}
