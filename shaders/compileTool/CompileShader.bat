@echo off
REM use your path
set GLSLC="%VULKAN_SDK%\Bin\glslc.exe"

if not exist %GLSLC% (
    echo ##########No glslc.exe found, pls check system path and ensure vulkan has been installed.##########
    exit /b 1
)

set OutputPath="%CD%/shaders/outputs"
if not exist %OutputPath% (
    mkdir %OutputPath%
)

call GLSLC %CD%/shaders/main.vert -o  %OutputPath%/vert.spv

if not %errorlevel% equ 0 (
    echo ##########Recompile Shaders Failed###########
    exit /b 1
)

call GLSLC %CD%/shaders/main.frag -o  %OutputPath%/frag.spv

if %errorlevel% equ 0 (
    echo ##########Recompile Shaders Success###########
    exit /b 0    
)
else (
    echo ##########Recompile Shaders Failed###########
    exit /b 1
)