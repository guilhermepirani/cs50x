// Ciphers a text using substitution cipher

#include <stdio.h>
#include <cs50.h>
#include <ctype.h>
#include <string.h>

// Prototype functions
void subs(char *, char *);

int main(int argc, char *argv[])
{
    //validates key
    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }
    if (strlen(argv [1]) != 26)
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }
    for (int i = 0; i < strlen(argv[1]); i++)
    {
        // First checks if char is alphabetic
        if (isalpha(argv[1][i]) == 0)
        {
            printf("Key must only contain alphabetic characters. \n");
            return 1;
        }
        // Then we use a nested loop to check repetitions
        for (int r = i + 1; r < strlen(argv[1]); r++)
        {
            // As the key could be any case we make sure to compare upper to upper
            if (toupper(argv[1][r]) == toupper(argv[1][i]))
            {
                printf("Key must only contain one of each alphabetic character. \n");
                return 1;
            }
        }
    }
    // Gets plaintext
    string text = get_string("Plaintext: ");
    // Make ciphertext
    subs(text, argv[1]);
}

void subs(char *t, char *k)
{
    printf("ciphertext: ");
    
    for (int i = 0; i < strlen(t); i++)
    {
        if (isalpha(t[i]) != 0)
        {
            // We need to maintain the same case for each letter as given by the user
            if (isupper(t[i]) != 0)
            {
                int index = t[i] - 'A';
                printf("%c", toupper(k[index]));
            }
            else
            {
                // We take 'a''s ascII value from t[i], so it matches our key index for position.
                int index = t[i] - 'a';
                printf("%c", tolower(k[index]));    
            }
        }
        // if not alphabetic just prints
        else
        {
            printf("%c", t[i]);
        }
    }
    printf("\n");
}