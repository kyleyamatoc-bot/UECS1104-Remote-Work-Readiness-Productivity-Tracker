/*
 Program Name: Remote Work Readiness and Productivity Tracking System

 Description:

 This program is designed to assess the readiness of a home office for remote work and track the productivity of employees.
 It provides two main functionalities:
 1. Remote Work Readiness Checklist: A safety checklist for remote work environments.
 2. Productivity Tracking System: Allows users to log work activities, track productivity metrics, and generate reports.

 The program uses a text file to store and retrieve data, including employee information, safety checklist results,
 and productivity logs. It provides options for generating reports based on the collected data.
 */

 //Preprocessor directives
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib> 
#include <sstream>
#include <iomanip>


using namespace std;

// Function prototypes

// Displays the main menu and handles user input.
int mainmenu();
// Displays the submenu for the Remote Work Readiness section.
void remoteReadinessSubmenu();
// Handles the Remote Work Readiness checklist, including user input and file operations.
void remoteWorkReadiness();
// Asks a question from the checklist, gets the user's answer, and writes it to the file.
void askQuestion(string* question, ofstream* outFile, int* countY, int* countN);
// Retrieves the current entry number from the file.
int getCurrentEntryNumber();
// Updates the entry number in the file.
void updateEntryNumber(int newEntryNumber);
// Validates the user's answer to ensure it is either 'Y' or 'N'.
bool isValidAnswer(string& answer);
// Generates a safety report based on the checklist data.
void generateSafetyReport();

// Handles the Productivity Tracking System, including logging work activities and generating reports.
void productivityTrackingSystem();
// Logs a work activity for productivity tracking.
void workProductivityLog();
// Validates the time input format (HH:MM).
bool isValidTime(const string& timeStr);
// Converts a time string (HH:MM) to total minutes.
int timeToMinutes(const string& timeStr);
// Converts total minutes to a time string (HH:MM).
string minutesToTime(int totalMinutes);
// Generates a productivity report based on logged work activities.
void generateProductivityReport();
// Retrieves the current work log number from the file.
int getCurrentWorkNumber();
// Updates the work log number in the file.
void updateWorkNumber(int newWorkNumber);

int main() {
    int choice;
    do {
        system("cls"); // Clear screen
        choice = mainmenu(); // Display the main menu and get user choice
        if (choice == 1) {
            cout << endl;
            system("cls");
            remoteReadinessSubmenu(); // Call the function for Remote Work Readiness Sub menu
        }
        else if (choice == 2) {
            cout << endl;
            system("cls");
            productivityTrackingSystem(); // Call the function for Productivity Tracking System 
        }
    } while (choice != 0); // Continue looping until the user chooses to exit by entering 0

    cout << "\nExiting the program. Goodbye!" << endl; // Display an exit message

    return 0;
}

/**
* //Function for Main menu

  Displays the main menu for the Remote Work Readiness and Productivity Tracking System.

  :return int - The user's choice (1 for Remote Work Readiness Menu, 2 for Productivity Tracking System Menu, 0 for Exit).
 */
int mainmenu() {
    int choice;

    cout << "Welcome to the Remote Work Readiness and Productivity Tracking System" << endl;
    cout << "---------------------------------------------------------------------\n" << endl;
    cout << "Remote Work Readiness Menu ----------- [1]\n" << endl;
    cout << "Productivity Tracking System Menu ---- [2]\n" << endl;
    cout << "\nExit --------------------------------- [0]\n" << endl;
    cout << "---------------------------------------------------------------------" << endl;
    cout << "Please select an option (1, 2, or 0): ";

    // Validate user input for menu choice
    while (!(cin >> choice) || (choice < 0 || choice > 2)) {
        cin.clear(); // Clear the error flag from invalid input
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
        cout << "\nInvalid input. Please enter a number (1, 2, or 0): ";
    }

    return choice; // Return user's valid choice
}

bool SafetyChecklistCompleted = false; // Used to check if Case 1 was done first (only for the first time)

/*
  // Function for the Remote Readiness submenu

  Displays the submenu for Remote Work Readiness, allowing the user to select from
  various options related to work readiness and report generation.
 */
