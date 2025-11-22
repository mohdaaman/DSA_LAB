/* numerology.c
 *
 * Name Numerology Analyzer
 * Language: C (C11)
 *
 * Features:
 *  - Interactive menu to add names, view results, save CSV, exit
 *  - Input validation and cleaning (keeps only A-Z letters)
 *  - Uppercase normalization
 *  - Numerology calculation (A=1..Z=26)
 *  - Reduction to single digit (preserve master numbers 11 and 22)
 *  - Dynamic array of results
 *  - Safe I/O and memory checks
 *
 * Compile: gcc -std=c11 -Wall -Wextra -O2 numerology.c -o numerology
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>

#define MAX_NAME_LEN 256        /* including terminating null */
#define INITIAL_CAPACITY 8

typedef struct {
    char original[MAX_NAME_LEN];   /* raw input (trimmed) */
    char cleaned[MAX_NAME_LEN];    /* only uppercase letters A-Z */
    int numerology;                /* raw sum A=1..Z=26 */
    int reduced;                   /* reduced number (single digit or master) */
} Person;

/* Function prototypes */
char *trim_newline_and_whitespace(char *s);
void clean_name(const char *src, char *dst);
int compute_numerology(const char *cleaned);
int reduce_number(int n);
int append_person(Person **arr, size_t *count, size_t *capacity, const Person *p);
void print_table(const Person *arr, size_t count);
int save_csv(const char *filename, const Person *arr, size_t count);
void flush_stdin_if_needed(FILE *stream, size_t read_len);

int main(void) {
    Person *people = NULL;
    size_t count = 0, capacity = 0;
    char input[MAX_NAME_LEN];
    int choice;

    /* Initialize dynamic array */
    capacity = INITIAL_CAPACITY;
    people = malloc(capacity * sizeof(Person));
    if (!people) {
        fprintf(stderr, "Error: Memory allocation failed.\n");
        return 1;
    }

    printf("=== Name Numerology Analyzer ===\n");
    for (;;) {
        printf("\nMenu:\n");
        printf("  1) Add name\n");
        printf("  2) View all results\n");
        printf("  3) Save results to CSV\n");
        printf("  4) Exit\n");
        printf("Choose an option (1-4): ");
        if (fgets(input, sizeof(input), stdin) == NULL) {
            printf("\nInput ended. Exiting.\n");
            break;
        }

        trim_newline_and_whitespace(input);
        if (strlen(input) == 0) {
            printf("No choice entered. Please type 1, 2, 3, or 4.\n");
            continue;
        }
        choice = atoi(input);

        if (choice == 1) {
            /* Add name flow */
            printf("Enter name (max %d characters): ", MAX_NAME_LEN - 1);
            if (fgets(input, sizeof(input), stdin) == NULL) {
                printf("No input. Returning to menu.\n");
                continue;
            }

            /* If input filled the buffer and last char isn't newline, there was overflow */
            size_t len = strlen(input);
            if (len > 0 && input[len - 1] != '\n') {
                /* flush remainder of line */
                flush_stdin_if_needed(stdin, len);
                printf("Warning: input exceeded %d chars - truncated.\n", MAX_NAME_LEN - 1);
            }
            trim_newline_and_whitespace(input);

            /* reject empty or only whitespace */
            int allspace = 1;
            for (size_t i = 0; i < strlen(input); ++i) {
                if (!isspace((unsigned char)input[i])) { allspace = 0; break; }
            }
            if (strlen(input) == 0 || allspace) {
                printf("Error: Name cannot be empty or only whitespace.\n");
                continue;
            }

            Person p = {0};
            strncpy(p.original, input, MAX_NAME_LEN - 1);
            p.original[MAX_NAME_LEN - 1] = '\0';

            /* Cleaning: keep only alphabetic ASCII letters and uppercase them */
            clean_name(p.original, p.cleaned);

            if (strlen(p.cleaned) == 0) {
                printf("Error: Name must contain at least one alphabetic (A-Z) character after cleaning.\n");
                continue;
            }

            p.numerology = compute_numerology(p.cleaned);
            p.reduced = reduce_number(p.numerology);

            if (append_person(&people, &count, &capacity, &p) != 0) {
                printf("Error: Could not save the entry due to memory error.\n");
                break;
            }
            printf("Added: '%s' -> cleaned: '%s' | numerology: %d | reduced: %d\n",
                p.original, p.cleaned, p.numerology, p.reduced);
        }
        else if (choice == 2) {
            /* View results */
            if (count == 0) {
                printf("No entries yet.\n");
            } else {
                print_table(people, count);
            }
        }
        else if (choice == 3) {
            if (count == 0) {
                printf("No entries to save.\n");
                continue;
            }
            printf("Enter CSV filename to save (e.g., results.csv): ");
            if (fgets(input, sizeof(input), stdin) == NULL) {
                printf("No input. Returning to menu.\n");
                continue;
            }
            trim_newline_and_whitespace(input);
            if (strlen(input) == 0) {
                printf("No filename entered. Cancelled.\n");
                continue;
            }
            if (save_csv(input, people, count) == 0) {
                printf("Saved results to %s\n", input);
            } else {
                printf("Failed to save results to %s\n", input);
            }
        }
        else if (choice == 4) {
            printf("Exiting. Goodbye!\n");
            break;
        }
        else {
            printf("Invalid choice. Enter 1–4.\n");
        }
    }

    free(people);
    return 0;
}

