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

		FILE *f = fopen("user.dat", "ab");

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
		while (fread(&x, sizeof(x), 1, f)==1) {
			printf("Name: %s\n", x.name);
			printf("Password: %s\n", x.password);
			printf("%ld\n",ftell(f));
		}

		fclose(f);

			}

	else if (argc >= 2 && strcmp(argv[1], "login") == 0) {
		
		FILE *f = fopen("user.dat", "rb");

		if (f == NULL) {
			printf("Cannot open file.\n");
			return 1;
		}
		while (fread(&x, sizeof(x), 1, f)==1) {
			if (strcmp(argv[2], x.name) == 0 && 
			    strcmp(argv[3], x.password) == 0) {
				printf("ok\n");
				fclose(f);
				return 0;
			}
		}
		fclose(f);
		printf("fail\n");
	}

	else if (argc >= 2 && strcmp(argv[1], "count") == 0) {
		FILE *f = fopen("user.dat", "rb");
		if (f == NULL) {
			printf("Cannot open file.\n");
			return 1;
		}
		fseek(f, 0, SEEK_END);
		long size = ftell(f);
		fclose(f);

		long count = size / sizeof(struct user);
		printf("Users: %ld\n", count);
	}


	else {
		printf("Usage:\n");
		printf(" %s add <name> <password>\n", argv[0]);
		printf(" %s show\n", argv[0]);
	}

	return 0;

}


