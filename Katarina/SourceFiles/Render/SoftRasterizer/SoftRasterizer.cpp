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
                screen_coords[j] = Point2((v.x + 1) * width / 2, (v.y + 1) * height / 2);
                world_coords[j] = v;
            }
            Vector3 n = Vector3::cross( world_coords[2] - world_coords[0] , world_coords[1] - world_coords[0]);
            n.normalize();
            real_t intensity = Vector3::dot( n , light_dir);
            if (intensity > 0) 
            {
                Trangle2 trangle{ screen_coords[0], screen_coords[1], screen_coords[2] };
                TGAColor color( intensity * 255, intensity * 255, intensity * 255, 255 );
                fillTriangle(trangle, image, color);
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
        // 不考虑退化三角形
        if (trangle[0].y == trangle[1].y && trangle[0].y == trangle[2].y) 
            return;

        if (trangle[0].y > trangle[1].y)
        {
            std::swap(trangle[0], trangle[1]);
        }
        if (trangle[0].y > trangle[2].y)
        {
            std::swap(trangle[0], trangle[2]);
        }
        if (trangle[1].y > trangle[2].y)
        {
            std::swap(trangle[1], trangle[2]);
        }
        int total_height = trangle[2].y-trangle[0].y;
        for (int i=0; i<total_height; i++) 
        {
            bool second_half = i>trangle[1].y-trangle[0].y || trangle[1].y==trangle[0].y;
            int segment_height = second_half ? trangle[2].y-trangle[1].y : trangle[1].y-trangle[0].y;
            real_t alpha = (real_t)i/total_height;
            real_t beta  = (real_t)(i-(second_half ? trangle[1].y-trangle[0].y : 0))/segment_height;
            Vector2 A = trangle[0] + (trangle[2]-trangle[0])*alpha;
            Vector2 B = second_half ? trangle[1] + (trangle[2]-trangle[1])*beta : trangle[0] + (trangle[1]-trangle[0])*beta;
            if (A.x>B.x) std::swap(A, B);
            for (int j=A.x; j<=B.x; j++)
            {
                image.set(j, trangle[0].y+i, color);
            }
        }
     }
}
