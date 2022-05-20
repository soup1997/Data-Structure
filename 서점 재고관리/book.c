#define _CRT_SECURE_NO_WARNINGS

//displayInventory(Inven) ���� X

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <memory.h>
#include <ctype.h>

int flag = 0, choice = 0, i = 0; // ���� �б� �������� �÷���, ���α׷� ���� choice����, ����ü �迭�� �����ϱ� ���� �ε��� ����
char file_name[20] = { 0, }; // ���� �̸�

int string_compare(char*, char*);
// ���� ������ �����ϴ� �ڷᱸ��
typedef struct books {
	char title[30]; // å �̸�
	int qty; // ��
	double price; // ����
	struct books* link;
}library;

// ���� ������ �����ϴ� �ڷᱸ��
typedef struct Inventory {
	char last_name[20]; // ��
	char first_name[20]; // �̸�
	struct books *head; // ���� ���� �ּ� ����
}theInventory;


///////////////////////////////////////////////////////////////////////////////
/////////////////////////////// ����� �߰� �Լ�///////////////////////////////

// ���Ͽ��� �о�� �����͸� �ܼ����Ḯ��Ʈ�� ����
void makeInventoryList(theInventory* Inven, char* last_name, char* first_name, char* book_title, int qty, double price) {
	library* last_book;
	library* new_book = (library*)malloc(sizeof(library));
	for (int check = 0; check < i; check++)
	{
		if (strcmp(Inven[check].last_name, last_name) == 0 && strcmp(Inven[check].first_name, first_name) == 0) // �迭�� ���ڸ��� ���� ���ڰ� �����Ѵٸ� �迭�� �Ҵ�X �� ���� ���� ����
		{
			strcpy(new_book->title, book_title);
			new_book->qty = qty;
			new_book->price = price;
			new_book->link = Inven[check].head;
			Inven[check].head = new_book;
			return;
		}
	}

	// ���� ���ڰ� �������� �ʴ´ٸ� �迭�� ���� �Ҵ��ϰ� ���� ���� ����
	strcpy(Inven[i].last_name, last_name);
	strcpy(Inven[i].first_name, first_name);
	strcpy(new_book->title, book_title);
	new_book->qty = qty;
	new_book->price = price;
	new_book->link = Inven[i].head;
	Inven[i].head = new_book;
	i++;
}

// ��������
void bubble_sort(char** title_array, int * qty_array, double * price_array, int title_cnt2)
{
	char tmp_title[30] = {0, };
	int tmp_qty = 0;
	double tmp_price = 0.0;

	for (int a = 0; a < title_cnt2; a++)
	{
		for (int b = 0; b < a; b++)
		{
			if (strcmp(title_array[b], title_array[b + 1]) > 0) // title_array[b]�� title_array[b+1]���� �۴ٸ�
			{
				strcpy(tmp_title, title_array[b]);
				tmp_qty = qty_array[b];
				tmp_price = price_array[b];

				strcpy(title_array[b], title_array[b + 1]);
				qty_array[b] = qty_array[b + 1];
				price_array[b] = price_array[b + 1];

				strcpy(title_array[b + 1], tmp_title);
				qty_array[b + 1] = tmp_qty;
				price_array[b + 1] = tmp_price;
			}
		}
	}

	for (int iteration = 0; iteration < title_cnt2; iteration++)
	{
		printf("	The title is: %s\n", title_array[iteration]);
		printf("	The qty is: %d\n", qty_array[iteration]);
		printf("	The price is: %.2lf\n", price_array[iteration]);
		printf("\n");
		printf("	------\n");
		printf("\n");
	}
}
///////////////////////////////////////////////////////////////////////////////


// ���α׷� ���� ���� ���
void greeting() {
	printf("Welome to the book store program!\n");
}

