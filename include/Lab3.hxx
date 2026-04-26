#ifndef PARTICLE_H
#define PARTICLE_H




class Vector {
    private :
    double x , y , z ; 
    public :
    Vector( double x , double y , double z ): x(x) , y(y), z(z) {}
    Vector( double x , double y ): x(x) , y(y) {}
    double getX() const { return x ;}
    double getY() const { return y ;} 
    double getZ() const { return z ;} 
    
    void setX( double x ) { this->x = x ;}
    void setY( double y ) { this->y = y ;}
    void setZ( double z ) { this->z = z ;}
    Vector plus( Vector &v ) const  { return Vector( x+ v.x , y + v.y , z + v.z  ) ;}
    Vector minus( Vector &v ) const  { return Vector( x - v.x , y - v.y , z - v.z  ) ;}
    public :
    double& operator[](int i)
    {
        if(i==0) return x;
        if(i==1) return y;
        return z;
    }
        double operator[](int i) const
    {
        if(i==0) return x;
        if(i==1) return y;
        return z;
    }
};

#endif