#include "Shapes.hpp"

Mesh octahedron(){
    // TODO Make this actually not awful code, this is very much a placeholder hoping to get around to it at somepoint
    vector<Vertex> vertices;
    vector<unsigned int> indices;

    Vertex vertex;

    glm::vec3 vector(0.0,0.0,0.0); 
    
    for(int j = 0; j<3; j++){
        vector[j] = -1.0;
        vertex.Position = vector;
        vertex.Normal = vector;
        vertices.push_back(vertex);
        vector[j] = 0.0;
    }
    for(int j = 0; j<3; j++){
        vector[j] = 1.0;
        vertex.Position = vector;
        vertex.Normal = vector;
        vertices.push_back(vertex);
        vector[j] = 0.0;
    }

    indices.push_back(5);
    indices.push_back(1);
    indices.push_back(3);
    
    indices.push_back(5);
    indices.push_back(0);
    indices.push_back(1);
    
    indices.push_back(5);
    indices.push_back(4);
    indices.push_back(0);
    
    indices.push_back(5);
    indices.push_back(3);
    indices.push_back(4);
    
    indices.push_back(2);
    indices.push_back(3);
    indices.push_back(1);
    
    indices.push_back(2);
    indices.push_back(1);
    indices.push_back(0);
    
    indices.push_back(2);
    indices.push_back(0);
    indices.push_back(4);
    
    indices.push_back(2);
    indices.push_back(4);
    indices.push_back(3);
    Mesh mesh(vertices, indices);
    return mesh;
}


vector<Mesh> subdivideTriangles(Mesh mesh, uint32_t resolution){
    vector<Mesh> subdividedMeshes;

    for(int triangle = 0; triangle<(mesh.indices.size()/3); triangle++){
        vector<Vertex> vertices;
        vector<unsigned int> indicies;
        // Get Verticies of seed triangle in counter clockwise order
        Vertex vertex1 = mesh.vertices[mesh.indices[triangle*3]];
        Vertex vertex2 = mesh.vertices[mesh.indices[triangle*3+1]];
        Vertex vertex3 = mesh.vertices[mesh.indices[triangle*3+2]];
        
        //* Build Verticies
        // Get basis directions
        glm::vec3 rowDir = (vertex2.Position - vertex1.Position)/(float)resolution;
        glm::vec3 columnDir = (vertex3.Position - vertex2.Position)/(float)resolution;
        // Add first point
        vertices.push_back(vertex1);

        for(float row=1.0f; row<=(float)resolution; row+=1.0f){
            for(float j=0.0; j<=row; j+=1.0f){
                Vertex vertex;
                vertex.Position = vertex1.Position + rowDir*row + columnDir*j;
                // Just for debugging, will be replaced with normal maps
                // Only actually normal after points are mapped to sphere
                vertex.Normal = glm::normalize(vertex.Position);
                vertices.push_back(vertex);
            }
        }


        //* Build indicies
        // Loop through each row 
        for(int row=1; row<=resolution; row++){
            // First index of the row (index of top left)
            uint32_t rowStart = (uint32_t)round(1 - 0.5*row + 0.5*row*row);

            // Start with /\ triangles
            for (int j=0; j<row; j++){
                // Top of the Triangle
                indicies.push_back(rowStart+j-1);
                // Bottom Left
                indicies.push_back(rowStart+row+j-1);
                // Bottom Right
                indicies.push_back(rowStart+row+j);
            }
            // \/ triangles
            for (int j=0; j<row-1; j++){
                // Top Left
                indicies.push_back(rowStart+j-1);
                // Bottom 
                indicies.push_back(rowStart+row+j);
                // Top Right
                indicies.push_back(rowStart+j);
            }
        }
        subdividedMeshes.push_back(Mesh(vertices, indicies));
    }
    return subdividedMeshes;
}

