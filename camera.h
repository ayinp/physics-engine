#ifndef CAMERA_H
#define CAMERA_H
#include "graphics.h"

class Camera
{
public:
    Vec2d offset = {0,0};
    mssm::Graphics& g;
public:
    Camera(mssm::Graphics& g);
    void   line(Vec2d p1, Vec2d p2, mssm::Color c = mssm::WHITE);
    void   ellipse(Vec2d center, double w, double h, mssm::Color c = mssm::WHITE, mssm::Color f = mssm::TRANSPARENT);
    void   arc(Vec2d center, double w, double h, double a, double alen, mssm::Color c = mssm::WHITE);
    void   chord(Vec2d center, double w, double h, double a, double alen, mssm::Color c = mssm::WHITE, mssm::Color f = mssm::TRANSPARENT);
    void   pie(Vec2d center, double w, double h, double a, double alen, mssm::Color c = mssm::WHITE, mssm::Color f = mssm::TRANSPARENT);
    void   rect(Vec2d corner, double w, double h, mssm::Color c = mssm::WHITE, mssm::Color f = mssm::TRANSPARENT);
    void   polygon(std::vector<Vec2d> pts, mssm::Color border, mssm::Color fill = mssm::TRANSPARENT);
    void   polyline(std::vector<Vec2d> pts, mssm::Color color);
    void   text(Vec2d pos, double size, const std::string& str, mssm::Color textColor = mssm::WHITE, mssm::HAlign hAlign = mssm::HAlign::left, mssm::VAlign vAlign = mssm::VAlign::baseline);

    void   textExtents(double size, const std::string& str, mssm::TextExtents& extents);

    void   point(Vec2d pos, mssm::Color c);
    void   points(std::vector<Vec2d> pts, mssm::Color c);

    void   image(Vec2d pos, const mssm::Image& img);
    void   image(Vec2d pos, const mssm::Image& img, Vec2d src, int srcw, int srch);
    void   image(Vec2d pos, double w, double h, const mssm::Image& img);
    void   image(Vec2d pos, double w, double h, const mssm::Image& img, Vec2d src, int srcw, int srch);

    void   imageC(Vec2d center, double angle, const mssm::Image& img);
    void   imageC(Vec2d center, double angle, const mssm::Image& img, Vec2d src, int srcw, int srch);
    void   imageC(Vec2d center, double angle, double w, double h, const mssm::Image& img);
    void   imageC(Vec2d center, double angle, double w, double h, const mssm::Image& img, Vec2d src, int srcw, int srch);

    bool   isKeyPressed(int c);
    bool   isKeyPressed(mssm::Key k);

    int    width();
    int    height();

    Vec2d worldToScreen(Vec2d pt);
    Vec2d screenToWorld(Vec2d pt);
};

#endif // CAMERA_H
