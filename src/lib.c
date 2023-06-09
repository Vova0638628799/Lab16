/**
\file lib.c
\brief Файл з реалізацією функцій

Цей файл, містить реалізацію функцій 'check_arguments', 'check_input_data', 'write_info_error', 'create_arr_students', 'create_students', 'free_memory','generate_year','recording_info_student','read_from_file', 'search_student', 'sort_student_by_year_decreas','sort_student_by_year_increas','sort_student_by_alphabet','auto_generate_arr_student', 'write_out_file', 'write_on_screen'.
*/

#include "lib.h"

/**
 Функція check_arguments
 \param number_arguments - кількість аргументів.
 \param *arr_arguments[] - масив аргусентів.
 \return Повертає номер перевірки як що та не була пройдена або нуль як що все гаразд.
 
 
 Послідовність дій
 
- Створення змінних
	FILE *output_file - вказівник на файл для вихідних даних.
	FILE *input_file - вказівник на файл з вхідними даних.

- Перевіряємо чи були введені якісь значення, як що ні то повертаємо 1, як що було щось введено ідемо далі.

- Перевіряємо чи дійснану кількість значень ввів користувач, як що ні то повертаємо 2, як що кількість значень задовільна ідемо далі.

- Присвоємо вказівнику на наші файл та відкриваємо їх.

- Перевіряємо чи були присвоєні файли їх вказівникам, як що так тоді закриваємо їх і повертаємо 0, як що ні  повертаємо 3.

*/
unsigned int check_arguments(int number_arguments, char *arr_arguments[])
{
	FILE *output_file;
	FILE *input_file;

	if (number_arguments > 1) {
		if (number_arguments != 3)
			return 2;
		else {
			output_file = fopen(*(arr_arguments + 2), "w");
			input_file = fopen(*(arr_arguments + 1), "r");

			if (output_file == NULL || input_file == NULL)
				return 3;
			else {
				fclose(input_file);
				fclose(output_file);
				return 0;
			}
		}
	}

	return 1;
}

/**
 Функція check_input_data
 \param *res_check - масив у якому зберігаються дані про помилку.
 \param path_input_file[] - шлях до файлу у якому превіряється правильність внесення даних.
 \return Повертає масив у якому номер перевірки як що та не була пройдена та строка де помилка або нуль і кількість строк.
 
 
 Послідовність дій
 
- Створення змінних
	FILE *input_file - вказівник на файл з вхідними даних.
	unsigned int n_str - кількість студентів яку треба перевірити
	struct student_data test_stedent - структура куди будуть записуватися дані з файлу

- Перевіряємо чи була введена кількість студентів, як що ні то записуємо у `*(res_check)` 4 ,закриваємо файл та повертаємо 1, як що було введено ідемо далі.

- Перевіряємо чи дорвнює кількість студентів 0, як що так то записуємо у `*(res_check)` 5, закриваємо файл та повертаємо 1, як що було введено ідемо далі.

- Створюємо цикл який буде перебирати вказану кількість строки у файллі.

- Записуємо у масив `true_false` строку із файлу, після чого перевіряємо як що наступний знак у файлі це не пробіл і записана у масив строка це не 'так' і 'ні' то записуємо у `*(res_check)` 6 і у *(res_check + 1) номер строки, закриваємо файл, завершкємо роботу функції.

- Записуємо у масив `name_student` строку із файлу, після чого перевіряємо як що наступний знак у файлі це не пробіл  то записуємо у `*(res_check)` 7 і у *(res_check + 1) номер строки, закриваємо файл, завершкємо роботу функції.

- Записуємо у масив `name_kurator` строку із файлу, після чого перевіряємо як що наступний знак у файлі це не пробіл  то записуємо у `*(res_check)` 8 і у *(res_check + 1) номер строки, закриваємо файл, завершкємо роботу функції.

- Записуємо у масив `name_faculti` строку із файлу, після чого перевіряємо як що наступний знак у файлі це не пробіл  то записуємо у `*(res_check)` 9 і у *(res_check + 1) номер строки, закриваємо файл, завершкємо роботу функції.

- Записуємо у масив `group_code` строку із файлу, після чого перевіряємо як що наступний знак у файлі це не пробіл  то записуємо у `*(res_check)` 10 і у *(res_check + 1) номер строки, закриваємо файл, завершкємо роботу функції.

- Записуємо у масив `name_cafedra` строку із файлу, після чого перевіряємо як що наступний знак у файлі це не перехід на іншу строку і записана у масив строка це не 'ВК','ГАК','У1' і 'У2' то записуємо у `*(res_check)` 11 і у *(res_check + 1) номер строки, закриваємо файл, завершкємо роботу функції.

- Як що цикл було завершено то закриваємо файл, записуємо *(res_check + 1) кількість строк і завершуємо функцію.
*/
void check_input_data(unsigned int *res_check, char *path_input_file)
{
	FILE *input_file = fopen(path_input_file, "r");
	unsigned int n_str;
	char budget_edu[8];
	char name_student[55];
	char name_kurator[55];
	char name_faculti[15];
	char group_n[21];
	char name_building_cafedra[8];

	if (fscanf(input_file, "Кількість студентів:%d", &n_str) != 1) {
		*(res_check) = 4;
		fclose(input_file);
		return;
	} else if (n_str == 0) {
		*(res_check) = 5;
		fclose(input_file);
		return;
	}

	for (unsigned int i = 1; i <= n_str; i++) {
		fscanf(input_file, "\n%7[^;\n];", budget_edu);
		if (fgetc(input_file) != ' ' && strcmp(budget_edu, "так") != 0 && strcmp(budget_edu, "ні") != 0) {
			*(res_check) = 6;
			*(res_check + 1) = i;
			fclose(input_file);
			return;
		}

		fscanf(input_file, "%54[^;\n];", name_student);
		if (fgetc(input_file) != ' ') {
			*(res_check) = 7;
			*(res_check + 1) = i;
			fclose(input_file);
			return;
		}

		fscanf(input_file, "%54[^;\n];", name_kurator);
		if (fgetc(input_file) != ' ') {
			*(res_check) = 8;
			*(res_check + 1) = i;
			fclose(input_file);
			return;
		}

		fscanf(input_file, "%14[^;\n];", name_faculti);
		if (fgetc(input_file) != ' ') {
			*(res_check) = 9;
			*(res_check + 1) = i;
			fclose(input_file);
			return;
		}

		fscanf(input_file, "%20[^;\n];", group_n);
		if (fgetc(input_file) != ' ') {
			*(res_check) = 10;
			*(res_check + 1) = i;
			fclose(input_file);
			return;
		}

		fscanf(input_file, "%7[^;\n];", name_building_cafedra);
		if (fgetc(input_file) != '\n' || (strcmp(name_building_cafedra, "ВК") != 0 && strcmp(name_building_cafedra, "ГАК") != 0 &&
						  strcmp(name_building_cafedra, "У1") != 0 && strcmp(name_building_cafedra, "У2") != 0)) {
			*(res_check) = 11;
			*(res_check + 1) = i;
			fclose(input_file);
			return;
		}
	}
	fclose(input_file);

	*(res_check + 1) = n_str;
	return;
}

