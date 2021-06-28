#version 400
void main()
{
    //Zn（xが実部、yが虚部）
    vec2 z = vec2(0.0,0.0);

    //C（xが実部、yが虚部）
    //原点の調整
    vec2 c = vec2(gl_FragCoord.x / 1280.0 -1.25, gl_FragCoord.y /720.0 -0.5);

    //発散したか否か
    bool frag=true;

    for(int i=0;i < 50;i++)
    {
        if(abs(z.x) > 2.0)
        {
            //発散したら
            frag = false;
            break;
        }
        z = vec2(z.x * z.x + z.y + c.x, 2.0 * z.x * z.y + c.y);
    }

    if(!frag)
        gl_FragColor = vec4(0.0,0.0,0.0,1.0);
    else
        gl_FragColor = vec4(1.0,0.0,0.0,1.0);
}