void remoteReadinessSubmenu() {
    int subChoice;

    do {
        cout << "Remote Work Readiness Menu selected. [1]" << endl;
        cout << "\nRemote Work Readiness Menu" << endl;
        cout << "--------------------------------------------\n" << endl;
        cout << "Remote Work Readiness safety Checklist --[1]\n" << endl;
        cout << "Generate Report -------------------------[2]\n" << endl;
        cout << "\nReturn to Main Menu ---------------------[0]\n" << endl;
        cout << "--------------------------------------------" << endl;
        cout << "Please select an option (1, 2, or 0): ";

        while (!(cin >> subChoice) || (subChoice < 0 || subChoice > 2)) {
            cin.clear(); // Clear the error flag from invalid input
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
            cout << "\nInvalid input. Please enter a number (1, 2, or 0): ";
        }

        switch (subChoice) {
        case 1:
            system("cls");
            cout << "Remote Work Readiness selected." << endl;
            remoteWorkReadiness(); // Call the Remote Work Readiness function
            SafetyChecklistCompleted = true; // Mark checklist as completed
            system("cls");
            break;
        case 2:
            system("cls");
            if (SafetyChecklistCompleted == true) {
                cout << "Generating Report from SafetyChecklist.txt...\n" << endl;
                generateSafetyReport(); // Generate the report from SafetyChecklist.txt
                system("cls");

            }
            else {
                cout << "Please complete Safety Checklist (option[1]) first, before Generating Report\n" << endl;
                //Wait for user to acknowledge the message and continue
                cout << "\nEnter any key to return...";
                cin.ignore();
                cin.get();
                system("cls");
            }
            break;
        case 0:
            cout << "Returning to Main Menu..." << endl;
            break;
        }
    } while (subChoice != 0);
}

/*
 // Function to handle Remote Work Readiness
  Handles the Remote Work Readiness checklist by asking a series of predefined questions,
  recording the responses, and generating a report in a text file.

  The function performs the following tasks:
  - Prompts the user for their details and workspace information.
  - Iterates through a list of safety-related questions, asking each question and recording the answers.
  - Writes the collected data and responses to a file named "SafetyChecklist.txt".
  - Provides a summary based on the number of 'Yes' and 'No' answers.
  - Updates the entry number for the checklist.
 */

