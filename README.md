# Single-Server-Client-Chat
A server and client program based on TCP protocol which helps in two way chat.

<b>Compiling the code:</b>
gcc filename.c -pthread

<b>Running the server:</b>
./a.out portnumber

<b>Running the client:</b>
./a.out portnumber

Remember, first run the server with a port number of your choice. The server runs on the localhost(127.0.0.1). You can change it by changing the server socket address.
Then run the client program by using the same port number given to the server.

Stopping the chat:
Both client and server need to say bye to each other to stop the chat and this ends both the programs.
