#include <iostream>
#include <string>

//the following section is used to define each of the program's function signatures - the actual functions are defined later in the code
//if we dont declare the functions signatures here we would have to define each of the functions before we call them
//each signature MUST match the actual function's call - so for example, the menu function does not expect any parameters to be passed to it and does
//not expect any parameters to be returned from the function; this is the same setup as quit
//however, the convert_to_option function expects to be given a string (called response) and to return an int value
void menu();
void quit();
int convert_to_option(std::string response);
std::string get_response(std::string message);
std::string getraw(void);
std::string getencrypted(void);
std::string encryptcaesar(std::string raw);
std::string encryptxor(std::string raw);
std::string decryptcaesar(std::string encrypted);
std::string decryptxor(std::string encrypted);


int main() {
	//in C++, the main function is automatically executed when the program is run
	std::cout << "\nCaesar & XOR Cipher Encryption"; //display the program name to the user
	menu(); //call (e.g. execute the menu function)
}


void menu() {
	//this function causes the system to present the user with all the menu options
	std::string raw = "";
	std::string encrypted = "";
	std::string decrypted = "";
	std::string userresponse = "";
	int option = -1;

	bool repeat = true; //set a boolean variable to act as a flag to keep the menu running

	while (repeat) { //keep repeating this code block while the flag is true
		std::cout << std::endl; //display a number of options to the user
		std::cout << std::endl << "\t1. Enter a 'raw' string";
		std::cout << std::endl << "\t2. Enter an 'encrypted' string";
		std::cout << std::endl; //display a blank line
		std::cout << std::endl << "\t3. Encrypt the current 'raw' string using a Caesar cipher";
		std::cout << std::endl << "\t4. Encrypt the current 'raw' string using a XOR cipher";
		std::cout << std::endl; //display a blank line
		std::cout << std::endl << "\t5. Decrypt the current 'encrypted' string using a Caesar cipher";
		std::cout << std::endl << "\t6. Decrypt the current 'encrypted' string using a XOR cipher";
		std::cout << std::endl << "\n\t0. Exit";

		std::cout << std::endl << std::endl << "\tCurrent (raw) string: \033[0;32m" << raw << "\033[0m"; //display the current raw string
		std::cout << std::endl << "\tCurrent (encrypted) string: \033[0;33m" << encrypted << "\033[0m"; //display the current encrypted string
		std::cout << std::endl << "\tCurrent (decrypted) string: \033[0;34m" << decrypted << "\033[0m"; //display the current decrypted string

		//call the get_response function and pass it a message to show to the user
		userresponse = get_response("\n\n\nPlease select an option (1 - 6, or 0 to exit): ");
		option = convert_to_option(userresponse);//convert the data from the user to a valid option
		
		//this code block checks the option against the functions, if it matches one it calls that function
		if(option == 0) { quit(); }
		else if (option == 1) { raw = getraw(); } //get a 'raw' unencrypted string from the user 
		else if (option == 2) { encrypted = getencrypted(); } //get an encrypted string from the user
		else if (option == 3) { encrypted = encryptcaesar(raw); } // use the caesar function to encypt the 'raw' string
		else if (option == 4) { encrypted = encryptxor(raw); } //use the xor function to encrypt the 'raw' string
		else if (option == 5) { decrypted = decryptcaesar(encrypted); } //use the caesar decryption function to convert an ecrypted string
		else if (option == 6) { decrypted = decryptxor(encrypted); } //use the xor decryprion function to convert an encrypted string
		else {
			//the option selected did not match any valid functions
			std::cout << "- Sorry, that was an invalid option - please try again.";
		}
	}
}


std::string get_response(std::string message) {
	//this function askes the user to provide some information
	std::string response; //declare a variable to hold the user response
	std::cout << message; //output the provided message
	getline (std::cin, response); //get the user's input
	return response; //return the response
}


int convert_to_option(std::string response) {
	//this function expects a string and returns its int value
	int option = -1;
	bool isnumber = true;

	for(int i = 0; i < response.length(); i++) { //iterate through each letter in the sting and check it is a digit
		if(isdigit(response[i]) == false) { //we seem to have found a 'non' digit - this means we can't convert the string
			isnumber = false; //set a flag so that we don't try to convert the string
		}
	}	
	if(isnumber == true) { //check to see if we have a valid string - e.g. it does not contain any 'non' digit characters
		option = stoi(response); //use the stoi function to convert the string to int
	}
	return option; //return the value of option 
}


void quit() {
	std::string response = get_response("Quit, are you sure (y/n): ");
	if(response == "y" || response == "Y") {
		std::cout << "Quitting...\n\n"; //output the exitting message
		exit(EXIT_SUCCESS);
	}
}


std::string getraw(void) {
	//this function returns a 'raw' user provided string
	std::string data = "";
	data = get_response("Enter a 'raw' (e.g. unencrypted) string: ");
	return data;
}


std::string getencrypted(void) {
	//this function returns an 'encrypted' user provided string
	std::string data = "";
	data = get_response("Enter an exiting 'encrypted' string: ");
	return data;
}


std::string encryptcaesar(std::string raw) {
	//this function returns an caesar 'encrypted' version of the 'raw' string
	std::string data = "";

	for (int i=0;i<raw.length();i++) { //iterate through each character
		//because ascii upper and lower case characters have different values we need to adjuct the shift
		if (isupper(raw[i])) { //deal with uppercase; an example ascii table can be found at: http://www.asciitable.com - however the are many others
			data += char( int(raw[i] +3 -65) %26 +65 ); //apply a 'shift' of 3 - dont forget ascii uppercase 'A' is 65 
		} else { //deal with lowercase
			data += char( int(raw[i] +3 -97) %26 +97 ); //apply a 'shift' of 3 - dont forget ascii lowercase 'a' is 97
		}
	} 
	return data;
}


std::string encryptxor(std::string raw) {
	//this function returns an xor 'encrypted' version of the 'raw' string
	char xorKey = 'K'; //Any char will work
	std::string data = "";

	data = raw; //initialise the data string to be the same as the raw
	for (int i = 0; i < raw.length(); i++) { //step through each character in the raw string
		data[i] = raw[i] ^ xorKey; //encrypt the current character using the value of the xorkey
	}
	return data; //return the now encrypted version of the raw string
}


std::string decryptcaesar(std::string encrypted) {
	//this function returns an decrypted version of a caesar 'encrypted' string
	std::string data = "";

	for (int i=0;i<encrypted.length();i++) { //iterate through each character
		//because ascii upper and lower case characters have different values we need to adjuct the shift
		if (isupper(encrypted[i])) { //deal with uppercase; an example ascii table can be found at: http://www.asciitable.com - however the are many others
			data += char( int(encrypted[i] -3 -65) %26 +65 ); //apply a 'shift' of 3 - dont forget ascii uppercase 'A' is 65 
		} else { //deal with lowercase
			data += char( int(encrypted[i] -3 -97) %26 +97 ); //apply a 'shift' of 3 - dont forget ascii lowercase 'a' is 97
		}
	} 
	return data;
}


std::string decryptxor(std::string encrypted) {
	//this function returns an decrypted version of an xor 'encrypted' string
	char xorKey = 'K'; //Any char will work
	std::string data = "";

	data = encrypted; //initialise the data string to be the same as the encrypted string
	for (int i = 0; i < encrypted.length(); i++) { //step through each character in the encrypted string
		data[i] = encrypted[i] ^ xorKey; //decrypt the current character using the value of the xorkey
	}
	return data; //return the now decrypted version of the encrypted string
}