/**
Функція write_info_error
 \param *res_check - масив у якому зберігаються дані про помилку.
 
 
 Послідовність дій
 
- Перевіряємо перший елемент у масиві res_check
	1 - вивидимо повідомлення `Ви не ввели ніякі дані`  та заврешуємо програму.
	2 - вивидимо повідомлення `Ви ввели некоректну кількість даних`  та заврешуємо програму.
	3 - вивидимо повідомлення `Не можливо отримати доступ до файлу або дерикторії`  та заврешуємо програму.
	4 - вивидимо повідомлення `Ви не ввели кількість студентів`  та заврешуємо програму.
	5 - вивидимо повідомлення `Кількість студентів для сортування дорівню 0`  та заврешуємо програму.
	6 - вивидимо повідомлення `У вас помилка на строці:(№ строки), у полі форма навчання`  та заврешуємо програму.
	7 - вивидимо повідомлення `У вас помилка на строці:(№ строки), у полі ім'я студента`  та заврешуємо програму.
	8 - вивидимо повідомлення `У вас помилка на строці:(№ строки), у полі ім'я куратора`  та заврешуємо програму.
	9 - вивидимо повідомлення `У вас помилка на строці:(№ строки), у полі назва факультету`  та заврешуємо програму.
	10 - вивидимо повідомлення `У вас помилка на строці:(№ строки), у полі код групи`  та заврешуємо програму.
	11 - вивидимо повідомлення `У вас помилка на строці:(№ строки), у полі назва кафедри`  та заврешуємо програму.
	12 - вивидимо повідомлення `Для роботи програми не вистачає ресурсів комп'ютера`  та заврешуємо програму.
*/
void write_info_error(unsigned int *res_check)
{
	switch (*res_check) {
	case 1:
		printf("Ви ввели не коректні дані\n");
		break;

	case 2:
		printf("Ви ввели некоректну кількість даних\n");
		break;

	case 3:
		printf("Не можливо отримати доступ до файлу або дерикторії\n");
		break;

	case 4:
		printf("Ви не ввели кількість студентів\n\n");
		break;

	case 5:
		printf("Кількість студентів для сортування дорівню 0\n\n");
		break;

	case 6:
		printf("У вас помилка на строці:%d, у полі форма навчання\n\n", *(res_check + 1));
		break;

	case 7:
		printf("У вас помилка на строці:%d, у полі ім'я студента\n\n", *(res_check + 1));
		break;

	case 8:
		printf("У вас помилка на строці:%d, у полі ім'я куратора\n\n", *(res_check + 1));
		break;

	case 9:
		printf("У вас помилка на строці:%d, у полі назва факультету\n\n", *(res_check + 1));
		break;

	case 10:
		printf("У вас помилка на строці:%d, у полі код групи\n\n", *(res_check + 1));
		break;

	case 11:
		printf("У вас помилка на строці:%d, у полі назва корпусу кафедри\n\n", *(res_check + 1));
		break;

	case 12:
		printf("Для роботи програми не вистачає ресурсів комп'ютера\n\n");
		break;
	}
}

