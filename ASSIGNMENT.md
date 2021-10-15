## Early Release Disclaimer:

This is an early release version of the programming assignment. We expect to enable Gradescope for evaluation. That might lead to small changes to how the output is produced and some of the expectations listed below. We are releasing this PA early so you can get started with the logic of the programs. More information will be provided about Gradescope in the next few days.

## Objective:

Understand creation of sockets
Understand the difference between TCP and UDP
Understand that application protocols often are simple plain text messages with special meanings 
Understand how to parse simple text commands

## Introduction:

In this assignment, you will create a chat room on a single computer where you and your (imaginary) friends can chat with each other. You will create the chat room application twice: once using TCP sockets and another using UDP sockets.

The following steps will be required for a functional chat room application:

1. Create a server program that is always running on a specific port (5001).
2. Create a client program that can join this server.
3. The client needs a display name and a passcode to enter the chat room. (Assume all clients use the same passcode but different display name).
4. The job of the server is to accept connections from clients, get their display name and passcode (in plaintext), verify that the passcode is correct and then allow clients into the chat room.
5. When any client sends a message, the display name is shown before the message, and the message is delivered to all other current clients. 
6. Clients can type any text message, or can type one of the following shortcut codes to display specific text to everyone:
- Type :Exit to close your connection and terminate the client
- [Fun part - not graded] '\' overrides the next word until a space or newline. For example, \:mytime will print :mytime instead of the actual time.
```
- Type :) to display [feeling happy]
- Type :( to display [feeling sad]
- Type :mytime to display the current time
- Type :+1hr to display the current time + 1 hour
```

For :mytime and :+1hr, please use the [c standard ctime()](https://www.cplusplus.com/reference/ctime/) function to format the date like this:

Mon Aug 13 08:23:14 2012

## What will you learn?

- Basic socket programming to create a client-server application
- How do multiple clients connect to a single server?
- How to keep multiple persistent TCP connections alive?
- Text parsing to develop a custom application layer protocol. (This is, in spirit, very similar to how HTTP works, for example)
- The difference between TCP and UDP

## Which programming language to use?

**We require you to use C or C++ for this assignment.** 

[Do we hear a groan?] This is important to understand the bare-bones working of computer networks. At its heart, Computer Networking is a systems course and for this programming assignment, we want you to understand the internal details of how servers and clients work. 

We are not restricting the operating system, but would prefer Linux or Linux on Mac. Windows is okay, but might be too much trouble to install Visual Studio for C/C++. We prefer if you use a Linux VM instead (for Windows computers). 

## Assignment Details

### Connection Establishment and Password Checking - Single Client - TCP (20 points)

You will create two programs: a client and a server. Each program takes the follow CLI parameters: the client takes the server's IP and listening port, the username, and the password (all clients should use the same password). The server takes its listening port and the password.

If the password is correct the client should receive a welcome message "Welcome to the CS3251 Chat Room", otherwise, it should receive a failure message "Incorrect passcode". Whenever, a new client joins the chatroom, all other clients should receive a message indicating the username of the new user that has just joined the room.

```
Command: ​./chatserver -start -port 5001
Output​: Server started on port 5001. Accepting connections
```

```
Command​: ./chatclient -join -host <hostname> -port 5001 -username<username> -passcode <passcode>
Output​ (on Server): <username> joined the chatroom
Output​ (on new Client): Connected to <hostname> on port 5001
```

Resource: Sample code for providing command line arguments to a C application https://linux.die.net/man/3/getopt_long

### Connection Establishment and Password Checking - Multiple Clients - TCP (10 points)

The server should be able to handle multiple clients connecting to it. This means that by running the above client command again (with a different username), the server should perform similarly. The server should also inform the already-connected clients that a new client has joined.

```
Command​: ./chatclient -join -host <hostname> -port 5001 -username<username> -passcode <passcode>
Output​ (on Server): <username> joined the chatroom
Output​ (on new Client): Connected to <hostname> on port 5001
Output (on all other clients): <username> joined the chatroom
```

You don't have to check for unique usernames, we will only test the code with unique usernames.

### Chat Functionality - TCP (10 points)

After successfully connected to the server, clients should be able to type messages that get sent to the server when the user enters a newline. All text before the newline should be sent to the server, displayed on the server's screen, and broadcasted and displayed on the screens of all clients.

```
Command​ (on a connected client with username: <username>): Hello Room
Output​ (on Server): <username>: Hello Room
Output​ (on the sending client): <username>: Hello Room
Output (on all other clients): <username>: Hello Room
```

If the chat functionality works with just one client, you will get only 2 points.

### Chat Shortcuts - TCP (5 points)

As discussed earlier, clients should be able to send shortcuts that are translated to text. The shortcut should be displayed as full text on all screens.

```
Command​ (on a connected client): :)
Output​ (on Server): <username>: [Feeling Happy]
Output​ (on the sending client): <username>: [Feeling Happy]
Output (on all other clients): <username>: [Feeling Happy]
```

Each shortcut is worth 1 points.

### Repeat all above functionality using UDP sockets (45 points)

### Notes and Suggestions

The Gradescope Autograder expects very specific outputs from your programs. Make sure that there are no extra lines or missing/extra spaces. Make sure your output looks like this:

```
Server started on port 5001. Accepting connections
alex joined the chatroom
alex: Hello World!
...
```

Rather than

```
Server started on port 5001. Accepting connections

alex joined the chatroom
alex:Hello World!
...
```

### Write a short report on the differences between the two implementations, answering the question of "In what scenarios would UDP be more preferable to TCP?" (10 points)

Please remember 

Your submission will be graded only if it compiles. ​We will be using Ubuntu 18.04 for testing your code. But if your submission has some extraordinary requirements (OS other than Linux, some obscure library (pthread is not obscure), etc.) please let us know beforehand and we can confirm if it is ok for you to use.

Additional note on resources​: GT provides computing resources for CoC students which you can make use of to help you with this assignment. Students have used these computing resources in the past in programming assignment 1, although there can be challenges with them at times. Please use the support helpdesk if you run into any issues while working withthem.

Note​: Please protect your folders if you are working on these servers. By default your homedirectory is world readable on those servers, You can fix it with the command `chmod 600~` and then only you will be able to access your homedir. Link - ​https://support.cc.gatech.edu/facilities/general-access-servers

Questions?

Use piazza, or office hours. Given the size of the class, we will find it difficult to manage emails.