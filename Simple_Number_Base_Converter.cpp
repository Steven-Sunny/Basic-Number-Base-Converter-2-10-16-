//2-10-16 Number Base Converter
//Steven Sun
#include <iostream>
#include <cctype>
#include <cmath>
#include <string>

//A simple and not optimized cpp code to change from different number bases.
//Namely: Base 2, base 10 and base 16.

//Checks for valid input
//An input is valid when the number provided has values that match the given source_base
//An input is valid when there are no extra decimal points and no special characters
bool validateInput(std::string input_number, int source_base){

    //Declares and initializes int count for counting the number of decimal points that are in the number.
    int count = 0;
    //Runs through the entire number to check for valid values/characters relative to the base given
    for(unsigned int i=0; i<input_number.size(); i++){
        //If not a binary number (1,0) and user said base was 2, return as false. 
        if(source_base==2 && input_number[i]!='1' && input_number[i]!='0' && input_number[i]!='.'){
            return false;
        }
        //If not a decimal number (9,8,...,1,0) and user said base was 10, return as false.
        else if(source_base==10 && !isdigit(input_number[i]) && input_number[i]!='.'){
            return false;
        }
        //If not a hexadecimal number (F,E,...,B,A,9,8,...,1,0) and user said base was 16, return as false.
        else if(!isxdigit(input_number[i]) && input_number[i]!='.'){
            return false;
        }
        //Adds 1 to count for every decimal point.
        if(input_number[i]=='.'){
            count++;
        }
    }
    //If there is more than 1 decimal point, return as false.
    if(count > 1){
        return false;
    }
    //Finally, return as true.
    return true;
}