/**
Функція free_memory
 \param struct student_arr *arr_students - вказівник для якого була виділена пам'ять.
 
 
 Послідовність дій
 
- Створюємо цкил який буду перебирати елемнти у масиві 'arr_students->students' та звільняти пам'ять яка була для них виділена.
- Звільняємо пам'ять для масиву arr_students->students.
- Звільняємо пам'ять для масиву arr_students.
*/
void free_memory(struct student_arr *arr_students)
{
	for (unsigned int i = 0; i < arr_students->n_students; i++) {
		if ((*(arr_students->students + i))->name_student != NULL) {
			free((*(arr_students->students + i))->name_student);
			free((*(arr_students->students + i))->name_kurator);
			free((*(arr_students->students + i))->faculti_and_group->name_faculti);
			free((*(arr_students->students + i))->faculti_and_group->group_n);
		}
		free((*(arr_students->students + i))->faculti_and_group);
		free(*(arr_students->students + i));
	}

	free(arr_students->students);
	free(arr_students);
}

/**
Функція create_arr_students
 \param num_students - кількість студентів у масиві
 \return Повертає адресу на блоки пам'яті.
 
 
 Послідовність дій
 
- Виділяємо пам'ять для вказівника array стільки скільки потребуя структура student_arr.
- Перевіряємо чи була виділена пам'ять, як що ні то повертаємо значення NULL.
- Як що перевірка була пройдена то виділяємо пам'ть для поля структури students стільки скільки потребує вказівник на структуру 'student_data * num_students'.
- Перевіряємо чи була виділена пам'ять, як що ні то звільняємо пам'ять для array та повертаємо значення NULL.
- Як що перевірка була пройдена то записуємо поле array->n_students кількість студентів.
- Повертаємо адресу виділеної пам'яті.
*/
struct student_arr *create_arr_students(unsigned int num_students)
{
	struct student_arr *array = malloc(sizeof(struct student_arr));
	if (array == NULL)
		return NULL;

	array->students = malloc(num_students * sizeof(struct student_data *));
	if (array->students == NULL) {
		free(array);
		return NULL;
	}

	array->n_students = num_students;

	return array;
}

/**
Функція create_students
 \return Повертає адресу на блоки пам'яті.
 
 
 Послідовність дій
 
- Виділяємо пам'ять для вказівника student стільки скільки потребуя структура student_data.
- Перевіряємо чи була виділена пам'ять, як що ні то повертаємо значення NULL.
- Як що перевірка була пройдена то виділяємо пам'ть для поля вказівника faculti_and_group стільки скільки потребує структура struct group.
- Перевіряємо чи була виділена пам'ять, як що ні то звільняємо пам'ять для student та повертаємо значення NULL.
- Повертаємо адресу виділеної пам'яті.
*/
struct student_data *create_students()
{
	struct student_data *student = malloc(sizeof(struct student_data));
	if (student == NULL)
		return NULL;

	student->faculti_and_group = malloc(sizeof(struct group));
	if (student->faculti_and_group == NULL) {
		free(student);
		return 0;
	}

	return student;
}

/**
Функція generate_year
 \param num_students - вказивник на масив вказівників студентів.
 
 
 Послідовність дій
 
- Викликаємо функцію srand для того щоб генерувати кожного разу рандомні числа.
- Створюємо цикл який буду перебирати елементи масиву arr_students.
- Як що у маисві студентів знайшовся студент у якого рик вступу дорівнює 0 то геренуємо для нього рандомне значення у диапазоні від 2017 до 2022.
- Створюємо ще один цикл який пебератиме елменти у масиві.
- Як що у масиві студентів знайдемо студента який з тієїж шрупи що і той якому ми тільки що присвойли рік вступу то копіюємо цей рік студенту якого знайшли у другомі циклі.
*/
void generate_year(struct student_arr *arr_students)
{
	srand((unsigned int)time(NULL));
	for (unsigned int i = 0; i < arr_students->n_students; i++) {
		if ((*(arr_students->students + i))->enroll_year == 0) {
			(*(arr_students->students + i))->enroll_year = (unsigned int)rand() % 5 + 2017;

			for (unsigned int j = i; j < arr_students->n_students; j++)
				if (strcmp((*(arr_students->students + j))->faculti_and_group->group_n,
					   (*(arr_students->students + i))->faculti_and_group->group_n) == 0)
					(*(arr_students->students + j))->enroll_year = (*(arr_students->students + i))->enroll_year;
		}
	}
}

