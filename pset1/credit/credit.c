#include <stdio.h>
#include <cs50.h>
#include <math.h>

// Prototype functions
bool luhnCheck(long cardNumber);
int getCardLen(long cardNumber);
void getCardProv(long cardNumber);

int main(void)
{
    // Asks for a card number
    long cardNumber = get_long_long("Card Number to Validate: ");
    //Checks if the number is valid to Luhn's Algorithm, if not prints invaliid
    if (luhnCheck(cardNumber) == true)
    {
        // Check if the card is valid for a provider
        getCardProv(cardNumber);

    }
    else
    {
        printf("INVALID\n");
    }
}

// Application of Luhn's Algorithm
bool luhnCheck(long cardNumber)
{
    // Our sum that validates or not the card
    int checkSum = 0;
    // Copy of credit card number we're destroying
    long tmp = cardNumber;
    
    // Iterates over each digit of the credit card number, checkig for odds and evens
    for (int pos = 0; tmp > 0; pos++)
    {
        if (pos % 2 == 0)
        {
            // Adds the last digit of the card to the sum
            checkSum += tmp % 10;
            // Excludes the last digit of the card
            tmp /= 10;
        }
        else
        {
            // For odd numbers it's necessary to *2
            int odd = (tmp % 10) * 2;
            // Makes sure we add each digit of the product an not the whole number
            checkSum += (odd / 10 + odd % 10);
            tmp /= 10;
        }
    }
    // Returns true or false for the card validation
    return (checkSum % 10) == 0;
}

int getCardLen(long cardNumber)
{
    // Counts how many digits the card number has
    int len = log10(cardNumber);
    return len + 1;
}

void getCardProv(long cardNumber)
{
    // Saves the card number lenght for use
    int len = getCardLen(cardNumber);
    // It's going to store the first 2 digits of the card number
    int prov;
    
    // Code Block for 16 digits lenght
    if (len == 16)   
    {
        // Uses scientific notation to reduce cardd number to 2 digits
        prov = (cardNumber / 1e14);
        // Then checks said digits and prints it's provider
        if (prov >= 51 && prov <= 55)
        {
            printf("MASTERCARD\n");
        }
        else if (prov >= 40 && prov <= 49)
        {
            printf("VISA\n");
        }
        // For check error
        else
        {
            printf("INVALID\n");
        }
    }
    
    // Same as above
    if (len == 13)
    {
        prov = (cardNumber / 1e12);
        if (prov == 4)
        {
            printf("VISA\n");
        }
        else
        {
            printf("INVALID\n");
        }
    }
    
    // Same as above
    if (len == 15)
    {
        prov = (cardNumber / 1e13);
        if (prov == 34 || prov == 37)
        {
            printf("AMEX\n");
        }
        else
        {
            printf("INVALID\n");
        }
    }
    // Deals with any other lenght not specified by blocks above
    else if (len <= 12 || len >= 17 || len == 14)
    {
        printf("INVALID\n");
    }
}
