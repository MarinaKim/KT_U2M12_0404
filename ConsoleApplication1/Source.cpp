/*стандартые ф-ции ввода-вывода
fprintf (куда записываем, шаблон, что)
fscanf (от куда считываем,шаблон, что)
fgets
fgets_s \считывает до пробела
fputs


stdin
stdout

fgets (откуда, что, куда)

fread (*buffer (указатель память куда считать данные), толщина (size_t), FILE (от куда считать))
возвращает кол-во символов

fwrite

*/

#include<stdint.h>
#include <iostream>
#include<stdlib.h>
#include <time.h>
#include<string.h>
#include"Header.h"

using namespace std;

void main()
{
	setlocale(LC_ALL, "Rus");
	srand(time(NULL));

	int n;
	do
	{
		printf("Введите номер задания: ");
		scanf("%d", &n);
		cin.get();
		switch (n) {
		case 1: {
			FILE *pf = NULL;
			char s[80];
			int t;
			if ((pf = fopen("test.txt", "w")) == NULL)
			{
				printf("Ошибка открытия файла \n");
				exit(1);
			}
			else
			{
				//читать с клавиатуры
				printf("Введите строку и число:");
				fscanf(stdin, "%s - %d", s, &t);
				//запись в файл

				fprintf(pf, "# %d. %s", t, s);

				fclose(pf);
				/*if (fclose(pf) == 0)
				{
					printf("файл закрыт успешно");
				}
				else
				{
					printf("Ошибка закрытия потока");
					exit(1);
				}*/
			}

			if ((pf = fopen("test.txt", "r")) == NULL)
			{
				printf("Ошибка открытия файла \n");
				exit(1);
			}
			char name[80];
			int i = 0;
			//читает с файла
			fscanf(pf, "# %d. %s", &i, name);
			fprintf(stdout, "# %d. %s\n", i, name);
		}break;

		case 2: {
			FILE *file;
			char words[40];
			if ((file = fopen("file.txt", "a+")) == NULL)
			{
				fprintf(stdout, "не удалось открыть файл\n");
				exit(1);
			}
			else
			{//cout or printf
				puts("введите слова.нажмите Enter");
				puts(" в начале строки для завершения программы");

				//cin.getLine
				while (gets_s(words) != NULL && words[0] != '\0')
				{
					fprintf(file, "%s", words);
				}
				puts("Содержимое файла: ");
				// вернет указатель в начало файла
				rewind(file);

				while (fscanf(file, "%s", words) == 1)
				{
					puts(words);
				}

				if (fclose(file) != 0)
					fprintf(stderr, "Ошибка при закрытии файла \n");
			}
		}break;

		case 3: {
			FILE *getsputs;

			// когда не знаешь длину строки файла
			char buffer[10];
			char *input = NULL;
			int t = 0;
			size_t curlen = 0;
			while (fgets(buffer, sizeof(buffer), stdin) != 0)
			{
				size_t bufLen = strlen(buffer);
				char *extra = (char*)realloc(input, bufLen + curlen + 1); //растянет указатель input  до 10

				if (extra == NULL)
					break;
				input = extra;
				strcpy(input + curlen, buffer); //copy from buffer to input
				curlen += bufLen;

				t++;
				if (t > 3)
					break;
			}
			printf("%s [%d]", input, (int)strlen(input));
			free(input); //очищаем память после realloc
		}break;

		case 4: {
			FILE *file;
			double d = 12.23, newD;
			int i = 101, newI;
			long l = 12233445L, newL;

			if ((file = fopen("fReadFile", "wb+")) == NULL)
			{
				printf(" ERROR\n");
			}
			else
			{
				fwrite(&d, sizeof(double), 1, file);
				fwrite(&i, sizeof(int), 1, file);
				fwrite(&l, sizeof(long), 1, file);

				rewind(file);

				fread(&newD, sizeof(double), 1, file);
				fread(&newI, sizeof(int), 1, file);

				fread(&newL, sizeof(long), 1, file);

				printf("%lf - %ld - %d \n\n", newD, newL, newI);
				fclose(file);
			}
		}break;
			//1.	Дан файл, содержащий различные даты. Каждая дата - это число, месяц и год. Найти самую раннюю дату.
		case 5: {
			int count = 1 + rand() % 10;
			int minY = 2018, minM = 12, minD = 30;
			FILE *datess;
			spisok *datest = NULL;
			spisok *Newdatest = NULL;
			datest = (spisok*)malloc(count * sizeof(spisok));
			if (datest != 0)
			{
				for (int i = 0;i < count;i++)
				{
					(datest + i)->dates = (date*)malloc(12 * sizeof(date));
					generateDate((datest + i)->dates);
					printf("# %d \t %d.%d.%d\t\n", i + 1, (datest + i)->dates->day, (datest + i)->dates->month, (datest + i)->dates->year);
				}
			}

			if ((datess = fopen("dates.txt", "w")) == NULL)
			{
				fprintf(stdout, "не удалось открыть файл\n");
				exit(1);
			}
			else
			{

				for (int i = 0;i < count;i++)
				{
					fprintf(datess, "%d.%d.%d\n", (datest + i)->dates->day, (datest + i)->dates->month, (datest + i)->dates->year);

					fscanf(datess, "%d.%d.%d", (datest + i)->dates->day, (datest + i)->dates->month, (datest + i)->dates->year);
					if (((datest + i)->dates->year) < minY)
					{
						minY = (datest + i)->dates->year;
						if (((datest + i)->dates->month) < minM)
						{
							minM = (datest + i)->dates->month;
							if (((datest + i)->dates->day) < minD)
							{
								minD = (datest + i)->dates->day;
							}
						}
					}

				}
				fprintf(stdout, "самая раняя дата: %d.%d.%d\n", datest ->dates->day, datest ->dates->month, datest ->dates->year);

			}
			fclose(datess);
		}break;

			//8.	Файл состоит из k компонент структуры, где каждая компонента содержит две матрицы: первая размерности m x n,
			//вторая размерности m x l. Получить k произведений соответствующих матриц и записать их во второй файл. 
			//Вывести на экран содержимое первого и второго файлов.
			//ДОДЕЛАТЬ
		case 6: {
			k ks[10];
			FILE *file;
			FILE *file1;
			int m, n,l,r=0;
			printf("Введите количество столбцов m:");
			scanf("%d", &m);
			printf("Введите количество строк n:");
			scanf("%d", &n);
			printf("Введите количество строк l:");
			scanf("%d", &l);
			for (int i = 0;i < 10;i++)
			{
				ks[i].matr = (int*)malloc(m*n * sizeof(int));
				for (int j = 0;j < m*n;j++)
				{
					ks[i].matr[j] = 1 + rand() % 50;
				}
				ks[i].matr1 = (double*)malloc(m*l * sizeof(double));
				for (int j = 0;j < m*n;j++)
				{
					ks[i].matr1[j] = 1.5 + rand() % 50 / 1.1 + rand() % 50;
				}
			}

				if ((file = fopen("file8.txt", "w")) != NULL)
				{
					for (int d = 0;d < 10;d++)
					{
						for (int i = 0;i < m*n;i++)
						{
							if (r== n)
							{
								fprintf(file, "%d\n", ks[d].matr[i]);
								r=0;
							}
							else
							{
								fprintf(file, "%d\t", ks[d].matr[i]);
								r++;
							}
						}
						fprintf(file, "-------------------------------------------\n");
					}
					fprintf(file, "-------------------------------------------\n");
									
					r = 0;
					for (int d = 0;d < 10;d++)
					{
						for (int i = 0;i < m*l;i++)
						{
							if (r == l)
							{
								fprintf(file, "%2.2lf\n", ks[d].matr1[i]);
								r = 0;
							}
							else
							{
								fprintf(file, "%2.2lf\t", ks[d].matr1[i]);
								r++;
							}
						}
						fprintf(file, "-------------------------------------------\n");
					}

				}
						
			fclose(file);

			/*if ((file1 = fopen("file8_1.txt", "wb")) != NULL)
			{
				for (int i = 0;i < 10;i++)
				{
					fwrite((ks + i), sizeof(k), 1, file1);
				}
			}*/

		}break;
/*10.	Создать бинарный файл со списком о студентах: 
a.	 фамилия и инициалы студентов;
b.	 номер группы; 
c.	 успеваемость (массив из трех дисциплин по 100-бальной системе); 
d.	 размер стипендии. 
e.	Вывести список студентов, имеющих по всем предметам положительные оценки и распечатать все сведения о них.
*/
		case 7: {
			struct stud
			{
				char name[30];
				char number[5];
				int usp[3];
				double step;
			};
			stud students;
			FILE *file;
			int count;
			printf("Введите количество студентов:");
			scanf("%d", &count);
			cin.get();

			for (int i = 0;i < count;i++)
			{
				printf(" введите имя студента: ");
				scanf("%s", students.name);
				printf(" введите группу студента: ");
				scanf("%s", students.number);
				printf(" введите оценки студента: ");
				scanf("%d %d %d", &students.usp[0], &students.usp[1], &students.usp[2]);
				printf(" введите стипендию студента: ");
				scanf("%lf", &students.step);
			}


			/*strcpy(students[0].name, "Ivanov R.B.");
			strcpy(students[0].number, "SMB-222");
			students[0].usp[0] = 10;
			students[0].usp[1] = 20;
			students[0].usp[2] = 30;
			students[0].step = 10000.00;

			strcpy(students[1].name, "Petrov K.M.");
			strcpy(students[1].number, "SMB-222");
			students[1].usp[0] = 10;
			students[1].usp[1] = 20;
			students[1].usp[2] = 30;
			students[1].step = 1000.00;*/
			/*//dc/Студенты/ПКО/SMB-172.1/Общее/Файлы/students.dat*/
			if ((file = fopen("students111.txt", "ab+")) != NULL)
			{
				for (int i = 0;i < count;i++)
				{
					fwrite(&students, sizeof(stud), 1, file);
					fprintf(file, "\n");
				}
			}
			fclose(file);

			stud st1;
			if ((file = fopen("students111.txt", "rb")) != NULL)
			{
				while (fread(&st1, sizeof(stud), 1, file))
					{
						printf("%s \t %s usp: \n%d\n%d\n%d \n step: %lf\n ", st1.name, st1.number, st1.usp[0], st1.usp[1], st1.usp[2], st1.step);
					}				
			}
			fclose(file);
			
		}break;
		}
	} while (n > 0);
}