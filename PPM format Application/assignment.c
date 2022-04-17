#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable:4996)

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <malloc.h>

typedef struct read_values
{
	int row;
	int col;
	int error_flag;
	int** image;
	int** grey_image;
}val;

typedef struct min_max
{
	int min;
	int max;
}minmax;

val read_file(char*);
minmax findMaxMin(struct read_values);
val loadGreyscale(struct read_values, struct min_max);
void make_file(char*, struct read_values);

// ��� ���� �Ϸ�
void main() 
{
	char file_name[30] = { 0, };
	val main_val;
	minmax res;

	printf("Enter the file name: ");
	scanf("%s", file_name);
	main_val = read_file(file_name);

	if (main_val.error_flag)
	{
		printf("Error: Problem reading the file\n");
	}

	else
	{
		res = findMaxMin(main_val); // �ִ� �ּ� ���ϱ�
		main_val = loadGreyscale(main_val, res); // �׷��� ������ �̹���
		make_file(file_name, main_val); // �׷��̽����� �̹����� ���Ϸ� ����� �Լ�
	}
}

val read_file(char* file_name)
{
	FILE* file;
	val read_val;

	char row_col[10] = { 0, };
	int row = 0, col = 0, row_size = 0, col_size = 0;
	int i = 0, j = 0, check_data = 1;
	file = fopen(file_name, "r");

	if (file == NULL) // ������ ����X
	{
		printf("Error: Unable to open file <%s>\n", file_name);
		exit(1);
	}

	else // ������ ����
	{
		read_val.error_flag = 0;
		while (*file_name)
		{
			if (isdigit(*file_name)) // �Է¹��� ���ϸ��� ���� ã��
			{
				row_col[i] = *file_name;
				i++;
			}
			file_name++;
		}

		if (i < 5) // i�� 5�̻����� �������� �ʾҴ� == row�� col�� ������ �Ǿ����� �ʴ�.
		{
			printf("Problem reading in rows and colums\n");
			read_val.error_flag = 1;
			return read_val;
		}
	    
		else
		{
			if (strlen(row_col) == 5) // ������ ������ ���ڿ�(row_col)�� ���� �񱳸� ���� row�� col ����
			{
				col = (row_col[0] - '0') * 10;
				col += (row_col[1] - '0') * 1;

				row = (row_col[2] - '0') * 100;
				row += (row_col[3] - '0') * 10;
				row += (row_col[4] - '0') * 1;

				read_val.row = row;
				read_val.col = col;
			}

			else if (strlen(row_col) == 6) // ������ ������ ���ڿ�(row_col)�� ���� �񱳸� ���� row�� col ����
			{
				col = (row_col[0] - '0') * 100;
				col += (row_col[1] - '0') * 10;
				col += (row_col[2] - '0') * 1;

				row = (row_col[3] - '0') * 100;
				row += (row_col[4] - '0') * 10;
				row += (row_col[5] - '0') * 1;

				read_val.row = row;
				read_val.col = col;
			}

			else
			{
				read_val.row = 0;
				read_val.col = 0;
				read_val.error_flag = 1;
			}

			if (read_val.row & read_val.col)
			{
				read_val.image = (int**)malloc(sizeof(int*) * read_val.row); // �̹��� �����͸� �����ϱ� ���� 2���� �迭 �����Ҵ�
				for (int i = 0; i < read_val.row; i++)
				{
					read_val.image[i] = (int*)malloc(read_val.col * sizeof(int));
				}
				col_size = _msize(read_val.image[0]) / sizeof(int); // �� ������ ���ϱ�
				row_size = _msize(read_val.image) / sizeof(int*); // �� ������ ���ϱ�

				if (row_size > read_val.row || col_size > read_val.col)
				{
					printf("Error: Too many data points\n");
					read_val.error_flag = 1;
				}

				else
				{
					for (int i = 0; i < read_val.row; i++)
					{
						for (int j = 0; j < read_val.col; j++)
						{
							check_data = fscanf(file, "%d", &read_val.image[i][j]); // ���������ϰ� int�� �о�鿩 ������

							if (check_data == 0) // non integer value
							{
								printf("Error: Read a non-integer value\n");
								read_val.error_flag = 1;
								break;
							}
							else if (check_data == -1) // EOF
							{
								printf("Error: End of file reached prior to getting all the required data\n");
								read_val.error_flag = 1;
								break;
							}
						}
						if (read_val.error_flag)
						{
							break;
						}
					}
				}
			}
		}
		fclose(file);
	}
	return read_val;
}

minmax findMaxMin(struct read_values rv)
{
	minmax mm;
	mm.min = rv.image[0][0];
	mm.max = rv.image[0][0];

	for (int i = 0; i < rv.row; i++)
	{
		for (int j = 0; j < rv.col; j++)
		{
			if (mm.max <= rv.image[i][j])
			{
				mm.max = rv.image[i][j]; // �ִ밪 ����
			}

			else
			{
				mm.min = rv.image[i][j]; // �ּҰ� ����
			}
		}
	}
	return mm;
}

val loadGreyscale(struct read_values rv, struct min_max mm)
{
	rv.grey_image = (int**)malloc(sizeof(int*) * rv.row);

	for (int i = 0; i < rv.row; i++)
	{
		rv.grey_image[i] = (int*)malloc(sizeof(int) * 3 * rv.col); // RGB 3ä���̹Ƿ� �Է¹��� ���� 3�� ���� 
	}

	for (int i = 0; i < rv.row; i++)
	{
		for (int j = 0; j < rv.col; j++)
		{
			for (int k = 3 * j; k < (3 * j) + 3; k++)
			{
				rv.grey_image[i][k] = (int)((((float)rv.image[i][j] - (float)mm.min) / ((float)mm.max - (float)mm.min)) * 255.0); 
			}
		}
	}
	return rv;
}

void make_file(char* file_name, struct read_values rv)
{
	FILE* result_file;
	strcat(file_name, ".ppm");
	result_file = fopen(file_name, "w");

	if (result_file == NULL)
	{
		printf("Failed to make file...\n");
	}
	else
	{
		fputs("P3\n", result_file);
		fprintf(result_file, "%d %d\n", rv.col, rv.row);
		fputs("255\n", result_file);

		for (int i = 0; i < rv.row; i++)
		{
			for (int j = 0; j < rv.col * 3; j++)
			{
				fprintf(result_file, "%d ", rv.grey_image[i][j]);
			}
			fprintf(result_file, "\n");
		}
		fclose(result_file);
	}
}