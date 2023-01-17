#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>
#define MIN_CHAR 33
#define MAX_CHAR 126
#define USER_RULES "* 1-10 characters\n* Alphabet characters only\n"
#define STRONG_PASS_RULES "* 8-15 characters\n* No special characters\n* At least 1 of each: digit, upper, and lowercase char\n*"

/**
 * Checks if char is not a letter or digit
 */
bool notInBounds(const char c)
{
    return c < 48 || (c > 57 && c < 65) || (c > 90 && c < 97) || c > 122;
}

/**
 * Self explanatory
 */
bool isLetter(const char c)
{
    return (c >= 65 && c <= 90) || (c >= 97 && c <= 122);
}

/**
 * letterCompare serves to make letters uppercase for comparison
 */
bool letterCompare(char c1, char c2)
{
    if(c1 >= 97) { c1 -= 32; }

    if(c2 >= 97) { c2 -= 32; }

    return c1 == c2;
}

bool isStrongPassword(const char* username, const char* password)
{
    if(password == 0) {
        return false;
    } else if(notInBounds(*password) || strlen(password) < 8) {
        return false;
    }
    /* These bools are the restrictions */
    bool upper = false, lower = false, digit = false, user = false;
    /* The userCount tracks the existence of the username in the password */
    int userCount = 0;

    while(*password != 0)
    {
        /* If char is letter, there are more specifications
         * to check unlike the digit further down */
        if(isLetter(*password)) {
            if(*password >= 65 && *password <= 90) {
                upper = true;
            } else {
                lower = true;
            }

            if(*username != 0) {
                if(letterCompare(*password, *username)) {
                    username++;
                    userCount++;
                } else {
                    username -= userCount;
                    userCount = 0;
                    if(letterCompare(*password, *username)) {
                         username++;
                         userCount++;
                    }
                }
            }
        } else {
            if(*password == *username) {
                username++;
                userCount++;
            }
            
            digit = true;
        }

        if(*username == 0) { return false; }

        password++;
    } /* End of non null password while loop */

    return !(!upper || !lower || !digit);
}

//Creates a random int within a  range
int myRand(int min, int max)
{
    return rand() % (max - min + 1) + min;
}
void generateDefaultPassword(char* default_password, const char* username)
{
    char mold[21] = {0};
    int i = 0;
    do
	{
        //This block resets the string
        i = 0;
        while(mold[i] != 0) { mold[i++] = 0; }

        int maxLength = myRand(0, 19);
        
        //Moves through array backwards
        for(; maxLength >= 0; maxLength--) {
            //This checks if the random character is viable
            do {
                mold[maxLength] = myRand(MIN_CHAR, MAX_CHAR);
            } while(notInBounds(mold[maxLength]));
        }         
    }
	while(!isStrongPassword(username, mold));
        
        //Sets value of defaule_password with the password in mold
        strcpy(default_password, mold);
}

int main(void)
{
        /* Allows for random password each program run */
        srand(time(0));
        char user[11] = {0}, password[16] = {0};
        char confirm;
        //while(true) {
            printf("%sEnter a username: ", USER_RULES);
            scanf("%10s", user);
        //    if(user) {
        //        printf("Username permitted: %s\n", password);
        //        break;
        //    } else {
        //        printf("Password is not strong enough. Follow these rules:\n%s", STRONG_PASS_RULES);
        //    }
        //}
        while(true) {
            printf("[Password Creation]\n*'Y' to manually enter one\n*'N' to randomly generate one\nCreate your own password?: ");
            scanf(" %1c%*", &confirm);

            /* If user decides to maually create a password*/
            if(letterCompare(confirm, 'Y')) {
                printf("[Password Requirements]\n%s", STRONG_PASS_RULES);
                while(true) {
                    printf("Enter a password: ");
                    scanf("%15s", password);
                    if(isStrongPassword(user, password)) {
                        printf("Password permitted: %s\n", password);
                        break;
                    } else {
                        printf("Password is not strong enough. Follow these rules:\n%s", STRONG_PASS_RULES);
                    }
                };
            } else if(letterCompare(confirm, 'N')) {
                printf("Generating default password...\n");
                generateDefaultPassword(password, user);
                printf("Default generated: %s\n", password);
                break;
            }
        }
        
}

