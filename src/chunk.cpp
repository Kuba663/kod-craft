#include "chunk.h"

void Chunk::draw() {
    int chunkSize = this->parent->getChunkSize();

    for (int x = 0; x < chunkSize; x++)
    for (int y = 0; y < chunkSize; y++)
    for (int z = 0; z < chunkSize; z++) {
        this->blocks[x][y][z].draw();
    }
}

Chunk::Chunk(Dimension* dimension, int x, int y, int z) {
    this->dimension = dimension;

    this->x = x;
    this->y = y;
    this->z = z;

    int chunkSize = dimension->getChunkSize();

    PyObject* generateChunkCallback = dimension->getTemplate()->generateChunkCallback;
    PyObject* chunkArray = PyObject_CallObject(generateChunkCallback, Py_BuildValue("(iiii)", x, y, z, chunkSize));

    // allocate memory
    this->blocks = (Block***) malloc(chunkSize * sizeof(Block**));

    for (int bX = 0; bX < chunkSize; bX++) {
        this->blocks[bX] = (Block**) malloc(chunkSize * sizeof(Block*));
        PyObject* chunkArrayX = PyList_GetItem(chunkArray, bX);

        for (int bY = 0; bY < chunkSize; bY++) {
            this->blocks[bX][bY] = (Block*) malloc(chunkSize * sizeof(Block));
            PyObject* chunkArrayXY = PyList_GetItem(chunkArrayX, bY);

            for (int bZ = 0; bZ < chunkSize; bZ++) {
                PyObject* chunkBlock = PyList_GetItem(chunkArrayXY, bZ);

                this->blocks[bX][bY][bZ] = Block(PyUnicode_AsUTF8(chunkBlock));
            }
        }
    }
}

void Chunk::setBlock(Block block, WorldPos x, WorldPos y, WorldPos z) {
    int chunkSize = this->dimension->getChunkSize();

    x = x%chunkSize;
    y = y%chunkSize;
    z = z%chunkSize;

    this->blocks[x][y][z] = block;
}

ChunkPos Chunk::getX() {
    return this->x;
}

ChunkPos Chunk::getY() {
    return this->y;
}

ChunkPos Chunk::getZ() {
    return this->z;
}
