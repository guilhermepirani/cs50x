#include "helpers.h"
#include "math.h"

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    // 2D loop
    for (int row = 0; row < height; row++)
    {
        for (int col = 0; col < width; col++)
        {
            // Assigning just to simplify
            int r = image[row][col].rgbtRed;
            int g = image[row][col].rgbtGreen;
            int b = image[row][col].rgbtBlue;
            
            // Grayscale equals the average of original rgb
            int grayValue = round((r + g + b) / 3.00);
            
            // In each channel
            image[row][col].rgbtRed = grayValue;
            image[row][col].rgbtGreen = grayValue;
            image[row][col].rgbtBlue = grayValue;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    //2D loop
    for (int row = 0; row < height; row++)
    {
        for (int col = 0; col < width; col++)
        {
            // Assigning just to simplify
            int r = image[row][col].rgbtRed;
            int g = image[row][col].rgbtGreen;
            int b = image[row][col].rgbtBlue;
            
            // Sepia formula
            int sepiaRed = round(.393 * r + .769 * g + .189 * b);
            int sepiaGreen = round(.349 * r + .686 * g + .168 * b);
            int sepiaBlue = round(.272 * r + .534 * g + .131 * b);
            
            // Make sure no value is bigger than 255
            image[row][col].rgbtRed = (sepiaRed > 255) ? 255 : sepiaRed;
            image[row][col].rgbtGreen = (sepiaGreen > 255) ? 255 : sepiaGreen;
            image[row][col].rgbtBlue = (sepiaBlue > 255) ? 255 : sepiaBlue;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    // 2D loop
    for (int row = 0; row < height; row++)
    {
        // Width divided by 2 otherwise we end up with the same image i.e. swap 2x
        for (int col = 0; col < width / 2; col++)
        {
            // Simple swap int function
            RGBTRIPLE temp = image[row][col];
            image[row][col] = image[row][width - col - 1];
            image[row][width - col - 1] = temp;
            
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // Temporary image to apply blur on
    RGBTRIPLE temp[height][width];

    // 2D loop
    for (int row = 0; row < height; row++)
    {
        for (int col = 0; col < width; col++)
        {
            // Initializing some variables
            int count = 0;
            float red = 0, green = 0, blue = 0;
            
            // Creating a box around each pixel
            int boxRows[] = {row - 1, row, row + 1};
            int boxCols[] = {col - 1, col, col + 1};
            
            // iterating each pixel in the box
            for (int r = 0; r < 3; r++)
            {
                for (int c = 0; c < 3; c++)
                {
                    int tempRow = boxRows[r];
                    int tempCol = boxCols[c];
                    
                    // Excluding out of edge pixels then adding colors to variable
                    if (tempRow >= 0 && tempRow < height && tempCol >= 0 && tempCol < width)
                    {
                        RGBTRIPLE boxColors = image[tempRow][tempCol];
                        
                        red += boxColors.rgbtRed;
                        green += boxColors.rgbtGreen;
                        blue += boxColors.rgbtBlue;
                        
                        count++;
                    }
                }
            }
            // Apllying buring formula
            temp[row][col].rgbtRed = round(red / count);
            temp[row][col].rgbtGreen = round(green / count);
            temp[row][col].rgbtBlue = round(blue / count);
        }
    }
    // Refreshing original image with blured one
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = temp[i][j];
        }
    }
    return;
}