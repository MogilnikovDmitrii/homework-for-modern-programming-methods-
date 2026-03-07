#include "long_numbers.hpp"
#include <algorithm>
#include <cmath>
using DmMog::LongNumber;
		
LongNumber::LongNumber() : numbers(new int[1]{0}), length(1), sign(1) {}

LongNumber::LongNumber(LongNumber&& x) noexcept : numbers(x.numbers), length(x.length), sign(x.sign) {
    x.numbers = nullptr;
    x.length = 0;
    x.sign = 1;
}

LongNumber::~LongNumber() {
	delete[] numbers;
}


LongNumber::LongNumber(int value) {
    if(value == 0){
        init_zero();
        return;
    }
	int rank = 0,pow = 1;
    if(value >= 0){
        sign = 1;
    } else{
        sign = -1;
    }

    if(value < 0){
        value *= -1;
    }
    while ( value - pow >= 0)
    {
        rank++;
        pow *= 10;
    }
    length = rank;
    numbers = new int[rank]();
    rank = 0;
    pow = 1;
    while (rank < length)
    {
        numbers[rank] = (value/pow)%10;
        rank ++;
        pow *= 10;
    }
    
    
}

LongNumber::LongNumber(const char* const str) {
    int len = get_length(str);
    if(len == 0){
        numbers = new int[1]{0};
        length = 1;
        sign = 1;
        return;
    }
    length = len;

    int ind = 0;
    sign = 1;

    if(str[ind] == '+'){
        ind++;
    } else if(str[ind] == '-'){
        sign = -1;
        ind++;
    }

    while(str[ind] == '0'){
        ind++;
    }

    numbers = new int[len];
    for(int j = 0; j < len; j++){
        numbers[j] = str[ind + len - 1 - j] - '0';  
    }

}
LongNumber::LongNumber(const LongNumber& x) {
    length = x.length;
    sign = x.sign;
    numbers = new int[length];

    for (int i = 0; i < length; ++i){
        numbers[i] = x.numbers[i];
    }
}




LongNumber& LongNumber::operator = (const char* const str) {
	LongNumber temp(str);
    *this = temp;
    return *this;
}

LongNumber& LongNumber::operator = (const LongNumber& x) {
	if (this == &x){
        return *this;
    }
    delete[] numbers;
    
    length = x.length;
    sign = x.sign;

    numbers = new int[length];

    for(int j = 0; j < length; j++){
        numbers[j] = x.numbers[j];
    }

    return *this;
}

LongNumber& LongNumber::operator = (LongNumber&& x) noexcept {
	if (this == &x){
        return *this;
    }

    delete[] numbers;

    length = x.length;
    sign = x.sign;
    numbers = x.numbers;

    x.numbers = nullptr;
    x.length = 0;
    x.sign = 1;

    return *this;

}

bool LongNumber::operator == (const LongNumber& x) const {
	if (x.length != length || x.sign != sign ){
        return false;
    }

    for(int i = 0; i < length ; i++){
        if (numbers[i] != x.numbers[i]){
            return false;
        }
    }
    return true;
}

bool LongNumber::operator != (const LongNumber& x) const {
	if(x == *this){
        return false;
    } else {
        return true;
    }
}

bool LongNumber::operator > (const LongNumber& x) const {
	if (x == *this) {
        return false;
    }

    if (sign > x.sign){
        return true;
    } else if (sign < x.sign){
        return false;
    }

    if (sign > 0){
        if (length > x.length){
            return true;
        } else if (length < x.length){
            return false;
        }
    } else{
        if (length > x.length){
            return false;
        } else if (length < x.length){
            return true;
        }
    }
    
    for (int i = length -1 ; i >= 0 ; i--){
        if( numbers[i] > x.numbers[i]){
            if (sign > 0){
                return true;
            } else{
                return false;
            }
        }
        if( numbers[i] < x.numbers[i]){
            if (sign > 0){
                return false;
            } else{
                return true;
            }
        }
    }
    return false;
    
}

bool LongNumber::operator < (const LongNumber& x) const {
	if (*this == x){
        return false;
    }
    if(*this > x){
        return false;
    }else {
        return true;
    }
}

LongNumber LongNumber::operator + (const LongNumber& x) const {
    if (sign == x.sign){
        int length_of_summ = std::max(length,x.length) + 1;
	    int* numbers_of_summ = new int[length_of_summ]();

        for (int i = 0; i < length_of_summ;i++){
            if(length >= i+1){
                numbers_of_summ[i] += numbers[i];
            }
            if(x.length >= i+1){
                numbers_of_summ[i] += x.numbers[i];
            }
            if(numbers_of_summ[i] >= 10){
                numbers_of_summ[i+1] +=1;
                numbers_of_summ[i] -= 10;
            }
        }
        DmMog::LongNumber Summ;
        if(numbers_of_summ[length_of_summ -1] == 0){
            length_of_summ -= 1 ;
        }
        Summ.length = length_of_summ;
        Summ.numbers = new int[length_of_summ];
        Summ.sign = sign;

        for(int i = 0; i < length_of_summ;i++){
            Summ.numbers[i] = numbers_of_summ[i];
        }
        delete[] numbers_of_summ;
        return Summ;
    } else {
        if(x.sign == -1){
            return *this - x.change_of_sign();
        } else {
            return x - change_of_sign();
        }
    }
}

