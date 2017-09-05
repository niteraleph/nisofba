#include <stdio.h>

int i;
unsigned long l;
char source_path[] = "./example2.txt";
char destination_path[] = "./backup_file.txt";
char current_file_content[50];
char *_current_file_content;
char chosen_operation[100];


void readConsoleArguments();
void readFile();
void addToList();
void createBackupFile();


int main(int argc, char *argv[])
{
	printf("%s", "Changed");
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
	FILE *file_to_read;
	file_to_read = fopen(source_path, "r");
	fread(current_file_content,sizeof(char),sizeof(current_file_content), file_to_read);
	fclose(file_to_read);
	/*for(int i = 0; i < 51; i++)
	{
		printf("%c",current_file_content[i]);
	}*/
}

void createBackupFile()
{
	FILE *file_to_write;
	file_to_write = fopen(destination_path, "w+");
	fwrite(current_file_content, sizeof(char), sizeof(current_file_content), file_to_write);
}

void addToList()
{
	FILE *backup_list;
	backup_list = fopen("./backup_list", "app");
	fwrite(source_path, sizeof(char), sizeof(source_path), backup_list);
}