void remoteWorkReadiness() {
    // Define an array of questions for the checklist
    string questions[] = {
        "(1) Is the work space free from excessive noise?",
        "(2) Is adequate lighting (side or rear) provided at the work station?",
        "(3) Is all electrical equipment free of recognized hazards that could cause physical harm\n     (frayed wires running through walls, exposed wires fixed to the ceiling)?                                ",
        "(4) Is electrical system adequate for office equipment?",
        "(5) Is electrical equipment grounded?",
        "(6) Are surge protectors properly installed?",
        "(7) Are aisles, doorways and floors free of obstructions to permit visibility and movement?",
        "(8) Is there an exit that allows prompt exiting?",
        "(9) Are phone lines, electrical cords and extension wires secured under a desk or along a baseboard?",
        "(10) Is the office space neat and clean?",
        "(11) Is a working fire extinguisher located nearby?",
        "(12) Are working smoke detectors installed at the work site?",
        "(13) Is the work area private and free of intrusion?",
        "(14) Are files and data secure?",
        "(15) Are first aid supplies readily accessible and adequate?",
        "(16) Are office furniture and equipment ergonomically correct?",
        "(17) Desk: 29” high?",
        "(18) Chairs: Sturdy and adjustable (90° at knees, feet flat on floor, 15° back tilt)\n     with backrest and casters appropriate for floor surface?                                                 ",
        "(19) Keyboard: In line with wrist and forearm position?",
        "(20) Monitor: 20-14” from eyes: Top of screen slightly below eye level?",
        "(21) Are work materials and equipment in a secure place that can be protected from damage or misuse?",
        "(22) Are there security requirements in place to protect confidentiality and security of\n     company information and computer systems?                                                                "
    };

    string employeeName, date, managerName, remoteWorkAddress, workAreaDescription;
    int countY = 0, countN = 0; // Initialize counters

    // Get the current entry number
    int entryNumber = getCurrentEntryNumber();
    entryNumber++; // Increase the entry number

    // Display the entry number
    cout << "\n----------------------------------------------" << endl;
    cout << "Entry Number: " << entryNumber << endl;
    cout << "----------------------------------------------\n" << endl;
    cin.ignore(); // Clear the newline character left in the input buffer

    // Collect user information
    do {
        cout << "Employee                : ";
        getline(cin, employeeName); // Read the employee's name
        if (employeeName == "0") return; // Exit if '0' is entered
    } while (employeeName.empty());

    do {
        cout << "Date                    : ";
        getline(cin, date); // Read the date
        if (date == "0") return; // Exit if '0' is entered
    } while (date.empty());

    do {
        cout << "Manager                 : ";
        getline(cin, managerName); // Read the manager's name
        if (managerName == "0") return; // Exit if '0' is entered
    } while (managerName.empty());

    do {
        cout << "Remote work site address: ";
        getline(cin, remoteWorkAddress); // Read the remote work site address
        if (remoteWorkAddress == "0") return; // Exit if '0' is entered
    } while (remoteWorkAddress.empty());

    do {
        cout << "Description of work area: ";
        getline(cin, workAreaDescription); // Read the description of the work area
        if (workAreaDescription == "0") return; // Exit if '0' is entered
    } while (workAreaDescription.empty());

    cout << endl; // Print a blank line
    cout << "----------------------------------------------------------------------------------------------------------------------\n" << endl;

    // Open a file to write the checklist data
    ofstream outFile("SafetyChecklist.txt", ios::app);

    // Write the entry number to the file
    outFile << "\n----------------------------------------------" << endl;
    outFile << "Checklist Number: " << entryNumber << endl;
    outFile << "----------------------------------------------\n" << endl;


    // Write user information to file
    outFile << "Home Office Safety Checklist\n\n";
    outFile << "Employee                 : " << employeeName << endl;
    outFile << "Date                     : " << date << endl;
    outFile << "Manager                  : " << managerName << endl;
    outFile << "Remote work site address : " << remoteWorkAddress << endl;
    outFile << "Description of work area : " << workAreaDescription << endl;
    outFile << endl; // Print a blank line in the txt file

    // Write the table header
    outFile << "----------------------------------------------------------------------------------------------------------------------" << endl;
    outFile << left << setw(110) << "Question" << "Answer" << endl;
    outFile << "----------------------------------------------------------------------------------------------------------------------\n" << endl;

    // Iterate (go) through the array of questions and ask each one
    for (int i = 0; i < 22; i++) {
        outFile << left << setw(110) << questions[i];
        askQuestion(&questions[i], &outFile, &countY, &countN); // Ask the question and write the answer to the file 
        outFile << endl; // Print a blank line in the txt file
    }

    // Write summary information
    outFile << "----------------------------------------------------------------------------------------------------------------------" << endl;
    outFile << "    Total number of Yes: " << countY << endl;
    outFile << "    Total number of No : " << countN << endl;
    outFile << "----------------------------------------------------------------------------------------------------------------------" << endl;

    // Add the summary to the file based on the number of 'Yes' and 'No' answers
    if (countN == 0) {
        outFile << "    Summary: The workspace is fully suitable for remote work." << endl;
    }
    else if (countN <= 3) {
        outFile << "    Summary: The workspace is mostly suitable for remote work but has some minor issues to address." << endl;
    }
    else if (countN <= 6) {
        outFile << "    Summary: The workspace has several issues that should be addressed before it can be considered suitable." << endl;
    }
    else {
        outFile << "    Summary: The workspace is currently not suitable for remote work due to significant safety concerns." << endl;
    }

    outFile << "----------------------------------------------------------------------------------------------------------------------" << endl;

    // Close the file after writing all data
    outFile << endl; // Print a blank line in the txt file
    outFile << "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx" << endl;

    outFile.close();

    // Update the entry number file
    updateEntryNumber(entryNumber);

    cout << "----------------------------------------------------------------------------------------------------------------------" << endl;
    cout << "\nEntry completed and saved to SafetyChecklist.txt" << endl;
    //Wait for user to continue
    cout << "\nEnter any key to continue...";
    cin.ignore();
    cin.get();
}

/*
 // Function to ask a question, get the user's answer, and write the question and answer to a file using pointers

  Asks a question to the user, retrieves their answer, and writes the question and answer to a file.

  The function performs the following tasks:
  - Prompts the user with a question and requests a Yes/No answer.
  - Validates the user's answer to ensure it is either 'Y', 'Yes', 'N', or 'No' (case insensitive).
  - Converts the answer to a consistent format ('Yes' or 'No').
  - Updates counters for 'Yes' and 'No' answers.
  - Writes the question and user's answer to the specified output file.

  :param question - A pointer to a string containing the question to be asked.
  :param outFile -  A pointer to an ofstream object used to write the question and answer to a file.
  :param countY -  A pointer to an integer that keeps track of the number of 'Yes' answers.
  :param countN - A pointer to an integer that keeps track of the number of 'No' answers.
 */
