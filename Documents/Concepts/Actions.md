# The concept of "Actions"

Table of contents:

- [1. Motivation](#motivation)
- [2. Enforcements](#enforcements)
  - [1. ActionRegistry requirements](#actionregistry-requirements)
    - [1. Direct owner of stored actions](#direct-owner-of-stored-actions)
    - [2. Scheduled actions are automatically launched in specified time](#scheduled-actions-are-automatically-launched-in-specified-time)
  - [2. Action requirements](#action-requirements)
    - [1. Scheduled calls cancelled on destruction](#scheduled-calls-cancelled-on-destruction)
- [3. Usage](#usage)

"Actions" is a pretty name to functions that can be easily scheduled for future call
or run immediately during action processing.

## 1. Motivation

Creating interesting gameplay often involves using postponed actions.
An example would be:

- equipping player with weapons on spawn
- teleporting him to location after specified # of seconds
- unfreezing player after teleportation

## 2. Enforcements

"Actions" must provide public modules listed below:

- **Action** - overlay to function, that can be scheduled with specified time interval.
- **ActionScheduler** - container and partial owner of actions. Does action processing that involves
  checking their status and calling them.

In addition, implementation strategy of "Actions" must fulfill following requirements:

### 2.1 "ActionScheduler" requirements

List of requirements "ActionScheduler" module must meet:

#### 2.1.1 Shared owner of stored actions

Scheduler has shared ownership over contained actions. It can uphold their lifetime.
Programmer can share ownership storing shared pointer to the action.

#### 2.1.2 Scheduled actions are automatically launched in specified time

Programmer does not need to do anything more than registering action that will be called.
Action processing is done automatically.

### 2.2 "Action" requirements

List of requirements "Action" module must meet:

#### 2.2.1 Scheduled calls cancelled on destruction

Every scheduled call of an action must be automatically interrupted and properly removed
when action object gets destroyed.

## 3. Usage

To be announced.