/**
Функція recording_info_student
 \param char* name_student - ім'я студента.
 \param char* name_kurator - ім'я куратора.
 \param char* name_kurator - назва факультету.
 \param char* group_n - номер групи.
 \return Повертає адресу на блоки пам'яті.
 
 
 Послідовність дій
 
- Викликаємо функцію create_students, та присвоюємо результат її роботи вказівнику.
- Перевіряємо чи була для вказівника виділена пам'ять, як що ні повертаємо NULL.
- Як що перевірка була пройдена то записуємо у поля структури student_data дані.
- Викликажмо функцію strdup яка виділить пам'ять для строки та присвоє її полю структури student_data.
- Перевіряємо чи буда виділена пам'ять, як що ні то звільняємо пам'ять для всіх вказівників для яких виділяли раніше та повертаємо NULL.
- Робимо такі дії для полей структури name_student, name_kurator,  name_faculti, group_n.
- Повертаємо адресу на блок пам'яті.
*/
struct student_data *recording_info_student(char *budget_edu, char *name_student, char *name_kurator, char *name_faculti, char *group_n,
					    char *name_building_cafedra)
{
	struct student_data *student = create_students();
	if (student == NULL)
		return NULL;

	student->enroll_year = 0;

	student->name_student = strdup(name_student);
	if (student->name_student == NULL) {
		free(student->faculti_and_group);
		free(student);
		return NULL;
	}

	student->name_kurator = strdup(name_kurator);
	if (student->name_kurator == NULL) {
		free(student->name_student);
		free(student->faculti_and_group);
		free(student);
		return NULL;
	}

	student->faculti_and_group->name_faculti = strdup(name_faculti);
	if (student->faculti_and_group->name_faculti == NULL) {
		free(student->name_student);
		free(student->name_kurator);
		free(student->faculti_and_group);
		free(student);
		return NULL;
	}

	student->faculti_and_group->group_n = strdup(group_n);
	if (student->faculti_and_group->group_n == NULL) {
		free(student->name_student);
		free(student->name_kurator);
		free(student->faculti_and_group->name_faculti);
		free(student->faculti_and_group);
		free(student);
		return NULL;
	}

	if (strcmp(budget_edu, "так") == 0)
		student->budget_edu = BUDGET_ON;
	else if (strcmp(budget_edu, "ні") == 0)
		student->budget_edu = BUDGET_OFF;
	else
		student->budget_edu = NO_INDICATE;

	if (strcmp(name_building_cafedra, "ВК") == 0)
		student->name_building_cafedra = BK;
	else if (strcmp(name_building_cafedra, "ГАК") == 0)
		student->name_building_cafedra = GAK;
	else if (strcmp(name_building_cafedra, "У1") == 0)
		student->name_building_cafedra = Y1;
	else if (strcmp(name_building_cafedra, "У2") == 0)
		student->name_building_cafedra = Y2;
	else
		student->name_building_cafedra = NO_INDICA;

	return student;
}
/**
 Функція read_from_file
 \param *path_input_file - строка із шляхом до файлу де зберігається.
 \return Повертає адресу на блоки пам'яті.
 
 Послідовність дій
 
- Створення змінних
	FILE *input_file - вказівник на файл з вхідними даних.
	int n_str - кількість строк.
	char budget_edu[8] - чи на бюджетній формі навчання чи ні.
	char name_student[55] - ім'я студента.
	char name_kurator[55] - ім'я куратора.
	char name_faculti[15] - абревіатура назви факультету.
	char group_n[21] - номер групи.
	char name_building_cafedra[8] - назва корпусу кафедри.
	

- Записуємо кількість строк у `n_str`.

- Викликаємо функцію `create_arr_students(n_str)`, та присвоюємо значення що вона повернула вказивнику arr_students.

- Перевіряємо те що вказівник зберігяє адресу на блоки пам'яті, як що ні то повертаємо NULL.

- Як що перевірка була пройдена створюємо цикл який буде перебирати вказану кількість строк у файллі та елементи у масиві arr_students.

- Записуємо дані у створені для цього масиви строк.

- Вкиликаємо функцію recording_info_student, та присвоюємо вказівнику значення що воня повернула

- Перевіряємо те що вказівник зберігяє адресу на блоки пам'яті, як що ні то звільняжмо пам'ять для вказівника arr_students та повертаємо NULL.

- Як що перевірка була пройдена то перевіряємо що записано у масиві budget_edu, і в залежності від змісту присвоюємо полю budget_edu структури student_data значення.

- Так само робимо для поля  name_building_cafedra.

- Після того як записали всі дані з файлу то закриваємо його.

- Викликаємо функцію generate_year.

- Повертаємо адресу на виділену пам'ять.
*/
struct student_arr *read_from_file(char *path_input_file)
{
	FILE *input_file = fopen(path_input_file, "r");
	unsigned int n_str;
	char budget_edu[8];
	char name_student[55];
	char name_kurator[55];
	char name_faculti[15];
	char group_n[21];
	char name_building_cafedra[8];

	fscanf(input_file, "Кількість студентів:%d", &n_str);

	struct student_arr *arr_students = create_arr_students(n_str);
	if (arr_students == NULL)
		return NULL;

	for (unsigned int i = 0; i < n_str; i++) {
		arr_students->n_students = i;

		fscanf(input_file, "\n%7[^;]; %54[^;]; %54[^;]; %14[^;]; %20[^;]; %7[^;];\n", budget_edu, name_student, name_kurator, name_faculti,
		       group_n, name_building_cafedra);

		(*(arr_students->students + i)) =
			recording_info_student(budget_edu, name_student, name_kurator, name_faculti, group_n, name_building_cafedra);
		if ((*(arr_students->students + i)) == NULL) {
			free_memory(arr_students);
			return NULL;
		}
	}
	fclose(input_file);
	arr_students->n_students++;

