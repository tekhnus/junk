uniform float value;
            uniform sampler2D last_spot;
            void main()
            {
                vec4 col = texture2D(last_spot, gl_TexCoord[0].st);
                float or,og,ob,r,g,b;
                or = col.r;
                og = col.g;
                ob = col.b;
                
                r = (or * 0.393 + og * 0.769 + ob * 0.189);
                g = (or * 0.349 + og * 0.686 + ob * 0.168);
                b = (or * 0.272 + og * 0.534 + ob * 0.131);

                vec4 finalColor = vec4(r,g,b,1.0);       
                gl_FragColor = mix(gl_FragColor, finalColor, 1.0);
            }