//Converts between number bases (2, 10 or 16)
//Takes a string of input_number and the two bases.
//Prereqs: Know how to change between number bases 2, 10 and 16 before reading this code.
int convert_number(std::string input_number, int source_base, int target_base){
    //Initializes and declares some important variables and values
    //decimal_point_pos for keeping track of the decimal point|input_size for total length of input_number
    //is_fractional to let code know when we are in the fractional component
    //total_sum for adding all of the values together into a base 10 number
    int decimal_point_pos = 0;
    int input_size = input_number.size();
    bool is_fractional = false;
    double total_sum = 0;

    //Find the location of the decimal point. If there is non, then decimal_point_pos = input_size 
    for(int i=0; i<input_size && input_number[i]!='.'; i++){
        decimal_point_pos++;
    }
    
    //2 to 10
    //16 to 10
    //Uses a lot of exponentiation for conversion, brought in the math library for it.
    if((source_base == 2 || source_base == 16) && target_base == 10){

        //int fractions tracks what decimal place the iterator is at for negative exponentiation (keeping track of the index is difficult...)
        int fractions = -1;
        //Counts decimal place position from the right side instead of left. Used for index manipulation later.
        decimal_point_pos = input_size-decimal_point_pos;

        //Runs through entire the entire input number
        for(int i=0; i<input_size; i++){
            //Runs for all fractional digits.
            if(is_fractional){
                //Since we are working with characters, we use the equivalent ASCII values for some easy manipulation.
                //If the char is between 65 and 70, we know that it is a upper-case alphabetical char and this runs.
                if(65 <= input_number[i] && input_number[i] <= 70){
                    //Knowing how to convert bewtween 2 to 10 and 16 to 10 will make this calculation make more sense.
                    //We take the displayed value of the char and use it in our calculations as an int.
                    //Take the int and multiply it by the source_base to the power of the position of its digit.
                    //Since we are in the fractional component, the exponent gives a fraction
                    //The subtraction is done to make the char actually usable in our calculations as it removes the ASCII aspect of the value.
                    //The final value is summed into total_sum and we continue.
                    //Same theory follows for all the other calculations.
                    total_sum = total_sum + (input_number[i]-55)*pow(source_base, fractions--);
                //If the char is between 97 and 102, we know that it is a lower-case alphabetical char and this runs.
                }else if (97 <= input_number[i] && input_number[i] <= 102) {
                    total_sum = total_sum + (input_number[i]-87)*pow(source_base, fractions--);
                //Otherwise, if it is not alphabetical at all, we know it is a numerical char and this runs instead.
                }else{
                    total_sum = total_sum + (input_number[i]-'0')*pow(source_base, fractions--);
                }
            
            //Excluding the decimal point, runs for all non-fractional digits.
            }else if (input_number[i]!='.'){
                //If the char is between 65 and 70, we know that it is a upper-case alphabetical char and this runs.
                if(65 <= input_number[i] && input_number[i] <= 70){
                    //The only difference from above is the indexing used to track the exponent value.
                    //Since we are in the integral part, we will get a whole number.
                    total_sum = total_sum + (input_number[i]-55)*pow(source_base, (input_size-(i+1))-decimal_point_pos);
                //If the char is between 97 and 102, we know that it is a lower-case alphabetical char and this runs.
                }else if (97 <= input_number[i] && input_number[i] <= 102) {
                    total_sum = total_sum + (input_number[i]-87)*pow(source_base, (input_size-(i+1))-decimal_point_pos);
                //Otherwise, if it is not alphabetical at all, we know it is a numerical char and this runs instead.
                }else{
                    total_sum = total_sum + (input_number[i]-'0')*pow(source_base, (input_size-(i+1))-decimal_point_pos);
                }
            }

            //If we see a decimal point, the loop does all following char as part of the fractional component.
            if(input_number[i]=='.'){
                is_fractional=true;
            }
        }
        //Output for base 2 to 10 and base 16 to 10
        std::cout<<std::endl<<"The result of converting the number "<<input_number<<" from base "
        <<source_base<<" to "<<target_base<<" is: "<<std::endl<<">> "<<total_sum<<std::endl;
    }

    //10 to 2
    //10 to 16
    //A lot of remainder division.
    if((target_base == 2 || target_base == 16) && source_base == 10){
        //Initializes and declares workable_input which has the same value as our input_number.
        //Transforms our string input_number into a double using stod.
        double workable_input = std::stod(input_number);

        //Integral component
        //Initializes and declares a long long int to store a crazy number of digits for extra accuracy.
        //Explicitly typecast to long long int for less errors
        //floor to remove the fractional component, we don't need it for the integral calculations for now.
        long long int integral = (long long int) floor(workable_input);
        //Essentially an output buffer so we can print in reverse (most significant first).
        char converted [128];

        //Initializes and declares a index so we can use it in our print for the integral component.
        int i = 0;

        //Runs until we don't need to divide anymore as 0 will always give 0 as a remainder.
        while (integral > 0){
            //If we are going from base 10 to 2, this runs.
            if(target_base == 2){
                //set the value of converted at index i to the related numerical char
                converted[i]= integral%2 + '0';
            //If we are going from base 10 to 16, this runs.
            }else{
                //If the value we get is numerical
                if(integral%16<=9){
                    //set the value of converted at index i to the related numerical char
                    converted[i]= integral%16 + '0';
                //If the value we get is alphabetical
                }else{
                    //set the value of converted at index i to the related alphabetical char
                    converted[i]= integral%16 + 55;
                }
            }
            //Complete the division and replace value of integral with the divided number
            integral = integral/target_base;
            i++;
        }
        //Output for the integral portion of base 10 to 2 and base 10 to 16
        std::cout<<std::endl<<"The result of converting the number "<<input_number<<" from base "
        <<source_base<<" to "<<target_base<<" is: "<<std::endl<<">> ";

        //If there is no whole number value and only fractional, print 0
        if(floor(workable_input) == 0){
            std::cout<<0;
        //Otherwise, print integral part in reverse/correct order from our converted output buffer.
        }else{
            //Reverse print for integral component
            for (int j=i - 1; j>=0; j--){
                std::cout<<converted[j];
            }
        }

        //Fractional component
        //Initializes and declares fractional for the fractional component.
        //Get the value of the fractional component by subtracting the floored number from the input number
        double fractional = workable_input - floor(workable_input);

        //Runs if there is any value in fractional.
        if(fractional!=0){
            //Prints a decimal point
            std::cout<<".";
            //Use a overflow to catch infinite repeating fractions/excessively long fractions
            int overflow=0;
            //Runs fractional is not 0/empty/has zero value and while there are less than 12 digits in fractional part.
            while (fractional != 0 && overflow < 12){
                //Multiplies fractional part by the wanted base to get value for calculation
                fractional = fractional * target_base;
                //Runs when we need base 16 alpha chars.
                if(target_base == 16 && floor(fractional) > 9){
                    //Does a quick ASCII conversion to char and prints the correct alphabetical char.
                    std::cout<< (char) (floor(fractional) + 55);
                //Otherwise, we need numerical values and this runs.
                }else{
                    //Prints the int that we obtained.
                    std::cout<< (int) floor(fractional);
                }
                //We take the fractional component again and loop through.
                fractional = fractional - floor(fractional);
                overflow++;
            }
        }
        //For output spacing.
        std::cout<<std::endl;
    }

    //16 to 2
    if(target_base == 2 && source_base == 16){
        //Two "dictionaries" made using arrays. b is used in the first output for prettier formating.
        std::string a[16] = {"0000","0001","0010","0011","0100","0101","0110","0111","1000","1001","1010","1011","1100","1101","1110","1111"};
        std::string b[16] = {"","1","10","11","100","101","110","111","1000","1001","1010","1011","1100","1101","1110","1111"};
        
        //Output for base 16 to 2.
        std::cout<<std::endl<<"The result of converting the number "<<input_number<<" from base "
        <<source_base<<" to "<<target_base<<" is: "<<std::endl<<">> ";
        
        //Runs through entire input number.
        for(int i = 0; i < input_size; i++){
            //Checks for printing decimal points and zeros
            //Runs if we are at index 0 and there is a decimal point there. Prints char '0'.
            if(i==0 && input_number[i] == '.'){
                std::cout<<'0';
            }
            //Runs if we the index we are at has a decimal point and we are not at the last char element in the string. Prints char '.'.
            if(input_number[i]=='.' && i<input_size-1){
                std::cout<<'.';
            //Otherwise, this runs if input number is not a decimal point. 
            }else if(input_number[i]!='.'){
                //Runs if we are at index zero or if we are at the last char element and the last element is char '0'.
                //Basically for pretty output formatting. We use array b here.
                if(i==0 || (i==input_size-1 && input_number[input_size-1] == '0')){
                    //Some ASCII manipulations
                    //Runs if the char at current index is an upper-case alphabetical char.
                    if(65 <= input_number[i] && input_number[i] <= 70){
                        //Getting the coresponding strings using char/int and ASCII manipulations.
                        std::cout<<b[input_number[i] - 55];
                    //Otherwise, this runs if is an lower-case alphabetical char.
                    }else if (97 <= input_number[i] && input_number[i] <= 102) {
                        std::cout<<b[input_number[i] - 87];
                    }else{
                        std::cout<<b[input_number[i] - '0'];
                    }
                //Otherwise this runs.
                }else{
                    //Much like above but we don't care much about formatting so we use array a.
                    if(65 <= input_number[i] && input_number[i] <= 70){
                        std::cout<<a[input_number[i] - 55];
                    }else if (97 <= input_number[i] && input_number[i] <= 102) {
                        std::cout<<a[input_number[i] - 87];
                    }else{
                        std::cout<<a[input_number[i] - '0'];
                    }
                }
            }
        }
        //For output spacing.
        std::cout<<std::endl;
    }

    //2 to 16
    //Lots of ifs, else ifs and c style substrings
    if(source_base == 2 && target_base == 16){

        //Integral component
        //Initializes and declares an index in_quad so we can know if we are able to split our input number into substrings of 4 chars.
        //Only counts up to the decimal point or to the end of the inputed number.
        int in_quad = decimal_point_pos;

        //Initializes and declares a string set to the same as input_number so manipulation doesn't affect the input.
        std::string temp_s = input_number;
        
        //Runs while in_quad is not divisible by 4.
        while(in_quad%4 !=0){
            //Inserts a char '0' into the front of the temp_s string.
            temp_s.insert(0, 1 , '0');
            in_quad++;
        } 
        
        //Output for base 2 to 16.
        std::cout<<std::endl<<"The result of converting the number "<<input_number<<" from base "
        <<source_base<<" to "<<target_base<<" is: "<<std::endl<<">> ";

        //Runs until the decimal point or until the end of input number. Need to make sure that we can divide by 4 to split into substrings of length 4.
        for(int i = 0; i < in_quad; i+=4){
            //Declares a substring flag
            std::string flag;
            //Runs until it can grab 4 chars. 
            for(int j = 0; (j+i)<i+4; j++){
                //Grabs the chars at the correct index and inserts them into the flag.
                flag.insert(j, 1, temp_s[i+j]);
            }
            //A long if and else if statement for checking the substring flag for any simillar values.
            //If there is, print the corresponding hexadecimal value.
            if(flag.compare("0000")==0){
                std::cout<<'0';
            }else if(flag.compare("0001")==0){
                std::cout<<'1';
            }else if(flag.compare("0010")==0){
                std::cout<<'2';
            }else if(flag.compare("0011")==0){
                std::cout<<'3';
            }else if(flag.compare("0100")==0){
                std::cout<<'4';
            }else if(flag.compare("0101")==0){
                std::cout<<'5';
            }else if(flag.compare("0110")==0){
                std::cout<<'6';
            }else if(flag.compare("0111")==0){
                std::cout<<'7';
            }else if(flag.compare("1000")==0){
                std::cout<<'8';
            }else if(flag.compare("1001")==0){
                std::cout<<'9';
            }else if(flag.compare("1010")==0){
                std::cout<<'A';
            }else if(flag.compare("1011")==0){
                std::cout<<'B';
            }else if(flag.compare("1100")==0){
                std::cout<<'C';
            }else if(flag.compare("1101")==0){
                std::cout<<'D';
            }else if(flag.compare("1110")==0){
                std::cout<<'E';
            }else if(flag.compare("1111")==0){
                std::cout<<'F';
            }
        }

        //Fractional component
        //Initializes and declares an index frac_quad so we can know if we are able to split the fractional part of input number into substrings of 4 chars.
        int frac_quad = (input_size-decimal_point_pos)-1;
        //Runs if there is a fractional part. Runs if decimal_point_pos is not equal to input size and the last character of input_number is not a '.' char.
        if(decimal_point_pos!=input_size && input_number[input_size-1] != '.'){
            std::cout<<'.';
            //Runs while frac_quad is not divisible by 4. Need to make sure that we can divide by 4 to split into substrings of length 4.
            while(frac_quad%4 !=0){
                //Adds '0's to the end of temp_s.
                temp_s.append(1, '0');
                frac_quad++;
            } 
            
            //Runs until we reach the end of the fractional component. Starts at the first decimal place.
            for(int i = in_quad+1; i<(input_size+frac_quad)-1; i+=4){
                //Declares a substring flag
                std::string flag;
                //Runs until it can grab 4 chars. 
                for(int j=0; (j+i)<i+4; j++){
                    //Grabs the chars at the correct index and inserts them into the flag.
                    flag.insert(j, 1, temp_s[i+j]);
                }
                //Same situation as the integral component.
                if(flag.compare("0000")==0){
                    std::cout<<'0';
                }else if(flag.compare("0001")==0){
                    std::cout<<'1';
                }else if(flag.compare("0010")==0){
                    std::cout<<'2';
                }else if(flag.compare("0011")==0){
                    std::cout<<'3';
                }else if(flag.compare("0100")==0){
                    std::cout<<'4';
                }else if(flag.compare("0101")==0){
                    std::cout<<'5';
                }else if(flag.compare("0110")==0){
                    std::cout<<'6';
                }else if(flag.compare("0111")==0){
                    std::cout<<'7';
                }else if(flag.compare("1000")==0){
                    std::cout<<'8';
                }else if(flag.compare("1001")==0){
                    std::cout<<'9';
                }else if(flag.compare("1010")==0){
                    std::cout<<'A';
                }else if(flag.compare("1011")==0){
                    std::cout<<'B';
                }else if(flag.compare("1100")==0){
                    std::cout<<'C';
                }else if(flag.compare("1101")==0){
                    std::cout<<'D';
                }else if(flag.compare("1110")==0){
                    std::cout<<'E';
                }else if(flag.compare("1111")==0){
                    std::cout<<'F';
                }
            }
        }
        //For output spacing.
        std::cout<<std::endl; 
    }
    return 0;
}

