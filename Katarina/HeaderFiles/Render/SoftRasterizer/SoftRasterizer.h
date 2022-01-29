#pragma once
#include"Render/Render.h"
#include "Render/Image/tgaimage.h"
#include "Core/Math/Vector2.h"
#include"Render/Model/Model.h"
#include<memory>
namespace Katarina
{
	class KATARINA_API SoftRasterizer:public Render
	{
	public:
		SoftRasterizer(std::shared_ptr< Model> m) :model(m), Render() {}
		// Í¨¹ý Render ¼Ì³Ð
		virtual void run() const override;
	private:

		void drawLine(Point2i p1, Point2i p2, TGAImage& image, const TGAColor& color)const;
		
		void drawHead()const;

		void drawFilledHead()const;

		void fillTriangle(Trangle2i trangle, TGAImage& image, const TGAColor& color)const;

	private:
		void scanLine(Trangle2i trangle, TGAImage& image, const TGAColor& color)const;
		void barycentric(Trangle2i trangle, TGAImage& image, const TGAColor& color)const;

	private:
		std::shared_ptr< Model> model;
	};


}