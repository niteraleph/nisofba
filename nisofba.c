#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>

int i; //obviously used in for functions. The problem is, I think sometimes I've used the inside function, which isn't great I think... TODO: make sure everything is what I regard as proper
int w; //same as w but for while functions;
unsigned long l; //Used in readConsoleArguments for the purpose of a counter. Don't change as for now
char *source_path; //Consider changing var name to something else, like source_file_path or file_to_backup_path.
char destination_path[] = "./backup_file.txt"; //destination path, obviously, should be changable
char add_operation[] = {'a','d','d','\0'}; //string containing add to list function
char *_current_file_content; //pointer
char chosen_operation[100]; //size of operation option word size. I guess it can be fixed.
char *buffer_file; //This is a pointer to a block in memory containing the read file content. It's a
off_t source_size;
struct stat stbuf; //consider renaming
int argv_length[10];


//List and declarations of all function. No definitions.
void fillArr(char targetArr[], char filler, int arrSize);
void readConsoleArguments();
int getArgvLength();
void getSourceFromArgument();
void readFile();
void addToList();
void createBackupFile(); 
int compare_char_arr(char array1[], char array2[], int length);



int main(int argc, char *argv[])
{
	readConsoleArguments(argc, argv); //needs to work better
	printf("%s", chosen_operation);
	//printf("starting the main function"); 
	readFile(); //currently uses fixed path TODO: make it use the source path. 
	createBackupFile(); //Not sure if 100% correct because of string
	return 0;
}





void fillArr(char targetArr[],char filler, int arrSize)
{
	for(i=0;i<arrSize;i++)
	{
		targetArr[i] = filler;
	}
}

void readConsoleArguments(int argument_number, char *argumentContent[]) //VERY UNFINISHED FUNCTION TODO: make it work properly
{
	//VERY BAD LOOKING SOLUTION - BUT IT ACTUALLY WORKS, SO JUST GONNA LEAVE IT
	l=0;
	w=0;
	fillArr(chosen_operation,'%',sizeof(chosen_operation));
	argv_length[1] = getArgvLength(1, argumentContent);
	while(w <= argv_length[1])
	{
		chosen_operation[w] = argumentContent[1][w];//argument content probably stores all argument strings, for the first dimension 0 is first word, 1 is second word (thus first argument) and so on.. 
		w++;
	}
	//END OF THIS INELEGANT SOLUTION
	getSourceFromArgument(2, argumentContent);
	if(compare_char_arr(chosen_operation, add_operation, 4) == 1)
		{
			addToList();
		}
}
int getArgvLength(int argv_num, char *argvContent[])
{
	i=0;
	while(argvContent[argv_num][i] != '\0')
	{
		i++;
	}
	return i;
}



void getSourceFromArgument(int which_argv, char *argvContent[])
{
	argv_length[which_argv] = getArgvLength(which_argv,argvContent);
	source_path = (char*) malloc (argv_length[which_argv]);
	for(i=0;i<argv_length[which_argv];i++)
	{
		source_path[i] = argvContent[which_argv][i];
	}

}




void readFile() //Function to read file and copy it to buffer. 
{
	int file_to_read_descriptor = 0;
	FILE *file_to_read;  
	file_to_read_descriptor = open(source_path, O_RDONLY); //descriptor which is later used to get the pointer to the struct which contains file size. And the file size is what we need
	file_to_read = fopen(source_path, "r"); //actually opens the file. For reading
	fstat(file_to_read_descriptor, &stbuf); //stbuf value gets it from the file descriptor, which was returned from open function.
	source_size = stbuf.st_size; //Now we get the file size. Awesome
	buffer_file = (char*)malloc(source_size);   // make space so that the buffer_file can store it. 
	fread(buffer_file,sizeof(char),source_size, file_to_read); //This basically sends the data from the file, to the buffer_file.
	fclose(file_to_read); //Probably should check if suceeded. TODO: check if successfully closed
	close(file_to_read_descriptor); //closes the file which we opened for getting the descriptor to get the struct and size.
	/*for(int i = 0; i < 51; i++)
	{
		printf("%c",current_file_content[i]);
	}*/
}

void createBackupFile() // The main function for writing to file. Done the simple way. TODO: checking if file opened properly
{
	FILE *file_to_write;
	file_to_write = fopen(destination_path, "w+");
	fwrite(buffer_file, sizeof(char),source_size, file_to_write);
	free(buffer_file); //We free the memory containing the file since we wrote it to the backup file. TODO: deallocate ONLY IF writing succeeded. Also: deallocate only if there is one destination...
}

void addToList() //This is a function to add a file to the backup list. Currently supports only the default list.  TODO: checking if file opened properly
{
	FILE *backup_list; //Consider changing the name to avoid confusion it with the actual several lists. Just for the future.
	backup_list = fopen("./backup_list", "app"); //opens for appending. In the future the file backup_list should be created in some specified directory, and the path to the file should be in place
	fwrite(source_path, 1,10, backup_list); //copies the source file path to the (currently defualt) list. Or more specifically appends it to the file
	fputc('\n', backup_list); //adds a newline char to make sure each path in a list is a new line
}

int compare_char_arr(char array1[], char array2[], int length) //This actually seems like it's done properly (quite) which mean I can use this function without too much worry. Good
{
	int is_the_same = 0;
	for(i = 0; i < length; i++)
	{
		if(array1[i] == array2[i])
		{
			is_the_same = 1;
		}
		else
		{
			is_the_same = 0;
			break;
		}
	}
	return is_the_same;
}




