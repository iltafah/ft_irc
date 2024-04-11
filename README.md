
---

# ft_irc: Custom IRC Server Implementation

`ft_irc` is an Internet Relay Chat (IRC) server built from scratch in C++98, adhering strictly to the standards and protocols that govern real-time internet text messaging. This project allows for an understanding of network programming, multi-client server architecture, and the IRC protocol.

## Project Overview

This IRC server implementation supports multiple client connections, enabling users to join channels, send and receive messages, and perform channel operations. It's designed to be compatible with standard IRC clients and provides a foundation for extending functionality to more complex IRC commands and features.

### Features

- **Multi-client Management**: Handles multiple client connections simultaneously without blocking.
- **Channel Operations**: Supports creating and joining channels, messaging within channels, and managing channel topics and modes.
- **User Commands**: Implements a subset of IRC commands including NICK, USER, JOIN, PRIVMSG, PART, QUIT, and MODE.
- **Operator Privileges**: Special privileges for channel operators like KICK, INVITE, and managing channel modes.
- **Authentication**: Requires a password for client connections to ensure controlled access.

## Installation

### Prerequisites

- A Unix-like operating system (Linux/MacOS)
- C++98 compliant compiler (e.g., g++)
- Make (for building the server using the provided Makefile)

### Building the Server

Clone the project repository:

```bash
git clone https://github.com/eagoumi/ft_irc.git
cd ft_irc
```

Compile the server using the Makefile:

```bash
make
```

This will create the `ircserv` executable within the project directory.

## Usage

To start the IRC server, run:

```bash
./ircserv <port> <server_password>
```

- `<port>`: Specifies the port number on which the server listens for incoming connections.
- `<server_password>`: Sets the password required for clients to connect to the server.

### Connecting to the Server

Clients can connect to the server using any standard IRC client by specifying the server's IP address and the port number. The connection password must be provided upon connection.
In MacOS you can user LimeChat IRC Client, or you could just connet to the server using the following command `NetCat` with specifing where your server is running and its port :

```bash
nc localhost 8080
```

You are now connected as a client to the IRC server, you should authenticate first to start using the other commands, hint: execute the following commands in order within your terminal that you have run your client on

```bash
pass your_server_password
nick your_nickname
user any_username
```

https://github.com/eagoumi/ft_irc/assets/56886719/b49f7555-b07b-46bf-a6f6-10c037a35703



## Supported Commands

This server supports a variety of IRC commands essential for channel management and communication. Here is a list of some supported commands:

- `JOIN`: Join a channel.
- `PART`: Leave a channel.
- `KICK`: Kick a user from a specified channel.
- `INVITE`: Invite a user to your channel.
- `MODE`: Set or unset channel modes (-+iklot).
- `TOPIC`: Set or unset channel topic.
- `PRIVMSG`: Send private messages to a user or channel.
- `QUIT`: Disconnect from the server.

## IRC Bot

There is an embeded bot within the IRC server, each client can use it by running one of the following commands:

- `LOGTIME`: Shows how many hours a user has logged in his 42 campus within a specified period of time.

https://github.com/eagoumi/ft_irc/assets/56886719/a739aba2-2819-4141-90ef-5e38667fca19

- `LOCATION`: Shows the location of a certain user within his 42 campus.

- `WHOIS`: Shows the 42 profile of a certain user within the 42 network.

https://github.com/eagoumi/ft_irc/assets/56886719/10941bcf-7c1c-47e1-afc9-319359c7ff2d


## Acknowledgments

- Special thanks to the 42 School for providing the guidelines and specifications for this project.
- Appreciation to all contributors and peers who have offered feedback and suggestions.
