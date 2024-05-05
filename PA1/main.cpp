#include <iostream>
#include <string.h> // Generated number will be a string
#include <ctime> // I am using this to generate random numbers appropriately
#include <cstdlib>


using namespace std;

// generates a random number
string generate_random_number(int N);
// calculate first count
int produce_first_count(const string&, const string&);
// calculate second count
int produce_second_count(const string&, const string&);
// check if the given input is valid or not
bool is_valid(const string &);
// checks if the entered characters are unique
bool is_unique(const string&);

// max length of a given or generated number
const int MAX_LENGTH = 15;
// max game round for the program
const int MAX_ITERATION = 100;



int main(int argc, char *argv[]) {

    // hold the Cexact, Cmisplaced
    int first_count, second_count;
    // store the user input as a string
    string user_input = "";
    // keep track of number of turns
    int turn_counter = 1;
    // flag to terminate the while loop if user finds the secret number
    bool found = false;
    // this will hold the secret number
    string secret_number;

    // if the argument length is bigger than 3, it will give E0 error
    if(argc != 3) 
    {
        cout << "E0" << endl;
        return 0;
    }
    
    // parse the given argument
    string option = argv[1];
    // this will be either length of the number or number itself, I will decide it using option
    string given_input = argv[2];

    // -r mode --> random number generation
    if(option == "-r") 
    {
        // Convert length to integer
        int length = std::atoi(given_input.c_str());
        
        // Error for invalid number length
        if (length <= 0 || length > 16) {
            cout << "E0\n";
            return 0;
        }
        
        // generate the secret number
        secret_number = generate_random_number(length);
        cout << secret_number << endl;

        do
        {
            // take a user input
            cin >> user_input;

            // Check if the user input is valid
            if (user_input.length() != length)
            {
                cout << "E1\n";
                return 0;
            }
            // invalid input error --> it contains non-digit
            if(!is_valid(user_input)) 
            {
                cout << "E2\n";
                return 0;

            }
            // give hints for every attempt
            // first_count --> Cexact
            // second_count --> Cmisplaced
            first_count = produce_first_count(user_input, secret_number);
            second_count = produce_second_count(user_input, secret_number);
            // if the first count is equal to the length of the secret number
            // it means, user found the secret number
            if(first_count == secret_number.length()) 
            {
                cout << "FOUND" << " " << turn_counter << endl;
                return 0;
            }

            cout << first_count << " " << second_count << endl;
            turn_counter++;
            
        } while (!found && turn_counter <= MAX_ITERATION);

        // if the user can not find it after 100 iterations
        cout << "FAILED" << endl;
        


    }
    // -u mode --> user will type a number
    else if(option == "-u") 
    {

        secret_number = given_input;

        // if the user enters a number with repeating digits --> non unique digits
        if(!is_unique(secret_number)) 
        {
            cout << "E0\n";
            return 0;
        }

        // check if the given secret number is valid --> contains non-digit
        if(!is_valid(secret_number)) 
        {
            cout << "E2\n";
            return 0;

        }
        
        // Error for invalid number length
        if (secret_number.length() <= 0 || secret_number.length() > 16) {
            cout << "E0\n";
            return 0;
        }

    
        do
        {
            // take a user input
            cin >> user_input;

            // invalid length
            if (secret_number.length() != user_input.length()) {
                cout << "E1\n";
                return 0;
            }
            // invalid input error --> it contains non-digit
            if(!is_valid(user_input)) 
            {
                cout << "E2\n";
                return 0;
            }
            // give hints for every attempt
            // first_count --> Cexact
            // second_count --> Cmisplaced
            first_count = produce_first_count(user_input, secret_number);
            second_count = produce_second_count(user_input, secret_number);
            // if the first count is equal to the length of the secret number
            // it means, user found the secret number
            if(first_count == secret_number.length()) 
            {
                cout << "FOUND" << " " << turn_counter << endl;
                return 0;
            }

            cout << first_count << " " << second_count << endl;
            turn_counter++;
            
        } while (!found && turn_counter <= MAX_ITERATION);

        // if the user can not find it after 100 iterations
        cout << "FAILED" << endl;

    }
    else 
    {
        cout << "EO" << endl; // Error for invalid option
        return 0;
    }
    

    return 0;
    
}



// Function to generate a random number as a string
string generate_random_number(int N) {
    // Initialization of random number generator
    srand(time(0));

    // Maximum length of digits array
    const int MAX_DIGITS = 15;
    // Array of possible digits
    char digits[MAX_DIGITS] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e'};
    int digitsLength = MAX_DIGITS;

    // String to store the generated number
    string valid_number = "";
    char selected_digit;
    int index;

    // Ensure the first digit is not '0'
    do {
        index = rand() % digitsLength;
        selected_digit = digits[index];
    } while (selected_digit == '0');

    // Add the first digit to the valid_number
    valid_number += selected_digit;

    // Swap the used digit with the last element and decrement the length
    swap(digits[index], digits[digitsLength - 1]);
    digitsLength--;

    // Construct the remaining part of the number
    for (int i = 1; i < N; ++i) {
        if (digitsLength == 0) {
            break; // Break if there are no more digits to choose from
        }

        index = rand() % digitsLength;
        selected_digit = digits[index];
        valid_number += selected_digit;

        // Swap the used character with the last element and reduce the length
        swap(digits[index], digits[digitsLength - 1]);
        digitsLength--;
    }

    return valid_number;
}


// calculate first count
int produce_first_count(const string & user_input, const string & secret_number) 
{
    // first count
    int count = 0;
    // count the number of match digit
    for (int i = 0; i < user_input.size() && i < secret_number.size(); ++i) {
        if (user_input[i] == secret_number[i]) {
            count++;
        }
    }
    return count;
}


// calculate second count
int produce_second_count(const string & user_input, const string & secret_number) 
{
    // second count
    int count = 0;

    // I will put intersection digits, then compare the indices in each string, the increment the count
    for(int i = 0; i < user_input.length(); i++) 
    {
        // select a character
        char ch = user_input[i];
        // compare the selected char with every char in secret number
        for(int j = 0; j < secret_number.length(); j++) 
        {
            if(ch == secret_number[j] && i != j) 
            {
                count++;
            }
        }
    }

    return count;


}


// checks if the given input is invalid or not --> if there exists a non-digit
bool is_valid(const string & user_input) 
{
    // digits
    char digits[MAX_LENGTH] = {'0','1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e'};

    // first character can not be 0
    if(user_input[0] == '0')
        return false;

    // Check if there exists any character in user_input that is not in digits
    for (char ch : user_input) 
    {
        // flag --> if the char is found
        bool is_digit_found = false;

        // Check each character against allowed digits
        for (char valid_digit : digits)
        {
            if (ch == valid_digit) {
                is_digit_found = true; // Set flag to true if the digit is found
            }
        }

        // If the character was not found in the list of valid digits, return false
        if (!is_digit_found)
            return false;
    }

    return true;
}

// checks if the entered characters are unique
bool is_unique(const string& user_input) 
{
    // Loop over each character in the string
    for (int i = 0; i < user_input.length(); i++) {
        // Compare it with every other character
        for (int j = i + 1; j < user_input.length(); ++j) {
            // If a match is found, characters are not unique
            if (user_input[i] == user_input[j]) {
                return false;
            }
        }
    }
    // If no matches were found, the characters are unique
    return true;

}





