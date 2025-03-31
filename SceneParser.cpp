//
// Created by Raed Alsheikh Amin on 3/07/2025.
//




#include "SceneParser.h"
#include <iostream>
#include <sstream>

//I will be using debug statements here to check if I am reading the file correctly, I am sorry if I forgot to delete them before submitting

bool SceneParser::parseScene(const std::string& filename, Scene& scene, Camera& camera, RayTracer& rayTracer) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Unable to open file " << filename << std::endl;
        return false;
    }

    std::string line;
    std::vector<Vector3> vertices;

    std::cout << "\n--- Parsing scene file: " << filename << " ---\n";

    while (std::getline(file, line)) {
        if (line.empty() || line[0] != '#') continue;

        if (line == "#BackgroundColor") {
            float r, g, b;
            file >> r >> g >> b;
            scene.backgroundColor = Vector3(r, g, b)/255.0f;
            std::cout << "[Parsed] BackgroundColor: " << r << ", " << g << ", " << b << std::endl;
        }
        else if (line == "#MaxRecursionDepth") {
            int d;
            file >> d;
            rayTracer.maxDepth = d;
            std::cout << "[Parsed] MaxRecursionDepth: " << d << std::endl;
        }
        else if (line == "#ShadowRayEpsilon") {
            float e;
            file >> e;
            rayTracer.shadowRayEpsilon = e;
            std::cout << "[Parsed] ShadowRayEpsilon: " << e << std::endl;
        }
        else if (line == "#Camera") {
            float px, py, pz, gx, gy, gz, ux, uy, uz, l, r, b, t, d;
            int w, h;
            file >> px >> py >> pz >> gx >> gy >> gz >> ux >> uy >> uz;
            file >> l >> r >> b >> t >> d >> w >> h;
            camera = Camera(Vector3(px, py, pz), Vector3(gx, gy, gz), Vector3(ux, uy, uz), l, r, b, t, d, w, h);
            std::cout << "[Parsed] Camera\n";
            std::cout << "  Position: (" << px << ", " << py << ", " << pz << ")\n";
            std::cout << "  Gaze:     (" << gx << ", " << gy << ", " << gz << ")\n";
            std::cout << "  Up:       (" << ux << ", " << uy << ", " << uz << ")\n";
            std::cout << "  Near Plane: left=" << l << " right=" << r << " bottom=" << b << " top=" << t << "\n";
            std::cout << "  Distance: " << d << "\n";
            std::cout << "  Resolution: " << w << " x " << h << "\n";
        }
        else if (line == "#Material") {
            int materialID;
            file >> materialID;
            if (materialID != scene.materials.size() + 1) {
                std::cerr << "Warning: Material ID not sequential\n"; // to check if they are sequential or not
            }


            float ar, ag, ab;
            float dr, dg, db;
            float sr, sg, sb;
            float phong;
            float mr, mg, mb;

            file >> ar >> ag >> ab;
            file >> dr >> dg >> db;
            file >> sr >> sg >> sb;
            file >> phong;
            file >> mr >> mg >> mb;

            scene.materials.emplace_back(Vector3(ar, ag, ab), Vector3(dr, dg, db),
                                         Vector3(sr, sg, sb), phong, Vector3(mr, mg, mb));

            std::cout << "[Parsed] Material " << materialID << ":\n";
            std::cout << "  Ambient:  (" << ar << ", " << ag << ", " << ab << ")\n";
            std::cout << "  Diffuse:  (" << dr << ", " << dg << ", " << db << ")\n";
            std::cout << "  Specular: (" << sr << ", " << sg << ", " << sb << ")  Phong Exp: " << phong << "\n";
            std::cout << "  Mirror:   (" << mr << ", " << mg << ", " << mb << ")\n";
        }

        else if (line == "#AmbientLight") {
            float r, g, b;
            file >> r >> g >> b;
            scene.lights.emplace_back(Vector3(0, 0, 0), Vector3(r, g, b)/255.0f);//there is a problem here, i am not finding the correct normalization
            std::cout << "[Parsed] AmbientLight: " << r << ", " << g << ", " << b << std::endl;
        }
        else if (line == "#PointLight") {
            int lightID;
            file >> lightID; // read the ID of the light
            float px, py, pz;
            float ir, ig, ib;

            file >> px >> py >> pz;    // read position (x, y, z)
            file >> ir >> ig >> ib;    // read intensity (r, g, b)

            // normalize the intensity values to [0,1] range by dividing by 255
            scene.addLight(Light(Vector3(px, py, pz), Vector3(ir, ig, ib) / 255.0f));

            std::cout << "[Parsed] PointLight ID: " << lightID
                      << " at (" << px << ", " << py << ", " << pz << ")"
                      << " with Intensity: (" << ir << ", " << ig << ", " << ib << ")\n";
        }



        else if (line == "#VertexList") {
            std::cout << "[Parsed] Vertex list:\n";
            while (std::getline(file, line)) {
                if (line.empty() || line[0] == '#') break;
                std::istringstream iss(line);
                float x, y, z;
                iss >> x >> y >> z;
                vertices.emplace_back(x, y, z);
                std::cout << "  Vertex: " << x << ", " << y << ", " << z << "\n";
            }
            std::cout << "  Total vertices: " << vertices.size() << "\n";
        }
        else if (line == "#Sphere") {
            int sphereCount;
            file >> sphereCount;
            std::cout << "[Parsed] " << sphereCount << " spheres...\n";
            for (int i = 0; i < sphereCount; i++) {
                int materialID, centerID;
                float radius;
                file >> materialID >> centerID >> radius;

                if (materialID < 1 || materialID > scene.materials.size()) {
                    std::cerr << "Invalid material ID " << materialID << " for Sphere " << (i+1) << "\n";
                    continue;
                }
                if (centerID < 1 || centerID > vertices.size()) {
                    std::cerr << "Invalid vertex index " << centerID << " for Sphere " << (i+1) << "\n";
                    continue;
                }

                scene.addObject(new Sphere(vertices[centerID - 1], radius, scene.materials[materialID - 1]));
                std::cout << "[Parsed] Sphere with Material ID: " << materialID
                          << ", Center Index: " << centerID
                          << ", Radius: " << radius << "\n";
            }
        }



        else if (line == "#Triangle") {
            int triangleID;
            int materialID;
            int v1, v2, v3;

            file >> triangleID;
            file >> materialID;
            file >> v1 >> v2 >> v3;

            // Validate indices
            if (materialID < 1 || materialID > scene.materials.size()) {
                std::cerr << "Invalid material ID " << materialID << " for Triangle " << triangleID << "\n";
                continue;
            }
            if (v1 < 1 || v2 < 1 || v3 < 1 ||
                v1 > vertices.size() || v2 > vertices.size() || v3 > vertices.size()) {
                std::cerr << "Invalid vertex index for Triangle " << triangleID << "\n";
                continue;
            }

            scene.addObject(new Triangle(
                    vertices[v1 - 1], vertices[v2 - 1], vertices[v3 - 1],
                    scene.materials[materialID - 1]));

            std::cout << "[Parsed] Triangle ID: " << triangleID << ", Material ID: " << materialID
                      << ", Vertices: " << v1 << ", " << v2 << ", " << v3 << "\n";
        }

        else if (line == "#Mesh") {
            int materialID;
            file >> materialID;
            std::vector<Triangle*> meshTriangles;

            std::cout << "[Parsed] Mesh with Material ID: " << materialID << "\n";
            while (std::getline(file, line)) {
                if (line.empty()) continue;
                if (line[0] == '#') break;
                std::istringstream iss(line);
                int v1, v2, v3;
                if (!(iss >> v1 >> v2 >> v3)) continue;
                meshTriangles.push_back(new Triangle(
                        vertices[v1 - 1], vertices[v2 - 1], vertices[v3 - 1], scene.materials[materialID - 1]));
                std::cout << "  Mesh Triangle: " << v1 << ", " << v2 << ", " << v3 << "\n";
            }

            Mesh* mesh = new Mesh(meshTriangles, scene.materials[materialID - 1]);
            scene.addObject(mesh);
            std::cout << "  Total Mesh Triangles: " << meshTriangles.size() << "\n";
        }
    }

    file.close();
    std::cout << "--- Scene parsing completed successfully ---\n\n";
    return true;
}
