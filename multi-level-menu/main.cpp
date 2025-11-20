#include <iostream>

int main() {
	int user_input;
	do {
		std:: cout << "Приветственный текст" << std:: endl ;
       		std:: cout << "1 - я хочу учиться математике" << std:: endl ;
        	std:: cout << "0 - я просто хочу пожить" << std:: endl ;
	        std:: cout << "Обучайка:" << std:: endl ;

		std:: cin >> user_input;

		if (user_input){
			std:: cout << "вперед !";
		} 
		else {
			exit(0);
		}

		std:: cout << std:: endl;
	} while(true);

	return 0;
}
