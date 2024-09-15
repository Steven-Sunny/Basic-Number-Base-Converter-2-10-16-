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

    if(input_number.size()<1){
        return false;
    }

    int count = 0;
    for(unsigned int i=0; i<input_number.size(); i++){
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
    }

    //10 to 2
    //10 to 16

    if((target_base == 2 || target_base == 16) && source_base == 10){
        double workable_input = std::stod(input_number);
        //integral component 
        long long int integral = (int) floor(workable_input);
        char converted [128];

        int i = 0;
        while (integral > 0){
            if(target_base == 2){
                converted[i]= integral%2 + '0';
            }else{
                if(integral%16<=9 && integral%16>=0){
                    converted[i]= integral%16 + '0';
                }else{
                    converted[i]= integral%16 + 55;
                }
            }
            integral = integral/target_base;
            i++;
        }
        std::cout<<std::endl<<"The result of converting the number "<<input_number<<" from base "
        <<source_base<<" to "<<target_base<<" is: "<<std::endl<<">> ";

        if(floor(workable_input) == 0){
            std::cout<<0;
        }else{
            //reverse print for integral component
            for (int j=i - 1; j>=0; j--){
                std::cout<<converted[j];
            }
        }

        //fractional component
        double fractional = workable_input - floor(workable_input);
        if(fractional!=0){
            std::cout<<".";
            //use a overflow to catch infinite repeating fractions/excessively long fractions
            int overflow=0;
            while (fractional != 0 && overflow < 12){
                fractional = fractional * target_base;
                if(target_base == 16 && floor(fractional) > 9){
                    std::cout<< (char) (floor(fractional) + 55);
                }else{
                    std::cout<< (int) floor(fractional);
                }
                fractional = fractional - floor(fractional);
                overflow++;
            }
        }
        std::cout<<std::endl;
    }

    //16 to 2
    if(target_base == 2 && source_base == 16){
    //two "dictionaries" made using arrays. b is used in the first output for prettier formating
    std::string a[16] = {"0000","0001","0010","0011","0100","0101","0110","0111","1000","1001","1010","1011","1100","1101","1110","1111"};
    std::string b[16] = {"","1","10","11","100","101","110","111","1000","1001","1010","1011","1100","1101","1110","1111"};
    
    std::cout<<std::endl<<"The result of converting the number "<<input_number<<" from base "
    <<source_base<<" to "<<target_base<<" is: "<<std::endl<<">> ";

        for(int i = 0; i < input_size; i++){
            if(i==0 && input_number[i] == '.'){
                std::cout<<'0';
            }
            if(input_number[i]=='.' && i<input_size-1){
                std::cout<<'.';
            }else if(input_number[i]!='.'){
                if(i==0 || (i==input_size-1 && input_number[input_size-1] == '0')){
                    if(65 <= input_number[i] && input_number[i] <= 70){
                        std::cout<<b[input_number[i] - 55];
                    }else if (97 <= input_number[i] && input_number[i] <= 102) {
                        std::cout<<b[input_number[i] - 87];
                    }else{
                        std::cout<<b[input_number[i] - '0'];
                    }
                }else{
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
        std::cout<<std::endl;
    }
    //2 to 16

    if(source_base == 2 && target_base == 16){
        //integral component
        int in_quad = input_size;

        if (decimal_point_pos!=input_size){
            in_quad = -(decimal_point_pos-input_size);
        }

        std::string temp_s = input_number;
        
        while(in_quad%4 !=0){
            temp_s.insert(0, 1 , '0');
            in_quad++;
        } 
        
        std::cout<<std::endl<<"The result of converting the number "<<input_number<<" from base "
        <<source_base<<" to "<<target_base<<" is: "<<std::endl<<">> ";
        for(int i = 0; i < in_quad; i+=4){
            std::string flag;
            for(int j = 0; (j+i)<i+4; j++){
                flag.insert(j, 1, temp_s[j+i]);
            }
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
        //fractional component

        std::cout<<std::endl; 
    }
    return 0;
}

int main(){

    int convert_to, convert_from;
    char yes_no = 'Y';
    std::cout.precision(15);
    while(yes_no == 'Y'){

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

        int number_size = number_input.size(), redundant=0;

        for(int i = 0 ; i<number_size; i++){
            if(number_input[i] == '0' || number_input[i] == '.'){
                redundant++;
            }
        }
        
        if(convert_from==convert_to){
            std::cout<<std::endl<<"The result of converting the number "<<number_input<<" from base "<<convert_from<<" to "<<convert_to
            <<" is: "<<std::endl<<">> "<<number_input<<std::endl;
        }else if(redundant == number_size){
            std::cout<<std::endl<<"The result of converting the number "<<0<<" from base "<<convert_from<<" to "<<convert_to
            <<" is: "<<std::endl<<">> "<<0<<std::endl;
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
