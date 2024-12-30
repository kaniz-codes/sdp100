#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void clear_screen();
void admin_panel();
void voter_menu();
void voter_registration();
void vote_cast();
void election_result();
void display_result();
void view_directory();
void clear_all_data();

void clear_screen()
{
#ifdef _WIN32
	system("cls");
#endif
}

void main_menu()
{
	int main_choice;

	while (1)
	{
		clear_screen();
		printf("---- Election System ----\n");
		printf("1. Admin Panel\n");
		printf("2. Voter Panel\n");
		printf("3. Exit\n");
		printf("Enter your choice: ");
		scanf("%d", &main_choice);
		getchar();
		clear_screen();

		switch (main_choice)
		{
		case 1:
			admin_panel();
			break;
		case 2:
			voter_menu();
			break;
		case 3:
			exit(0);
		default:
			printf("Invalid choice! Please try again.\n");
			getchar();
		}
	}
}

void voter_menu()
{
	int voter_choice;

	while (1)
	{
		clear_screen();
		printf("---- Voter Panel ----\n");
		printf("1. Voter Registration\n");
		printf("2. Vote Cast\n");
		printf("3. View Election Result\n");
		printf("4. Back to Main Menu\n");
		printf("Enter your choice: ");
		scanf("%d", &voter_choice);
		getchar();
		clear_screen();

		switch (voter_choice)
		{
		case 1:
			voter_registration();
			break;
		case 2:
			vote_cast();
			break;
		case 3:
			election_result();
			break;
		case 4:
			return;
		default:
			printf("Invalid choice! Please try again.\n");
			getchar();
		}
	}
}

void voter_registration()
{
	int choice;

	while (1)
	{
		clear_screen();
		printf("---- Voter Registration ----\n");
		printf("1. Sign Up\n");
		printf("2. Back to Voter Menu\n");
		printf("Enter your choice: ");
		scanf("%d", &choice);
		getchar();

		if (choice == 1)
		{
			char name[100], id[20], dob[15], gender[10];
			int age;
			FILE *fp = fopen("voter_data.txt", "a+");
			if (fp == NULL)
			{
				printf("Error opening file!\n");
				return;
			}

			printf("Enter your name: ");
			fgets(name, sizeof(name), stdin);
			name[strcspn(name, "\n")] = 0;

			printf("Enter your ID: ");
			fgets(id, sizeof(id), stdin);
			id[strcspn(id, "\n")] = 0;

			char line[150], existing_id[20];
			rewind(fp);
			while (fgets(line, sizeof(line), fp))
			{
				sscanf(line, "%*[^,],%[^,],%*s", existing_id);
				if (strcmp(existing_id, id) == 0)
				{
					printf("This ID is already registered!\n\n");
					fclose(fp);
					printf("Press Enter to go back...");
					getchar();
					return;
				}
			}

			printf("Enter your Date of Birth (dd-mm-yyyy): ");
			fgets(dob, sizeof(dob), stdin);
			dob[strcspn(dob, "\n")] = 0;

			printf("Enter your Gender: ");
			fgets(gender, sizeof(gender), stdin);
			gender[strcspn(gender, "\n")] = 0;

			sscanf(dob + 6, "%d", &age);
			age = 2024 - age;

			if (age < 18)
			{
				printf("Not eligible to vote. You must be 18 or older.\n\n");
				fclose(fp);
				printf("Press Enter to go back...");
				getchar();
				return;
			}

			fprintf(fp, "%s,%s,%s,%s\n", name, id, dob, gender);
			fclose(fp);

			printf("Voter registration successful!\n\n");
			printf("Press Enter to go back...");
			getchar();
		}
		else if (choice == 2)
		{
			return;
		}
		else
		{
			printf("Invalid choice! Please try again.\n");
			getchar();
		}
	}
}

int check_if_voted(char *id)
{
	char line[150], vote_id[20];
	FILE *fp = fopen("vote_data.txt", "r");

	if (fp == NULL)
	{
		return 0;
	}

	while (fgets(line, sizeof(line), fp))
	{
		sscanf(line, "%[^,]", vote_id);
		if (strcmp(vote_id, id) == 0)
		{
			fclose(fp);
			return 1;
		}
	}

	fclose(fp);
	return 0;
}