void askQuestion(string* question, ofstream* outFile, int* countY, int* countN) {
    string answer; // Variable to store the user's answer
    cout << *question << "\n\n     (Y-Yes/n-No): "; // Prompt the user with the question and ask for a Yes/No answer
    cin >> answer;

    // Validate the answer
    while (!isValidAnswer(answer)) {
        cout << "\n     Invalid answer. Please enter (Y-Yes or N-No) [case insensitive]: ";
        cin >> answer;
    }

    // This is done to ensure consistency throughout the answers in the checklist
    if (answer == "YES" || answer == "Yes" || answer == "Y" || answer == "y") {
        answer = "Yes";
        (*countY)++;
    }
    else {
        answer = "No";
        (*countN)++;
    }

    *outFile << left << setw(3) << answer << endl; // Write the question and the user's answer  to the file, followed by a newline
    cout << endl; // Print a blank line
}

/**
 // Function to generate and display a report from SafetyChecklist.txt
  Generates and displays a report from the SafetyChecklist.txt file.

  This function performs the following tasks:
  - Opens the SafetyChecklist.txt file for reading.
  - Reads and displays each line of the file on the console.
  - Provides error messages if the file cannot be opened.
  - Waits for user input before returning to the previous menu.

  :pre - The SafetyChecklist.txt file should exist and contain valid data.
  :post - The console displays the contents of SafetyChecklist.txt or an error message if the file cannot be opened.
 */
void generateSafetyReport() {
    ifstream in_File("SafetyChecklist.txt");
    string line;

    if (in_File.is_open()) {
        cout << "\nSafety Checklist Report:\n" << endl;
        while (getline(in_File, line)) {
            cout << line << endl;
        }
        in_File.close(); // Close the file after reading
    }
    else {
        cout << "Unable to open the SafetyChecklist.txt file.\n" << endl;
        cout << "Possible Reason 1: No entry for Safety Checklist (option[1]). Please Complete it atleast once.\n" << endl;
        cout << "Possible Reason 2: SafetyChecklist.txt file has not been created.\n" << endl;

    }
    //Wait for user to continue
    cout << "\nEnter any key to return...";
    cin.ignore();
    cin.get();
    system("cls");
}

/*
 // Function to get the current entry number by reading from a file
  Gets the current entry number by reading from the EntryNumber.txt file.

  This function performs the following tasks:
  - Opens the EntryNumber.txt file for reading.
  - Reads the entry number from the file.
  - Closes the file after reading.

  :return int - The current entry number read from the file. If the file is empty or cannot be opened, returns 0.
 */

int getCurrentEntryNumber() {
    ifstream inFile("EntryNumber.txt");
    int entryNumber = 0; // Initialize entry number to 0

    if (inFile.is_open()) {
        inFile >> entryNumber;  // Read the entry number from the file
        inFile.close(); // Close the file after reading
    }
    return entryNumber; // Return the entry number
}

/*
 // Function to update the entry number in the file
  Updates the entry number in the EntryNumber.txt file.

  This function performs the following tasks:
  - Opens the EntryNumber.txt file for writing.
  - Writes the new entry number to the file.
  - Closes the file after writing.
  - Displays an error message if the file cannot be opened.

  :param newEntryNumber - The new entry number to be written to the file.
 */
void updateEntryNumber(int newEntryNumber) {
    ofstream outFile("EntryNumber.txt");
    if (outFile.is_open()) {
        outFile << newEntryNumber; // Write the updated entry number to the file
        outFile.close(); // Close the file after writing
    }
    else {
        cout << "Unable to update entry number file." << endl; // Error message if file cannot be opened
        //Wait for user to continue
        cout << "\nEnter any key to continue...";
        cin.ignore();
        cin.get();
    }
}

/**
 // Function to check if the user's answer is valid
  Checks if the user's answer is valid.

  This function validates the user's response to ensure it matches expected values for Yes or No.

  :param answer - The user's answer to validate.
  :return bool - True if the answer is one of the valid responses (Yes/No), false otherwise.
 */
