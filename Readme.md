# Election System
This project is an Election Management System written in C. It simulates the process of registering voters, casting votes, and viewing election results. The system provides separate interfaces for administrators and voters, ensures proper management and security of election data.

## Features

### 1. Main Menu

The system starts with a main menu where users can:

- Access the Admin Panel

- Access the Voter Panel

- Exit the application

### 2. Admin Panel

The admin panel provides functionalities for election management. Admins need to log in with valid credentials (username: \*\*\*\*, password: \*\*\*\*\*) to access the following features:

- View Directory: View the list of all registered voters.

- Clear Voter & Election Data: Reset all data, removing both voter registrations and vote records.

- View Votes: Displays the number of votes cast for each candidate.

- Logout: Exit the admin panel and return to the main menu.

### 3. Voter Panel

The voter panel allows users to participate in the election process through:

- Voter Registration: Voters can sign up by providing their name, ID, date of birth, and gender. Only users aged 18 or above are eligible to register.

- Vote Casting: Registered voters can log in with their ID to cast their vote. Duplicate voting is not allowed.

- View Election Results: Voters can view the percentage of votes received by each candidate.

### 4. Election Result Calculation

The results show the percentage of total votes received by each candidate, dynamically calculated based on the vote records.

## File Structure

### Data Files

The program uses two data files to store information:

- voter_data.txt: Stores voter details (Name, ID, Date of Birth, Gender).

- vote_data.txt: Stores vote records (Voter ID, Candidate Choice).

## Source Code Functions

### Core Functions

- main_menu: Displays the main menu and navigates to the Admin Panel or Voter Panel.

- admin_panel: Provides administrative functionalities.

- voter_menu: Provides options for voter registration, vote casting, and viewing election results.

### Voter Functions

- voter_registration: Handles voter sign-up, prevents duplicate registrations, and validates age eligibility.

- vote_cast: Allows registered voters to log in and cast votes. Ensures duplicate voting is prevented.

### Admin Functions

- authenticate: Verifies admin login credentials.

- view_directory: Displays all registered voter details.

- view_votes: Shows vote counts for each candidate.

- clear_all_data: Deletes all voter and election data.

### Utility Functions

- clear_screen: Clears the console screen (Windows-specific implementation).

- authenticate_voter: Verifies if a voter ID exists in the database.

- check_if_voted: Checks if a voter has already cast their vote.

- display_result: Calculates and displays the election results in percentages.

## Future Enhancements

- Implement data encryption for improved security.

- Develop a graphical user interface (GUI).

- Enhance error handling and validation mechanisms.

## Credit
This is a group project.

## Author
Written by @kanizfatema.