// ���Ͽ��� �о �ڷᱸ���� �Ҵ��ϴ� �Լ�
void readDatabase(theInventory* Inven) {
	char buffer[100] = { 0, }; // ���Ͽ��� ���� �� �о�������� ����
	char* ptr = NULL; // ���ڿ��� �޸��� �����ϱ� ���� ������ ����

	char temp_last_name[20] = { 0, }; // ���� �̸� �ӽ����� ����
	char temp_first_name[20] = { 0, }; // ���� �� �ӽ����� ����
	char temp_book_title[30] = { 0, }; // å ���� �ӽ����� ����
	int temp_qty = 0; // å ���� �ӽ����� ����
	double temp_price = 0.0; // å ���� �ӽ����� ����

	int cnt = 0;
	FILE* file;

	printf("Enter the name of the file: ");
	scanf("%s", file_name); // ���� �̸� �Է� �ޱ�
	file = fopen(file_name, "r"); // ���� �б��� ����

	while (file == NULL)
	{
		printf("Error: reading Database\n");
		printf("Enter the name of the file: ");
		scanf("%s", file_name); // ���� �̸� �Է� �ޱ�
		file = fopen(file_name, "r"); // ���� �б��� ����
		while (getchar() != '\n'); // �Է� ���� ����
		flag = 0;
	}

	for (int j = 0; j < 50; j++)
	{
		Inven[j].head = NULL; // ����ü �迭�� head�� ��� NULL�� �ʱ�ȭ�ϰ� ����
	}

	while (fgets(buffer, sizeof(buffer), file) != NULL) // ���� ���� �� �о����
	{
		memset(temp_last_name, '\0', sizeof(temp_last_name));
		memset(temp_first_name, '\0', sizeof(temp_first_name));
		memset(temp_book_title, '\0', sizeof(temp_book_title));

		ptr = strtok(buffer, ","); // ���ۿ��� �޾ƿ� ���� ������ �޸� �������� ���ڿ� �ڸ���

		while (ptr != NULL) // �޸� �������� ���ڿ� �ڸ��� �ݺ���
		{
			if (cnt == 0)
			{
				strcpy(temp_last_name, ptr);
			}
			else if (cnt == 1)
			{
				strcpy(temp_first_name, ptr);
			}

			else if (cnt == 2)
			{
				strcpy(temp_book_title, ptr);
			}

			else if (cnt == 3)
			{
				temp_qty = atoi(ptr);
			}

			else if (cnt == 4)
			{
				temp_price = atof(ptr);
			}

			ptr = strtok(NULL, ",");  // ���� ���ڿ��� �߶� ������ ��ȯ
			cnt++;
			if (cnt == 5) cnt = 0; // �޸� �������� ���� �Ϸ�
		}
		makeInventoryList(Inven, temp_last_name, temp_first_name, temp_book_title, temp_qty, temp_price);
	}
	flag = 1;
	fclose(file);
}

// �޴� ���
int printMenu() {
	int check = 0;
	printf("\n");
	printf("--------------------------------------\n");
	printf("Enter 0 to display the original inventory\n");
	printf("Enter 1 to display the inventory\n");
	printf("Enter 2 to display the the books by one author\n");
	printf("Enter 3 to add a book\n");
	printf("Enter 4 to chage the price on hand\n");
	printf("Enter 5 to change the qty on hand\n");
	printf("Enter 6 to view the total number of books in the inventory\n");
	printf("Enter 7 to see the total amount of the entire inventory\n");
	printf("Enter 8 to exit\n");
	printf("Enter your choice: ");

	while (scanf("%d", &choice) == 0 || choice < 0) // ������ �Է� ����
	{
		printf("Error: Invalida Choice\n");
		printf("Enter your choice: ");
		while (getchar() != '\n'); // ���� �ʱ�ȭ
	}
	return choice;
}

// �����ͺ��̽� ���
void displayOrigianlInventory(theInventory* Inven) {
	library* p = NULL;

	for (int j = 0; j < i; j++) // reverse�Լ�
	{
		p = Inven[j].head;

		printf("The author is: %s, %s\n", Inven[j].last_name, Inven[j].first_name);
		while (p != NULL) 
		{
			printf("\n");
			printf("	The title is: %s\n", p->title);
			printf("	The qty is: %d\n", p->qty);
			printf("	The price is: %.2lf\n", p->price);
			printf("\n");
			printf("	----------\n");
			printf("\n");
			p = p->link;
		}
	}
}

