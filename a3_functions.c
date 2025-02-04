/********* definitions.c ********
    Student Name 	= Andrew Roberts
    Student Number	= 101268396
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "a3_nodes.h"
#include "a3_functions.h"

// Your solution goes here

/*
   Function that creates a new user and adds it to a sorted (ascending order) linked list at
   the proper sorted location. Return the head of the list.
*/
user_t *add_user(user_t *users, char *username, const char *password)
{
   // converts uppercase to lowercase
   unsigned short length = strlen(username);

   for (unsigned short i = 0; i < length; i++)
   {
      if (username[i] >= 'A' && username[i] <= 'Z')
      {
         username[i] += 32;
      }
   }

   // Initializes user_t struct current equal to users struct to use for traversing the linked list
   user_t *current = users;

   // Allocates memory for new user and termninates the program by assert if memory allocation fails
   user_t *new_user = malloc(sizeof(user_t));
   assert(new_user != NULL);

   // initialize new user's structure details
   strcpy(new_user->username, username);
   strcpy(new_user->password, password);
   new_user->next = NULL;
   new_user->friends = NULL;
   new_user->posts = NULL;

   // makes new_user the head of the link list if conditions evaluate to true
   if (users == NULL || strcmp(username, users->username) < 0)
   {
      new_user->next = users;
      return new_user;
   }

   // loop to iterate through the linked list to the proper location
   while (current->next != NULL && strcmp(username, current->next->username) > 0)
   {
      current = current->next;
   }

   // Inserts new_user to the proper location in the linked list
   new_user->next = current->next;
   current->next = new_user;

   return users;
}

/*
   Function that searches if the user is available in the database
   Return a pointer to the user if found and NULL if not found.
*/
user_t *find_user(user_t *users, char *username)
{
   // Initializes current user_t structure for use in loop
   user_t *current = users;

   // converts uppercase to lowercase
   unsigned short length = strlen(username);

   for (unsigned short i = 0; i < length; i++)
   {
      if (username[i] >= 'A' && username[i] <= 'Z')
      {
         username[i] += 32;
      }
   }

   // Iterates through the linked list, comparing each username member to the inputted username
   while (current != NULL)
   {
      if ((strcmp(current->username, username)) == 0)
      {
         return current;
      }
      current = current->next;
   }
   return NULL;
}

/*
   Function that creates a new friend's node.
   Return the newly created node.
*/
friend_t *create_friend(char *username)
{
   // creates a new node called new_friend and terminates the program via assert if memory allocation fails
   friend_t *new_friend = malloc(sizeof(friend_t));
   assert(new_friend != NULL);

   // Initilizes the members of new friend
   strcpy(new_friend->username, username);
   new_friend->next = NULL;

   return new_friend;
}

/*
   Function that links a friend to a user. The friend's name should be added into
   a sorted (ascending order) linked list.
*/
void add_friend(user_t *users, user_t *user, char *friend)
{
   // converts uppercase to lowercase
   unsigned short length = strlen(friend);

   for (unsigned short i = 0; i < length; i++)
   {
      if (friend[i] >= 'A' && friend[i] <= 'Z')
      {
         friend[i] += 32;
      }
   }

   user_t *friend_node = find_user(users, friend);

   // checks if user exists
   if (friend_node == NULL)
   {
      return;
   }
   else
   {
      // calls create_friend to allocate memory for new_friend and sets current to be the the first friend node for the inputted user
      friend_t *new_friend = create_friend(friend);
      friend_t *current = user->friends;

      // sets new_friend as the first friend node for user if conditions are met
      if (user->friends == NULL || strcmp(new_friend->username, user->friends->username) < 0)
      {
         new_friend->next = user->friends;
         user->friends = new_friend;
      }
      else
      {
         // Traverses the linked list to find correct position to insert new node
         while (current->next != NULL && strcmp(new_friend->username, current->next->username) > 0)
         {
            current = current->next;
         }
         // Inserts new node at correct position
         new_friend->next = current->next;
         current->next = new_friend;
      }
      new_friend->posts = &(friend_node->posts);
   }
}

