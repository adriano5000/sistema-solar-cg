project('sistema-solar', 'cpp', 'c')
glfw = dependency('glfw3')
glew = dependency('GLEW')
opengl = dependency('GL')

src =  ['main.cpp', 'mesh.cpp', 'obj_loader.cpp', 'window.cpp', 'texture.cpp', 'shader.cpp', 'planet.cpp']

configure_file(copy: true, input: 'ball.obj', output: 'ball3.obj')
configure_file(copy: true, input: 'earth.jpg', output: 'earth.jpg')
configure_file(copy: true, input: 'jupiter.jpg', output: 'jupiter.jpg')
configure_file(copy: true, input: 'moon.jpg', output: 'moon.jpg')
configure_file(copy: true, input: 'space.jpg', output: 'space.jpg')
configure_file(copy: true, input: 'sun.jpg', output: 'sun.jpg')
configure_file(copy: true, input: 'shader.fragment', output: 'shader.fragment')
configure_file(copy: true, input: 'shader.vertex', output: 'shader.vertex')
configure_file(copy: true, input: 'shader2.fragment', output: 'shader2.fragment')
configure_file(copy: true, input: 'shader2.vertex', output: 'shader2.vertex')

executable('sistema-solar', src, dependencies: [glfw, glew, opengl])
