varying vec3 vertex;
varying vec3 worldVertex;
varying vec3 normal;
varying vec3 lightDir;

/*
 * 2D, 3D and 4D Perlin noise, classic and simplex, in a GLSL fragment shader.
 *
 * Classic noise is implemented by the functions:
 * float noise(vec2 P)
 * float noise(vec3 P)
 * float noise(vec4 P)
 *
 * Simplex noise is implemented by the functions:
 * float snoise(vec2 P)
 * float snoise(vec3 P)
 * float snoise(vec4 P)
 *
 * Author: Stefan Gustavson ITN-LiTH (stegu@itn.liu.se) 2004-12-05
 * You may use, modify and redistribute this code free of charge,
 * provided that my name and this notice appears intact.
 */

/*
 * To create offsets of one texel and one half texel in the
 * texture lookup, we need to know the texture image size.
 */

float fade(float t) {
  // return t*t*(3.0-2.0*t); // Old fade, yields discontinuous second derivative
  return t*t*t*(t*(t*6.0-15.0)+10.0); // Improved fade, yields C2-continuous noise
}

#define ONE 0.00390625
#define ONEHALF 0.001953125
// The numbers above are 1/256 and 0.5/256, change accordingly
// if you change the code to use another texture size.


uniform sampler2D permTexture;
//uniform sampler1D simplexTexture;
uniform float time;
/*
 * 3D simplex noise. Comparable in speed to classic noise, better looking.
 */

/*
 * 3D classic noise. Slower, but a lot more useful than 2D noise.
 */
float noise(vec3 P)
{
  vec3 Pi = ONE*floor(P)+ONEHALF; // Integer part, scaled so +1 moves one texel
                                  // and offset 1/2 texel to sample texel centers
  vec3 Pf = fract(P);     // Fractional part for interpolation

  // Noise contributions from (x=0, y=0), z=0 and z=1
  float perm00 = texture2D(permTexture, Pi.xy).a ;
  vec3  grad000 = texture2D(permTexture, vec2(perm00, Pi.z)).rgb * 4.0 - 1.0;
  float n000 = dot(grad000, Pf);
  vec3  grad001 = texture2D(permTexture, vec2(perm00, Pi.z + ONE)).rgb * 4.0 - 1.0;
  float n001 = dot(grad001, Pf - vec3(0.0, 0.0, 1.0));

  // Noise contributions from (x=0, y=1), z=0 and z=1
  float perm01 = texture2D(permTexture, Pi.xy + vec2(0.0, ONE)).a ;
  vec3  grad010 = texture2D(permTexture, vec2(perm01, Pi.z)).rgb * 4.0 - 1.0;
  float n010 = dot(grad010, Pf - vec3(0.0, 1.0, 0.0));
  vec3  grad011 = texture2D(permTexture, vec2(perm01, Pi.z + ONE)).rgb * 4.0 - 1.0;
  float n011 = dot(grad011, Pf - vec3(0.0, 1.0, 1.0));

  // Noise contributions from (x=1, y=0), z=0 and z=1
  float perm10 = texture2D(permTexture, Pi.xy + vec2(ONE, 0.0)).a ;
  vec3  grad100 = texture2D(permTexture, vec2(perm10, Pi.z)).rgb * 4.0 - 1.0;
  float n100 = dot(grad100, Pf - vec3(1.0, 0.0, 0.0));
  vec3  grad101 = texture2D(permTexture, vec2(perm10, Pi.z + ONE)).rgb * 4.0 - 1.0;
  float n101 = dot(grad101, Pf - vec3(1.0, 0.0, 1.0));

  // Noise contributions from (x=1, y=1), z=0 and z=1
  float perm11 = texture2D(permTexture, Pi.xy + vec2(ONE, ONE)).a ;
  vec3  grad110 = texture2D(permTexture, vec2(perm11, Pi.z)).rgb * 4.0 - 1.0;
  float n110 = dot(grad110, Pf - vec3(1.0, 1.0, 0.0));
  vec3  grad111 = texture2D(permTexture, vec2(perm11, Pi.z + ONE)).rgb * 4.0 - 1.0;
  float n111 = dot(grad111, Pf - vec3(1.0, 1.0, 1.0));

  // Blend contributions along x
  vec4 n_x = mix(vec4(n000, n001, n010, n011),
                 vec4(n100, n101, n110, n111), fade(Pf.x));

  // Blend contributions along y
  vec2 n_xy = mix(n_x.xy, n_x.zw, fade(Pf.y));

  // Blend contributions along z
  float n_xyz = mix(n_xy.x, n_xy.y, fade(Pf.z));

  // We're done, return the final noise value.
  return n_xyz;
}

const float scale = 5.0;

void main (void)
{
  
  vec3 lightVec = vec3(0.0, 1.0, 0.0);
  
  vec4 color = vec4(0.1, 0.24, 0.65, 1.0);
  
  vec3 eyeDir = normalize(-vertex);
  //vec3 lightDir = normal;
  vec3 reflected = gl_NormalMatrix * lightVec;//-reflect(normalize(lightDir), normalize(normal));
  float n = 0.5 + 0.7 * 0.5 * noise(vec3(worldVertex.x/scale, worldVertex.z/scale, time/1.5));
  float kSpec = pow(max(0.0, dot(eyeDir, reflected)), 0.7) * 1.0 * n;
  color += vec4(1.0, 1.0, 1.0, 1.0)*kSpec*kSpec;
  
  gl_FragColor = clamp(color, 0.0, 1.0);
  gl_FragColor.w = 0.7;
}

