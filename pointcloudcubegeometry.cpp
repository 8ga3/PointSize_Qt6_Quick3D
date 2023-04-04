#include "pointcloudcubegeometry.h"
#include <QRandomGenerator>
#include <QVector3D>

constexpr int NUM_POINTS = 10000;

PointCloudCubeGeometry::PointCloudCubeGeometry()
    : m_fPointCount(NUM_POINTS)
{
    updateData();
}

void PointCloudCubeGeometry::updateData()
{
    clear();

    constexpr int stride = (3 + 4) * sizeof(float);

    QByteArray vertexData(m_fPointCount * stride, Qt::Initialization::Uninitialized);
    float *p = reinterpret_cast<float *>(vertexData.data());

    for (int i = 0; i < m_fPointCount; ++i) {
        *p++ = randomFloat(-5.0f, +5.0f);
        float y = randomFloat(-5.0f, +5.0f);
        *p++ = y;
        *p++ = randomFloat(-5.0f, +5.0f);

        float h = (y + 5.0) / 10.0;
        QVector3D color = hsv(h, 0.8, 0.8);

        *p++ = color.x();
        *p++ = color.y();
        *p++ = color.z();
        *p++ = 1.0f;
    }

    setVertexData(vertexData);
    setStride(stride);
    setBounds(QVector3D(-5.0f, -5.0f, -5.0f), QVector3D(+5.0f, +5.0f, +5.0f));

    setPrimitiveType(QQuick3DGeometry::PrimitiveType::Points);

    addAttribute(QQuick3DGeometry::Attribute::PositionSemantic,
                 0,
                 QQuick3DGeometry::Attribute::ComponentType::F32Type);
    addAttribute(QQuick3DGeometry::Attribute::ColorSemantic,
                 3 * sizeof(float),
                 QQuick3DGeometry::Attribute::ComponentType::F32Type);
}

float PointCloudCubeGeometry::randomFloat(const float lowest, const float highest)
{
    return lowest + QRandomGenerator::global()->generateDouble() * (highest - lowest);
}

QVector3D PointCloudCubeGeometry::hsv(float h, float s, float v)
{
    double hh = h * 6.0;
    if (hh >= 6.0) hh = 0;
    int i = (int)hh;
    double f = hh - i;
    float p = v * (1.0 - s);
    float q = v * (1.0 - (s * f));
    float t = v * (1.0 - (s * (1.0 - f)));
    float r, g, b;

    switch(i) {
    case 0:
        r = v;
        g = t;
        b = p;
        break;
    case 1:
        r = q;
        g = v;
        b = p;
        break;
    case 2:
        r = p;
        g = v;
        b = t;
        break;

    case 3:
        r = p;
        g = q;
        b = v;
        break;
    case 4:
        r = t;
        g = p;
        b = v;
        break;
    case 5:
    default:
        r = v;
        g = p;
        b = q;
        break;
    }

    return QVector3D(r, g, b);
}