void displayAuthorsWork(theInventory* Inven) {
	library* ptr; // library head������ ������ ���� 
	char last_name[20] = { 0, };
	char first_name[20] = { 0, };

	int title_cnt = 0;
	int title_cnt2 = 0;

	printf("Enter the author's first name: ");
	scanf("%s", first_name);
	_strlwr(first_name);
	first_name[0] -= 32;

	printf("Enter the author's last name: ");
	scanf("%s", last_name);
	_strlwr(last_name);
	last_name[0] -= 32;

	for (int j = 0; j < i; j++) // �̹� �����ϴ� �������� Ž��
	{
		ptr = Inven[j].head;
		if (strcmp(Inven[j].last_name, last_name) == 0 && strcmp(Inven[j].first_name, first_name) == 0) // ���ڸ� ��ġ
		{
			while (ptr != NULL)
			{
				title_cnt++;
				ptr = ptr->link;
			}
			
			ptr = Inven[j].head; // ������ ���� �ʱ�ȭ
			char** title_array = (char *)malloc(sizeof(char *) * title_cnt); // ���ڿ� �迭 ����
			for (int cnt = 0; cnt < title_cnt; cnt++)
			{
				title_array[cnt] = (char*)malloc(sizeof(char) * 30); // ���ڿ��� �ִ� 30��ŭ �޾ƿ����� �����Ҵ�
			}
			
			int *qty_array = (int*)malloc(sizeof(int) * title_cnt); // ������ ������ �迭 ����
			double* price_array = (double*)malloc(sizeof(double) * title_cnt); // ������ ������ �迭 ����

			while (ptr != NULL)
			{
				title_array[title_cnt2] = ptr->title; // ���ڿ� �迭�� å ���� �Ҵ�
				qty_array[title_cnt2] = ptr->qty;
				price_array[title_cnt2] = ptr->price;
				ptr = ptr->link;
				title_cnt2++;
			}
			bubble_sort(title_array, qty_array, price_array, title_cnt2); // ��������
			return;
		}
		else
		{
			if (j == i - 1) // �ε��� ������ Ž���������� ��ġ�ϴ� ���ڸ��� ���ٸ� ���� ���
			{
				printf("Sorry, but no books by %s, %s in the inventory\n", last_name, first_name);
				return;
			}
		}
	}

}

void addBook(theInventory* Inven) {
	library* ptr = NULL;

	char first_name[20] = { 0, };
	char last_name[20] = { 0, };
	char title[30] = { 0, };
	int qty = 0;
	
	double price = 0;
	char f_price[10] = {0, }; // price�� ���ڿ��� �Է¹��� �� atof()�� �Ǽ��� �����ϱ� ���� ����
	char f_qty[10] = { 0, };// qty�� ���ڿ��� �Է¹��� �� atof()�� �Ǽ��� �����ϱ� ���� ����

	printf("Enter the author's first name: ");
	scanf("%s", first_name);
	_strlwr(first_name);
	first_name[0] -= 32; // ù��° ���� �빮�ڷ� ����

	printf("Enter the author's last name: ");
	scanf("%s", last_name);
	_strlwr(last_name);
	last_name[0] -= 32; // ù��° ���� �빮�ڷ� ����


	while (getchar() != '\n'); // �Է� ���� ����
	printf("Enter the title: ");
	scanf("%[^\n]s", title);
	_strlwr(title);
	title[0] -= 32; // ���� ù��° ���� �빮�ڷ� ����
	for (int k = 0; k < strlen(title); k++) // ���� �ڿ� ������ ���ڵ��� �빮�ڷ� �����ϴ� �ݺ���
	{
		if (isspace(title[k]) && k != 0 && k != strlen(title) - 1)
		{
			title[k + 1] -= 32;
		}
	}

	for (int j = 0; j < i; j++) // �̹� �����ϴ� �������� �˻�
	{
		ptr = Inven[j].head;
		if (strcmp(Inven[j].last_name, last_name) == 0 && strcmp(Inven[j].first_name, first_name) == 0)
		{
			while (ptr != NULL)
			{
				if (strcmp(ptr->title, title) == 0)
				{
					printf("This book is already in the Inventory and cannot be added again\n");
					return;
				}
				ptr = ptr->link;
			}
		}
	}
	
	printf("Enter the qty: ");
	scanf("%s", f_qty);
	qty = atoi(f_qty);
	while (strlen(f_qty) != 1 || qty < 0) // 0�� ���� ������ �Է� �ޱ�
	{
		printf("Invalid input for qty\n");
		printf("Enter the qty: ");
		while (getchar() != '\n'); // �Է� ���� ����
		scanf("%s", f_qty);
		qty = atoi(f_qty);
	}

	printf("Enter the price: ");
	scanf("%s", f_price);
	price = atof(f_price);
	while (strlen(f_price) != 4 || price < 0.0)
	{
		printf("Invalid input for price\n");
		printf("Enter the price: ");
		while (getchar() != '\n'); // �Է� ���� ����
		scanf("%s", f_price);
		price = atof(f_price);
	}

	makeInventoryList(Inven, last_name, first_name, title, qty, price); // �������� �ʴ� ������� �κ��丮 ������Ʈ
}

