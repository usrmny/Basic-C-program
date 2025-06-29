#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Student
{
	float gpa;
	char* name;

};

int main() {
	unsigned char input;
	unsigned short count = 0;
	char nameBuf[100];
	char gpaBuf[10];
	struct Student* students = NULL;
//	struct Student* students = malloc(count * sizeof(struct Student));

	do {
		printf("Pick from the following: \n" 
				"\t1 - Enter a new student\n"
				"\t2 - Remove a student\n"
				"\t3 - List students\n"
				"\t4 - Exit\n");
		scanf_s(" %c", &input, 1);
		(void)getchar();

		switch (input) {
		case '1':
			count++;
			struct Student* temp = realloc(students, count * sizeof(struct Student));
			if (!temp) {
				printf("Temp realloc failed.");
				return 1;
			}
			students = temp;

			printf("Enter the student's name: \n");
			fgets(nameBuf, sizeof(nameBuf), stdin);
			nameBuf[strcspn(nameBuf, "\n")] = 0; // remove newline
			students[count - 1].name = malloc(strlen(nameBuf) + 1);
			strcpy_s(students[count - 1].name, strlen(nameBuf) + 1, nameBuf);

			printf("Enter the student's GPA: \n");
			fgets(gpaBuf, sizeof(gpaBuf), stdin); 
			sscanf_s(gpaBuf,"%f", &students[count-1].gpa);

			break;
		case '2': {
			int index;
			printf("Enter the index you which to remove (0 to %d):\n", count - 1);
			scanf_s("%d", &index);
			(void) getchar();


			if (index >= 0 && index < count) {
				if (count > 1) {
					free(students[index].name);
					for (int i = index; i < count - 1; i++) {
						students[i] = students[i + 1];
					}


					count--;
						struct Student* temp = realloc(students, count * sizeof(struct Student));

						if (!temp) {
							printf("Temp realloc failed.");
							return 1;
						}
					students = temp;
				}
				else if (count == 1) {
					count--;
					free(students);
					students = NULL;
				}
			}
			else {
				printf("invalid index\n");
			}

			break;
		}
			
		case '3':
			for (int i = 0; i < count; i++) {
				printf("%s - %.2f\n",students[i].name, students[i].gpa);
			}
			break;
		}

	} while (input != '4');

	return 0;
}