	generate_year(arr_students);

	return arr_students;
}

/**
 Функція search_student
 \param *student -динамічний масив у якому потрібно знати студентів за конкретним роком вступу.
 \param *enroll_year - рік вступників якого потрібно знайти.
 \param path_to_file -шлях до файлу у який потрібно записати дані.
 \return Повертає адресу на блоки пам'яті.
 
 Послідовність дій
 
- Створення змінних
	unsigned int n_students - кількість знайдених студентів.
	struct student_arr *arr_found_students - вказіник на знайдені об'єкти.

- Запускаємо цикл який знайде всі об'єкти які підходять за задиним критерієм тоб то їх поле `enroll_year` дорівню параметру enroll_year.

- Викликаємо функцію `create_arr_students(n_str)`, та присвоюємо значення що вона повернула вказивнику arr_students.

- Перевіряємо те що вказівник зберігяє адресу на блоки пам'яті, як що ні то повертаємо NULL.

- Створюємо цикл який буде перебирати вказану кількість елементів у масиві `arr_students` та `*arr_found_students`.

- Перевіряємо як що поле `enroll_year` об'єкту `(*(arr_students->students + i))` дорівнює параметру enroll_year то копіюємо адресу цього елемнту у  *(arr_found_students->students + j).

- Записуємо у вихідний файл певну строку та викликаємо функції write_out_file, write_on_screen. 

- Повертаємо адресу на виділену пам'ять.
*/
struct student_arr *search_student(struct student_arr *arr_students, unsigned int enroll_year, char *path_to_file)
{
	unsigned int n_students = 0;
	struct student_arr *arr_found_students;

	for (unsigned int i = 0; i < (arr_students->n_students); i++) {
		if ((*(arr_students->students + i))->enroll_year == enroll_year) {
			n_students++;
		}
	}

	arr_found_students = create_arr_students(n_students);
	if (arr_found_students == NULL)
		return NULL;

	for (unsigned int i = 0, j = 0; i < (arr_students->n_students); i++) {
		if ((*(arr_students->students + i))->enroll_year == enroll_year) {
			*(arr_found_students->students + j) = *(arr_students->students + i);
			j++;
		}
	}

	FILE *file = fopen(path_to_file, "w");
	fprintf(file, "Студенти які вступили у %d році\n", enroll_year);
	fclose(file);

	write_out_file(path_to_file, arr_found_students);
	write_on_screen(arr_found_students);

	return arr_found_students;
}

/**
 Функція sort_student_by_year_increas
 \param *student -динамічний масив який потрібно відсортувати.
 \param path_to_file -шлях до файлу у який потрібно записати дані.
 
 Послідовність дій
 
- Створення змінних
	int stop_sort - змінна для того щоб зупинити сортування.

- Запускаємо цикл який перебератиме всі елементи масиву крім одного.

- Запускаємо ще один цикл який перебератиме всі елементи масиву крім ще одного.

- Перевіряємо як що поле enroll_year менше ніж те ще іде у наступного елемента то міняємо їх мясцями.

- Записуємо у вихідний файл певну строку та викликаємо функції write_out_file, write_on_screen. 

- Повертаємо адресу на виділену пам'ять.
*/
void sort_student_by_year_decreas(struct student_arr *sort_arr_student, char *path_to_file)
{
	int stop_sort;

	if ((sort_arr_student->n_students) > 0) {
		for (unsigned int i = 0; i < (sort_arr_student->n_students) - 1; i++) {
			stop_sort = 0;

			for (unsigned int j = 0; j < (sort_arr_student->n_students) - i - 1; j++) {
				if ((*(sort_arr_student->students + j))->enroll_year < (*(sort_arr_student->students + j + 1))->enroll_year) {
					struct student_data *student = *(sort_arr_student->students + j);
					*(sort_arr_student->students + j) = *(sort_arr_student->students + j + 1);
					*(sort_arr_student->students + j + 1) = (student);
					stop_sort = 1;
				}
			}

			if (stop_sort == 0)
				break;
		}
	}

	FILE *file = fopen(path_to_file, "w");
	fprintf(file, "Відсортовані студенти за роком вступу від старошого до молодшого\n");
	fclose(file);

	write_out_file(path_to_file, sort_arr_student);
	write_on_screen(sort_arr_student);
}

