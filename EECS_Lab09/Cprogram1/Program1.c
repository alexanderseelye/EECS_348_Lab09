/*
 * Program1.c
 *
 *  Created on: Feb 9, 2023
 *      Author: a771s435
 */

#include <stdio.h>
#include <stdlib.h>

#define MONTHS 12

float* read_data_from(char *file_name){
	float* month_sales_data = (float*)malloc(sizeof(float) * MONTHS);
	FILE *fp = fopen(file_name, "r+");
	for(int i=0; i  < MONTHS; ++i){
		fscanf(fp, "%f\n", &month_sales_data[i]);
	}

	return month_sales_data;
}

void print_data(const char *months[], const float *sales){
	printf("Monthly sales report for 2022:\n");
	for(int i=0; i < MONTHS; ++i){
		printf("%10s $%.2f\n", months[i], sales[i]);
	}
}

void print_summary(const char *months[], const float *sales){
	printf("\nSales Summary:\n");
	float max = 0, min = 0, average = 0, total = 0;
	int max_index = 0, min_index = 0;
	for(int i=0; i < MONTHS; ++i){
		if(i == 0) min = sales[i];
		if(sales[i] < min){
			min = sales[i];
			min_index = i;
		}
		if(sales[i] > max){
			max = sales[i];
			max_index = i;
		}
		total += sales[i];
	}
	average = total/MONTHS;
	printf("Minimum Sales: $%.2f\t(%s)\n", sales[min_index], months[min_index]);
	printf("Maximum Sales: $%.2f\t(%s)\n", sales[max_index], months[max_index]);
	printf("Average Sales: $%.2f\n", average);
}

void print_moving_average(const char *months[], const float *sales){
	float average, total;
	printf("\nSix-Month Moving gAverage Report:\n");
	for(int i=0; i < 7; ++i){
		average = 0;
		total = 0;
		for(int j=i; j < i+6; ++j){
			total += sales[j];
		}
		average = total/6;
		printf("%-10s-   %-10s$%.2f\n", months[i], months[i+5], average);
	}
}

void print_sorted_sales( char *months[], float *sales){
	printf("\nSales Report (Highest to Lowest):\n");
	float back_sales[MONTHS];
	char* back_months[] = {"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};
	for(int i = 0; i < MONTHS; ++i){
		back_sales[i] = sales[i];
	}
	for(int i = 0; i < MONTHS; ++i){
		for(int j = i; j < MONTHS; ++j){
			if(back_sales[j] > back_sales[i]){
				float temp = back_sales[j];
				back_sales[j] = back_sales[i];
				back_sales[i] = temp;

				char* temp_month = back_months[j];
				back_months[j] = back_months[i];
				back_months[i] = temp_month;
			}
		}
	}
	for(int i = 0; i < MONTHS; ++i){
		printf("%-10s $%.2f\n", back_months[i], back_sales[i]);
	}
}



int main(){
	float* sales = read_data_from("data.txt");
	char *months[] = {"January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};
	print_data(months, sales);
	print_summary(months, sales);
	print_moving_average(months, sales);
	print_sorted_sales(months, sales);
	return 0;
}
