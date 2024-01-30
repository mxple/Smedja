#include "RectPacker.h"
#include "Texture.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stbi_write/stbi_image_write.h"
#include <chrono>
#include <filesystem>
#include <iostream>
#include <stb_image.h>

std::vector<std::string> readDirectory(const std::string &directoryPath) {
    std::vector<std::string> files;
    try {
        for (const auto &entry :
             std::filesystem::directory_iterator(directoryPath)) {
            if (std::filesystem::is_regular_file(entry.path())) {
                files.push_back(entry.path().string());
            }
        }
    } catch (const std::exception &e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
    return files;
}

void generateAtlas(const std::string &directoryPath, int padding = 4096) {
    // Read in all images in the directory
    std::vector files = readDirectory(directoryPath);

    std::vector<RectPacker::Rect> rects;
    std::vector<Smedja::Texture> textures;

    // Store them in a vector of Rects
    int textureIndex = 0;
    for (const auto &file : files) {
        // Read in the image
        Smedja::Texture &texture = textures.emplace_back();
        texture.loadFromPath(file);

        // Store the Rect in a vector
        rects.emplace_back(0, 0, texture.width(), texture.height());
        rects.back().textureIndex = textureIndex++;
    }

    std::cerr << "padding: " << padding << std::endl;
    auto t1 = std::chrono::high_resolution_clock::now();

    int dims = RectPacker::binarySearchPack(rects, padding);

    auto t2 = std::chrono::high_resolution_clock::now();
    auto duration =
        std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();

    std::cerr << "Packing took " << duration << "us" << std::endl;

    if (dims == -1) {
        std::cerr << "Failed to pack" << std::endl;
    } else {
        std::cerr << "Packed successfully" << std::endl;
    }

    Smedja::Texture atlas;
    unsigned char *data =
        (unsigned char *)calloc(dims * dims * 4, sizeof(unsigned char));
    atlas.loadFromData(data, dims, dims, 4);

    // Write out to the atlas file
    for (const auto &rect : rects) {
        atlas.subImage(textures[rect.textureIndex], rect.x, rect.y);
    }

    stbi_write_png("atlas.png", atlas.width(), atlas.height(), 4, atlas.data(),
                   0);
    std::cerr << "Atlas size: " << atlas.width() << "x" << atlas.height()
              << std::endl;
} // segfault here

int main(int argc, char **argv) {
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " <directory_path> "
                  << "<padding>" << std::endl;
        return 1;
    }

    generateAtlas(argv[1], std::stoi(argv[2]));

    return 0;
}
