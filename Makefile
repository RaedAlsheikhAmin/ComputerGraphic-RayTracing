# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++11 -O3 -Wall

# Output binary
TARGET = Raytracer

# Object files
OBJS = main.o Camera.o Light.o Material.o Mesh.o Object.o \
       PPMWriter.o Ray.o RayTracer.o Scene.o SceneParser.o Sphere.o Triangle.o

# Final executable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(TARGET)

# Compilation rules for each source file
main.o: main.cpp
	$(CXX) $(CXXFLAGS) -c main.cpp

Camera.o: Camera.cpp Camera.h
	$(CXX) $(CXXFLAGS) -c Camera.cpp

Light.o: Light.cpp Light.h
	$(CXX) $(CXXFLAGS) -c Light.cpp

Material.o: Material.cpp Material.h
	$(CXX) $(CXXFLAGS) -c Material.cpp

Mesh.o: Mesh.cpp Mesh.h
	$(CXX) $(CXXFLAGS) -c Mesh.cpp

Object.o: Object.cpp Object.h
	$(CXX) $(CXXFLAGS) -c Object.cpp

PPMWriter.o: PPMWriter.cpp PPMWriter.h
	$(CXX) $(CXXFLAGS) -c PPMWriter.cpp

Ray.o: Ray.cpp Ray.h
	$(CXX) $(CXXFLAGS) -c Ray.cpp

RayTracer.o: RayTracer.cpp RayTracer.h
	$(CXX) $(CXXFLAGS) -c RayTracer.cpp

Scene.o: Scene.cpp Scene.h
	$(CXX) $(CXXFLAGS) -c Scene.cpp

SceneParser.o: SceneParser.cpp SceneParser.h
	$(CXX) $(CXXFLAGS) -c SceneParser.cpp

Sphere.o: Sphere.cpp Sphere.h
	$(CXX) $(CXXFLAGS) -c Sphere.cpp

Triangle.o: Triangle.cpp Triangle.h
	$(CXX) $(CXXFLAGS) -c Triangle.cpp

# Clean rule
clean:
	rm -f *.o $(TARGET)