/**
Функція sort_student_by_year_increas
 \param *student -динамічний масив який потрібно відсортувати.
 \param path_to_file -шлях до файлу у який потрібно записати дані.
 
 Послідовність дій
 
- Створення змінних
	int stop_sort - змінна для того щоб зупинити сортування.

- Запускаємо цикл який перебератиме всі елементи масиву крім одного.

- Запускаємо ще один цикл який перебератиме всі елементи масиву крім ще одного.

- Перевіряємо як що поле enroll_year більш ніж той ще іде у наступного елемента то міняємо їх мясцями.

- Записуємо у вихідний файл певну строку та викликаємо функції write_out_file, write_on_screen. 

- Повертаємо адресу на виділену пам'ять.
*/
void sort_student_by_year_increas(struct student_arr *sort_arr_student, char *path_to_file)
{
	int stop_sort;

	if ((sort_arr_student->n_students) > 0) {
		for (unsigned int i = 0; i < (sort_arr_student->n_students) - 1; i++) {
			stop_sort = 0;

			for (unsigned int j = 0; j < (sort_arr_student->n_students) - i - 1; j++) {
				if ((*(sort_arr_student->students + j))->enroll_year > (*(sort_arr_student->students + j + 1))->enroll_year) {
					struct student_data *student = *(sort_arr_student->students + j);
					*(sort_arr_student->students + j) = *(sort_arr_student->students + j + 1);
					*(sort_arr_student->students + j + 1) = (student);
					stop_sort = 1;
				}
			}

			if (stop_sort == 0)
				break;
		}
	}

	FILE *file = fopen(path_to_file, "a");
	fprintf(file, "Відсортовані студенти за роком вступу від молодшого до старошого\n");
	fclose(file);

	write_out_file(path_to_file, sort_arr_student);
	write_on_screen(sort_arr_student);
}

/**
Функція sort_student_by_alphabet
 \param *student -динамічний масив який потрібно відсортувати.
 \param path_to_file -шлях до файлу у який потрібно записати дані.
 
 Послідовність дій
 
- Створення змінних
	int stop_sort - змінна для того щоб зупинити сортування.

- Запускаємо цикл який перебератиме всі елементи масиву крім одного.

- Запускаємо ще один цикл який перебератиме всі елементи масиву крім ще одного.

- Перевіряємо як що код тексту поля name_student більш ніж той ще іде у наступного елемента то міняємо їх мясцями.

- Записуємо у вихідний файл певну строку та викликаємо функції write_out_file, write_on_screen. 

- Повертаємо адресу на виділену пам'ять.
*/
void sort_student_by_alphabet(struct student_arr *sort_arr_student, char *path_to_file)
{
	int stop_sort;

	if ((sort_arr_student->n_students) > 0) {
		for (unsigned int i = 0; i < (sort_arr_student->n_students) - 1; i++) {
			stop_sort = 0;

			for (unsigned int j = 0; j < (sort_arr_student->n_students) - i - 1; j++) {
				if (strcmp((*(sort_arr_student->students + j))->name_student, (*(sort_arr_student->students + j + 1))->name_student) >
				    0) {
					struct student_data *student = *(sort_arr_student->students + j);
					*(sort_arr_student->students + j) = *(sort_arr_student->students + j + 1);
					*(sort_arr_student->students + j + 1) = (student);
					stop_sort = 1;
				}
			}

			if (stop_sort == 0)
				break;
		}
	}

	FILE *file = fopen(path_to_file, "a");
	fprintf(file, "Відсортовані студенти за алфавітом\n");
	fclose(file);

	write_out_file(path_to_file, sort_arr_student);
	write_on_screen(sort_arr_student);
}

/**
Функція auto_generate_arr_student
 \param unsigned int n_students - кількість студентів.
 \return Повертає адресу на блоки пам'яті.
 
 Послідовність дій
 
- Створення змінних
	char name_student[55] - ім'я студента.
	char name_kurator[55] - ім'я куртора.
	char name_faculti[15] - назва факультету.
	char group_n[21] - номер групи.
	char letter_arr[] - укаїнський алфавіт.

- Викликаємо функцію `create_arr_students(n_students)`, та присвоюємо значення що вона повернула вказивнику arr_students.

- Перевіряємо те що вказівник зберігяє адресу на блоки пам'яті, як що ні то повертаємо NULL.

- Викликаємо функцію srand для того щоб генерувати кожного разу рандомні числа.

- Створюємо цикл який створить необхідну кількість елементів.

- Запускаємо цикл який обере необхідну кількість літер.

- Обираємо рандомно літеру з масиву

- Перевіряємо що обрали індекс де починається код літери

- Після чого записуємо його у зроблений для цього масив.

- Робимо такі дії для кожного поля.

- Вкиликаємо функцію recording_info_student, та присвоюємо вказівнику значення що вона повернула

- Перевіряємо те що вказівник зберігяє адресу на блоки пам'яті, як що ні то звільняжмо пам'ять для вказівника arr_students та повертаємо NULL.

- Рандомно обираємо значення для полей budget_edu та name_building_cafedra

- Чистимо масиву куди записували ранжомно обрані літери

- Викликаємо функцію generate_year

- Повертаємо адресу на виділену пам'ять.
*/
struct student_arr *auto_generate_arr_student(unsigned int n_students)
{
	char budget_edu[8] = { 0 };
	char name_student[55] = { 0 };
	char name_kurator[55] = { 0 };
	char name_faculti[15] = { 0 };
	char group_n[21] = { 0 };
	char name_building_cafedra[8] = { 0 };
	char letter_arr[] = "АаБбВвГгҐґДдЕеЄєЖжЗзИиІіЇїЙйКкЛлМмНнОоПпРрСсТтУуФфХхЦцЧчШшЩщьЮюЯя";

