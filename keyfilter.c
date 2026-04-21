#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

#define MAX_TOWNS 300
#define MAX_LENGTH 200
#define ALPHABET_LENGTH 26

int load_address_count(char towns[MAX_TOWNS][MAX_LENGTH]) {
    //function loads towns from stdin and returns number of towns
    int count = 0;
    for (; count < (MAX_TOWNS - 1) && fgets(towns[count], MAX_LENGTH, stdin); count++) {
        //removing newline
        int len = 0;
        while (towns[count][len] != '\0') {
            if (towns[count][len] == '\n') {
                towns[count][len] = '\0';
                break;
            }
            len++;
        }
    }
    //if too many addresses return -1 (will return error in main)
    if (fgets(towns[count], MAX_LENGTH, stdin)) return -1;
    return count;
}

//make characters uppercases
void case_insensitive(char word[]){
    for (int i = 0; word[i] != '\0'; i++) {
        word[i] = toupper(word[i]);
    }
}
 
void compare(char towns[MAX_TOWNS][MAX_LENGTH], char *prefix, int string_compare[], int string_compare_char[], int *address_count){
    int prefix_length = strlen(prefix);
    //compare all towns with prefix, store reult in string_compare
    for (int i = 0; i < *address_count; i++){
        string_compare[i] = strncmp(towns[i], prefix, prefix_length);
        int number_of_spaces = 0;
        //remove spaces after prefix_length to get next character
        while (towns[i][prefix_length + number_of_spaces] == ' '){
            number_of_spaces++;
        }
        //store next character after spaces
        string_compare_char[i] = (towns[i][prefix_length + number_of_spaces] - 'A');
    }
}

//set alpha_array to true at positions where next character is possible
void return_alchar(int string_compare[], bool alpha_array[], int string_compare_char[], int *address_count){
    for (int i = 0; i < *address_count; i++){
        if (string_compare[i] == 0) alpha_array[string_compare_char[i]] = true;
    }
}

int check_match(int string_compare[], char towns[MAX_TOWNS][MAX_LENGTH], char *prefix, int *address_count){
    int match_count = 0;
    int match_address[MAX_TOWNS];
    //find all matches
    for (int i = 0; i < *address_count; i++){
        if (string_compare[i] == 0){
            match_address[match_count] = i;
            match_count++;
        }
    }
    //if no match print not found
    if (match_count == 0){
        printf("Not found\n");
        return match_count;
    }
    //if exactly one unique match print it
    if (match_count == 1){
        printf("Found: %s\n", towns[match_address[0]]);
        match_count--;
        return match_count;
    }
    //if multiple matches check if one matches exactly
    for(int i = 0; i < match_count; i++){
        if (match_count >= 1 && strlen(towns[match_address[i]]) == strlen(prefix)){
            //if it matches exactly print it
            printf("Found: %s\n", towns[match_address[i]]);
            match_count--;
        }
    }
    return match_count;
}

//get first characters of all towns into alpha_array
void return_firstchar(char towns[MAX_TOWNS][MAX_LENGTH], bool alpha_array[], int *address_count){
    for (int i = 0; i < *address_count; i++){
        alpha_array[towns[i][0] - 'A'] = true;
    }
}

//print next characters using alpha_array
void print_alchar(bool alpha_array[]){
    printf("Enable: ");
    for (int i = 0; i < ALPHABET_LENGTH; i++){
        if (alpha_array[i] == true) printf("%c", (i+'A'));
    }
    printf("\n");
}

//if prefix contains non-alphabetic character return true
bool error_is_not_alpha(char *prefix){
    int prefix_length = strlen(prefix);
    for (int i = 0; i < prefix_length; i++){
        if (!(isalpha(prefix[i]))) return true;
    }
    return false;
}

//if no towns loaded return true
bool error_no_count(int *address_count){
    if (*address_count == 0) return true;
    return false;
}


int main(int argc, char *argv[]){

    //load towns from stdin
    //load number of towns
    char towns[MAX_TOWNS][MAX_LENGTH];
    int address_count = load_address_count(towns);
    
    //make all words uppercase (case insensitive)
    for (int i = 0; i < address_count; i++) case_insensitive(towns[i]);

    //array long as alphabet to store possible letters
    bool alpha_array[ALPHABET_LENGTH] = {false};

    //if no argument print first letters
    if (argc < 2){
        return_firstchar(towns, alpha_array, &address_count);
        print_alchar(alpha_array);
        return 0;
    }

    //get prefix from argument
    char *prefix = argv[1];
    case_insensitive(prefix);

    //check for errors
    if (error_is_not_alpha(prefix)){
        fprintf(stderr, "Error: Prefix must contain only alphabetic characters.\n");
        return 1;
    }
    if (error_no_count(&address_count)){
        fprintf(stderr, "Error: Textfile must contain at least one address.\n");
        return 1;
    }
    if (address_count == -1){
        //if too many addresses in textfile print error
        fprintf(stderr, "Error: Too many addresses in textfile. The program supports only %d addresses.\n", MAX_TOWNS);
        return 1;
    }

    //find matching towns
    int string_compare[address_count];
    int string_compare_char[address_count];
    compare(towns, prefix, string_compare, string_compare_char, &address_count);

    //get possible next letters
    return_alchar(string_compare, alpha_array, string_compare_char, &address_count);

    //check if a town matches exactly
    int match_count = check_match(string_compare, towns,  prefix, &address_count);

    if (match_count != 0) print_alchar(alpha_array);
    return 0;
}
//eof
