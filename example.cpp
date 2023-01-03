#include <iostream>
#include <fstream>
#include <format>
#include "nms.hpp"

std::vector<std::vector<float>> read_boxes(const std::string& filename)
{
    std::vector<std::vector<float>> boxes;
    std::ifstream file(filename);
    if (!file.is_open())
    {
        std::cout << "file open failed" << std::endl;
        return boxes;
    }
    while (!file.eof())
    {
        std::vector<float> box;
        float x1, y1, x2, y2, score, class_id;
        file >> x1 >> y1 >> x2 >> y2 >> score >> class_id;
        boxes.push_back({x1, y1, x2, y2, score, class_id});
    }
    file.close();
    return boxes;
}

void write_boxes(const std::string& filename, const std::vector<std::vector<float>>& boxes)
{
    std::ofstream file(filename);
    if (!file.is_open())
    {
        std::cout << "file open failed" << std::endl;
        return;
    }
    for (auto box : boxes) // Do you feel uncomfortable? Do you want to use for_each?
    {
       file << std::format("{} {} {} {} {} {}\n", box[0], box[1], box[2], box[3], box[4], box[5]);
    }
    file.close();
}

int main()
{
    std::vector<std::vector<float>> boxes = read_boxes("boxes.txt");
    nms(boxes);
    write_boxes("boxes_nms.txt", boxes);
    return 0;
}