/* trim_newline_and_whitespace:
 * Remove trailing newline and any leading/trailing whitespace in place.
 * Returns pointer to the damaged buffer (same as input).
 */
char *trim_newline_and_whitespace(char *s) {
    if (!s) return s;
    /* Remove trailing newline and trailing spaces */
    size_t len = strlen(s);
    while (len > 0 && (s[len - 1] == '\n' || isspace((unsigned char)s[len - 1]))) {
        s[len - 1] = '\0';
        --len;
    }
    /* Remove leading spaces by shifting */
    size_t start = 0;
    while (s[start] != '\0' && isspace((unsigned char)s[start])) start++;
    if (start > 0) memmove(s, s + start, strlen(s + start) + 1);
    return s;
}

/* clean_name:
 * Copy only ASCII alphabetic characters from src to dst, converted to uppercase.
 * dst must have space for MAX_NAME_LEN characters.
 */
void clean_name(const char *src, char *dst) {
    size_t di = 0;
    for (size_t i = 0; src[i] != '\0' && di < MAX_NAME_LEN - 1; ++i) {
        unsigned char ch = (unsigned char)src[i];
        if (isalpha(ch) && ch < 128) {  /* restrict to ASCII letters */
            dst[di++] = (char) toupper(ch);
        }
    }
    dst[di] = '\0';
}

/* compute_numerology:
 * Sum letters where A=1 .. Z=26.
 * Assumes input is uppercase A-Z only.
 */
int compute_numerology(const char *cleaned) {
    int sum = 0;
    for (size_t i = 0; cleaned[i] != '\0'; ++i) {
        char c = cleaned[i];
        if (c >= 'A' && c <= 'Z') {
            sum += (c - 'A') + 1;
        }
    }
    return sum;
}

/* reduce_number:
 * Reduce an integer sum to a single digit (1-9), preserving master numbers 11 and 22.
 * Example: 29 -> 2+9 = 11 -> preserved (returns 11). If you want to always reduce to 2,
 * you can call reduce_number again. This implementation preserves 11 and 22 as masters.
 */
int reduce_number(int n) {
    while (n > 9 && n != 11 && n != 22) {
        int s = 0;
        int temp = n;
        while (temp > 0) {
            s += temp % 10;
            temp /= 10;
        }
        n = s;
    }
    return n;
}

/* append_person:
 * Append a Person to dynamic array, reallocating if needed.
 * Returns 0 on success, -1 on memory error.
 */
int append_person(Person **arr, size_t *count, size_t *capacity, const Person *p) {
    if (*count >= *capacity) {
        size_t newcap = (*capacity == 0) ? INITIAL_CAPACITY : (*capacity * 2);
        Person *tmp = realloc(*arr, newcap * sizeof(Person));
        if (!tmp) {
            return -1;
        }
        *arr = tmp;
        *capacity = newcap;
    }
    (*arr)[*count] = *p;
    (*count)++;
    return 0;
}

/* print_table:
 * Print a formatted table of results.
 */
void print_table(const Person *arr, size_t count) {
    printf("\n%-4s | %-30s | %-30s | %-10s | %-7s\n", "No.", "Original", "Cleaned", "Numerology", "Reduced");
    printf("----+--------------------------------+--------------------------------+------------+--------\n");
    for (size_t i = 0; i < count; ++i) {
        printf("%-4zu | %-30s | %-30s | %-10d | %-7d\n",
            i + 1,
            arr[i].original,
            arr[i].cleaned,
            arr[i].numerology,
            arr[i].reduced);
    }
}

/* save_csv:
 * Save results to a CSV file. Format:
 * Original,Cleaned,Numerology,Reduced
 * Returns 0 on success, -1 on error.
 */
int save_csv(const char *filename, const Person *arr, size_t count) {
    FILE *f = fopen(filename, "w");
    if (!f) {
        fprintf(stderr, "Error: Could not open file '%s' for writing: %s\n", filename, strerror(errno));
        return -1;
    }
    /* Header */
    if (fprintf(f, "Original,Cleaned,Numerology,Reduced\n") < 0) {
        fclose(f);
        fprintf(stderr, "Error: Write failed (header).\n");
        return -1;
    }
    for (size_t i = 0; i < count; ++i) {
        /* Escape quotes or commas if you want more robust CSV (not necessary for names without commas) */
        if (fprintf(f, "\"%s\",\"%s\",%d,%d\n",
                    arr[i].original,
                    arr[i].cleaned,
                    arr[i].numerology,
                    arr[i].reduced) < 0) {
            fclose(f);
            fprintf(stderr, "Error: Write failed at row %zu.\n", i + 1);
            return -1;
        }
    }
    if (fclose(f) != 0) {
        fprintf(stderr, "Error: Could not close file properly: %s\n", strerror(errno));
        return -1;
    }
    return 0;
}

/* flush_stdin_if_needed:
 * If the user input exceeded our buffer, flush the rest of the line from stdin.
 */
void flush_stdin_if_needed(FILE *stream, size_t read_len) {
    int ch;
    /* If the last read char was not newline, clear until newline or EOF */
    if (read_len == 0) return;
    /* Check last char - not accessible here reliably; just flush until newline */
    while ((ch = fgetc(stream)) != EOF && ch != '\n') {
        /* discard */
    }
}