bool isValidAnswer(string& answer) {
    return answer == "Yes" || answer == "YES" || answer == "yes" || answer == "y" || answer == "Y" ||
        answer == "No" || answer == "NO" || answer == "no" || answer == "n" || answer == "N";
}

bool case1CompletedFirst = false; // Used to check if Case 1 was done first (only for the first time)

/*
 // Function to handle Productivity Tracking System
  Handles the Productivity Tracking System menu and its options.

  This function displays the Productivity Tracking System menu with options to:
  1. Log work activity and track productivity metrics.
  2. Generate a report based on recorded work activities.
  0. Return to the main menu.

  It ensures that users complete work logging before generating a report.

  :pre - The global variable `case1CompletedFirst` is used to track whether work activity logging has been completed.
  :post - Depending on user selection, the function calls `workLog()` to log activities, `generateReport()` to generate reports,
          or returns to the main menu. The console displays appropriate messages based on the user's actions and status.
 */

void productivityTrackingSystem() {

    int subChoice; // Variable to store the user's submenu choice

    do {
        // Display the Productivity Tracking System menu
        cout << "Productivity Tracking System Menu selected. [2]" << endl;
        cout << "\nProductivity Tracking System Menu" << endl;
        cout << "-------------------------------------------------------------------\n" << endl;
        cout << "Log Work Activity & Track Productivity Metrics -----------------[1]\n" << endl;
        cout << "Generate Report ------------------------------------------------[2]\n" << endl;
        cout << "\nReturn to Main Menu --------------------------------------------[0]\n" << endl;
        cout << "-------------------------------------------------------------------" << endl;
        cout << "Please select an option (1, 2, or 0): ";

        // Validate user input for submenu choice
        while (!(cin >> subChoice) || (subChoice < 0 || subChoice > 3)) {
            cin.clear(); // Clear error flags
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
            cout << "\nInvalid input. Please enter a number (1, 2, or 0): ";
        }

        // Handle user selection
        switch (subChoice) {
        case 1:
            system("cls"); // Clear screen
            workProductivityLog(); // Call the function to log work activities and track productivity metrics
            system("cls"); // Clear screen after work log

            case1CompletedFirst = true; // Mark that work logging has been completed

            break;

        case 2:
            if (case1CompletedFirst == true) { // Check if work activity has been logged

                system("cls"); // Clear screen
                cout << "Report List" << endl;
                generateProductivityReport(); // Call the function to generate the productivity report
                system("cls"); // Clear screen after generating the report
            }

            else {
                system("cls"); // Clear screen
                cout << "Posibble Reason 1: No Entry Recorded \n"
                    << "\nPlease Login your Work Activity and Complete Track Productivity Metrics (Option [1])\n"
                    << "\nBefore Generating Report\n" << endl;
                //Wait for user to continue
                cout << "\nEnter any key to return...";
                cin.ignore();
                cin.get();
                system("cls"); // Clear screen after message
            }
            break;
        case 0:
            cout << "Returning to Main Menu..." << endl; // Inform the user that they are  returned to the Main menu.
            break;
        }

    } while (subChoice != 0); // Repeat until the user selects the option to exit
}

/*
 // Function to handle WorkLog
  Collects and logs work activities and productivity metrics.

  This function:
  - Creates or opens the WorkLog.txt file in append mode.
  - Retrieves and displays the current entry number.
  - Collects basic information such as name, contact, date, department, and supervisor.
  - Collects details of each activity, including start and end times, status, and notes.
  - Calculates total scheduled time and logs productivity metrics for each activity.
  - Writes all collected data to the WorkLog.txt file with proper formatting.
  - Updates the work entry number.

  :pre - The `EntryNumber.txt` file must exist and contain a valid integer to track the current entry number.
  :post - The WorkLog.txt file is updated with new entries, including work activities and productivity metrics.
 */
