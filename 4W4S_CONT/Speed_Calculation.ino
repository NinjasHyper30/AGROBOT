void getRoverSpeed()
{
    
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
        wRef[i]=sqrt(r);
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