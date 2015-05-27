## My first C++ game
A space shooter game. You control a triangle spaceship that can shoot from its three vertices. 
Your enemies are pentagonals, which rotate around their center and shoot at you, according to your position.

The game ends when you die.

### How to run the project?
I have used SFML for the graphics and FMOD for creating the music interface. Because of this you will have to download them and fix the references in the `.vcxproj` file.

* [FMOD](http://www.fmod.org/download/#StudioAPI) - Download the library and configure the project so it references the `lowlevel`'s `lib` and `inc` directories.
* [SFML](http://www.nightlybuilds.ch/project/show/1/SFML/) - The downloaded version must match your operating system architecture and your compiler version. Otherwise it probably won't work. 
Be careful when referencing it. There are two different `dll` files for each part of the library. You must use the ones with suffix `-d` in `Debug` mode and the others in `Release`.
