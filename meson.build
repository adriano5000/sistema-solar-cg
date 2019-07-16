project('sistema-solar', 'cpp', 'c')
glfw = dependency('glfw3')
glew = dependency('GLEW')
opengl = dependency('GL')
src =  ['main.cpp', 'mesh.cpp', 'obj_loader.cpp', 'window.cpp', 'texture.cpp', 'shader.cpp', 'planet.cpp']
executable('sistema-solar', src, dependencies: [glfw, glew, opengl])
