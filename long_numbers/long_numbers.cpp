#include "long_numbers.hpp"

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

// LongNumber LongNumber::operator + (const LongNumber& x) const {
// 	// TODO
// }

// LongNumber LongNumber::operator - (const LongNumber& x) const {
// 	// TODO
// }

// LongNumber LongNumber::operator * (const LongNumber& x) const {
// 	// TODO
// }

// LongNumber LongNumber::operator / (const LongNumber& x) const {
// 	// TODO
// }

// LongNumber LongNumber::operator % (const LongNumber& x) const {
// 	// TODO
// }

bool LongNumber::is_negative() const noexcept {
	return sign < 0;
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