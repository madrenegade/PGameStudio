cmake_minimum_required(VERSION 2.8)

SUBDIRS(
	AITests
	AtmosphereTests
	CoreTests
	GameTests
	GeometryTests
	GraphicsTests
	GUITests
	InputTests
	MathTests
	ParticlesTests
	Physics.BulletTests
	PhysicsTests
	Platform.LinuxTests
	Renderer.OpenGL3Tests
	RenderContextLinuxOpenGL3Tests
	Scripting.AngelscriptTests
	Scripting.LuaTests
	ScriptingTests
	Sound.OpenALTests
	SoundTests
	TerrainTests
	UtilitiesTests
)

SUBDIRS(TestRunner)
