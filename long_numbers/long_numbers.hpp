#pragma once 

#include <iostream>

namespace DmMog {
	class LongNumber {
		private:
			int* numbers;
			int length;
			int sign;


            
		
		public:
			LongNumber();
			LongNumber(const char* const str);
			LongNumber(int value);
			LongNumber(const LongNumber& x);
			LongNumber(LongNumber&& x) noexcept;
			
			~LongNumber();
			
			LongNumber& operator = (const char* const str);
			LongNumber& operator = (const LongNumber& x);
			LongNumber& operator = (LongNumber&& x)noexcept;
			
			bool operator == (const LongNumber& x) const;
			bool operator != (const LongNumber& x) const;
			bool operator > (const LongNumber& x) const;
			bool operator < (const LongNumber& x) const;
			
			LongNumber operator + (const LongNumber& x) const;
			LongNumber operator - (const LongNumber& x) const;
			LongNumber operator * (const LongNumber& x) const;
			LongNumber operator / (const LongNumber& x) const;
			LongNumber operator % (const LongNumber& x) const;
			
			bool is_negative() const noexcept;
			LongNumber module() const noexcept;
			LongNumber change_of_sign()const noexcept;
			
			
			friend std::ostream& operator << (std::ostream &os, const LongNumber& x);
			
		private:
			int get_length(const char* const str) const noexcept;
            void init_zero();
	};
}