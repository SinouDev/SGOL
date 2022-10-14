-- premake5.lua
workspace "SGOL"
   architecture "x64"
   configurations { "Debug", "Release", "Dist" }
   startproject "SGOL-Test"

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

include "SGOL"
include "SGOL-Test"