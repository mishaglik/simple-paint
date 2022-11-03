#include "BasicTools.hpp"
#include <set>
#include <queue>
namespace mge {
    namespace tools {

        KatmulRom::KatmulRom() {}   
        KatmulRom::~KatmulRom() {}

        void KatmulRom::addPoint(aGL::Point pt)
        {
            mgm::Vector2f v = mgm::asVector(pt);

            if(points_ == 4)
            {
                y_[0] = y_[1];
                y_[1] = y_[2];
                y_[2] = y_[3];
                y_[3] = v;
                dy_[0] = dy_[1];
            }
            else {
                for(uint8_t i = points_; i < 4; ++i)
                    y_[i] = v;
                points_++;
                dy_[0] =  y_[2];
                dy_[0] -= y_[0];
                dy_[0] *= 0.5;
            }

            dy_[1] =  y_[3];
            dy_[1] -= y_[1];
            dy_[1] *= 0.5;

            a_[0] = y_[1];
            a_[1] = dy_[1];

            a_[3] = y_[1];
            a_[3] -= y_[2];
            a_[3] *= 2;
            a_[3] += dy_[1];
            a_[3] += dy_[0];

            a_[2] = y_[2];
            a_[2] -= a_[0];
            a_[2] -= a_[1];
            a_[2] -= a_[3];
        }

        void KatmulRom::reset()
        {
            points_ = 0;
        }

        aGL::Point KatmulRom::getPoint(double t)
        {
            // t += 1;
            double x = 1;
            mgm::Point2f ans = {};
            for(uint8_t i = 0; i < 4; ++i)
            {
                mgm::Vector2f p = a_[i];
                p *= x;
                ans += p;
                x *= t;
            }
            return ans;
        }

        void drawLine(aGL::Image* image, aGL::Point p0, aGL::Point p1, aGL::Color color)
        {
            mAssert(image);
            // if(p1.x < p0.x) std::swap(p0, p1);
            int dx = abs(p1.x - p0.x);
            int sx = p0.x < p1.x ? 1 : -1;
            int dy = -abs(p1.y - p0.y);
            int sy = p0.y < p1.y ? 1 : -1;
            int error = dx + dy;
            int x = p0.x;
            int y = p0.y;
            while(p1 != aGL::Point(x, y))
            {
                image->setPixel(x, y, color);
                int e2 = 2 * error;
                if(e2 >= dy)
                {
                    if(x == p1.x) break;
                    error += dy;
                    x += sx;
                }
                if(e2 <= dy)
                {
                    if(y == p1.y) break;
                    error += dx;
                    y += sy;
                }
            }
            image->setPixel(x, y, color);
        }


        void RectFiller::onMousePress(const ToolAction& action)
        {
            if(hasFirst_)
            {   
                aGL::Point second = action.point;
                if(first_.x > second.x)
                    std::swap(first_.x, second.x);
                if(first_.y > second.y)
                    std::swap(first_.y, second.y);

                for(int x = first_.x; x <= second.x; ++x)
                    for(int y = first_.y; y <= second.y; ++y)
                        action.image->setPixel(x, y, context_->foregroundColor);
                hasFirst_ = false;
            }
            else
            {
                first_ = action.point;
                hasFirst_ = true;
            }
        }

        void EllipseFiller::onMousePress(const ToolAction& action)
        {
            if(hasFirst_)
            {   
                aGL::Point second = action.point;
                if(first_.x > second.x)
                    std::swap(first_.x, second.x);
                if(first_.y > second.y)
                    std::swap(first_.y, second.y);
                int w = (second.x - first_.x) / 2;
                int h = (second.y - first_.y) / 2;
                int w2 = w * w;
                int h2 = h * h;
                for(int x = first_.x; x <= second.x; ++x)
                {
                    for(int y = first_.y; y <= second.y; ++y)
                    {
                        int dx2 = (x - first_.x - w) * (x - first_.x - w);
                        int dy2 = (y - first_.y - h) * (y - first_.y - h);
                        if(dx2 * h2 + dy2 * w2 <= w2 * h2)
                            action.image->setPixel(x, y, context_->foregroundColor);
                    }
                }
                hasFirst_ = false;
            }
            else
            {
                first_ = action.point;
                hasFirst_ = true;
            }
        }

        int cmpColors(const aGL::Color& c1, const aGL::Color c2)
        {
            int diff = (
                (c1.r() - c2.r()) * (c1.r() - c2.r()) + 
                (c1.g() - c2.g()) * (c1.g() - c2.g()) + 
                (c1.b() - c2.b()) * (c1.b() - c2.b()) + 
                (c1.a() - c2.a()) * (c1.a() - c2.a())
             );
            return diff ?  diff / 262 + 1 : 0;
        }

        void Filler::onMousePress(const ToolAction& action)
        {
            aGL::Color startColor = action.image->getPixel(action.point.x, action.point.y);
            std::queue<aGL::Point> q;
            std::set<aGL::Point> st;
            q.push(action.point);
            st.insert(action.point);

            const int colorEdge = 3;

            while (!q.empty()) {
                aGL::Point pt = q.front();
                q.pop();
                action.image->setPixel(pt.x, pt.y, action.ctrl ?  context_->backgroundColor : context_->foregroundColor);

                pt.x++;
                if(pt.x < static_cast<int>(action.image->getW()) && !st.contains(pt) && cmpColors(startColor, action.image->getPixel(pt.x, pt.y)) < colorEdge)
                {
                    q.push(pt);
                    st.insert(pt);
                }

                pt.x-=2;
                if(pt.x >= 0 && !st.contains(pt) && cmpColors(startColor, action.image->getPixel(pt.x, pt.y)) < colorEdge)
                {
                    q.push(pt);
                    st.insert(pt);
                }

                pt.x++;
                pt.y++;
                if(pt.y < static_cast<int>(action.image->getH()) &&!st.contains(pt) && cmpColors(startColor, action.image->getPixel(pt.x, pt.y)) < colorEdge)
                {
                    q.push(pt);
                    st.insert(pt);
                }

                pt.y-=2;
                if(pt.y >= 0 && !st.contains(pt) && cmpColors(startColor, action.image->getPixel(pt.x, pt.y)) < colorEdge)
                {
                    q.push(pt);
                    st.insert(pt);
                }
            }
        }

    }
}
