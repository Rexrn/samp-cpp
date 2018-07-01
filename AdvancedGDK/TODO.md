# TODO - Things to do in this project

## Fixing and current features completion

- [ ] Create relation between following classes:

	- `Player`
	- `Vehicle` **(important)**
	- `IMapObject` and derivatives

	Every single one of them should have common base class `I3DNode`.

- [ ] Find better way to implement scene loading algorithm
- [ ] Complete documentation of existing features
- [ ] Make sure that vehicles are being synced correctly -
	player enter/exit must be called properly
- [ ] Make sure that streamer works with personal objects
- [ ] Provide handy methods for creating full object scenes, as well as every
	personal, global and universal objects separately

- [ ] **Think about and implement proper server behaviour for NPCs**

## New features

- [ ] Make use of threads in `ActionScheduler` and `Streamer`
- [ ] Implement `Actor` class and its proper streaming. 
- [ ] Implement `Checkpoint` and `RaceCheckpoint` and their proper streaming.
- [ ] Implement textdraws and their proper streaming.
- [ ] Implement map marks and their proper streaming
- [ ] Implement gang zones and their proper streaming