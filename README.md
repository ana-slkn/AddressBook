# Address Book Application

## Description

The Address Book Application is a command-line interface program designed for managing contacts. Users can perform various operations such as creating, editing, deleting, and displaying contacts in an organized manner. The application stores contact information in a `.txt` file in CSV format, facilitating easy external viewing and editing.

## Getting Started

### Dependencies

- A C++ compiler (e.g., G++ or Clang)
- Make (optional, for compiling multiple files)

### Running the Program

To compile the program, follow these steps:

1. Open your command-line interface (CLI) and navigate to the project directory.
2. Create the object file:
   ```bash
   g++ Contact.cpp FileFunctions.cpp Functions.cpp HelpFunctions.cpp Main.cpp -o main
   ```
3. Execute the following command:

    ```bash
    main.exe
    ```

### File Format

Contacts are stored in a text file in CSV format. Here's an example of the file structure (`ab.txt`):

```
G,Smith,John,555-1234,john.smith@example.com
B,Doe,Jane,555-5678,jane.doe@example.com,CompanyX,Manager,555-9012
P,Roe,Richard,555-2468,richard.roe@example.com,1985-07-12,www.richardroe.com
F,Doe,Emily,555-1357,emily.doe@example.com,Sister,2023-05-15
```

The first character indicates the contact type:

- `G` for Generic
- `B` for Business
- `P` for Personal
- `F` for Family

Subsequent fields include the last name, first name, phone number, and email address. Business contacts also include company name, job title, and business phone. Personal contacts include birthday and personal website. Family contacts include relationship and important dates.

## Features

- **Create or Open an Address Book**: Start a new address book or open an existing one.
- **Add Contacts Alphabetically**: Add new contacts alphabetically by last name.
- **Display Contacts**: View all contacts or filter by type (Generic, Business, Personal, Family).
- **Search for Contacts**: Find contacts by name, phone number, or email.
- **Edit Contacts**: Modify existing contact details.
- **Delete Contacts**: Remove individual contacts or the entire address book.
