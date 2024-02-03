# Functionalities of a Server

- Has different lobbies for running concurrently
- Stores a secret state for each lobby seperately
- Sends information to all / some of the clients in the lobby
- Receives information from clients, updates the secret state accordingly

# The Ideas of an Implementation
- We first form a lobby. This is done by establishing connection with some number of clients. We give clients their identifiers during this phase.
- What we usually want with these identifiers is that each player should have a unique ID, username or both. We also may want to classify each player with a `class` to group certain players together, for example form a team.
- After the connection is established, the client and the server can communicate. In order to do this, the server must know what type of information the client might send and vice versa.
- We enumerate the type of requests as constants. See below:
```
const int REQUEST_1 = 1000;
const int REQUEST_2 = 1001; // and more of these

void send_request_1(int x){
    client.send(REQUEST_1); // first sends the type of message
    client.send(x); // then sends the content of the message
}

send_request_1(5);
```
- In the above psuedo-code, the client sends a request to the server. Server is looking for the agreed upon integer `REQUEST_1`. Upon receiving this integer, the server immediately knows how to read the data and how to interpret the data being sent. The same goes for the client.
- Every communication the server receives will have a response. This response may or may not alter the secret state and may or may not send a communication back to some / all of the clients.
- The following is tentative. In a proper framework, I would like to have this (REVIEW THIS): 
```
// This is psuedo-code
const int REQUEST_1 = 1000;

class GameState : SecretState{
public:
    std::vector<std::vector<<int>> board;
    bool turn;
    pair<int, int> scores;
    // and more...
};

class REQ_1{
public:
    int x;
};

// just a random function
void respond_to_req_1(GameState& gs, REQ_1& request){
    // alter game state
    if(gs.turn)
        gs.scores.first += request.x;
    else
        gs.scores.second += request.x;

    // may also send response to clients
}

// adds the response to requests of type REQUEST_1 to a particular lobby type called LOBBY_TYPE_1

server.add_lobby_type(LOBBY_TYPE_1, GameState);
server.add_request_type(LOBBY_TYPE_1, REQUEST_1, REQ_1);
server.add_response(LOBBY_TYPE_1, REQUEST_1, respond_to_req_1);
```
- I would like to handle the response to a request in this way. The user will define a function taking in the secret state and the request. This function will construct the response to the request. We will pass the pointer of this function to the server class which is hidden from the user. The server class will look for the integer `REQUEST_1` and read the response into an object of type `REQ_1` (this works on java, I think). We will then pass this (and the secret state) into the function `respond_to_req_1()`

# Random Bits and Pieces
- Three common modes of sending information from client to server must be implemented. 
    - Send information to all of the clients in the lobby.
    - Send information to all the clients belonging to a particular class in the lobby.
    - Send information to all of the clients except one or more specific clients in the lobby.
-  In addition to these, we may want to have these functions send information to all players in a server regardless of lobby.
- There also should be a non-lobby connection state, think of the main page on lichess. You can see all of the lobbies (individual games) but you are not in any lobby yourself. From this state, you can send a request to create a lobby for example.
- Lobbies must have unique identifiers. However, they also can have `types`, imagine a chess lobby or a go lobby in the same server.

