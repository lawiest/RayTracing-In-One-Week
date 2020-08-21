// PPM.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <fstream>
#include "../../common/color.h"
#include "../../common/ray.h"

bool hit_sphere(const point3& center, const double& radius, const ray& r)
{
    auto A_C = r.origin() - center;
    auto A = dot(r.direction(), r.direction());
    auto B = 2 * dot(r.direction(), A_C);
    auto C = dot(A_C, A_C) - (radius * radius);
    return B * B - 4 * A * C >= 0;
}

color ray_color(const ray r)
{
    if (hit_sphere(point3(0.0, 0.0, -1.0), 0.5, r))
        return color(1.0,0.0,0.0);

     vec3 dir = unit_vector(r.direction());
     auto t = (dir.y() + 1.0) / 2.0;
     return (1 - t) * color(1.0, 1.0, 1.0) + t * color(0.5, 0.7, 1.0);
}

int main()
{
    const auto aspect_ratio = 16.0 / 9.0;
    const int image_width = 400;
    const int image_height = static_cast<int>(image_width / aspect_ratio);

    auto viewport_height = 2.0;
    auto viewport_width = viewport_height * aspect_ratio;
    auto focal_length = 1.0;

    auto origine = vec3(0.0, 0.0, 0.0);
    auto horizontal = vec3(viewport_width, 0.0, 0.0);
    auto vertical = vec3(0.0, viewport_height, 0.0);
    auto lower_left_corner = origine - horizontal / 2.0 - vertical / 2.0 - vec3(0.0, 0.0, focal_length);

    std::ofstream file;
    file.open("./image.ppm");

    file << "P3\n" << image_width << " " << image_height << "\n" << "255\n";

    for (int j = image_height - 1; j >= 0; --j)
    {
		std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;

        for (int i = 0; i < image_width; ++i)
        {
            /*
            auto r = double(i) / (image_width - 1);
            auto g = double(j) / (image_height - 1);
            auto b = 0.25f;
            int ir = static_cast<int>(r * 255.999);
            int ig = static_cast<int>(g * 255.999);
            int ib = static_cast<int>(b * 255.999);*/
            //file << ir << " " << ig << " " << ib << "\n";
            //color color(double(i) / (image_width - 1), double(j) / (image_height - 1),0.25f);

            auto u = double(i) / image_width;
            auto v = double(j) / image_height;

            ray r(origine, lower_left_corner + u * horizontal + v * vertical - origine );

            color c = ray_color(r);

            write_color(file, c);
        }
    }
    std::cerr << "\nDone.\n";

    file.close();



    std::cout << "Hello World!\n";
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
