#include "csv.h"


int main(int argc, char *argv[]) {
    char input_path[256], output_path[256];
    char **headers;
    char ***data;
    int rows, cols;

    parse_arguments(argc, argv, input_path, output_path);
    load_csv(input_path, &headers, &data, &rows, &cols);

    printf("Soubor: %s, sloupce: %d, radky: %d\n", input_path, cols, rows);

    char command[MAX_LINE_LENGTH];
    while (1) {
        printf("Zadejte prikaz: ");
        fgets(command, sizeof(command), stdin);
        command[strcspn(command, "\n")] = '\0';

        if (strncmp(command, "addrow", 6) == 0) {
            char *row_data = command + 7;
            add_row(headers, data, &rows, cols, row_data);
        } else if (strncmp(command, "average", 7) == 0) {
            char *column_name = command + 8;
            int col_index = get_column_index(headers, cols, column_name);
            if (col_index != -1) {
                double avg = calculate_average(data, rows, col_index);
                printf("Prumer sloupce %s: %.1f\n", column_name, avg);
            } else {
                printf("Sloupec `%s` nebyl nalezen.\n", column_name);
            }
        } else if (strncmp(command, "sum", 3) == 0) {
            char *column_name = command + 4;
            int col_index = get_column_index(headers, cols, column_name);
            if (col_index != -1) {
                double sum = calculate_sum(data, rows, col_index);
                printf("Soucet sloupce %s: %.1f\n", column_name, sum);
            } else {
                printf("Sloupec `%s` nebyl nalezen.\n", column_name);
            }
        } else if (strncmp(command, "max", 3) == 0) {
            char *column_name = command + 4;
            int col_index = get_column_index(headers, cols, column_name);
            if (col_index != -1) {
                double max_value = calculate_max(data, rows, col_index);
                printf("Maximalni hodnota ve sloupci %s: %.1f\n", column_name, max_value);
            } else {
                printf("Sloupec `%s` nebyl nalezen.\n", column_name);
            }
         } else if (strncmp(command, "min", 3) == 0) {
            char *column_name = command + 4;
            int col_index = get_column_index(headers, cols, column_name);
            if (col_index != -1) {
                double min_value = calculate_min(data, rows, col_index);
                printf("Minimalni hodnota ve sloupci %s: %.1f\n", column_name, min_value);
            } else {
                printf("Sloupec `%s` nebyl nalezen.\n", column_name);
            }
        } else if (strncmp(command, "addcol", 6) == 0) {
            char *column_data = command + 7;
            char *header_end = strchr(column_data, ' ');
            if (header_end) {
                *header_end = '\0';
                add_column(headers, data, rows, &cols, column_data, header_end + 1);
            } else {
                printf("Error: Invalid column data format.\n");
            }
        } else if (strcmp(command, "exit") == 0) {
            save_csv(output_path, headers, data, rows, cols);
            break;
        } else {
            printf("Neznamy prikaz: %s\n", command);
        }
    }

    // Uvolnění alokované paměti
    for (int i = 0; i < MAX_COLUMNS; i++) {
        free(headers[i]);
    }
    free(headers);

    for (int i = 0; i < MAX_ROWS; i++) {
        for (int j = 0; j < MAX_COLUMNS; j++) {
            free(data[i][j]);
        }
        free(data[i]);
    }
    free(data);

    return 0;
}
