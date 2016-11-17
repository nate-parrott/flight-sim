varying vec3 vertex;
varying vec3 worldVertex;
varying vec3 normal;
varying vec3 lightDir;
attribute vec4 terrainTextureAttribute;
varying vec4 terrainTexture;

void main (void)
{
  worldVertex = vec3(gl_Vertex);
  vertex = vec3(gl_ModelViewMatrix * gl_Vertex);
  normal = normalize(vec3(gl_NormalMatrix * gl_Normal));
  lightDir = normalize(vec3(gl_ModelViewMatrix * gl_LightSource[0].position) - vertex);
  gl_Position = gl_ProjectionMatrix * (gl_ModelViewMatrix * gl_Vertex);
  terrainTexture = terrainTextureAttribute;
}
