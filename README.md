# Advanced GDK
A C++17 library based on SAMPGDK for creating SAMP (San Andreas Multiplayer) game modes.
## 1. Status: 75%
## 2. Goals:
The main goal of **Advanced GDK** is to make game mode creation process a real pleasure. User code simplicity and performance stays always at the top.
### 1. Code look predictions.
Since the library is not finished yet, this section is not 100 percent sure to stay as it is. However I can make certain predictions and show sample code, that I think will do some fun stuff. Lets take a look at it:
#### 1. Running the server.
One thing I want to make significantly easier is the base server setup.
```cpp
#include <AdvancedGDK.hpp>	// all-in-one header.

// Server main function.
int main()
{
    g_server->setup(std::make_unique<agdk::DefaultGameMode>());
}
```
That runs the default server gamemode implemented inside Advanced GDK.
#### 2. Setting server description.
To set server description shown in SAMP Client, we will use `Server::setDescription` method:
```cpp
g_server->setDescription(">>> My perfect gamemode <<<");
```

#### 3. Adding _basic_ command
Command parameters are passed using `CommandInput` class. Since commands are dependent on gamemode setup, from now we will use `g_gameMode` global pointer. Lets see how to add simple `/heal` command:
```cpp
// Forwad declare the command function"
void healPlayerCommand(agdk::CommandInput input);

int main()
{
	// ... server setup ...
	// Add command to game mode:
	g_gameMode->commands += agdk::Command({"heal", "100hp", "life"}, healPlayerCommand);
}

// Define the command:
void healPlayerCommand(agdk::CommandInput input)
{
	// Caller is stored inside `input.target` pointer:
	input.target->setHealth(100);
}
```
Command adding is the interesting part:
```cpp
g_gameMode->commands += agdk::Command({"heal", "100hp", "life"}, healPlayerCommand);
```
The first argument of `Command` constructor is a vector that contains possible words that player needs to type to invoke the command.
This code heals player whenever he send one of following commands:
* `/heal`
* `/100hp`
* `/life`
Thats simple, isn't it?
