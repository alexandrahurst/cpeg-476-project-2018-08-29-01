#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char DECRYPTED_FILE_PREFIX[] = "decrypted_";
const char ascii_lowercase_char_offset = 97;

char get_letter(const char* num) {
    int letter_id = atoi(num);
    letter_id = ((letter_id + 13) - 1) % 26;
    return (char)letter_id + ascii_lowercase_char_offset;
}

int main(int argc, char* argv[]) {
    // Check correct number of args
    if (argc != 2) {
        fprintf(stderr, "Error: Incorrect number of arguments. Please specify " 
                "a single message file to decrypt.\n");
        return -1;
    }
    
    // Open input file
    FILE* in_file = fopen(argv[1], "r");
    if (in_file == NULL) {
        fprintf(stderr, "Error: Unable to open input file.\n");
        return -1;
    }
    
    // Open output file
    int out_file_name_len = strlen(argv[1]) + strlen(DECRYPTED_FILE_PREFIX)  + 1;
    char* out_file_name = malloc(out_file_name_len);
    if (out_file_name == NULL) {
        fprintf(stderr, "Error: Failed to allocate memory.\n");
        return -1;
    }
    strncpy(out_file_name, DECRYPTED_FILE_PREFIX, out_file_name_len);
    out_file_name[strlen(DECRYPTED_FILE_PREFIX)] = '\0';
    strncat(out_file_name, argv[1], out_file_name_len);
    out_file_name[out_file_name_len - 1] = '\0';
    FILE* out_file = fopen(out_file_name, "w");
    if (out_file == NULL) {
        fprintf(stderr, "Error: Unable to open output file.\n");
    }
    
    
    char word_buf[1024];
    while (fscanf(in_file, " %1023s", word_buf) == 1) {
        int word_buf_len = strlen(word_buf);
        char letter_buf[2];
        letter_buf[0] = '\0';
        letter_buf[1] = '\0';
        int letter_buf_i = 0;
        for (int i = 0; i < word_buf_len; i++) {
            if (word_buf[i] == '-') {
                fprintf(out_file,  "%c", get_letter(letter_buf));
                letter_buf[0] = '\0';
                letter_buf[1] = '\0';
                letter_buf_i = 0;
            } else {
                letter_buf[letter_buf_i] = word_buf[i];
                letter_buf_i = 1;
            }
            
            if (i == word_buf_len - 1) {
                fprintf(out_file,  "%c", get_letter(letter_buf));
                fprintf(out_file, " ");
            }
        }
    }
    fclose(in_file);
    fclose(out_file);
    free(out_file_name);
    
    return 0;
}