void workProductivityLog() {
    // Create WorkLog.txt file in append mode
    ofstream workLogFile("WorkLog.txt", ios::app);

    string name, contact, date, department, supervisor, experience;
    int numActivities;

    // Retrieve and increase entry number
    int workNumber = getCurrentWorkNumber() + 1;


    // Display current entry number
    cout << "---------------------\n";
    cout << "WORK LOG - ENTRY " << workNumber << "\n";
    cout << "---------------------\n\n";
    cin.ignore();// Ignore leftover newline characters

    // Collecting basic information
    do {

        cout << "Name         : ";
        getline(cin, name); // Read the name
        if (name == "0") return; //if user enter 0, return 
    } while (name.empty());

    do {
        cout << "Contact No   : ";
        getline(cin, contact); // Read the contact

    } while (contact.empty());

    do {
        cout << "Today's Date : ";
        getline(cin, date); // Read the date

    } while (date.empty());

    do {
        cout << "Department   : ";
        getline(cin, department); // Read the department

    } while (department.empty());

    do {
        cout << "Supervisor   : ";
        getline(cin, supervisor); // Read the supervisor

    } while (supervisor.empty());

    // Collect the number of activities with input validation
    while (true) {
        cout << "\nEnter the number of activities for today: ";
        cin >> numActivities;

        // Check if the input is a valid integer
        if (cin.fail() || numActivities <= 0) {
            cout << "ERROR: Please enter a valid positive integer for the number of activities: " << endl;
            cin.clear(); // Clear the error flag on cin
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
        }
        else {
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard remaining input
            break; // Exit loop if input is valid
        }
    }

    // Check if file was opened successfully
    if (!workLogFile.is_open()) {
        cerr << "Error: Unable to open WorkLog.txt." << endl;
        return;
    }

    // Writing the entry number and basic information with better formatting
    workLogFile << "\nWORK LOG - ENTRY " << workNumber << "\n";
    workLogFile << "------------------------------------------------------------------------------------------------------------------\n";
    workLogFile << left << setw(24) << "NAME" << setw(25) << "CONTACT" << setw(20) << "TODAY'S DATE" << setw(20) << "DEPARTMENT" << setw(11) << "SUPERVISOR\n";
    workLogFile << "------------------------------------------------------------------------------------------------------------------\n";
    workLogFile << left << setw(24) << name << setw(25) << contact << setw(20) << date << setw(20) << department << setw(11) << supervisor << "\n\n";

    workLogFile << "------------------------------------------------------------------------------------------------------------------\n";
    workLogFile << left << setw(45) << "ACTIVITY" << setw(12) << "START TIME" << setw(12) << "END TIME" << setw(10) << "TOTAL" << setw(15) << "STATUS" << "NOTES\n";
    workLogFile << "------------------------------------------------------------------------------------------------------------------\n";

    // Initialize totalschtime accumulator
    int totalschTimeMinutes = 0;

    // Allocate memory for the activities array dynamically
    /*
        Dynamic memory allocation is used here because the number of activities
        is not known at compile time. Allocating memory dynamically allows us
        to create an array of the exact size needed based on user input.
    */
    string* activities = new string[numActivities];

    // Loop through activities and Collect details for each activity
    for (int i = 0; i < numActivities; i++) {
        string activity, startTime, endTime, status, notes;
        int totalMinutes;

        cout << "\n-----------------" << endl;
        cout << "Enter Activity " << (i + 1) << ": ";
        getline(cin, activity);
        activities[i] = activity; // Store activity in array
        cout << "------------------------------------------------------------------\n" << endl;

        // Collect and validate start time
        while (true) {
            cout << "Enter Start Time (24-hour format) (HH:MM): ";
            getline(cin, startTime);
            if (isValidTime(startTime)) {
                break;
            }
            cout << "Invalid time format. Please enter time in HH:MM format.\n" << endl;
        }

        // Collect and validate end time
        while (true) {
            cout << "Enter End Time (24-hour format) (HH:MM): ";
            getline(cin, endTime);
            if (isValidTime(endTime)) {
                break;
            }
            cout << "Invalid time format. Please enter time in HH:MM format.\n" << endl;
        }

        cout << "\nEnter Status (e.g., In Progress, Complete, Not Started): ";
        getline(cin, status);
        cout << "Enter Notes: ";
        getline(cin, notes);
        cout << "------------------------------------------------------------------\n" << endl;

        // Calculate the total time in minutes
        int startMinutes = timeToMinutes(startTime);
        int endMinutes = timeToMinutes(endTime);
        totalMinutes = endMinutes - startMinutes;

        if (totalMinutes < 0) {
            // Adjust for cases where the end time is after midnight
            totalMinutes += 24 * 60;
        }

        // Accumulate the total scheduled time in minutes
        totalschTimeMinutes += totalMinutes;

        // Convert total time and accumulated time back to HH:MM format
        string totalTimeStr = minutesToTime(totalMinutes);
        string totalschTimeStr = minutesToTime(totalschTimeMinutes);

        // Write the activity to the file with better formatting
        workLogFile << left << setw(45) << activity << setw(12) << startTime << setw(12) << endTime
            << setw(10) << totalTimeStr << setw(15) << status << notes << "\n";
    }

    // Write total scheduled time to file
    workLogFile << "\n------------------------------------------------------------------------------------------------------------------\n";
    workLogFile << "Total Scheduled Time : " << minutesToTime(totalschTimeMinutes) << "\n";
    workLogFile << "------------------------------------------------------------------------------------------------------------------\n\n";

    system("cls");



    // The Start OF Productivity Tracking
    workLogFile << "\nProductivity Tracking\n";
    workLogFile << "------------------------------------------------------------------------------------------------------------------------------------------------------------\n";
    workLogFile << left << setw(30) << "ACTIVITY" << setw(16) << "CATEGORY" << setw(14) << "FOCUS LEVEL" << setw(15) << "DISTRACTIONS"
        << setw(15) << "PRODUCTIVE?" << setw(30) << "EVALUATION" << setw(22) << "SATISFACTION" << setw(9) << "FEEDBACK\n";
    workLogFile << "------------------------------------------------------------------------------------------------------------------------------------------------------------\n";

    int productiveTasks = 0;
    int nonProductiveTasks = 0;

    cout << "---------------------" << endl;
    cout << "Productivity Tracking" << endl;
    cout << "---------------------" << endl;
    cout << "\n----------------------------------------------------------------------------------------------------------\n";

    // Collect productivity details for each activity
    for (int i = 0; i < numActivities; i++) {
        string category, productive, priority, evaluate, satisfaction, feedback;
        int focusLevel, distractions;

        do {
            cout << "\nEnter Category for activity \"" << activities[i] << "\" (e.g., Emailing, Coding, Meetings): ";
            getline(cin, category);
        } while (category.empty());

        cout << "\nRate the focus level required for \"" << activities[i] << "\" on a scale of 1-5: ";
        while (!(cin >> focusLevel) || focusLevel < 1 || focusLevel > 5) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "\nInvalid Input. Please enter a number between 1 and 5: ";
        }

        cout << "\nHow often were you distracted during \"" << activities[i] << "\" on a scale of 1-5: ";
        while (!(cin >> distractions) || distractions < 1 || distractions > 5) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "\nInvalid Input. Please enter a number between 1 and 5: ";
        }

        cout << "\nWas the activity \"" << activities[i] << "\" productive? (Yes/No): ";
        cin.ignore();
        getline(cin, productive);

        // Validate answer
        while (!isValidAnswer(productive)) {
            cout << "Invalid input. Please answer (Y-Yes or N-No): ";
            getline(cin, productive);
        }

        // This is done to ensure consistency throughout the answers in the checklist and Count productive/non-productive tasks
        if (productive == "YES" || productive == "Yes" || productive == "Y" || productive == "y") {
            productive = "Yes";
            productiveTasks++;
        }
        else {
            productive = "No";
            nonProductiveTasks++;
        }

        // Collect additional feedback
        do {
            cout << "\nHow would you evaluate the activity \"" << activities[i] << "\"? (e.g., highly productive, could have been better): ";
            getline(cin, evaluate);
        } while (evaluate.empty());

        do {
            cout << "\nHow satisfied were you with the completion of \"" << activities[i] << "\"? (e.g., very satisfied, somewhat satisfied, not satisfied): ";
            getline(cin, satisfaction);
        } while (satisfaction.empty());

        do {
            // Additional open-ended feedback question
            cout << "\nPlease provide any additional thoughts on the activity \"" << activities[i] << "\": ";
            getline(cin, feedback);
        } while (feedback.empty());
        cout << "\n----------------------------------------------------------------------------------------------------------\n";

        // Write productivity details to file with formatting
        workLogFile << left << setw(30) << activities[i] << setw(16) << category << setw(14) << focusLevel
            << setw(15) << distractions << setw(15) << productive << setw(30) << evaluate << setw(22) << satisfaction << setw(20) << feedback << "\n";
    }

    //Ask for user's overall experience
    cout << "\nHow was your overall task experience? : ";
    cin >> experience;

    // Write productivity summary to file
    workLogFile << "\n------------------------------------------------------------------------------------------------------------------------------------------------------------\n";
    workLogFile << "Productive Tasks     : " << productiveTasks << "\n";
    workLogFile << "Non-Productive Tasks : " << nonProductiveTasks << "\n";
    workLogFile << "Total Number of Task Completed: " << numActivities << "\n";
    workLogFile << "------------------------------------------------------------------------------------------------------------------------------------------------------------\n";
    workLogFile << "Overall Experience : " << experience << endl;
    workLogFile << "------------------------------------------------------------------------------------------------------------------------------------------------------------\n\n\n";
    workLogFile << "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx\n" << endl;

    // Free the allocated memory
    delete[] activities;

    // Close the file and update work entry number
    workLogFile.close();
    updateWorkNumber(workNumber);

    cout << "\nWork log saved successfully to WorkLog.txt!" << endl;
    //Wait for user to continue
    cout << "\nEnter any key to continue...";
    cin.ignore();
    cin.get();
    system("cls");
}

