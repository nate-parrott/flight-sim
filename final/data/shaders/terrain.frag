uniform sampler2D shadow;
uniform sampler2D sand;
uniform sampler2D grass;
uniform sampler2D rock;
uniform sampler2D snow;

uniform vec2 shadowPos;
uniform vec2 shadowSize;

varying vec3 vertex;
varying vec3 worldVertex;
varying vec3 normal;
varying vec3 lightDir;
varying vec4 terrainTexture;

const float texScale = 50.0;

const float diffuseEffect = 0.6; // from 0.0 to 1.0

float rangeWeight(float x, float start, float end) {
  if (x < start || x > end) {
    return 0.0;
  } else {
    return 1.0-abs((end+start)*0.5 - x)/(end-start)*2.0;
  }
}

void main (void)
{
  vec2 texCoord = vec2(mod(worldVertex.x/texScale, 1.0), mod(worldVertex.z/texScale, 1.0));
  float y = clamp(worldVertex.y, 0.01, 0.99);
    
  vec4 color = vec4(0.0);
  float totalContrib = 0.0;
  float contrib = 0.0;
  
  contrib = terrainTexture.x;
  color += texture2D(sand, texCoord)*contrib;
  totalContrib += contrib;
  
  contrib = terrainTexture.y;
  color += texture2D(grass, texCoord)*contrib;
  totalContrib += contrib;
  
  contrib = terrainTexture.z;
  color += texture2D(rock, texCoord)*contrib;
  totalContrib += contrib;
  
  contrib = terrainTexture.w;
  color += texture2D(snow, texCoord)*contrib;
  totalContrib += contrib;
  
  color /= totalContrib;
  
  color *= 1.0-diffuseEffect + diffuseEffect*(dot(normalize(vec3(gl_LightSource[0].position)-vertex), normalize(normal)));
  
  if (worldVertex.x >= shadowPos.x - shadowSize.x/2.0 &&
    worldVertex.x < shadowPos.x + shadowSize.x/2.0 &&
      worldVertex.z >= shadowPos.y - shadowSize.y/2.0 &&
        worldVertex.z < shadowPos.y + shadowSize.y/2.0) {
          vec4 shadowColor = texture2D(shadow, vec2((worldVertex.x - shadowPos.x)/shadowSize.x + 0.5, (worldVertex.z - shadowPos.y)/shadowSize.y + 0.5));
          color *= 0.5 + shadowColor * 0.5;
        }
  //color *= 0.5 + 0.5 * texture2D(shadow, shadowCoord);
  
  gl_FragColor = color;
}

