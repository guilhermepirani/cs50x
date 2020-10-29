#include <stdio.h>
#include <cs50.h>
#include <math.h>
#include <ctype.h>

// Prototype functions
int counters(string text);
void printGrade(int);
int colemanIndex(int, int, int);

// Global variables
int l, w, s, index;

int main(void)
{
    // Gets text from the user
    string text = get_string("Text: ");
    // Analyzes the text
    counters(text);
    colemanIndex(l, w, s);
    // Print results
    printGrade(index);
}
// Iterates through all the text and counts each letter, word and sentence.
int counters(string text)
{
    int letters = 0;
    int words = 1;
    int sentences = 0;
    
    for (int i = 0; text[i] != '\0'; i++)
    {
        if (isalpha(text[i]) > 0)
        {
            letters++;
        }
        if (text[i] == ' ')
        {
            words++;
        }
        if (text[i] == '.' || text[i] == '!' || text[i] == '?')
        {
            sentences++;
        }
    }
    return l = letters, w = words, s = sentences;
}
// Uses the Coleman index formula to grade the text
int colemanIndex(int a, int b, int c)
{
    return index = round(0.0588 * (a / ((float)b / 100)) - 0.296 * (c / ((float)b / 100)) - 15.8);
}
// Printing different outputs based on grade
void printGrade(int grade)
{
    if (grade < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (grade >= 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %i\n", grade);
    }
}