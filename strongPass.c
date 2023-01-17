#include <stdio.h>
#include <stdbool.h>

//Checks if char is not a letter or digit
bool notInBounds(const char c)
{
    return c < 48 || (c > 57 && c < 65) || (c > 90 && c < 97) || c > 122)
        { return true; }
        
       	return false;
}

//Self explanatory
bool isLetter(const char c)
{
        if((c >= 65 && c <= 90) || (c >= 97 && c <= 122))
        { return true; }
        
        return false;
}

//letterCompare serves to make letters uppercase for comparison
bool letterCompare(char c1, char c2)
{
        if(c1 >= 97)
        { c1 -= 32; }
        
       	if(c2 >= 97)
        { c2 -= 32; }

        if(c1 == c2)
        { return true; }

        return false;
}

bool isStrongPassword(const char* username, const char* password)
{
        //These bools are the restrictions
        bool charMin = false, upper = false, lower = false, digit = false,
             charOutBound = false, string = false, user = false;
        //The ints serve as counters: how many chars in the password,
        //how many consecutive letters, and username counter
        int charCount = 0, strCount = 0, userCount = 0;

        while(*password != 0)
        {
                charCount++;

                if(notInBounds(*password))
                { charOutBound = true; }
                else
                {
                        //If char is letter, there are more specifications
                        //to check unlike the digit further down
                        if(isLetter(*password))
                        {
                                if(*password >= 65 && *password <= 90)
                                { upper = true; }
                                else
                                { lower = true; }
                                
                                if(*username != 0)
                                {
                                        if(isLetter(*username) && 
                                                letterCompare(*password, 
                                                *username))
                                        //Move username pointer and increases
                                        //userCount variable
                                        { 
                                                username++;
                                                userCount++;
                                        }
                                        else
                                        //Resets the userCount and pointer
                                        { 
                                                username -= userCount;
                                                userCount = 0;
                                        }
                                }
                                //Increases string counter since letters
                                strCount++;
                        }
                        else
                        {
                                if(*password == *username)
                                {
                                        username++;
                                        userCount++;
                                }

                                digit = true;
                                //Digit resets the str counter
                                strCount = 0;
                        }
                } //End of in Bound else

                if(charCount == 8)
                { charMin = true; }

                if(strCount == 4)
                { string = true; }

                if(*username == 0)
                { user = true; }

                password++;
        }//End of loop

        //Returns false if base requirements aren't met or there are
        //special characters or the username in password
        if(!charMin || !upper || !lower || !digit || charOutBound ||
                       !string || user)
        { return false; }

        return true;
}

int main(void)
{
        char user[10] = {0}, password[15] = {0};

        printf("[Username Requirements]\n* 1-10 characters\n* Alphabet characters only\nEnter a username: ");
        scanf("%s", user);
        printf("[Password Requirements]\n * 1-15 characters\n: ");
        scanf("%s", password);

        if(isStrongPassword(user, password)) {
            printf("[This is a strong password]\n");
        } else {
            printf("[This password is not strong. Try again]\n");
        }

        return 0;
}

