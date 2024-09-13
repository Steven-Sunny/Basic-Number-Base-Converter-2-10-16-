//2-10-16 Number Base Converter
//Steven Sun
#include <iostream>
#include <cctype>
#include <cmath>
#include <string>

//Checks for valid input
//An input is valid when the number provided has values that match the given source_base
//An input is valid when there are no extra decimal points and no special characters
bool validateInput(std::string input_number, int source_base){

    int count = 0;
    for(int i=0; i<input_number.size(); i++){
        if(source_base==2 && input_number[i]!='1' && input_number[i]!='0' && input_number[i]!='.'){
            return false;
        }
        else if(source_base==10 && !isdigit(input_number[i]) && input_number[i]!='.'){
            return false;
        }
        else if(!isxdigit(input_number[i]) && input_number[i]!='.'){
            return false;
        }

        // if(source_base==10 && input_number[i]!='9' && input_number[i]!='8' && input_number[i]!='7' && 
        // input_number[i]!='6' && input_number[i]!='5' && input_number[i]!='4' && input_number[i]!='3' && 
        // input_number[i]!='2' && input_number[i]!='1' && input_number[i]!='0' && input_number[i]!='.'){
        //     return false;
        // }

        // if(source_base==16 && input_number[i]!='F' && input_number[i]!='E' && 
        // input_number[i]!='D' && input_number[i]!='C' && input_number[i]!='B' && 
        // input_number[i]!='A' && input_number[i]!='9' && input_number[i]!='8' && 
        // input_number[i]!='7' && input_number[i]!='6' && input_number[i]!='5' &&
        // input_number[i]!='4' && input_number[i]!='3' && input_number[i]!='2' && 
        // input_number[i]!='1' && input_number[i]!='0' && input_number[i]!='.'){
        //     return false;
        // }
        //AHHHHHHHHHHHHHHHHHHHHHHHHHHH
        if(input_number[i]=='.'){
            count++;
        }
    }
    if(count > 1){
        return false;
    }
    return true;
    //std::cout<<input_number[i]<<std::endl;
    // if(source_base == 10){
    //     for(int i=0; i<input_number.size(); i++){
            
    //     }
    // }

    // if(source_base ==16){
    //     for(int i=0; i<input_number.size(); i++){
            
    //     }
    // }
}

//Converts between number bases (2, 10 or 16)

int convert_number(std::string input_number, int source_base, int target_base){    
    // double workable_input = std::stod(input_number);
    //unsigned long long int workable_input_int;
    int decimal_point_pos = 0;
    int input_size = input_number.size();
    bool is_fractional = false;
    double total_sum = 0;

    for(int i=0; i<input_size && input_number[i]!='.'; i++){
        decimal_point_pos = decimal_point_pos+1;
    }
    
    //2 to 10
    //16 to 10

    if((source_base == 2 || source_base == 16) && target_base == 10){

        //int fractions tracks what decimal place the iterator is at for negative exponentiation (keeping track of the iterator is difficult...)
        int fractions = -1;
        decimal_point_pos = input_size-decimal_point_pos;

        for(int i=0; i<input_size; i++){

            if(is_fractional){
                if(65 <= input_number[i] && input_number[i] <= 70){
                    total_sum = total_sum + (input_number[i]-55)*pow(source_base, fractions--);
                }else if (97 <= input_number[i] && input_number[i] <= 102) {
                    total_sum = total_sum + (input_number[i]-87)*pow(source_base, fractions--);
                }else{
                    total_sum = total_sum + (input_number[i]-'0')*pow(source_base, fractions--);
                }

            }else if (input_number[i]!='.'){
                if(65 <= input_number[i] && input_number[i] <= 70){
                    total_sum = total_sum + (input_number[i]-55)*pow(source_base, (input_size-(i+1))-decimal_point_pos);
                }else if (97 <= input_number[i] && input_number[i] <= 102) {
                    total_sum = total_sum + (input_number[i]-87)*pow(source_base, (input_size-(i+1))-decimal_point_pos);
                }else{
                    total_sum = total_sum + (input_number[i]-'0')*pow(source_base, (input_size-(i+1))-decimal_point_pos);
                }
            }

            if(input_number[i]=='.'){
                is_fractional=true;
            }
        }
        std::cout<<std::endl<<"The result of converting the number "<<input_number<<" from base "
        <<source_base<<" to "<<target_base<<" is: "<<std::endl<<">> "<<total_sum<<std::endl;
        return 0;
    }

    //10 to 2
    //10 to 16

    //2 to 16
    //16 to 2
    

    // while(floor(workable_input)!=workable_input){
    //     workable_input=workable_input*target_base;
    // }

    // workable_input_int= (unsigned long long int) workable_input;

    // while(workable_input_int % target_base){

    // }
    return 0;
}

int main(){

    char yes_no = 'Y';
    std::cout.precision(15);
    while(yes_no == 'Y'){

        int convert_to, convert_from;
        std::string number_input;
        std::cout<<std::endl<<"Please enter the following inputs:"<<std::endl;
        std::cout<<"The number to convert"<<std::endl<<">> ";
        std::cin>>number_input;

        std::cout<<std::endl<<"The source base (i.e., the base to convert from)"<<std::endl<<">> ";
        std::cin>>convert_from;

        while(convert_from!=16&&convert_from!=10&&convert_from!=2){
            std::cout<<std::endl<<"The source base (Please enter a valid base: 2, 10 or 16)"<<std::endl<<">> ";
            std::cin>>convert_from;
        }        
        
        while(!validateInput(number_input, convert_from)){
            std::cout<<std::endl<<"Invalid input, the number to convert or the source base is incorrect! Please try again:"<<std::endl;
            std::cout<<"The number to convert (No negatives!)"<<std::endl<<">> ";
            std::cin>>number_input;
            std::cout<<std::endl<<"The source base (Please enter a valid base: 2, 10 or 16)"<<std::endl<<">> ";
            std::cin>>convert_from;
        }
        
        std::cout<<std::endl<<"The target base (i.e., the base to convert to)"<<std::endl<<">> ";
        std::cin>>convert_to;

        while(convert_to!=16&&convert_to!=10&&convert_to!=2){
            std::cout<<std::endl<<"The target base (Please enter a valid base: 2, 10 or 16)"<<std::endl<<">> ";
            std::cin>>convert_to;
        }
        
        if(convert_from==convert_to){
            std::cout<<std::endl<<"The result of converting the number "<<number_input<<" from base "<<convert_from<<" to "<<convert_to
            <<" is: "<<std::endl<<">> "<<number_input<<std::endl;
        }else{
            convert_number(number_input, convert_from, convert_to);
        }

        std::cout<<"Do you wish to continue with other numbers?"<<std::endl<<"Enter 'Y' to continue"<<std::endl<<"Enter 'N' to quit"<<std::endl<<">> ";
        std::cin>>yes_no;

        while(yes_no != 'N' && yes_no != 'Y'){ 
            std::cout<<"Make sure to enter 'N' or 'Y', it is case-sensitive: ";
            std::cin>>yes_no;
        }

        if (yes_no == 'N')
        {
            std::cout<<std::endl<<"Quitting calculator, have a good day!"<<std::endl;
            return 0;     
        }
    } 
    return 0;
}