function vector spiralPos(float ang, rad; vector pos){
    vector newpos = pos + set(cos(ang), 0, sin(ang)) * rad;
    return newpos;
}