#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_VOTERS 100
#define MAX_NAME_LENGTH 50

// Structure to represent a voter
typedef struct {
    int id;
    char name[MAX_NAME_LENGTH];
    int age;
    int voted; // Flag to check if the voter has already voted
    int party; // Party chosen by the voter (1 to 4)
} Voter;

// Function to generate a unique ID for each voter
int generateID() {
    static int id = 0;
    return ++id;
}

// Function to register a new voter
void registerVoter(Voter voters[], int *numVoters) {
    Voter newVoter;
    printf("Enter your name: ");
    scanf("%s", newVoter.name);
    printf("Enter your age: ");
    scanf("%d", &newVoter.age);

    if (newVoter.age < 18) {
        printf("Sorry, you must be 18 or older to vote.\n");
        return;
    }

    newVoter.id = generateID();
    newVoter.voted = 0;

    voters[*numVoters] = newVoter;
    (*numVoters)++;

    printf("You have been registered successfully. Your ID is: %d\n", newVoter.id);
}

// Function to vote for a party
void vote(Voter voters[], int numVoters, int id) {
    for (int i = 0; i < numVoters; i++) {
        if (voters[i].id == id) {
            if (voters[i].voted) {
                printf("You have already voted.\n");
                return;
            }
            if (voters[i].age < 18) {
                printf("You are not eligible to vote.\n");
                return;
            }
            printf("Welcome, %s! Please select a party to vote:\n", voters[i].name);
            printf("1. Party A\n");
            printf("2. Party B\n");
            printf("3. Party C\n");
            printf("4. Party D\n");
            printf("Enter your choice (1-4): ");
            scanf("%d", &voters[i].party);
            printf("Thank you for voting!\n");
            voters[i].voted = 1;
            return;
        }
    }
    printf("Invalid ID.\n");
}

// Function to display voter details
void displayDetails(Voter voters[], int numVoters, int id) {
    for (int i = 0; i < numVoters; i++) {
        if (voters[i].id == id) {
            printf("Name: %s\n", voters[i].name);
            printf("Age: %d\n", voters[i].age);
            if (voters[i].voted)
                printf("Party Voted for: %d\n", voters[i].party);
            else
                printf("You have not voted yet.\n");
            return;
        }
    }
    printf("Invalid ID.\n");
}

// Function to display election results
void displayResults(Voter voters[], int numVoters) {
    int partyVotes[4] = {0};

    for (int i = 0; i < numVoters; i++) {
        if (voters[i].voted) {
            partyVotes[voters[i].party - 1]++;
        }
    }

    printf("\n--- Election Results ---\n");
    printf("Party A: %d votes\n", partyVotes[0]);
    printf("Party B: %d votes\n", partyVotes[1]);
    printf("Party C: %d votes\n", partyVotes[2]);
    printf("Party D: %d votes\n", partyVotes[3]);
}

int main() {
    Voter voters[MAX_VOTERS];
    int numVoters = 0;
    int choice, id;

    do {
        printf("\n--- Election System Menu ---\n");
        printf("1. Register\n");
        printf("2. Vote\n");
        printf("3. Display Details\n");
        printf("4. Display Results\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1:
                registerVoter(voters, &numVoters);
                break;
            case 2:
                printf("Enter your ID: ");
                scanf("%d", &id);
                vote(voters, numVoters, id);
                break;
            case 3:
                printf("Enter your ID: ");
                scanf("%d", &id);
                displayDetails(voters, numVoters, id);
                break;
            case 4:
                displayResults(voters, numVoters);
                break;
            case 5:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while(choice != 5);

    return 0;
}