/*
 // Function to check if the time format is valid
  Checks if the given time string is in a valid HH:MM format.

  :param timeStr - The time string to check.
  :return - True if the time string is valid, otherwise false.
 */
bool isValidTime(const string& timeStr) {
    // Check if the length of the string is 5 and if the third character is a colon
    if (timeStr.length() != 5 || timeStr[2] != ':')
    {
        return false; // Invalid format
    }

    // Extract hours and minutes from the string
    int hours = stoi(timeStr.substr(0, 2)); // Get hours from the first two characters
    int minutes = stoi(timeStr.substr(3, 2)); // Get minutes from the last two characters

    // Check if hours are within the range [0, 23] and minutes are within the range [0, 59]
    return hours >= 0 && hours < 24 && minutes >= 0 && minutes < 60;
}

/*
 // Function to convert HH:MM to total minutes
  Converts a time string in HH:MM format to the total number of minutes.

  :param timeStr - The time string to convert.
  :return - The total number of minutes.
 */
 // Function to convert HH:MM to total minutes
int timeToMinutes(const string& timeStr) {
    int hours, minutes;
    char colon;
    istringstream timeStream(timeStr);
    timeStream >> hours >> colon >> minutes;
    return hours * 60 + minutes;
}

/*
 // Function to convert total minutes to HH:MM format
  Converts total minutes into a time string in HH:MM format.

  :param totalMinutes - The total number of minutes to convert.
  :return - The time string in HH:MM format.
 */
