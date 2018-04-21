# Project plan

## 1. Module list

- [Game mode](#game-mode)
- [Server](#server)
  - [GameWorld](#game-world)
    - [Players](#players)
    - [Vehicles](#vehicles)
    - [MapObjects](#map-objects)
    - [Textdraws](#textdraws)
  - [Streamer](#streamer)

## 2. Module details

### Game mode

A simple module that provides basic `IGameMode` interface to the library user. It is filled with necessary things.

Enforcements and proposals:

- Using resources involves referencing `g_server`. For example:
    ```cpp
    
    ```
- Some other rule

Currently proposed view of the class:

```cpp
class IGameMode
{
    
};
```

### mod.srv (Server)

Main module of the library. It is responsible for everything that needs to be done implicitly on the server,
like basic handling every server event.

### mod.srv.gw (GameWorld)

Connects storage for every player, vehicle, map object and textdraw.

### mod.srv.gw.pla (Players)

Stores every player, processes their events and provides way to manage them from outside.

### mod.srv.gw.veh (Vehicles)

Stores every vehicle, processes their events and provides way to manage them from outside.

### mod.srv.gw.mo (MapObjects)

Stores every map object, processes their events and provides way to manage them from outside.

### mod.srv.gw.td (Textdraws)

Stores every textdraw, processes their events and provides way to manage them from outside.

### mod.srv.str (Streamer)

Streams `GameWorld` items to player depending on its location, status etc.
