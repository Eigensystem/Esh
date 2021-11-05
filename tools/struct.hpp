#include <string>
#ifndef _STRINGHANDLER_HPP_
#define _STRINGHANDLER_HPP_
	#include "stringHandler.hpp"
#endif

struct file_data{
	char * dir_path;	//not including /
	char * file_name;   //pure name
};

struct shell{
	char ** dir;
	int dir_count;
	char * workdir;
};

class command{
public:
	bool redirect;
	bool readorwrite;	   //operate read 0 , operate write 1
	bool pipe;
	bool quote;
	int comd_counter;	   //sub command counter
	int * sub_counter;
	char * raw_command;
	char *** command_arr;   //first layer : sub command in a command if use pipe
						//second layer: arguments array in a sub command
						//third layer : arguments string
	command(char * string){
		comd_counter = 0;		  //sub command calculater
		int sub_size;			  //single sub command's argument's number
		int size = 0x21;			   //size of pointer of every sub command
		void * end = string + strlen(string);   //sign of the end of command string
		sub_counter = (int *)malloc(4 * sizeof(int));	 //alloc mem to the counter arr of all the sub command
		command_arr = (char ***)malloc(size);
		raw_command = (char *)malloc(strlen(string));
		strcpy(raw_command, string);		//copy the raw command string and store it to struct
		string = crossfront(string, ' ');   //ignore all the SPACE in front of the command string
		char * element = string;
		
		while(string < end){					//look through all the command string
			sub_size = 0;
			char ** argument = (char **)malloc(0x21);	//	
			while(string[0] == ' ' || string[0] == '&' || string[0] == '|'){
				++string;
			}
			element = string;
			while(1){
				if(string[0] == '\0'){
					argument[sub_size] = element;
					element = string;
					++sub_size;
					if(sub_size % 4 == 0){
						argument = (char **)realloc(argument, 8 * (sub_size + 4) + 1);
					}
					break;
				}
				else if(string[0] == '|'){
					pipe = 1;
					string[0] = '\0';
					argument[sub_size] = element;
					++sub_size;
					if(sub_size % 4 == 0){
						argument = (char **)realloc(argument, 8 * (sub_size + 4) + 1);
					}
					break;
				}
				else if(string[0] == '&' && string[1] == '&'){
					break;
				}
				else if(string[0] == '>' || string[0] == '<'){
					redirect = 1;
					if(string[0] == '>'){
						readorwrite = 1;
					}
					else{
						readorwrite = 0;
					}

					string[0] = '\0';
					char * tmp = string - 1;
					if(tmp[0] != ' ' && tmp[0] != '\0'){
						argument[sub_size] = element;
						++sub_size;
						if(sub_size % 4 == 0){
							argument = (char **)realloc(argument, 8 * (sub_size + 4) + 1);
						}
					}

					if(string[1] == ' '){
						string = crossfront(string+1, ' ');
						element = string;
					}
					else{
						++string;
						element = string;
					}

					while(string[0] != '\0' && string[0] != ' ' && string[0] != '|' && (string[0] != '&' || string[1] != '&')){
						++string;
					}
					string[0] = '\0';
					++string;
					argument[sub_size] = element;
					++sub_size;
					if(sub_size % 4 == 0){
						argument = (char **)realloc(argument, 8 * (sub_size + 4) + 1);
					}
					break;
				}
				

				++string;

				if(string[0] == ' '){
					string[0] = '\0';
					string = crossfront(string + 1, ' ');
					argument[sub_size] = element;
					element = string;
					++sub_size;
					if(sub_size % 4 == 0){
						argument = (char **)realloc(argument, 8 * (sub_size + 4) + 1);
					}
				}
			}
			argument[sub_size] = nullptr;
			command_arr[comd_counter] = argument;
			sub_counter[comd_counter] = sub_size;
			++comd_counter;
			if(comd_counter % 4 == 0){
				size += 0x20;
				command_arr = (char ***)realloc(command_arr, size);
				sub_counter = (int *)realloc(sub_counter, sizeof(int) * (comd_counter + 4));
			}
			
		}
	}
};