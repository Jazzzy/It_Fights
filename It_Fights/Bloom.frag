uniform sampler2D texture;


void main()
{
    // lookup the pixel in the texture
    vec4 pixel = texture2D(texture, gl_TexCoord[0].xy);
    
    // multiply it by the color
    pixel = gl_Color * pixel;
    

    vec4 sum = vec4(0);
    vec2 texcoord = gl_TexCoord[0].xy;

    
    
    for( int i= -4 ;i < 4; i++)
    {
        for ( int j = -3; j < 3; j++)
        {
            sum += texture2D(texture, texcoord + vec2(j, i)*0.004) * 0.25;
        }
    }
    

    if (texture2D(texture, texcoord).r < 0.3)
    {
        gl_FragColor = sum*sum*0.012 + texture2D(texture, texcoord);
    }
    else
    {
        if (texture2D(texture, texcoord).r < 0.5)
        {
            gl_FragColor = sum*sum*0.009 + texture2D(texture, texcoord);
        }
        else
        {
            gl_FragColor = (sum*sum*0.0075) * pixel;
        }
    }
    
    
}
