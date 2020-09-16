// PPM.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <fstream>
#include "../../include/common/color.h"
#include "../../include/common/rtweekend.h"
#include "../../include/hittable_list.h"
#include "../../include/sphere.h"


color ray_color(const ray& r, const hittable& world)
{
	hit_record rec;
	if (world.hit(r, 0, infinity, rec)) {
		return 0.5 * (rec.normal + color(1, 1, 1));
	}
	vec3 unit_direction = unit_vector(r.direction());
	auto t = 0.5 * (unit_direction.y() + 1.0);
	return (1.0 - t) * color(1.0, 1.0, 1.0) + t * color(0.5, 0.7, 1.0);
}

int main()
{
    //image
    const auto aspect_ratio = 16.0 / 9.0;
    const int image_width = 400;
    const int image_height = static_cast<int>(image_width / aspect_ratio);

	// World
	hittable_list world;
	world.add(make_shared<sphere>(point3(0, 0, -1), 0.5));
	world.add(make_shared<sphere>(point3(0, -100.5, -1), 100));

    //Camera
    auto viewport_height = 2.0;
    auto viewport_width = viewport_height * aspect_ratio;
    auto focal_length = 1.0;

    auto origine = vec3(0.0, 0.0, 0.0);
    auto horizontal = vec3(viewport_width, 0.0, 0.0);
    auto vertical = vec3(0.0, viewport_height, 0.0);
    auto lower_left_corner = origine - horizontal / 2.0 - vertical / 2.0 - vec3(0.0, 0.0, focal_length);

    //render
    std::ofstream file;
    file.open("./image.ppm");

    file << "P3\n" << image_width << " " << image_height << "\n" << "255\n";

    for (int j = image_height - 1; j >= 0; --j)
    {
		std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;

        for (int i = 0; i < image_width; ++i)
        {
            auto u = double(i) / image_width;
            auto v = double(j) / image_height;

            ray r(origine, lower_left_corner + u * horizontal + v * vertical - origine );

            color c = ray_color(r,world);

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
