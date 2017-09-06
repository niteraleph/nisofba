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
char *_current_file_content;
char chosen_operation[100];
char *buffer_file;
off_t source_size;
struct stat stbuf;


void readConsoleArguments();
void readFile();
void addToList();
void createBackupFile();



int main(int argc, char *argv[])
{
	readConsoleArguments(argc, argv);
	printf("%s", chosen_operation);
	addToList();
	
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

}

void readFile()
{
	int file_to_read_descriptor = 0;
	FILE *file_to_read;
	file_to_read_descriptor = open(source_path, O_RDONLY);
	file_to_read = fopen(source_path, "r");
	fstat(file_to_read_descriptor, &stbuf);
	source_size = stbuf.st_size;
	buffer_file = (char*)malloc(source_size);
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
}
