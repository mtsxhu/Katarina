#include"Render/SoftRasterizer/SoftRasterizer.h"
#include<cmath>
namespace Katarina 
{
    void SoftRasterizer::run() const
    {
        drawFilledHead();
    }

    void SoftRasterizer::drawHead()const
    {
        // TODO 摄像机
        const int width = 800;
        const int height = 800;
        TGAImage image(width, height, TGAImage::RGB);
        const TGAColor white = TGAColor(255, 255, 255, 255);
        for (int i = 0; i < model->nfaces(); i++) 
        {
            std::vector<int> face = model->face(i);
            for (int j = 0; j < 3; j++) 
            {
                Vector3 v0 = model->vert(face[j]);
                Vector3 v1 = model->vert(face[(j + 1) % 3]);
                Point2 p1{ (v0.x + 1) * width / 2,(v0.y + 1) * height / 2 };
                Point2 p2{ (v1.x + 1) * width / 2 ,(v1.y + 1) * height / 2 };
                drawLine(p1, p2, image,  white);
            }
        }
       // image.flip_vertically();
        image.write_tga_file("output.tga");
    }

    void SoftRasterizer::drawFilledHead()const
    {
        // TODO 摄像机
        const int width = 800;
        const int height = 800;
        Vector3 light_dir(0, 0, -1);
            TGAImage image(width, height, TGAImage::RGB);
        for (int i = 0; i < model->nfaces(); i++) 
        {
            std::vector<int> face = model->face(i);
            Point2 screen_coords[3];
            Vector3 world_coords[3];
            for (int j = 0; j < 3; j++) 
            {
                Vector3 v = model->vert(face[j]);
                screen_coords[j] = Point2((v.x + 1.) * width / 2., (v.y + 1.) * height / 2.);
                world_coords[j] = v;
            }
            Vector3 n = (world_coords[2] - world_coords[0]) ^ (world_coords[1] - world_coords[0]);
            n.normalize();
            real_t intensity = Vector3::dot( n , light_dir);
            if (intensity > 0) 
            {
                fillTriangle(Trangle2{ screen_coords[0], screen_coords[1], screen_coords[2] }, image,
                    TGAColor(intensity * 255, intensity * 255, intensity * 255, 255));
            }
        }
        // image.flip_vertically();
        image.write_tga_file("output.tga");
    }

    void SoftRasterizer::drawLine( Point2 p1,  Point2 p2, TGAImage& image, const TGAColor& color)const
    {
        bool steep = false;
        // 如果线段斜率大于1（陡峭），则翻转线段
        if (std::abs(p1.x - p2.x) < std::abs(p1.y - p2.y))
        {
            std::swap(p1.x, p1.y);
            std::swap(p2.x, p2.y);
            steep = true;
        }
        // 确保从左向右画
        if (p1.x > p2.x) 
        {
            std::swap(p1.x, p2.x);
            std::swap(p1.y, p2.y);
        }
        int dx = p2.x - p1.x;
        int dy = p2.y - p1.y;
        int derror = std::abs(dy) * 2;
        int error = 0;
        int y = p1.y;
        const int yinc = (p2.y > p1.y ? 1 : -1);
        auto errorFunc = [&]() {
            error += derror;
            if (error > dx)
            {
                y += yinc;
                error -= dx * 2;
            }
        };
        auto steepFunc = [&]() {
            for (int x = p1.x; x <= p2.x; ++x)
            {
                image.set(y, x, color);
                errorFunc();
            }
        };
        auto normalFunc = [&]() {
            for (int x = p1.x; x <= p2.x; ++x)
            {
                image.set(x, y, color);
                errorFunc();
            }
        };
        if (steep) {
            steepFunc();
        }
        else
        {
            normalFunc();
        }
    }

    void SoftRasterizer::fillTriangle(Trangle2 trangle,TGAImage& image, const TGAColor& color)const
    {
        Point2 bboxmin(image.get_width() - 1, image.get_height() - 1);
        Point2 bboxmax(0, 0);
        Point2 clamp(image.get_width() - 1, image.get_height() - 1);
        for (int i = 0; i < 3; i++) 
        {
            for (int j = 0; j < 2; j++) 
            {
                bboxmin[j] = std::max(0.0, std::min(bboxmin[j], trangle[i][j]));
                bboxmax[j] = std::min(clamp[j], std::max(bboxmax[j], trangle[i][j]));
            }
        }
        Point2 p;
        for (p.x = bboxmin.x; p.x <= bboxmax.x; p.x++)
        {
            for (p.y = bboxmin.y; p.y <= bboxmax.y; p.y++)
            {
                Vector3 bc_screen = Math::GetBarycentric(trangle, p);
                if (bc_screen.x < 0 || bc_screen.y < 0 || bc_screen.z < 0) 
                    continue;
                image.set(p.x, p.y, color);
            }
        }
     }
}
