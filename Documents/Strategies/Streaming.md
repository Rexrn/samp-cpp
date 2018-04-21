# The strategy for "Streaming"

## 1. World is split using a 3D grid of "Chunks"

A chunk is a small, cube shaped piece of space.
It stores every [`Actor`](../Concepts/Actors.md) that is currently inside of it.
It will increase performance, because streaming algorithm won't have to deal always
with every *Actor*, whose count can exceed 10<sup>5</sup>. 

## 2. Two types of streamables

Two types of streamables can be distinguished:

- **Globally streamable** - a thing that must be spawned for every player
  when at least one player sees it.
  Example: vehicle, global map object
- **Per player streamable** - a thing that is spawned separately per-player.
  Example: universal object, personal object.




