#include <string>
// #ifndef _STRINGHANDLER_HPP_
// #define _STRINGHANDLER_HPP_
// 	#include "stringHandler.hpp"
// #endif

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
	int comd_counter;	   //sub command counter
	int * sub_counter;
/*
set redirect_read to 0b1
	redirect_write to 0b10
	pipe to 0b100
	muti-command to 0b1000
	quote to 0b10000
*/
	short * sub_status;
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
		sub_status = (short *)malloc(4 * sizeof(short));
		command_arr = (char ***)malloc(size);
		raw_command = (char *)malloc(strlen(string));
		strcpy(raw_command, string);		//copy the raw command string and store it to struct
		char * element;
		
		while(string < end){					//look through all the command string
			sub_size = 0;
			char ** argument = (char **)malloc(0x21);	//	
			while(string[0] == ' ' || string[0] == '&' || string[0] == '|'){
				++string;
			}
			element = string;
			while(1){
				sub_status[comd_counter] = 0;
				if(string[0] == '\0'){									//end of command processing
					char * tmp = string - 1;
					if(tmp[0] != ' ' && tmp[0] != '\0'){
						argument[sub_size] = element;
						++sub_size;
						if(sub_size % 4 == 0){
							argument = (char **)realloc(argument, 8 * (sub_size + 4) + 1);
						}
					}
					++string;
					break;
				}
				else if(string[0] == '|'){								//pipe processing
					sub_status[comd_counter] |= 0b100;
					string[0] = '\0';
					char * tmp = string - 1;
					if(tmp[0] != ' ' && tmp[0] != '\0'){
						argument[sub_size] = element;
						++sub_size;
						if(sub_size % 4 == 0){
							argument = (char **)realloc(argument, 8 * (sub_size + 4) + 1);
						}
					}
					++string;
					break;
				}
				else if(string[0] == '&' && string[1] == '&'){			//muti-command processing
					sub_status[comd_counter] |= 0b1000;
					string[0] = '\0';
					char * tmp = string - 1;
					if(tmp[0] != ' ' && tmp[0] != '\0'){
						argument[sub_size] = element;
						++sub_size;
						if(sub_size % 4 == 0){
							argument = (char **)realloc(argument, 8 * (sub_size + 4) + 1);
						}
					}
					++string;
					break;
				}
				else if(string[0] == '>' || string[0] == '<'){			//redirect processing
					if(string[0] == '>'){
						sub_status[comd_counter] |= 0b10;
					}
					else{
						sub_status[comd_counter] |= 0b1;
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
						++string;
						while(string[0] == ' '){
							++string;
						}
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
					while(string[0] == ' '){
						++string;
					}
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
					++string;
					while (string[0] == ' '){
						++string;
					}
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
				sub_status = (short *)realloc(sub_status, sizeof(short) * (comd_counter + 4));
			}
			
		}
	}

	~command(){
		free(sub_counter);
		free(sub_status);
		free(raw_command);
		for(int i = 0; i < comd_counter; ++i){
			free(command_arr[i][0]);
			free(command_arr[i]);
		}
		free(command_arr);
	}
};