void changePrice(theInventory* Inven) {
	library* ptr = NULL; // ���� ����Ʈ�� ��带 ����Ű�� ������ ����

	char first_name[20] = { 0, };
	char last_name[20] = { 0, };
	char title[20] = { 0, };

	double price = 0;
	char f_price[10] = { 0, }; // price�� ���ڿ��� �Է¹��� �� atof()�� �Ǽ��� �����ϱ� ���� ����

	int find_title_flag = 0;
	int res;

	// ���� �۽�Ʈ ���� ������ ó��
	printf("Enter the author's first name: ");
	scanf("%s", first_name);
	_strlwr(first_name);
	first_name[0] -= 32; // ù��° ���� �빮�ڷ� ����

	// ���� ��Ʈ ���� ������ ó��
	printf("Enter the author's last name: ");
	scanf("%s", last_name);
	_strlwr(last_name);
	last_name[0] -= 32; // ù��° ���� �빮�ڷ� ����

	// �̹� �����ϴ� ���� �������� �˻�
	for (int j = 0; j < i; j++)
	{
		if (strcmp(Inven[j].last_name, last_name) == 0 && strcmp(Inven[j].first_name, first_name) == 0)
		{
			break;
		}
		else
		{
			if (j == i - 1) // �ݺ����� ������ Ž���������� ���ڰ� ���ٸ� ���� ���
			{
				printf("No such author in your database. So you cannot change the price\n");
				return;
			}
		}
	}

	// å �����ϴ��� Ž��
	for (int j = 0; j < i; j++)
	{
		ptr = Inven[j].head;
		if (strcmp(Inven[j].last_name, last_name) == 0 && strcmp(Inven[j].first_name, first_name) == 0)
		{
			while (ptr != NULL)
			{
				res = string_compare(ptr->title, title);
				if (res == 1)
				{
					find_title_flag = 1; 
				}
				ptr = ptr->link;
			}
			if (find_title_flag == 0)
			{
				printf("No book with the title %s by %s, %s in the inventory\n", title, last_name, first_name);
				return;
			}
		}
	}

	// å ���� �Է� ������ ó��
	while (getchar() != '\n'); // �Է� ���� ����
	printf("Enter the title: ");
	scanf("%[^\n]s", title); // ���� �����ؼ� �Է� �ޱ�
	title[0] -= 32; // ���� ù��° ���� �빮�ڷ� ����
	for (int k = 0; k < strlen(title); k++) // ���� ���� �ڿ� ������ ���ڵ��� �빮�ڷ� �����ϴ� �ݺ���
	{
		if (isspace(title[k]) && k != 0 && k != strlen(title) - 1)
		{
			title[k + 1] -= 32;
		}
	}

	// å ���� �Է� ������ ó��
	printf("Enter the price: ");
	scanf("%s", f_price);
	price = atof(f_price);
	while (strlen(f_price) != 4 || price < 0.0)
	{
		printf("Invalid input for price\n");
		printf("Enter the price: ");
		while (getchar() != '\n'); // �Է� ���� ����
		scanf("%s", f_price);
		price = atof(f_price);
	}

	// å ���� �����ϱ� ���� Ž��
	for (int j = 0; j < i; j++)
	{
		ptr = Inven[j].head;
		if (strcmp(Inven[j].last_name, last_name) == 0 && strcmp(Inven[j].first_name, first_name) == 0)
		{
			while (ptr != NULL)
			{
				res = string_compare(ptr->title, title);
				if (res == 1)
				{
					printf("Price will be updated from %.2lf to %.2lf", ptr->price, price);
					(* ptr).price = price;
					return;
				}
				ptr = ptr->link;
			}
		}
	}
}

