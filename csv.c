#include "csv.h"



void load_csv(const char *input_path, char ***headers, char ****data, int *rows, int *cols) {
    FILE *file = fopen(input_path, "r");
    if (!file) {
        perror("Error opening input file");
        exit(EXIT_FAILURE);
    }

    char line[MAX_LINE_LENGTH];
    *rows = 0;
    *cols = 0;

    // Dynamicky alokujeme místo pro hlavičky
    *headers = malloc(sizeof(char*) * MAX_COLUMNS);
    for (int i = 0; i < MAX_COLUMNS; i++) {
        (*headers)[i] = malloc(MAX_LINE_LENGTH * sizeof(char));
    }

    //přeskočí první řádek
    if (fgets(line, MAX_LINE_LENGTH - 1, file)) {
        int col = 0;
        char *token = strtok(line, ",\n");
        while (token) {
            strcpy((*headers)[col], token);
            token = strtok(NULL, ",\n");
            col++;
        }
        *cols = col;
    } else {
        fprintf(stderr, "Error: Empty CSV file or missing header.");
        fclose(file);
        exit(EXIT_FAILURE);
    }

    // Dynamicky alokujeme místo pro data
    *data = malloc(sizeof(char**) * MAX_ROWS);
    for (int i = 0; i < MAX_ROWS; i++) {
        (*data)[i] = malloc(sizeof(char*) * MAX_COLUMNS);
        for (int j = 0; j < MAX_COLUMNS; j++) {
            (*data)[i][j] = malloc(MAX_LINE_LENGTH * sizeof(char));
        }
    }

    // přečte zbytek dat v souboru
    while (fgets(line, sizeof(line), file)) {
        int col = 0;
        char *token = strtok(line, ",\n");
        while (token) {
            strncpy((*data)[*rows][col], token, MAX_LINE_LENGTH - 1);
            token = strtok(NULL, ",\n");
            col++;
        }
        (*rows)++;
        if (*rows >= MAX_ROWS) {
            break;
        }
    }

    fclose(file);
}
void print_csv(char **headers, char ***data, int rows, int cols) {
    printf("Soubor: input.csv, sloupce: %d, radky: %d\n", cols, rows);
}

void add_row(char **headers, char ***data, int *rows, int cols, const char *line) {
    if (*rows >= MAX_ROWS) {
        printf("Error: Cannot add more rows. Maximum rows reached.\n");
        return;
    }

    char *token = strtok((char *)line, ",\n");
    int col = 0;
    while (token && col < cols) {
        strncpy(data[*rows][col], token, MAX_LINE_LENGTH - 1);
        token = strtok(NULL, ",\n");
        col++;
    }

    if (col < cols) {
        printf("Error: Insufficient columns provided.\n");
        return;
    }

    (*rows)++;
    printf("Radek byl pridan.\n");
}

double parse_to_double(const char *value) {
    char *endptr;
    double num = strtod(value, &endptr);
    return endptr == value ? 0.0 : num;
}

double calculate_average(char ***data, int rows, int col_index) {
    double sum = 0;
    for (int i = 0; i < rows; i++) {
        sum += parse_to_double(data[i][col_index]);
    }
    return rows > 0 ? sum / rows : 0;
}

double calculate_sum(char ***data, int rows, int col_index) {
    double sum = 0;
    for (int i = 0; i < rows; i++) {
        sum += parse_to_double(data[i][col_index]);
    }
    return sum;
}

int get_column_index(char **headers, int cols, const char *name) {
    for (int i = 0; i < cols; i++) {
        if (strcmp(headers[i], name) == 0) {
            return i;
        }
    }
    return -1;
}

void add_column(char **headers, char ***data, int rows, int *cols, const char *header, const char *line) {
    if (*cols >= MAX_COLUMNS) {
        printf("Error: Cannot add more columns. Maximum columns reached.\n");
        return;
    }

    strncpy(headers[*cols], header, MAX_LINE_LENGTH - 1);

    char *token = strtok((char *)line, ",\n");
    int row = 0;
    while (token && row < rows) {
        strncpy(data[row][*cols], token, MAX_LINE_LENGTH - 1);
        token = strtok(NULL, ",\n");
        row++;
    }

    if (row < rows) {
        printf("Error: Insufficient rows provided.\n");
        return;
    }

    (*cols)++;
    printf("Sloupec %s byl pridan.\n", header);
}

void save_csv(const char *output_path, char **headers, char ***data, int rows, int cols) {
    FILE *file = fopen(output_path, "w");
    if (!file) {
        perror("Error opening output file");
        exit(EXIT_FAILURE);
    }

    // Vypíše hlavičku do uloženého souboru
    for (int j = 0; j < cols; j++) {
        fprintf(file, "%s", headers[j]);
        if (j < cols - 1) {
            fprintf(file, ",");
        }
    }
    fprintf(file, "\n");

    // Vypíše data do uloženého souboru
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            fprintf(file, "%s", data[i][j]);
            if (j < cols - 1) {
                fprintf(file, ",");
            }
        }
        fprintf(file, "\n");
    }

    fclose(file);
    printf("Ukladam databazi do souboru %s.\n", output_path);
}

void parse_arguments(int argc, char *argv[], char *input_path, char *output_path) {
    int input_provided = 0, output_provided = 0;

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "--input") == 0) {
            if (input_provided || i + 1 >= argc) {
                fprintf(stderr, "Error: Invalid or duplicate --input argument.\n");
                exit(EXIT_FAILURE);
            }
            strncpy(input_path, argv[++i], 255);
            input_provided = 1;
        } else if (strcmp(argv[i], "--output") == 0) {
            if (output_provided || i + 1 >= argc) {
                fprintf(stderr, "Error: Invalid or duplicate --output argument.\n");
                exit(EXIT_FAILURE);
            }
            strncpy(output_path, argv[++i], 255);
            output_provided = 1;
        } else {
            fprintf(stderr, "Error: Unknown argument %s.\n", argv[i]);
            exit(EXIT_FAILURE);
        }
    }

    if (!input_provided || !output_provided) {
        fprintf(stderr, "Error: Both --input and --output arguments must be provided.\n");
        exit(EXIT_FAILURE);
    }
}

double calculate_max(char ***data, int rows, int col_index) {
    double max_value = 0;
    for (int i = 0; i < rows; i++) {
        double value = parse_to_double(data[i][col_index]);
        if (value > max_value) {
            max_value = value;
        }
    }
    return max_value;
}

double calculate_min(char ***data, int rows, int col_index) {
    double min_value = __DBL_MAX__;
    for (int i = 0; i < rows; i++) {
        double value = parse_to_double(data[i][col_index]);
        if (value < min_value) {
            min_value = value;
        }
    }
    return rows > 0 ? min_value : 0;
}
