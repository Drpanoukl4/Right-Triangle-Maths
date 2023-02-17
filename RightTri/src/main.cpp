#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"

struct vec2d 
{

    float x;
    float y;

};

vec2d Tris[3];

float posX;
float posY;

float fscale = 45.0f;
float cr = 2.0f;

bool Fnear;

class Example : public olc::PixelGameEngine
{
public:
	Example()
	{
		sAppName = "Example";
	}

public:

    bool IspointedCircle(float cx, float cy, float x, float y, float radius) 
    {

        if (sqrt(( x - cx )*( x - cx ) + ( y - cy )*( y - cy )) < radius)
        {

            return true;

        }else
        {

            return false;

        };

    }


    float Angle(float x0, float y0) 
	{

        float fpi = 3.14159f;

		return acosf(x0 / y0) * 180 / fpi;

	}

    float fDistance (float x, float y, float cx, float cy) 
    {   


        return sqrt(( x - cx )*( x - cx ) + ( y - cy )*( y - cy ));

    }

	bool OnUserCreate() override
	{
		// Called once at the start, so create things here

        posX = ScreenWidth() / 2;
        posY = ScreenHeight() / 2;

        Tris[0].x = 0.0f * fscale;
        Tris[0].y = 0.0f * fscale;

        Tris[1].x = 1.0f * fscale;
        Tris[1].y = 0.0f * fscale;

        Tris[2].x = 1.0f * fscale;
        Tris[2].y = -1.0f * fscale;

        for( int i = 0; i < 3; i ++ )
        {

            Tris[i].x += posX;
            Tris[i].y += posY;

        }

		return true;
	}

	bool OnUserUpdate(float fElapsedTime) override
	{
		// called once per frame

        Clear(olc::Pixel(200,200,200));

        float fSourceX = GetMouseX();
		float fSourceY = GetMouseY();

		for (int x = 0; x < ScreenWidth(); x += 10)
			for (int y = 0; y < ScreenHeight(); y += 10)
				Draw(x, y, olc::Pixel(15,15,15));	


        DrawLine(Tris[0].x, Tris[0].y, Tris[1].x, Tris[1].y, olc::YELLOW);
        DrawLine(Tris[1].x, Tris[1].y, Tris[2].x, Tris[2].y, olc::RED);
        DrawLine(Tris[2].x, Tris[2].y, Tris[0].x, Tris[0].y, olc::VERY_DARK_BLUE);


		FillCircle( Tris[0].x, Tris[0].y, cr, olc::DARK_BLUE);
        FillCircle( Tris[1].x, Tris[1].y, cr, (IspointedCircle(fSourceX, fSourceY, Tris[1].x, Tris[1].y, 6.0f) ? olc::GREEN : olc::DARK_BLUE) );
        FillCircle( Tris[2].x, Tris[2].y, cr, (IspointedCircle(fSourceX, fSourceY, Tris[2].x, Tris[2].y, 6.0f) ? olc::GREEN : olc::DARK_BLUE) );


        if ( IspointedCircle(fSourceX, fSourceY, Tris[2].x, Tris[2].y, 16.0f) )
        {
		    if(GetMouse(0).bHeld)
		    {

                Tris[2].y = GetMouseY();

		    }

        }else
        {

            if ( IspointedCircle(fSourceX, fSourceY, Tris[1].x, Tris[1].y, 16.0f) )
            {
 
		        if(GetMouse(0).bHeld)
		        {

                    Tris[1].x = GetMouseX();
                    Tris[2].x = GetMouseX();

		        }

            }
 
        }

        if(GetKey(olc::Key::Q).bHeld) DrawString(60, 20, "Cosine : " + std::to_string( fDistance (Tris[1].x, Tris[1].y, Tris[0].x, Tris[0].y) / fDistance(Tris[2].x, Tris[2].y, Tris[0].x, Tris[0].y )) , olc::VERY_DARK_GREY);
        if(GetKey(olc::Key::W).bHeld) DrawString(60, 20, "Sine : " + std::to_string( fDistance (Tris[1].x, Tris[1].y, Tris[2].x, Tris[2].y) / fDistance(Tris[2].x, Tris[2].y, Tris[0].x, Tris[0].y )) , olc::VERY_DARK_GREY);
        if(GetKey(olc::Key::E).bHeld) DrawString(60, 20, "Tangent : " + std::to_string( fDistance (Tris[1].x, Tris[1].y, Tris[2].x, Tris[2].y) / fDistance(Tris[0].x, Tris[0].y, Tris[1].x, Tris[1].y )) , olc::VERY_DARK_GREY);

        DrawString(10, 180, "H : " + std::to_string( fDistance (Tris[2].x, Tris[2].y, Tris[0].x, Tris[0].y)) , olc::VERY_DARK_BLUE);
        DrawString(10, 190, "O : " + std::to_string( fDistance (Tris[1].x, Tris[1].y, Tris[2].x, Tris[2].y)) , olc::RED);
        DrawString(10, 200, "A : " + std::to_string( fDistance (Tris[0].x, Tris[0].y, Tris[1].x, Tris[1].y)) , olc::YELLOW);
        DrawString(10, 210, "Angle : "  + std::to_string( Angle( fDistance (Tris[1].x, Tris[1].y, Tris[0].x, Tris[0].y), fDistance (Tris[2].x, Tris[2].y, Tris[0].x, Tris[0].y) )) , olc::WHITE);

		return true;
	}
};


int main()
{
	Example demo;
	if (demo.Construct(256, 240, 4, 4))
		demo.Start();

	return 0;
}