/*
   Function that removes a friend from a user's friend list.
   Return true of the friend was deleted and false otherwise.
*/
_Bool delete_friend(user_t *user, char *friend_name)
{
   // converts uppercase to lowercase
   unsigned short length = strlen(friend_name);

   for (unsigned short i = 0; i < length; i++)
   {
      if (friend_name[i] >= 'A' && friend_name[i] <= 'Z')
      {
         friend_name[i] += 32;
      }
   }
   // Initializes current and previous nodes for use in loop
   friend_t *current = user->friends;
   friend_t *previous = NULL;

   // traverses the linked list, keeping track of the previous node and moving to the next node in the linked list until the conditions are met
   while (current != NULL && strcmp(current->username, friend_name) != 0)
   {
      previous = current;
      current = current->next;
   }

   // returns false if could not find the friend in the linked list
   if (current == NULL)
   {
      return 0;
   }

   // if friend is at the start of the linked list, point head to the next node
   else if (previous == NULL)
   {
      user->friends = current->next;
   }

   // point the previous node to the node pointed at by current next to preserve its address
   else
   {
      previous->next = current->next;
   }

   // free the memory allocated for current node
   free(current);
   return 1;
}

/*
   Function that creates a new user's post.
   Return the newly created post.
*/
post_t *create_post(const char *text)
{
   // creates a new node called new_post and terminates the program via assert if memory allocation fails
   post_t *new_post = malloc(sizeof(post_t));
   assert(new_post != NULL);

   // initilizes the members of the new post
   strcpy(new_post->content, text);
   new_post->next = NULL;

   return new_post;
}

/*
   Function that adds a post to a user's timeline. New posts should be added following
   the stack convention (LIFO) (i.e., to the beginning of the Posts linked list).
*/
void add_post(user_t *user, const char *text)
{
   // calls create_post to allocate memory for new_post
   post_t *new_post = create_post(text);

   // Adds new post to the first position pointed to by the user's post member
   new_post->next = user->posts;
   user->posts = new_post;
}

/*
   Function that removes a post from a user's list of posts.
   Return true if the post was deleted and false otherwise.
*/
_Bool delete_post(user_t *user, int number)
{
   // calls post_counter to check if inputed number is greater than the number of post's the user has or if its less than one, if true return false
   if (number > post_counter(user) || number < 1)
   {
      return 0;
   }

   // Initializes current and previous nodes for use in loop
   post_t *current = user->posts;
   post_t *previous = NULL;
   unsigned short current_post = 1;

   // iterates through linked list to find post to delete
   while (current_post != number)
   {
      previous = current;
      current = current->next;
      current_post++;
   }

   // sets head of user's posts to the next node pointed at by current
   if (previous == NULL)
   {
      user->posts = current->next;
   }

   // sets previous to the next node pointed at by current to preserve its address
   else
   {
      previous->next = current->next;
   }

   // frees memory allocated for current posts
   free(current);
   return 1;
}

/*
   Function that displays a specific user's posts
*/
void display_user_posts(user_t *user)
{
   // Initializes variables for use in loop
   post_t *current = user->posts;
   unsigned short i = 1;

   spacer('-', 47);
   printf("\t\t%s's posts\n", user->username);

   // checks if user's post node is empty
   if (user->posts == NULL)
   {
      printf("No posts avaliable for %s.\n", user->username);
   }

   // Iterates through user's post link list, printing each post
   else
   {
      while (current != NULL)
      {
         printf("%hu- %s\n", i, current->content);
         current = current->next;
         i++;
      }
   }
   spacer('-', 47);
}

/*
   Function that displays a specific user's friends
*/
void display_user_friends(user_t *user)
{
   // Initializes variables for use in loop
   friend_t *current = user->friends;
   unsigned short i = 1;

   printf("\nList of %s's friends:\n", user->username);

   // checks if user's friends node is empty
   if (user->friends == NULL)
   {
      printf("No friends avaliable for %s.\n", user->username);
   }

   // Iterates through user's friends link list, printing each friend's username
   else
   {
      while (current != NULL)
      {
         printf("%hu- %s\n", i, current->username);
         current = current->next;
         i++;
      }
   }
}

/*
   Function that displays all the posts of 2 users at a time from the database.
   After displaying 2 users' posts, it prompts if you want to display
   posts of the next 2 users.
   If there are no more post or the user types “n” or “N”, the function returns.
*/
void display_all_posts(user_t *users)
{
   // Initializes variables for use in loop
   user_t *current_user = users;
   char user_choice;
   unsigned short count = 0;

   // Iterates through the first two user's posts linked lists, printing the content of each one
   while (current_user != NULL && count != 2)
   {
      // Initializes variables used for printing user's posts
      unsigned short post_count = 1;
      post_t *current_post = current_user->posts;

      // Iterates through current user's post linked list, printing each ones content
      while (current_post != NULL)
      {
         printf("%hu- %s: %s\n", post_count, current_user->username, current_post->content);
         current_post = current_post->next;
         post_count++;
      }

      // Increment current_user to next user node and count by 1
      current_user = current_user->next;
      count++;
   }

   // Asks the user if they want to display the next two users posts
   printf("\nDo you want to display the next 2 users posts? (Y/N): ");
   scanf(" %c", &user_choice);

   // Exits the funciton if there are no more user's or the user inputs N/n
   if (current_user == NULL || user_choice == 'N' || user_choice == 'n')
   {
      return;
   }

   // calls display_all_posts recursively while the user enters Y/y and there are still users left in the linked list
   else if (user_choice == 'Y' || user_choice == 'y')
   {
      display_all_posts(current_user);
   }
}