int authenticate_voter(char *id)
{
	char line[150], voter_id[20];
	FILE *fp = fopen("voter_data.txt", "r");

	if (fp == NULL)
	{
		printf("Error opening voter database!\n");
		return 0;
	}

	while (fgets(line, sizeof(line), fp))
	{
		sscanf(line, "%*[^,],%[^,],%*s", voter_id);
		if (strcmp(voter_id, id) == 0)
		{
			fclose(fp);
			return 1;
		}
	}

	fclose(fp);
	return 0;
}

void vote_cast()
{
	int choice;

	while (1)
	{
		clear_screen();
		printf("---- Vote Cast ----\n");
		printf("1. Login\n");
		printf("2. Back to Voter Menu\n");
		printf("Enter your choice: ");
		scanf("%d", &choice);
		getchar();

		if (choice == 1)
		{
			char id[20], vote[20];
			int candidate_choice;

			printf("Enter your ID: ");
			fgets(id, sizeof(id), stdin);
			id[strcspn(id, "\n")] = 0;

			if (!authenticate_voter(id))
			{
				printf("User not found. Please register first.\n\n");
				printf("Press Enter to go back to the main menu...");
				getchar();
				return;
			}

			if (check_if_voted(id))
			{
				printf("You have already cast your vote!\n\n");
				printf("Press Enter to go back to the Voter menu...");
				getchar();
				return;
			}

			clear_screen();
			printf("---- Vote Cast ----\n");
			printf("Please select a candidate:\n\n");

			printf("-------------------------------------------------------------\n");
			printf("|        1        |        2        |        3              |\n");
			printf("|  AWAMI LEAGUE   |       BNP       |  TAMIM'S PARTY        |\n");
			printf("-------------------------------------------------------------\n");

			printf("\nVote: ");
			scanf("%d", &candidate_choice);
			getchar();

			switch (candidate_choice)
			{
			case 1:
				strcpy(vote, "Awami League");
				break;
			case 2:
				strcpy(vote, "BNP");
				break;
			case 3:
				strcpy(vote, "Tamim's Party");
				break;
			default:
				printf("Invalid choice!\n");
				printf("Press Enter to go back to the Voter menu...");
				getchar();
				return;
			}

			FILE *fp = fopen("vote_data.txt", "a");
			if (fp == NULL)
			{
				printf("Error opening file!\n");
				return;
			}
			fprintf(fp, "%s,%s\n", id, vote);
			fclose(fp);

			printf("\nThank you for voting for %s!\n\n", vote);
			printf("Press Enter to go back to the main menu...");
			getchar();
		}
		else if (choice == 2)
		{
			return;
		}
		else
		{
			printf("Invalid choice! Please try again.\n");
			getchar();
		}
	}
}

void election_result()
{
	clear_screen();
	printf("---- Election Result ----\n");
	display_result();
	printf("Press Enter to go back...");
	getchar();
}
void display_result()
{
	FILE *fp = fopen("vote_data.txt", "r");
	if (fp == NULL)
	{
		printf("No votes recorded yet!\n");
		return;
	}

	char line[150], vote[50];
	int total_votes = 0;
	int awami_votes = 0, bnp_votes = 0, tamim_votes = 0;

	while (fgets(line, sizeof(line), fp))
	{
		if (sscanf(line, "%*[^,],%[^\n]", vote) == 1)
		{
			total_votes++;
			if (strcmp(vote, "Awami League") == 0)
				awami_votes++;
			else if (strcmp(vote, "BNP") == 0)
				bnp_votes++;
			else if (strcmp(vote, "Tamim's Party") == 0)
				tamim_votes++;
		}
	}
	fclose(fp);

	printf("\n\tAWAMI LEAGUE\t    BNP\t        TAMIM'S PARTY\n");
	printf("\t-----------------------------------------------\n");
	printf("\t %.2f%%\t\t%.2f%%\t\t%.2f%%\n\n",
		   (total_votes ? (awami_votes * 100.0 / total_votes) : 0),
		   (total_votes ? (bnp_votes * 100.0 / total_votes) : 0),
		   (total_votes ? (tamim_votes * 100.0 / total_votes) : 0));
}

