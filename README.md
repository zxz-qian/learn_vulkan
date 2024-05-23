### Learn Vulkan 
#### Requirement:
- **Vulkan 1.3.268.0:** Base environment, may using other version.
- **GLFW 3.3.9:** Placed in [thirdparty](./thirdparty/) folder.
- **CMake 3.15:** Minimum requirement in *CMakeLists.txt*, may using other version.
- **GLM:** provided by vulkan sdk, placed in vulkan sdk folder.
- **stb_image:** v2.29
- **VSCode&CMake VSC plugin**

#### Something else:
- This is a learning project for vulkan api, followed by [Khronos Vulkan® Tutorial](https://docs.vulkan.org/tutorial/latest/00_Introduction.html).
- There is a bat script called [CompileShader.bat](./shaders/compileTool/CompileShader.bat) which can help compile shader scripts easily. **Call this bat from root folder**. It's basically calling glslc.exe to compile shader scripts.