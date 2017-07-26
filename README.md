# It_Fights

Project that contains the full implementation of my End-Of-Degree project. It contains a simple but full **game engine** containing a plethora of subsystems connected by a message bus. It is used to make a **Top-Down Zelda-like game** in which you fight an **Agent** trained with a custom made **reinforcement learning** algorithm by iterating through simulations inside this engine but without rendering.

All the **assets** (animated sprites, music, etc) and the **algorithm** have been made by me with the knowledge and abilities I had at the time.

## Controlls

![Controller Image from Microsoft Website](http://nxeassets.xbox.com/shaxam/0201/bc/fd/bcfd38d2-f77c-40bd-a8e5-bd6bedcadfc6.PNG?v=1#xbox-controller-labeles-l-m.PNG)

### Menu
* **D-PAD** (number 2): Used to change the preselected option.
* **X** (letter X): Executes the preselected option.

### Gameplay
* **Left Joystick** (number 3): Moves the player in any direction. You can vary the speed by tilting it slightly.
* **A** (letter A): Executes an attack in the direction the player is looking.
* **B** (letter B): Executes a *parry*, rendering the player invulnerable for a while. If the parry is not succesfull there will be a *cooldown* where he can't move nor attack.
* **Back Button** (number 4): Exits the fight and comes back to the menu.


## Unity Prototype

[![Unity prototype problems](http://img.youtube.com/vi/PY4H8dk8zcU/0.jpg)](https://www.youtube.com/watch?v=PY4H8dk8zcU)

As we can see in the video above, the first prototype of the project was made in Unity. It includes all the main mechanics that the final game has as far as movement and attacking. It also has a custom made CRT simulation camera that I made on another project.

Since the AI agent needed to train agains a virtual opponent the plan was to use Unity's *TimeScale* but as shown in the video, **this broke the mechanics** quite significantly. It has to be noted that without rendering it would not work either.


## C++ game & engine

[![Kavinsky - Nightcall](http://img.youtube.com/vi/NdtrxdUIRWw/0.jpg)](https://www.youtube.com/watch?v=NdtrxdUIRWw)

Here we see a video in which out trained agent fights with a rule based enemy. We can observe how we learned to chase him very effectively. It is even able to wait out the *parry* mechanic used in the last fight, attacking when the enemy is vulnerable again.

The game has a custom made menu as well as an in-game console that is not shown in the video. A better video explaining how all the different elements work will be made soon when I have the time.

## Notes

If you understand spanish you can read the full project documentation [HERE](https://github.com/Jazzzy/It_Fights/blob/master/doc/Final_Versions_ES/OsorioLopezRuben_MemoriaTrabajoFinDeGrado_060717_v1.0.pdf), but beware, is quite long :D