string minutesToTime(int totalMinutes) {
    int hours = totalMinutes / 60;
    int minutes = totalMinutes % 60;
    ostringstream timeStream;
    timeStream << setw(2) << setfill('0') << hours << ":"
        << setw(2) << setfill('0') << minutes;
    return timeStream.str();
}

/*
 // Function to get the current work number from the file
  Retrieves the current work number from the WorkNumber.txt file.

  :return int - The current work number. If the file cannot be opened, returns 0.
 */
int getCurrentWorkNumber() {
    int workNumber = 0;
    ifstream workFile("WorkNumber.txt");

    if (workFile.is_open()) {
        workFile >> workNumber; // Read the work number from the file
        workFile.close();
    }
    else {
        cerr << "Error: Unable to open WorkNumber.txt. Starting from entry 1." << endl;
    }
    return workNumber; // Return the current work number
}

/*
 // Function to update the login number file with the new login number
  Updates the WorkNumber.txt file with the new work number.

  :param newWorkNumber - The new work number to write to the file.
 */
void updateWorkNumber(int newWorkNumber) {
    ofstream workFile("WorkNumber.txt");

    if (workFile.is_open()) {
        workFile << newWorkNumber; // Write the new work number to the file
        workFile.close();
    }
    else {
        cerr << "Error: Unable to update WorkNumber.txt." << endl;
        //Wait for user to continue
        cout << "\nEnter any key to continue...";
        cin.ignore();
        cin.get();
    }

}

/*
 // Function to generate and display a report of logged activities
 Generates and displays a report of logged activities from WorkLog.txt.
 */
void generateProductivityReport() {
    ifstream in_File("WorkLog.txt");
    string line;

    if (in_File.is_open()) {
        cout << "\nGenerated Report:\n" << endl;
        while (getline(in_File, line)) {
            cout << line << endl;
        }
        in_File.close(); // Close the file after reading

    }
    else {
        cout << "Unable to open the Work Log file." << endl;
    }

    //Wait for user to continue
    cout << "\nEnter any key to continue...";
    cin.ignore();
    cin.get();
    system("cls");
}