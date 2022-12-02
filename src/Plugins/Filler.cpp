#include "Filler.hpp"
#include "Color.hpp"
#include <queue>
#include <set>
#include "Vector.hpp"

using Point = mgm::Vector2<int64_t>;

static int cmpColors(const Color& c1, const Color c2)
{
    int diff = (
        (c1.r() - c2.r()) * (c1.r() - c2.r()) + 
        (c1.g() - c2.g()) * (c1.g() - c2.g()) + 
        (c1.b() - c2.b()) * (c1.b() - c2.b()) + 
        (c1.a() - c2.a()) * (c1.a() - c2.a())
        );
    return diff ?  diff / 262 + 1 : 0;
}

static bool isOnImage(Image* image, int x, int y)
{
    return x >= 0 && x < static_cast<int>(image->getW()) && 
           y >= 0 && y < static_cast<int>(image->getH());
}


void Filler::apply(Image* image, const Event* event)
{
    if(event->type == EventType::MousePressed && event->Oleg.mbedata.button == MouseButton::Left && isOnImage(image, event->Oleg.mbedata.x, event->Oleg.mbedata.y))
    {
        fill(image, event->Oleg.mbedata.x, event->Oleg.mbedata.y, event->Oleg.mbedata.ctrl ? APPCONTEXT->bgColor : APPCONTEXT->fgColor);
    }
}


void Filler::fill(Image* image, int startX, int startY, Color fillColor)
{
    Color startColor = image->getPixel(startX, startY);
    std::queue<Point> q;
    std::set<Point> visited;
    q.push(Point(startX, startY));
    visited.insert(Point(startX, startY));

    const int colorEdge = 3;

    while (!q.empty()) {
        Point pt = q.front();
        q.pop();
        image->setPixel(pt.x, pt.y, fillColor);

        pt.x++;
        if(pt.x < static_cast<int>(image->getW()) && !visited.contains(pt) && cmpColors(startColor, image->getPixel(pt.x, pt.y)) < colorEdge)
        {
            q.push(pt);
            visited.insert(pt);
        }

        pt.x-=2;
        if(pt.x >= 0 && !visited.contains(pt) && cmpColors(startColor, image->getPixel(pt.x, pt.y)) < colorEdge)
        {
            q.push(pt);
            visited.insert(pt);
        }

        pt.x++;
        pt.y++;
        if(pt.y < static_cast<int>(image->getH()) &&!visited.contains(pt) && cmpColors(startColor, image->getPixel(pt.x, pt.y)) < colorEdge)
        {
            q.push(pt);
            visited.insert(pt);
        }

        pt.y-=2;
        if(pt.y >= 0 && !visited.contains(pt) && cmpColors(startColor, image->getPixel(pt.x, pt.y)) < colorEdge)
        {
            q.push(pt);
            visited.insert(pt);
        }
    }
}

extern "C" void init_module()
{
    addTool(new Filler);
}

static const GUID GUID_ = {"0d5aa80-c6b7-4126-ae88-5343a7eaf6b3"};

extern "C" GUID getGUID()
{
    return GUID_;
}
