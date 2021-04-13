# FlappyBirdClone
 
This is my 10th Project

Brief description - 
   Made this to understand how collisions between squares and circles could work.
   Just a clone of the famous flappy bird game. I could give it textures to make it look more iconic but I ain't bothered so programmer graphics will do.

Preview

![ezgif com-gif-maker (4)](https://user-images.githubusercontent.com/67654528/114613014-b9246980-9c9a-11eb-9c28-57f685ad5d4f.gif)

Full video on Youtube -- https://youtu.be/2WctcCo-0UQ



This uses the SFML library. -- I think its the 64bit Visual Studio 15 one.

Setup - (This is for myself in the future)

Go into Project Properties- Select all Configurations In C++ -> Additional Include Dicts add "c:\SFMLVS\INCLUDE" In Linker -> Additional Library Dicts "c:\SFMLVS\lib" In Linker, Linker Input -> Additional Dependencies "sfml-window.lib;sfml-system.lib;sfml-graphics.lib;sfml-audio.lib;sfml-network.lib;"

Apply <- Go into Debug Configuration In Linker, Linker Input -> "sfml-window-d.lib;sfml-system-d.lib;sfml-graphics-d.lib;sfml-audio-d.lib;sfml-network-d.lib;"

After that get SFMLVS Bin .dlls and add into solution with CPP files. --> Run
