#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>

int i;
unsigned long l;
char source_path[] = "./example2.txt";
char destination_path[] = "./backup_file.txt";
char add_operation[] = {'a','d','d'};
char *_current_file_content;
char chosen_operation[100];
char *buffer_file;
off_t source_size;
struct stat stbuf; //consider renaming


void readConsoleArguments();
void readFile();
void addToList();
void createBackupFile();
int compare_char_arr(char array1[], char array2[], int length);



int main(int argc, char *argv[])
{
	readConsoleArguments(argc, argv);
	printf("%s", chosen_operation);
	readFile();
	createBackupFile();  
	return 0;
}

void readConsoleArguments(int argument_number, char *argumentContent[])
{
	for(l =0; l <= sizeof(chosen_operation); l++)
	{
		chosen_operation[l] = argumentContent[1][l];
	}
	if(compare_char_arr(chosen_operation, add_operation, 3) == 1)
		{
			addToList();
		}
}

void readFile()
{
	int file_to_read_descriptor = 0;
	FILE *file_to_read;
	file_to_read_descriptor = open(source_path, O_RDONLY);
	file_to_read = fopen(source_path, "r");
	fstat(file_to_read_descriptor, &stbuf);
	source_size = stbuf.st_size;
	buffer_file = (char*)malloc(source_size);   ///FIX THE MALLOC. MUST DEALLOCATE
	fread(buffer_file,sizeof(char),source_size, file_to_read);
	fclose(file_to_read);
	close(file_to_read_descriptor);
	/*for(int i = 0; i < 51; i++)
	{
		printf("%c",current_file_content[i]);
	}*/
}

void createBackupFile()
{
	FILE *file_to_write;
	file_to_write = fopen(destination_path, "w+");
	fwrite(buffer_file, sizeof(char),source_size, file_to_write);
}

void addToList()
{
	FILE *backup_list;
	backup_list = fopen("./backup_list", "app");
	fwrite(source_path, sizeof(char), sizeof(source_path)-1, backup_list);
	fputc('\n', backup_list);
}

int compare_char_arr(char array1[], char array2[], int length)
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




