#include "SceneParser.h"
#include <iostream>
#include <sstream>

bool SceneParser::parseScene(const std::string& filename, Scene& scene, Camera& camera, RayTracer& rayTracer, std::vector<Material>& materials) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Unable to open file " << filename << std::endl;
        return false;
    }

    std::string line;
    std::vector<Vector3> vertices;

    while (std::getline(file, line)) {
        std::istringstream iss(line);

        if (line == "#BackgroundColor") {
            float r, g, b;
            file >> r >> g >> b;
            scene.backgroundColor = Vector3(r, g, b);
        }
        else if (line == "#MaxRecursionDepth") {
            int maxDepth;
            file >> maxDepth;
            rayTracer.maxDepth = maxDepth;
        }
        else if (line == "#ShadowRayEpsilon") {
            float epsilon;
            file >> epsilon;
            rayTracer.shadowRayEpsilon = epsilon;
        }
        else if (line == "#Camera") {
            float px, py, pz, gx, gy, gz, ux, uy, uz, l, r, b, t, d;
            int w, h;
            file >> px >> py >> pz >> gx >> gy >> gz >> ux >> uy >> uz;
            file >> l >> r >> b >> t >> d >> w >> h;
            camera = Camera(Vector3(px, py, pz), Vector3(gx, gy, gz), Vector3(ux, uy, uz), l, r, b, t, d, w, h);
        }
        else if (line == "#Material") {
            int materialCount;
            file >> materialCount;
            for (int i = 0; i < materialCount; i++) {
                float ar, ag, ab, dr, dg, db, sr, sg, sb, phong, mr, mg, mb;
                file >> ar >> ag >> ab >> dr >> dg >> db >> sr >> sg >> sb >> phong >> mr >> mg >> mb;
                materials.push_back(Material(Vector3(ar, ag, ab), Vector3(dr, dg, db), Vector3(sr, sg, sb), phong, Vector3(mr, mg, mb)));
            }
        }
        else if (line == "#Mesh") {
            int meshCount;
            file >> meshCount;
            for (int i = 0; i < meshCount; i++) {
                int materialID;
                file >> materialID;
                std::vector<Triangle *> meshTriangles;

                while (std::getline(file, line) && !line.empty() && line[0] != '#') {
                    std::istringstream meshStream(line);
                    int v1, v2, v3;
                    meshStream >> v1 >> v2 >> v3;
                    meshTriangles.push_back(new Triangle(vertices[v1 - 1], vertices[v2 - 1], vertices[v3 - 1],
                                                         materials[materialID - 1]));
                }

                Mesh *mesh = new Mesh(meshTriangles, materials[materialID - 1]);
                scene.addObject(mesh);
            }


    }
    }

    file.close();
    return true;
}
