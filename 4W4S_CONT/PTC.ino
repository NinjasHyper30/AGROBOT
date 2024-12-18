void estPos()
{
    float xDot,yDot;
    //Tranformation to world cordinate
    xDot=cos(phi)*Vx-sin(phi)*Vy;
    yDot=sin(phi)*Vx+cos(phi)*Vy;
    //Deadrocking
    x+=Ts*xDot;
    y+=Ts*yDot;
    phi+=Ts*gam;
}
void PTC()
{
    estPos();
    float xref,yref,phiref,xDot,yDot;     
    float Kp=8.5;              //propotional constant
    TrajPlanner(xref,yref,phiref);
    //propotional control
    xDot=Kp*(xref-x);
    yDot=Kp*(yref-y);
    gam=Kp*(phiref-phi);
    //Tranformation to rover cordinate
    Vx=(cos(phi)*xDot)+(sin(phi)*yDot);
    Vy=(-sin(phi)*xDot)+(cos(phi)*yDot);
}
