#ifndef FACE_H
#define FACE_H

#include <QVector3D>

class Face
{
public:
    Face();
    Face(int id,int s1,int s2,int s3);

    int getId() const;

    int getS1() const;
    int getS2() const;
    int getS3() const;

    void setId(int s1);

    void setS1(int s1);
    void setS2(int s2);
    void setS3(int s3);

    int getT1() const;
    int getT2() const;
    int getT3() const;

    void setT1(int t1);
    void setT2(int t2);
    void setT3(int t3);

    void addTr(int tr);

    bool operator!=(Face const& a) ;
private:

    int id;

    int s1;
    int s2;
    int s3;

    int t1;
    int t2;
    int t3;
};

#endif // FACE_H