void changeQty(theInventory* Inven) {
	library* ptr = NULL; // ���� ����Ʈ�� ��带 ����Ű�� ������ ����

	char first_name[20] = { 0, };
	char last_name[20] = { 0, };
	char title[30] = { 0, };
	int qty = 0;

	// ���� �۽�Ʈ ���� ������ ó��
	printf("Enter the author's first name: ");
	scanf("%s", first_name);
	_strlwr(first_name);
	first_name[0] -= 32; // ù��° ���� �빮�ڷ� ����

	// ���� ��Ʈ ���� ������ ó��
	printf("Enter the author's last name: ");
	scanf("%s", last_name);
	_strlwr(last_name);
	last_name[0] -= 32; // ù��° ���� �빮�ڷ� ����

	// �̹� �����ϴ� ���� �������� �˻�
	for (int j = 0; j < i; j++)
	{
		if (strcmp(Inven[j].last_name, last_name) == 0 && strcmp(Inven[j].first_name, first_name) == 0)
		{
			break;
		}
		else
		{
			if (j == i - 1) // �ݺ����� ������ Ž���������� ���ڰ� ���ٸ� ���� ���
			{
				printf("No such author in your database. So you cannot change the qty\n");
				return;
			}
		}
	}

	// å ���� �Է� ������ ó��
	while (getchar() != '\n'); // �Է� ���� ����
	printf("Enter the title: ");
	scanf("%[^\n]s", title); // ���� �����ؼ� �Է� �ޱ�
	title[0] -= 32; // ���� ù��° ���� �빮�ڷ� ����
	for (int k = 0; k < strlen(title); k++) // ���� ���� �ڿ� ������ ���ڵ��� �빮�ڷ� �����ϴ� �ݺ���
	{
		if (isspace(title[k]) && k != 0 && k != strlen(title) - 1)
		{
			title[k + 1] -= 32;
		}
	}

	printf("Enter the qty: ");
	while (scanf("%d", &qty) != 1 || qty < 0) // 0�� ���� ������ �Է� �ޱ�
	{
		printf("Invalid input for qty\n");
		printf("Enter the qty: ");
		while (getchar() != '\n'); // �Է� ���� ����
	}

	// å ���� �����ϱ� ���� Ž��
	for (int j = 0; j < i; j++)
	{
		ptr = Inven[j].head;
		if (strcmp(Inven[j].last_name, last_name) == 0 && strcmp(Inven[j].first_name, first_name) == 0)
		{
			while (ptr != NULL)
			{
				if (strcmp(ptr->title, title) == 0)
				{
					printf("Qty will be updated from %d to %d", ptr->qty, qty);
					ptr->qty = qty;
					return;
				}
				ptr = ptr->link;
			}
		}
	}
}

void totalQty(theInventory *Inven) {
	library* ptr = NULL;
	int total = 0;
	for (int j = 0; j < i; j++) // �����ͺ��̽� ��¹�
	{
		ptr = Inven[j].head;
		while (ptr != NULL)
		{
			total += ptr->qty;
			ptr = ptr->link;
		}
	}
	printf("The total number of books is %d\n", total);
}

void calculateTotalAmount(theInventory * Inven) {
	library* ptr = NULL;
	double total_amount = 0;
	for (int j = 0; j < i; j++) // �����ͺ��̽� ��¹�
	{
		ptr = Inven[j].head;
		while (ptr != NULL)
		{
			total_amount += (ptr->qty * ptr->price);
			ptr = ptr->link;
		}
	}
	printf("The total value of inventory is $%.2f\n", total_amount);
}

int main() {	
	theInventory Inven[50]; // ����ü ������ �迭 ����
	greeting(); // ȯ�� ���� ���

	readDatabase(Inven);

	while (flag)
	{
		choice = printMenu();
		switch (choice)
		{
		case 0:
			displayOrigianlInventory(Inven);
			break;
		case 1:
			//displayInventory(Inven);
			break;
		case 2:
			displayAuthorsWork(Inven);
			break;
		case 3:
			addBook(Inven);
			break;
		case 4:
			changePrice(Inven);
			break;
		case 5:
			changeQty(Inven);
			break;
		case 6:
			totalQty(Inven);
			break;
		case 7:
			calculateTotalAmount(Inven);
			break;
		case 8:
			printf("Thank you for using this program\n");
			flag = 0;
			break;
		default:
			printf("Invalid Choice\n");
			break;
		}
	}
	return 0;
}

int string_comapre(char* a, char* b) // ���ڿ� �� �Լ�
{
	int len_a = strlen(a);
	int len_b = strlen(b);
	int cmp_flag = 0;
	if (strlen(len_a) == strlen(len_b))
	{
		for (int check = 0; check < strlen(a); a++)
		{
			if (a[check] == b[check])
			{
				cmp_flag = 1;
			}
		}
	}
	return cmp_flag;
}