#include "camera.h"
#pragma GCC diagnostic ignored "-Wsign-compare"
using namespace mssm;
using namespace std;

Camera::Camera(Graphics& g)
    :g{g}
{

}

void Camera::line(Vec2d p1, Vec2d p2, Color c)
{
    p1 = worldToScreen(p1);
    p2 = worldToScreen(p2);
    g.line(p1, p2, c);
}

void Camera::ellipse(Vec2d center, double w, double h, Color c, Color f)
{
    center = worldToScreen(center);
    g.ellipse(center, w, h, c, f);
}

void Camera::arc(Vec2d center, double w, double h, double a, double alen, Color c)
{
    center = worldToScreen(center);
    g.arc(center, w, h, a, alen, c);
}

void Camera::chord(Vec2d center, double w, double h, double a, double alen, Color c, Color f)
{
    center = worldToScreen(center);
    g.chord(center, w, h, a, alen, c, f);
}

void Camera::pie(Vec2d center, double w, double h, double a, double alen, Color c, Color f)
{
    center = worldToScreen(center);
    g.pie(center, w, h, a, alen, c, f);
}

void Camera::rect(Vec2d corner, double w, double h, Color c, Color f)
{
    corner = worldToScreen(corner);
    g.rect(corner, w, h, c, f);
}

void Camera::polygon(std::vector<Vec2d> pts, Color border, Color fill)
{
    for(int i = 0; i < pts.size(); i++){
        pts[i] = worldToScreen(pts[i]);
    }
    g.polygon(pts, border, fill);
}

void Camera::polyline(std::vector<Vec2d> pts, Color color)
{
    for(int i = 0; i < pts.size(); i++){
        pts[i] = worldToScreen(pts[i]);
    }
    g.polyline(pts, color);
}

void Camera::text(Vec2d pos, double size, const string &str, Color textColor, HAlign hAlign, VAlign vAlign)
{
    pos = worldToScreen(pos);
    g.text(pos, size, str, textColor, hAlign, vAlign);
}

void Camera::textExtents(double size, const string &str, TextExtents &extents)
{
    g.textExtents(size, str, extents);
}

void Camera::point(Vec2d pos, Color c)
{
     pos = worldToScreen(pos);
    g.point(pos, c);
}

void Camera::points(std::vector<Vec2d> pts, Color c)
{
    for(int i = 0; i < pts.size(); i++){
        pts[i] = worldToScreen(pts[i]);
    }
    g.points(pts, c);
}

void Camera::image(Vec2d pos, const Image &img)
{
     pos = worldToScreen(pos);
    g.image(pos, img);
}

void Camera::image(Vec2d pos, const Image &img, Vec2d src, int srcw, int srch)
{
     pos = worldToScreen(pos);
    g.image(pos, img, src, srcw, srch);
}

void Camera::image(Vec2d pos, double w, double h, const Image &img)
{
     pos = worldToScreen(pos);
    g.image(pos, w, h, img);
}

void Camera::image(Vec2d pos, double w, double h, const Image &img, Vec2d src, int srcw, int srch)
{
    pos = worldToScreen(pos);
    g.image(pos, w, h, img, src, srcw, srch);
}

void Camera::imageC(Vec2d center, double angle, const Image &img)
{
    center = worldToScreen(center);
    g.imageC(center, angle, img);
}

void Camera::imageC(Vec2d center, double angle, const Image &img, Vec2d src, int srcw, int srch)
{
    center = worldToScreen(center);
    g.imageC(center, angle, img, src, srcw, srch);
}

void Camera::imageC(Vec2d center, double angle, double w, double h, const Image &img)
{
    center = worldToScreen(center);
    g.imageC(center, angle, w, h, img);
}

void Camera::imageC(Vec2d center, double angle, double w, double h, const Image &img, Vec2d src, int srcw, int srch)
{
    center = worldToScreen(center);
    g.imageC(center, angle, w, h, img, src, srcw, srch);
}

bool Camera::isKeyPressed(int c)
{
    return g.isKeyPressed(c);
}

bool Camera::isKeyPressed(Key k)
{
    return g.isKeyPressed(k);
}

int Camera::width()
{
    return g.width();
}

int Camera::height()
{
    return g.height();
}

Vec2d Camera::worldToScreen(Vec2d pt)
{
    return pt + offset;
}

Vec2d Camera::screenToWorld(Vec2d pt)
{
    return pt - offset;
}
