
#ifndef PROJEKT_CSV_H
#define PROJEKT_CSV_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_LINE_LENGTH 256
#define MAX_COLUMNS 32
#define MAX_ROWS 32

void load_csv(const char *input_path, char ***headers, char ****data, int *rows, int *cols);
void print_csv(char **headers, char ***data, int rows, int cols);
void add_row(char **headers, char ***data, int *rows, int cols, const char *line);
double parse_to_double(const char *value);
double calculate_average(char ***data, int rows, int col_index);
double calculate_sum(char ***data, int rows, int col_index);
double calculate_max(char ***data, int rows, int col_index);
double calculate_min(char ***data, int rows, int col_index);
int get_column_index(char **headers, int cols, const char *name);
void add_column(char **headers, char ***data, int rows, int *cols, const char *header, const char *line);
void save_csv(const char *output_path, char **headers, char ***data, int rows, int cols);
void parse_arguments(int argc, char *argv[], char *input_path, char *output_path);


#endif //PROJEKT_CSV_H
