void getRoverSpeed()
{
    
    const float Wm=4.0;          //max wheel speed rad/sec
    float v1=abs(Vx)+ld*abs(gam);
    float v2=abs(Vy)+lf*abs(gam);
    float w=sqrt(v1*v1+v2*v2)/R;  //max wheel speed for cur config
    //maintain wheel speed below 4 rad/sec
    if(w>Wm)
    {
        float c=1;
        c=w/Wm;
        Vx/=c; Vy/=c; gam/=c;    
    }

}
void getOmega()
{
    getRoverSpeed();
    for(int i=0,j=-1;i<4;i++)
    {
        double V[2];
        V[0]=Vx+j*gam*ld;
        j*=-1;
        //Calculating wheel velocity
        if(i<2)
            V[1]=Vy+lf*gam;
        else
            V[1]=Vy-lr*gam;
        
        //calculating angular velocity
        double r=(V[0]*V[0])+(V[1]*V[1]);
        wRef[i]=sqrt(r)/R;
        ///calculating steer angle
        if(wRef[i]==0)
        {
            delta[i]=0;
        }
        else
        {
            float angRad=atan2(V[1],V[0]);
            int ang=degrees(angRad);
            if(ang>90)
            {
                wRef[i]=-wRef[i];
                ang=90-ang;
            }
            else if(ang<-90)
            {
                wRef[i]=-wRef[i];
                ang=(-90-ang);
            }
            ang*=-1;      // to set it capatable with servo class
            delta[i]=ang;
        }
    }      
}