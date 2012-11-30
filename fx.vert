varying vec3 normal;
varying vec3 vertex_to_light_vector;
 
void main()
{
    gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
}