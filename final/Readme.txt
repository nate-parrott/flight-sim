Nate Parrott
CS123

[NAME] Flight Simulator
===========================

For my final project, I implemented a flight simulator flying through an infinite, procedurally-generated world.

Terrain is generated procedurally using several layers of Perlin noise. It's colored using a shader that combines several image textures (sand, grass, snow, etc) depending on altitude.

Terrain is rendered at variable levels of detail, depending on its distance from the viewer.

The plane model is loaded from a .obj file, and rendered using a VBO.

The "flight" is *very* roughly physically based; completely arbitrary "altitude" and "speed" indicators are provided.

Water is generated using a 3D Perlin noise function written in GLSL (not mine), combined with specular reflection.

Rudimentary shadowing is supported by rendering the top-down silhouette and mapping this as a texture onto the terrain. Currently, only the plane casts a shadow, and does not cast a shadow on water.

There's a dome-shaped skybox.

Clouds are randomly generated and rendered using billboarded particles with alpha transparency.

Running
=============

Qt's resource system doesn't allow you to include entire resource folders, and trips up when loading things from relative paths (like .obj files and their associated .mtl and texture files). Instead, I just used a resource folder, which must be placed manually.

There's a resource folder, "data," in the project. In final.h, there's a #define, PATH_TO_DATA_DIR, which must point to the data dir, wherever it is. If nothing shows up, the path is wrong.g

Acknowledgements
===================

The water shader uses Stefan Gustavson's 3D Perlin noise implementation in GLSL (and some C support code).
 * Author: Stefan Gustavson ITN-LiTH (stegu@itn.liu.se) 2004-12-05
 * You may use, modify and redistribute this code free of charge,
 * provided that my name and this notice appears intact.
 (Linked from http://stackoverflow.com/questions/4200224/random-noise-functions-for-glsl)
 
 Loading Wavefront .obj files is done with a (modified) copy of the Tiny Obj Loader project.
https://github.com/syoyo/tinyobjloader

C++ Perlin noise generation functions come from the GPLv3-licensed battlestar-tux project:
https://code.google.com/p/battlestar-tux/


