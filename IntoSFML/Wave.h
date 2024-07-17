#pragma once
class Wave
{
public: 

	float seed; 
	float frequency; 
	float amplitude; 

	Wave(float Seed, float Frequency, float Amplitude)
		: seed(Seed),frequency(Frequency),amplitude(Amplitude)
	{}
};
