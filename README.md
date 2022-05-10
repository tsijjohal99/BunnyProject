# Bunny Simulator

## Introduction:

This project we were asked to that creates and managers a group of bunnies to a specific specification.
I completed the base specification along as \*, ** and ***.

## Usage

The program runs automatically from start. Press 'K' to half the population and press '0' to exit.

## Bunny Simulation

The 'logicHandler.cpp' is designed to handle to the menu and main loop.
'bunnyManager.cpp' is designed to handle, store and manage the 'bunny.cpp' each iteration of the loop.
Each bunny object has a pointer that is stored in a list and consequently stored in a 2D vector.
A list was required but I chose a 2D vector to implement the grid as it is more versatile than an array.

Each iteration, each bunny has its age incremented by one and checks to see if the bunny is still alive.
After that, random movement takes place any of the 8 directions, with movement 1.
Then it checks to see whether a new bunny can be born or if another bunny can be infected.
If available, it then produced those outcomes.
If the population exceeds 1000, then the population is reduced by half.
Then the information is printed to the console.

After an internal debate of deciding which half of the random population would be terminated, the best way I decided to implement a true pseudo-random solution would be to shuffle the elements of the list and cut of the second half of the list. Other methods I came up with were either not true random or was not efficient enough.