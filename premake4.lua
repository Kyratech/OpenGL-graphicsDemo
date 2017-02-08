solution ('OpenGL_Intro')
   configurations { 'Release' }
      language 'C++'
      project("Introduction")
        kind 'WindowedApp'
        targetdir('./')
        links{'glew32', 'glfw3', 'opengl32'}
        files {"*.cpp"}
        buildoptions{'-Wno-write-strings'}