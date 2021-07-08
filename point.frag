#version 400
uniform int size;
uniform ivec2 origin;
uniform int order;
void main()
{
    //Zn（xが実部、yが虚部）
    vec2 z = vec2(0.0,0.0);

    //C（xが実部、yが虚部）
    //原点の調整
    vec2 c = vec2((gl_FragCoord.x -640 + origin.x) / size,
                (gl_FragCoord.y - 360 + origin.y) / size);

    //発散したか否か
    bool frag=true;

    float cnt=0.0;

    for(float i=0;i < order;i++)
    {
        if(abs(z.x) >= 2.0)
        {
            //発散したら
            frag = false;
            cnt = i/order;
            break;
        }
        //Z(n+1)=Zn*Zn+C
        z = vec2(z.x * z.x - z.y * z.y + c.x, 2.0 * z.x * z.y + c.y);
    }

    if(!frag)
        if(-0.0025*320/size <= mod(c.x,1.0) && mod(c.x,1.0) <= 0.0025*320/size || 
            -0.0025*320/size <= mod(c.y,1.0) && mod(c.y,1.0) <= 0.0025*320/size)
            gl_FragColor = vec4(0.2,0.2,0.2,1.0);
        else
            gl_FragColor = vec4(cnt,0.0,0.0,1.0);
    else
        gl_FragColor = vec4(1.0,1.0,1.0,1.0);
}
