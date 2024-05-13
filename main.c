/********* main.c ********
    Student Name 	= Andrew Roberts
    Student Number	= 101268396
*/

// Includes go here
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include "a3_nodes.h"
#include "a3_functions.h"

int main()
{
    /******** DONT MODIFY THIS PART OF THE CODE ********/
    /* THIS CODE WILL LOAD THE DATABASE OF USERS FROM THE FILE
       AND GENERATE THE STARTING LINKED LIST.
    */
    FILE *csv_file = fopen("user_details.csv", "r");
    if (csv_file == NULL)
    {
        perror("Error opening the CSV file");
        return 1;
    }
    // Parse CSV data and create users
    user_t *users = read_CSV_and_create_users(csv_file, 50);

    fclose(csv_file);
    /******** DONT MODIFY THIS PART OF THE CODE ********/

    /* IMPORTANT: You must use the users linked list created in the code above.
                  Any new users should be added to that linked list.
    */

    // Your solution goes here

    // prints the welcome message for users
    spacer('*', 47);
    printf("\tWelcome to Text-Based Facebook\n");
    spacer('*', 47);

    // Declares variables to be used throughout main
    unsigned short choice = 0;
    char username[30];
    char password[15];
    user_t *node;
    user_t *friend_node;

    // Loop to prompt the user to choose options in the main menu and carry out the processes of those options until the user exits the program via 6
    do
    {
        // prompts the user to enter a value for their choice in the main menu until they enter a valid choice
        do
        {
            print_menu();
            printf("Enter your choice: ");
            choice = user_input(1, 3);
        } while (choice < 1 || choice > 3);

        // switch case to change which process is executed based on the user's input
        switch (choice)
        {

        // option 1 for registering a new user
        case (1):

            // prompts the user to enter a username
            printf("Enter a username: ");
            scanf("%s", username);

            // prompts the user to enter a password
            printf("Enter an upto 15 characters password: ");
            scanf("%s", password);

            // calls find_user to check if username alreadyt exists
            if (find_user(users, username) == NULL)
            {
                // calls add_user to add it to the linked list of users
                add_user(users, username, password);
                printf("\n**** User Added! ****\n");
            }
            else
            {
                printf("Username already exists\n");
            }

            // exits the switch case and returns to main menu
            break;

        // option 2 for logging in with existing user's information
        case (2):
            unsigned short choice_2 = 0;

            printf("Enter your username: ");
            scanf("%s", username);

            printf("Enter your password: ");
            scanf("%s", password);

            node = find_user(users, username);

            if (node == NULL || strcmp(node->password, password))
            {
                printf("Invalid username/password combination\n");
                break;
            }

            do
            {
                print_user_menu(node);
                printf("\nEnter your choice: ");
                choice_2 = user_input(1, 5);

                switch (choice_2)
                {
                // option 1 for changing the user's password
                case (1):

                    // prompts the user to enter a new password for the user they entered
                    printf("\nEnter a new password that is upto 15 characters: ");
                    scanf("%s", password);
                    strcpy(node->password, password);
                    printf("\n**** Password changed! ****\n");

                    // exits the switch case and returns to main menu
                    choice_2 = 0;
                    break;

                // option 2 for managing a user's posts
                case (2):

                    // calls display_user_posts to print the posts of the user entered
                    display_user_posts(node);

                    // Initializes choice_3 variable for use in new switch case
                    unsigned short choice_3 = 0;

                    // do while loop to return the user to the posts menu until they choose to exit to the main menu by entering 3
                    do
                    {
                        // prompts the user to choose one of the options shown in the post's menu
                        printf("\n1. Add a new user post"
                               "\n2. Remove a users post"
                               "\n3. Return to user menu"
                               "\n\nYour choice: ");
                        choice_3 = user_input(1, 3);

                        // switch case to perform the different options based on user input
                        switch (choice_3)
                        {

                        // option 1 for adding a new post, prompts the user to enter the post's content and calls add_post to add it to the user's posts linked list
                        // calls display user's posts to display the new updated list of posts for the user
                        case (1):
                            char post[250];
                            printf("Enter your post content: ");
                            scanf(" %[^\n]s", post);
                            add_post(node, post);
                            printf("Post added to your profile.\n");
                            display_user_posts(node);
                            break;

                        // option 2 for removing a post, prompts the user to choose which post they want to delete
                        case (2):
                            printf("Which post would you like to delete? ");
                            short int input;
                            scanf("%hd", &input);

                            // if delete_post returns true print a message notifying the user the post was deletedd successfully
                            if (delete_post(node, input))
                            {
                                printf("Post %hd was deleted successfully!\n", input);
                            }

                            // Notifies the user they entered an invalid post number
                            else
                            {
                                printf("Invalid post's number\n");
                            }

                            // calls display_user_posts and exits the switch case returning to the manage posts menu
                            display_user_posts(node);
                            break;
                        }
                    } while (choice_3 != 3);

                    // exits the switch case and returns to main menu
                    choice_2 = 0;
                    break;

                // option 3 for managing a user's friends
                case (3):

                    // Initializes choice_4 variable for use in new switch case
                    unsigned short choice_4 = 0;

                    // do while loop to return the user to the friends menu until they choose to exit to the main menu by entering 4
                    do
                    {
                        // prompts the user to choose an option from the friends menu
                        printf("\n");
                        spacer('-', 47);
                        printf("\t\t%s's friends\n", node->username);
                        spacer('-', 47);

                        printf("\n1. Display all user's friends"
                               "\n2. Add a new friend"
                               "\n3. Delete a friend"
                               "\n4. Dispaly a friend's posts"
                               "\n5. Return to user menu"
                               "\n\nYour choice: ");

                        choice_4 = user_input(1, 5);

                        // switch case to perform the operations of each menu option based on user input
                        switch (choice_4)
                        {

                        // option 1 calls dispaly_user_friends to display the list of friends of the inputed user
                        case (1):
                            display_user_friends(node);
                            break;

                        // option 2 prompts the user to enter the name of a new friend and calls add_friend to add it to the inputted user's friends linked list
                        case (2):
                            printf("Enter a new friend's name: ");
                            scanf("%s", username);

                            friend_node = find_user(users, username);

                            // checks if user exists
                            if (friend_node == NULL)
                            {
                                printf("\n");
                                spacer('-', 47);
                                printf("\t\tUser not Found.\n");
                                spacer('-', 47);
                            }
                            else
                            {
                                add_friend(users, node, username);
                                printf("Friend added to the list.\n");
                            }
                            break;

                        // option 3 prompts the user to enter the name of the friend they want to remove
                        case (3):
                            display_user_friends(node);
                            printf("\nEnter a friend's name to delete: ");
                            scanf("%s", username);

                            // calls delete_friend returns where if it returns false, notifies the user they have inputed an invalid friends name and returns them to the manage friends menu
                            if (!delete_friend(node, username))
                            {
                                printf("Invalid friend's name\n");
                            }

                            // calls dispaly_user_friends and exits the switch case, returning the manage friends menu
                            display_user_friends(node);
                            choice_2 = 0;
                            break;

                        // option 4 prompts the user to enter the name of the friend whose posts they want to view
                        case (4):
                            display_user_friends(node);
                            printf("\nEnter a friend's name to view their posts: ");
                            scanf("%s", username);

                            friend_node = find_user(users, username);

                            // checks if friend_node was found in users
                            if (friend_node == NULL)
                            {
                                printf("Invalid friend's name\n");
                            }

                            // displays the posts of the friend the user entered
                            else
                            {
                                display_user_posts(friend_node);
                            }
                            break;
                        }
                    } while (choice_4 != 5);

                    // exits the switch case and returns to main menu
                    break;

                // option 4 for dispalying all posts by calling display_all_posts
                case (4):
                    display_all_posts(users);

                    // exits the switch case and returns to main menu
                    choice_2 = 0;
                    break;
                }
            } while (choice_2 != 5);
        }
    } while (choice != 3);

    // prints a thank you message to the user and calls teardown to free the memory for the users, their friends and their posts before exiting the program
    spacer('*', 47);
    printf("Thank you for using Text-Based Facebook\n\t\tGoodBye!\n");
    spacer('*', 47);
    teardown(users);
    return EXIT_SUCCESS;
}