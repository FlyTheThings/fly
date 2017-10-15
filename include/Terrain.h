#ifndef TERRAIN_H
#define TERRAIN_H

#include <vector>
#include <unordered_map>
#include "TerrainRenderer.h"
#include "Drawable.h"
#include "BoundingBox.h"


namespace fly
{


class Terrain : public Drawable
{
public:
    Terrain(int radius, int detail);
    void generate(float seed);
    bool above(const OBB& obb);
    void draw() override    { m_renderer.draw(); };
    void rawDraw() override { m_renderer.rawDraw(); };
    void moveCenter(const glm::vec2& displacement);
    void setCenter(const glm::vec2& pos) { moveCenter(pos - m_center); }
    void setView(const glm::mat4& view) { m_renderer.setView(view); }
    void setLightSpace(const glm::mat4& lm) { m_renderer.setLightSpace(lm); }
    void setProjection(const glm::mat4& proj) { m_renderer.setProjection(proj); }
private:
    int getChunkIndexX(int x);
    int getChunkIndexY(int y);

    struct Pair
    {
        int x, y;
    };

    void generateChunk(int chunk_x, int chunk_y, int coord_x, int coord_y, std::vector<float>& heights,
                       std::vector<float>& color);
    Pair& chunk (int x, int y) { return m_chunkMap[x + m_radius - 1][y + m_radius - 1]; }


    const int                      m_radius;
    const int                      m_detail;
    const int                      m_totalChunks;
    const int                      m_verticesPerChunk;

    float                          m_seed;

    glm::vec2                      m_center;
    Pair                           m_centerChunk;
    std::vector<std::vector<Pair>> m_chunkMap;    // maps chunk index to the coords they store
    std::vector<float>             m_heightMap;

    TerrainRenderer                m_renderer;
};

}
#endif // TERRAIN_H