LongNumber LongNumber::operator - (const LongNumber& x) const {
    if(x == *this) return LongNumber("0");

    if(sign != x.sign){
        return *this + x.change_of_sign();
    }

    LongNumber a = module();
    LongNumber b = x.module();
    int length_of_subt = std::max(a.length, b.length);
    int* numbers_of_subt = new int[length_of_subt]();

    bool result_negative = (sign < 0);
    if(b > a){
        std::swap(a, b);
        result_negative = !result_negative;
    }

    for(int i = 0; i < length_of_subt; i++){
        int b_digit = 0;
        if(i < b.length) {
            b_digit = b.numbers[i];
        }
        if(a.numbers[i] >= b_digit){
            numbers_of_subt[i] = a.numbers[i] - b_digit;
        } else {
            numbers_of_subt[i] = a.numbers[i] + 10 - b_digit;
            int j = i+1;
            while(a.numbers[j] == 0){
                a.numbers[j] = 9;
                j++;
            }
            a.numbers[j] -= 1;
        }
    }

    for(int i = length_of_subt -1; i > 0;i--){
        if(numbers_of_subt[i] == 0){
            length_of_subt -=1; 
        } else { break; 
        }
    }

    LongNumber Subt;
    Subt.length = length_of_subt;
    Subt.numbers = new int[length_of_subt];
    if(result_negative){
        Subt.sign = -1;
    }
    for(int i = 0; i < length_of_subt; i++){
        Subt.numbers[i] = numbers_of_subt[i];
    }

    delete[] numbers_of_subt;
    return Subt;
}


LongNumber LongNumber::operator * (const LongNumber& x) const {
    int length_of_prod = length + x.length;
    int* numbers_of_prod = new int[length_of_prod]();

    for(int i = 0; i < length; i++) {
        for(int j = 0; j < x.length; j++) {
            numbers_of_prod[i + j] += numbers[i] * x.numbers[j];
        }
    }

    for(int i = 0; i < length_of_prod - 1; i++) {
        if(numbers_of_prod[i] >= 10) {
            numbers_of_prod[i+1] += numbers_of_prod[i] / 10;
            numbers_of_prod[i] %= 10;
        }
    }

     for(int i = length_of_prod -1; i > 0;i--){
        if(numbers_of_prod[i] == 0){
            length_of_prod -=1; 
        } else { break; 
        }
    }

    LongNumber Prod;
    Prod.length = length_of_prod;
    Prod.numbers = new int[length_of_prod];
    Prod.sign = sign * x.sign;

    for(int i = 0; i < length_of_prod; i++) {
        Prod.numbers[i] = numbers_of_prod[i];
    }

    delete[] numbers_of_prod;
    return Prod;
}
LongNumber LongNumber::operator / (const LongNumber& x) const {
	if(x.module() == module()) {
        if(sign == x.sign){
            return 1;
        } else{
            return -1;
        }
    }
    if(x.module() > module()) {
        return 0;
    }
    int length_of_div = length;
    int* numbers_of_div = new int[length_of_div]();
    LongNumber remainder = 0;

    for(int i = length-1; i >= 0; i--)
    {
        remainder = remainder * 10;
        LongNumber digit(numbers[i]);
        remainder = remainder + digit;

        for(int j = 9; j >= 0; j--)
        {
            LongNumber d(j);

            if(x.module() * d < remainder or x.module() * d == remainder)
            {
                numbers_of_div[i] = j;
                remainder = remainder - x.module() * d;
                break;
            }
        }
    }
    for(int i = length_of_div -1; i > 0;i--){
        if(numbers_of_div[i] == 0){
            length_of_div -=1; 
        } else { break; 
        }
    }
    LongNumber Div;
    Div.length = length_of_div;
    Div.numbers = numbers_of_div;
    if(*this < 0 && (module() - x.module()*Div) != 0){
        Div = Div + 1;
    }
    Div.sign = sign * x.sign;
 
    return Div;

}

LongNumber LongNumber::operator % (const LongNumber& x) const {
    LongNumber a = *this - x * (*this / x);
    // if(a < LongNumber("0")){
    //     a = a + x.module();
    // }
	return a;
}


bool LongNumber::is_negative() const noexcept {
	return sign < 0;
}
LongNumber LongNumber::change_of_sign() const noexcept {
	LongNumber result(*this);  
    result.sign *= -1;           
    return result;
}

LongNumber LongNumber::module() const noexcept {
	LongNumber result(*this);  
    result.sign = 1;           
    return result;
}

// ----------------------------------------------------------
// PRIVATE
// ----------------------------------------------------------
int LongNumber::get_length(const char* const str) const noexcept {
	if (!str || str[0] == '\0'){
        return 0;
    }

    int ind = 0;

    if (str[0] == '+' || str[0] == '-'){
        ind++;
    }

    while(str[ind] == '0'){
        ind++;
    }

    int start = ind;

    while(str[ind] >= '0' && str[ind] <= '9'){
        ind++;
    }

    int len = ind - start;

    if(len == 0){
        return 0;
    }

    return len;
}
void LongNumber::init_zero() {
    numbers = new int[1]{0};
    length = 1;
    sign = 1;
}

// ----------------------------------------------------------
// FRIENDLY
// ----------------------------------------------------------
namespace DmMog {
    std::ostream& operator<<(std::ostream& os, const LongNumber& x) {
    if(!x.numbers || x.length == 0) {
        os << "0";
        return os;
    }
    if (x.sign < 0) os << '-';
    for (int i = x.length - 1; i >= 0; --i) {
        os << x.numbers[i];
    }
    return os;
    }
}


// int main() {
//     DmMog:: LongNumber a = 10;
//     DmMog:: LongNumber b = 140;

    
//     std::cout << a + b ;
// }