	struct student_arr *arr_students = create_arr_students(n_students);
	if (arr_students == NULL)
		return NULL;

	srand((unsigned int)time(NULL));

	for (unsigned int t = 0; t < n_students; t++) {
		arr_students->n_students = t;

		for (int i = 0; i < 10; i++) {
			int j = (int)(rand() % (int)strlen(letter_arr)) - 1;
			if (j % 2 != 0)
				j++;
			strncat(name_student, &letter_arr[j], 2);
		}

		for (int i = 0; i < 10; i++) {
			int j = (int)(rand() % (int)strlen(letter_arr));
			if (j % 2 != 0)
				j++;
			strncat(name_kurator, &letter_arr[j], 2);
		}

		for (int i = 0; i < 3; i++) {
			int j = (int)(rand() % (int)strlen(letter_arr));
			if (j % 2 != 0)
				j++;
			strncat(name_faculti, &letter_arr[j], 2);
		}

		for (int i = 0; i < 4; i++) {
			int j = (int)(rand() % (int)strlen(letter_arr));
			if (j % 2 != 0)
				j++;
			strncat(group_n, &letter_arr[j], 2);
		}

		int budget = rand() % 2;
		int cafedra = rand() % 4;

		if (budget == BUDGET_ON)
			strcpy(budget_edu, "так");
		else
			strcpy(budget_edu, "ні");

		if (cafedra == 0)
			strcpy(name_building_cafedra, "ВК");
		else if (cafedra == 1)
			strcpy(name_building_cafedra, "ГАК");
		else if (cafedra == 2)
			strcpy(name_building_cafedra, "У1");
		else
			strcpy(name_building_cafedra, "У2");

		(*(arr_students->students + t)) =
			recording_info_student(budget_edu, name_student, name_kurator, name_faculti, group_n, name_building_cafedra);
		if ((*(arr_students->students + t)) == NULL) {
			free_memory(arr_students);
			return NULL;
		}

		memset(name_building_cafedra, 0, 8);
		memset(budget_edu, 0, 8);
		memset(name_student, 0, 55);
		memset(name_kurator, 0, 55);
		memset(name_faculti, 0, 15);
		memset(group_n, 0, 21);
	}
	arr_students->n_students = n_students;

	generate_year(arr_students);

	return arr_students;
}

struct student_arr *delete_student(struct student_arr *arr_students, unsigned int n_student)
{
	if (n_student <= 0 || n_student > arr_students->n_students)
		return arr_students;

	struct student_arr *arr_new_students = create_arr_students((arr_students->n_students) - 1);
	if (arr_new_students == NULL) {
		free_memory(arr_students);
		return NULL;
	}

	for (unsigned int i = 0, j = 0; i < (arr_students->n_students); i++) {
		if (i != n_student - 1) {
			*(arr_new_students->students + j) = *(arr_students->students + i);
			j++;
		}
	}

	free((*(arr_students->students + n_student - 1))->name_student);
	free((*(arr_students->students + n_student - 1))->name_kurator);
	free((*(arr_students->students + n_student - 1))->faculti_and_group->name_faculti);
	free((*(arr_students->students + n_student - 1))->faculti_and_group->group_n);
	free((*(arr_students->students + n_student - 1))->faculti_and_group);
	free(*(arr_students->students + n_student - 1));
	free(arr_students->students);
	free(arr_students);

	return arr_new_students;
}

struct student_arr *add_student(struct student_arr *arr_students)
{
	char budget_edu[8];
	char name_student[55];
	char name_kurator[55];
	char name_faculti[15];
	char group_n[21];
	char name_building_cafedra[8];

	struct student_arr *arr_new_students = create_arr_students(arr_students->n_students + 1);
	if (arr_new_students == NULL) {
		free_memory(arr_students);
		return NULL;
	}

	for (unsigned int i = 0; i < arr_students->n_students; i++)
		*(arr_new_students->students + i) = *(arr_students->students + i);

	free(arr_students->students);
	free(arr_students);

	scanf("\n%7[^;]; %54[^;]; %54[^;]; %14[^;]; %20[^;]; %7[^;];", budget_edu, name_student, name_kurator, name_faculti, group_n,
	      name_building_cafedra);

	(*(arr_new_students->students + arr_new_students->n_students - 1)) =
		recording_info_student(budget_edu, name_student, name_kurator, name_faculti, group_n, name_building_cafedra);
	if ((*(arr_new_students->students + arr_new_students->n_students - 1)) == NULL) {
		arr_new_students->n_students = arr_students->n_students - 1;
		free_memory(arr_new_students);
		return NULL;
	}

	while (getchar() != '\n')
		;

	generate_year(arr_new_students);

	return arr_new_students;
}

