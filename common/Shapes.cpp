#include "Shapes.hpp"

Mesh octahedron()
{
    // TODO Make this actually not awful code, this is very much a placeholder hoping to get around to it at somepoint
    vector<Vertex> vertices;
    vector<unsigned int> indices;

    Vertex vertex;

    glm::vec3 vector(0.0, 0.0, 0.0);

    for (int j = 0; j < 3; j++)
    {
        vector[j] = -1.0;
        vertex.Position = vector;
        vertex.Normal = vector;
        vertices.push_back(vertex);
        vector[j] = 0.0;
    }
    for (int j = 0; j < 3; j++)
    {
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

Mesh pretty_octahedron()
{
    // TODO Make this actually not awful code, this is very much a placeholder hoping to get around to it at somepoint
    vector<Vertex> vertices;
    vector<unsigned int> indices;

    Vertex vertex;

    glm::vec3 vector(0.0, 0.0, 0.0);

    for (int j = 0; j < 3; j++)
    {
        vector[j] = -1.0;
        vertex.Position = vector;
        vertex.Normal = vector;
        vertices.push_back(vertex);
        vector[j] = 0.0;
    }
    for (int j = 0; j < 3; j++)
    {
        vector[j] = 1.0;
        vertex.Position = vector;
        vertex.Normal = vector;
        vertices.push_back(vertex);
        vector[j] = 0.0;
    }

    for (int n = 0; n < 7; n++)
    {
        // Fit some polynomials to the values that each coordinate cycles through for each vertex
        // xCoord goes 5,5,5,5,2,2,2,2
        // yCoord goes 1,0,4,3,3,1,0,4
        // zCoord goes 3,1,0,4,1,0,4,3
        int xCoord = 5 + (2341 * n) / 140 - (931 * pow(n, 2)) / 24 + (791 * pow(n, 3)) / 24 - (161 * pow(n, 4)) / 12 + (337 * pow(n, 5)) / 120 - (7 * pow(n, 6)) / 24 + pow(n, 7) / 84;
        int yCoord = 1 - (435 * n) / 14 + (2213 * pow(n, 2)) / 36 - (1075 * pow(n, 3)) / 24 + (146 * pow(n, 4)) / 9 - (25 * pow(n, 5)) / 8 + (11 * pow(n, 6)) / 36 - pow(n, 7) / 84;
        int zCoord = 3 + (329 * n) / 10 - (14041 * pow(n, 2)) / 180 + (2501 * pow(n, 3)) / 40 - (212 * pow(n, 4)) / 9 + (547 * pow(n, 5)) / 120 - (79 * pow(n, 6)) / 180 + pow(n, 7) / 60;

        indices.push_back(xCoord);
        indices.push_back(yCoord);
        indices.push_back(zCoord);
    }
}

Mesh icosahedron()
{
    // todo make this the real icosahedron function as opposed to a dummy function

    vector<Vertex> vertices;
    vector<unsigned int> indices;

    Vertex vertex;

    glm::vec3 vector(0.0, 0.0, 0.0);
    Mesh mesh(vertices, indices);
    return mesh;
}

Mesh pretty_icosahedron()
{
    // TODO this will be the testing function for more elegant icosahedron code

    vector<Vertex> vertices;
    vector<unsigned int> indices;

    Vertex vertex;

    glm::vec3 vector(0.0, 0.0, 0.0);

    // golden ratio
    float phi = (1 + pow(5, 0.5)) / 2;

    // the vertices are just a shuffling of -1,1,-phi, and phi where the +-phi always comes before the +-1 ( add 2 and mod3 to index)
    int phiCoord = 0;
    for (int i = 0; j < 3; j++)
    {
        phiCoord = (i + 2) % 3;
        for (int j = -1; j < 2; j += 2)
        {
            // Making j<2 instead of j<=phi will stop foat errors from messing with it I think
            for (float k = -phi; j < 2; j += 2 * phi)
            {
                vector[i] = j;
                vector[phiCoord] = k;
                vertex.Position = vector;
                vertex.Normal = vector;
                vertices.push_back(vertex);
                vector[j] = 0.0;
                vector[phiCoord] = 0.0;
            }
        }
    }

    for (int n = 0; n < 19; n++)
    {

        // Set it up as the order of top 5 faces, bottom 5, and middle 10
        // Fit some polynomials to the values that each coordinate cycles through for each vertex
        // xCoord goes 11,11,11,11,11,  8,8,8,8,8,  1,1,1,6,6,9,9,7,7,3
        // yCoord goes 1,6,9,7,3,  5,10,4,0,2,  10,4,6,0,9,2,7,5,3,10
        // zCoord goes 3,1,6,9,7,  10,4,0,2,5,  3,10,4,4,0,0,2,2,5,5
        // todo check if this will work with such huge coeff or if it will not work
        // todo chnage all ^ to pow
        int xCoord = 11 + (636145253291 * n) / 16628040 - (78938537703859 * pow(x, 2)) / 593762400 + (30933962001881143 * pow(x, 3)) / 154378224000 - (4440468867823147 * pow(x, 4)) / 25147584000 + (1374150132247921 * pow(x, 5)) / 13343616000 - (250274450610701843 * pow(x, 6)) / 5884534656000 + (76303262679539969 * pow(x, 7)) / 5884534656000 - (329008179121427 * pow(x, 8)) / 109734912000 + (1291809100301603 * pow(x, 9)) / 2414168064000 - (1022030472749 * pow(x, 10)) / 13716864000 + (1403116522211 * pow(x, 11)) / 172440576000 - (1261909404557 * pow(x, 12)) / 1810626048000 + (2192509003819 * pow(x, 13)) / 47076277248000 - (724175777 * pow(x, 14)) / 301771008000 + (366416387 * pow(x, 15)) / 3923023104000 - (3203209 * pow(x, 16)) / 1207084032000 + (3955513 * pow(x, 17)) / 76218734592000 - (11353 * pow(x, 18)) / 18188561664000 + (10579 * pow(x, 19)) / 3041127510220800;
        int yCoord = 1 - (9660626251307 * n) / 116396280 + (629002586131 * pow(x, 2)) / 2199120 - (4121518679857603 * pow(x, 3)) / 9648639000 + (739056863873557 * pow(x, 4)) / 1981324800 - (2712238512333949 * pow(x, 5)) / 12573792000 + (173418304943811259 * pow(x, 6)) / 1961511552000 - (5729992275660019 * pow(x, 7)) / 213983078400 + (495515178551413 * pow(x, 8)) / 80472268800 - (330151293553507 * pow(x, 9)) / 301771008000 + (2776426699903 * pow(x, 10)) / 18289152000 - (79836295257839 * pow(x, 11)) / 4828336128000 + (170645375777 * pow(x, 12)) / 120708403200 - (4442308807723 * pow(x, 13)) / 47076277248000 + (22219573 * pow(x, 14)) / 4572288000 - (5935915177 * pow(x, 15)) / 31384184832000 + (5623801 * pow(x, 16)) / 1046139494400 - (196267 * pow(x, 17)) / 1865493504000 + (168953 * pow(x, 18)) / 133382785536000 - (429899 * pow(x, 19)) / 60822550204416000;
        int zCoord = 3 + (1018960391389 * n) / 15519504 - (6985019619679817 * pow(x, 2)) / 30875644800 + (78844765318729 * pow(x, 3)) / 233376000 - (4239826677807953 * pow(x, 4)) / 14370048000 + (223183097586838867 * pow(x, 5)) / 1307674368000 - (102962341257758791 * pow(x, 6)) / 1471133664000 + (38407681414167817 * pow(x, 7)) / 1810626048000 - (2142714693360211 * pow(x, 8)) / 438939648000 + (598726983175367 * pow(x, 9)) / 689762304000 - (15116515409659 * pow(x, 10)) / 125411328000 + (126865077327869 * pow(x, 11)) / 9656672256000 - (508711662211 * pow(x, 12)) / 452656512000 + (3532831818731 * pow(x, 13)) / 47076277248000 - (242635251253 * pow(x, 14)) / 62768369664000 + (1349130073 * pow(x, 15)) / 8966909952000 - (2949341 * pow(x, 16)) / 689762304000 + (89271043 * pow(x, 17)) / 1067062284288000 - (586003 * pow(x, 18)) / 582033973248000 + (52541 * pow(x, 19)) / 9357315416064000;

        indices.push_back(xCoord);
        indices.push_back(yCoord);
        indices.push_back(zCoord);
    }
}

Mesh mesh(vertices, indices);
return mesh;

vector<Mesh> subdivideTriangles(Mesh mesh, uint32_t resolution)
{
    vector<Mesh> subdividedMeshes;

    for (int triangle = 0; triangle < (mesh.indices.size() / 3); triangle++)
    {
        vector<Vertex> vertices;
        vector<unsigned int> indicies;
        // Get Verticies of seed triangle in counter clockwise order
        Vertex vertex1 = mesh.vertices[mesh.indices[triangle * 3]];
        Vertex vertex2 = mesh.vertices[mesh.indices[triangle * 3 + 1]];
        Vertex vertex3 = mesh.vertices[mesh.indices[triangle * 3 + 2]];

        //* Build Verticies
        // Get basis directions
        glm::vec3 rowDir = (vertex2.Position - vertex1.Position) / (float)resolution;
        glm::vec3 columnDir = (vertex3.Position - vertex2.Position) / (float)resolution;
        // Add first point
        vertices.push_back(vertex1);

        for (float row = 1.0f; row <= (float)resolution; row += 1.0f)
        {
            for (float j = 0.0; j <= row; j += 1.0f)
            {
                Vertex vertex;
                vertex.Position = vertex1.Position + rowDir * row + columnDir * j;
                // Just for debugging, will be replaced with normal maps
                // Only actually normal after points are mapped to sphere
                vertex.Normal = glm::normalize(vertex.Position);
                vertices.push_back(vertex);
            }
        }

        //* Build indicies
        // Loop through each row
        for (int row = 1; row <= resolution; row++)
        {
            // First index of the row (index of top left)
            uint32_t rowStart = (uint32_t)round(1 - 0.5 * row + 0.5 * row * row);

            // Start with /\ triangles
            for (int j = 0; j < row; j++)
            {
                // Top of the Triangle
                indicies.push_back(rowStart + j - 1);
                // Bottom Left
                indicies.push_back(rowStart + row + j - 1);
                // Bottom Right
                indicies.push_back(rowStart + row + j);
            }
            // \/ triangles
            for (int j = 0; j < row - 1; j++)
            {
                // Top Left
                indicies.push_back(rowStart + j - 1);
                // Bottom
                indicies.push_back(rowStart + row + j);
                // Top Right
                indicies.push_back(rowStart + j);
            }
        }
        subdividedMeshes.push_back(Mesh(vertices, indicies));
    }
    return subdividedMeshes;
}