int main(){

    //Declares and initializes ints convert_to and convert_from
    int convert_to, convert_from;
    //Declares and initializes char yes_no for continuing program or ending program at user's discretion
    char yes_no = 'Y';
    //Sets the number of printed output digits for ints, doubles, floats to 15.
    std::cout.precision(15);

    //Runs when user still wants to do more calculations i.e: yes_no = Y.
    while(yes_no == 'Y'){
        //Declares a string number_input to store user input.
        std::string number_input;

        //Printing out questions for user input
        std::cout<<std::endl<<"Please enter the following inputs:"<<std::endl;
        std::cout<<"The number to convert"<<std::endl<<">> ";
        //Takes input from user for the number that the user wants to change
        std::cin>>number_input;

        std::cout<<std::endl<<"The source base (i.e., the base to convert from)"<<std::endl<<">> ";
        //Takes input from user for the base that the user's number is in
        std::cin>>convert_from;

        //Runs while a non-valid base that is not 2, 10 or 16 is inputed and continues running until a valid number is entered
        while(convert_from!=16&&convert_from!=10&&convert_from!=2){
            std::cout<<std::endl<<"The source base (Please enter a valid base: 2, 10 or 16)"<<std::endl<<">> ";
            std::cin>>convert_from;
        }        
        
        //Runs while the user's inputed number is not valid or number base does not match the number.
        //Calls function validateInput to get if it is valid or not.
        while(!validateInput(number_input, convert_from)){
            std::cout<<std::endl<<"Invalid input, the number to convert or the source base is incorrect! Please try again:"<<std::endl;
            std::cout<<"The number to convert (No negatives!)"<<std::endl<<">> ";
            //Re-takes value for user's number (hopefully correct this time)
            std::cin>>number_input;
            std::cout<<std::endl<<"The source base (Please enter a valid base: 2, 10 or 16)"<<std::endl<<">> ";
            //Re-takes value for user's number's base (hopefully correct this time)
            std::cin>>convert_from;
        }
        
        std::cout<<std::endl<<"The target base (i.e., the base to convert to)"<<std::endl<<">> ";
        //Takes input from user for the base that the user wants their number to be in
        std::cin>>convert_to;

        //Runs while a non-valid base that is not 2, 10 or 16 is inputed and continues running until a valid number is entered
        while(convert_to!=16&&convert_to!=10&&convert_to!=2){
            std::cout<<std::endl<<"The target base (Please enter a valid base: 2, 10 or 16)"<<std::endl<<">> ";
            std::cin>>convert_to;
        }

        //Declares and initializes ints number_size and redundant
        int number_size = number_input.size(), redundant=0;

        //Counts the number of 0s and decimal points.
        for(int i = 0 ; i<number_size; i++){
            if(number_input[i] == '0' || number_input[i] == '.'){
                redundant++;
            }
        }
        
        //If the number's base and the base that the user wants to convert to is the same, just print the number that was inputed
        if(convert_from==convert_to){
            std::cout<<std::endl<<"The result of converting the number "<<number_input<<" from base "<<convert_from<<" to "<<convert_to
            <<" is: "<<std::endl<<">> "<<number_input<<std::endl;
        //Checks if number is redundant/can be written as 0 instead i.e. 0.00 <-> 0.
        //If a number has the same number of zeros and decimal points (redundant) as the length of the entire number, then it is a 0 equivalent number
        }else if(redundant == number_size){
            //Prints 0 because a 0 equivalent number doesn't need to be transformed into other bases.
            std::cout<<std::endl<<"The result of converting the number "<<0<<" from base "<<convert_from<<" to "<<convert_to
            <<" is: "<<std::endl<<">> "<<0<<std::endl;
        }else{
            //Some cleaning up of zeros for prettier outputs.
            //Removes any leading zeros using str.erase()
            while(number_input[0]=='0' && number_input[1]!='.'){
                number_input.erase(0, 1);
            }

            //Checks and removes any zeros without significant digits in the fractional component i.e: 1.000000 <-> 1
            number_size= number_input.size();
            int decimal_point_pos=0;
            //Starts from the decimal point and keeps going until the end of the number
            for(int i=0; i<number_size && number_input[i]!='.'; i++){
                decimal_point_pos++;
            }

            bool is_useful=false;
            //Checks for if the zeros are okay to be removed, if not, useful is set to true
            for(int i=number_size-1; i>decimal_point_pos && is_useful==false; i--){
                if(number_input[i]!='0'){
                    is_useful=true;
                }
            }

            //Knowing that the zeros are not important, removes them and cleans up input i.e: 1.000000 <-> 1.
            if(is_useful==false){
                //erases zeros after decimal point
                number_input.erase(decimal_point_pos);
                //std::cout<<"number_input after: "<<number_input<<std::endl;
            }
            //Finally, calling the function convert_number to convert the user inputed number
            convert_number(number_input, convert_from, convert_to);
        }

        //Printing out questions for user input
        std::cout<<"Do you wish to continue with other numbers?"<<std::endl<<"Enter 'Y' to continue"<<std::endl<<"Enter 'N' to quit"<<std::endl<<">> ";
        //User input into yes_no
        std::cin>>yes_no;

        //Runs and continues running when user does not give a valid input for yes_no
        while(yes_no != 'N' && yes_no != 'Y'){ 
            std::cout<<"Make sure to enter 'N' or 'Y', it is case-sensitive: ";
            //User input into yes_no
            std::cin>>yes_no;
        }

        //If the user does not want to do any more calculations/yes_no = N, this runs.
        if (yes_no == 'N'){
            //Prints a nice message and terminates the program
            std::cout<<std::endl<<"Quitting calculator, have a good day!"<<std::endl;
            return 0;     
        }
    } 
    return 0;
}
