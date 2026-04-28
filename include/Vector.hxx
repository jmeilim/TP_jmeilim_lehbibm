#ifndef VECTOR_HXX
#define VECTOR_HXX


class Vector {
    private :
    double x , y , z ; 
    public :
    Vector( double x , double y , double z );
    Vector( double x , double y );
    double getX() const;
    double getY() const;
    double getZ() const;


    void setX(double x);
    void setY(double y);
    void setZ(double z);


    Vector operator+(const Vector& v) const;
    Vector operator-(const Vector& v) const;

    Vector operator*(double a) const;

    Vector& operator+=(const Vector& v);
    Vector& operator-=(const Vector& v);


    double& operator[](int i);

    double operator[](int i) const;

};

#endif