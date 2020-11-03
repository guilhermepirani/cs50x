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
            // Apllying bluring formula
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

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    // Temporary image to apply blur on
    RGBTRIPLE temp[height][width];
    
    // Detection matrix for x and y
    int Gx[3][3] = 
    {
        {-1, 0, 1},
        {-2, 0, 2},
        {-1, 0, 1}
    };
    
    int Gy[3][3] =
    {
        {-1, -2, -1},
        {0, 0, 0},
        {1, 2, 1}
    };

    // 2D loop
    for (int row = 0; row < height; row++)
    {
        for (int col = 0; col < width; col++)
        {
            // Initializing some variables
            float redGx = 0, greenGx = 0, blueGx = 0;
            float redGy = 0, greenGy = 0, blueGy = 0;
            
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
                        
                        redGx += Gx[r][c] * boxColors.rgbtRed;
                        greenGx += Gx[r][c] * boxColors.rgbtGreen;
                        blueGx += Gx[r][c] * boxColors.rgbtBlue;
                        
                        redGy += Gy[r][c] * boxColors.rgbtRed;
                        greenGy += Gy[r][c] * boxColors.rgbtGreen;
                        blueGy += Gy[r][c] * boxColors.rgbtBlue;
                    }
                }
            }
            
            // Normalizing values
            int red = round(sqrt(pow(redGx, 2) + pow(redGy, 2)));
            int green = round(sqrt(pow(greenGx, 2) + pow(greenGy, 2)));
            int blue = round(sqrt(pow(blueGx, 2) + pow(blueGy, 2)));
            
            temp[row][col].rgbtRed = red > 255 ? 255 : red;
            temp[row][col].rgbtGreen = green > 255 ? 255 : green;
            temp[row][col].rgbtBlue = blue > 255 ? 255 : blue;
        }
    }
    
    // Refreshing original image with edged one
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = temp[i][j];
        }
    }
}
