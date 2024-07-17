#include <SFML/Graphics.hpp>
#include <iostream>
#include <math.h>


// https://www.youtube.com/watch?v=kCIaHqb60Cw

//sf::Vector2f RandomGradient(int ix, int iy) {
//    // No precomputed gradients mean this works for any number of grid coordinates
//    const unsigned w = 8 * sizeof(unsigned);
//    const unsigned s = w / 2;
//    unsigned a = ix, b = iy;
//    a *= 3284157443;
//
//    b ^= a << s | a >> w - s;
//    b *= 1911520717;
//
//    a ^= b << s | b >> w - s;
//    a *= 2048419325;
//    float random = a * (3.14159265 / ~(~0u >> 1)); // in [0, 2*Pi]
//
//    // Create the vector from the angle
//    sf::Vector2f v;
//    v.x = sin(random);
//    v.y = cos(random);
//
//    return v;
//}
//
//
//// dot product of the distance and gradient vectors
//float DotGridGradient(int ix, int iy, float fx, float fy)
//{
//	sf::Vector2f gradient = RandomGradient(ix, iy); 
//    
//    //distance Vector
//    float dx = fx - (float)ix; 
//    float dy = fy - (float)iy;
//
//    // Dot Product
//    return (dx * gradient.x + dy * gradient.y); 
//}
//
//float Interpolate(float a0, float a1, float weight)
//{
//    return (a1 - a0) * (3.0 - weight * 2.0) * weight * weight + a0; 
//}
//
//float Perlin(float x, float y)
//{
//	// grid cell corners
//	int x0 = (int)x; 
//	int y0 = (int)y; 
//	int x1 = x0++; 
//	int y1 = y0++; 
//
//	// interpolation weights
//	float sx = x - (float)x0; 
//	float sy = y - (float)y0;
//
//    // interpolate top two corners
//    float n0 = DotGridGradient(x0, y0, x, y); 
//    float n1 = DotGridGradient(x1, y0, x, y);
//    float ix0 = Interpolate(n0, n1, sx);
//
//    // interpolate bottom two corners
//    n0 = DotGridGradient(x0, y1, x, y);
//    n1 = DotGridGradient(x1, y1, x, y);
//    float ix1 = Interpolate(n0, n1, sx);
//
//    return Interpolate(ix0, ix1, sy);
//}