void view_votes()
{
	FILE *fp = fopen("vote_data.txt", "r");
	char line[150], vote[50];
	int total_votes = 0, awami = 0, bnp = 0, tamim = 0;

	if (fp == NULL)
	{
		printf("No votes found!\n");
		printf("\nPress Enter to return to the Admin Panel...");
		getchar();
		return;
	}

	while (fgets(line, sizeof(line), fp))
	{
		sscanf(line, "%*[^,],%[^\n]", vote);
		if (strcmp(vote, "Awami League") == 0)
			awami++;
		else if (strcmp(vote, "BNP") == 0)
			bnp++;
		else if (strcmp(vote, "Tamim's Party") == 0)
			tamim++;
		total_votes++;
	}

	fclose(fp);

	printf("\n---- Vote Results ----\n");
	printf("Total Votes: %d\n", total_votes);
	printf("Awami League: %d\n", awami);
	printf("BNP: %d\n", bnp);
	printf("Tamim's Party: %d\n", tamim);

	printf("\nPress Enter to return to the Admin Panel...");
	getchar();
}

int authenticate()
{
	char username[50], password[50];

	printf("---- Admin Login ----\n");
	printf("Enter username: ");
	fgets(username, sizeof(username), stdin);
	username[strcspn(username, "\n")] = 0;

	printf("Enter password: ");
	fgets(password, sizeof(password), stdin);
	password[strcspn(password, "\n")] = 0;

	return (strcmp(username, "admin") == 0 && strcmp(password, "1234") == 0);
}

void admin_panel()
{
	int admin_choice;

	while (1)
	{
		clear_screen();
		printf("---- Admin Panel ----\n");
		printf("1. Login\n");
		printf("2. Back to Main Menu\n");
		printf("Enter your choice: ");
		scanf("%d", &admin_choice);
		getchar();

		if (admin_choice == 1)
		{
			if (!authenticate())
			{
				printf("Login Failed\n");
				getchar();
				continue;
			}

			while (1)
			{
				clear_screen();
				printf("---- Admin Panel ----\n");
				printf("1. View Directory\n");
				printf("2. Clear Voter & Election Data\n");
				printf("3. View Votes\n");
				printf("4. Logout\n");
				printf("Enter your choice: ");
				int choice;
				scanf("%d", &choice);
				getchar();

				switch (choice)
				{
				case 1:
					view_directory();
					break;
				case 2:
					clear_all_data();
					break;
				case 3:
					view_votes();
					break;
				case 4:
					return;
				default:
					printf("Invalid choice! Please try again.\n");
				}
			}
		}
		else if (admin_choice == 2)
		{
			return;
		}
		else
		{
			printf("Invalid choice! Please try again.\n");
			getchar();
		}
	}
}

void clear_all_data()
{
	FILE *fp;

	fp = fopen("voter_data.txt", "w");
	if (fp != NULL)
		fclose(fp);

	fp = fopen("vote_data.txt", "w");
	if (fp != NULL)
		fclose(fp);

	printf("All data cleared!\n");
	getchar();
}

void view_directory()
{
	FILE *fp = fopen("voter_data.txt", "r");
	if (fp == NULL)
	{
		printf("No voter registrations found!\n\n");
		printf("Press Enter to go back...");
		getchar();
		return;
	}

	char line[150];
	printf("Voter Directory:\n");
	printf("------------------------------------------------------------------------\n");
	printf("Name\t\t\t\tID\t\tDOB\t\tGender\n");
	printf("------------------------------------------------------------------------\n");

	while (fgets(line, sizeof(line), fp))
	{
		char name[100], id[20], dob[15], gender[10];
		sscanf(line, "%[^,],%[^,],%[^,],%s", name, id, dob, gender);
		printf("%-30s %-15s %-15s %-15s\n", name, id, dob, gender);
	}

	fclose(fp);

	printf("\nPress Enter to return to the Admin Panel...");
	getchar();
}

int main()
{
	main_menu();
	return 0;
}