void rewrite_input_file(char *path_output_file, struct student_arr *arr_sort_students)
{
	FILE *output_file = fopen(path_output_file, "w");

	fprintf(output_file, "Кількість студентів:%d\n", arr_sort_students->n_students);

	for (unsigned int i = 0; i < (arr_sort_students->n_students); i++) {
		if ((*(arr_sort_students->students + i))->budget_edu == BUDGET_ON)
			fprintf(output_file, "\nтак; ");
		else if ((*(arr_sort_students->students + i))->budget_edu == BUDGET_OFF)
			fprintf(output_file, "\nні; ");
		else
			fprintf(output_file, "\nне вказано; ");

		fprintf(output_file, "%s; %s; %s; %s;", (*(arr_sort_students->students + i))->name_student,
			(*(arr_sort_students->students + i))->name_kurator, (*(arr_sort_students->students + i))->faculti_and_group->name_faculti,
			(*(arr_sort_students->students + i))->faculti_and_group->group_n);

		switch ((*(arr_sort_students->students + i))->name_building_cafedra) {
		case BK:
			fprintf(output_file, " ВК\n");
			break;
		case GAK:
			fprintf(output_file, " ГАК\n");
			break;
		case Y1:
			fprintf(output_file, " У1\n");
			break;
		case Y2:
			fprintf(output_file, " У2\n");
			break;
		case NO_INDICA:
			fprintf(output_file, " не вказано\n");
			break;
		}
	}
	fclose(output_file);
}
/**
 Функція write_out_file
 \param *path_output_file - шлях до файлу у який потрібно записати дані.
 \param *student -динамічний масив де зберігаються дані для виводу.
 
 Послідовність дій
 
- Створення змінних
	FILE *output_file - вказівник на файл куди треба записати вміст масиву `*student_sort`.

- Створюємо цикл який буде перебирати вказану кількість елементів у масиві `*(arr_sort_students->students)`.

- Записуємо у файл кожний елемент у масиві `(*(arr_sort_students->students + i))`.

- Закриваємо файл.
*/
void write_out_file(char *path_output_file, struct student_arr *arr_sort_students)
{
	FILE *output_file = fopen(path_output_file, "a");

	fprintf(output_file, "Кількість студентів дорівнює %d\n", arr_sort_students->n_students);

	for (unsigned int i = 0; i < (arr_sort_students->n_students); i++) {
		if ((*(arr_sort_students->students + i))->budget_edu == BUDGET_ON)
			fprintf(output_file, "\nтак; ");
		else if ((*(arr_sort_students->students + i))->budget_edu == BUDGET_OFF)
			fprintf(output_file, "\nні; ");
		else
			fprintf(output_file, "\nне вказано; ");

		fprintf(output_file, "%s; %s; %s; %s; %d;", (*(arr_sort_students->students + i))->name_student,
			(*(arr_sort_students->students + i))->name_kurator, (*(arr_sort_students->students + i))->faculti_and_group->name_faculti,
			(*(arr_sort_students->students + i))->faculti_and_group->group_n, (*(arr_sort_students->students + i))->enroll_year);

		switch ((*(arr_sort_students->students + i))->name_building_cafedra) {
		case BK:
			fprintf(output_file, " ВК\n\n");
			break;
		case GAK:
			fprintf(output_file, " ГАК\n\n");
			break;
		case Y1:
			fprintf(output_file, " У1\n\n");
			break;
		case Y2:
			fprintf(output_file, " У2\n\n");
			break;
		case NO_INDICA:
			fprintf(output_file, " не вказано\n");
			break;
		}
	}

	fclose(output_file);
}

/**
 Функція write_on_screen
 \param *student_sort -динамічний масив де зберігаються дані для виводу на екран.
 
 Послідовність дій

- Створюємо цикл який буде перебирати вказану кількість елементів у масиві `*(arr_sort_students->students)`.

- Виводимо на екран кожний елемент у масиві `(*(arr_sort_students->students + i))`.
*/
void write_on_screen(struct student_arr *arr_sort_students)
{
	printf("Кількість студентів дорівнює %d\n", arr_sort_students->n_students);

	for (unsigned int i = 0, j = 1; i < (arr_sort_students->n_students); i++, j++) {
		if ((*(arr_sort_students->students + i))->budget_edu == BUDGET_ON)
			printf("\n%d.так; ", j);
		else if ((*(arr_sort_students->students + i))->budget_edu == BUDGET_OFF)
			printf("\n%d.ні; ", j);
		else
			printf("\n%d.не вказано; ", j);

		printf("%s; %s; %s; %s; %d;", (*(arr_sort_students->students + i))->name_student, (*(arr_sort_students->students + i))->name_kurator,
		       (*(arr_sort_students->students + i))->faculti_and_group->name_faculti,
		       (*(arr_sort_students->students + i))->faculti_and_group->group_n, (*(arr_sort_students->students + i))->enroll_year);

		switch ((*(arr_sort_students->students + i))->name_building_cafedra) {
		case BK:
			printf(" ВК\n\n");
			break;
		case GAK:
			printf(" ГАК\n\n");
			break;
		case Y1:
			printf(" У1\n\n");
			break;
		case Y2:
			printf(" У2\n\n");
			break;
		case NO_INDICA:
			printf(" не вказано\n\n");
			break;
		}
	}
}
