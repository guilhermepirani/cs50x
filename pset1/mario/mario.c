// Used Libraries
#include <stdio.h>
#include <cs50.h>

// Prototype functions
int getValue();
void draw(int height);

// Simplest main loop ever
int main(void)
{
    int height = getValue();
    draw(height);
}

// Function to receive and check the required height value
int getValue()
{
    // Initializing a outside do Loop otherwise while won't get it
    int a;
    do
    {
        a = get_int("Height: ");
    }
    while (a < 1 || a > 8);
    
    // Return value of a to height
    return a;
}

// Function that draws the pyramid
void draw(int height)
{
    // Mother Loop, provides an increasing variable and breaks end of lines at each row
    for (int row = 0; row < height; row++)
    {
        // 1st Nested, prints spaces that make the pyramid face to the right side
        for (int spaces = row + 1; spaces < height; spaces++)
        {
            printf(" ");
        }
        
        // 2nd Nested, prints the actual pyramid
        for (int hashes = height + row + 1; hashes > height; hashes--)
        {
            printf("#");
        }
    printf("  ");
    
    for (int hashes = height + row + 1; hashes > height; hashes--)
    {
        printf("#");
    }   
    printf("\n");
    }
}