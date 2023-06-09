/*!
\file lib.h
\brief Бібіиотечный файл

Це файл, який містить декларацію функцій 'check_arguments', 'check_input_data', 'write_info_error', 'create_arr_students', 'create_students', 'free_memory','generate_year','recording_info_student','read_from_file', 'search_student', 'sort_student_by_year_decreas','sort_student_by_year_increas','sort_student_by_alphabet','auto_generate_arr_student', 'write_out_file', 'write_on_screen', ініціалізацію структур 'group', 'student_data', 'student_arr' та ініціалізацію 'enum cafedra'.
*/

#pragma once

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#define SEARCH_STUDENTS 1
#define SORT_STUDENTS 2
#define GENERATION_STUDENTS 3
#define WRITE_OUT_FILE 4
#define DELETE_STUDENT 5
#define ADD_STUDENT 6
#define CLOSE_PROGRAM 7

#define BUDGET_ON 1
#define BUDGET_OFF 0

#define NO_INDICATE 3

/**
Перераховуючий тип даних cafedra

- Перераховую назву кафедр  BK, GAK, Y1, Y2.
*/
enum cafedra { BK, GAK, Y1, Y2 ,NO_INDICA};
/**
Структура group
 	char *name_faculti - масив у якому зберігається назва факультету.
	char *group_n -  масив у якому зберігається номер групи.
*/
struct group {
	char *name_faculti;
	char *group_n;
};

/**
Структура student_data
 	unsigned int budget_edu - зберігається відповідь на питання чи набжеті студент або ні.
	char *name_student -  масив у якому зберігається ім'я студента.
	char *name_kurator -  масив у якому зберігається ім'я куратора.
	unsigned int enroll_year - рік у якому поступив студент.
	struct group *faculti_and_group - об'єкт типу структури group.
	enum cafedra name_building_cafedra - зберігається назва кафедри.
*/
struct student_data {
	unsigned int budget_edu;
	char *name_student;
	char *name_kurator;
	unsigned int enroll_year;
	struct group *faculti_and_group;
	enum cafedra name_building_cafedra;
};

/**
Структура student_arr
 	unsigned int n_students - кількість студентів у масиві
 	struct student_data **students - масив вказівників на об'єкти структури student_data
*/
struct student_arr {
	unsigned int n_students;
	struct student_data **students;
};

/**
Функція check_arguments
 \param number_arguments - кількість аргументів.
 \param *arr_arguments[] - масив аргусентів.
 \return Повертає номер перевірки як що та не була пройдена або нуль як що все гаразд.
*/
unsigned int check_arguments(int number_arguments, char *arr_arguments[]);

/**
Функція check_input_data
 \param *res_check - масив у якому зберігаються дані про помилку.
 \param path_input_file[] - шлях до файлу у якому превіряється правильність внесення даних.
 \return Повертає масив у якому номер перевірки як що та не була пройдена та строка де помилка або нуль і кількість строк.
*/
void check_input_data(unsigned int *res_check, char *path_input_file);

/**
Функція write_info_error
 \param *res_check - масив у якому зберігаються дані про помилку.
*/
void write_info_error(unsigned int *res_check);

/**
Функція create_arr_students
 \param num_students - кількість студентів у масиві
 \return Повертає адресу на блоки пам'яті.
*/
struct student_arr *create_arr_students(unsigned int num_students);

/**
Функція create_students
 \return Повертає адресу на блоки пам'яті.
*/
struct student_data *create_students();

/**
Функція generate_year
 \param num_students - вказивник на масив вказівників студентів.
*/
void generate_year(struct student_arr *arr_students);

/**
Функція free_memory
 \param struct student_arr *arr_students - вказівник для якого була виділена пам'ять.
 */
void free_memory(struct student_arr *arr_students);

/**
Функція read_from_file
 \param *path_input_file - строка із шляхом до файлу де зберігається.
 \return Повертає адресу на блоки пам'яті.
*/
struct student_arr *read_from_file(char *path_input_file);

/**
Функція search_student
 \param *student -динамічний масив у якому потрібно знати студентів за конкретним роком вступу.
 \param *enroll_year - рік вступників якого потрібно знайти.
 \param path_to_file -шлях до файлу у який потрібно записати дані.
 \return Повертає адресу на блоки пам'яті.
*/
struct student_arr *search_student(struct student_arr *student, unsigned int enroll_year, char *path_to_file);

/**
Функція sort_student_by_year_increas
 \param *student -динамічний масив який потрібно відсортувати.
 \param path_to_file -шлях до файлу у який потрібно записати дані.
*/
void sort_student_by_year_increas(struct student_arr *sort_arr_student, char *path_to_file);

/**
Функція sort_student_by_year_decreas
 \param *student -динамічний масив який потрібно відсортувати.
 \param path_to_file -шлях до файлу у який потрібно записати дані.
*/
void sort_student_by_year_decreas(struct student_arr *sort_arr_student, char *path_to_file);

/**
Функція sort_student_by_alphabet
 \param *student -динамічний масив який потрібно відсортувати.
 \param path_to_file -шлях до файлу у який потрібно записати дані.
*/
void sort_student_by_alphabet(struct student_arr *sort_arr_student, char *path_to_file);

/**
Функція recording_info_student
 \param char* name_student - ім'я студента.
 \param char* name_kurator - ім'я куратора.
 \param char* name_kurator - назва факультету.
 \param char* group_n - номер групи.
 \return Повертає адресу на блоки пам'яті.
*/
struct student_data *recording_info_student(char *budget_edu, char *name_student, char *name_kurator, char *name_faculti, char *group_n,
					    char *name_building_cafedra);

/**
Функція auto_generate_arr_student
 \param unsigned int n_students - кількість студентів.
 \return Повертає адресу на блоки пам'яті.
*/
struct student_arr *auto_generate_arr_student(unsigned int n_students);

struct student_arr *delete_student(struct student_arr *arr_students, unsigned int n_student);

struct student_arr *add_student(struct student_arr *arr_students);

void rewrite_input_file(char *path_output_file, struct student_arr *arr_students);

/**
Функція write_out_file
 \param *path_output_file - шлях до файлу у який потрібно записати дані.
 \param *student -динамічний масив де зберігаються дані для виводу.
*/
void write_out_file(char *path_output_file, struct student_arr *student);

/**
Функція write_on_screen
 \param *student_sort -динамічний масив де зберігаються дані для виводу на екран.
*/
void write_on_screen(struct student_arr *student);
