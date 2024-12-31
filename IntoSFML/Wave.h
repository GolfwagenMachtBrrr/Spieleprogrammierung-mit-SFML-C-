#pragma once
struct Wave
{

	float seed; 
	float frequency; 
	float amplitude; 

	Wave(const float &Seed, const float &Frequency, const float &Amplitude)
		: seed(Seed),frequency(Frequency),amplitude(Amplitude)
	{}

};
