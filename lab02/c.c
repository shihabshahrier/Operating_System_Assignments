#include <stdio.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    FILE *file = fopen(argv[1], "a");
    if (file == NULL) {
        printf("No such File%s\n", argv[1]);
        return 1;
    }

    char str[1000];
    printf("Enter strings to write to the file. Enter '-1' to stop.\n");
    
    while (1) {
        printf("Enter a string: ");
        fgets(str, sizeof(str), stdin);

        if (str[0] == '-' && str[1] == '1') {
            break;
        }

        fprintf(file, "%s\n", str);
        printf("%s", str);
        printf("%ld", sizeof(str));
    }

    fclose(file);
    return 0;
}
