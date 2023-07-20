# Tema 1 - IPv4_Address
Nume: Mateescu F. Viorel-Cristian

Grupa: 312 CB

# Overview
- This README provides an overview of the code and its functionality.
- The code is written in C and performs various tasks related to IP addresses and masks.
- Below is a breakdown of the code structure and the tasks it accomplishes.

# Code Structure
The code consists of several functions and a main function. Here is a brief description of each function:
- *binaryRepresentation(unsigned char n)*: This function prints the binary representation of a given unsigned char.
- *getByte(unsigned int IP, int n)*: This function extracts a specific byte from a given IP address.
- *createMask(int length)*: This function creates a mask of a specified length.
- *printIP(unsigned int IP)*: This function prints the IP address in the standard dotted decimal notation.
- *printTask1(unsigned int IP, unsigned int mask)*: This function prints the network IP address by applying the given mask to the IP address.
- *printTask2(unsigned int MSK_1)*: This function prints the mask in both octal and hexadecimal formats.
- *printTask3(unsigned int IP, unsigned int mask)*: This function prints the network IP address by applying the given mask to the IP address.
- *printTask4(unsigned int IP, unsigned int mask)*: This function prints the broadcast IP address by applying the bitwise NOT operation on the mask and OR operation on the IP address.
- *printTask5(unsigned int IP_1, unsigned int IP_2, unsigned int mask)*: This function compares the network IP addresses of two given IP addresses and prints "DA" if they are the same, and "NU" otherwise.
- *printTask6(unsigned int MSK_1)*: This function checks if the given mask is a contiguous mask and prints "DA" if it is, and "NU" otherwise.
- *printTask7(unsigned int MSK_1)*: This function prints the smallest contiguous mask that is greater than or equal to the given mask.
- *printTask8(unsigned int IP_1)*: This function prints the binary representation of the given IP address.
- *printTask9(unsigned int IP_2, unsigned int N)*: This function reads a number of IP addresses and masks from the user and prints the indices of the IP addresses that belong to the same network as the given IP address.
- *main()*: This is the main function that drives the execution of the program. It reads input from the user, calls the appropriate functions, and prints the results.

# Tasks
The code performs the following tasks:
- Task 0: Prints the given IP address and mask.
- Task 1: Prints the network IP address by applying the given mask to the IP address.
- Task 2: Prints the mask in octal and hexadecimal formats.
- Task 3: Prints the network IP address by applying the given mask to the IP address.
- Task 4: Prints the broadcast IP address by applying the bitwise NOT operation on the mask and OR operation on the IP address.
- Task 5: Compares the network IP addresses of two given IP addresses and prints the result.
- Task 6: Checks if the given mask is a contiguous mask and prints the result.
- Task 7: Prints the smallest contiguous mask that is greater than or equal to the given mask.
- Task 8: Prints the binary representation of the given IP address.
- Task 9: Reads a number of IP addresses and masks from the user and prints the indices of the IP addresses that belong to the same network as the given IP address.

# Input Format
The code expects input in the following format:
1. The number of sets of IP addresses and masks to process.
2. For each set, the following inputs are required:
- The first IP address.
- The mask length.
- The second IP address.
- The number of IP addresses and masks to compare.
3. For each comparison, the IP address and mask are provided.
  
# Output Format
The code produces output in the following format:
1. For each set, it prints the set number.
2. For each task, it prints the task number followed by the corresponding output.
3. The output is printed to the console.

# Conclusion
- This code provides a set of functions to perform various tasks related to IP addresses and masks.
- By following the input format and using the provided functions, you can easily manipulate and analyze IP addresses in your C programs.
