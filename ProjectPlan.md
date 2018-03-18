# Project plan

## Table of contents
1. Module list  
   1. Details about `GameMode`


## 1. Module list

Hey

- [GameMode](#module-desc-gamemode)
- [Server](#module-desc-server)
  - [GameWorld](#module-desc-server-gameworld)
    - [Players](#module-desc-server-gameworld-players)
    - [Vehicles](#module-desc-server-gameworld-vehicles)
    - [MapObjects](#module-desc-server-gameworld-mapobjects)
    - [Textdraws](#module-desc-server-gameworld-textdraws)
  - [Streamer](#module-desc-server-streamer)

### 1.1 Details about every module

- <span id="module-desc-gamemode">**GameMode**</span>  
  A simple module that provides basic `IGameMode` interface to the library user. It is filled with necessary things.
- <span id="module-desc-server">**Server**</span>  
  Main module of the library. It is responsible for everything that needs to be done implicitly on the server,
  like basic handling every server event.
  - <span id="module-desc-server-gameworld">**GameWorld**</span>  
    Connects storage for every player, vehicle, map object and textdraw.
    - <span id="module-desc-server-gameworld-players">**Players**</span>   
      Stores every player, processes their events and provides way to manage them from outside.
    - <span id="module-desc-server-gameworld-vehicles">**Vehicles**</span>   
      Stores every vehicle, processes their events and provides way to manage them from outside.
    - <span id="module-desc-server-gameworld-mapobjects">**MapObjects**</span>   
      Stores every map object, processes their events and provides way to manage them from outside.
    - <span id="module-desc-server-gameworld-textdraws">**Textdraws**</span>   
      Stores every textdraw, processes their events and provides way to manage them from outside.
  - <span id="module-desc-server-streamer">**Streamer**</span>   
    Streams `GameWorld` items to player depending on its location, status etc.




### 1.2 Details about `Server`



#### 1.2.1 Details about `GameWorld`



##### 1.2.1.1 Details about `Players`



##### 1.2.1.2 Details about `Vehicles`



##### 1.2.1.3 Details about `MapObjects`



##### 1.2.1.4 Details about `Textdraws`



#### 1.2.2 Details about `Streamer`


