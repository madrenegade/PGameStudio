cmake_minimum_required(VERSION 2.8)

SUBDIRS(Math)
SUBDIRS(StackTrace)
SUBDIRS(MemoryProfiler)
SUBDIRS(Utilities)

SUBDIRS(Core)

SUBDIRS(Platform.Linux)
SUBDIRS(Platform.Editor)

SUBDIRS(Renderer.OpenGL)
SUBDIRS(Input)

#SUBDIRS(Geometry)
SUBDIRS(Graphics)
#SUBDIRS(GUI)

SUBDIRS(Scripting)
#SUBDIRS(Scripting.Lua)
#SUBDIRS(Scripting.Angelscript)

#SUBDIRS(Sound)
#SUBDIRS(Sound.OpenAL)

#SUBDIRS(Physics)
#SUBDIRS(Physics.Bullet)

#SUBDIRS(Terrain)

#SUBDIRS(AI)

#SUBDIRS(Atmosphere)

#SUBDIRS(Particles)

SUBDIRS(Game)
SUBDIRS(Demo)