/*
   Function that free all users from the database before quitting the application.
*/
void teardown(user_t *users)
{
   // traverses through users linked list, freeing each user's friends, posts and then user nodes
   while (users != NULL)
   {
      user_t *current_user = users;
      users = users->next;

      // free the user's friends
      friend_t *current_friend = current_user->friends;
      while (current_friend != NULL)
      {
         friend_t *temp_friend = current_friend;
         current_friend = current_friend->next;
         free(temp_friend);
      }
      current_user->friends = NULL;

      // Free the user's posts
      post_t *current_post = current_user->posts;
      while (current_post != NULL)
      {
         post_t *temp_post = current_post;
         current_post = current_post->next;
         free(temp_post);
      }
      current_user->posts = NULL;

      // free the user node
      free(current_user);
   }
}

/*
   Function that prints the main menu with a list of options for the user to choose from
*/
void print_menu()
{
   printf("\n");
   spacer('*', 47);
   printf("\t\tMAIN MENU:\n");
   spacer('*', 47);
   printf("1. Register a new User"
          "\n2. Login with existing user's information"
          "\n3. Exit\n\n");
}

/*
Prints specified number of a character
*/
void spacer(char c, unsigned short n)
{
   // prints specified characterc, n times
   for (unsigned short i = 0; i < n; i++)
   {
      printf("%c", c);
   }
   printf("\n");
}

/*
   Gets user input for an unsigned short in specfied range, inclusive. If they enter an invalid value the function prompts the user to enter a valid input
*/
unsigned short int user_input(unsigned short n, unsigned short i)
{
   short signed int input;
   scanf("%hd", &input);       // gets user input
   if (input < n || input > i) // checks if input is less than n or greater than i
   {
      printf("Invalid Choice. Please try again.\n");
   }
   return input; // returns input
}

/*
   counts the number of post's for a specified user
*/
unsigned short post_counter(user_t *user)
{
   // Initializes post_t struct and counter to travers the users post and count how many there are
   post_t *current = user->posts;
   unsigned short count = 0;

   // Traverses the user's post linked list, incrementing the count by one each time
   while (current != NULL)
   {
      current = current->next;
      count++;
   }
   return count;
}

/*
   Function that prints the user menu with a list of options for the user to choose from
*/
void print_user_menu(user_t *user)
{
   printf("\n");
   spacer('*', 47);
   printf("\t\tWelcome %s:\n", user->username);
   spacer('*', 47);
   printf("\n1. Manage a user's profile (change password)"
          "\n2. Manage a user's posts (display/add/remove)"
          "\n3. Manage a user's friends (display/add/remove)"
          "\n4. Display All Posts"
          "\n5. Logout\n");
}
/*
   ******** DONT MODIFY THIS FUNCTION ********
   Function that reads users from the text file.
   IMPORTANT: This function shouldn't be modified and used as is
   ******** DONT MODIFY THIS FUNCTION ********
*/
user_t *read_CSV_and_create_users(FILE *file, int num_users)
{
   user_t *users = NULL;
   char buffer[500];
   fgets(buffer, sizeof(buffer), file); // Read and discard the header line
   int count = 0;
   for (int i = 0; i < num_users; i++)
   {
      fgets(buffer, sizeof(buffer), file);
      buffer[strcspn(buffer, "\r\n")] = 0; // Remove newline characters

      char *token = strtok(buffer, ",");
      char *token2 = strtok(NULL, ",");
      users = add_user(users, token, token2);
      char *username = token;

      token = strtok(NULL, ",");

      user_t *current_user = users;
      for (; current_user != NULL && strcmp(current_user->username, username) != 0; current_user = current_user->next)
         ;

      while (token != NULL && strcmp(token, ",") != 0 && count < 3)
      {
         if (strcmp(token, " ") != 0)
         {
            add_friend(users, current_user, token);
         }
         token = strtok(NULL, ",");
         count++;
      }
      count = 0;

      // token = strtok(NULL, ",");
      while (token != NULL && strcmp(token, ",") != 0)
      {
         add_post(current_user, token);
         token = strtok(NULL, ",");
      }
   }
   return users;
}
