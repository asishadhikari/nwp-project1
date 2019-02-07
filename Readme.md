  # Assignment 1 - Simple Client Server Application

  ![logo_c]
  # Features:
  - The **client** program reads input from user and performs the following actions repeatedly until directed to exit:
    - If the user enters **'s'** it will ask user to enter a string. It then sends *"CAP\nxxx\n"* to the server (where "xxx" is the string entered by the user,which could input any character except"\n"), and receives a message from the server and display the message on the screen.
    - If the user enters **'f'** it will ask user to enter a string. It then sends "FILE\nxxx\n" to the server (where "xxx" is the string entered by the user), and receives data from the server and savesthe data to a file named "xxx" in the directory where the client program is in.
    - If the user enters **'q'** it will exit.
    - If the user enters anything else, it will ignore.
  - The **server** program performs following operations:
    - If **"CAP\nxxx\n"** is received from the client, it capitalizes the received string and sends **"###\nCCC"** back to the client, where "###" is the number of characters in the capitalized string and "CCC" is the capitalized string. If a character has no upper case, such as a comma, the character is sent back as it is. 
    - If **"FILE\nxxx\n"** is received from the client,it reads the content from the file named "xxx" from the directory where the server program is in and sends **"###\nDDD"** back to the client,where"###" is the number of bytes of the file and "DDD" is the content of the file. Note that the file may contain binary data such as images. If no file of the name "xxx" exists, it sends **"###\nNOT FOUND"** back to the client, where "###" is the number of characters in the string of "NOT FOUND". 
    - The server supports multiple connections with the client simultaneously.

  # To Build:
  ``` sh
  $ cd nwp-project1
  $ Make
  ```
  Run  ```make clean``` to clear the compiled binaries.
  # To Run:
  > Run client as:
  >>``` sh
  >>$ cd nwp-project1
  >>$ ./client xxx.xxx.xxx yy
  >>```
  > Run server as:
  >>``` sh
  >>$ cd nwp-project1
  >>$ ./server yy
  >>```

  Where ```xxx.xxx.xxx``` is the server IP address and ```yy``` is the port number. 

  [logo_c]: <https://seeklogo.com/images/C/c-programming-language-logo-9B32D017B1-seeklogo.com.png>
