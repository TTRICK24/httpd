#include <stdio.h>
#include <string.h>

struct user {
	char name[64];
	char password[64];
};



int main(int argc, char *argv[]) 
{
	struct user x;

	if (argc >= 2 && strcmp(argv[1], "add") == 0) {

		if (argc != 4) {
			printf("Usage: %s add <name> <password>\n", argv[0]);
			return 1;
		}

		strcpy(x.name, argv[2]);
		strcpy(x.password, argv[3]);

		FILE *f = fopen("user.dat", "wb");

		if (f == NULL) {
			printf("Cannot open file.\n");
			return 1;
		}

		fwrite(&x, sizeof(x), 1, f);
		fclose(f);

		printf("User saved.\n");
	}
	else if (argc >= 2 && strcmp(argv[1], "show") == 0) {

		FILE *f = fopen("user.dat", "rb");

		if (f == NULL) {
			printf("Cannot open file.\n");
			return 1;
		}

		fread(&x, sizeof(x), 1, f);
		fclose(f);

		printf("Name: %s\n", x.name);
		printf("Password: %s\n", x.password);
	}
	else {
		printf("Usage:\n");
		printf(" %s add <name> <password>\n", argv[0]);
		printf(" %s show\n", argv[0]);
	}

	return 0;

}


