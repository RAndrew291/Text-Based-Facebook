# Text-Based Facebook

## Overview
**Text-Based Facebook** is a social networking platform implemented in C. It allows users to register, authenticate, manage friends, create and delete posts, and view a timeline. The project uses linked lists for efficient data management and provides a menu-driven interface for an intuitive user experience.

## Features
- **User Registration & Login**: Secure authentication system for users.
- **Friend Management**: Add and remove friends from a user's network.
- **Post Creation & Deletion**: Users can create and delete posts.
- **Timeline Display**: View posts from friends in chronological order.
- **File Handling**: Persist user data and posts between sessions.

## Technologies Used
- **Programming Language**: C
- **Data Structures**: Linked Lists
- **File Handling**: Used for data persistence
- **User Authentication**: Basic validation and login functionality

## Installation & Usage
### Prerequisites
- GCC Compiler
- Terminal (Linux/macOS) or Command Prompt (Windows)

### Compilation & Execution
1. Clone the repository:
   ```sh
   git clone <repository_url>
   cd text-based-facebook
   ```
2. Compile the program:
   ```sh
   gcc main.c a3_functions.c -o facebook
   ```
3. Run the program:
   ```sh
   ./facebook
   ```

## Project Structure
```
text-based-facebook/
├── main.c            # Entry point of the application
├── a3_functions.c    # Implementation of core functionalities
├── a3_functions.h    # Function declarations and prototypes
├── a3_nodes.h        # Data structure definitions
├── user_details.csv  # CSV file containing user data (if applicable)
├── README.md         # Project documentation
```

## How It Works
- **User Registration**: Users create an account with a username and password.
- **Login & Authentication**: Users log in with their credentials to access the platform.
- **Friend Management**: Users can add friends, remove them, and view their friends list.
- **Post Management**: Users can create posts, delete posts, and view their timeline.
- **Timeline Display**: Users can see posts from their friends in order.
- **Data Persistence**: User data, friend relationships, and posts are stored in a CSV file.

---
**Author**: Andrew Roberts


