project "SGOL"
   kind "StaticLib"
   language "C++"
   cppdialect "C++17"
   targetdir "bin/%{cfg.buildcfg}"
   staticruntime "off"

   files { "src/**.h", "src/**.cpp", "include/**.hpp" }

   targetdir ("../bin/" .. outputdir .. "/%{prj.name}")
   objdir ("../bin-int/" .. outputdir .. "/%{prj.name}")

   includedirs
   {
      "include/"
   }

   filter "system:windows"
      systemversion "latest"
      defines { "_CRT_SECURE_NO_WARNINGS" }

   filter "configurations:Debug"
      defines { "_CRT_SECURE_NO_WARNINGS"  }
      runtime "Debug"
      symbols "On"

   filter "configurations:Release"
      defines { "_CRT_SECURE_NO_WARNINGS"  }
      runtime "Release"
      optimize "On"
      symbols "On"

   filter "configurations:Dist"
      kind "WindowedApp"
      defines { "_CRT_SECURE_NO_WARNINGS"  }
      runtime "Release"
      optimize "On"
      symbols "Off"