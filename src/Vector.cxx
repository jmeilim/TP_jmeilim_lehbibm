#include "../include/Vector.hxx"

Vector::Vector(double x,double y,double z)
: x(x), y(y), z(z)
{}

Vector::Vector(double x,double y)
: x(x), y(y), z(0)
{}
double Vector::getX() const { return x ;}
double Vector::getY() const { return y ;} 
double Vector::getZ() const { return z ;} 
    
void Vector::setX( double x ) { this->x = x ;}
void Vector::setY( double y ) { this->y = y ;}
void Vector::setZ( double z ) { this->z = z ;}
Vector Vector::operator+( const Vector& v ) const  { return Vector( x+ v.x , y + v.y , z + v.z  ) ;}
Vector Vector::operator-( const Vector& v ) const  { return Vector( x - v.x , y - v.y , z - v.z  ) ;}
double& Vector::operator[](int i)
{
    if(i==0) return x;
    if(i==1) return y;
    return z;
}
    double Vector::operator[](int i) const
{
    if(i==0) return x;
    if(i==1) return y;
    return z;
}

