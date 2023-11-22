workspace "minecraft-clone"
    architecture "x64"
    configurations { "Debug", "Release" }

OutputDir = "%{cfg.system}-%{cfg.architecture}/%{cfg.buildcfg}"

project "minecraft-clone"
   location "minecraft-clone"
   kind "WindowedApp"
   language "C++"
   cppdialect "C++20"
   staticruntime "off"
   targetdir ("bin/" .. OutputDir .. "/%{prj.name}")
   objdir ("bin-int/" .. OutputDir .. "/%{prj.name}")

   files 
   { 
        "minecraft-clone/src/**.h",
        "minecraft-clone/src/**.cpp",
        "minecraft-clone/vendor/glad/src/glad.c"
   }

   IncludeDir = {}
   IncludeDir["Glad"] = "minecraft-clone/vendor/glfw/include"
   IncludeDir["GLFW"] = "minecraft-clone/vendor/Glad/include"
   IncludeDir["glm"] = "minecraft-clone/vendor/glm"
   IncludeDir["stb_image"] = "minecraft-clone/vendor/stb_image/include"
   IncludeDir["FastNoise2"] = "minecraft-clone/vendor/FastNoise2/include"

   includedirs
   {
        "minecraft-clone/src",
        "%{IncludeDir.GLFW}",
        "%{IncludeDir.Glad}",
        "%{IncludeDir.glm}",
        "%{IncludeDir.stb_image}",
        "%{IncludeDir.FastNoise2}"
   }

   links
   {
        "GLFW",
        "Glad",
        "opengl32.lib",
        "minecraft-clone/vendor/FastNoise2/lib/FastNoise.lib"
   }

   include "minecraft-clone/vendor/glfw"
   include "minecraft-clone/vendor/Glad"

   filter "system:windows"
       systemversion "latest"
       defines { }

   filter "configurations:Debug"
       defines { "DEBUG" }
       runtime "Debug"
       symbols "On"

   filter "configurations:Release"
       defines { "RELEASE" }
       runtime "Release"
       optimize "On"
       symbols "On"

   filter "configurations:Dist"
       defines { "DIST" }
       runtime "Release"
       optimize "On"
       symbols "Off"