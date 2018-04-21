# The concept of "Streaming"

SAMP internal mechanisms allow for limited amount of:

- map objects (global and per-player)
- vehicles
- textdraws ("UI" module is responsible for textdraws)

Streamer is responsible for spawning and despawning objects and vehicles dynamically.

## 1. Motivation

A common need to overcome very low SAMP limits, easy way to spawn objects and vehicles
without worrying about whether it can be properly spawned or not.

## 2. Enforcements

Streamer algorithm is implemented inside World module and controls
every SAMP object or vehicle.  
See also:

- ["Objects" concept](Objects.md)
- ["Vehicles" concept](Vehicles.md)

Streamer is forced to spawn maximum possible nearest per-player objects to player at any time.
It also must ensure, that any vehicle or global object is spawned when any player
is close to it.
